

// Copyright (c) 2022-2023 Jacob R. Green
// All Rights Reserved.

#include "muchcool/uxui/Controls/Control.hpp"

namespace uxui {

/*
 * Control
 */

Control::Control() : _background(Color::White), _foreground(Color::Black) {}

void Control::OnRender(RenderEvent &e) {
  auto &rect = GetFinalRect();
  auto &color = GetBackground();
  e.Context.DrawRectangle(rect, color);
}

} // namespace uxui
