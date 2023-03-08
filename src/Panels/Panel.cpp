
// Copyright (c) 2022-2023 Jacob R. Green
// All Rights Reserved.

#include "muchcool/uxui/Panels/Panel.hpp"

namespace uxui {

#pragma region Panel

void Panel::OnRender(RenderEvent &e) {
  if (_background.a > 0.0f)
    e.Context.DrawRectangle(GetFinalRect(), _background);
}

#pragma endregion

} // namespace uxui