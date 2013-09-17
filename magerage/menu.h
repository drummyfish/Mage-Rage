#ifndef MENU_H
#define MENU_H

/**
 * Menu class header file.
 *
 * Copyright 2013 Miloslav Číž
 *
 * This file is part of Mage Rage.
 *
 * Mage Rage is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Mage Rage is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar. If not, see <http://www.gnu.org/licenses/>.
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
	  t_menu_type menu_type;            /** menu type */
	  int current_item;                 /** currently highlighted menu item */
	  int number_of_text_lines;         /** number of text lines or items displayed on info screen */  
	  string text_lines[10];            /** text displayed on info screen or items displayed in the menu */
	  int number_of_levels;             /** number of available levels on the level selection screen */
	  t_input_output_state *io;         /** information about keys pressed etc. */
	  boolean pressed;                  /** to capture key down only once */
	  double effect_time;               /** this is used to display effects such as fade in etc. */
	  double screen_end_time;           /** time when the info screen will disappear */
	  bool fading_in;                   /** whether the fade in effect is active */               
	  bool fading_out;                  /** whether the fade out effect is active */
	  string title;                     /** menu title */
	  unsigned char bg_color[3];        /** background color for the info screen */
	  double easter_egg_started;        /** easter egg start time */

	  int level_number_positions_x[22]; /** x poxel positions of level numbers at level choosing screen */
	  int level_number_positions_y[22]; /** same as above but with y coordinations */

	  ALLEGRO_BITMAP *menu_top;         /** bitmap - top part of the menu */
	  ALLEGRO_BITMAP *menu_middle;      /** bitmap - middle part part of the menu */
	  ALLEGRO_BITMAP *menu_bottom;      /** bitmap - bottom part of the menu */
	  ALLEGRO_BITMAP *menu_selection;   /** bitmap - highlight for menu items */
	  ALLEGRO_BITMAP *info_background;  /** bitmap - info screen image */
	  ALLEGRO_BITMAP *menu_border;      /** bitmap - menu decorative border */
	  ALLEGRO_BITMAP *easter_egg;       /** bitmap - easter egg */

	  ALLEGRO_FONT *text_font;          /** font to display the text */

	  ALLEGRO_SAMPLE *click_sound;      /** click sound for the menu */

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

	  void set_menu_items(string items[], int number_of_items, string title, bool keep_cursor);

	    /**
		  Sets the menu type to normal menu where
		  player can select from number of
		  choices and specifies those choices.

		  @param items menu items
		  @param number_of_items length of
		    items array
		  @param title title of the menu
		  @param keep_cursor if true, the menu
		    highlight cursor will stay on its
			position, otherwise it will move
			to the first item
		*/

	  void display_easter_egg();

	    /**
		  Displays the easter egg for a little
		  while no matter what menu type is
		  set.
		*/

	  void set_menu_info_screen(string image_path, string text_lines[], int number_of_lines, double duration, unsigned char bg_red, unsigned char bg_green, unsigned char bg_blue);

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
		  @param duration if negative, the 
		    screen will be waiting for the
			user to press a key to disappear,
			othervise this value is a
			number of seconds in which
			the screen will disappear on
			it's own
		  @param bg_red amount of red for the
		    background color
		  @param bg_green amount of green for
		    the background color
		  @param bg_blue amount of blue for
		    the background color
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