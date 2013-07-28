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
	  t_animation_type playing_animation;  /** type of animation being played or looped */
	  long int started_playing;            /** time when the animation started playing to count the animation frame */
	  long int *global_time;               /** reference to a global time counter variable (for animations) */
	  long int animation_frame;            /** current animation frame */
	  bool looping_animation;              /** true if the animation is looping, false otherwise */
	  int animation_period;                /** number of frames of the current animation */
	  bool succesfully_loaded;             /** stores information about errors */
	  ALLEGRO_SAMPLE_ID playing_sound_id;  /** an ID of the sound being played */

    public:

      virtual void c_graphic_object::draw(int x, int y);

	    /**
	      Tells the object to draw itself at given
	  	  coordinations on the screen.

		  @param x x coordination of the screen
		  @param y y coordination of the screen
	    */

	  virtual void play_animation(t_animation_type animation);

	    /**
		  Plays given animation.

		  @param animation animation to be played
		*/

	  virtual void loop_animation(t_animation_type animation);

	    /**
		  Loops the given animation untill it's
		  stopped by stop_animation().

		  @param animation animation to be looped
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

	  virtual void update_animation_period();

	    /**
		  Depending on current animation sets
		  the animation period attribute.
		*/

	  t_animation_type get_playing_animation();

	    /**
		  Returns a type of animation being
		  played or looped.

		  @return type of animation
		*/

	  bool is_succesfully_loaded();

	    /**
		  Checks if the map has been loaded
		  succesfully.

		  @return true if the map is loaded
		    succesfully, false otherwise
		*/
  };

#endif