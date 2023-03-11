
// Copyright (c) 2023 Jacob R. Green
// All Rights Reserved.

#include "muchcool/uxui/events.hpp"
#include "muchcool/uxui/uielement.hpp"

namespace muchcool::uxui {

Event::Event() : Handled(false), Time(DateTime::now()) {}

KeyEvent::KeyEvent(KeyButton key, KeyState state) : Key(key), State(state) {}

MouseEvent::MouseEvent(Point pos) : Position(pos) {}

Point MouseEvent::GetPosition(const UIElement* relativeTo) {
  return Position - relativeTo->final_rect().Offset;
}

MouseButtonEvent::MouseButtonEvent(Point pos, MouseButton button,
                                   MouseButtonState state)
    : MouseEvent(pos), Button(button), State(state) {}

FocusEvent::FocusEvent(bool focused) : Focused(focused) {}

RenderEvent::RenderEvent(Shared<rndr::RenderSurface> surface)
    : Context(std::move(surface)) {}

}  // namespace muchcool::uxui