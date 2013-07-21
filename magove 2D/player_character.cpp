/**
 * Player character class implementation file.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
 */

#include "player_character.h"

//--------------------------------------------------

c_player_character::c_player_character(t_player_type player_type)
  {
	string help_string;

	this->set_position(0,0);
	this->player_type = player_type;
	this->direction = DIRECTION_SOUTH;

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
  }

//--------------------------------------------------

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
  }

//--------------------------------------------------

t_player_type c_player_character::get_player_type()
  {
	return this->player_type;
  }

//--------------------------------------------------

void c_player_character::draw(int x, int y, long int global_time)
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
	else                                                // playing animation
	  {
		 this->animation_frame = (started_playing - global_time / 4) % 2;
		 
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
		 
	  }
  }

//--------------------------------------------------