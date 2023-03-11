
// Copyright (c) 2023 Jacob R. Green
// All Rights Reserved.

#pragma once

#include "events.hpp"

namespace muchcool::uxui {

class Visual : public virtual Object {
  using Collection = std::vector<Shared<Visual>>;

  Collection _children;

 protected:
  Visual() = default;
  Visual(Visual&&) = delete;
  Visual(const Visual&) = delete;

  void AddChild(Shared<Visual> visual);
  bool RemoveChild(Shared<Visual> visual);
  uword ChildCount() const { return _children.size(); }

  virtual void OnRender(DrawingContext& context);
};

}  // namespace muchcool::uxui
