
// Copyright (c) 2023 Jacob R. Green
// All Rights Reserved.

#include "muchcool/uxui/control/button.hpp"

#include "muchcool/uxui/control/label.hpp"

namespace muchcool::uxui {

Button::Button(const char* text) { set_content(new Label(text)); }

}  // namespace muchcool::uxui