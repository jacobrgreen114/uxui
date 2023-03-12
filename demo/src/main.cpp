
// Copyright (c) 2023 Jacob R. Green
// All Rights Reserved.

#include <muchcool/uxui.hpp>

#define loop while (true)

using namespace muchcool;
using namespace muchcool::uxui;

constexpr auto lorem_ipsum = std::string_view{
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit,sed do\n"
    "eiusmod tempor incididunt ut labore et dolore magna liqua. Utenim\n"
    "ad minim veniam, quis nostrud exercitation llamco laboris nisi ut\n"
    "aliquip ex ea commodo consequat. Duis aute rure dolor in\n"
    "reprehenderit in voluptate velit esse cillum olore eu fugiat nulla\n"
    "pariatur. Excepteur sint occaecat cupidatat nonproident, sunt in\n"
    "culpa qui officia deserunt mollit anim id estlaborum."};

class MainWindow : public Window {
 public:
  MainWindow() : Window("Uxui Demo Window", 1280, 720) {
    set_background(Color::Gray);

    const auto button = new Button("Button");
    button->set_size({200, 200});

    const auto label = new Label("Hello, World!");
    label->set_size({100, 100});
    label->set_background(Color::MidnightGreen);
    label->set_foreground(Color::RoseGold);
    label->set_padding({5});

    const auto label2 = new Label(lorem_ipsum.data());
    label2->set_background(Color::Black);
    label2->set_foreground(Color::White);
    label2->set_padding({25});

    const auto stacker = new StackPanel();
    stacker->add_child(button);
    stacker->add_child(label);
    stacker->add_child(label2);

    const auto grid_label0 = new Label("Label0");
    const auto grid_label1 = new Label("Label1");
    const auto grid_label2 = new Label("Label2");
    new Label("Label3");

    const auto image = new Image(
        "C:/Users/jacob/Pictures/beautiful-lake-amp-mountains-wallpaper.JPG");
    image->set_size(SIZE_FILL);

    const auto grid = new GridPanel(3, 2);
    grid->set_size({500, 100});
    grid->set_background(Color::Amber);
    grid->add_child(grid_label0, 0, 0);
    grid->add_child(grid_label1, 2, 0);
    grid->add_child(grid_label2, 0, 1);
    grid->add_child(image, 1, 0, 1, 2);

    stacker->add_child(grid);

    set_content(stacker);
  }

  static auto create() { return Shared{new MainWindow()}; }
};

class App : public Application {
 public:
  App(int argc, const char** argv)
      : Application(argc, argv, ShutdownMode::LastWindow) {}

  ~App() override = default;

  static auto create(int argc, const char** argv) {
    return Shared{new App(argc, argv)};
  }

 private:
  void OnStartup(const StartupEventArgs& e) override {
    Application::OnStartup(e);
    auto mainWindow = MainWindow::create();
    SetMainWindow(mainWindow.get());
    mainWindow->Show();
  }

  void OnShutdown(ShutdownEventArgs& e) override { Application::OnShutdown(e); }
};

int main(int argc, const char** argv) {
  auto app = App::create(argc, argv);
  auto exitCode = app->Run();
  app = null;

  return exitCode;
}

auto WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
             int nShowCmd) -> int {
  return main(0, null);
}