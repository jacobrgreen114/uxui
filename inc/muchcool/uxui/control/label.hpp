// Copyright (c) 2023 Jacob R. Green
// All Rights Reserved.

#pragma once

#include "control.hpp"

namespace muchcool::uxui {

class Label : public Control {
  Shared<xgdi::FormattedText> _formattedText;

  Radial _padding;

 public:
  Label(const char* text);
  ~Label() override = default;

  auto& padding() const { return _padding; }
  void set_padding(const Radial& padding) { _padding = padding; }

 protected:
  void on_render(RenderEvent& e) override;

  Size on_measure(const Size& availableSize) override;
  Rect on_arrange(const Rect& finalRect) override;
};

}  // namespace muchcool::uxui