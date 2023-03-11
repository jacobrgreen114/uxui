
// Copyright (c) 2023 Jacob R. Green
// All Rights Reserved.

#pragma once

#include "control/content_control.hpp"

namespace muchcool::uxui {

class Application;

/*
 * Enums
 */

enum class WindowState { Normal, Minimized, Maximized };

/*
 * Events
 */

class ClosingEvent final : public Event {
 public:
  bool Cancel = false;
};

struct SizeEvent final : public Event {
  const uword Width;
  const uword Height;
};

struct PositionEventArgs final : public Event {
  const iword Left;
  const iword Top;
};

/*
 * Window
 */

class Window : public ContentControl {
  UXUI_INTERNAL
  Application* _application;
  GLFWwindow* _handle;

  Shared<rndr::RenderSurface> _renderSurface;

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

  iword GetPosX() const {
    auto left = 0;
    glfwGetWindowPos(_handle, &left, null);
    return left;
  }

  iword GetPosY() const {
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

  Size on_measure(const Size& available_size) override;
  Rect on_arrange(const Rect& final_rect) override;

  Size calculate_size(const Size& available_size,
                      const Size& required_size) override;

 private:
  void DoClose();

  UXUI_INTERNAL

  void UpdateLayout();

  void InvokeClose();
  void InvokeSizeChanged(uword width, uword height);
  void InvokeFramebufferSizeChanged(uword width, uword height);
  void InvokePosChanged(iword x, iword y);
  void InvokeContentScaleChanged(float scaleX, float scaleY);
  void InvokeStateChanged(WindowState state);
  void InvokeFocusChanged(bool focused);
};

}  // namespace muchcool::uxui
