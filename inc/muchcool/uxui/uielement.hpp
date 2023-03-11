
// Copyright (c) 2023 Jacob R. Green
// All Rights Reserved.

#pragma once

#include "visual.hpp"

#define SIZE_UNSPECIFIED \
  uxui::Size { -1, -1 }
#define SIZE_FILL \
  uxui::Size { -2, -2 }

namespace muchcool::uxui {

constexpr Point find_center(const Rect& rect) {
  return {rect.Offset.x + (rect.Size.x / 2), rect.Offset.y + (rect.Size.y / 2)};
}

constexpr Rect center(const Rect& root, const Rect& child) {
  const auto root_center = find_center(root);
  const auto child_center = find_center(child);
  const auto offset = root_center - child_center;
  return {child.Offset + offset, child.Size};
}

class _parent_info {
 public:
  virtual ~_parent_info() = default;

 private:
  virtual void _() {}
};

/**
 * UIElement
 */
class UIElement : public virtual Object {
#pragma region Ctors / Dtors

 protected:
  UIElement();

 public:
  ~UIElement() override = default;

#pragma endregion

#pragma region Fields

 private:
  UIElement* _parent = nullptr;
  _parent_info* _parentData = nullptr;

  Size _minSize = SIZE_UNSPECIFIED;
  Size _maxSize = SIZE_UNSPECIFIED;
  Size _preferSize = SIZE_UNSPECIFIED;

  Size _desiredSize = {};
  Rect _finalRect = {};

  Visibility _visibility;

#pragma endregion

#pragma region Getters / Setters

 public:
  Visibility visibility() const;
  void set_visibility(Visibility visibility);

  bool is_visible() const;
  bool is_keyboard_focused() const;

  bool hit_test(const Point& point) const;

  auto& min_size() const { return _minSize; }
  auto& max_size() const { return _maxSize; }
  auto& size() const { return _preferSize; }

  void set_size(const Size& size) { _preferSize = size; }

  auto& desired_size() const { return _desiredSize; }
  auto& final_rect() const { return _finalRect; }

  bool _is_size_set() const {
    return _preferSize != SIZE_UNSPECIFIED && _preferSize != SIZE_FILL;
  }

  auto& _get_parent() const { return _parent; }
  void _set_parent(UIElement* parent) { _parent = parent; }
  auto _has_parent() const { return _get_parent() != nullptr; }

  auto& _get_parent_data() const { return _parentData; }
  void _set_parent_data(_parent_info* data) { _parentData = data; }

 protected:
  virtual auto children() const -> ArrayProxy<const Shared<UIElement>>;

#pragma endregion

#pragma region Layouting

 public:
  Size measure(const Size& availableSize);
  Rect arrange(const Rect& finalRect);

  virtual Size calculate_size(const Size& availableSize,
                              const Size& requiredSize = {});

 protected:
  virtual Size on_measure(const Size& availableSize);
  virtual Rect on_arrange(const Rect& finalRect);

#pragma endregion

#pragma region Eventing

 protected:
  // Key Events

  virtual void on_preview_key_event(KeyEvent& e);
  virtual void on_preview_key_press(KeyEvent& e);
  virtual void on_preview_key_release(KeyEvent& e);

  virtual void on_key_event(KeyEvent& e);
  virtual void on_key_press(KeyEvent& e);
  virtual void on_key_release(KeyEvent& e);

  // Mouse Button Events

  virtual void on_preview_mouse_button(MouseButtonEvent& e);
  virtual void on_preview_mouse_press(MouseButtonEvent& e);
  virtual void on_preview_mouse_release(MouseButtonEvent& e);

  virtual void on_mouse_button(MouseButtonEvent& e);
  virtual void on_mouse_press(MouseButtonEvent& e);
  virtual void on_mouse_release(MouseButtonEvent& e);

  // Mouse Move Events

  virtual void on_preview_mouse_move(MouseEvent& e);
  virtual void on_mouse_move(MouseEvent& e);

  virtual void on_preview_mouse_enter(MouseEnterEvent& e);
  virtual void on_preview_mouse_leave(MouseEnterEvent& e);

  virtual void on_mouse_enter(MouseEnterEvent& e);
  virtual void on_mouse_leave(MouseEnterEvent& e);

  // Focus Events

  virtual void on_focus(FocusEvent& e);
  virtual void on_focus_lost(FocusEvent& e);

  // Rendering

  virtual void on_render(RenderEvent& e);

  UXUI_INTERNAL

  void dispatch_key_event(KeyEvent& e);
  void dispatch_mouse_move_event(MouseEvent& e);
  void dispatch_mouse_button_event(MouseButtonEvent& e);
  void dispatch_render_event(RenderEvent& e);

#pragma endregion
};

}  // namespace muchcool::uxui