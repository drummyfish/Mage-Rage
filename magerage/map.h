﻿#ifndef MAP_H
#define MAP_H

/**
 * Map class header file.
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
#include "graphic_object.h"
#include "player_character.h"
#include "monster_character.h"
#include "map_object.h"
#include "character.h"
#include "animation.h"
#include "associative_array.h"

typedef enum
  {
	SQUARE_NORMAL,
	SQUARE_WATER,
	SQUARE_ICE,
	SQUARE_COLLAPSE,
	SQUARE_HOLE
  } t_square_type;

typedef struct
  {
	/**
      Holds info about one map square.
    */

	int height;                                         /** square height, min is 0, max is 2 */
	t_square_type type;                                 /** square type, like normal, water, ice and so on. */
	c_map_object *map_objects[MAX_OBJECTS_PER_SQUARE];  /** objects on this square (NULL means no object) */
    c_animation *animation;                             /** animation being played on this square */
  } t_map_square;

typedef struct
  {
	/**
	  Represents a magical missile.
	*/

	t_missile_type type;                                /** missile type */
	t_direction direction;                              /** direction in which the missile is going */
	double position_x;                                  /** current x position */
	double position_y;                                  /** current y position */
	int square_y;                                       /** y square position */
	int square_x;                                       /** x square position */
	int height;                                         /** height level */
	ALLEGRO_BITMAP *bitmap;                             /** pointer to missile's bitmap */
  } t_missile;

class c_map: public c_graphic_object
  {
	/**
	  This class represents a game map. It is
	  able to draw it and manage playing it with
	  help of the game class.
	*/

    protected:
	  int width;                                                       /** map width in squares */
	  int height;                                                      /** map height in squares */
	  int *button_positions_x;                                         /** an array containing x coordinations of all button objects on the map for faster browsing */
	  int *button_positions_y;                                         /** an array containing y coordinations of all buttons */
	  int number_of_buttons;                                           /** number of buttons on the map */
	  int current_player;                                              /** current player number */
	  int screen_center_x;                                             /** center point of the screen (x) */
	  int screen_center_y;                                             /** center point of the screen (y) */
	  t_environment environment;                                       /** map environment */
	  t_map_square squares[MAP_MAX_WIDTH][MAP_MAX_HEIGHT];             /** map squares */
	  c_player_character *player_characters[3];                        /** player characters, NULL means no character */            
	  c_monster_character *monster_characters[MAX_MONSTERS_ON_MAP];    /** monster characters, NULL means no character */
	  int number_of_monsters;                                          /** number of monsters on the map */
	  t_input_output_state *input_output_state;                        /** pointer to information about keyboard and mouse */
	  double time_before;                                              /** to compute time difference between frames (for movement etc.) */
	  double time_difference;                                          /** stores time between two frames to calculate step length etc. */
	  int portrait_x_positions[3];                                     /** a helper array containing portrait x positions so they don't have to be counted each frame */
	  int portrait_y_position;                                         /** y position of portraits in pixels */
	  bool pressed_1;                                                  /** to handle events only once per keypressed, not each frame */
	  bool pressed_2;
	  bool pressed_3;
	  bool mouse_pressed;
	  bool check_firecloak;                                            /** says if fire cloak spell time should be being checked */
	  double fire_cloak_end_time;                                      /** stores the end time for the fire cloak spell */
	  int language;                                                    /** number of language, it must be know in order to set right sign texts etc. */
	  int textbox_size[2];                                             /** width and height of the textbox for displayed message */
	  string description;                                              /** map text description displayed during the intro */
	  bool oren_destroyed;                                             /** keeps information about whether the oren was destroyed */
	  double change_flame_state;                                       /** time when to change flames states (from active to non active and vice versa) */
	  string music_name;                                               /** name of the music that should be playing in the map */

	  char text_lines[MAX_TEXT_LINES][MAX_TEXT_CHARACTERS_PER_LINE];   /** lines of text being displayed on screen */
	  bool text_is_displayed;                                          /** whether the text is to be displayed */
	  double text_end_time;                                            /** time when the text will stop being displayed */

	  bool flames_on;                                                  /** turns on or off bursting flames of flame objects switched on */
	  int frame_count;                                                 /** counts frames */

	  t_missile missiles[MAX_MISSILES_ON_MAP];                         /** array of missiles that are currently at the map */
	  int number_of_missiles;                                          /** length of the missiles array */

	  int screen_square_resolution[2];                                 /** depending on screen resolution, this will contain screen resolution in game squares */
	  int screen_square_position[2];                                   /** position of the upper left screen corner aat the game map */
	  int screen_pixel_position[2];                                    /** screen square position converted to pixels */
	  int screen_square_end[2];                                        /** position of the lower right corner of the screen in game squares */

	  c_animation *animation_water_splash;                             /** animation for water splash */
	  c_animation *animation_refresh;                                  /** animation for refresh */
	  c_animation *animation_crate_shift_north;                        /** animation of crate shifting north (other directions are done animating the crate itself) */
	  c_animation *animation_collapse;                                 /** animation for collapsing square */
	  c_animation *animation_melt;                                     /** animation of melting ice */
	  c_animation *animation_teleport;                                 /** teleport animation */
	  c_animation *animation_explosion;                                /** explosion animation */
	  c_animation *animation_shadow_explosion;                         /** shadow explosion animation */

	  ALLEGRO_BITMAP *portrait_selection;                              /** bitmap - GUI selection behind the portrait */ 
	  ALLEGRO_BITMAP *portrait_mia;                                    /** bitmap - GUI portrait of Mia */
	  ALLEGRO_BITMAP *portrait_metodej;                                /** bitmap - GUI portrait of Metodej */
	  ALLEGRO_BITMAP *portrait_starovous;                              /** bitmap - GUI portrait of Starovous */
	  ALLEGRO_BITMAP *tile;                                            /** bitmap - normal tile */
	  ALLEGRO_BITMAP *tile_cliff_south_1;                              /** bitmap - south cliff, height 1 */
	  ALLEGRO_BITMAP *tile_cliff_south_2;                              /** bitmap - south cliff, height 2 */
	  ALLEGRO_BITMAP *tile_cliff_southwest_1;                          /** bitmap - southwest cliff, height 1 */
	  ALLEGRO_BITMAP *tile_cliff_southwest_2;                          /** bitmap - southwest cliff, height 2 */
	  ALLEGRO_BITMAP *tile_cliff_southeast_1;                          /** bitmap - southeast cliff, height 1 */
	  ALLEGRO_BITMAP *tile_cliff_southeast_2;                          /** bitmap - southeast cliff, height 2 */
	  ALLEGRO_BITMAP *tile_cliff_west;                                 /** bitmap - west cliff (any height) */
	  ALLEGRO_BITMAP *tile_cliff_east;                                 /** bitmap - east cliff (any height) */
	  ALLEGRO_BITMAP *tile_cliff_north;                                /** bitmap - north cliff (any height) */
	  ALLEGRO_BITMAP *tile_cliff_northwest;                            /** bitmap - northwest cliff (any height) */
	  ALLEGRO_BITMAP *tile_cliff_northeast;                            /** bitmap - northeast cliff (any height) */
	  ALLEGRO_BITMAP *tile_edge;                                       /** bitmap - used as south border with other surface */
	  ALLEGRO_BITMAP *tile_water[5];                                   /** bitmap - water, 5 animation frames */
	  ALLEGRO_BITMAP *tile_ice;                                        /** bitmap - ice */
	  ALLEGRO_BITMAP *tile_collapse;                                   /** bitmap - collapse square */
	  ALLEGRO_BITMAP *tile_hole;                                       /** bitmap - hole square */
	  ALLEGRO_BITMAP *bitmap_crate_water;                              /** bitmap - crate in water */
	  ALLEGRO_BITMAP *spell_mia_1[3];                                  /** bitmap - Mia's first spell missile */
	  ALLEGRO_BITMAP *spell_mia_2[3];                                  /** bitmap - Mia's second spell missile */
	  ALLEGRO_BITMAP *spell_metodej_1[3];                              /** bitmap - Metodej's first spell missile */
	  ALLEGRO_BITMAP *spell_starovous_1[3];                            /** bitmap - Starovous' first spell missile */
	  ALLEGRO_BITMAP *spell_starovous_2[3];                            /** bitmap - Starovous' second spell missile */
	  ALLEGRO_BITMAP *spell_icons[7];                                  /** bitmaps - spell icons */

	  ALLEGRO_BITMAP *map_shadow_north;                                /** bitmap - map transition to dark background on north edge */
	  ALLEGRO_BITMAP *map_shadow_south;                                /** bitmap - map transition to dark background on south edge */
	  ALLEGRO_BITMAP *map_shadow_east;                                 /** bitmap - map transition to dark background on east edge */
	  ALLEGRO_BITMAP *map_shadow_west;                                 /** bitmap - map transition to dark background on west edge */

	  ALLEGRO_SAMPLE *spell_sounds_mia[2];                             /** Mia's cast sounds */
	  ALLEGRO_SAMPLE *spell_sounds_metodej[2];                         /** Metodej's cast sounds */
	  ALLEGRO_SAMPLE *spell_sounds_starovous[2];                       /** Starovous' cast sounds */
	  ALLEGRO_SAMPLE *change_player_sound;                             /** sound played when player is changed */

	  ALLEGRO_FONT *text_font;                                         /** font for displaying texts */

	  void static next_square(int x, int y, t_direction direction, int *next_x, int *next_y);

	    /**
		  Computes the next square coordination
		  depending on a position and direction.

		  @param x x coordination of the square
		  @param y y coordination of the square
		  @param direction direction of the next
		    square
		  @param next_x in this variable will be
		    the x coordination of the next square
			returned
		  @param next_y in this variable will be
		    the y coordination of the next square
			returned
		*/

	  static string get_nth_substring(string from_what, int n);

	    /**
		  Returns nth substring from string in
		  format "part1|part2|..." If for example
		  n equals 0, then "part1" is returned.

		  @param from_what string to be parsed
		  @param n number of substring to return
		  @return nth substring of from_what
		    string, without the '|' separators
		*/

	  void move_character(c_character *character, t_direction direction);

	    /**
	      Updates character's movement in given
		  direction and handles colisions and
		  interaction with map objects.

		  @param character character to be moved
		  @param direction direction in which
		    the player is moving
		*/

	  void add_map_object(c_map_object *map_object, int x, int y);

	    /**
	      Places an object on the map square.
		  The map must be loaded.

		  @param map_object map object to be
		    put onto map
		  @param x x coordination of the square
		  @param y y coordination of the square
		*/

	  void use_key_press();

	    /**
		  Handles use key press.
		*/

	  void cast_key_press(int spell_number);

	    /**
	      Handles cast keys press.

		  @param spell_number number of spell
		    cast (0, 1 or 2)
		*/

	  bool load_from_file(string filename);

	    /**
	      Loads the map from given file. Also
		  loads all other things from files
		  like fonts, sounds etc.

		  @param filename path to the file
		  @return true if the map was loaded
		    succesfully, otherwise false
		*/

	  bool character_can_move_to_square(c_character *character, t_direction direction);

	    /**
		  Checks if given character can move to
		  the next square in given direction.

		  @param character character to be
		    checked
		  @param direction direction of the next
		    square relative to character's
			current square
		  @return true if the character can
		    move to the next square in that
			direction, otherwise false
		*/

	  bool square_has_object(int x, int y, t_object_type object_type);

	    /**
	      Checks if there is object of given
		  type at given square.

		  @param x x coordination of the square
		  @param y y coordination of the square
		  @param object_type type of object to
		    check
          @return true if there is object of
		    given type on given square,
			otherwise false
		*/

	  bool square_is_stepable(int x, int y);

	    /**
	      Checks whether given position can
		  be moved to by a character.

		  @param x x coordination of the square
		  @param y y coordination of the square
		  @return true if the square at given
		    position is stepable, otherwise
			false, for coordinations outside
			the map false is returned
		*/

	  int get_elevation_for_character(c_character *character);

	    /**
	      Gets elevation in pixels for given
		  character depending on their position
		  on the map, objects they're standing on
		  etc.

		  @param character character to be
		    checked
		  @return height offset in pixels
		*/

	  bool set_environment(t_environment new_environment);

	    /**
		  Sets the map environment, which affects
		  it's tileset (it's look). This should
		  only be called once for the object
		  because the method doesn't free any
		  previously allocated memory.

		  @param new_environment new environment to
		    be set
		  @return true, if the environment was
		    succesfully set, otherwise false
		*/

	  int get_height(int x, int y);
	    
	    /**
		  Returns map height at given position. If
		  the position is outside the map, 0 is
		  returned. The height is calculated as
		  terrain height + height of objects
		  (crates, elevators etc.).

		  @param x x position
		  @param y y position
		  @return map height at given position
		    including object heights
		*/

	  int get_terrain_height(int x, int y);

	  	/**
		  Returns map height at given position. If
		  the position is outside the map, 0 is
		  returned. Only the height of the terrain
		  is returned.

		  @param x x position
		  @param y y position
		  @return map height at given position
		*/

	  void shift_crate(int x, int y, t_direction direction);

		/**
		  Shift a crate at given square in given
		  direction. It must be checked that it is
		  possible to shift the crate.

		  @param x x coordination of the square
		  @param y y coordination of the square
		  @param direction direction in which to
		    shift the crate
		*/

	  bool crate_can_be_shifted(int x, int y, int height, t_direction direction);

	    /**
		  Checks if a crate at given square can
		  be shifted in given direction. It is
		  assumed that the square given really
		  holds a crate object.

		  @param x x coordination of the square
		  @param y y coordination of the square
		  @param height height from which the
		    crate is being pushed
		  @param direction direction in which
		    the crate is to be shifted
		  @return true if the crate can be
		    shifted, otherwise false
		*/

	  t_square_type get_square_type(int x, int y);
	    
	    /**
		  Returns type of square at given position
		  of the map. If the position is outside
		  the map, SQUARE_NORMAL is returned.

		  @param x x position
		  @param y y position
		  @return square type at given position
		*/

	  void set_square_type(int x, int y, t_square_type type);
	    
	    /**
		  Sets the square type. If the
		  coordinations are outside the map,
		  nothing happens.

		  @param x x position
		  @param y y position
		  @param type square typ to be set
		*/

	  void update_map_object_states();
	    
	    /**
		  Updates object states depending on
		  links between them.
		*/

	  void remove_object(int x, int y, int index);

	    /**
		  Removes nth object from given square
		  and shifts all remaining to the left
		  so the object array stays consistent.
		  The object's memory is not freed.

		  @param x x coordination of the square
		  @param y y coordination of the square
		  @param n index of the object to be
		    removed
		*/

	  void link_objects();

	    /**
		  Establishes pointer connections between
		  map objects depending on their link
		  ids.
		*/

	  void check_buttons();

	    /**
		  Tests all the button objects on the
		  map and performs appropriate actions.
		*/

	  void draw_borders(int x, int y, int plus_x, int plus_y);

	    /**
		  Draws borders for given square
		  depending on neighbour squares (for
		  example if there is water-grass,
		  there must be a border drawn between
		  them). This can't be used for cliffs.

		  @param x x coordination of the square
		  @param y y coordination of the square
		  @param plus_x x offset in pixels
		  @param plus_y y offset in pixels
		*/

	  bool must_have_border(t_square_type type1, t_square_type type2);

	    /**
		  Checks if two given square types
		  must have border drawn between them.
		  
		  @param type1 type of the first square
		  @param type2 type of the seconf square
		  @return true if the border should be
		    drawn, otherwise false
		*/

	  bool square_has_character(int x, int y);

	    /**
		  Checks if there is a character on
		  given square.

		  @param x x coordination of the square
		  @param y y coordination of the square
		  @return true if there is at least
		    one character on the square,
			otherwise false
		*/

	  void display_animation(t_display_animation animation, int x, int y);

	    /**
	      Displays animation on the map square.

		  @param animation the animation to be
		    displayed
		  @param x x coordination of the square
		  @param y y coordination of the square
		*/

	  void update_screen_position();

	    /**
		  Updates the screen position depending
		  on current player's position on
		  the map and the screen resolution.
		*/

	  void fire_missile(int spell_number);

	    /**
		  Creates a spell missile depending on
		  player type selected and given
		  spell number.

		  @param spell_number number of spell
		    cast (0 or 1)
		*/

	  void update_missiles();
	   
	    /**
		  This should be called every update
		  frame to update missile movement and
		  events associated with them.
		*/

	  void switch_player(int player_number);

	    /**
		  Sqitches active player.

		  @param player_number number of
		    player to be made active, if the
			player is not available on the map,
			nothing happens
		*/

	  void update_flames();

		/**
		  Switches all flames that are set on to
		  opposite state (i.e. bursting flames or
		  not). Flames set to off are not affected
		  by this.
		*/

	  bool object_can_be_used(c_map_object *what);

	    /**
	      Checks if given object can be used
		  (i.e. nothing prevents using it, like
		  player standing in a door etc.)

		  @param what object to be tested
		  @return true if the object can be used,
		    false otherwise
		*/

	  void get_object_position(c_map_object *what, int *x, int *y);

	    /**
		  Returns object's position on the
		  map.

		  @param what object of which the
		    position will be found out
		  @param x in this variable the
		    x coordination will be returned
		  @param y in this variable the
		    y coordination will be returned
		*/

	  void display_text(string text, double duration);

	    /**
		  Displays given text on the screen
		  for given time.

		  @param text text to be displayed
		  @param duration duration in seconds
		*/

	  void check_teleport();

	    /**
		  Checks if the current player is
		  standing on a teleport and if so,
		  teleports him in matching output
		  teleport.
		*/

	  bool door_can_be_passed(int x, int y, t_direction direction);

	    /**
	      Checks if a door at given position
		  can be passed in given direction.
		  If there is no door at the square,
		  true is returned.

		  @param x x coordination of the square
		  @param y y coordination of the square
		  @param direction direction to be
		    tested
		  @return true if the door at given
		    square can be passed in given
			direction
		*/

	  void update_monsters();

	    /**
		  Updates all monsters on the map (their
		  positions etc.)
		*/

	  void shift_screen(int x, int y);

	    /**
		  Shifts the screen by given values.
		  Checks borders and doesn't allow the
		  screen to be shifted too far.

		  @param x possibly negative x
		    offset in pixels
		  @param y possibly negative y
		    offset in pixels
		*/

	  void check_ice();

	    /**
		  Checks all player characters if they
		  are on ice and moving and keeps them
		  in movement.
		*/

	  void set_map_objects(string object_string);

	    /**
		  Accoording to given special object
		  string sets the objects specified by
		  it at the map.

		  @param object_string string describing
		    objects to be put on the map, for
			the string format see the
			documentation
		*/

	  void set_monsters(string monster_string);

	    /**
		  Accoording to given special monster
		  string sets the monsters specified by
		  it at the map.

		  @param monster_string string describing
		    monsters to be put on the map, for
			the string format see the
			documentation		  
		*/

	  void record_buttons();

	    /**
		  Records all buttons on the map into
		  special data structure so that the
		  checking of them will be faster. This
		  must be called in order for buttons
		  to work.
		*/

	  t_game_state check_game_state();

	    /**
		  Checks the game state. That means
		  if nothing happens or if the
		  player lost because he's
		  encountered a monster etc.

		  @return current game state
		*/

    public:

      c_map(string filename, t_input_output_state *input_output_state, long int *global_time, int language);

	    /** 
	      Class constructor, loads new map from
		  given file.

		  @param filename path to the map file
		  @param input_output_state pointer to
		    structure, which will be used to pass
			information about keyboard and mouse
			to this object.
		  @param global_time reference to a
		    global time counter variable which is
			needed for animations
		  @param language language number, 0 =
		    english, 1 = czech
	    */

	  ~c_map();
	    
	    /**
		  Class destructor, frees all it's memory.
		*/

	  t_game_state update();

	    /**
		  Updates the map, which means it handles
		  it's another frame, including drawing
		  it and handling events.

		  @return current game state (i.e
		    playing, lost, ...)
		*/

	  virtual void draw(int x, int y);

	    /**
		  Draws the map at given position on the
		  screen.

		  @param x x position of the screen
		  @param y y position of the screen
		*/

	  string get_description();

	    /**
		  Returns the map text description.

		  @return the text description
		*/

	  string get_music_name();

	    /**
		  Gets the name of the music that should
		  be playing in the map.

		  @return music name
		*/
  };

#endif