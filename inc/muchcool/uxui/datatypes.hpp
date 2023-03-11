
// Copyright (c) 2023 Jacob R. Green
// All Rights Reserved.

#pragma once

#include "common.hpp"

#include "muchcool/xgdi.hpp"

namespace muchcool::uxui {

using Point = xgdi::Point;
using Size = xgdi::Size;
using Rect = xgdi::Rect;
using Color = xgdi::Color;

struct Radial {
 public:
  using type = float;

  union {
    type n, t;
  };
  union {
    type e, r;
  };
  union {
    type s, b;
  };
  union {
    type w, l;
  };

  Radial(type val) : n(val), e(val), s(val), w(val) {}
  Radial(type vertical, type horizontal)
      : n(vertical), e(horizontal), s(vertical), w(horizontal) {}
  Radial(type n, type e, type s, type w) : n(n), e(e), s(s), w(w) {}
};

constexpr Size& operator+=(Size& size, const Radial& radial) {
  size.x += radial.l + radial.r;
  size.y += radial.t + radial.b;
  return size;
}

}  // namespace muchcool::uxui
