
// Copyright (c) 2022-2023 Jacob R. Green
// All Rights Reserved.

#include "muchcool/uxui/Controls/Button.hpp"

#include "muchcool/uxui/Controls/Label.hpp"

namespace uxui {

Button::Button(const char *text) { SetContent(new Label(text)); }

} // namespace uxui