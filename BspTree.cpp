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
   subsector1->linesegs.push_back( { &sectors[1].linedefs[5], Vector2f( 30, 120 ), Vector2f( 60, 90 ) } );
   subsector1->linesegs.push_back( { &sectors[0].linedefs[11], Vector2f( 60, 210 ), Vector2f( 60, 290 ) } );
   subsector1->linesegs.push_back( { &sectors[0].linedefs[12], Vector2f( 60, 290 ), Vector2f( 0, 290 ) } );
   subsector1->linesegs.push_back( { &sectors[0].linedefs[13], Vector2f( 0, 290 ), Vector2f( 0, 150 ) } );

   auto subsector2 = new Subsector;
   subsector2->linesegs.push_back( { &sectors[1].linedefs[4], Vector2f( 20, 110 ), Vector2f( 30, 120 ) } );
   subsector2->linesegs.push_back( { &sectors[0].linedefs[13], Vector2f( 0, 150 ), Vector2f( 0, 90 ) } );

   auto subsector3 = new Subsector;
   subsector3->linesegs.push_back( { &sectors[1].linedefs[3], Vector2f( 40, 90 ), Vector2f( 20, 110 ) } );

   auto subsector4 = new Subsector;
   subsector4->linesegs.push_back( { &sectors[1].linedefs[6], Vector2f( 60, 90 ), Vector2f( 85, 90 ) } );
   subsector4->linesegs.push_back( { &sectors[1].linedefs[7], Vector2f( 85, 90 ), Vector2f( 85, 130 ) } );
   subsector4->linesegs.push_back( { &sectors[0].linedefs[10], Vector2f( 70, 210 ), Vector2f( 60, 210 ) } );

   auto subsector5 = new Subsector;
   subsector5->linesegs.push_back( { &sectors[0].linedefs[9], Vector2f( 85, 225 ), Vector2f( 70, 210 ) } );

   auto subsector6 = new Subsector;
   subsector6->linesegs.push_back( { &sectors[1].linedefs[8], Vector2f( 85, 130 ), Vector2f( 95, 130 ) } );
   subsector6->linesegs.push_back( { &sectors[5].linedefs[2], Vector2f( 155, 195 ), Vector2f( 155, 205 ) } );
   subsector6->linesegs.push_back( { &sectors[0].linedefs[7], Vector2f( 155, 290 ), Vector2f( 150, 290 ) } );
   subsector6->linesegs.push_back( { &sectors[0].linedefs[9], Vector2f( 90, 230 ), Vector2f( 85, 225 ) } );

   auto subsector7 = new Subsector;
   subsector7->linesegs.push_back( { &sectors[0].linedefs[7], Vector2f( 150, 290 ), Vector2f( 90, 290 ) } );
   subsector7->linesegs.push_back( { &sectors[0].linedefs[8], Vector2f( 90, 290 ), Vector2f( 90, 230 ) } );

   auto subsector8 = new Subsector;
   subsector8->linesegs.push_back( { &sectors[1].linedefs[9], Vector2f( 95, 130 ), Vector2f( 95, 90 ) } );
   subsector8->linesegs.push_back( { &sectors[1].linedefs[10], Vector2f( 95, 90 ), Vector2f( 110, 90 ) } );

   auto subsector9 = new Subsector;
   subsector9->linesegs.push_back( { &sectors[0].linedefs[13], Vector2f( 0, 90 ), Vector2f( 0, 40 ) } );
   subsector9->linesegs.push_back( { &sectors[0].linedefs[14], Vector2f( 0, 40 ), Vector2f( 40, 0 ) } );
   subsector9->linesegs.push_back( { &sectors[0].linedefs[0], Vector2f( 40, 0 ), Vector2f( 100, 0 ) } );
   subsector9->linesegs.push_back( { &sectors[1].linedefs[3], Vector2f( 50, 80 ), Vector2f( 40, 90 ) } );

   auto subsector10 = new Subsector;
   subsector10->linesegs.push_back( { &sectors[1].linedefs[1], Vector2f( 100, 60 ), Vector2f( 100, 80 ) } );
   subsector10->linesegs.push_back( { &sectors[1].linedefs[2], Vector2f( 100, 80 ), Vector2f( 50, 80 ) } );

   auto subsector11 = new Subsector;
   subsector11->linesegs.push_back( { &sectors[0].linedefs[0], Vector2f( 100, 0 ), Vector2f( 155, 0 ) } );
   subsector11->linesegs.push_back( { &sectors[1].linedefs[0], Vector2f( 110, 60 ), Vector2f( 100, 60 ) } );

   auto subsector12 = new Subsector;
   subsector12->linesegs.push_back( { &sectors[1].linedefs[11], Vector2f( 110, 90 ), Vector2f( 110, 60 ) } );

   auto subsector13 = new Subsector;
   subsector13->linesegs.push_back( { &sectors[4].linedefs[2], Vector2f( 190, 140 ), Vector2f( 250, 160 ) } );
   subsector13->linesegs.push_back( { &sectors[0].linedefs[3], Vector2f( 260, 160.0f + ( 10.0f / 3.0f ) ), Vector2f( 260, 180 ) } );
   subsector13->linesegs.push_back( { &sectors[0].linedefs[7], Vector2f( 260, 290 ), Vector2f( 185, 290 ) } );
   subsector13->linesegs.push_back( { &sectors[5].linedefs[6], Vector2f( 185, 205 ), Vector2f( 185, 195 ) } );

   auto subsector14 = new Subsector;
   subsector14->linesegs.push_back( { &sectors[0].linedefs[4], Vector2f( 260, 180 ), Vector2f( 300, 200 ) } );
   subsector14->linesegs.push_back( { &sectors[0].linedefs[5], Vector2f( 300, 200 ), Vector2f( 300, 250 ) } );
   subsector14->linesegs.push_back( { &sectors[0].linedefs[6], Vector2f( 300, 250 ), Vector2f( 260, 290 ) } );

   auto subsector15 = new Subsector;
   subsector15->linesegs.push_back( { &sectors[5].linedefs[7], Vector2f( 185, 195 ), Vector2f( 175, 185 ) } );

   auto subsector16 = new Subsector;
   subsector16->linesegs.push_back( { &sectors[5].linedefs[0], Vector2f( 175, 185 ), Vector2f( 165, 185 ) } );

   auto subsector17 = new Subsector;
   subsector17->linesegs.push_back( { &sectors[5].linedefs[1], Vector2f( 165, 185 ), Vector2f( 155, 195 ) } );

   auto subsector18 = new Subsector;
   subsector18->linesegs.push_back( { &sectors[5].linedefs[3], Vector2f( 155, 205 ), Vector2f( 165, 215 ) } );
   subsector18->linesegs.push_back( { &sectors[0].linedefs[7], Vector2f( 185, 290 ), Vector2f( 155, 290 ) } );

   auto subsector19 = new Subsector;
   subsector19->linesegs.push_back( { &sectors[5].linedefs[4], Vector2f( 165, 215 ), Vector2f( 175, 215 ) } );

   auto subsector20 = new Subsector;
   subsector20->linesegs.push_back( { &sectors[5].linedefs[5], Vector2f( 175, 215 ), Vector2f( 185, 205 ) } );

   auto subsector21 = new Subsector;
   subsector21->linesegs.push_back( { &sectors[0].linedefs[1], Vector2f( 300, 0 ), Vector2f( 300, 140.0f + ( 20.0f / 3.0f ) ) } );
   subsector21->linesegs.push_back( { &sectors[0].linedefs[2], Vector2f( 300, 140.0f + ( 20.0f / 3.0f ) ), Vector2f( 260, 130.0f + ( 10.0f / 3.0f ) ) } );
   subsector21->linesegs.push_back( { &sectors[4].linedefs[4], Vector2f( 250, 130 ), Vector2f( 230, 120.0f + ( 10.0f / 3.0f ) ) } );
   subsector21->linesegs.push_back( { &sectors[3].linedefs[2], Vector2f( 260, 40 ), Vector2f( 270, 30 ) } );

   auto subsector22 = new Subsector;
   subsector22->linesegs.push_back( { &sectors[0].linedefs[3], Vector2f( 260, 130.0f + ( 10.0f / 3.0f ) ), Vector2f( 260, 160.0f + ( 10.0f / 3.0f ) ) } );
   subsector22->linesegs.push_back( { &sectors[4].linedefs[3], Vector2f( 250, 160 ), Vector2f( 250, 130 ) } );

   auto subsector23 = new Subsector;
   subsector23->linesegs.push_back( { &sectors[3].linedefs[1], Vector2f( 250, 30 ), Vector2f( 260, 40 ) } );
   subsector23->linesegs.push_back( { &sectors[2].linedefs[3], Vector2f( 230, 70 ), Vector2f( 230, 60 ) } );

   auto subsector24 = new Subsector;
   subsector24->linesegs.push_back( { &sectors[0].linedefs[0], Vector2f( 230, 0 ), Vector2f( 280, 0 ) } );
   subsector24->linesegs.push_back( { &sectors[3].linedefs[0], Vector2f( 260, 20 ), Vector2f( 250, 30 ) } );

   auto subsector25 = new Subsector;
   subsector25->linesegs.push_back( { &sectors[0].linedefs[0], Vector2f( 280, 0 ), Vector2f( 300, 0 ) } );
   subsector25->linesegs.push_back( { &sectors[3].linedefs[3], Vector2f( 270, 30 ), Vector2f( 260, 20 ) } );

   auto subsector26 = new Subsector;
   subsector26->linesegs.push_back( { &sectors[2].linedefs[2], Vector2f( 170, 70 ), Vector2f( 230, 70 ) } );
   subsector26->linesegs.push_back( { &sectors[4].linedefs[4], Vector2f( 230, 120.0f + ( 10.0f / 3.0f ) ), Vector2f( 220, 120 ) } );

   auto subsector27 = new Subsector;
   subsector27->linesegs.push_back( { &sectors[4].linedefs[1], Vector2f( 190, 130 ), Vector2f( 190, 140 ) } );

   auto subsector28 = new Subsector;
   subsector28->linesegs.push_back( { &sectors[4].linedefs[0], Vector2f( 220, 120 ), Vector2f( 190, 130 ) } );

   auto subsector29 = new Subsector;
   subsector29->linesegs.push_back( { &sectors[0].linedefs[0], Vector2f( 155, 0 ), Vector2f( 170, 0 ) } );
   subsector29->linesegs.push_back( { &sectors[2].linedefs[1], Vector2f( 170, 60 ), Vector2f( 170, 70 ) } );

   auto subsector30 = new Subsector;
   subsector30->linesegs.push_back( { &sectors[0].linedefs[0], Vector2f( 170, 0 ), Vector2f( 230, 0 ) } );
   subsector30->linesegs.push_back( { &sectors[2].linedefs[0], Vector2f( 230, 60 ), Vector2f( 170, 60 ) } );

   // build the tree (root node is C5)
   _rootNode = new BspNode;
   _rootNode->type = BspNodeType::Node;
   _rootNode->linedef = &sectors[5].linedefs[2];

   auto nodeG1 = new BspNode;
   nodeG1->type = BspNodeType::Node;
   nodeG1->parent = _rootNode;
   _rootNode->rightChild = nodeG1;
   nodeG1->linedef = &sectors[1].linedefs[6];

   auto nodeH1 = new BspNode;
   nodeH1->type = BspNodeType::Node;
   nodeH1->parent = nodeG1;
   nodeG1->rightChild = nodeH1;
   nodeH1->linedef = &sectors[1].linedefs[7];

   auto nodeL0 = new BspNode;
   nodeL0->type = BspNodeType::Node;
   nodeL0->parent = nodeH1;
   nodeH1->rightChild = nodeL0;
   nodeL0->linedef = &sectors[0].linedefs[11];

   auto nodeF1 = new BspNode;
   nodeF1->type = BspNodeType::Node;
   nodeF1->parent = nodeL0;
   nodeL0->rightChild = nodeF1;
   nodeF1->linedef = &sectors[1].linedefs[5];

   auto node1 = new BspNode;
   node1->type = BspNodeType::Leaf;
   node1->parent = nodeF1;
   nodeF1->rightChild = node1;
   node1->subsector = subsector1;

   auto nodeE1 = new BspNode;
   nodeE1->type = BspNodeType::Node;
   nodeE1->parent = nodeF1;
   nodeF1->leftChild = nodeE1;
   nodeE1->linedef = &sectors[1].linedefs[4];

   auto node2 = new BspNode;
   node2->type = BspNodeType::Leaf;
   node2->parent = nodeE1;
   nodeE1->rightChild = node2;
   node2->subsector = subsector2;

   auto node3 = new BspNode;
   node3->type = BspNodeType::Leaf;
   node3->parent = nodeE1;
   nodeE1->leftChild = node3;
   node3->subsector = subsector3;

   auto nodeK0 = new BspNode;
   nodeK0->type = BspNodeType::Node;
   nodeK0->parent = nodeL0;
   nodeL0->leftChild = nodeK0;
   nodeK0->linedef = &sectors[0].linedefs[10];

   auto node4 = new BspNode;
   node4->type = BspNodeType::Leaf;
   node4->parent = nodeK0;
   nodeK0->rightChild = node4;
   node4->subsector = subsector4;

   auto node5 = new BspNode;
   node5->type = BspNodeType::Leaf;
   node5->parent = nodeK0;
   nodeK0->leftChild = node5;
   node5->subsector = subsector5;

   auto nodeI1 = new BspNode;
   nodeI1->type = BspNodeType::Node;
   nodeI1->parent = nodeH1;
   nodeH1->leftChild = nodeI1;
   nodeI1->linedef = &sectors[1].linedefs[8];

   auto nodeJ0 = new BspNode;
   nodeJ0->type = BspNodeType::Node;
   nodeJ0->parent = nodeI1;
   nodeI1->rightChild = nodeJ0;
   nodeJ0->linedef = &sectors[0].linedefs[9];

   auto node6 = new BspNode;
   node6->type = BspNodeType::Leaf;
   node6->parent = nodeJ0;
   nodeJ0->rightChild = node6;
   node6->subsector = subsector6;

   auto node7 = new BspNode;
   node7->type = BspNodeType::Leaf;
   node7->parent = nodeJ0;
   nodeJ0->leftChild = node7;
   node7->subsector = subsector7;

   auto node8 = new BspNode;
   node8->type = BspNodeType::Leaf;
   node8->parent = nodeI1;
   nodeI1->leftChild = node8;
   node8->subsector = subsector8;

   auto nodeB1 = new BspNode;
   nodeB1->type = BspNodeType::Node;
   nodeB1->parent = nodeG1;
   nodeG1->leftChild = nodeB1;
   nodeB1->linedef = &sectors[1].linedefs[1];

   auto nodeD1 = new BspNode;
   nodeD1->type = BspNodeType::Node;
   nodeD1->parent = nodeB1;
   nodeB1->rightChild = nodeD1;
   nodeD1->linedef = &sectors[1].linedefs[3];

   auto node9 = new BspNode;
   node9->type = BspNodeType::Leaf;
   node9->parent = nodeD1;
   nodeD1->rightChild = node9;
   node9->subsector = subsector9;

   auto node10 = new BspNode;
   node10->type = BspNodeType::Leaf;
   node10->parent = nodeD1;
   nodeD1->leftChild = node10;
   node10->subsector = subsector10;

   auto nodeA1 = new BspNode;
   nodeA1->type = BspNodeType::Node;
   nodeA1->parent = nodeB1;
   nodeB1->leftChild = nodeA1;
   nodeA1->linedef = &sectors[1].linedefs[0];

   auto node11 = new BspNode;
   node11->type = BspNodeType::Leaf;
   node11->parent = nodeA1;
   nodeA1->rightChild = node11;
   node11->subsector = subsector11;

   auto node12 = new BspNode;
   node12->type = BspNodeType::Leaf;
   node12->parent = nodeA1;
   nodeA1->leftChild = node12;
   node12->subsector = subsector12;

   auto nodeC4 = new BspNode;
   nodeC4->type = BspNodeType::Node;
   nodeC4->parent = _rootNode;
   _rootNode->leftChild = nodeC4;
   nodeC4->linedef = &sectors[4].linedefs[2];

   auto nodeG5 = new BspNode;
   nodeG5->type = BspNodeType::Node;
   nodeG5->parent = nodeC4;
   nodeC4->rightChild = nodeG5;
   nodeG5->linedef = &sectors[5].linedefs[6];

   auto nodeD0 = new BspNode;
   nodeD0->type = BspNodeType::Node;
   nodeD0->parent = nodeG5;
   nodeG5->rightChild = nodeD0;
   nodeD0->linedef = &sectors[0].linedefs[3];

   auto node13 = new BspNode;
   node13->type = BspNodeType::Leaf;
   node13->parent = nodeD0;
   nodeD0->rightChild = node13;
   node13->subsector = subsector13;

   auto node14 = new BspNode;
   node14->type = BspNodeType::Leaf;
   node14->parent = nodeD0;
   nodeD0->leftChild = node14;
   node14->subsector = subsector14;

   auto nodeH5 = new BspNode;
   nodeH5->type = BspNodeType::Node;
   nodeH5->parent = nodeG5;
   nodeG5->leftChild = nodeH5;
   nodeH5->linedef = &sectors[5].linedefs[7];

   auto node15 = new BspNode;
   node15->type = BspNodeType::Leaf;
   node15->parent = nodeH5;
   nodeH5->rightChild = node15;
   node15->subsector = subsector15;

   auto nodeA5 = new BspNode;
   nodeA5->type = BspNodeType::Node;
   nodeA5->parent = nodeH5;
   nodeH5->leftChild = nodeA5;
   nodeA5->linedef = &sectors[5].linedefs[0];

   auto node16 = new BspNode;
   node16->type = BspNodeType::Leaf;
   node16->parent = nodeH5;
   nodeA5->rightChild = node16;
   node16->subsector = subsector16;

   auto nodeB5 = new BspNode;
   nodeB5->type = BspNodeType::Node;
   nodeB5->parent = nodeA5;
   nodeA5->leftChild = nodeB5;
   nodeB5->linedef = &sectors[5].linedefs[1];

   auto node17 = new BspNode;
   node17->type = BspNodeType::Leaf;
   node17->parent = nodeB5;
   nodeB5->rightChild = node17;
   node17->subsector = subsector17;

   auto nodeD5 = new BspNode;
   nodeD5->type = BspNodeType::Node;
   nodeD5->parent = nodeB5;
   nodeB5->leftChild = nodeD5;
   nodeD5->linedef = &sectors[5].linedefs[3];

   auto node18 = new BspNode;
   node18->type = BspNodeType::Leaf;
   node18->parent = nodeD5;
   nodeD5->rightChild = node18;
   node18->subsector = subsector18;

   auto nodeE5 = new BspNode;
   nodeE5->type = BspNodeType::Node;
   nodeE5->parent = nodeD5;
   nodeD5->leftChild = nodeE5;
   nodeE5->linedef = &sectors[5].linedefs[4];

   auto node19 = new BspNode;
   node19->type = BspNodeType::Leaf;
   node19->parent = nodeE5;
   nodeE5->rightChild = node19;
   node19->subsector = subsector19;

   auto node20 = new BspNode;
   node20->type = BspNodeType::Leaf;
   node20->parent = nodeE5;
   nodeE5->leftChild = node20;
   node20->subsector = subsector20;

   auto nodeD2 = new BspNode;
   nodeD2->type = BspNodeType::Node;
   nodeD2->parent = nodeC4;
   nodeC4->leftChild = nodeD2;
   nodeD2->linedef = &sectors[2].linedefs[3];

   auto nodeC3 = new BspNode;
   nodeC3->type = BspNodeType::Node;
   nodeC3->parent = nodeD2;
   nodeD2->rightChild = nodeC3;
   nodeC3->linedef = &sectors[3].linedefs[2];

   auto nodeC0 = new BspNode;
   nodeC0->type = BspNodeType::Node;
   nodeC0->parent = nodeC3;
   nodeC3->rightChild = nodeC0;
   nodeC0->linedef = &sectors[0].linedefs[2];

   auto node21 = new BspNode;
   node21->type = BspNodeType::Leaf;
   node21->parent = nodeC0;
   nodeC0->rightChild = node21;
   node21->subsector = subsector21;

   auto node22 = new BspNode;
   node22->type = BspNodeType::Leaf;
   node22->parent = nodeC0;
   nodeC0->leftChild = node22;
   node22->subsector = subsector22;

   auto nodeB3 = new BspNode;
   nodeB3->type = BspNodeType::Node;
   nodeB3->parent = nodeC3;
   nodeC3->leftChild = nodeB3;
   nodeB3->linedef = &sectors[3].linedefs[1];

   auto node23 = new BspNode;
   node23->type = BspNodeType::Leaf;
   node23->parent = nodeB3;
   nodeB3->rightChild = node23;
   node23->subsector = subsector23;

   auto nodeA3 = new BspNode;
   nodeA3->type = BspNodeType::Node;
   nodeA3->parent = nodeB3;
   nodeB3->leftChild = nodeA3;
   nodeA3->linedef = &sectors[3].linedefs[0];

   auto node24 = new BspNode;
   node24->type = BspNodeType::Leaf;
   node24->parent = nodeA3;
   nodeA3->rightChild = node24;
   node24->subsector = subsector24;

   auto node25 = new BspNode;
   node25->type = BspNodeType::Leaf;
   node25->parent = nodeA3;
   nodeA3->leftChild = node25;
   node25->subsector = subsector25;

   auto nodeC2 = new BspNode;
   nodeC2->type = BspNodeType::Node;
   nodeC2->parent = nodeD2;
   nodeD2->leftChild = nodeC2;
   nodeC2->linedef = &sectors[2].linedefs[2];

   auto nodeE4 = new BspNode;
   nodeE4->type = BspNodeType::Node;
   nodeE4->parent = nodeC2;
   nodeC2->rightChild = nodeE4;
   nodeE4->linedef = &sectors[4].linedefs[4];

   auto node26 = new BspNode;
   node26->type = BspNodeType::Leaf;
   node26->parent = nodeE4;
   nodeE4->rightChild = node26;
   node26->subsector = subsector26;

   auto nodeB4 = new BspNode;
   nodeB4->type = BspNodeType::Node;
   nodeB4->parent = nodeE4;
   nodeE4->leftChild = nodeB4;
   nodeB4->linedef = &sectors[4].linedefs[1];

   auto node27 = new BspNode;
   node27->type = BspNodeType::Leaf;
   node27->parent = nodeB4;
   nodeB4->rightChild = node27;
   node27->subsector = subsector27;

   auto node28 = new BspNode;
   node28->type = BspNodeType::Leaf;
   node28->parent = nodeB4;
   nodeB4->leftChild = node28;
   node28->subsector = subsector28;

   auto nodeB2 = new BspNode;
   nodeB2->type = BspNodeType::Node;
   nodeB2->parent = nodeC2;
   nodeC2->leftChild = nodeB2;
   nodeB2->linedef = &sectors[2].linedefs[1];

   auto node29 = new BspNode;
   node29->type = BspNodeType::Leaf;
   node29->parent = nodeB2;
   nodeB2->rightChild = node29;
   node29->subsector = subsector29;

   auto node30 = new BspNode;
   node30->type = BspNodeType::Leaf;
   node30->parent = nodeB2;
   nodeB2->leftChild = node30;
   node30->subsector = subsector30;
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
