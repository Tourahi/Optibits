
#ifndef OPTI_STRING_MAP_H
#define OPTI_STRING_MAP_H

#include <string>
#include <vector>

// As StringMap instantiates std::vector<std::string> for instances that use
// getNames(), we end up with multiple copies in the object files. This
// declaration means we only emit it once (in StringMap.cpp).
extern template class std::vector<std::string>;


namespace opti
{

  template<typename T, unsigned int SIZE>
  class StringMap
  {
    private:

      struct Record
      {
        const char *key;
        T value;
        bool set;
        Record() : set(false) {}
      };

      static const unsigned int MAX = SIZE * 2;

      Record records[MAX];
      const char *reverse[SIZE];


    public:
      struct Entry
      {
        const char *key;
        T value;
      };

      StringMap(const Entry *entries, unsigned int num)
      {
        for (unsigned int i = 0; i < SIZE; ++i)
          reverse[i] = nullptr;

        unsigned int n = num / sizeof(Entry);

        for (unsigned int i = 0; i < n; ++i) {
          add(entries[i].key, entries[i].value);
        }
      }

      unsigned int hashDjb2(const char *key)
      {
        unsigned int hash = 5381; // The gods said it should be 5381. Amen.
        int c;

        while ((c = *key++))
          hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash;
      }

      bool add(const char *key, T value)
      {
        unsigned int str_hash = hashDjb2(key);
        bool inserted = false;

        for (unsigned int i = 0; i < MAX; ++i)
        {
          // ensures that the index is within the bounds of records.
          unsigned int str_i = (str_hash + i) % MAX;

          if (!records[str_i].set)
          {
            inserted = true;
            // Maybe we can add the possibility to "soft" set.
            records[str_i].set = true;
            records[str_i].key = key;
            records[str_i].value = value;
            break;
          }
        }

        unsigned int index = (unsigned int) value;

        if (index >= SIZE)
        {
          printf("Constant %s out of bounds with %u!\n", key, index);
          return false;
        }

        reverse[index] = key;

        return inserted;
      }

      bool streq(const char *a, const char *b)
      {
        while(*a != 0 && *b != 0)
        {
          if (*a != *b)
            return false;

          ++a;
          ++b;
        }

        return (*a == 0 && *b == 0);
      }

      bool find(const char *key, T &t)
      {
        unsigned int str_hash = hashDjb2(key);

        for (unsigned int i = 0; i < MAX; ++i)
        {
          unsigned int str_i = (str_hash + i) % MAX;

          if (!records[str_i].set) // linear probing MAGIC
            return false;

          if (streq(records[str_i].key, key))
          {
            t = records[str_i].value;
            return true;
          }
        }

        return false;
      }

      bool find(T key, const char *&str)
      {
        unsigned int index = (unsigned int) key;

        if (index >= SIZE)
          return false;

        if (reverse[index] != nullptr)
        {
          str = reverse[index];
          return true;
        }

        return false;
      }
  };

#define STRINGMAP_DECLARE(type) \
bool getConstant(const char *in, type &out); \
bool getConstant(type in, const char *&out); \
std::vector<std::string> getConstants(type); \

#define STRINGMAP_BEGIN(type, count, name) \
static StringMap<type, count>::Entry name##Entries[] =

#define STRINGMAP_END(type, count, name) \
; \
static StringMap<type, count> name##s(name##Entries, sizeof(name##Entries)); \
bool getConstant(const char *in, type &out) { return name##s.find(in, out); } \
bool getConstant(type in, const char *&out) { return name##s.find(in, out); } \
std::vector<std::string> getConstants(type) { return name##s.getNames(); }

#define STRINGMAP_CLASS_DECLARE(type) \
static bool getConstant(const char *in, type &out); \
static bool getConstant(type in, const char *&out); \
static std::vector<std::string> getConstants(type); \

#define STRINGMAP_CLASS_BEGIN(classname, type, count, name) \
static StringMap<type, count>::Entry name##Entries[] =

#define STRINGMAP_CLASS_END(classname, type, count, name) \
; \
static StringMap<type, count> name##s(name##Entries, sizeof(name##Entries)); \
bool classname::getConstant(const char *in, type &out) { return name##s.find(in, out); } \
bool classname::getConstant(type in, const char *&out) { return name##s.find(in, out); } \
std::vector<std::string> classname::getConstants(type) { return name##s.getNames(); }

}

#endif
