#pragma once

#include <vector>

#include "Linedef.h"

namespace Playground
{
   struct Sector
   {
      std::vector<Linedef> linedefs;
   };
}
