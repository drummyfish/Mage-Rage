/**
 * Graphic object class implementation.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
 */

#include "graphic_object.h"

//-----------------------------------------------

void c_graphic_object::draw(int x, int y, long int global_time)
  {
  }

//-----------------------------------------------

void c_graphic_object::play_animation(t_animation_type animation, long int global_time)
  {
	this->playing_animation = animation;
	this->animation_frame = 0;
	this->looping_animation = false;
	this->started_playing = global_time;
  }

//-----------------------------------------------

void c_graphic_object::loop_animation(t_animation_type animation, long int global_time)
  {
	this->playing_animation = animation;
	this->animation_frame = 0;
	this->looping_animation = true;
	this->started_playing = global_time;
  }

//-----------------------------------------------

bool c_graphic_object::is_animating()
  {
	return this->playing_animation != ANIMATION_NONE;
  }

//-----------------------------------------------

void c_graphic_object::stop_animation()
  {
    this->playing_animation = ANIMATION_NONE;
	this->animation_frame = 0;
  }

//-----------------------------------------------