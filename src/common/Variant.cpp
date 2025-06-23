
#include <memory>

#include "Variant.h"
#include "common/StringMap.h"

namespace opti
{
  Variant::Variant(Type vtype)
    : type(vtype)
  {}

  Variant::Variant()
    : type(NIL)
  {}

  Variant::Variant(bool boolean)
    : type(BOOLEAN)
  {
    data.boolean = boolean;
  }

  Variant::Variant(double number)
    : type(NUMBER)
  {
    data.number = number;
  }

  Variant::Variant(const char *str, size_t len)
  {
    if (len <= MAX_SMALL_STRING_LENGTH)
    {
      type = SMALLSTRING;
      memcpy(data.smallstring.str, str, len);
      data.smallstring.len = (uint8) len;
    }
    else
    {
      type = STRING;
      data.string = new SharedString(str, len);
    }
  }

  Variant::Variant(const std::string &str)
    : Variant(str.c_str(), str.length())
  {
  }

  Variant::Variant(void *lightuserdata)
    : type(LUSERDATA)
  {
    data.userdata = lightuserdata;
  }

  Variant::Variant(opti::Type *optitype, opti::Knot *knot)
    : type(OPTIKNOT)
  {
    data.knotproxy.type = optitype;
    data.knotproxy.knot = knot;

    if (data.knotproxy.knot != nullptr)
      data.knotproxy.knot->tie();
  }

  Variant::Variant(SharedTable *table)
    : type(TABLE)
  {
    data.table = table;
  }

  Variant::Variant(const Variant &v)
  : type(v.type)
  , data(v.data)
  {
    if (type == STRING)
      data.string->tie();
    else if (type == OPTIKNOT && data.knotproxy.knot != nullptr)
      data.knotproxy.knot->tie();
    else if (type == TABLE)
      data.table->tie();
  }

  Variant::Variant(Variant &&v)
    : type(std::move(v.type))
    , data(std::move(v.data))
  {
    v.type = NIL;
  }

  Variant::~Variant()
  {
    if (type == STRING)
      data.string->release();
    else if (type == OPTIKNOT && data.knotproxy.knot != nullptr)
      data.knotproxy.knot->release();
    else if (type == TABLE)
      data.table->release();
  }

  Variant &Variant::operator = (const Variant &v)
  {
    if (v.type == STRING)
      v.data.string->tie();
    else if (v.type == OPTIKNOT && v.data.knotproxy.knot != nullptr)
      v.data.knotproxy.knot->tie();
    else if (v.type == TABLE)
      v.data.table->tie();

    if (type == STRING)
      data.string->release();
    else if (type == OPTIKNOT && data.knotproxy.knot != nullptr)
      data.knotproxy.knot->release();
    else if (type == TABLE)
      data.table->release();

    type = v.type;
    data = v.data;

    return *this;
  }
}
