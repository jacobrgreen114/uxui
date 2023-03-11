
// Copyright (c) 2023 Jacob R. Green
// All Rights Reserved.

#include "muchcool/uxui/control/content_control.hpp"

namespace muchcool::uxui {

/**
 * ContentChangedEvent
 */

ContentChangedEvent::ContentChangedEvent(Shared<UIElement> content)
    : Content(std::move(content)) {}

/**
 * ContentControl
 */

void ContentControl::set_content(Shared<UIElement> content_,
                                 HorizontalAlignment hAlign,
                                 VerticalAlignment vAlign) {
  _content = std::move(content_);
  _hAlign = hAlign;
  _vAlign = vAlign;

  auto evt = ContentChangedEvent(_content);
  on_content_changed(evt);
}

void ContentControl::on_content_changed(ContentChangedEvent& e) {}

Size ContentControl::on_measure(const Size& availableSize) {
  if (!_content) return Control::on_measure(availableSize);

  auto s = _is_size_set() ? size() : availableSize;
  auto requiredSize = content()->measure(s);
  return calculate_size(s, requiredSize);
}

Rect ContentControl::on_arrange(const Rect& finalRect) {
  if (_content) {
    auto& contentSize = _content->desired_size();

    // Center content
    auto contentRect = center(finalRect, {{0.0f, 0.0f}, contentSize});

    // Prevent content from pushing off-screen
    contentRect.Offset =
        glm::clamp(contentRect.Offset, {0.0f, 0.0f}, {FLT_MAX, FLT_MAX});

    content()->arrange(contentRect);
  }

  return Control::on_arrange(finalRect);
}

auto ContentControl::children() const -> ArrayProxy<const Shared<UIElement>> {
  if (!_content) {
    return {};
  }
  return ArrayProxy(_content);
}

}  // namespace muchcool::uxui
