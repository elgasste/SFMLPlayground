#pragma once

#include <SFML/Graphics.hpp>

#include "Lineseg.h"

namespace Playground
{
   class GeometricUtilities
   {
   public:
      static float CrossProduct( const sf::Vector2f& point, const sf::Vector2f& origin, float dx, float dy );
      static bool IsPositionOnRightSide( const sf::Vector2f& position, Linedef* linedef );
      static bool LineIntersectsLineseg( float p1x, float p1y, float p2x, float p2y, const Lineseg& lineseg, sf::Vector2f& pIntersect );
      static bool RayIntersectsLineseg( const sf::Vector2f& p, float angle, const Lineseg& lineseg, sf::Vector2f& pIntersect );
   };
}
