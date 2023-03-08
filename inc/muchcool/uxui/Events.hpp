
// Copyright (c) 2022. Jacob R. Green
// All Rights Reserved.

#pragma once

#include "DataTypes.hpp"
#include "Enums.hpp"

namespace uxui {

class UiElement;

class Event {
public:
  bool Handled;
  const DateTime Time;

  Event();

  inline bool IsHandled() const { return Handled; }
  inline void MarkHandled() { Handled = true; }
};

class KeyEvent : public Event {
public:
  const KeyButton Key;
  const KeyState State;

  KeyEvent(KeyButton key, KeyState state);
};

class MouseEvent : public Event {
public:
  const Point Position;

  MouseEvent(Point pos);

  Point GetPosition(const UiElement* relativeTo);
};

class MouseButtonEvent : public MouseEvent {
public:
  const MouseButton Button;
  const MouseButtonState State;

  MouseButtonEvent(Point pos, MouseButton button, MouseButtonState state);
};

using MouseEnterEvent = MouseEvent;

class FocusEvent : public Event {
public:
  const bool Focused;

  FocusEvent(bool focused);
};

using DrawingContext = xgdi::DrawingContext;

class RenderEvent : public Event {
public:
  DrawingContext Context;

  RenderEvent(rndr::RenderSurface* surface);
};

} // namespace uxui
