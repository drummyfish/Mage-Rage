#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

/**
 * Player character class header file.
 *
 * authors: Miloslav Číž
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

	  int magic_energy;                              /** current amount of magic energy */
	  bool fire_cloak_on;                            /** whether the fire cloak spell is on for this player */

	  ALLEGRO_BITMAP *sprite_north_casting;          /** player casting north */
	  ALLEGRO_BITMAP *sprite_east_casting;           /** player casting east */
	  ALLEGRO_BITMAP *sprite_south_casting;          /** player casting south */
	  ALLEGRO_BITMAP *sprite_west_casting;           /** player casting west */

	  ALLEGRO_BITMAP *fire_cloak_1;                  /** bitmap for fire cloak spell, frame 1 */
	  ALLEGRO_BITMAP *fire_cloak_2;                  /** bitmap for fire cloak spell, frame 2 */
	  ALLEGRO_BITMAP *fire_cloak_3;                  /** bitmap for fire cloak spell, frame 3 */

	  ALLEGRO_SAMPLE *sound_firecloak;               /** sound - firecloak spell */
	  ALLEGRO_SAMPLE_ID sound_firecloak_id;          /** id to stop looping sound */

    public:
	  c_player_character(t_player_type player_type, long int *global_time);

	    /**
	      Class constructor, initialises new player
		  character.

	  	  @param player_type type of player character
		  @param global_time reference to a global
		    time counter which is needed for
			animations
	    */

	  ~c_player_character();

	    /**
	      Class destructor, frees it's memory.
	    */

	  virtual void update_animation_period();

	    /**
		  Depending on current animation sets
		  the animation period attribute.
		*/

	  virtual void draw(int x, int y);

	    /**
	      Draws player character at given position.

		  @param x x position on the scrren
		  @param y y position on the screen
	    */

	  t_player_type get_player_type();

	    /**
	      Returns type of this character.

		  @return character type
	    */

	  virtual void play_animation(t_animation_type animation);

	    /**
		  Plays given animation.

		  @param animation animation to be played
		*/

	  void change_magic_energy(int amount);

	    /**
		  Takes or gives an amount of magic
		  energy from or to the player.

		  @param amount amount of energy to
		    be added, this can be also a
			negative number - if the player
			already has full amount of energy
			or zero energy, no overflow will
			occur
		*/

	  int get_magic_energy();

	    /**
		  Returns amount of the player's
		  magic energy.

		  @return player's magic energy
		*/

	  void set_fire_cloak(bool state);

	    /**
		  Sets the fire cloak on or off for this
		  player. Only works for Metodej.

		  @param state if true, the fire cload
		    will be set on, otherwise it will
			be set off
		*/

	  bool fire_cloak_is_on();

	    /**
		  Checks if the fire cloak spell is on
		  for this player.

		  @return true if the fire cloak spell
		  is on, false otherwise
		*/
  };

#endif