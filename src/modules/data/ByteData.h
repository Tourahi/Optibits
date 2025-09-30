
#pragma once

#include "common/Data.h"

#include <stddef.h>

namespace opti {
  namespace data {


    class ByteData : public opti::Data {
    public:
      static opti::Type type;

      ByteData(size_t size, bool clear = true);
      ByteData(const void *d, size_t size);
      ByteData(void *d, size_t size, bool own);
      ByteData(const ByteData &d);
      virtual ~ByteData();

      ByteData *clone() const override;
      void *getData() const override;
      size_t getSize() const override;

    private:

      void create();

      char *data;
      size_t size;

    };

  }
}



