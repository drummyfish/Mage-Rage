/**
 * Game class implementation file.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
 */

#include "game.h"

//--------------------------------------------------

c_game::c_game()
  {
    ALLEGRO_DISPLAY *display = NULL;

	if(!al_init())                                 // initialise allegro
	  {
	    cerr << "Failed to initialize allegro." << endl;
	  }
 
	if(!al_init_image_addon())
	  {
		cerr << "Failed to initialize al_init_image_addon." << endl; 
	  }
 
	display = al_create_display(800,600);          // initialise screen
 
	if(!display)
	  {
		cerr << "Failed to initialize display." << endl; 
	  }

	event_queue = al_create_event_queue();         // initialise event queue

	if(!event_queue)
	  {
        cerr << "failed to create event_queue." << endl;
      }

	 al_register_event_source(event_queue, al_get_display_event_source(display));
  }

//--------------------------------------------------

void c_game::run()
  {
	c_map *map;
    map = new c_map();
	ALLEGRO_EVENT program_event;
	ALLEGRO_TIMEOUT timeout;
	bool event_occured;

	al_init_timeout(&timeout, 0.06);
	event_occured = false;

	while (true)                // main loop
	  {
        map->draw(50,50);
	    al_flip_display();

		event_occured = al_wait_for_event_until(event_queue, &program_event, &timeout);

		if (event_occured && program_event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		  break;                // window close event -> end the program

        al_rest(0.02);
	  }

	delete map;
  }

//--------------------------------------------------