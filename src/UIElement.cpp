

// Copyright (c) 2022-2023 Jacob R. Green
// All Rights Reserved.

#include "muchcool/uxui/UIElement.hpp"

namespace uxui {

bool Intersects(const Rect &rect, const Point &point) {
  return (rect.Offset.x <= point.x) &&
         (point.x <= (rect.Offset.x + rect.Size.x)) &&
         (rect.Offset.y <= point.y) &&
         (point.y <= (rect.Offset.y + rect.Size.y));
}

/*
 * UIElement
 */

UiElement::UiElement() : _visibility(Visibility::Visible) {}

Visibility UiElement::GetVisibility() const { return _visibility; }

void UiElement::SetVisibility(Visibility visibility) {
  _visibility = visibility;
}

bool UiElement::IsVisible() const { return _visibility == Visibility::Visible; }

// TODO : Implement IsKeyboardFocused for UIElement
bool UiElement::IsKeyboardFocused() const { return true; }

bool UiElement::HitTest(const Point &point) const {
  return Intersects(_finalRect, point);
}

ArrayProxy<Pointer<UiElement>> UiElement::GetChildren() { return {}; }

/*
 * UIElement Events
 */

void UiElement::DispatchKeyEvent(KeyEvent &e) {
  OnPreviewKeyEvent(e);
  if (e.Handled)
    return;

  for (const auto children = GetChildren(); auto &child : children) {
    if (child->IsKeyboardFocused()) {
      child->DispatchKeyEvent(e);
      if (e.Handled)
        return;
    }
  }

  OnKeyEvent(e);
}

void UiElement::DispatchMouseButtonEvent(MouseButtonEvent &e) {
  OnPreviewMouseButton(e);
  if (e.Handled)
    return;

  for (const auto children = GetChildren(); auto &child : children) {
    if (child->HitTest(e.Position)) {
      child->DispatchMouseButtonEvent(e);
      if (e.Handled)
        return;
    }
  }

  OnMouseButton(e);
}

void UiElement::DispatchMouseMoveEvent(MouseEvent &e) {
  OnPreviewMouseMove(e);
  if (e.Handled)
    return;

  for (const auto children = GetChildren(); auto &child : children) {
    if (child->HitTest(e.Position)) {
      child->DispatchMouseMoveEvent(e);
      if (e.Handled)
        return;
    }
  }

  OnMouseMove(e);
}

void UiElement::DispatchRenderEvent(RenderEvent &e) {
  OnRender(e);
  if (e.Handled)
    return;

  for (const auto children = GetChildren(); auto &child : children) {
    if (child->IsVisible()) {
      child->DispatchRenderEvent(e);
      if (e.Handled)
        return;
    }
  }
}

void UiElement::OnPreviewKeyEvent(KeyEvent &e) {
  switch (e.State) {
  case KeyState::Released:
    OnPreviewKeyRelease(e);
    break;
  case KeyState::Pressed:
  case KeyState::Repeat:
    OnPreviewKeyPress(e);
    break;
  default:
    return;
  }
}

void UiElement::OnPreviewKeyPress(KeyEvent &e) {}
void UiElement::OnPreviewKeyRelease(KeyEvent &e) {}

void UiElement::OnKeyEvent(KeyEvent &e) {
  switch (e.State) {
  case KeyState::Released:
    OnKeyRelease(e);
    break;
  case KeyState::Pressed:
  case KeyState::Repeat:
    OnKeyPress(e);
    break;
  default:
    return;
  }
}

void UiElement::OnKeyPress(KeyEvent &e) {}
void UiElement::OnKeyRelease(KeyEvent &e) {}

void UiElement::OnPreviewMouseButton(MouseButtonEvent &e) {
  switch (e.State) {
  case MouseButtonState::Released:
    OnPreviewMouseRelease(e);
    break;
  case MouseButtonState::Pressed:
    OnPreviewMousePress(e);
    break;
  default:
    return;
  }
}

void UiElement::OnPreviewMousePress(MouseButtonEvent &e) {}
void UiElement::OnPreviewMouseRelease(MouseButtonEvent &e) {}

void UiElement::OnMouseButton(MouseButtonEvent &e) {
  switch (e.State) {
  case MouseButtonState::Released:
    OnMousePress(e);
    break;
  case MouseButtonState::Pressed:
    OnMouseRelease(e);
    break;
  default:
    return;
  }
}

void UiElement::OnMousePress(MouseButtonEvent &e) {}
void UiElement::OnMouseRelease(MouseButtonEvent &e) {}

void UiElement::OnPreviewMouseMove(MouseEvent &e) {}
void UiElement::OnMouseMove(MouseEvent &e) {}

void UiElement::OnPreviewMouseEnter(MouseEnterEvent &e) {}
void UiElement::OnPreviewMouseLeave(MouseEnterEvent &e) {}

void UiElement::OnMouseEnter(MouseEnterEvent &e) {}
void UiElement::OnMouseLeave(MouseEnterEvent &e) {}

void UiElement::OnFocus(FocusEvent &e) {}
void UiElement::OnFocusLost(FocusEvent &e) {}

void UiElement::OnRender(RenderEvent &e) {}

/*
 * UIElement Layout
 */

Size UiElement::Measure(const Size &availableSize) {
  return _desiredSize = OnMeasure(availableSize);
}

Rect UiElement::Arrange(const Rect &finalRect) {
  return _finalRect = OnArrange(finalRect);
}

Size UiElement::OnMeasure(const Size &availableSize) {
  return CalculateSize(availableSize, {});
}

Rect UiElement::OnArrange(const Rect &finalRect) { return finalRect; }

Size UiElement::CalculateSize(const Size &availableSize,
                              const Size &requiredSize) {
  Size minSize = _minSize;
  Size maxSize = _maxSize;
  Size preferredSize = _preferSize;

  if (minSize == SIZE_UNSPECIFIED)
    minSize = {0, 0};
  if (maxSize == SIZE_UNSPECIFIED)
    maxSize = {FLT_MAX, FLT_MAX};

  if (preferredSize == SIZE_UNSPECIFIED)
    preferredSize = requiredSize;
  else if (preferredSize == SIZE_FILL)
    preferredSize = availableSize;

  preferredSize = glm::clamp(preferredSize, minSize, maxSize);
  preferredSize = glm::clamp(preferredSize, minSize, availableSize);

  return {glm::max(preferredSize.x, requiredSize.x),
          glm::max(preferredSize.y, requiredSize.y)};
}

} // namespace uxui