// Copyright (c) 2022. Jacob R. Green
// All Rights Reserved.

#pragma once

#include "ContentControl.hpp"

namespace uxui {

class Border : public ContentControl {

protected:
  void OnRender(RenderEvent& e) override;
};

} // namespace UXUI