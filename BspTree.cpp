#include "BspTree.h"
#include "GeometricUtilities.h"

using namespace std;
using namespace sf;
using namespace Playground;

BspTree::BspTree( vector<Sector>& sectors ) :
   _rootNode( nullptr )
{
   // all subsectors and linesegs
   auto subsector1 = new Subsector;
   subsector1->linesegs.push_back( { &sectors[0].linedefs[0], Vector2f( 40, 0 ), Vector2f( 140, 0 ) } );
   subsector1->linesegs.push_back( { &sectors[1].linedefs[1], Vector2f( 140, 20 ), Vector2f( 140, 40 ) } );
   subsector1->linesegs.push_back( { &sectors[2].linedefs[2], Vector2f( 120, 80 ), Vector2f( 100, 60 ) } );

   auto subsector2 = new Subsector;
   subsector2->linesegs.push_back( { &sectors[0].linedefs[1], Vector2f( 200, 40 ), Vector2f( 200, 120 ) } );
   subsector2->linesegs.push_back( { &sectors[0].linedefs[2], Vector2f( 200, 120 ), Vector2f( 160, 120 ) } );
   subsector2->linesegs.push_back( { &sectors[1].linedefs[1], Vector2f( 140, 40 ), Vector2f( 160, 40 ) } );

   auto subsector3 = new Subsector;
   subsector3->linesegs.push_back( { &sectors[0].linedefs[0], Vector2f( 160, 0 ), Vector2f( 200, 0 ) } );
   subsector3->linesegs.push_back( { &sectors[0].linedefs[1], Vector2f( 200, 0 ), Vector2f( 200, 40 ) } );
   subsector3->linesegs.push_back( { &sectors[1].linedefs[2], Vector2f( 160, 40 ), Vector2f( 160, 20 ) } );

   auto subsector4 = new Subsector;
   subsector4->linesegs.push_back( { &sectors[0].linedefs[0], Vector2f( 140, 0 ), Vector2f( 160, 0 ) } );
   subsector4->linesegs.push_back( { &sectors[1].linedefs[3], Vector2f( 160, 20 ), Vector2f( 140, 20 ) } );

   auto subsector5 = new Subsector;
   subsector5->linesegs.push_back( { &sectors[0].linedefs[0], Vector2f( 0, 0 ), Vector2f( 40, 0 ) } );
   subsector5->linesegs.push_back( { &sectors[2].linedefs[0], Vector2f( 100, 60 ), Vector2f( 90, 70 ) } );
   subsector5->linesegs.push_back( { &sectors[0].linedefs[5], Vector2f( 60, 60 ), Vector2f( 0, 40 ) } );
   subsector5->linesegs.push_back( { &sectors[0].linedefs[6], Vector2f( 0, 40 ), Vector2f( 0, 0 ) } );

   auto subsector6 = new Subsector;
   subsector6->linesegs.push_back( { &sectors[0].linedefs[4], Vector2f( 0, 60 ), Vector2f( 60, 60 ) } );
   subsector6->linesegs.push_back( { &sectors[2].linedefs[0], Vector2f( 90, 70 ), Vector2f( 80, 80 ) } );
   subsector6->linesegs.push_back( { &sectors[0].linedefs[2], Vector2f( 40, 120 ), Vector2f( 0, 120 ) } );
   subsector6->linesegs.push_back( { &sectors[0].linedefs[3], Vector2f( 0, 120 ), Vector2f( 0, 60 ) } );

   auto subsector7 = new Subsector;
   subsector7->linesegs.push_back( { &sectors[2].linedefs[1], Vector2f( 80, 80 ), Vector2f( 100, 100 ) } );
   subsector7->linesegs.push_back( { &sectors[0].linedefs[2], Vector2f( 120, 120 ), Vector2f( 40, 120 ) } );

   auto subsector8 = new Subsector;
   subsector8->linesegs.push_back( { &sectors[2].linedefs[2], Vector2f( 100, 100 ), Vector2f( 120, 80 ) } );
   subsector8->linesegs.push_back( { &sectors[0].linedefs[2], Vector2f( 160, 120 ), Vector2f( 120, 120 ) } );

   // build the tree
   _rootNode = new BspNode;
   _rootNode->type = BspNodeType::Node;
   _rootNode->linedef = &sectors[2].linedefs[3];

   auto nodeH = new BspNode;
   nodeH->type = BspNodeType::Node;
   nodeH->parent = _rootNode;
   _rootNode->leftChild = nodeH;
   nodeH->linedef = &sectors[2].linedefs[0];

   auto nodeK = new BspNode;
   nodeK->type = BspNodeType::Node;
   nodeK->parent = nodeH;
   nodeH->leftChild = nodeK;
   nodeK->linedef = &sectors[2].linedefs[1];

   auto leaf8 = new BspNode;
   leaf8->type = BspNodeType::Leaf;
   leaf8->parent = nodeK;
   nodeK->leftChild = leaf8;
   leaf8->subsector = subsector8;

   auto leaf7 = new BspNode;
   leaf7->type = BspNodeType::Leaf;
   leaf7->parent = nodeK;
   nodeK->rightChild = leaf7;
   leaf7->subsector = subsector7;

   auto nodeC = new BspNode;
   nodeC->type = BspNodeType::Node;
   nodeC->parent = nodeH;
   nodeH->rightChild = nodeC;
   nodeC->linedef = &sectors[0].linedefs[5];

   auto leaf6 = new BspNode;
   leaf6->type = BspNodeType::Leaf;
   leaf6->parent = nodeC;
   nodeC->leftChild = leaf6;
   leaf6->subsector = subsector6;

   auto leaf5 = new BspNode;
   leaf5->type = BspNodeType::Leaf;
   leaf5->parent = nodeC;
   nodeC->rightChild = leaf5;
   leaf5->subsector = subsector5;

   auto nodeL = new BspNode;
   nodeL->type = BspNodeType::Node;
   nodeL->parent = _rootNode;
   _rootNode->rightChild = nodeL;
   nodeL->linedef = &sectors[1].linedefs[0];

   auto nodeO = new BspNode;
   nodeO->type = BspNodeType::Node;
   nodeO->parent = nodeL;
   nodeL->leftChild = nodeO;
   nodeO->linedef = &sectors[1].linedefs[1];

   auto nodeN = new BspNode;
   nodeN->type = BspNodeType::Node;
   nodeN->parent = nodeO;
   nodeO->leftChild = nodeN;
   nodeN->linedef = &sectors[1].linedefs[2];

   auto leaf4 = new BspNode;
   leaf4->type = BspNodeType::Leaf;
   leaf4->parent = nodeN;
   nodeN->leftChild = leaf4;
   leaf4->subsector = subsector4;

   auto leaf3 = new BspNode;
   leaf3->type = BspNodeType::Leaf;
   leaf3->parent = nodeN;
   nodeN->rightChild = leaf3;
   leaf3->subsector = subsector3;

   auto leaf2 = new BspNode;
   leaf2->type = BspNodeType::Leaf;
   leaf2->parent = nodeO;
   nodeO->rightChild = leaf2;
   leaf2->subsector = subsector2;

   auto leaf1 = new BspNode;
   leaf1->type = BspNodeType::Leaf;
   leaf1->parent = nodeL;
   nodeL->rightChild = leaf1;
   leaf1->subsector = subsector1;
}

BspTree::~BspTree()
{
   DeleteNodeRecursive( _rootNode );
}

void BspTree::DeleteNodeRecursive( BspNode* node )
{
   if ( !node )
   {
      return;
   }

   if ( node->subsector )
   {
      delete node->subsector;
      node->subsector = nullptr;
   }

   DeleteNodeRecursive( node->leftChild );
   DeleteNodeRecursive( node->rightChild );

   delete node;
   node = nullptr;
}
