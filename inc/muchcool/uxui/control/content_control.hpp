
// Copyright (c) 2023 Jacob R. Green
// All Rights Reserved.

#pragma once

#include "control.hpp"

namespace muchcool::uxui {

/**
 * ContentChangedEvent
 */
class ContentChangedEvent : public Event {
 public:
  Shared<UIElement> Content;

  ContentChangedEvent(Shared<UIElement> content);
};

/**
 * ContentControl
 */
class ContentControl : public Control {
  Shared<UIElement> _content;
  HorizontalAlignment _hAlign = HorizontalAlignment::Center;
  VerticalAlignment _vAlign = VerticalAlignment::Center;

 public:
  ContentControl() = default;
  ~ContentControl() override = default;

  auto& content() const { return _content; }

  void set_content(Shared<UIElement> content,
                   HorizontalAlignment hAlign = HorizontalAlignment::Center,
                   VerticalAlignment vAlign = VerticalAlignment::Center);

 protected:
  auto children() const -> ArrayProxy<const Shared<UIElement>> override;

 protected:
  virtual void on_content_changed(ContentChangedEvent& e);

  Size on_measure(const Size& availableSize) override;
  Rect on_arrange(const Rect& finalRect) override;
};

}  // namespace muchcool::uxui
