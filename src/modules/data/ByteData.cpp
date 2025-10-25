
#include "ByteData.h"
#include "common/Exception.h"
#include "common/int.h"

#include <string.h>

namespace opti {
  namespace data {

    opti::Type ByteData::type("ByteData", &ByteData::type);

    void ByteData::create() {
      if (size == 0)
        throw opti::Exception("Attempt to create an empty ByteData");

      try {
        data = new char[size];
      } catch (std::exception &) {
        throw opti::Exception("Out of memory.");
      }
    }


    ByteData::ByteData(size_t size, bool clear)
      : size(size)
    {
      create();
      if (clear)
        memset(data, 0, size);
    }

    ByteData::ByteData(const void *d, size_t size)
      : size(size)
    {
      create();
      if (d != nullptr)
        memcpy(data, d, size);
    }

    ByteData::ByteData(void *d, size_t size, bool own)
      : size(size)
    {
      if (own)
        data = static_cast<char *>(d);
      else {
        create();
        if (d != nullptr)
          memcpy(data, d, size);
      }
    }

    ByteData::ByteData(const ByteData &d)
     : size(size)
    {
      create();
      memcpy(data, d.data, size);
    }

    ByteData::~ByteData()
    {
      delete[] data;
    }

    ByteData *ByteData::clone() const {
      return new ByteData(*this);
    }

    void *ByteData::getData() const {
      return data;
    }

    size_t ByteData::getSize() const {
      return size;
    }
  }
}