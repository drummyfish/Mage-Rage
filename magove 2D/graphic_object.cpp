/**
 * Graphic object class implementation.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
 */

#include "graphic_object.h"

//-----------------------------------------------

void c_graphic_object::draw(int x, int y)
  {
  }

//-----------------------------------------------

void c_graphic_object::play_animation(t_animation_type animation)
  {
	this->playing_animation = animation;
	this->animation_frame = 0;
	this->looping_animation = false;
	this->started_playing = *this->global_time;
	this->update_animation_period();
  }

//-----------------------------------------------

bool c_graphic_object::is_succesfully_loaded()
  {
	return this->succesfully_loaded;
  }

//-----------------------------------------------

t_animation_type c_graphic_object::get_playing_animation()
  {
	return this->playing_animation;
  }

//-----------------------------------------------

void c_graphic_object::update_animation_period()
  {
  }

//-----------------------------------------------

void c_graphic_object::loop_animation(t_animation_type animation)
  {
	this->playing_animation = animation;
	this->animation_frame = 0;
	this->looping_animation = true;
	this->started_playing = *this->global_time;
	this->update_animation_period();
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