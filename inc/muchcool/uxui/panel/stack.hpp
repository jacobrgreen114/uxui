
// Copyright (c) 2023 Jacob R. Green
// All Rights Reserved.

#pragma once

#include "panel.hpp"

namespace muchcool::uxui {

class StackPanel : public Panel {
  std::vector<Shared<UIElement>> _children;

 public:
  ~StackPanel() override = default;

  void add_child(UIElement* element);
  void remove_child(const UIElement* element);

 protected:
  auto children() const -> ArrayProxy<const Shared<UIElement>> final;

  Size on_measure(const Size& available_size) final;
  Rect on_arrange(const Rect& finalRect) final;
};

}  // namespace muchcool::uxui