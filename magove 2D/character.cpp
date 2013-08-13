/**
 * Character class implementation file.
 *
 * authors: Miloslav Číž
 * year: 2013
 */

#include "character.h"

//-----------------------------------------------

void c_character::move_by(double x, double y)
  {
	this->position_x += x;
	this->position_y += y;
  }

//-----------------------------------------------

void c_character::set_direction(t_direction direction)
  {
	this->direction = direction;
  }

//-----------------------------------------------

void c_character::set_position(double x, double y)
  {
	this->position_x = x;
	this->position_y = y;
  }

//-----------------------------------------------

double c_character::get_position_x()
  {
	return this->position_x;
  }
	
//-----------------------------------------------

double c_character::get_position_y()
  {
	return this->position_y;
  }

//-----------------------------------------------

int c_character::position_to_square(double position, bool take_x)
  {
	if (take_x)
	  return floor(position + 0.3);
	else
	  return position > -0.3 ? floor(position + 0.3) + 1 : 0;
  }

//-----------------------------------------------

double c_character::square_to_position(int square_position, bool take_x)
  {
	if (take_x)
	  return square_position + 0.25;
	else
	  return square_position > 0.0 ? square_position - 0.5 : -0.31;
  }

//-----------------------------------------------

int c_character::get_square_x()
  {
	return this->position_to_square(this->position_x,true);
	// return floor(this->position_x + 0.3);  // 0.3 is a centering constant
  }

//-----------------------------------------------

int c_character::get_square_y()
  {
	return this->position_to_square(this->position_y,false);
	//return this->position_y > -0.3 ? floor(this->position_y + 0.3) + 1 : 0;
  }

//-----------------------------------------------

double c_character::get_fraction_x()
  {
	double helper;

	return modf(this->position_x + 0.3,&helper);
  }

//-----------------------------------------------

double c_character::get_fraction_y()
  {
	double helper;

	return this->position_y > -0.3 ? modf(this->position_y + 0.3,&helper) : 1.3 + this->position_y;
  }

//-----------------------------------------------

t_direction c_character::get_direction()
  {
	return this->direction;
  }

//-----------------------------------------------

void c_character::loop_animation(t_animation_type animation)
  { 
	this->stop_animation();
	this->playing_animation = animation;
	this->animation_frame = 0;
	this->looping_animation = true;
	this->started_playing = *this->global_time;
	this->update_animation_period();

	switch (animation)
	  {
	    case ANIMATION_RUN:
		  if (this->sound_footsteps != NULL)
		    {
			  al_play_sample(this->sound_footsteps,this->footsteps_gain,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,&this->playing_sound_id);
		      this->playing_sound = true;
		    }

		  break;
	  }
  }

//-----------------------------------------------