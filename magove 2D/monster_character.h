#ifndef MONSTER_CHARACTER_H
#define MONSTER_CHARACTER_H

/**
 * Monster character class header file.
 *
 * authors: Miloslav Číž
 * year: 2013
 */

#include "general.h"
#include "character.h"

class c_monster_character: public c_character
  {
    protected:

	  t_monster_type type;                                   /** monster type */

	  int path_length;                                       /** length of path directions and path steps arrays */
      int current_path_instruction;                          /** current position in path arrays */
	  int goes_to;                                           /** x or y coordination (depending on direction) to which the character is headed by the current path instruction */
	  t_direction path_directions[MAX_MONSTER_PATH_LENGTH];  /** contains sequence of directions in which steps are made */
	  int path_steps[MAX_MONSTER_PATH_LENGTH];               /** contains sequence of number of steps that will be made in given directions */
	  bool is_dead;                                          /** whether the monster is dead */
	  bool waiting;                                          /** whether the monster is waiting and not moving */
	  double waiting_end;                                    /** end time of waiting */

	  void next_instruction();

	    /**
		  Switches to the next path instruction.
		*/

    public:

	  c_monster_character(t_monster_type type, long *global_time);

	    /**
		  Class constructor, creates a new object.

		  @param type monster type to be set
		  @param global_time pointer to global
		    time counter
		*/

	  ~c_monster_character();

	    /**
		  Class destructor, frees it's memory.
		*/
	  
	  void add_path_instruction(t_direction direction, int number_of_steps);

	    /**
		  Adds a path instruction for the
		  monster. There is a maximum of
		  MAX_MONSTER_PATH_LENGTH that can be
		  added. Those are instructions for
		  monster to make it's movement.

		  @param direction direction in which
		    to move
		  @param number_of_steps number of
		    steps to make in provided
			direction
		*/

      t_direction get_next_move();

		/**
		  Returns the direction in which the
		  monster should move next;

		  @return direction in which monster
		    should move (can be DIRECTION_NONE
			which means it should wait)
		*/

	  void start_moving();

	    /**
		  Starts the monster's movement, it's
		  position and path should be set by
		  the time this method is called.
		*/

	  virtual void draw(int x, int y);

	    /**
	      Draws monster character at given position.

		  @param x x position on the scrren
		  @param y y position on the screen
	    */
  };

#endif