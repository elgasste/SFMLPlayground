#include "Game.h"
#include "BspTree.h"
#include "GeometricUtilities.h"

using namespace std;
using namespace sf;
using namespace Playground;

Game::Game() :
   _playerPosition( Vector2f( 20, 105 ) ), // sub-sector 6
   _playerMoveIncrement( 2.0f ),
   _playerAngle( RAD_45 ),
   _playerTurnIncrement( RAD_45 / 15.0f ),
   _rayAngleIncrement( ( RAD_30 * 2 ) / SCREEN_WIDTH ),
   _wallHeight( 100.0f ),
   _projectionPlaneDelta( SCREEN_HEIGHT / 2.0f ),
   _lightingScalar( 2.0f )
{
   // TODO: try textured walls

   // outer-most sector
   _sectors.push_back( Sector() );
   _sectors[0].linedefs.push_back( { Vector2f( 0, 0 ), Vector2f( 200, 0 ), Color::Blue } );
   _sectors[0].linedefs.push_back( { Vector2f( 200, 0 ), Vector2f( 200, 120 ), Color::Blue } );
   _sectors[0].linedefs.push_back( { Vector2f( 200, 120 ), Vector2f( 0, 120 ), Color::Blue } );
   _sectors[0].linedefs.push_back( { Vector2f( 0, 120 ), Vector2f( 0, 60 ), Color::Blue } );
   _sectors[0].linedefs.push_back( { Vector2f( 0, 60 ), Vector2f( 60, 60 ), Color::Blue } );
   _sectors[0].linedefs.push_back( { Vector2f( 60, 60 ), Vector2f( 0, 40 ), Color::Blue } );
   _sectors[0].linedefs.push_back( { Vector2f( 0, 40 ), Vector2f( 0, 0 ), Color::Blue } );

   // straight column sector
   _sectors.push_back( Sector() );
   _sectors[1].linedefs.push_back( { Vector2f( 140, 20 ), Vector2f( 140, 40 ), Color::Red } );
   _sectors[1].linedefs.push_back( { Vector2f( 140, 40 ), Vector2f( 160, 40 ), Color::Red } );
   _sectors[1].linedefs.push_back( { Vector2f( 160, 40 ), Vector2f( 160, 20 ), Color::Red } );
   _sectors[1].linedefs.push_back( { Vector2f( 160, 20 ), Vector2f( 140, 20 ), Color::Red } );

   // diagonal column sector
   _sectors.push_back( Sector() );
   _sectors[2].linedefs.push_back( { Vector2f( 100, 60 ), Vector2f( 80, 80 ), Color::Green } );
   _sectors[2].linedefs.push_back( { Vector2f( 80, 80 ), Vector2f( 100, 100 ), Color::Green } );
   _sectors[2].linedefs.push_back( { Vector2f( 100, 100 ), Vector2f( 120, 80 ), Color::Green } );
   _sectors[2].linedefs.push_back( { Vector2f( 120, 80 ), Vector2f( 100, 60 ), Color::Green } );

   _bspTree = shared_ptr<BspTree>( new BspTree( _sectors ) );

   _ceilingRenderRect[0] = Vertex( Vector2f( 0, 0 ), Color( 128, 128, 128 ) );
   _ceilingRenderRect[1] = Vertex( Vector2f( SCREEN_WIDTH, 0 ), Color( 128, 128, 128 ) );
   _ceilingRenderRect[2] = Vertex( Vector2f( SCREEN_WIDTH, SCREEN_HEIGHT / 2.0f ), Color::Black );
   _ceilingRenderRect[3] = Vertex( Vector2f( 0, SCREEN_HEIGHT / 2.0f ), Color::Black );

   _floorRenderRect[0] = Vertex( Vector2f( 0, SCREEN_HEIGHT / 2.0f ), Color::Black );
   _floorRenderRect[1] = Vertex( Vector2f( SCREEN_WIDTH, SCREEN_HEIGHT / 2.0f ), Color::Black );
   _floorRenderRect[2] = Vertex( Vector2f( SCREEN_WIDTH, SCREEN_HEIGHT ), Color( 128, 128, 128 ) );
   _floorRenderRect[3] = Vertex( Vector2f( 0, SCREEN_HEIGHT ), Color( 128, 128, 128 ) );
}

void Game::MoveForward()
{
   auto dx = cos( _playerAngle ) * _playerMoveIncrement;
   auto dy = tan( _playerAngle ) * dx;
   ChangePlayerPosition( dx, -dy );
}

void Game::MoveBack()
{
   auto dx = cos( _playerAngle ) * _playerMoveIncrement;
   auto dy = tan( _playerAngle ) * dx;
   ChangePlayerPosition( -dx, dy );
}

void Game::TurnLeft()
{
   _playerAngle += _playerTurnIncrement;

   if ( _playerAngle >= RAD_360 )
   {
      _playerAngle -= RAD_360;
   }
}

void Game::TurnRight()
{
   _playerAngle -= _playerTurnIncrement;

   if ( _playerAngle < 0 )
   {
      _playerAngle = RAD_360 + _playerAngle;
   }
}

void Game::StrafeLeft()
{
   auto strafeAngle = _playerAngle + RAD_90;
   if ( strafeAngle >= RAD_360 )
   {
      strafeAngle -= RAD_360;
   }
   auto dx = cos( strafeAngle ) * _playerMoveIncrement;
   auto dy = -( tan( strafeAngle ) * dx );
   ChangePlayerPosition( dx, dy );
}

void Game::StrafeRight()
{
   auto strafeAngle = _playerAngle - RAD_90;
   if ( strafeAngle < 0 )
   {
      strafeAngle = RAD_360 + strafeAngle;
   }
   auto dx = cos( strafeAngle ) * _playerMoveIncrement;
   auto dy = -( tan( strafeAngle ) * dx );
   ChangePlayerPosition( dx, dy );
}

void Game::Render( const shared_ptr<RenderWindow> window )
{
   float angle = _playerAngle + RAD_30;
   Vector2f intersectionPoint;
   Linedef intersectingLinedef;

   window->draw( _ceilingRenderRect, 4, Quads );
   window->draw( _floorRenderRect, 4, Quads );

   for ( int i = 0; i < SCREEN_WIDTH; i++, angle -= _rayAngleIncrement )
   {
      if ( angle >= RAD_360 )
      {
         angle -= RAD_360;
      }
      else if ( angle < 0 )
      {
         angle = RAD_360 + angle;
      }

      CheckRayCollisionRecursive( _bspTree->GetRootNode(), _playerPosition, angle, intersectionPoint, intersectingLinedef );

      auto columnIndex = i * 2;

      // the old method. it causes fish-eye.
      //auto rayLength = (float)sqrt( pow( intersectionPoint.x - _playerPosition.x, 2 ) + pow( intersectionPoint.y - _playerPosition.y, 2 ) );

      // from the Wolfenstein 3D book. it's supposed to fix fish-eye, but sometimes it seems to cause reverse-fish-eye
      auto rayLength = ( ( intersectionPoint.x - _playerPosition.x ) * cos( _playerAngle ) ) - ( ( intersectionPoint.y - _playerPosition.y ) * sin( _playerAngle ) );

      // this uses the formula ProjectedWallHeight = ( ActualWallHeight / DistanceToWall ) * DistanceToProjectionPlane
      auto projectedWallHeight = ( ( _wallHeight / rayLength ) * _projectionPlaneDelta );

      auto color = intersectingLinedef.color;
      auto lightAdjustment = ( rayLength == 0.0f ) ? 0.0f : min( rayLength / _lightingScalar, 255.0f );
      color.r = (Uint8)max( 0, (int)( color.r - lightAdjustment ) );
      color.g = (Uint8)max( 0, (int)( color.g - lightAdjustment ) );
      color.b = (Uint8)max( 0, (int)( color.b - lightAdjustment ) );

      _renderColumns[columnIndex].color = color;
      _renderColumns[columnIndex + 1].color = color;
      _renderColumns[columnIndex].position.x = (float)i;
      _renderColumns[columnIndex].position.y = ( SCREEN_HEIGHT / 2.0f ) - ( projectedWallHeight / 2.0f );
      _renderColumns[columnIndex + 1].position.x = (float)i;
      _renderColumns[columnIndex + 1].position.y = ( SCREEN_HEIGHT / 2.0f ) + ( projectedWallHeight / 2.0f );

      window->draw( _renderColumns + columnIndex, 2, Lines );
   }
}

void Game::ChangePlayerPosition( float dx, float dy )
{
   // TODO: check for lineseg collisions
   _playerPosition.x += dx;
   _playerPosition.y += dy;
}

bool Game::CheckRayCollisionRecursive( BspNode* node,
                                       const Vector2f& playerPosition,
                                       float angle,
                                       Vector2f& intersectionPoint,
                                       Linedef& intersectingLinedef ) const
{
   if ( node->type == BspNodeType::Node )
   {
      intersectingLinedef = *node->linedef;

      if ( GeometricUtilities::IsPositionOnRightSide( playerPosition, node->linedef ) )
      {
         return CheckRayCollisionRecursive( node->rightChild, playerPosition, angle, intersectionPoint, intersectingLinedef ) ?
            true : CheckRayCollisionRecursive( node->leftChild, playerPosition, angle, intersectionPoint, intersectingLinedef );
      }
      else
      {
         return CheckRayCollisionRecursive( node->leftChild, playerPosition, angle, intersectionPoint, intersectingLinedef ) ?
            true : CheckRayCollisionRecursive( node->rightChild, playerPosition, angle, intersectionPoint, intersectingLinedef );
      }
   }
   else
   {
      for ( const auto& lineseg : node->subsector->linesegs )
      {
         if ( GeometricUtilities::RayIntersectsLineseg( playerPosition, angle, lineseg, intersectionPoint ) )
         {
            intersectingLinedef = *lineseg.linedef;
            return true;
         }
      }

      return false;
   }
}
