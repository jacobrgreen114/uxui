
// Copyright (c) 2023 Jacob R. Green
// All Rights Reserved.

#pragma once

#include "content_control.hpp"

namespace muchcool::uxui {

class Button : public ContentControl {
 public:
  Button() = default;
  Button(const char* text);
  ~Button() override = default;

  // static Shared<Button> New() { return Shared{new Button()}; }
};

}  // namespace muchcool::uxui