
// Copyright (c) 2023 Jacob R. Green
// All Rights Reserved.

#include "muchcool/uxui/control/image.hpp"

#include "muchcool/uxui/application.hpp"

namespace muchcool::uxui {

Image::Image(const char* path) {
  _bitmap =
      new xgdi::Bitmap(Application::GetCurrent()->GetGraphicsContext(), path);
  set_size({_bitmap->GetWidth(), _bitmap->GetHeight()});
}

void Image::on_render(RenderEvent& e) {
  e.Context.draw_bitmap(final_rect(), *_bitmap);
}

}  // namespace muchcool::uxui