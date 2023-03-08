
// Copyright (c) 2022-2023 Jacob R. Green
// All Rights Reserved.

#pragma once

#include "muchcool/rndr.hpp"

#include "Window.hpp"

namespace uxui {

enum class ShutdownMode { MainWindow, LastWindow, Explicit };

struct CancelableEventArgs {
  bool Cancel;
};

struct StartupEventArgs {};

struct ShutdownEventArgs : public CancelableEventArgs {
  int ExitCode = 0;
};

class Application : public virtual Object {
  std::vector<std::string_view> _cliArguments;
  ShutdownMode _shutdownMode;
  bool _explicitShutdown = false;
  std::vector<Pointer<Window>> _windows;
  Pointer<Window> _mainWindow;

  Pointer<rndr::GraphicsContext> _graphicsContext;

protected:
  Application(int argc = 0, const char **argv = nullptr,
              ShutdownMode shutdownMode = ShutdownMode::MainWindow);

  virtual ~Application();

  virtual void OnStartup(const StartupEventArgs &e);

  virtual void OnShutdown(ShutdownEventArgs &e);

public:
  int Run();

  inline ShutdownMode GetShutdownMode() const { return _shutdownMode; }
  inline void SetShutdownMode(ShutdownMode mode) { _shutdownMode = mode; }

  inline Window *GetMainWindow() const { return _mainWindow; }
  inline void SetMainWindow(Window *window) { _mainWindow = window; }

  static Application *GetCurrent();

private:
  void Mainloop() const;
  bool ShutdownRequirementsMet() const;

  friend Window;

  void RegisterWindow(Window *window);
  void UnregisterWindow(Window *window);

  UXUI_INTERNAL

  inline rndr::GraphicsContext *GetGraphicsContext() const {
    return _graphicsContext;
  }
};

} // namespace uxui