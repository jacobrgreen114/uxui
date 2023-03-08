
// Copyright (c) 2022-2023 Jacob R. Green
// All Rights Reserved.

#include "muchcool/uxui/Panels/StackPanel.hpp"

namespace uxui {

#pragma region StackPanel

ArrayProxy<Pointer<UiElement>> StackPanel::GetChildren() { return _children; }

void StackPanel::AddChild(UiElement *element) {
  if (element->_HasParent())
    throw std::exception();

  _children.emplace_back(element);
}

void StackPanel::RemoveChild(const UiElement *element) {
  for (auto it = std::find(_children.begin(), _children.end(), element);
       it != _children.end(); it = std::find(it, _children.end(), element))
    _children.erase(it);
}

Size StackPanel::OnMeasure(const Size &available_size) {
  auto space_left = available_size;
  auto required = Size{0, 0};

  for (const auto &child : _children) {
    const auto child_size = child->Measure(space_left);
    required.y += child_size.y;
    required.x = glm::max(required.x, child_size.x);

    space_left.y -= child_size.y;
  }

  return CalculateSize(available_size, required);
}

Rect StackPanel::OnArrange(const Rect &finalRect) {
  auto current_pos = finalRect.Offset;

  for (const auto &child : _children) {
    auto child_size = child->GetDesiredSize();
    // child_size.x = finalRect.Size.x;

    auto child_rect = Rect{current_pos, child_size};
    child_rect = child->Arrange(child_rect);
    current_pos.y += child_rect.Size.y;
  }

  return Panel::OnArrange(finalRect);
}

#pragma endregion

} // namespace uxui