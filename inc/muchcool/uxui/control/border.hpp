// Copyright (c) 2023 Jacob R. Green
// All Rights Reserved.

#pragma once

#include "content_control.hpp"

namespace muchcool::uxui {

class Border : public ContentControl {
 protected:
  void on_render(RenderEvent& e) override;
};

}  // namespace muchcool::uxui