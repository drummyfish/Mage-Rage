/**
 * Player character class implementation file.
 *
 * authors: Miloslav Číž
 * year: 2013
 */

#include "player_character.h"

//-----------------------------------------------

c_player_character::c_player_character(t_player_type player_type, long int *global_time)
  {
	string help_string;

	this->global_time = global_time;
	this->footsteps_gain = 2.0;
	this->magic_energy = MAX_MAGIC_ENERGY;
	this->playing_sound = false;
	this->set_position(0,0);
	this->player_type = player_type;
	this->direction = DIRECTION_SOUTH;
	this->sound = NULL;
	this->fire_cloak_1 = NULL;
	this->fire_cloak_2 = NULL;
	this->fire_cloak_3 = NULL;
	this->sound_firecloak = NULL;
	this->fire_cloak_on = false;
	this->skate_gain = 0.1;

	this->playing_animation = ANIMATION_NONE;

	switch (this->player_type)
	  {
	    case PLAYER_MIA: help_string = "mia"; break;
	    case PLAYER_METODEJ: help_string = "metodej"; break;
	    case PLAYER_STAROVOUS: help_string = "starovous"; break;
	    default: help_string = "mia"; break;
	  }

	// load bitmaps:

	this->shadow = al_load_bitmap("resources/shadow.png");
	this->sprite_north = al_load_bitmap(("resources/character_" + help_string + "_north.png").c_str());
	this->sprite_north_casting = al_load_bitmap(("resources/character_" + help_string + "_north_casting.png").c_str());
	this->sprite_north_running_1 = al_load_bitmap(("resources/character_" + help_string + "_north_running_1.png").c_str());
	this->sprite_north_running_2 = al_load_bitmap(("resources/character_" + help_string + "_north_running_2.png").c_str());
	this->sprite_east = al_load_bitmap(("resources/character_" + help_string + "_east.png").c_str());
	this->sprite_east_casting = al_load_bitmap(("resources/character_" + help_string + "_east_casting.png").c_str());
	this->sprite_east_running_1 = al_load_bitmap(("resources/character_" + help_string + "_east_running_1.png").c_str());
	this->sprite_east_running_2 = al_load_bitmap(("resources/character_" + help_string + "_east_running_2.png").c_str());
	this->sprite_south = al_load_bitmap(("resources/character_" + help_string + "_south.png").c_str());
	this->sprite_south_casting = al_load_bitmap(("resources/character_" + help_string + "_south_casting.png").c_str());
	this->sprite_south_running_1 = al_load_bitmap(("resources/character_" + help_string + "_south_running_1.png").c_str());
	this->sprite_south_running_2 = al_load_bitmap(("resources/character_" + help_string + "_south_running_2.png").c_str());
	this->sprite_west = al_load_bitmap(("resources/character_" + help_string + "_west.png").c_str());
	this->sprite_west_casting = al_load_bitmap(("resources/character_" + help_string + "_west_casting.png").c_str());
	this->sprite_west_running_1 = al_load_bitmap(("resources/character_" + help_string + "_west_running_1.png").c_str());
	this->sprite_west_running_2 = al_load_bitmap(("resources/character_" + help_string + "_west_running_2.png").c_str());

	this->sound_footsteps = al_load_sample("resources/footsteps.wav");
	this->sound_skate = al_load_sample("resources/skate.wav");

	this->succesfully_loaded =
	   (this->shadow && this->sprite_north && this->sprite_north_casting &&
		this->sprite_north_running_1 && this->sprite_north_running_2 &&
		this->sprite_east && this->sprite_east_casting && this->sprite_east_running_1 && 
		this->sprite_east_running_2 && this->sprite_south && this->sprite_south_casting &&
		this->sprite_south_running_1 && this->sprite_south_running_2 && this->sprite_west &&
		this->sprite_west_casting && this->sprite_west_running_1 && this->sprite_west_running_2
		&& this->sound_footsteps && this->sound_skate);

	if (this->player_type == PLAYER_METODEJ)
	  {
		this->fire_cloak_1 = al_load_bitmap("resources/spell_2_metodej_1.png");
		this->fire_cloak_2 = al_load_bitmap("resources/spell_2_metodej_2.png");
		this->fire_cloak_3 = al_load_bitmap("resources/spell_2_metodej_3.png");
		this->sound_firecloak = al_load_sample("resources/metodej_cast2.wav");

		if (!this->fire_cloak_1 || !this->fire_cloak_2 || !this->fire_cloak_3 || !this->sound_firecloak)
		  this->succesfully_loaded = false;
	  }
  }

//-----------------------------------------------

c_player_character::~c_player_character()
  {
	al_destroy_bitmap(this->shadow);                // free bitmaps
	al_destroy_bitmap(this->sprite_north);
	al_destroy_bitmap(this->sprite_north_casting);
	al_destroy_bitmap(this->sprite_north_running_1);
	al_destroy_bitmap(this->sprite_north_running_2);
	al_destroy_bitmap(this->sprite_east);
	al_destroy_bitmap(this->sprite_east_casting);
	al_destroy_bitmap(this->sprite_east_running_1);
	al_destroy_bitmap(this->sprite_east_running_2);
	al_destroy_bitmap(this->sprite_south); 
	al_destroy_bitmap(this->sprite_south_casting);
	al_destroy_bitmap(this->sprite_south_running_1);
	al_destroy_bitmap(this->sprite_south_running_2);
	al_destroy_bitmap(this->sprite_west);
	al_destroy_bitmap(this->sprite_west_casting);
	al_destroy_bitmap(this->sprite_west_running_1);
	al_destroy_bitmap(this->sprite_west_running_2);
	al_destroy_bitmap(this->fire_cloak_1);
	al_destroy_bitmap(this->fire_cloak_2);
	al_destroy_bitmap(this->fire_cloak_3);
	al_destroy_sample(this->sound_firecloak);
	al_destroy_sample(this->sound_footsteps);
	al_destroy_sample(this->sound_skate);
  }

//-----------------------------------------------

void c_player_character::update_animation_period()
  {
	switch (this->playing_animation)
	  {
	    case ANIMATION_RUN:
		  this->animation_period = 2;
		  break;

		case ANIMATION_USE:
		case ANIMATION_CAST:
		  this->animation_period = 2;
		  break;
	  }
  }

//-----------------------------------------------

t_player_type c_player_character::get_player_type()
  {
	return this->player_type;
  }

//-----------------------------------------------

void c_player_character::draw(int x, int y)
  {
    al_draw_bitmap(this->shadow,x,y,0);
	
	if (this->playing_animation == ANIMATION_NONE)
	  {                                                 // no animation
	    switch (this->direction)
	      {
	        case DIRECTION_NORTH:
		      al_draw_bitmap(this->sprite_north,x,y,0);
	          break;

		    case DIRECTION_EAST:
		      al_draw_bitmap(this->sprite_east,x,y,0);
	          break;

		    case DIRECTION_SOUTH:
		      al_draw_bitmap(this->sprite_south,x,y,0);
	          break;
		
		    case DIRECTION_WEST:
	          al_draw_bitmap(this->sprite_west,x,y,0);
	          break;  
	      }
	  }
	else   // playing animation
	  {
		 this->animation_frame = (*this->global_time - this->started_playing) / 4;

		 if (this->looping_animation)
		   this->animation_frame = this->animation_frame % this->animation_period;
		 
		 if (this->playing_animation == ANIMATION_RUN)  // run animation
		   {
			 switch (this->direction)
			   {
			     case DIRECTION_NORTH:
				   if (this->animation_frame == 0)
					 al_draw_bitmap(this->sprite_north_running_1,x,y,0);
				   else
					 al_draw_bitmap(this->sprite_north_running_2,x,y,0); 
				   break;

                 case DIRECTION_EAST:
				   if (this->animation_frame == 0)
					 al_draw_bitmap(this->sprite_east_running_1,x,y,0);
				   else
					 al_draw_bitmap(this->sprite_east_running_2,x,y,0); 
				   break;

				 case DIRECTION_SOUTH:
				   if (this->animation_frame == 0)
					 al_draw_bitmap(this->sprite_south_running_1,x,y,0);
				   else
					 al_draw_bitmap(this->sprite_south_running_2,x,y,0); 
				   break;

				 case DIRECTION_WEST:
				   if (this->animation_frame == 0)
					 al_draw_bitmap(this->sprite_west_running_1,x,y,0);
				   else
					 al_draw_bitmap(this->sprite_west_running_2,x,y,0); 
				   break;
			   }
		   }
		 else if (this->playing_animation == ANIMATION_CAST || this->playing_animation == ANIMATION_USE)
		   { 
			 switch (this->direction)
			   {
			     case DIRECTION_NORTH:
				   al_draw_bitmap(this->sprite_north_casting,x,y,0);
				   break;

                 case DIRECTION_EAST:
				   al_draw_bitmap(this->sprite_east_casting,x,y,0);
				   break;

				 case DIRECTION_SOUTH:
				   al_draw_bitmap(this->sprite_south_casting,x,y,0);
				   break;

				 case DIRECTION_WEST:
				   al_draw_bitmap(this->sprite_west_casting,x,y,0);
				   break;
			   }
		   }
		 else if (this->playing_animation == ANIMATION_SKATE)
		   {
			 switch (this->direction)
			   {
			     case DIRECTION_NORTH:
				   al_draw_bitmap(this->sprite_north_running_1,x,y,0);
				   break;

                 case DIRECTION_EAST:
				   al_draw_bitmap(this->sprite_east_running_1,x,y,0);
				   break;

				 case DIRECTION_SOUTH:
				   al_draw_bitmap(this->sprite_south_running_1,x,y,0);
				   break;

				 case DIRECTION_WEST:
				   al_draw_bitmap(this->sprite_west_running_1,x,y,0);
				   break;
			   }
		   }
		 
		 if (this->animation_frame >= this->animation_period)
		   this->stop_animation();
	  }

	if (this->fire_cloak_on && this->player_type == PLAYER_METODEJ) // draw fire cloak
	  {
		switch ((*this->global_time / 8) % 3)
		  {
		    case 0:
			  al_draw_bitmap(this->fire_cloak_1,x - 12,y - 15,0);
			  break;

		    case 1:
			  al_draw_bitmap(this->fire_cloak_2,x - 12,y - 15,0);
			  break;

		    case 2:
			  al_draw_bitmap(this->fire_cloak_3,x - 12,y - 15,0);
			  break;
		  }
	  }
  }

//-----------------------------------------------

void c_player_character::play_animation(t_animation_type animation)
  {
	this->stop_animation();
	this->playing_animation = animation;
	this->animation_frame = 0;
	this->looping_animation = false;
	this->started_playing = *this->global_time;
	this->update_animation_period();
  }

//-----------------------------------------------

void c_player_character::change_magic_energy(int amount)
  {
	this->magic_energy += amount;
	  
	if (this->magic_energy > MAX_MAGIC_ENERGY)
	  this->magic_energy = MAX_MAGIC_ENERGY;
	else if (this->magic_energy < 0)
	  this->magic_energy = 0;
  }

//-----------------------------------------------

int c_player_character::get_magic_energy()
  {
	return this->magic_energy;
  }

//-----------------------------------------------

void c_player_character::set_fire_cloak(bool state)

  {
	if (this->player_type != PLAYER_METODEJ)
	  return;

	if (state)
	  {
		if (!this->fire_cloak_on)
	      al_play_sample(this->sound_firecloak,0.2,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,&this->sound_firecloak_id);
	  }
	else
	  { 
		if (this->fire_cloak_on)
	      al_stop_sample(&this->sound_firecloak_id);
	  }

	this->fire_cloak_on = state;
  }

//-----------------------------------------------

bool c_player_character::fire_cloak_is_on()

  {
	return this->fire_cloak_on;
  }

//-----------------------------------------------