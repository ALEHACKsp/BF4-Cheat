#include "Gun.h"
bool Gun::IsValid ()
{
  return std::strlen(this->Name) > 0;
}
