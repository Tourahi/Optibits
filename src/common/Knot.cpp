
// OPTI
#include "Knot.h"

namespace opti
{

  opti::Type Knot::type("Knot", nullptr);


  Knot::Knot()
    : count(1)
  {}

  Knot::Knot(const Knot &)
    : count(1)
  {}

  Knot::~Knot()
  {}

  int Knot::getReferenceCount() const
  {
    return count;
  }

  void Knot::tie()
  {
    count.fetch_add(1, std::memory_order_relaxed);
  }

  void Knot::release()
  {
    if (count.fetch_sub(1, std::memory_order_release) == 1)
    {
      std::atomic_thread_fence(std::memory_order_acquire);
      delete this;
    }
  }
}
