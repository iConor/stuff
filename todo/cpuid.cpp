#include <iostream>
#include <intrin.h>

int main()
{
  int b[4];

  for (int a = 0; a < 5; a++)
  {
    __cpuid(b, a);
    std::cout << "The code " << a << " gives " << b[0] << ", " << b[1] << ", " << b[2] << ", " << b[3] << std::endl;
  }

  __cpuid(b, 7);
  std::cout << "The code " << 7 << " gives " << b[0] << ", " << b[1] << ", " << b[2] << ", " << b[3] << std::endl;

  return 0;
}
