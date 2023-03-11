

// Copyright (c) 2023 Jacob R. Green
// All Rights Reserved.

#include "muchcool/uxui/control/control.hpp"

namespace muchcool::uxui {

/*
 * Control
 */

Control::Control() : _background(Color::White), _foreground(Color::Black) {}

void Control::on_render(RenderEvent& e) {
  auto& rect = final_rect();
  auto& color = background();
  e.Context.draw_rectangle(rect, color);
}

}  // namespace muchcool::uxui
