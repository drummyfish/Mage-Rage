#ifndef CHARACTER_H
#define CHARACTER_H

/**
 * Character class header file.
 *
 * authors: Miloslav Číž, Martin Gabriel
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

    public:

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
  };

#endif