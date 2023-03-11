
// Copyright (c) 2023 Jacob R. Green
// All Rights Reserved.

#include "muchcool/uxui/application.hpp"

#include <GLFW/glfw3.h>

namespace muchcool::uxui {

std::array<const char*, 1> instanceLayers = {"VK_LAYER_KHRONOS_validation"};

std::array<const char*, 2> instanceExtensions = {
    VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WIN32_SURFACE_EXTENSION_NAME};

std::array<const char*, 0> deviceLayers = {};

std::array<const char*, 1> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

Application* currentApplication = null;

Application::Application(int argc, const char** argv, ShutdownMode shutdownMode)
    : _shutdownMode(shutdownMode) {
  if (currentApplication != null)
    throw std::exception(
        "Only one instance of application can exist at a time.");

  glfwInit();

  currentApplication = this;

  _cliArguments.reserve(argc);
  for (auto i = 0; i < argc; ++i) _cliArguments.emplace_back(argv[i]);

  _graphicsContext = rndr::GraphicsContext::create();
}

Application::~Application() {
  _mainWindow = null;
  for (auto& window : _windows) window->Close();

  _windows.clear();

  currentApplication = null;
  glfwTerminate();
}

int Application::Run() {
  auto startupArgs = StartupEventArgs();
  OnStartup(startupArgs);

  ShutdownEventArgs shutdownArgs;

  do {
    Mainloop();
    shutdownArgs = ShutdownEventArgs();
    OnShutdown(shutdownArgs);
  } while (shutdownArgs.Cancel);

  return shutdownArgs.ExitCode;
}

void Application::Mainloop() const {
  while (!ShutdownRequirementsMet()) {
    glfwWaitEvents();
    glfwPollEvents();
  }
}

Application* Application::GetCurrent() { return currentApplication; }

void Application::OnStartup(const StartupEventArgs& e) {}

void Application::OnShutdown(ShutdownEventArgs& e) {}

bool Application::ShutdownRequirementsMet() const {
  switch (_shutdownMode) {
    case ShutdownMode::MainWindow:
      return !_mainWindow || _mainWindow->IsClosed();
    case ShutdownMode::LastWindow:
      return _windows.size() < 1;
    case ShutdownMode::Explicit:
      return _explicitShutdown;
    default:
      throw std::exception("Unknown shutdown mode");
  }
}

void Application::RegisterWindow(Window* window) {
  _windows.emplace_back(window);
}

void Application::UnregisterWindow(Window* window) {
  if (_mainWindow == window) {
    _mainWindow = null;
  }
  erase_if(_windows, [window](auto& ptr) -> bool { return ptr == window; });
}

}  // namespace muchcool::uxui
