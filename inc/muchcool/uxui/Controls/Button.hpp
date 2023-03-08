
#pragma once

#include "ContentControl.hpp"

namespace uxui {

class Button : public ContentControl {
public:
  Button() = default;
  Button(const char* text);
  ~Button() override = default;

  inline static Pointer<Button> New() { return new Button(); }
};

} // namespace UXUI