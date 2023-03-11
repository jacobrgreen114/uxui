
// Copyright (c) 2023 Jacob R. Green
// All Rights Reserved.

#pragma once

#include "../datatypes.hpp"
#include "../uielement.hpp"

namespace muchcool::uxui {

/**
 * Control
 */
class Control : public UIElement {
 private:
  Color _background;
  Color _foreground;

 public:
  Control();
  ~Control() override = default;

  auto& background() const { return _background; }
  auto& foreground() const { return _foreground; }

  void set_background(const Color& color) { _background = color; }
  void set_foreground(const Color& color) { _foreground = color; }

 protected:
  void on_render(RenderEvent& e) override;
};

}  // namespace muchcool::uxui