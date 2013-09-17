/**
 * Animation object class implementation.
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

#include "animation.h"

//----------------------------------------------

c_animation::c_animation(long int *global_time, string file_prefix, int number_of_frames, int offset_x, int offset_y, int speed,
  bool has_sound, string sound_path, double sound_gain)
  {
	int i;

	if (has_sound)
	  {
	    this->sound = al_load_sample(sound_path.c_str());

	    if (!this->sound)
          this->succesfully_loaded = false;
	  }
	else
	  this->sound = NULL;

	this->sound_gain = sound_gain;
	this->playing_sound = false;
	this->animation_period = number_of_frames;
	this->offset_x = offset_x;
	this->offset_y = offset_y;
	this->speed = speed;
	this->global_time = global_time;
	this->succesfully_loaded = true;

	for (i = 0; i < MAX_ANIMATION_FRAMES; i++)
	  this->frames[i] = NULL;

	for (i = 0; i < number_of_frames; i++)
	  {
		this->frames[i] = al_load_bitmap((file_prefix + "_" + to_string((long long)(i + 1)) + ".png").c_str());

		if (this->frames[i] == NULL)
		  {
			this->succesfully_loaded = false;
			break;
		  }
	  }
  }

//----------------------------------------------

c_animation::~c_animation()
  {
	int i;

	al_destroy_sample(this->sound);

	for (i = 0; i < MAX_ANIMATION_FRAMES; i++)
	  al_destroy_bitmap(this->frames[i]);
  }

//----------------------------------------------

void c_animation::draw(int x, int y)
  {
	this->animation_frame = (*this->global_time - this->started_playing) / this->speed;

	if (!this->looping_animation)
	  if (this->animation_frame >= this->animation_period)
	    {
		  this->stop_animation();
	      return;
	    }

	al_draw_bitmap(this->frames[this->animation_frame % this->animation_period],this->offset_x + x,this->offset_y + y,0);
  }

//----------------------------------------------