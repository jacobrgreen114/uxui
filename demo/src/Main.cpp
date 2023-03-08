
// Copyright (c) 2022-2023 Jacob R. Green
// All Rights Reserved.

#include <muchcool/uxui.hpp>

#define loop while (true)

using namespace uxui;

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
    SetBackground(Color::Gray);

    const auto button = new Button("Button");
    button->SetSize({200, 200});

    const auto label = new Label("Hello, World!");
    label->SetSize({100, 100});
    label->SetBackground(Color::MidnightGreen);
    label->SetForeground(Color::RoseGold);
    label->SetPadding({5});

    const auto label2 = new Label(lorem_ipsum.data());
    label2->SetBackground(Color::Black);
    label2->SetForeground(Color::White);
    label2->SetPadding({25});

    const auto stacker = new StackPanel();
    stacker->AddChild(button);
    stacker->AddChild(label);
    stacker->AddChild(label2);

    const auto grid_label0 = new Label("Label0");
    const auto grid_label1 = new Label("Label1");
    const auto grid_label2 = new Label("Label2");
    new Label("Label3");

    const auto image = new Image(
        "C:/Users/jacob/Pictures/beautiful-lake-amp-mountains-wallpaper.JPG");
    image->SetSize(SIZE_FILL);

    const auto grid = new GridPanel(3, 2);
    grid->SetSize({500, 100});
    grid->SetBackground(Color::Amber);
    grid->AddChild(grid_label0, 0, 0);
    grid->AddChild(grid_label1, 2, 0);
    grid->AddChild(grid_label2, 0, 1);
    grid->AddChild(image, 1, 0, 1, 2);

    stacker->AddChild(grid);

    SetContent(stacker);
  }

  static Pointer<MainWindow> New() { return new MainWindow(); }
};

class App : public Application {
public:
  using pointer_t = Pointer<App>;

  App(int argc, const char **argv)
      : Application(argc, argv, ShutdownMode::LastWindow) {}

  ~App() override = default;

  static pointer_t New(int argc, const char **argv) {
    return new App(argc, argv);
  }

private:
  void OnStartup(const StartupEventArgs &e) override {
    Application::OnStartup(e);
    auto mainWindow = MainWindow::New();
    SetMainWindow(mainWindow);
    mainWindow->Show();
  }

  void OnShutdown(ShutdownEventArgs &e) override { Application::OnShutdown(e); }
};

int main(int argc, const char **argv) {
  auto app = App::New(argc, argv);
  auto exitCode = app->Run();
  app = null;

  return exitCode;
}