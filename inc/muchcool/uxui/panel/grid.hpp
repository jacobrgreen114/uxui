
// Copyright (c) 2023 Jacob R. Green
// All Rights Reserved.

#pragma once

#include "panel.hpp"

namespace muchcool::uxui {

enum class GridMode { Relative, Absolute };

struct GridSize {
  GridMode Mode;
  float Value;
};

class GridPanel : public Panel {
  std::vector<Shared<UIElement>> _children;

  const uint32 _cols;
  const uint32 _rows;
  std::vector<GridSize> _col_sizes;
  std::vector<GridSize> _row_sizes;

  std::vector<float> _calculated_col_sizes;
  std::vector<float> _calculated_row_sizes;

 public:
  GridPanel(uint32 cols, uint32 rows);

  uint32 columns() const { return _cols; }
  uint32 rows() const { return _rows; }

  void set_row_size(uint32 row, const GridSize& size) {
    _row_sizes[row] = size;
  }
  void set_col_size(uint32 col, const GridSize& size) {
    _col_sizes[col] = size;
  }

  void add_child(
      UIElement* element, uint32 column = 0, uint32 row = 0,
      uint32 column_span = 1, uint32 row_span = 1,
      HorizontalAlignment horizontal_alignment = HorizontalAlignment::Left,
      VerticalAlignment vertical_alignment = VerticalAlignment::Top);

  void remove_child(UIElement* element);

 protected:
  auto children() const -> ArrayProxy<const Shared<UIElement>> override;

  Size on_measure(const Size& available_size) override;
  Rect on_arrange(const Rect& final_rect) override;

 private:
  static GridPanel* Get(const UIElement* element);

 public:
  static void set_pos(const UIElement* element, uint32 column, uint32 row,
                      uint32 column_span = 1, uint32 row_span = 1);

  static void set_alignment(const UIElement* element,
                            HorizontalAlignment horizontal_align);

  static void set_alignment(const UIElement* element,
                            VerticalAlignment vertical_align);
};

}  // namespace muchcool::uxui
