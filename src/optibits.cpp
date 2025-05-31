#include <iostream>
#include <string>


int main(int argc, char **argv)
{
#ifdef OPTI_ENABLE_DEBUG
  std::cout << "CMAKE cooked!!! W in chat!!!" << std::endl;
#endif
  return 1;
}
