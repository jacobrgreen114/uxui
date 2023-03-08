
// Copyright (c) 2022-2023. Jacob R. Green
// All Rights Reserved.

#pragma once

#include "Controls/ContentControl.hpp"

namespace uxui {

class Application;

/*
 * Enums
 */

enum class WindowState {
  Normal,
  Minimized,
  Maximized
};

/*
 * Events
 */

class ClosingEvent final : public Event {
public:
  bool Cancel = false;
};

struct SizeEvent final : public Event {
  const uintn Width;
  const uintn Height;
};

struct PositionEventArgs final : public Event {
  const intn Left;
  const intn Top;
};

/*
 * Window
 */

class Window : public ContentControl {
  UXUI_INTERNAL
  Application* _application;
  GLFWwindow* _handle;

  Pointer<rndr::RenderSurface> _renderSurface;

  vk::Semaphore _imageAvailableSemaphore;
  vk::Semaphore _renderFinishedSemaphore;

  bool _closed = false;

  std::string _title;

  WindowState _windowState = WindowState::Normal;

  bool _framebuffer_modified = false;

public:
  Window(const char* title, uint32 width, uint32 height);
  ~Window() noexcept override;

  void Show();
  void Hide();

  void Close();

  intn GetPosX() const {
    auto left = 0;
    glfwGetWindowPos(_handle, &left, null);
    return left;
  }

  intn GetPosY() const {
    auto top = 0;
    glfwGetWindowPos(_handle, null, &top);
    return top;
  }

  const std::string& GetTitle() const { return _title; }
  void SetTitle(const char* title);

  bool IsClosed() const { return _closed; };

protected:
  virtual void OnClosing(ClosingEvent& e);
  virtual void OnClosed(Event& e);

  virtual void OnSizeChanged(SizeEvent& e);
  virtual void OnPosChanged(PositionEventArgs& e);

  virtual void OnFocusChanged(FocusEvent& e);

  Size OnMeasure(const Size& available_size) override;
  Rect OnArrange(const Rect& final_rect) override;

  Size CalculateSize(const Size& available_size,
                     const Size& required_size) override;

private:
  void DoClose();

  UXUI_INTERNAL

  void UpdateLayout();

  void InvokeClose();
  void InvokeSizeChanged(uintn width, uintn height);
  void InvokeFramebufferSizeChanged(uintn width, uintn height);
  void InvokePosChanged(intn x, intn y);
  void InvokeContentScaleChanged(float scaleX, float scaleY);
  void InvokeStateChanged(WindowState state);
  void InvokeFocusChanged(bool focused);
};

} // namespace uxui
