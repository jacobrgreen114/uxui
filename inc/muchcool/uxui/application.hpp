
// Copyright (c) 2023 Jacob R. Green
// All Rights Reserved.

#pragma once

#include "muchcool/rndr.hpp"

#include "window.hpp"

namespace muchcool::uxui {

enum class ShutdownMode { MainWindow, LastWindow, Explicit };

struct CancelableEventArgs {
  bool Cancel;
};

struct StartupEventArgs {};

struct ShutdownEventArgs : public CancelableEventArgs {
  int ExitCode = 0;
};

class Application : public Object {
  std::vector<std::string_view> _cliArguments;
  ShutdownMode _shutdownMode;
  bool _explicitShutdown = false;
  std::vector<Shared<Window>> _windows;
  Shared<Window> _mainWindow;

  Shared<rndr::GraphicsContext> _graphicsContext;

 protected:
  Application(int argc = 0, const char** argv = nullptr,
              ShutdownMode shutdownMode = ShutdownMode::MainWindow);

  virtual ~Application();

  virtual void OnStartup(const StartupEventArgs& e);

  virtual void OnShutdown(ShutdownEventArgs& e);

 public:
  int Run();

  ShutdownMode GetShutdownMode() const { return _shutdownMode; }
  void SetShutdownMode(ShutdownMode mode) { _shutdownMode = mode; }

  constexpr auto& GetMainWindow() const { return _mainWindow; }
  constexpr void SetMainWindow(Shared<Window> window) {
    _mainWindow = std::move(window);
  }

  static Application* GetCurrent();

 private:
  void Mainloop() const;
  bool ShutdownRequirementsMet() const;

  friend Window;

  void RegisterWindow(Window* window);
  void UnregisterWindow(Window* window);

  UXUI_INTERNAL

  auto& GetGraphicsContext() const { return _graphicsContext; }
};

}  // namespace muchcool::uxui