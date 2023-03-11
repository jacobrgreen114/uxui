

// Copyright (c) 2023 Jacob R. Green
// All Rights Reserved.

#include "muchcool/uxui/uielement.hpp"

namespace muchcool::uxui {

bool Intersects(const Rect& rect, const Point& point) {
  return (rect.Offset.x <= point.x) &&
         (point.x <= (rect.Offset.x + rect.Size.x)) &&
         (rect.Offset.y <= point.y) &&
         (point.y <= (rect.Offset.y + rect.Size.y));
}

/*
 * UIElement
 */

UIElement::UIElement() : _visibility(Visibility::Visible) {}

Visibility UIElement::visibility() const { return _visibility; }

void UIElement::set_visibility(Visibility visibility) {
  _visibility = visibility;
}

bool UIElement::is_visible() const {
  return _visibility == Visibility::Visible;
}

// TODO : Implement IsKeyboardFocused for UIElement
bool UIElement::is_keyboard_focused() const { return true; }

bool UIElement::hit_test(const Point& point) const {
  return Intersects(_finalRect, point);
}

auto UIElement::children() const -> ArrayProxy<const Shared<UIElement>> {
  return {};
}

/*
 * UIElement Events
 */

void UIElement::dispatch_key_event(KeyEvent& e) {
  on_preview_key_event(e);
  if (e.Handled) return;

  for (auto& child : children()) {
    if (child->is_keyboard_focused()) {
      child->dispatch_key_event(e);
      if (e.Handled) return;
    }
  }

  on_key_event(e);
}

void UIElement::dispatch_mouse_button_event(MouseButtonEvent& e) {
  on_preview_mouse_button(e);
  if (e.Handled) return;

  for (auto& child : children()) {
    if (child->hit_test(e.Position)) {
      child->dispatch_mouse_button_event(e);
      if (e.Handled) return;
    }
  }

  on_mouse_button(e);
}

void UIElement::dispatch_mouse_move_event(MouseEvent& e) {
  on_preview_mouse_move(e);
  if (e.Handled) return;

  for (auto& child : children()) {
    if (child->hit_test(e.Position)) {
      child->dispatch_mouse_move_event(e);
      if (e.Handled) return;
    }
  }

  on_mouse_move(e);
}

void UIElement::dispatch_render_event(RenderEvent& e) {
  on_render(e);
  if (e.Handled) return;

  for (auto& child : children()) {
    if (child->is_visible()) {
      child->dispatch_render_event(e);
      if (e.Handled) return;
    }
  }
}

void UIElement::on_preview_key_event(KeyEvent& e) {
  switch (e.State) {
    case KeyState::Released:
      on_preview_key_release(e);
      break;
    case KeyState::Pressed:
    case KeyState::Repeat:
      on_preview_key_press(e);
      break;
    default:
      return;
  }
}

void UIElement::on_preview_key_press(KeyEvent& e) {}
void UIElement::on_preview_key_release(KeyEvent& e) {}

void UIElement::on_key_event(KeyEvent& e) {
  switch (e.State) {
    case KeyState::Released:
      on_key_release(e);
      break;
    case KeyState::Pressed:
    case KeyState::Repeat:
      on_key_press(e);
      break;
    default:
      return;
  }
}

void UIElement::on_key_press(KeyEvent& e) {}
void UIElement::on_key_release(KeyEvent& e) {}

void UIElement::on_preview_mouse_button(MouseButtonEvent& e) {
  switch (e.State) {
    case MouseButtonState::Released:
      on_preview_mouse_release(e);
      break;
    case MouseButtonState::Pressed:
      on_preview_mouse_press(e);
      break;
    default:
      return;
  }
}

void UIElement::on_preview_mouse_press(MouseButtonEvent& e) {}
void UIElement::on_preview_mouse_release(MouseButtonEvent& e) {}

void UIElement::on_mouse_button(MouseButtonEvent& e) {
  switch (e.State) {
    case MouseButtonState::Released:
      on_mouse_press(e);
      break;
    case MouseButtonState::Pressed:
      on_mouse_release(e);
      break;
    default:
      return;
  }
}

void UIElement::on_mouse_press(MouseButtonEvent& e) {}
void UIElement::on_mouse_release(MouseButtonEvent& e) {}

void UIElement::on_preview_mouse_move(MouseEvent& e) {}
void UIElement::on_mouse_move(MouseEvent& e) {}

void UIElement::on_preview_mouse_enter(MouseEnterEvent& e) {}
void UIElement::on_preview_mouse_leave(MouseEnterEvent& e) {}

void UIElement::on_mouse_enter(MouseEnterEvent& e) {}
void UIElement::on_mouse_leave(MouseEnterEvent& e) {}

void UIElement::on_focus(FocusEvent& e) {}
void UIElement::on_focus_lost(FocusEvent& e) {}

void UIElement::on_render(RenderEvent& e) {}

/*
 * UIElement Layout
 */

Size UIElement::measure(const Size& availableSize) {
  return _desiredSize = on_measure(availableSize);
}

Rect UIElement::arrange(const Rect& finalRect) {
  return _finalRect = on_arrange(finalRect);
}

Size UIElement::on_measure(const Size& availableSize) {
  return calculate_size(availableSize, {});
}

Rect UIElement::on_arrange(const Rect& finalRect) { return finalRect; }

Size UIElement::calculate_size(const Size& availableSize,
                               const Size& requiredSize) {
  Size minSize = _minSize;
  Size maxSize = _maxSize;
  Size preferredSize = _preferSize;

  if (minSize == SIZE_UNSPECIFIED) minSize = {0, 0};
  if (maxSize == SIZE_UNSPECIFIED) maxSize = {FLT_MAX, FLT_MAX};

  if (preferredSize == SIZE_UNSPECIFIED)
    preferredSize = requiredSize;
  else if (preferredSize == SIZE_FILL)
    preferredSize = availableSize;

  preferredSize = glm::clamp(preferredSize, minSize, maxSize);
  preferredSize = glm::clamp(preferredSize, minSize, availableSize);

  return {glm::max(preferredSize.x, requiredSize.x),
          glm::max(preferredSize.y, requiredSize.y)};
}

}  // namespace muchcool::uxui