
// Copyright (c) 2022. Jacob R. Green
// All Rights Reserved.

#pragma once

#include "Panel.hpp"

namespace uxui {

enum class GridMode {
  Relative,
  Absolute
};

struct GridSize {
  GridMode Mode;
  float Value;
};

class GridPanel : public Panel {

  std::vector<Pointer<UiElement>> _children;

  const uint32 _cols;
  const uint32 _rows;
  std::vector<GridSize> _col_sizes;
  std::vector<GridSize> _row_sizes;

  std::vector<float> _calculated_col_sizes;
  std::vector<float> _calculated_row_sizes;

public:
  GridPanel(uint32 cols, uint32 rows);

  uint32 ColumnCount() const { return _cols; }
  uint32 RowCount() const { return _rows; }

  void SetRowSize(uint32 row, const GridSize& size) { _row_sizes[row] = size; }
  void SetColSize(uint32 col, const GridSize& size) { _col_sizes[col] = size; }

  void
  AddChild(UiElement* element, uint32 column = 0, uint32 row = 0,
           uint32 column_span = 1, uint32 row_span = 1,
           HorizontalAlignment horizontal_alignment = HorizontalAlignment::Left,
           VerticalAlignment vertical_alignment = VerticalAlignment::Top);

  void RemoveChild(UiElement* element);

protected:
  ArrayProxy<Pointer<UiElement>> GetChildren() override;

  Size OnMeasure(const Size& available_size) override;
  Rect OnArrange(const Rect& final_rect) override;

private:
  static GridPanel* Get(const UiElement* element);

public:
  static void SetPos(const UiElement* element, uint32 column, uint32 row,
                     uint32 column_span = 1, uint32 row_span = 1);

  static void SetAlignment(const UiElement* element,
                           HorizontalAlignment horizontal_align);
  static void SetAlignment(const UiElement* element,
                           VerticalAlignment vertical_align);
};

} // namespace uxui
