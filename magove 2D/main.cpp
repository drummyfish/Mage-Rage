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
#include "map.h"
 
int main(int argc, char **argv)
  {
	// TEMPORARY CODE !!!!!!!!!!!!!!!!!!!!!!!

	 ALLEGRO_DISPLAY *display = NULL;
	 c_map *map;

	 if(!al_init()) {
		  al_show_native_message_box(display, "Error", "Error", "Failed to initialize allegro!", 
									 NULL, ALLEGRO_MESSAGEBOX_ERROR);
		  return 0;
	   }
 
	   if(!al_init_image_addon()) {
		  al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!", 
									 NULL, ALLEGRO_MESSAGEBOX_ERROR);
		  return 0;
	   }
 
	   display = al_create_display(800,600);
 
	   if(!display) {
		  al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!", 
									 NULL, ALLEGRO_MESSAGEBOX_ERROR);
		  return 0;
	   }

	   map = new c_map();
	   map->draw(50,50);

	   al_flip_display();
       al_rest(10);

	   delete map;
  }