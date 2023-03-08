
// Copyright (c) 2022. Jacob R. Green
// All Rights Reserved.

#pragma once

#include "Visual.hpp"

#define SIZE_UNSPECIFIED                                                       \
  uxui::Size { -1, -1 }
#define SIZE_FILL                                                              \
  uxui::Size { -2, -2 }

namespace uxui {

constexpr Point find_center(const Rect& rect) {
  return {rect.Offset.x + (rect.Size.x / 2), rect.Offset.y + (rect.Size.y / 2)};
}

constexpr Rect center(const Rect& root, const Rect& child) {
  const auto root_center = find_center(root);
  const auto child_center = find_center(child);
  const auto offset = root_center - child_center;
  return {child.Offset + offset, child.Size};
}

class _ParentInfo {
public:
  virtual ~_ParentInfo() = default;

private:
  virtual void _() {}
};

/**
 * UIElement
 */
class UiElement : public virtual Object {

#pragma region Ctors / Dtors

protected:
  UiElement();
  ~UiElement() override = default;

#pragma endregion

#pragma region Fields

private:
  UiElement* _parent = nullptr;
  _ParentInfo* _parentData = nullptr;

  Size _minSize = SIZE_UNSPECIFIED;
  Size _maxSize = SIZE_UNSPECIFIED;
  Size _preferSize = SIZE_UNSPECIFIED;

  Size _desiredSize = {};
  Rect _finalRect = {};

  Visibility _visibility;

#pragma endregion

#pragma region Getters / Setters

public:
  Visibility GetVisibility() const;
  void SetVisibility(Visibility visibility);

  bool IsVisible() const;
  bool IsKeyboardFocused() const;

  bool HitTest(const Point& point) const;

  auto& GetMinSize() const { return _minSize; }
  auto& GetMaxSize() const { return _maxSize; }
  auto& GetSize() const { return _preferSize; }

  void SetSize(const Size& size) { _preferSize = size; }

  auto& GetDesiredSize() const { return _desiredSize; }
  auto& GetFinalRect() const { return _finalRect; }

  bool _IsSizeSet() const {
    return _preferSize != SIZE_UNSPECIFIED && _preferSize != SIZE_FILL;
  }

  void _SetParent(UiElement* parent) { _parent = parent; }
  auto& _GetParent() const { return _parent; }
  auto _HasParent() const { return _GetParent() != nullptr; }

  void _SetParentData(_ParentInfo* data) { _parentData = data; }
  auto& _GetParentData() const { return _parentData; }

protected:
  virtual ArrayProxy<Pointer<UiElement>> GetChildren();

#pragma endregion

#pragma region Layouting

public:
  Size Measure(const Size& availableSize);
  Rect Arrange(const Rect& finalRect);

  virtual Size CalculateSize(const Size& availableSize,
                             const Size& requiredSize = {});

protected:
  virtual Size OnMeasure(const Size& availableSize);
  virtual Rect OnArrange(const Rect& finalRect);

#pragma endregion

#pragma region Eventing

protected:
  // Key Events

  virtual void OnPreviewKeyEvent(KeyEvent& e);
  virtual void OnPreviewKeyPress(KeyEvent& e);
  virtual void OnPreviewKeyRelease(KeyEvent& e);

  virtual void OnKeyEvent(KeyEvent& e);
  virtual void OnKeyPress(KeyEvent& e);
  virtual void OnKeyRelease(KeyEvent& e);

  // Mouse Button Events

  virtual void OnPreviewMouseButton(MouseButtonEvent& e);
  virtual void OnPreviewMousePress(MouseButtonEvent& e);
  virtual void OnPreviewMouseRelease(MouseButtonEvent& e);

  virtual void OnMouseButton(MouseButtonEvent& e);
  virtual void OnMousePress(MouseButtonEvent& e);
  virtual void OnMouseRelease(MouseButtonEvent& e);

  // Mouse Move Events

  virtual void OnPreviewMouseMove(MouseEvent& e);
  virtual void OnMouseMove(MouseEvent& e);

  virtual void OnPreviewMouseEnter(MouseEnterEvent& e);
  virtual void OnPreviewMouseLeave(MouseEnterEvent& e);

  virtual void OnMouseEnter(MouseEnterEvent& e);
  virtual void OnMouseLeave(MouseEnterEvent& e);

  // Focus Events

  virtual void OnFocus(FocusEvent& e);
  virtual void OnFocusLost(FocusEvent& e);

  // Rendering

  virtual void OnRender(RenderEvent& e);

  UXUI_INTERNAL

  void DispatchKeyEvent(KeyEvent& e);
  void DispatchMouseMoveEvent(MouseEvent& e);
  void DispatchMouseButtonEvent(MouseButtonEvent& e);
  void DispatchRenderEvent(RenderEvent& e);

#pragma endregion
};

} // namespace uxui