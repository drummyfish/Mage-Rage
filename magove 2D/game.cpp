/**
 * Game class implementation file.
 *
 * authors: Miloslav Číž
 * year: 2013
 */

#include "game.h"

//-----------------------------------------------

c_game::c_game()
  {   
	string help_array[1];
	ALLEGRO_DISPLAY_MODE display_data;

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
 
	if (!al_reserve_samples(20))                   // reserve audio samples
	  {
        cerr << "ERROR: failed to reserve samples." << endl;
      }

    if (!al_init_acodec_addon())                   // initialise audio codec addon
	  {
        cerr << "ERROR: failed to initialize audio codecs." << endl;
      }

    if (!al_init_primitives_addon())               // initialise primitives addon
	  {
		cerr << "ERROR: failed to initialize primitives addon." << endl;
	  }

	al_init_font_addon();                          // initialise the font addon
    al_init_ttf_addon();                           // initialise the ttf addon

	if(!al_install_mouse())
	  {
        cerr << "ERROR: failed to initialize mouse." << endl;
      }
	
	this->win_sound = al_load_sample("resources/win.wav");
	this->lose_sound = al_load_sample("resources/lose.wav");

	this->load();                                  // load the progress and settings from the data file

	if (this->settings.fullscreen)
	  {
		al_get_display_mode(al_get_num_display_modes() - 1,&display_data);
		al_set_new_display_flags(ALLEGRO_FULLSCREEN);
		this->input_output_state.screen_x = display_data.width;
		this->input_output_state.screen_y = display_data.height;
	  }
	else
	  {
		this->input_output_state.screen_x = 800;
		this->input_output_state.screen_y = 600;
	  }

    display = al_create_display(this->input_output_state.screen_x,this->input_output_state.screen_y);  // initialise screen

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

	this->local_texts = new c_associative_array();      // set the language
	this->set_language(this->settings.language);

	al_register_event_source(this->event_queue,al_get_display_event_source(display));
	al_register_event_source(this->event_queue,al_get_timer_event_source(this->global_timer));
	al_register_event_source(this->event_queue,al_get_keyboard_event_source());
	this->global_time = 0;
	
	this->cheat_buffer[0] = 0;
	this->cheat_used = false;

	al_hide_mouse_cursor(display);
	
	this->set_keys();
	this->update_volume();

	this->input_output_state.key_down = false;            // set keyboard/mouse state
	this->input_output_state.key_up = false;
	this->input_output_state.key_left = false;
	this->input_output_state.key_right = false;
	this->input_output_state.key_1 = false;
	this->input_output_state.key_2 = false;
	this->input_output_state.key_3 = false;
	this->input_output_state.mouse_x = 0;
	this->input_output_state.mouse_y = 0;
	this->input_output_state.key_use = false;
	this->input_output_state.key_cast_1 = false;
	this->input_output_state.key_cast_2 = false;
	this->input_output_state.key_cast_3 = false;
	this->input_output_state.mouse_1 = false; 
	this->input_output_state.key_map_explore = false;
	this->input_output_state.key_back = false;
	this->music = NULL;

	this->map = NULL;
  }

//-----------------------------------------------

void c_game::initialise_new_game(int level_number)
  {
	int language;

	if (this->map != NULL)
	  {
	    delete this->map;
	  }

	if (this->settings.language.compare("english") == 0)
	  language = 0;
	else
	  language = 1;

	if (level_number >= 1 && level_number <= 22)
	  this->map = new c_map("resources/map" + to_string((long long) level_number),&this->input_output_state,&this->global_time,language);
  }

//-----------------------------------------------

void c_game::update_volume()
  {
	double gain;

	gain = this->settings.sound_volume / (double) 100;

	if (gain > 1.0)
	  gain = 1.0;
	else if (gain < 0.0)
      gain = 0.0;

	al_set_mixer_gain(al_get_default_mixer(),gain);
  }

//-----------------------------------------------

void c_game::set_keys()
  {
	this->key_up = ALLEGRO_KEY_UP;
	this->key_down = ALLEGRO_KEY_DOWN;
	this->key_right = ALLEGRO_KEY_RIGHT;
	this->key_left = ALLEGRO_KEY_LEFT;
	this->key_cast1 = ALLEGRO_KEY_Q;
	this->key_cast2 = ALLEGRO_KEY_W;
	this->key_cast3 = ALLEGRO_KEY_E;
	this->key_switch1 = ALLEGRO_KEY_1;
	this->key_switch2 = ALLEGRO_KEY_2;
	this->key_switch3  = ALLEGRO_KEY_3;
	this->key_use = ALLEGRO_KEY_ENTER;
	this->key_use_alt = ALLEGRO_KEY_F;
	this->key_back = ALLEGRO_KEY_ESCAPE;
	this->key_map = ALLEGRO_KEY_SPACE;
  }

//-----------------------------------------------

void c_game::set_language(string language)
  {
	this->settings.language = language;

	if (this->settings.language.compare("english") == 0)
	  this->local_texts->load_from_file("resources/local_texts_english");
	else
	  this->local_texts->load_from_file("resources/local_texts_czech");

    this->main_menu_title = this->local_texts->get_text("main_menu_title");
	this->main_menu_items[0] = this->local_texts->get_text("main_menu_0");
	this->main_menu_items[1] = this->local_texts->get_text("main_menu_1");
	this->main_menu_items[2] = this->local_texts->get_text("main_menu_2");
	this->main_menu_items[3] = this->local_texts->get_text("main_menu_3");
	this->main_menu_items[4] = this->local_texts->get_text("main_menu_4");
	this->game_menu_title = this->local_texts->get_text("game_menu_title");
	this->game_menu_items[0] = this->local_texts->get_text("game_menu_0");
	this->game_menu_items[1] = this->local_texts->get_text("game_menu_1");
	this->game_menu_items[2] = this->local_texts->get_text("game_menu_2");
	this->game_menu_items[3] = this->local_texts->get_text("game_menu_3");
	this->settings_menu_title = this->local_texts->get_text("settings_menu_title");
	this->settings_menu_items[0] = this->local_texts->get_text("settings_menu_0");
	this->settings_menu_items[1] = this->local_texts->get_text("settings_menu_1");
	this->settings_menu_items[2] = this->local_texts->get_text("settings_menu_2");
	this->settings_menu_items[3] = this->local_texts->get_text("settings_menu_3");
	this->settings_menu_items[4] = this->local_texts->get_text("settings_menu_4");
	this->about_lines[0] = this->local_texts->get_text("about_0") + VERSION;         // append the program version number
	this->about_lines[1] = this->local_texts->get_text("about_1");
	this->about_lines[2] = this->local_texts->get_text("about_2");
	this->intro_lines_1[0] = this->local_texts->get_text("intro_0");
	this->intro_lines_1[1] = this->local_texts->get_text("intro_1");
	this->intro_lines_1[2] = this->local_texts->get_text("intro_2");
	this->intro_lines_1[3] = this->local_texts->get_text("intro_3");
	this->intro_lines_1[4] = this->local_texts->get_text("intro_4");
	this->intro_lines_1[5] = this->local_texts->get_text("intro_5");
	this->intro_lines_1[6] = this->local_texts->get_text("intro_6");
	this->intro_lines_1[7] = this->local_texts->get_text("intro_7");
	this->intro_lines_1[8] = this->local_texts->get_text("intro_8");
	this->intro_lines_1[9] = this->local_texts->get_text("intro_9");
	this->intro_lines_2[0] = this->local_texts->get_text("intro_10");
	this->intro_lines_2[1] = this->local_texts->get_text("intro_11");
	this->intro_lines_2[2] = this->local_texts->get_text("intro_12");
	this->intro_lines_2[3] = this->local_texts->get_text("intro_13");
	this->intro_lines_2[4] = this->local_texts->get_text("intro_14");
	this->intro_lines_2[5] = this->local_texts->get_text("intro_15");
	this->intro_lines_2[6] = this->local_texts->get_text("intro_16");
	this->intro_lines_2[7] = this->local_texts->get_text("intro_17");
	this->intro_lines_2[8] = this->local_texts->get_text("intro_18");
	this->intro_lines_2[9] = this->local_texts->get_text("intro_19");
	this->outro_lines[0] = this->local_texts->get_text("outro_0");
	this->outro_lines[1] = this->local_texts->get_text("outro_1");
	this->outro_lines[2] = this->local_texts->get_text("outro_2");
	this->outro_lines[3] = this->local_texts->get_text("outro_3");
	this->outro_lines[4] = this->local_texts->get_text("outro_4");
	this->outro_lines[5] = this->local_texts->get_text("outro_5");
	this->outro_lines[6] = this->local_texts->get_text("outro_6");
	this->outro_lines[7] = this->local_texts->get_text("outro_7");
	this->outro_lines[8] = this->local_texts->get_text("outro_8");
	this->outro_lines[9] = this->local_texts->get_text("outro_9");
	this->how_to_play_lines[0] = this->local_texts->get_text("how_to_play_0");
	this->how_to_play_lines[1] = this->local_texts->get_text("how_to_play_1");
	this->how_to_play_lines[2] = this->local_texts->get_text("how_to_play_2");
	this->how_to_play_lines[3] = this->local_texts->get_text("how_to_play_3");
	this->how_to_play_lines[4] = this->local_texts->get_text("how_to_play_4");
	this->how_to_play_lines[5] = this->local_texts->get_text("how_to_play_5");
	this->how_to_play_lines[6] = this->local_texts->get_text("how_to_play_6");
	this->how_to_play_lines[7] = this->local_texts->get_text("how_to_play_7");
	this->how_to_play_lines[8] = this->local_texts->get_text("how_to_play_8");
	this->how_to_play_lines[9] = this->local_texts->get_text("how_to_play_9");
  }

//-----------------------------------------------

c_game::~c_game()
  {
	al_stop_samples();                           // stop all sounds	
	delete this->map;
	delete this->menu;
	delete this->local_texts;
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_shutdown_primitives_addon();
	al_shutdown_image_addon();
	al_shutdown_font_addon();
	al_destroy_timer(this->global_timer); 
	al_destroy_display(this->display);
	al_destroy_event_queue(this->event_queue);
	al_destroy_sample(this->win_sound);
	al_destroy_sample(this->lose_sound);
	al_destroy_sample(this->music);
	al_uninstall_audio();
  }

//-----------------------------------------------

void c_game::load()
  {
    c_associative_array *associate_array;

	associate_array = new c_associative_array();

	if (associate_array == NULL)
	  return;

	associate_array->load_from_file("data");
	this->settings.fullscreen = (associate_array->get_text("fullscreen").compare("1") == 0);
	this->settings.music_on = (associate_array->get_text("music_on").compare("1") == 0);
	this->settings.sound_volume = atoi(associate_array->get_text("sound_volume").c_str());
	this->settings.last_level = atoi(associate_array->get_text("last_level").c_str());
	this->settings.language = associate_array->get_text("language");

	delete associate_array;
  }

//-----------------------------------------------

void c_game::save()
  {
    c_associative_array *associate_array;

	associate_array = new c_associative_array();

	if (associate_array == NULL)
	  return;

	if (this->settings.fullscreen)
	  associate_array->set_text("fullscreen","1");
	else
	  associate_array->set_text("fullscreen","0");

	if (this->settings.music_on)
	  associate_array->set_text("music_on","1");
	else
	  associate_array->set_text("music_on","0");

	associate_array->set_text("sound_volume",to_string((long long) this->settings.sound_volume));
	associate_array->set_text("last_level",to_string((long long) this->settings.last_level));
	associate_array->set_text("language",this->settings.language);

	associate_array->save_to_file("data");

	delete associate_array;
  }

//-----------------------------------------------

void c_game::update_settings_menu_items()
  {
	if (this->settings.fullscreen)
	  this->settings_menu_items_done[0] = this->settings_menu_items[0] + ": " + this->local_texts->get_text("option_on");
	else
      this->settings_menu_items_done[0] = this->settings_menu_items[0] + ": " + this->local_texts->get_text("option_off");

	if (this->settings.music_on)
	  this->settings_menu_items_done[1] = this->settings_menu_items[1] + ": " + this->local_texts->get_text("option_on");
	else
      this->settings_menu_items_done[1] = this->settings_menu_items[1] + ": " + this->local_texts->get_text("option_off");

	this->settings_menu_items_done[2] = this->settings_menu_items[2] + ": " + to_string((long long) this->settings.sound_volume);

	if (this->settings.language.compare("english") == 0)
	  this->settings_menu_items_done[3] = this->settings_menu_items[3] + ": EN";
	else
	  this->settings_menu_items_done[3] = this->settings_menu_items[3] + ": CZ";

	this->settings_menu_items_done[4] = this->settings_menu_items[4];
  }
 
//-----------------------------------------------

void c_game::run()
  { 
	string help_str;
	int menu_return_value;
	int i;
	bool quit_program;
	bool event_occured;
	ALLEGRO_EVENT program_event;
	ALLEGRO_TIMEOUT timeout;
	string help_string_array[2];
	ALLEGRO_KEYBOARD_STATE keyboard_state;
	char character;
	t_game_state game_state;
	
	this->menu = new c_menu(&this->input_output_state);

	this->menu_state = MENU_STATE_FIRST_SCREEN; 
	this->menu->set_menu_info_screen("resources/introduction.png",NULL,0,5.0,255,255,255); 

	al_start_timer(this->global_timer);

	al_init_timeout(&timeout, 0.05);

	quit_program = false;
	
	while (true)                   // main loop
	  {
		switch (this->menu_state)             // manage the menu state machine
		  {
		    case MENU_STATE_PLAYING:

			  game_state = map->update();

			  if (this->cheat_used)
			    {
				  game_state = GAME_STATE_WIN;
				  this->cheat_used = false;
			    }

			  switch (game_state)
			    {
				  case GAME_STATE_PLAYING:
				    break;

				  case GAME_STATE_LOSE:
					al_stop_samples();
					al_play_sample(this->lose_sound,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
					this->menu_state = MENU_STATE_LOST;
					help_string_array[0] = this->local_texts->get_text("lost");
					this->menu->set_menu_info_screen("",help_string_array,1,-1,240,0,0);

					this->initialise_new_game(this->current_level);
				    break;

				  case GAME_STATE_WIN:
					al_stop_samples();
					al_play_sample(this->win_sound,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);

                    if (this->current_level == 22) // last level - the game is won
					  {
						this->play_music("university of magic");
					    this->menu_state = MENU_STATE_OUTRO;
						this->menu->set_menu_info_screen("resources/characters.png",this->outro_lines,10,-1.0,255,255,255);
					  }
					else  
					  {
						if (this->current_level == this->settings.last_level) // unlock the next level
						  {
							this->settings.last_level++;
					        this->save();
						  }

						this->menu_state = MENU_STATE_LEVEL_CHOOSING;
						this->menu->set_menu_choose_level(this->settings.last_level);
					  }				
					
					break;

				  case GAME_STATE_PAUSE:
					al_stop_samples();        // stops the looping sounds
					this->menu_state = MENU_STATE_GAME_MENU;
					this->menu->set_menu_items(this->game_menu_items,3,this->game_menu_title,false);
				    break;
			    }

		      break;

			case MENU_STATE_LOST:
			  menu_return_value = this->menu->update();

			  if (menu_return_value >= 0)
			    {
				  this->menu_state = MENU_STATE_PLAYING;
				  this->play_music(this->map->get_music_name());
				  this->initialise_new_game(this->current_level);
			    }

			  break;

			case MENU_STATE_GAME_MENU:
			  menu_return_value = this->menu->update();

			  switch (menu_return_value)
			    {
			      case 0:   // resume
					this->menu_state = MENU_STATE_PLAYING;
					this->play_music(this->map->get_music_name());
					break;

				  case 1:   // restart the game
					this->initialise_new_game(this->current_level);
					this->play_music(this->map->get_music_name());
					help_string_array[0] = this->local_texts->get_text("level") + " " + to_string((long long) this->current_level);
				    help_string_array[1] = this->map->get_description();
					this->menu->set_menu_info_screen("",help_string_array,2,-1,255,255,255);
					this->menu_state = MENU_STATE_LEVEL_INTRO;
					break;

				  case 2:   // back to menu
					this->menu_state = MENU_STATE_MAIN_MENU;
					this->play_music("university of magic");
				    this->menu->set_menu_items(this->main_menu_items,5,this->main_menu_title,false);
					break;
			    }

			  break;

		    case MENU_STATE_FIRST_SCREEN:
			case MENU_STATE_ABOUT:
			case MENU_STATE_HOW_TO_PLAY:
              menu_return_value = this->menu->update();

			  if (menu_return_value > 0)
			    {
				  if (this->menu_state == MENU_STATE_FIRST_SCREEN)
                    this->play_music("university of magic");

				  this->menu_state = MENU_STATE_MAIN_MENU;
				  this->menu->set_menu_items(this->main_menu_items,5,this->main_menu_title,false);
			    }

			  break;

			case MENU_STATE_OUTRO:
			  menu_return_value = this->menu->update();

			  if (menu_return_value > 0)
			    {
				  this->menu_state = MENU_STATE_ABOUT;
				  this->menu->set_menu_info_screen("resources/characters.png",this->about_lines,3,-1.0,255,255,255);
			    }

			  break;

			case MENU_STATE_LEVEL_INTRO:
              menu_return_value = this->menu->update();

			  if (menu_return_value > 0)
				this->menu_state = MENU_STATE_PLAYING;
			  
			  break;

			case MENU_STATE_INTRO:
			  menu_return_value = this->menu->update();

			  if (menu_return_value >= 0)
			    {
				  this->menu_state = MENU_STATE_INTRO2;
				  this->menu->set_menu_info_screen("resources/characters.png",this->intro_lines_2,10,-1,255,255,255);
			    }

			  break;

			case MENU_STATE_INTRO2:
			  menu_return_value = this->menu->update();	

			  if (menu_return_value >= 0)
			    {
			  	  this->menu->set_menu_choose_level(this->settings.last_level);
				  this->menu_state = MENU_STATE_LEVEL_CHOOSING;
			    }

			  break;

			case MENU_STATE_LEVEL_CHOOSING:
			  menu_return_value = this->menu->update();
			  
			  if (menu_return_value < 0)
			    { 
				  // nothing chosen - do nothing
			    }
			  else if (menu_return_value == this->settings.last_level + 1) // back pressed
			    {
				  this->menu_state = MENU_STATE_MAIN_MENU;
				  this->menu->set_menu_items(this->main_menu_items,5,this->main_menu_title,false);				  
			    }
			  else if (menu_return_value == this->settings.last_level) // intro pressed
			    {
                  this->menu_state = MENU_STATE_INTRO;
				  this->menu->set_menu_info_screen("resources/characters.png",this->intro_lines_1,10,-1,255,255,255);				  
			    }
			  else  // a level was chosen
			    {
				  this->current_level = menu_return_value + 1;
				  this->initialise_new_game(this->current_level);
				  this->play_music(this->map->get_music_name());
				  help_string_array[0] = this->local_texts->get_text("level") + " " + to_string((long long) this->current_level);
				  help_string_array[1] = this->map->get_description();
				  this->menu->set_menu_info_screen("",help_string_array,2,-1,255,255,255);
				  this->menu_state = MENU_STATE_LEVEL_INTRO;
			    }

			  break;

			case MENU_STATE_MAIN_MENU:
			  menu_return_value = this->menu->update();

			  al_get_keyboard_state(&keyboard_state);

			  if (al_key_down(&keyboard_state,ALLEGRO_KEY_H) && al_key_down(&keyboard_state,ALLEGRO_KEY_I)) // easter egg when E and I pressed together
				this->menu->display_easter_egg();

			  switch (menu_return_value)
			    {
			      case 0: // new game
					if (this->settings.last_level == 0)
					  {
						this->settings.last_level = 1;        // set information that the intro has been played
						this->save();
						this->menu_state = MENU_STATE_INTRO;
						this->menu->set_menu_info_screen("resources/characters.png",this->intro_lines_1,10,-1,255,255,255);
					  }
					else
					  { 
						this->menu->set_menu_choose_level(this->settings.last_level);
						this->menu_state = MENU_STATE_LEVEL_CHOOSING;
					  }

					break;

				  case 1: // settings
					this->menu_state = MENU_STATE_SETTINGS_MENU;
					this->update_settings_menu_items();
					this->menu->set_menu_items(this->settings_menu_items_done,5,this->settings_menu_title,false);
					break;

				  case 2: // how to play
					this->menu_state = MENU_STATE_HOW_TO_PLAY;
					this->menu->set_menu_info_screen("",this->how_to_play_lines,10,-1.0,253,221,91);
                    break;

				  case 3: // about
					this->menu_state = MENU_STATE_ABOUT;
					this->menu->set_menu_info_screen("",this->about_lines,3,-1.0,253,221,91);
					break;

				  case 4: // exit
					quit_program = true;
					break;
			    }

			  break;

			case MENU_STATE_SETTINGS_MENU:

			  menu_return_value = this->menu->update();

			  switch (menu_return_value)
			    {
			      case 0: // fullscreen
					this->settings.fullscreen = !this->settings.fullscreen;
					this->update_settings_menu_items();
					this->menu->set_menu_items(this->settings_menu_items_done,5,this->settings_menu_title,true);
				    break;

				  case 1: // music on/off
					this->settings.music_on = !this->settings.music_on;				
                    this->play_music("university of magic");
					this->update_settings_menu_items();
					this->menu->set_menu_items(this->settings_menu_items_done,5,this->settings_menu_title,true);
					break;

				  case 2: // sound volume
					this->settings.sound_volume += 20;

					if (this->settings.sound_volume > 100)
					  this->settings.sound_volume = 0;
					
					this->update_volume();

					this->update_settings_menu_items();
					this->menu->set_menu_items(this->settings_menu_items_done,5,this->settings_menu_title,true);
					break;

				  case 3: // language
					if (this->settings.language.compare("english") == 0)
					  this->settings.language = "czech";
					else
					  this->settings.language = "english";

					this->set_language(this->settings.language);
					this->update_settings_menu_items();
					this->menu->set_menu_items(this->settings_menu_items_done,5,this->settings_menu_title,true);
					break;

				  case 4:
					this->menu_state = MENU_STATE_MAIN_MENU;
				    this->menu->set_menu_items(this->main_menu_items,5,this->main_menu_title,false);
					this->save();
					break;
			    }

			  break;
		  }

		al_flip_display();
		
		this->input_output_state.key_use = false;      // we only want to detect one key press

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
				if (program_event.keyboard.keycode == this->key_up)
				  this->input_output_state.key_up = true;
                else if (program_event.keyboard.keycode == this->key_down)
				  this->input_output_state.key_down = true;
                else if (program_event.keyboard.keycode == this->key_left)
				  this->input_output_state.key_left = true;
                else if (program_event.keyboard.keycode == this->key_right)
				  this->input_output_state.key_right = true;
                else if (program_event.keyboard.keycode == this->key_switch1)
				  this->input_output_state.key_1 = true;
			    else if (program_event.keyboard.keycode == this->key_switch2)
				  this->input_output_state.key_2 = true;
			    else if (program_event.keyboard.keycode == this->key_switch3)
				  this->input_output_state.key_3 = true; 
                else if (program_event.keyboard.keycode == this->key_cast1)
				  this->input_output_state.key_cast_1 = true;
				else if (program_event.keyboard.keycode == this->key_cast2)
				  this->input_output_state.key_cast_2 = true;
				else if (program_event.keyboard.keycode == this->key_cast3)
				  this->input_output_state.key_cast_3 = true;
				else if (program_event.keyboard.keycode == this->key_use ||
				  program_event.keyboard.keycode == this->key_use_alt)
				  this->input_output_state.key_use = true;
				else if (program_event.keyboard.keycode == this->key_map)
				  this->input_output_state.key_map_explore = true;
				else if (program_event.keyboard.keycode == this->key_back)
				  this->input_output_state.key_back = true;
				else if (!this->letter_pressed)       // possibly typing a cheatcode
				  {
					 switch (program_event.keyboard.keycode)
					   {
					     case ALLEGRO_KEY_I:
						   character = 'i';
						   this->letter_pressed = true;
						   break;

                         case ALLEGRO_KEY_A:
						   character = 'a';
						   this->letter_pressed = true;
						   break;

						 case ALLEGRO_KEY_M:
						   character = 'm';
						   this->letter_pressed = true;
						   break;

						 case ALLEGRO_KEY_N:
						   character = 'n';
						   this->letter_pressed = true;
						   break;

						 case ALLEGRO_KEY_O:
						   character = 'o';
						   this->letter_pressed = true;
						   break;

						 case ALLEGRO_KEY_B:
						   character = 'b';
						   this->letter_pressed = true;
						   break;

						 default:
                           character = '-';
						   break;
					   }

					 if (character != '-')
					   {
						 for (i = 0; i < 6; i++) // shift the buffer to the left
						   this->cheat_buffer[i] = this->cheat_buffer[i + 1];

						 this->cheat_buffer[6] = character;

						 if (this->cheat_buffer[0] == 'i' && this->cheat_buffer[1] == 'a' &&
						   this->cheat_buffer[2] == 'm' && this->cheat_buffer[3] == 'n' &&
						   this->cheat_buffer[4] == 'o' && this->cheat_buffer[5] == 'o' &&
						   this->cheat_buffer[6] == 'b')
						   {
						     if (this->menu_state == MENU_STATE_PLAYING)
						       this->cheat_used = true;
							 else
                               this->cheat_buffer[0] = '-';
						   }
					   }
				  }
				
				break;

			  case ALLEGRO_EVENT_KEY_UP:               // key up event
				if (program_event.keyboard.keycode == this->key_up)
				  this->input_output_state.key_up = false;
                else if (program_event.keyboard.keycode == this->key_down)
				  this->input_output_state.key_down = false;
                else if (program_event.keyboard.keycode == this->key_left)
				  this->input_output_state.key_left = false;
                else if (program_event.keyboard.keycode == this->key_right)
				  this->input_output_state.key_right = false;
                else if (program_event.keyboard.keycode == this->key_switch1)
				  this->input_output_state.key_1 = false;
			    else if (program_event.keyboard.keycode == this->key_switch2)
				  this->input_output_state.key_2 = false;
			    else if (program_event.keyboard.keycode == this->key_switch3)
				  this->input_output_state.key_3 = false; 
                else if (program_event.keyboard.keycode == this->key_cast1)
				  this->input_output_state.key_cast_1 = false;
				else if (program_event.keyboard.keycode == this->key_cast2)
				  this->input_output_state.key_cast_2 = false;
				else if (program_event.keyboard.keycode == this->key_cast3)
				  this->input_output_state.key_cast_3 = false;
				else if (program_event.keyboard.keycode == this->key_use ||
				  program_event.keyboard.keycode == this->key_use_alt)
				  this->input_output_state.key_use = false;
				else if (program_event.keyboard.keycode == this->key_map)
				  this->input_output_state.key_map_explore = false;
				else if (program_event.keyboard.keycode == this->key_back)
				  this->input_output_state.key_back = false;

				this->letter_pressed = false;

			    break;
		    }

		if (quit_program)
		  break; 
	  }
  }

//-----------------------------------------------

void c_game::play_music(string name)
  {
	al_stop_samples();

	if (this->settings.music_on)
	  {		
		al_destroy_sample(this->music);
		this->music = al_load_sample(("resources/" + name + ".ogg").c_str());
		al_play_sample(this->music,1.0,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,&this->music_id);
	  }
  }

//-----------------------------------------------

void c_game::stop_music()
  {
	if (this->settings.music_on)
	  {
		al_stop_sample(&this->music_id);
	  }
  }

//-----------------------------------------------