// Copyright (c) 2023 Jacob R. Green
// All Rights Reserved.

#include "muchcool/uxui/control/label.hpp"
#include "muchcool/uxui/application.hpp"

namespace muchcool::uxui {

Label::Label(const char* text) : _padding(0.0f, 0.0f, 0.0f, 0.0f) {
  set_background(Color::Transparent);

  auto font = xgdi::Font::Load(Application::GetCurrent()->GetGraphicsContext(),
                               xgdi::Font::SegoeUI, 12);
  _formattedText = new xgdi::FormattedText(font, text);
}

void Label::on_render(RenderEvent& e) {
  auto point = final_rect().Offset;
  auto& pad = padding();

  point.x += pad.l;
  point.y += pad.t + _formattedText->font()->baseline_y();

  e.Context.draw_rectangle(final_rect(), {}, background());
  e.Context.draw_formatted_text(point, *_formattedText, foreground());
}

// TODO : Fix background height size and or vertical alignment
Size Label::on_measure(const Size& availableSize) {
  auto& font = _formattedText->font();
  auto& text = _formattedText->text();
  auto lineHeight = font->line_height();

  auto requiredSize = Size{0, lineHeight};

  auto curLineWidth = 0.0f;

  for (auto c : text) {
    if (c == '\n') {
      requiredSize.y += lineHeight;
      requiredSize.x = glm::max(requiredSize.x, curLineWidth);
      curLineWidth = 0.0f;
    } else {
      auto& glyph = font->glyph(c);
      curLineWidth += glyph.advance();
    }
  }
  requiredSize.x = glm::max(requiredSize.x, curLineWidth);

  requiredSize += padding();

  return calculate_size(availableSize, requiredSize);
}

Rect Label::on_arrange(const Rect& finalRect) {
  return Control::on_arrange(finalRect);
}

}  // namespace muchcool::uxui