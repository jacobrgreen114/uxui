
// Copyright (c) 2022. Jacob R. Green
// All Rights Reserved.

#pragma once

#include "Control.hpp"

namespace uxui {

/**
 * ContentChangedEvent
 */
class ContentChangedEvent : public Event {
public:
  Pointer<UiElement> Content;

  ContentChangedEvent(UiElement* content);
};

/**
 * ContentControl
 */
class ContentControl : public Control {
  Pointer<UiElement> _content;
  HorizontalAlignment _hAlign = HorizontalAlignment::Center;
  VerticalAlignment _vAlign = VerticalAlignment::Center;

public:
  ContentControl() = default;
  ~ContentControl() override = default;

  void SetContent(UiElement* content,
                  HorizontalAlignment hAlign = HorizontalAlignment::Center,
                  VerticalAlignment vAlign = VerticalAlignment::Center);
  UiElement* GetContent() const;

protected:
  ArrayProxy<Pointer<UiElement>> GetChildren() override;

protected:
  virtual void OnContentChanged(ContentChangedEvent& e);

  Size OnMeasure(const Size& availableSize) override;
  Rect OnArrange(const Rect& finalRect) override;
};

} // namespace uxui
