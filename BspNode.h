#pragma once

#include "BspNodeType.h"
#include "Subsector.h"

namespace Playground
{
   struct BspNode
   {
      BspNodeType type;

      BspNode* parent = nullptr;
      BspNode* leftChild = nullptr;
      BspNode* rightChild = nullptr;

      Linedef* linedef = nullptr;
      Subsector* subsector = nullptr;
   };
}
