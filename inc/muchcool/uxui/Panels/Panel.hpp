
// Copyright (c) 2022. Jacob R. Green
// All Rights Reserved.

#pragma once

#include "../UIElement.hpp"

namespace uxui {

class Panel : public UiElement {
  Color _background = Color::Transparent;

public:
  Panel() = default;
  ~Panel() override = default;

  void SetBackground(const Color& c) { _background = c; }

protected:
  void OnRender(RenderEvent& e) override;
};

class DockPanel {};

} // namespace uxui