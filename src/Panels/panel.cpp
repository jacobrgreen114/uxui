
// Copyright (c) 2023 Jacob R. Green
// All Rights Reserved.

#include "muchcool/uxui/panel/panel.hpp"

namespace muchcool::uxui {

#pragma region Panel

void Panel::on_render(RenderEvent& e) {
  if (_background.a > 0.0f) e.Context.draw_rectangle(final_rect(), _background);
}

#pragma endregion

}  // namespace muchcool::uxui