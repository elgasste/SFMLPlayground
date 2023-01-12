#pragma once

#include <SFML/Window.hpp>
#include <memory>
#include <vector>

#include "Defines.h"
#include "Sector.h"
#include "BspNode.h"

namespace sf
{
   class RenderWindow;
}

namespace Playground
{
   class BspTree;

   class Game
   {
   public:
      Game();

      void MoveForward();
      void MoveBack();
      void TurnLeft();
      void TurnRight();
      void StrafeLeft();
      void StrafeRight();

      void Render( const std::shared_ptr<sf::RenderWindow> window );

   private:
      void ChangePlayerPosition( float dx, float dy );
      bool CheckRayCollisionRecursive( BspNode* node,
                                       const sf::Vector2f& playerPosition,
                                       float angle,
                                       sf::Vector2f& intersectionPoint,
                                       Linedef& intersectingLinedef ) const;

   private:
      std::vector<Sector> _sectors;
      std::shared_ptr<BspTree> _bspTree;
      sf::Vertex _renderColumns[SCREEN_WIDTH * 2];

      sf::Vector2f _playerPosition;
      float _playerMoveIncrement;
      float _playerAngle;
      float _playerTurnIncrement;

      float _rayAngleIncrement;

      float _wallHeight;
      float _projectionPlaneDelta;
      float _lightingScalar;
   };
}
