#ifndef CHARACTER_H
#define CHARACTER_H

/**
 * Character class header file.
 *
 * authors: Miloslav Číž
 * year: 2013
 */

#include "general.h"
#include "graphic_object.h"

class c_character: public c_graphic_object
  {
    /**
	  This abstract class represents an ingame
	  character.
	*/

    protected:

	  double position_x;     /** x position on the map */
	  double position_y;     /** y position on the map */
	  t_direction direction; /** direction, in which the character is facing */
	  double footsteps_gain; /** footstep sound gain */
	  double skate_gain;     /** skate sound gain */

	  ALLEGRO_BITMAP *shadow;                        /** shadow bitmap */
	  ALLEGRO_BITMAP *sprite_north;                  /** character facing north */
	  ALLEGRO_BITMAP *sprite_north_running_1;        /** character running north, frame 1 */
	  ALLEGRO_BITMAP *sprite_north_running_2;        /** character running north, frame 2 */
	  ALLEGRO_BITMAP *sprite_east;                   /** character facing east */
	  ALLEGRO_BITMAP *sprite_east_running_1;         /** character running east, frame 1 */
	  ALLEGRO_BITMAP *sprite_east_running_2;         /** character running east, frame 2 */
	  ALLEGRO_BITMAP *sprite_south;                  /** character facing south */
	  ALLEGRO_BITMAP *sprite_south_running_1;        /** character running south. frame 1 */
	  ALLEGRO_BITMAP *sprite_south_running_2;        /** character running south, frame 2 */
	  ALLEGRO_BITMAP *sprite_west;                   /** character facing west */
	  ALLEGRO_BITMAP *sprite_west_running_1;         /** character running west, frame 1 */
	  ALLEGRO_BITMAP *sprite_west_running_2;         /** character running west, frame 2 */
	  ALLEGRO_SAMPLE *sound_footsteps;               /** sound - footsteps */
	  ALLEGRO_SAMPLE *sound_skate;                   /** sound - skate */

    public:

	  static int position_to_square(double position, bool take_x);

	    /**
	      Converts either x or y double position
		  to integer position in map squares.

		  @param position position to be converted
		  @param take_x if true, the position is
		    considered as x position, otherwise
			y position
		  @return position in map squares
		*/

	  static double square_to_position(int square_position, bool take_x);

	    /**
	      Converts position in map squares to
		  double position.

		  @param square_position position in map
		    squares to be converted
		  @param take_x if true, the position is
		    considered as x position, otherwise
			y position
		  @return double position
		*/

	  void set_position(double x, double y);

	    /**
	      Sets the character's new position.

		  @param x new position x
		  @param y new position y
	    */

	  void set_direction(t_direction direction);

	    /**
	      Sets the character's facing direction.

		  @param direction new direction
	    */

	  void move_by(double x, double y);

	    /**
	      Sets the character's position relatively
		  to current position.

		  @param x value to be added to x position
		  @param y value to be added to y position
	    */

	  double get_position_x();

	    /**
	      Returns x position of the character.

		  @return x position
	    */

	  double get_position_y();
     
	    /**
	      Returns y position of the character.
		
		  @return y position
	    */

	  int get_square_x();

	    /**
	      Returns x coordination of the square at
		  which the character is standing.

		  @return x coordination of the
		    character's square 
	    */

	  int get_square_y();

	    /**
	      Returns y coordination of the square at
		  which the character is standing.

		  @return y coordination of the
		    character's square 
	    */

	  double get_fraction_x();

	    /**
	      Returns fraction part of the position,
		  which is position within current square.

		  @return x position within current
		    square (value in range <0;1>)
	    */

	  double get_fraction_y();

	    /**
	      Returns fraction part of the position,
		  which is position within current square.

	  	  @return y position within current
		    square (value in range <0;1>)
	    */

	  virtual void loop_animation(t_animation_type animation);

	    /**
		  Loops the given animation untill it's
		  stopped by stop_animation().

		  @param animation animation to be looped
		*/

	  t_direction get_direction();

	    /**
	      Returns character's direction.

		  @return character's direction
	    */
  };

#endif