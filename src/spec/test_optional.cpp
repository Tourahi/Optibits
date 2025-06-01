#include "../libs/utest.h"
#include "../common/Optional.h"


UTEST(Optional, DefaultConstructor) {
  opti::OptionalInt optInt;
  ASSERT_FALSE(optInt.hasValue);
  ASSERT_EQ(optInt.get(0), 0);
}

UTEST(Optional, ParameterizedConstructor) {
  opti::OptionalInt optInt(20);
  ASSERT_TRUE(optInt.hasValue);
  ASSERT_EQ(optInt.get(0), 20);
}

UTEST(Optional, SetValue) {
  opti::Optional<int> opt;
  opt.set(1);
  ASSERT_TRUE(opt.hasValue);
  ASSERT_EQ(opt.get(2), 1);
}

UTEST(Optional, GetValue) {
  opti::Optional<int> opt(233);
  ASSERT_TRUE(opt.hasValue);
  ASSERT_EQ(opt.get(2), 233);
}

UTEST(Optional, Clear) {
  opti::Optional<int> opt;
  opt.set(1);
  opt.clear();
  ASSERT_FALSE(opt.hasValue);
  ASSERT_EQ(opt.get(2), 2);
}
