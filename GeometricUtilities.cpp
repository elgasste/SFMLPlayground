#include <algorithm>

#include "GeometricUtilities.h"
#include "Defines.h"

using namespace std;
using namespace sf;
using namespace Playground;

float GeometricUtilities::CrossProduct( const Vector2f& point, const Vector2f& origin, float dx, float dy )
{
   return ( ( dx * ( point.y - origin.y ) ) - ( dy * ( point.x - origin.x ) ) );
}

bool GeometricUtilities::IsPositionOnRightSide( const Vector2f& position, Linedef* linedef )
{
   auto dx = linedef->end.x - linedef->start.x;
   auto dy = linedef->end.y - linedef->start.y;

   // shortcut if linedef is vertical
   if ( dx == 0 )
   {
      return ( dy > 0 ) ? position.x <= linedef->start.x : position.x > linedef->start.x;
   }

   // shortcut if linedef is horizontal
   if ( dy == 0 )
   {
      return ( dx > 0 ) ? position.y > linedef->start.y : position.y <= linedef->start.y;
   }

   return GeometricUtilities::CrossProduct( position, linedef->start, dx, dy ) > 0;
}

// https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect/1968345#1968345
// Returns true if the lines intersect, an stores the intersection point in pIntersect
bool GeometricUtilities::LineIntersectsLineseg( float p1x, float p1y, float p2x, float p2y, const Lineseg& lineseg, Vector2f& pIntersect )
{
   auto pdx = p2x - p1x;
   auto pdy = p2y - p1y;
   auto ldx = lineseg.end.x - lineseg.start.x;
   auto ldy = lineseg.end.y - lineseg.start.y;
   auto cp = -ldx * pdy + pdx * ldy;

   if ( cp == 0.0f )
   {
      // lines are parallel or collinear
      return false;
   }

   auto s = ( -pdy * ( p1x - lineseg.start.x ) + pdx * ( p1y - lineseg.start.y ) ) / cp;
   auto t = ( ldx * ( p1y - lineseg.start.y ) - ldy * ( p1x - lineseg.start.x ) ) / cp;

   if ( s >= 0 && s <= 1 && t >= 0 && t <= 1 )
   {
      // collision detected
      pIntersect.x = p1x + ( t * pdx );
      pIntersect.y = p1y + ( t * pdy );
      return true;
   }

   return false;
}

bool GeometricUtilities::RayIntersectsLineseg( const Vector2f& p, float angle, const Lineseg& lineseg, Vector2f& pIntersect )
{
   auto dx = cos( angle ) * RAY_LENGTH;
   auto dy = tan( angle ) * dx;
   return LineIntersectsLineseg( p.x, p.y, p.x + dx, p.y - dy, lineseg, pIntersect );
}
