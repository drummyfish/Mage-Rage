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

	pole->load_from_file("test.txt");

	cout << pole->get_text("a50") << " " << pole->get_text("a70") << " " << pole->get_text("hehe") << endl;
  
	al_rest(2);
  }