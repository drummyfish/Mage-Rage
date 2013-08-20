#ifndef MENU_H
#define MENU_H

/**
 * Menu class header file.
 *
 * authors: Miloslav Číž
 * year: 2013
 */

#include "general.h"

typedef enum
  {
	/**
	  Possible menu types.
	*/
	MENU_TYPE_NORMAL,        /** normal menu with items */
	MENU_TYPE_INFO,          /** info screen with text */
	MENU_TYPE_LEVEL_CHOOSE   /** level selection screen */
  } t_menu_type;

class c_menu
  {
	/**
	  This class is capable of displaying and
	  handling different kinds of menus and
	  dialogs for the player.
	*/

    protected:
	  t_menu_type menu_type;           // menu type
	  int current_item;                // currently highlighted menu item
	  int number_of_text_lines;        // number of text lines or items displayed on info screen    
	  string text_lines[10];           // text displayed on info screen or items displayed in the menu
	  int number_of_levels;            // number of available levels on the level selection screen
	  t_input_output_state *io;        // information about keys pressed etc.
	  boolean pressed;                 // to capture key down only once
	  double effect_time;              // this is used to display effects such as fade in etc.

	  ALLEGRO_BITMAP *menu_top;        // bitmap - top part of the menu
	  ALLEGRO_BITMAP *menu_middle;     // bitmap - middle part part of the menu 
	  ALLEGRO_BITMAP *menu_bottom;     // bitmap - bottom part of the menu
	  ALLEGRO_BITMAP *menu_selection;  // bitmap - highlight for menu items
	  ALLEGRO_BITMAP *info_background; // bitmap - info screen image

	  ALLEGRO_FONT *text_font;         // font to display the text

    public: 
	  c_menu(t_input_output_state *input_output_state);

	    /**
		  Class constructor, initialises a new
		  object.

		  @param input_output_state pointer to
		    input output state structure which
			stores info about keys pressed etc.
		*/

	  ~c_menu();

	    /**
		  Class destructor, frees all object's
		  memory.
		*/

	  void set_menu_items(string items[], int number_of_items);

	    /**
		  Sets the menu type to normal menu where
		  player can select from number of
		  choices and specifies those choices.

		  @param items menu items
		  @param number_of_items length of
		    items array
		*/

	  void set_menu_info_screen(string image_path, string text_lines[], int number_of_lines);

	    /**
		  Sets the menu type to info screen
		  which is a screen that displays
		  a text and an optional image. It
		  can be skipped by player with any
		  key.

		  @param image_path image to be
		    displayed, if zero length string
			is provided, no image displays
	      @param text_lines lines of text to
		    be displayed
		  @param number_of_lines length of
		    text_lines array, maximum is 10
		*/

	  void set_menu_choose_level(int number_of_levels);

	    /**
		  Sets the menu type to level choosing
		  screen.

		  @param number_of_levels number of
		    levels from which the player can
			choose, for example 3 lets the
			player choose levels 1, 2 or 3.
		*/

	  int update();

	    /**
		  Updates and draws another frame of the
		  menu and returns the choice the player
		  have made.

		  @return number of menu item selected
		    (counting from 0) or -1 if the
			player hasn't chosen anything yet
		*/
  };

#endif