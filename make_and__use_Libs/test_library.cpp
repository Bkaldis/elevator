#include "test_library.h"

int count = 0;

int addPrevInt(int a)
{
  count = a + count;
  return count;
}
