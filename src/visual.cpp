

// Copyright (c) 2023 Jacob R. Green
// All Rights Reserved.

#include "muchcool/uxui/visual.hpp"

namespace muchcool::uxui {

void Visual::AddChild(Shared<Visual> visual) { _children.emplace_back(visual); }

bool Visual::RemoveChild(Shared<Visual> visual) {
  auto erasedCount =
      std::erase_if(_children, [&](auto& child) { return child == visual; });
  return erasedCount > 0;
}

void Visual::OnRender(DrawingContext& context) {}

}  // namespace muchcool::uxui