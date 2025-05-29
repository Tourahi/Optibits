
#ifndef OPTI_TYPES_H
#define OPTI_TYPES_H

#include "int.h"

// STD
#include <bitset>

namespace opti
{

  class Type
  {

    public:
      static const uint32 MAX_TYPES = 128;

      Type(const char *name, Type *parent);
      Type(const Type&) = delete;

      static Type *byName(const char *name);

      void init();
      uint32 getId();
      const char *getName() const;

      bool isa(const uint32 &other)
      {
        if (!initialized)
          init();
        return bits[other];
      }

      bool isa(const Type &other)
      {
        if (!initialized)
          init();
        return bits[other.id];
      }

    private:
      const char * const name;
      Type * const parent;
      uint32 id;
      bool initialized;
      std::bitset<MAX_TYPES> bits;

  };

}

#endif // OPTI_TYPES_H
