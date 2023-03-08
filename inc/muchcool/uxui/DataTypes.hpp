
// Copyright (c) 2022-2023 Jacob R. Green
// All Rights Reserved.

#pragma once

#include "Platform.hpp"

#include "muchcool/xgdi.hpp"

namespace uxui {

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

  inline Radial(type val) : n(val), e(val), s(val), w(val) {}
  inline Radial(type vertical, type horizontal)
      : n(vertical), e(horizontal), s(vertical), w(horizontal) {}
  inline Radial(type n, type e, type s, type w) : n(n), e(e), s(s), w(w) {}
};

inline Size &operator+=(Size &size, const Radial &radial) {
  size.x += radial.l + radial.r;
  size.y += radial.t + radial.b;
  return size;
}

} // namespace uxui
