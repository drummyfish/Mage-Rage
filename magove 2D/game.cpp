/**
 * Game class implementation file.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
 */

#include "game.h"

//-----------------------------------------------

c_game::c_game()
  {   
	if (!al_init())                                // initialise allegro
	  {
	    cerr << "ERROR: failed to initialize allegro." << endl;
	  }
 
	if (!al_init_image_addon())                    // initialise image addon
	  {
		cerr << "ERROR: failed to initialize al_init_image_addon." << endl; 
	  }
 
	if (!al_install_keyboard())                    // initialise keyboard
	  {
        cerr << "ERROR: failed to initialize the keyboard." << endl;
      }

	if (!al_install_audio())                       // initialise audio
	  {
        cerr << "ERROR: failed to initialize audio." << endl;
      }
 
    if (!al_init_acodec_addon())
	  {
        cerr << "ERROR: failed to initialize audio codecs." << endl;
      }

	display = al_create_display(800,600);          // initialise screen
 
	if(!this->display)
	  {
		cerr << "ERROR: failed to initialize display." << endl; 
	  }
	
	this->event_queue = al_create_event_queue();   // initialise event queue

	if(!this->event_queue)
	  {
        cerr << "ERROR: failed to create event_queue." << endl;
      }

	this->global_timer = al_create_timer(0.05);    // initialise the timer
	
	if(!this->global_timer)
	  {
        cerr << "ERROR: failed to create global timer." << endl;
      }

	al_register_event_source(this->event_queue,al_get_display_event_source(display));
	al_register_event_source(this->event_queue,al_get_timer_event_source(this->global_timer));
	al_register_event_source(this->event_queue,al_get_keyboard_event_source());
	this->global_time = 0;

	this->input_state.key_down = false;            // set keyboard/mouse state
	this->input_state.key_up = false;
	this->input_state.key_left = false;
	this->input_state.key_right = false;
	this->input_state.key_1 = false;
	this->input_state.key_2 = false;
	this->input_state.key_3 = false;
	this->input_state.mouse_x = 0;
	this->input_state.mouse_y = 0;
	this->input_state.key_use = false;
  }

//-----------------------------------------------

c_game::~c_game()
  {
	al_destroy_event_queue(this->event_queue);
	al_destroy_timer(this->global_timer); 
	al_destroy_display(this->display);
    delete this->map;
  }

//-----------------------------------------------

void c_game::run()
  {
	c_map *map;
	string help_str;

	map = new c_map(help_str,&this->input_state,&this->global_time);

	if (!map->is_succesfully_loaded())
	  {
		cerr << "ERROR: the map couldn't be loaded." << endl;
	  }

	ALLEGRO_EVENT program_event;
	bool quit_program;
	
	ALLEGRO_TIMEOUT timeout;
	bool event_occured;

	al_start_timer(this->global_timer);

	al_init_timeout(&timeout, 0.05);

	quit_program = false;
	
	while (true)                   // main loop
	  { 
		map->update(); 
	    al_flip_display();
		
		this->input_state.key_use = false;             // we only want to detect one press

		event_occured = al_get_next_event(this->event_queue, &program_event);

		if (event_occured)                             // handle events
		  switch (program_event.type)
		    {
		      case ALLEGRO_EVENT_DISPLAY_CLOSE:        // program close
                quit_program = true;
				break;

			  case ALLEGRO_EVENT_TIMER:                // global timer event
				this->global_time++;
				break;

			  case ALLEGRO_EVENT_KEY_DOWN:             // key down event
				switch(program_event.keyboard.keycode)
				  {
					case ALLEGRO_KEY_UP:
					   this->input_state.key_up = true;
					   break;
 
					case ALLEGRO_KEY_DOWN:
					   this->input_state.key_down = true;
					   break;
 
					case ALLEGRO_KEY_LEFT: 
					   this->input_state.key_left = true;
					   break;
 
					case ALLEGRO_KEY_RIGHT:
					   this->input_state.key_right = true;
					   break;

					case ALLEGRO_KEY_1:
					   this->input_state.key_1 = true;
					   break;

					case ALLEGRO_KEY_2:
					   this->input_state.key_2 = true;
					   break;

					case ALLEGRO_KEY_3:
					   this->input_state.key_3 = true;
					   break;

					case ALLEGRO_KEY_Q:
					  this->input_state.key_use = true;
					  break;
				  }
				break;

			  case ALLEGRO_EVENT_KEY_UP:               // key up event
				switch(program_event.keyboard.keycode)
				  {
					case ALLEGRO_KEY_UP:
					   this->input_state.key_up = false;
					   break;
 
					case ALLEGRO_KEY_DOWN:
					   this->input_state.key_down = false;
					   break;
 
					case ALLEGRO_KEY_LEFT: 
					   this->input_state.key_left = false;
					   break;
 
					case ALLEGRO_KEY_RIGHT:
					   this->input_state.key_right = false;
					   break;

					case ALLEGRO_KEY_1:
					   this->input_state.key_1 = false;
					   break;

					case ALLEGRO_KEY_2:
					   this->input_state.key_2 = false;
					   break;

					case ALLEGRO_KEY_3:
					   this->input_state.key_3 = false;
					   break;
				  }
				break;
		    }

		if (quit_program)
		  break;

		al_rest(0.01); 
	  }
  }

//-----------------------------------------------