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

	int height;               /** square height, min is 0, max is 2 */
	t_square_type type;       /** square type, like normal, water, ice and so on. */
	c_map_object *map_object; /** object on this square (NULL means no object) */
  } t_map_square;

class c_map: c_graphic_object
  {
	/**
	  This class represents a game map. It is
	  able to draw it and manage playing it with
	  help of the game class.
	*/

    private:
	  int width;                                           /** map width in squares */
	  int height;                                          /** map height in squares */
	  int current_player;                                  /** current player number */
	  t_environment environment;                           /** map environment */
	  t_map_square squares[MAP_MAX_WIDTH][MAP_MAX_HEIGHT]; /** map squares */
	  c_player_character *player_characters[3];            /** player characters, NULL means no character */            
	  t_input_state *input_state;                          /** pointer to information about keyboard and mouse */
	  double time_before;                                  /** to compute time difference between frames (for movement etc.) */
	  double time_difference;                              /** stores time between two frames to calculate step length etc. */

	  ALLEGRO_BITMAP *portrait_selection;                  /** bitmap - GUI selection behind the portrait */ 

	  ALLEGRO_BITMAP *portrait_mia;                        /** bitmap - GUI portrait of Mia */
	  ALLEGRO_BITMAP *portrait_metodej;                    /** bitmap - GUI portrait of Metodej */
	  ALLEGRO_BITMAP *portrait_starovous;                  /** bitmap - GUI portrait of Starovous */

	  ALLEGRO_BITMAP *object_crate;                        /** bitmap - crate */

	  ALLEGRO_BITMAP *tile;                                /** bitmap - normal tile */
	  ALLEGRO_BITMAP *tile_cliff_south_1;                  /** bitmap - south cliff, height 1 */
	  ALLEGRO_BITMAP *tile_cliff_south_2;                  /** bitmap - south cliff, height 2 */
	  ALLEGRO_BITMAP *tile_cliff_southwest_1;              /** bitmap - southwest cliff, height 1 */
	  ALLEGRO_BITMAP *tile_cliff_southwest_2;              /** bitmap - southwest cliff, height 2 */
	  ALLEGRO_BITMAP *tile_cliff_southeast_1;              /** bitmap - southeast cliff, height 1 */
	  ALLEGRO_BITMAP *tile_cliff_southeast_2;              /** bitmap - southeast cliff, height 2 */
	  ALLEGRO_BITMAP *tile_cliff_west;                     /** bitmap - west cliff (any height) */
	  ALLEGRO_BITMAP *tile_cliff_east;                     /** bitmap - east cliff (any height) */
	  ALLEGRO_BITMAP *tile_cliff_north;                    /** bitmap - north cliff (any height) */
	  ALLEGRO_BITMAP *tile_cliff_northwest;                /** bitmap - northwest cliff (any height) */
	  ALLEGRO_BITMAP *tile_cliff_northeast;                /** bitmap - northeast cliff (any height) */
	  ALLEGRO_BITMAP *tile_edge;                           /** bitmap - used as south border with other surface */
	  ALLEGRO_BITMAP *tile_water[5];                       /** bitmap - water, 5 animation frames */

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

    public:

      c_map(t_input_state *input_state);

	    /** 
	      Class constructor, initialises new map
	  	  object.

		  @param input_state pointer to structure,
		    which will be used to pass information
			about keyboard and mouse to this object.
	    */

	  ~c_map();
	    
	    /**
		  Class destructor, frees all it's memory.
		*/

	  void set_environment(t_environment new_environment);

	    /**
		  Changes the maps environment, which
		  affects it's tileset (it's look).

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

	  t_square_type get_square_type(int x, int y);
	    
	    /**
		  Returns type of square at given position
		  of the map. If the position is outside
		  the map, SQUARE_NORMAL is returned.

		  @param x x position
		  @param y y position
		  @return square type at given position
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