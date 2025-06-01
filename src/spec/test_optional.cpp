#include "../libs/utest.h"
#include "../common/Optional.h"

UTEST(Optional, get) {
  opti::OptionalInt optInt(1);
  ASSERT_EQ(optInt.get(300), 1);
}
