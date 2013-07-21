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
	if(!al_init())                                 // initialise allegro
	  {
	    cerr << "Failed to initialize allegro." << endl;
	  }
 
	if(!al_init_image_addon())
	  {
		cerr << "Failed to initialize al_init_image_addon." << endl; 
	  }
 
	display = al_create_display(800,600);          // initialise screen
 
	if(!this->display)
	  {
		cerr << "Failed to initialize display." << endl; 
	  }

	this->event_queue = al_create_event_queue();   // initialise event queue

	if(!this->event_queue)
	  {
        cerr << "failed to create event_queue." << endl;
      }
	
	this->global_timer = al_create_timer(0.01);    // initialise the timer
	
	if(!this->global_timer)
	  {
        cerr << "failed to create global timer." << endl;
      }

	al_register_event_source(this->event_queue,al_get_display_event_source(display));
	al_register_event_source(this->event_queue,al_get_timer_event_source(this->global_timer));
	this->global_time = 0;
  }

//--------------------------------------------------

void c_game::run()
  {
	
	c_map *map;
    map = new c_map();
	ALLEGRO_EVENT program_event;
	bool quit_program;
	
	ALLEGRO_TIMEOUT timeout;
	bool event_occured;

	al_start_timer(this->global_timer);

	al_init_timeout(&timeout, 0.05);

	quit_program = false;

	while (true)                   // main loop
	  {
		map->update(this->global_time);
	    al_flip_display();

		event_occured = al_wait_for_event_until(event_queue, &program_event, &timeout);

		if (event_occured)
		  switch (program_event.type)
		    {
		      case ALLEGRO_EVENT_DISPLAY_CLOSE:
                quit_program = true;
				break;

			  case ALLEGRO_EVENT_TIMER:
				this->global_time++;
				break;
		    }

		if (quit_program)
		  break;
	  }

	delete map;
  }

//--------------------------------------------------