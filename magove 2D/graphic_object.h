#ifndef GRAPHIC_OBJECT_H
#define GRAPHIC_OBJECT_H

/**
 * Graphic object class header file.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
 */

#include "general.h"

using namespace std;

class c_graphic_object
  {
	/**
	  This class represents an object that is able to
	  draw itself on the screen. It can also play
	  animations.
	*/

    protected:
	  t_animation_type playing_animation;  /** Type of animation being played or looped. */
	  long int started_playing;            /** Time when the animation started playing to count the animation frame. */
	  int animation_frame;                 /** Current animation frame. */
	  bool looping_animation;              /** True if the animation is looping, false otherwise. */

    public:

      virtual void c_graphic_object::draw(int x, int y, long int global_time);

	    /**
	      Tells the object to draw itself at given
	  	  coordinations on the screen.

		  @param x x coordination of the screen
		  @param y y coordination of the screen
		  @param global_time global time counter
		    which is needed for animations etc.
	    */

	  virtual void play_animation(t_animation_type animation, long int global_time);

	    /**
		  Plays given animation.

		  @param animation animation to be played
		  @param global_time global time counter
		*/

	  virtual void loop_animation(t_animation_type animation, long int global_time);

	    /**
		  Loops the given animation untill it's
		  stopped by stop_animation().

		  @param animation animation to be looped
		  @param global_time global time counter
		*/

	  virtual void stop_animation();
	    
	    /**
		  Stops playing the current animation.
		*/

	  bool is_animating();

	    /**
		  Checks if any animation is playing.

		  @return true if any animation is
		    playing or looping, false otherwise
		*/
  };

#endif