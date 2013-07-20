#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

/**
 * Player character class header file.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
 */

#include "character.h"

class c_player_character: public c_character
  {
	/**
	  Represents a player character.
	*/

    private:
	  t_player_type player_type;

	  ALLEGRO_BITMAP *shadow;                        /** shadow bitmap */
	  ALLEGRO_BITMAP *sprite_north;                  /** player facing north */
	  ALLEGRO_BITMAP *sprite_north_casting;          /** player casting north */
	  ALLEGRO_BITMAP *sprite_north_running_1;        /** player running north, frame 1 */
	  ALLEGRO_BITMAP *sprite_north_running_2;        /** player running north, frame 2 */
	  ALLEGRO_BITMAP *sprite_east;                   /** player facing east */
	  ALLEGRO_BITMAP *sprite_east_casting;           /** player casting east */
	  ALLEGRO_BITMAP *sprite_east_running_1;         /** player running east, frame 1 */
	  ALLEGRO_BITMAP *sprite_east_running_2;         /** player running east, frame 2 */
	  ALLEGRO_BITMAP *sprite_south;                  /** player facing south */
	  ALLEGRO_BITMAP *sprite_south_casting;          /** player casting south */
	  ALLEGRO_BITMAP *sprite_south_running_1;        /** player running south. frame 1 */
	  ALLEGRO_BITMAP *sprite_south_running_2;        /** player running south, frame 2 */
	  ALLEGRO_BITMAP *sprite_west;                   /** player facing west */
	  ALLEGRO_BITMAP *sprite_west_casting;           /** player casting west */
	  ALLEGRO_BITMAP *sprite_west_running_1;         /** player running west, frame 1 */
	  ALLEGRO_BITMAP *sprite_west_running_2;         /** player running west, frame 2 */

    public:
	  c_player_character(t_player_type player_type);

	  /**
	    Class constructor, initialises new player
		character.

		@param player_type type of player character
	  */

	  ~c_player_character();

	  /**
	    Class destructor, frees it's memory.
	  */

	  virtual void c_player_character::draw(int x, int y);

	  /**
	    Draws player character at given position.

		@param x x position on the scrren
		@param y y position on the screen
	  */
  };

#endif