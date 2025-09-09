
// STL
#include <unordered_map>

#include "types.h"

#define TYPES_ID_UNINITIALIZED 0

namespace opti
{

  static std::unordered_map<std::string, Type*> types;

  Type::Type(const char *name, Type *parent)
  : name(name),
    parent(parent),
    id(TYPES_ID_UNINITIALIZED),
    initialized(false)
  {}

  void Type::init()
  {
    static uint32 nextId = 1;

    if (initialized) // TODO: ADD WARN
      return;

    types[name] = this;
    id = nextId++;
    bits[id] = true;
    initialized = true;

    if (!parent)
      return;
    if (!parent->initialized)
      parent->init();

    // bits inheritance
    bits |= parent->bits;
  }

  uint32 Type::getId()
  {
    if (!initialized)
      init();
    return id;
  }

  const char *Type::getName() const
  {
    return name;
  }

  Type *Type::byName(const char *name)
  {
    auto pos = types.find(name);
    if (pos == types.end())
      return nullptr;
    return pos->second;
  }

}
