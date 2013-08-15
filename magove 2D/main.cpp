/**
 * The main game file.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
 */

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "associative_array.h"
#include "general.h"
#include "game.h"
 
int main(int argc, char **argv)
  {
    c_game *game;
	game = new c_game();
//	game->run();
	delete game;

	c_associative_array* pole;
	pole = new c_associative_array();

	int i;

	pole->set_text("jedna","neco jedna");
	pole->set_text("dvaa","  sasaASas123");
	pole->set_text("trii","ssssssss");

	pole->save_to_file("test.txt");

	al_rest(2);
  }