
// Copyright (c) 2022. Jacob R. Green
// All Rights Reserved.

#pragma once

#include "Control.hpp"

namespace uxui {

class Image : public Control {

  Pointer<xgdi::Bitmap> _bitmap;

public:
  Image(const char* path);
  ~Image() override = default;

  inline auto GetImageWidth() const { return _bitmap->GetWidth(); }
  inline auto GetImageHeight() const { return _bitmap->GetHeight(); }

protected:
  void OnRender(RenderEvent& e) override;
};

} // namespace uxui