﻿#ifndef GAME_H
#define GAME_H

/**
 * Game class header file.
 *
 * authors: Miloslav Číž
 * year: 2013
 */

#include "general.h"
#include "map.h"
#include "menu.h"

typedef struct
  {
	/**
	  Stores game settings.
	*/

	bool fullscreen;      /** whether the game is full screen or windowed */
	bool music_on;        /** whether the music is on or off */
	int sound_volume;     /** sound volume in range 0 - 100 */
	int last_level;       /** the last level the player reached */
	string language;      /** the game environment language */
  } t_game_settings;

typedef enum
  {
	/**
	  Possible game states.
	*/

	MENU_STATE_MAIN_MENU,
	MENU_STATE_GAME_MENU,
	MENU_STATE_SETTINGS_MENU,
	MENU_STATE_ABOUT,
	MENU_STATE_PLAYING,
	MENU_STATE_INTRO,
	MENU_STATE_INTRO2,
	MENU_STATE_OUTRO,
	MENU_STATE_FIRST_SCREEN,
	MENU_STATE_LEVEL_CHOOSING
  } t_menu_state;

class c_game
  {
    /**
	  This class holds and manipulates the data
	  of the whole game.
	*/

    protected:
	  c_map *map;                               /** handles the map */
	  c_menu *menu;                             /** handles menus and info screens */
	  ALLEGRO_DISPLAY *display;                 /** the game screen */
	  ALLEGRO_EVENT_QUEUE *event_queue;         /** event queue */
	  ALLEGRO_TIMER *global_timer;              /** global clock */
	  long int global_time;                     /** global time counter */
	  t_input_output_state input_output_state;  /** keyboard and mouse state */
	  ALLEGRO_BITMAP *cursor_bitmap;            /** mouse cursor bitmap */
	  ALLEGRO_MOUSE_CURSOR *cursor;             /** mouse cursor */
	  t_game_settings settings;                 /** game settings and the player's progress */
	  t_menu_state menu_state;                  /** stores the state of the menu system */
	  c_associative_array *local_texts;         /** stores game texts in local language */

	  int key_up;                               /** keycode for key up */
	  int key_down;                             /** keycode for key down */
	  int key_right;                            /** keycode for key right */
	  int key_left;                             /** keycode for key left */
	  int key_cast1;                            /** keycode for key cast spell 1 */
	  int key_cast2;                            /** keycode for key cast spell 2 */
	  int key_cast3;                            /** keycode for key cast spell 3 */
	  int key_switch1;                          /** keycode for key switch to player 1 */
	  int key_switch2;                          /** keycode for key switch to player 2 */
	  int key_switch3;                          /** keycode for key switch to player 3 */
	  int key_use;                              /** keycode for key used to use items and confirm things */
	  int key_back;                             /** keycode for key back */
	  int key_map;                              /** keycode for key that manipulates the camera */

	  string main_menu_items[4];                /** main menu items */
	  string main_menu_title;                   /** main menu title */
	  string settings_menu_items[5];            /** settings menu items */
	  string settings_menu_title;               /** settings menu title */
	  string settings_menu_items_done[5];       /** settings menu items with values added (on/off etc.) */
	  string about_lines[3];                    /** information about the program for the about screen */
      string intro_lines_1[10];                 /** intro text, page one */
	  string intro_lines_2[10];                 /** intro text, page two */

      void update_settings_menu_items();

	    /**
		  Updates the settings_menu_items_done
		  array so that it contains valid
		  items depending on current game
		  settings.
		*/

	  void set_language(string language);

	    /**
		  Sets the game texts to given
		  language.

		  @param language language name like
		    "english" or "czech" which will
			be loaded from the corresponding
			file in game resources
		*/

	  void set_keys();

	    /**
		  Loads the keyboard layout from file
		  and sets the classes variables for
		  the key codes.
		*/

    public:
	
	  c_game();
	  
	    /**
	      Class constructor, initialises new game
		  object.
	    */

	  ~c_game();

	    /**
	      Class destructor, frees the object's
		  memory.
	    */

	  void save();

	    /**
	      Saves the game settings (including
		  player's progress) in the configuration
		  file.
	    */

	  void load();

	    /**
	      Loads the game settings (including
		  player's progress) from the configuration
		  file.
	    */

	  void run();

	    /**
	      Runs the game and handles everything about
		  it.
	    */
  };

#endif