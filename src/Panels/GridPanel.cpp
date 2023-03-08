
// Copyright (c) 2022-2023 Jacob R. Green
// All Rights Reserved.

#include "muchcool/uxui/Panels/GridPanel.hpp"

namespace uxui {

#pragma region GridInfo

struct GridInfo final : _ParentInfo {
  uint32 col, row, col_span, row_span;
  HorizontalAlignment h_align = HorizontalAlignment::Center;
  VerticalAlignment v_align = VerticalAlignment::Center;

  GridInfo() = delete;
  GridInfo(GridInfo &&) = delete;
  GridInfo(const GridInfo &) = delete;

  GridInfo(const uint32 col, const uint32 row, const uint32 col_span,
           const uint32 row_span, const HorizontalAlignment h_align,
           const VerticalAlignment v_align)
      : col(col), row(row), col_span(col_span), row_span(row_span),
        h_align(h_align), v_align(v_align) {}

  static GridInfo &Get(const UiElement *element);
};

GridInfo &GridInfo::Get(const UiElement *const element) {
  return *As<GridInfo>(element->_GetParentData());
}

#pragma endregion

#pragma region Helpers

std::tuple<float, float>
_get_weight_absolute_allocation(const std::vector<GridSize> &grid_sizes) {
  float weight = 0;
  float absolute = 0;

  for (const auto &size : grid_sizes) {
    switch (size.Mode) {
    case GridMode::Relative: {
      weight += size.Value;
      break;
    }
    case GridMode::Absolute: {
      absolute += size.Value;
      break;
    }
    default: {
      throw std::exception("Unknown grid mode.");
    }
    }
  }

  return {weight, absolute};
}

float _gridsize_to_float(const GridSize &grid_size, const float weight_size) {
  switch (grid_size.Mode) {
  case GridMode::Relative: {
    return grid_size.Value * weight_size;
  }
  case GridMode::Absolute: {
    return grid_size.Value;
  }
  default: {
    throw std::exception("Unknown grid mode.");
  }
  }
}

std::vector<float> _calculate_sizes(const float size_to_fill,
                                    const std::vector<GridSize> &grid_sizes) {
  std::vector<float> calculated_sizes(grid_sizes.size());

  const auto [total_weight, absolute] =
      _get_weight_absolute_allocation(grid_sizes);

  const auto weighted_size = size_to_fill - absolute;
  const auto size_per_weight = weighted_size / total_weight;

  for (auto i = 0ull; i < grid_sizes.size(); ++i) {
    calculated_sizes[i] = _gridsize_to_float(grid_sizes[i], size_per_weight);
  }

  return calculated_sizes;
}

float _calculate_cell_size_dimension(const uint32 start, const uint32 span,
                                     const std::vector<float> &sizes) {
  float size = 0.0f;
  for (auto i = 0ull; i < span; ++i) {
    size += sizes[start + i];
  }
  return size;
}

Size _calculate_cell_size(const uint32 col, const uint32 row,
                          const uint32 col_span, const uint32 row_span,
                          const std::vector<float> &col_sizes,
                          const std::vector<float> &row_sizes) {
  return {_calculate_cell_size_dimension(col, col_span, col_sizes),
          _calculate_cell_size_dimension(row, row_span, row_sizes)};
}

Size _calculate_cell_size(const GridInfo &grid_info,
                          const std::vector<float> &col_sizes,
                          const std::vector<float> &row_sizes) {
  return _calculate_cell_size(grid_info.col, grid_info.row, grid_info.col_span,
                              grid_info.row_span, col_sizes, row_sizes);
}

float _calculate_cell_offset_dimension(const uint32 index,
                                       const std::vector<float> &sizes) {
  float offset = 0.0f;
  for (auto i = 0u; i < index; ++i) {
    offset += sizes[i];
  }
  return offset;
}

Size _calculate_cell_offset(const uint32 column, const uint32 row,
                            const std::vector<float> &column_sizes,
                            const std::vector<float> &row_sizes) {

  return {_calculate_cell_offset_dimension(column, column_sizes),
          _calculate_cell_offset_dimension(row, row_sizes)};
}

Size _calculate_cell_offset(const GridInfo &grid_info,
                            const std::vector<float> &column_sizes,
                            const std::vector<float> &row_sizes) {

  return _calculate_cell_offset(grid_info.col, grid_info.row, column_sizes,
                                row_sizes);
}

#pragma endregion

GridPanel::GridPanel(const uint32 cols, const uint32 rows)
    : _cols(cols), _rows(rows), _col_sizes(cols), _row_sizes(rows) {
  for (auto i = 0; i < _cols; ++i) {
    _col_sizes[i] = GridSize{GridMode::Relative, 1.0f};
  }

  for (auto i = 0; i < _rows; ++i) {
    _row_sizes[i] = GridSize{GridMode::Relative, 1.0f};
  }
}

ArrayProxy<Pointer<UiElement>> GridPanel::GetChildren() { return _children; }

void GridPanel::AddChild(UiElement *const element, const uint32 column,
                         const uint32 row, const uint32 column_span,
                         const uint32 row_span,
                         const HorizontalAlignment horizontal_alignment,
                         const VerticalAlignment vertical_alignment) {
  if (element->_HasParent())
    throw std::invalid_argument("Provided element already has a parent.");

  if (column + column_span > _cols)
    throw std::invalid_argument("Provided column + column span is greater than "
                                "total number of columns.");

  if (row + row_span > _rows)
    throw std::invalid_argument("Provided row + row span is greater than "
                                "total number of rows.");

  element->_SetParent(this);
  element->_SetParentData(new GridInfo(column, row, column_span, row_span,
                                       horizontal_alignment,
                                       vertical_alignment));
  _children.emplace_back(element);
}

void GridPanel::RemoveChild(UiElement *const element) {
  const auto it = std::find(_children.begin(), _children.end(), element);
  if (it == _children.end()) {
    throw std::invalid_argument("GridPanel doesn't contain provided element.");
  }
  _children.erase(it);
  delete element->_GetParentData();
  element->_SetParent(null);
  element->_SetParentData(null);
}

#pragma region Layout Measuring

Size GridPanel::OnMeasure(const Size &available_size) {
  const auto calculated_size = CalculateSize(available_size, available_size);

  _calculated_col_sizes = _calculate_sizes(calculated_size.x, _col_sizes);
  _calculated_row_sizes = _calculate_sizes(calculated_size.y, _row_sizes);

  for (auto &child : _children) {
    const auto &grid_info = GridInfo::Get(child);

    const auto cell_size = _calculate_cell_size(
        grid_info, _calculated_col_sizes, _calculated_row_sizes);

    child->Measure(cell_size);
  }

  return calculated_size;
}

Rect GridPanel::OnArrange(const Rect &final_rect) {
  for (auto &child : _children) {
    const auto &grid_info = GridInfo::Get(child);
    const auto p = _calculate_cell_offset(grid_info, _calculated_col_sizes,
                                          _calculated_row_sizes);

    const auto s = _calculate_cell_size(grid_info, _calculated_col_sizes,
                                        _calculated_row_sizes);

    child->Arrange({final_rect.Offset + p, s});
  }

  return Panel::OnArrange(final_rect);
}

#pragma endregion

GridPanel *GridPanel::Get(const UiElement *element) {
  const auto panel = dynamic_cast<GridPanel *>(element->_GetParent());
  return panel ? panel
               : throw std::exception(
                     "The parent of the given UiElement is not a GridPanel.");
}

#pragma region Static Position Movement

void GridPanel::SetPos(const UiElement *element, const uint32 column,
                       const uint32 row, const uint32 column_span,
                       const uint32 row_span) {

  const auto panel = GridPanel::Get(element);
  auto &info = GridInfo::Get(element);
  info.col = column;
  info.row = row;
  info.col_span = column_span;
  info.row_span = row_span;
}

void GridPanel::SetAlignment(const UiElement *element,
                             const HorizontalAlignment horizontal_align) {
  auto &info = GridInfo::Get(element);
  info.h_align = horizontal_align;
}

void GridPanel::SetAlignment(const UiElement *element,
                             const VerticalAlignment vertical_align) {
  auto &info = GridInfo::Get(element);
  info.v_align = vertical_align;
}

#pragma endregion

} // namespace uxui