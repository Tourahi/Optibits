#include "../common/config.h"
#include "../libs/utest.h"

int main(int argc, char **argv)
{
#ifdef OPTI_ENABLE_UTEST
  return utest_main(argc, argv);
#else
  return 1;
#endif
}

#ifdef OPTI_ENABLE_UTEST
  UTEST_STATE();
#endif
