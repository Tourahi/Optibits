
#ifndef OPTI_VARIANT_H
#define OPTI_VARIANT_H


#include "common/config.h"
#include "common/Knot.h"
#include "common/int.h"


#include <cstring>
#include <string>
#include <vector>


namespace opti
{

  class OPTI_EXPORT Variant
  {
    public:
      static const int MAX_SMALL_STRING_LENGTH = 15;

      enum Type
      {
        UNKNOWN = 0,
        BOOLEAN,
        NUMBER,
        STRING,
        SMALLSTRING,
        LUSERDATA,
        OPTIKNOT,
        NIL,
        TABLE
      };

      class SharedString : public opti::Knot
      {
        public:
          SharedString(const char *string, size_t len)
            : len(len)
          {
            str = new char[len + 1];
            str[len] = '\0';
            memcpy(str, string, len);
          }
          virtual ~SharedString() { delete[] str; }

          char *str;
          size_t len;
      };

      class SharedTable : public opti::Knot
      {
        public:
          SharedTable() {}
          virtual ~SharedTable() {}

          std::vector<std::pair<Variant, Variant>> pairs;
      };

      union Data
      {
        bool boolean;
        double number;
        SharedString *string;
        void *userdata;
        Proxy knotproxy;
        SharedTable *table;
        struct
        {
          char str[MAX_SMALL_STRING_LENGTH];
          uint8 len;
        } smallstring;
      };

      Variant();
      Variant(bool boolean);
      Variant(double number);
      Variant(const char *str, size_t len);
      Variant(const std::string &str);
      Variant(void *lightuserdata);
      Variant(opti::Type *type, opti::Knot *knot);
      Variant(SharedTable *table);
      Variant(const Variant &v);
      Variant(Variant &&v);
      ~Variant();

      Variant &operator = (const Variant &v);

      Type getType() const { return type; }
      const Data &getData() const { return data; }

      static Variant unknown() { return Variant(UNKNOWN); }

    private:
      Variant(Type vtype);

      Type type;
      Data data;

  }; // Variant

} // opti

#endif
