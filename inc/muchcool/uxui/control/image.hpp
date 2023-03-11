
// Copyright (c) 2023 Jacob R. Green
// All Rights Reserved.

#pragma once

#include "control.hpp"

namespace muchcool::uxui {

class Image : public Control {
  Shared<xgdi::Bitmap> _bitmap;

 public:
  Image(const char* path);
  ~Image() override = default;

  auto image_width() const { return _bitmap->GetWidth(); }
  auto image_height() const { return _bitmap->GetHeight(); }

 protected:
  void on_render(RenderEvent& e) override;
};

}  // namespace muchcool::uxui