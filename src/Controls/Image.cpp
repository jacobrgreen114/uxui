
// Copyright (c) 2022-2023 Jacob R. Green
// All Rights Reserved.

#include "muchcool/uxui/Controls/Image.hpp"

#include "muchcool/uxui/Application.hpp"

namespace uxui {

Image::Image(const char *path) {
  _bitmap =
      new xgdi::Bitmap(Application::GetCurrent()->GetGraphicsContext(), path);
  SetSize({_bitmap->GetWidth(), _bitmap->GetHeight()});
}

void Image::OnRender(RenderEvent &e) {
  e.Context.DrawBitmap(GetFinalRect(), _bitmap);
}

} // namespace uxui