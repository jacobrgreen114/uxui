
#pragma once

#include "Events.hpp"

namespace uxui {

class Visual : public virtual Object {
  using Collection = std::vector<Pointer<Visual>>;

  Collection _children;

protected:
  Visual() = default;
  Visual(Visual&&) = delete;
  Visual(const Visual&) = delete;

  void AddChild(Visual* visual);
  bool RemoveChild(Visual* visual);
  inline uintn ChildCount() const { return _children.size(); }

  virtual void OnRender(DrawingContext& context);
};

} // namespace UXUI
