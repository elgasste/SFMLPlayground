#pragma once

#include "Sector.h"
#include "BspNode.h"

namespace Playground
{
   class BspTree
   {
   public:
      BspTree( std::vector<Sector>& sectors );
      ~BspTree();

      BspNode* GetRootNode() const { return _rootNode; }

   private:
      void DeleteNodeRecursive( BspNode* node );

   private:
      BspNode* _rootNode;
   };
}
