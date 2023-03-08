
// Copyright (c) 2022-2023 Jacob R. Green
// All Rights Reserved.

#include "muchcool/uxui/Controls/ContentControl.hpp"

namespace uxui {

/**
 * ContentChangedEvent
 */

ContentChangedEvent::ContentChangedEvent(UiElement *content)
    : Content(content) {}

/**
 * ContentControl
 */

void ContentControl::SetContent(UiElement *content, HorizontalAlignment hAlign,
                                VerticalAlignment vAlign) {
  _content = content;
  _hAlign = hAlign;
  _vAlign = vAlign;

  auto evt = ContentChangedEvent(_content);
  OnContentChanged(evt);
}

UiElement *ContentControl::GetContent() const { return _content; }

void ContentControl::OnContentChanged(ContentChangedEvent &e) {}

Size ContentControl::OnMeasure(const Size &availableSize) {
  if (!_content)
    return Control::OnMeasure(availableSize);

  auto s = _IsSizeSet() ? GetSize() : availableSize;
  auto requiredSize = GetContent()->Measure(s);
  return CalculateSize(s, requiredSize);
}

Rect ContentControl::OnArrange(const Rect &finalRect) {
  if (_content) {
    auto &contentSize = _content->GetDesiredSize();

    // Center content
    auto contentRect = center(finalRect, {{0.0f, 0.0f}, contentSize});

    // Prevent content from pushing off-screen
    contentRect.Offset =
        glm::clamp(contentRect.Offset, {0.0f, 0.0f}, {FLT_MAX, FLT_MAX});

    GetContent()->Arrange(contentRect);
  }

  return Control::OnArrange(finalRect);
}

ArrayProxy<Pointer<UiElement>> ContentControl::GetChildren() {
  if (!_content)
    return {};

  return _content;
}

} // namespace uxui
