/**
 * Graphic object class implementation.
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

#include "graphic_object.h"

//-----------------------------------------------

void c_graphic_object::draw(int x, int y)
  {
  }

//-----------------------------------------------

int c_graphic_object::get_animation_frame()
  {
	return this->animation_frame;
  }

//-----------------------------------------------

void c_graphic_object::play_animation(t_animation_type animation)
  {
	this->stop_animation();
	this->playing_animation = animation;
	this->animation_frame = 0;
	this->looping_animation = false;
	this->started_playing = *this->global_time;
	this->update_animation_period();

	if (this->sound != NULL)
	  {
	    al_play_sample(this->sound,this->sound_gain,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&this->playing_sound_id);
		this->playing_sound = true;
	  } 
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
	this->stop_animation();
	this->playing_animation = animation;
	this->animation_frame = 0;
	this->looping_animation = true;
	this->started_playing = *this->global_time;
	this->update_animation_period();

	if (this->sound != NULL)
	  {
	    al_play_sample(this->sound,this->sound_gain,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,&this->playing_sound_id);
  		this->playing_sound = true;
	  }
  }

//-----------------------------------------------

bool c_graphic_object::is_animating()
  {
	return this->playing_animation != ANIMATION_NONE;
  }

//-----------------------------------------------

void c_graphic_object::stop_animation()
  {
	if (this->looping_animation && this->playing_sound)
	  {
		al_stop_sample(&this->playing_sound_id);
	    this->playing_sound = false;
	  }

    this->playing_animation = ANIMATION_NONE;
	this->animation_frame = 0;
  }

//-----------------------------------------------