
// Copyright (c) 2022. Jacob R. Green
// All Rights Reserved.

#pragma once

#include "../DataTypes.hpp"
#include "../UIElement.hpp"

namespace uxui {

/**
 * Control
 */
class Control : public UiElement {
private:
  Color _background;
  Color _foreground;

public:
  Control();
  ~Control() override = default;

  inline auto& GetBackground() const { return _background; }
  inline auto& GetForeground() const { return _foreground; }

  inline void SetBackground(const Color& color) { _background = color; }
  inline void SetForeground(const Color& color) { _foreground = color; }

protected:
  void OnRender(RenderEvent& e) override;
};

} // namespace uxui