#include "Game.h"

using namespace std;
using namespace sf;
using namespace Playground;

int main()
{
   auto videoMode = VideoMode( SCREEN_WIDTH, SCREEN_HEIGHT );
   auto window = shared_ptr<RenderWindow>( new RenderWindow( videoMode, "SFML Playground", Style::Titlebar | Style::Close ) );
   window->setFramerateLimit( 60 );

   auto game = make_shared<Game>();

   window->display();

   while ( window->isOpen() )
   {
      Event e;

      while ( window->pollEvent( e ) )
      {
         switch ( e.type )
         {
            case Event::Closed:
               window->close();
               break;
            case Event::KeyPressed:
               if ( e.key.code == Keyboard::Escape )
               {
                  window->close();
               }
               break;
         }
      }

      if ( Keyboard::isKeyPressed( Keyboard::Up ) || Keyboard::isKeyPressed( Keyboard::W ) )
      {
         game->MoveForward();
      }
      if ( Keyboard::isKeyPressed( Keyboard::Down ) || Keyboard::isKeyPressed( Keyboard::S ) )
      {
         game->MoveBack();
      }
      if ( Keyboard::isKeyPressed( Keyboard::A ) )
      {
         game->StrafeLeft();
      }
      if ( Keyboard::isKeyPressed( Keyboard::D ) )
      {
         game->StrafeRight();
      }
      if ( Keyboard::isKeyPressed( Keyboard::Left ) )
      {
         game->TurnLeft();
      }
      if ( Keyboard::isKeyPressed( Keyboard::Right ) )
      {
         game->TurnRight();
      }

      window->clear();
      game->Render( window );
      window->display();
   }

   return 0;
}
