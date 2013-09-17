#ifndef GRAPHIC_ANIMATION_H
#define GRAPHIC_ANIMATION_H

/**
 * Animation object class header file.
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

using namespace std;

class c_animation: public c_graphic_object
  {
	/**
	  This class represents an animation object.
	  It contains one animation, that can be
	  played on the screen. It does not affect
	  the game itself, only makes it look nicer.
	*/

    protected:
	  int speed;                                    /** animation speed, 1 is normal, 2 is twice as slow and so on */
	  int offset_x;                                 /** x offset for drawing in pixels */
	  int offset_y;                                 /** y offset for drawing in pixels */	  

	  ALLEGRO_BITMAP *frames[MAX_ANIMATION_FRAMES]; /** bitmaps- animation frames */

    public:

	  c_animation(long int *global_time, string file_prefix, int number_of_frames, int offset_x, int offset_y, int speed,
        bool has_sound, string sound_path, double sound_gain);

	    /**
		  Class constructor, initialises a new
		  object.

		  @param global_time reference to a global
		    time counter
		  @param file_prefix string prefix of
		    file names, that contain the
			animation frames - for example if
			"a" is specified and number of frames
			is 3, then this method will search
			for files "a_1.png", "a_2.png" and
			"a_3.png"
		  @param number_of_frames number of
		    animation frames (there must be
			corresponding number of png
			files)
		  @param offset_x x offset for drawing
		    in pixels (can be negative)
		  @param offset_y y offset for drawing
		    in pixels (can be negative)
		  @param speed speed of the animation,
		    1 is normal, 2 is twice as slow
			and so on
		  @param has_sound set this to true
		    if sound should be loaded for this
			animation, otherwise false
		  @param sound_path if the previous
		    parameter is true, this specifies
			the path to the sound file
		  @param sound_gain sound gain
		    (volume), 1.0 is normal
		*/

	  ~c_animation();

	    /**
		  Class destructor, frees all it's
		  memory.
		*/

      virtual void draw(int x, int y);

	    /**
	      Tells the object to draw itself at given
	  	  coordinations on the screen.

		  @param x x coordination of the screen
		  @param y y coordination of the screen
	    */
  };

#endif