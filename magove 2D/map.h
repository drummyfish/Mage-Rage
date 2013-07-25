#ifndef MAP_H
#define MAP_H

/**
 * Map class header file.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
 */

#include "general.h"
#include "graphic_object.h"
#include "player_character.h"
#include "map_object.h"

typedef enum
  {
	SQUARE_NORMAL,
	SQUARE_WATER,
	SQUARE_ICE
  } t_square_type;

typedef struct
  {
	/**
      Holds info about one map square.
    */

	int height;                                         /** square height, min is 0, max is 2 */
	t_square_type type;                                 /** square type, like normal, water, ice and so on. */
	c_map_object *map_objects[MAX_OBJECTS_PER_SQUARE];  /** objects on this square (NULL means no object) */
  } t_map_square;

class c_map: c_graphic_object
  {
	/**
	  This class represents a game map. It is
	  able to draw it and manage playing it with
	  help of the game class.
	*/

    private:
	  int width;                                                       /** map width in squares */
	  int height;                                                      /** map height in squares */
	  int *button_positions_x;                                         /** an array containing x coordinations of all button objects on the map for faster browsing */
	  int *button_positions_y;                                         /** an array containing y coordinations of all buttons */
	  int number_of_buttons;                                           /** number of buttons on the map */
	  int current_player;                                              /** current player number */
	  t_environment environment;                                       /** map environment */
	  t_map_square squares[MAP_MAX_WIDTH][MAP_MAX_HEIGHT];             /** map squares */
	  c_player_character *player_characters[3];                        /** player characters, NULL means no character */            
	  t_input_state *input_state;                                      /** pointer to information about keyboard and mouse */
	  double time_before;                                              /** to compute time difference between frames (for movement etc.) */
	  double time_difference;                                          /** stores time between two frames to calculate step length etc. */

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

	  void move_character(c_character *character, t_direction direction, long int global_time);

	    /**
	      Updates character's movement in given
		  direction and handles colisions and
		  interaction with map objects.

		  @param character character to be moved
		  @param direction direction in which
		    the player is moving
		  @param global_time global time counter
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

	  void use_key_press(long int global_time);

	    /**
		  Handles use key press.

		  @param global_time global time counter
		*/

	  bool load_from_file(string filename);

	    /**
	      Loads the map from given file.

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

	  void set_environment(t_environment new_environment);

	    /**
		  Sets the map environment, which affects
		  it's tileset (it's look). This should
		  only be called once for the object
		  because the method doesn't free any
		  previously allocated memory.

		  @param new_environment new environment to
		    be set
		*/

	  int get_height(int x, int y);
	    
	    /**
		  Returns map height at given position. If
		  the position is outside the map, 0 is
		  returned.

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

	  bool crate_can_be_shifted(int x, int y, t_direction direction);

	    /**
		  Checks if a crate at given square can
		  be shifted in given direction. It is
		  assumed that the square given really
		  holds a crate object.

		  @param x x coordination of the square
		  @param y y coordination of the square
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

	  void update_map_object_states(long int global_time);
	    
	    /**
		  Updates object states depending on
		  links between them.

		  @param global_time global time counter
		*/

	  void link_objects();

	    /**
		  Establishes pointer connections between
		  map objects depending on their link
		  ids.
		*/

	  void check_buttons(long int global_time);

	    /**
		  Tests all the button objects on the
		  map and performs appropriate actions.

		  @param global_time global time counter
		*/

    public:

      c_map(string filename, t_input_state *input_state);

	    /** 
	      Class constructor, loads new map from
		  given file.

		  @param filename path to the map file
		  @param input_state pointer to structure,
		    which will be used to pass information
			about keyboard and mouse to this object.
	    */

	  ~c_map();
	    
	    /**
		  Class destructor, frees all it's memory.
		*/

	  void update(long int global_time);

	    /**
		  Updates the map, which means it handles
		  it's another frame, including drawing
		  it and handling events.

		  @param global_time global time counter
		    which is needed for animations etc.
		*/

	  virtual void draw(int x, int y, long int global_time);

	    /**
		  Draws the map at given position on the
		  screen.

		  @param x x position of the screen
		  @param y y position of the screen
		  @param global_time global time counter
		    which is needed for animations etc.
		*/
  };

#endif