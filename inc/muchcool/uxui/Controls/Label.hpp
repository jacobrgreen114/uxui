// Copyright (c) 2022. Jacob R. Green
// All Rights Reserved.

#pragma once

#include "Control.hpp"

namespace uxui {

class Label : public Control {

  Pointer<xgdi::FormattedText> _formattedText;

  Radial _padding;

public:
  Label(const char* text);
  ~Label() override = default;

  inline auto& GetPadding() const { return _padding; }
  inline void SetPadding(const Radial& padding) { _padding = padding; }

protected:
  void OnRender(RenderEvent& e) override;

  Size OnMeasure(const Size& availableSize) override;
  Rect OnArrange(const Rect& finalRect) override;
};

} // namespace uxui