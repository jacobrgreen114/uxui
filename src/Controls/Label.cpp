// Copyright (c) 2022-2023 Jacob R. Green
// All Rights Reserved.

#include "muchcool/uxui/Controls/Label.hpp"
#include "muchcool/uxui/Application.hpp"

namespace uxui {

Label::Label(const char *text) : _padding(0.0f, 0.0f, 0.0f, 0.0f) {
  SetBackground(Color::Transparent);

  auto font = xgdi::Font::Load(Application::GetCurrent()->GetGraphicsContext(),
                               xgdi::Font::SegoeUI, 12);
  _formattedText = new xgdi::FormattedText(font, text);
}

void Label::OnRender(RenderEvent &e) {
  auto point = GetFinalRect().Offset;
  auto &padding = GetPadding();

  point.x += padding.l;
  point.y += padding.t + _formattedText->GetFont()->GetBaselineY();

  e.Context.DrawRectangle(GetFinalRect(), {}, GetBackground());
  e.Context.DrawFormattedText(point, _formattedText, GetForeground());
}

// TODO : Fix background height size and or vertical alignment
Size Label::OnMeasure(const Size &availableSize) {
  auto &font = _formattedText->GetFont();
  auto &text = _formattedText->GetText();
  auto lineHeight = font->GetLineHeight();

  auto requiredSize = Size{0, lineHeight};

  auto curLineWidth = 0.0f;

  for (auto c : text) {
    if (c == '\n') {
      requiredSize.y += lineHeight;
      requiredSize.x = glm::max(requiredSize.x, curLineWidth);
      curLineWidth = 0.0f;
    } else {
      auto &glyph = font->GetGlyph(c);
      curLineWidth += glyph.GetAdvance();
    }
  }
  requiredSize.x = glm::max(requiredSize.x, curLineWidth);

  requiredSize += GetPadding();

  return CalculateSize(availableSize, requiredSize);
}

Rect Label::OnArrange(const Rect &finalRect) {
  return Control::OnArrange(finalRect);
}

} // namespace uxui