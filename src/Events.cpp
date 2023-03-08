
// Copyright (c) 2022-2023 Jacob R. Green
// All Rights Reserved.

#include "muchcool/uxui/Events.hpp"
#include "muchcool/uxui/UIElement.hpp"

namespace uxui {

Event::Event() : Handled(false), Time(DateTime::Now()) {}

KeyEvent::KeyEvent(KeyButton key, KeyState state) : Key(key), State(state) {}

MouseEvent::MouseEvent(Point pos) : Position(pos) {}

Point MouseEvent::GetPosition(const UiElement *relativeTo) {
  return Position - relativeTo->GetFinalRect().Offset;
}

MouseButtonEvent::MouseButtonEvent(Point pos, MouseButton button,
                                   MouseButtonState state)
    : MouseEvent(pos), Button(button), State(state) {}

FocusEvent::FocusEvent(bool focused) : Focused(focused) {}

RenderEvent::RenderEvent(rndr::RenderSurface *surface) : Context(surface) {}

} // namespace uxui