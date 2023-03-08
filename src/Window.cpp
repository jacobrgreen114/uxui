
// Copyright (c) 2022-2023 Jacob R. Green
// All Rights Reserved.

#include "muchcool/uxui/Window.hpp"

#include "muchcool/uxui/Application.hpp"

namespace uxui {

Window *GetWindowPtr(GLFWwindow *window) {
  return static_cast<Window *>(glfwGetWindowUserPointer(window));
}

#pragma region Window Callbacks

void WindowCloseCallback(GLFWwindow *_window) {
  GetWindowPtr(_window)->InvokeClose();
}

void WindowSizeCallback(GLFWwindow *_window, int width, int height) {
  GetWindowPtr(_window)->InvokeSizeChanged(width, height);
}

void FramebufferSizeCallback(GLFWwindow *_window, int width, int height) {
  GetWindowPtr(_window)->InvokeFramebufferSizeChanged(width, height);
}

void WindowPosCallback(GLFWwindow *_window, int xpos, int ypos) {
  GetWindowPtr(_window)->InvokePosChanged(xpos, ypos);
}

void WindowContentScaleCallback(GLFWwindow *_window, float scaleX,
                                float scaleY) {
  GetWindowPtr(_window)->InvokeContentScaleChanged(scaleX, scaleY);
}

void WindowFocusCallback(GLFWwindow *_window, int focused) {
  GetWindowPtr(_window)->InvokeFocusChanged(focused == GLFW_TRUE);
}

void WindowRefreshCallback(GLFWwindow *_window) {
  const auto window = GetWindowPtr(_window);

  window->UpdateLayout();
  auto renderEvent = RenderEvent(window->_renderSurface);
  renderEvent.Context.StartRecording();
  window->DispatchRenderEvent(renderEvent);
  renderEvent.Context.EndRecording();

  renderEvent.Context.Submit();
}

void WindowIconifiedCallback(GLFWwindow *_window, int iconified) {
  GetWindowPtr(_window)->InvokeStateChanged(
      iconified == GLFW_TRUE ? WindowState::Minimized : WindowState::Normal);
}

void WindowMaximizedCallback(GLFWwindow *_window, int maximized) {
  GetWindowPtr(_window)->InvokeStateChanged(
      maximized == GLFW_TRUE ? WindowState::Maximized : WindowState::Normal);
}

#pragma endregion

#pragma region Input Callbacks

KeyButton ToKeyButton(int key) { return static_cast<KeyButton>(key); }

KeyState ToKeyState(int action) { return static_cast<KeyState>(action); }

MouseButton ToMouseButton(int button) {
  return static_cast<MouseButton>(button);
}

MouseButtonState ToMouseButtonState(int action) {
  return static_cast<MouseButtonState>(action);
}

void KeyCallback(GLFWwindow *_window, int key, int scancode, int action,
                 int mods) {
  auto window = GetWindowPtr(_window);

  auto keyButton = ToKeyButton(key);
  auto keyState = ToKeyState(action);
  auto keyEvent = KeyEvent(keyButton, keyState);

  window->DispatchKeyEvent(keyEvent);
}

void CursorPosCallback(GLFWwindow *_window, double pos_x, double pos_y) {
  auto window = GetWindowPtr(_window);

  auto position = Point(pos_x, pos_y);
  auto mouseEvent = MouseEvent(position);

  window->DispatchMouseMoveEvent(mouseEvent);
}

void CursorEnterCallback(GLFWwindow *_window, int entered) {}

void MouseButtonCallback(GLFWwindow *_window, int _button, int _action,
                         int _mods) {
  const auto window = GetWindowPtr(_window);

  double pos_x, pos_y;
  glfwGetCursorPos(_window, &pos_x, &pos_y);

  const auto position = Point(pos_x, pos_y);
  const auto button = ToMouseButton(_button);
  const auto state = ToMouseButtonState(_action);
  auto button_event = MouseButtonEvent(position, button, state);

  window->DispatchMouseButtonEvent(button_event);
}

void ScrollCallback(GLFWwindow *_window, double offset_x, double offset_y) {}

void DropCallback(GLFWwindow *_window, int count, const char **paths) {}

#pragma endregion

#pragma region Construction / Destruction

Window::Window(const char *title, uint32 width, uint32 height) {
  _application = Application::GetCurrent();
  if (!_application)
    throw std::exception("An application must be create before a window");

  glfwDefaultWindowHints();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
  // glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

  _handle = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height),
                             title, null, null);
  glfwSetWindowUserPointer(_handle, this);

  glfwSetWindowSizeLimits(_handle, 1, 1, INT16_MAX, INT16_MAX);

  glfwSetWindowCloseCallback(_handle, WindowCloseCallback);
  glfwSetWindowSizeCallback(_handle, WindowSizeCallback);
  glfwSetFramebufferSizeCallback(_handle, FramebufferSizeCallback);
  glfwSetWindowPosCallback(_handle, WindowPosCallback);
  glfwSetWindowContentScaleCallback(_handle, WindowContentScaleCallback);
  glfwSetWindowIconifyCallback(_handle, WindowIconifiedCallback);
  glfwSetWindowMaximizeCallback(_handle, WindowMaximizedCallback);
  glfwSetWindowFocusCallback(_handle, WindowFocusCallback);
  glfwSetWindowRefreshCallback(_handle, WindowRefreshCallback);

  glfwSetKeyCallback(_handle, KeyCallback);
  glfwSetCursorPosCallback(_handle, CursorPosCallback);
  glfwSetCursorEnterCallback(_handle, CursorEnterCallback);
  glfwSetMouseButtonCallback(_handle, MouseButtonCallback);
  glfwSetScrollCallback(_handle, ScrollCallback);
  glfwSetDropCallback(_handle, DropCallback);

  _application->RegisterWindow(this);

  int w, h, x, y;
  glfwGetWindowSize(_handle, &w, &h);
  glfwGetWindowPos(_handle, &x, &y);

  SetSize({width, height});

  const auto win32_handle = glfwGetWin32Window(_handle);

  _renderSurface = rndr::RenderSurface::New(_application->GetGraphicsContext(),
                                            win32_handle);

  const auto &renderSurface = *_renderSurface;
  auto &graphics_context = renderSurface.GetGraphicsContext();
  auto &instance = graphics_context->GetInstance();
  auto &physical_device = graphics_context->GetPhysicalDevice();
  auto &device = graphics_context->GetDevice();

  _imageAvailableSemaphore = device.createSemaphore({});
  _renderFinishedSemaphore = device.createSemaphore({});

  //_renderThread = std::jthread(RenderLoop, this);
}

Window::~Window() noexcept { Close(); }

#pragma endregion

#pragma region Methods

void Window::Show() { glfwShowWindow(_handle); }
void Window::Hide() { glfwHideWindow(_handle); }

void Window::Close() { InvokeClose(); }

void Window::DoClose() {
  _closed = true;

  auto &renderSurface = *_renderSurface;
  auto &graphicsContext = *renderSurface.GetGraphicsContext();
  auto &instance = graphicsContext.GetInstance();
  auto &device = graphicsContext.GetDevice();

  device.destroy(_renderFinishedSemaphore);
  device.destroy(_imageAvailableSemaphore);

  glfwDestroyWindow(_handle);

  auto application = Application::GetCurrent();
  if (application)
    application->UnregisterWindow(this);

  _handle = null;
}

#pragma endregion

#pragma region Getters / Setters

void Window::SetTitle(const char *title) {
  _title = title;
  glfwSetWindowTitle(_handle, title);
}

#pragma endregion

#pragma region Virtual Methods

void Window::OnClosing(ClosingEvent &e) {}

void Window::OnClosed(Event &e) {}

void Window::OnSizeChanged(SizeEvent &e) {}

void Window::OnPosChanged(PositionEventArgs &e) {}

void Window::OnFocusChanged(FocusEvent &e) {}

#pragma endregion

#pragma region Virtual Overrides

Size Window::OnMeasure(const Size &available_size) {
  ContentControl::OnMeasure(available_size);
  return GetSize();
}
Rect Window::OnArrange(const Rect &final_rect) {
  ContentControl::OnArrange(final_rect);
  return {{}, GetSize()};
}

Size Window::CalculateSize(const Size &available_size,
                           const Size &required_size) {
  return GetSize();
}

void Window::UpdateLayout() {
  Measure(GetSize());
  Arrange({{}, GetSize()});
}

#pragma endregion

#pragma region Callbacks

void Window::InvokeClose() {
  if (_closed)
    return;

  auto eventArgs = ClosingEvent();
  OnClosing(eventArgs);
  if (!eventArgs.Cancel)
    DoClose();
}

void Window::InvokeSizeChanged(uintn width, uintn height) {
  SetSize({static_cast<float>(width), static_cast<float>(height)});

  auto eventArgs = SizeEvent{.Width = width, .Height = height};
  OnSizeChanged(eventArgs);
}

void Window::InvokeFramebufferSizeChanged(uintn width, uintn height) {
  if (_windowState != WindowState::Minimized) {
    _renderSurface->UpdateSwapchain();
    _framebuffer_modified = true;
  }
}

void Window::InvokePosChanged(intn x, intn y) {
  auto eventArgs = PositionEventArgs{.Left = x, .Top = y};
  OnPosChanged(eventArgs);
}

void Window::InvokeContentScaleChanged(float scaleX, float scaleY) {}

void Window::InvokeStateChanged(WindowState state) { _windowState = state; }

void Window::InvokeFocusChanged(bool focused) {
  auto e = FocusEvent(focused);
  OnFocusChanged(e);
}

#pragma endregion

} // namespace uxui
