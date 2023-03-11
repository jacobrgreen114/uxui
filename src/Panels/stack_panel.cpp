
// Copyright (c) 2023 Jacob R. Green
// All Rights Reserved.

#include "muchcool/uxui/panel/stack.hpp"

namespace muchcool::uxui {

#pragma region StackPanel

auto StackPanel::children() const -> ArrayProxy<const Shared<UIElement>> {
  return _children;
}

void StackPanel::add_child(UIElement* element) {
  if (element->_has_parent()) throw std::exception();

  _children.emplace_back(element);
}

void StackPanel::remove_child(const UIElement* element) {
  for (auto it = std::find(_children.begin(), _children.end(), element);
       it != _children.end(); it = std::find(it, _children.end(), element))
    _children.erase(it);
}

Size StackPanel::on_measure(const Size& available_size) {
  auto space_left = available_size;
  auto required = Size{0, 0};

  for (const auto& child : _children) {
    const auto child_size = child->measure(space_left);
    required.y += child_size.y;
    required.x = glm::max(required.x, child_size.x);

    space_left.y -= child_size.y;
  }

  return calculate_size(available_size, required);
}

Rect StackPanel::on_arrange(const Rect& finalRect) {
  auto current_pos = finalRect.Offset;

  for (const auto& child : _children) {
    auto child_size = child->desired_size();
    // child_size.x = finalRect.Size.x;

    auto child_rect = Rect{current_pos, child_size};
    child_rect = child->arrange(child_rect);
    current_pos.y += child_rect.Size.y;
  }

  return Panel::on_arrange(finalRect);
}

#pragma endregion

}  // namespace muchcool::uxui