/**
 * The main game file.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
 */

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "general.h"
#include "game.h"
 
int main(int argc, char **argv)
  {
    c_game *game;
	game = new c_game();
	game->run();
	delete game;
  }