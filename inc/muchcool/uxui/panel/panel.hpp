
// Copyright (c) 2023 Jacob R. Green
// All Rights Reserved.

#pragma once

#include "../uielement.hpp"

namespace muchcool::uxui {

class Panel : public UIElement {
  Color _background = Color::Transparent;

 public:
  Panel() = default;
  ~Panel() override = default;

  void set_background(const Color& c) { _background = c; }

 protected:
  void on_render(RenderEvent& e) override;
};

class DockPanel {};

}  // namespace muchcool::uxui