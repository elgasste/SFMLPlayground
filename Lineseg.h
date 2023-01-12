#pragma once

#include <SFML/Graphics.hpp>

#include "Linedef.h"

namespace Playground
{
   struct Lineseg
   {
      Linedef* linedef;
      sf::Vector2f start;
      sf::Vector2f end;
   };
}
