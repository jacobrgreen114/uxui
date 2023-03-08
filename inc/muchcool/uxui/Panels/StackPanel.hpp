
// Copyright (c) 2022. Jacob R. Green
// All Rights Reserved.

#pragma once

#include "Panel.hpp"

namespace uxui {

class StackPanel : public Panel {
  std::vector<Pointer<UiElement>> _children;

public:
  ~StackPanel() override = default;

  void AddChild(UiElement* element);
  void RemoveChild(const UiElement* element);

protected:
  ArrayProxy<Pointer<UiElement>> GetChildren() final;

  Size OnMeasure(const Size& available_size) final;
  Rect OnArrange(const Rect& finalRect) final;
};

} // namespace uxui