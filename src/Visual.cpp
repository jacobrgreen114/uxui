

// Copyright (c) 2023 Jacob R. Green
// All Rights Reserved.

#include "muchcool/uxui/Visual.hpp"

namespace uxui {

void Visual::AddChild(Visual *visual) { _children.emplace_back(visual); }

bool Visual::RemoveChild(Visual *visual) {
  auto erasedCount = std::erase_if(
      _children, [visual](auto &child) { return child == visual; });
  return erasedCount > 0;
}

void Visual::OnRender(DrawingContext &context) {}

} // namespace uxui