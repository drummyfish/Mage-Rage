#ifndef MAP
#define MAP

/**
 * Map class header file.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
 */

#include "general.h"
#include "graphic_object.h"

#define MAP_MAX_WIDTH 30            // maximum map width in squares
#define MAP_MAX_HEIGHT 30           // maximum map height in squares

class c_map: c_graphic_object
  {
	/**
	  This class represents a game map. It is
	  able to draw and manage it.
	*/

    private:
	  int width;                                           /** map width in squares */
	  int height;                                          /** map height in squares */
	  t_environment environment;                           /** map environment */
	  t_map_square squares[MAP_MAX_WIDTH][MAP_MAX_HEIGHT]; /** map squares */

	  ALLEGRO_BITMAP  *tile;                               /** bitmap - normal tile */
	  ALLEGRO_BITMAP  *tile_cliff_south_1;                 /** bitmap - south cliff, height 1 */
	  ALLEGRO_BITMAP  *tile_cliff_south_2;                 /** bitmap - south cliff, height 2 */
	  ALLEGRO_BITMAP  *tile_cliff_southwest_1;             /** bitmap - southwest cliff, height 1 */
	  ALLEGRO_BITMAP  *tile_cliff_southwest_2;             /** bitmap - southwest cliff, height 2 */
	  ALLEGRO_BITMAP  *tile_cliff_southeast_1;             /** bitmap - southeast cliff, height 1 */
	  ALLEGRO_BITMAP  *tile_cliff_southeast_2;             /** bitmap - southeast cliff, height 2 */
	  ALLEGRO_BITMAP  *tile_cliff_west;                    /** bitmap - west cliff (any height) */
	  ALLEGRO_BITMAP  *tile_cliff_east;                    /** bitmap - east cliff (any height) */
	  ALLEGRO_BITMAP  *tile_cliff_north;                   /** bitmap - north cliff (any height) */
	  ALLEGRO_BITMAP  *tile_cliff_northwest;               /** bitmap - northwest cliff (any height) */
	  ALLEGRO_BITMAP  *tile_cliff_northeast;               /** bitmap - northeast cliff (any height) */

    public:

      c_map();

	    /** 
	      Class constructor, initialises new map
	  	  object.
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

	  virtual void c_map::draw(int x, int y);

	    /**
		  Draws the map at given position on the
		  screen.

		  @param x x position of the screen
		  @param y y position of the screen
		*/
  };

#endif