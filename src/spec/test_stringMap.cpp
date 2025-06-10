#include "../libs/utest.h"
#include "../common/StringMap.h"


UTEST(StringMapTests, Construction) {
  opti::StringMap<unsigned int, 5> map(nullptr, 0);
  ASSERT_TRUE(true);
}

UTEST(StringMapTests, AddAndFindStringKey) {
  opti::StringMap<unsigned int, 5> map(nullptr, 0);

  ASSERT_TRUE(map.add("key1", 1));
  ASSERT_TRUE(map.add("key2", 2));

  unsigned int value1 = 0;
  ASSERT_TRUE(map.find("key1", value1));
  ASSERT_EQ(1, value1);

  unsigned int value2 = 0;
  ASSERT_TRUE(map.find("key2", value2));
  ASSERT_EQ(2, value2);

  unsigned int value3 = 0;
  ASSERT_FALSE(map.find("nonexistent", value3));
}


UTEST(StringMapTests, AddAndFindTKey) {
  opti::StringMap<unsigned int, 6> map(nullptr, 0);

  // Add some key-value pairs (using add with string key first)
  map.add("key1", 1);
  map.add("key5", 5);

  // Find the added keys using T key
  const char* str1 = nullptr;
  ASSERT_TRUE(map.find(1, str1));
  ASSERT_TRUE(map.streq("key1", str1));

  const char* str5 = nullptr;
  ASSERT_TRUE(map.find(5, str5));
  ASSERT_TRUE(map.streq("key5", str5));

  // Try to find a non-existent key
  const char* str99 = nullptr;
  ASSERT_FALSE(map.find(99, str99));
}

UTEST(StringMapTests, HandleOutOfBoundsTKey) {
  opti::StringMap<unsigned int, 5> map(nullptr, 0);

  // Try to find an out-of-bounds key
  const char* str = nullptr;
  ASSERT_FALSE(map.find(6, str)); // Key is out of bounds (SIZE is 5)

  //Also test a negative out of bounds
  const char* str_neg = nullptr;
  ASSERT_FALSE(map.find(-1, str_neg));
}

UTEST(StringMapTests, CollisionHandling) {
  opti::StringMap<unsigned int, 5> map(nullptr, 0);

  map.add("Aa", 1);
  map.add("BB", 2);

  unsigned int value1 = 0;
  ASSERT_TRUE(map.find("Aa", value1));
  ASSERT_EQ(1, value1);

  unsigned int value2 = 0;
  ASSERT_TRUE(map.find("BB", value2));
  ASSERT_EQ(2, value2);
}

UTEST(StringMapTests, Entries) {
  opti::StringMap<unsigned int, 3>::Entry entries[] = {
    {"key1", 10}
  };

  opti::StringMap<unsigned int, 3> map(entries, 20);

  unsigned int value1 = 0;
  ASSERT_TRUE(map.find("key1", value1));
  ASSERT_EQ(10, value1);
}
