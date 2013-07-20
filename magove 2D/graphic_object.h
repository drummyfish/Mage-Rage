#ifndef GRAPHIC_OBJECT_H
#define GRAPHIC_OBJECT_H

/**
 * Graphic object class header file.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
 */

using namespace std;

class c_graphic_object
  {
	/**
	  This class represents an object that is able to
	  draw itself on the screen. It can also play
	  animations.
	*/

    protected:
	  int playing_animation;  /// Id of the current animation, -1 means no animation.
	  int animation_frame;    /// Current animation frame. 
	  bool looping_animation; /// True if the animation is looping, false otherwise.

    public:

      virtual void c_graphic_object::draw(int x, int y);

	    /**
	      Tells the object to draw itself at given
	  	  coordinations on the screen.

		  @param x x coordination of the screen
		  @param y y coordination of the screen
	    */

	  void play_animation(int animation_id);

	    /**
		  Plays given animation.

		  @param animation_id id of the animation,
		    which must not be negative
		*/

	  void loop_animation(int animation_id);

	    /**
		  Loops the given animation untill it's
		  stopped by stop_animation().

		  @param animation_id id of the animation,
		    which must not be negative
		*/

	  void stop_animation();
	    
	    /**
		  Stops playing the current animation.
		*/
  };

#endif