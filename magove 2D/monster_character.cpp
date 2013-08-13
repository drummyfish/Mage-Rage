/**
 * Monster character class implementation file.
 *
 * authors: Miloslav Číž
 * year: 2013
 */

#include "monster_character.h"

//-----------------------------------------------

c_monster_character::c_monster_character(t_monster_type type, int square_x, int square_y, long *global_time)
  {
	this->is_dead = false;
	this->path_length = 0;
	this->type = type;
	this->direction = DIRECTION_SOUTH;
	this->current_path_instruction = 0;
	this->waiting = false;
	this->global_time = global_time;
	this->sound_footsteps = al_load_sample("resources/footsteps.wav");
	this->playing_animation = ANIMATION_NONE;
	this->playing_sound = false;


	this->shadow = al_load_bitmap("resources/shadow.png");

	this->position_x = c_character::square_to_position(square_x,true);
	this->position_y = c_character::square_to_position(square_y,false);

	switch (type)
	  {
	    case MONSTER_GHOST:
		  this->sprite_north = al_load_bitmap("resources/character_ghost_north.png");
		  this->sprite_north_running_1 = this->sprite_north;
		  this->sprite_north_running_2 = this->sprite_north;
		  this->sprite_east = al_load_bitmap("resources/character_ghost_east.png");
		  this->sprite_east_running_1 = this->sprite_east;
		  this->sprite_east_running_2 = this->sprite_east;
		  this->sprite_south = al_load_bitmap("resources/character_ghost_south.png");
		  this->sprite_south_running_1 = this->sprite_south;
		  this->sprite_south_running_2 = this->sprite_south;
		  this->sprite_west = al_load_bitmap("resources/character_ghost_west.png");
		  this->sprite_west_running_1 = this->sprite_west;
		  this->sprite_west_running_2 = this->sprite_west;
		  break;

		case MONSTER_TROLL:
		  this->sprite_north = al_load_bitmap("resources/character_troll_north.png");
		  this->sprite_north_running_1 = al_load_bitmap("resources/character_troll_north_running_1.png");
		  this->sprite_north_running_2 = al_load_bitmap("resources/character_troll_north_running_2.png");
		  this->sprite_east = al_load_bitmap("resources/character_troll_east.png");
		  this->sprite_east_running_1 = al_load_bitmap("resources/character_troll_east_running_1.png");
		  this->sprite_east_running_2 = al_load_bitmap("resources/character_troll_east_running_2.png");
		  this->sprite_south = al_load_bitmap("resources/character_troll_south.png");
		  this->sprite_south_running_1 = al_load_bitmap("resources/character_troll_south_running_1.png");
		  this->sprite_south_running_2 = al_load_bitmap("resources/character_troll_south_running_2.png");
		  this->sprite_west = al_load_bitmap("resources/character_troll_west.png");
		  this->sprite_west_running_1 = al_load_bitmap("resources/character_troll_west_running_1.png");
		  this->sprite_west_running_2 = al_load_bitmap("resources/character_troll_west_running_2.png");
		  break;
	  }
	
	this->succesfully_loaded = (!this->shadow || !this->sprite_north || !this->sprite_north_running_1 || 
	  !this->sprite_north_running_2 || !this->sprite_east || !this->sprite_east_running_1 || 
	  !this->sprite_east_running_2 || !this->sprite_south || !this->sprite_south_running_1 || 
	  !this->sprite_south_running_2 || !this->sprite_west || !this->sprite_west_running_1 ||
	  !this->sprite_west_running_2 || !this->sound_footsteps); 
  }

//-----------------------------------------------

c_monster_character::~c_monster_character()
  {
  }

//-----------------------------------------------

void c_monster_character::draw(int x, int y)
  {
	ALLEGRO_BITMAP *bitmap_to_draw;
	
	if (this->is_animating())
	  this->animation_frame = (*this->global_time / 4) % 2;

	switch(this->direction)
	  {
         case DIRECTION_NORTH:
  		   if (this->is_animating())
			 {
		  	   if (this->animation_frame)
			     bitmap_to_draw = this->sprite_north_running_1;
			   else
			     bitmap_to_draw = this->sprite_north_running_2;
			 }
		   else
			 bitmap_to_draw = this->sprite_north;
		    
		   break;

         case DIRECTION_EAST:
  		   if (this->is_animating())
			 {
			   if (this->animation_frame)
			     bitmap_to_draw = this->sprite_east_running_1;
			   else
			     bitmap_to_draw = this->sprite_east_running_2;
			 }
		   else
			 bitmap_to_draw = this->sprite_east;
		  
		   break;

         case DIRECTION_SOUTH:
  		   if (this->is_animating())
			 {
			   if (this->animation_frame)
			     bitmap_to_draw = this->sprite_south_running_1;
			   else
			     bitmap_to_draw = this->sprite_south_running_2;
			 }
		   else
			 bitmap_to_draw = this->sprite_south;
		  break;

        case DIRECTION_WEST:
		  if (this->is_animating())
			 {
			   if (this->animation_frame)
				 bitmap_to_draw = this->sprite_west_running_1;
			   else
				 bitmap_to_draw = this->sprite_west_running_2;
			 }
		   else
			 bitmap_to_draw = this->sprite_west;
		  break;
	  }

	al_draw_bitmap(this->shadow,x,y,0);
	al_draw_bitmap(bitmap_to_draw,x,y,0);
  }

//-----------------------------------------------

void c_monster_character::next_instruction()
  {
    this->current_path_instruction = (this->current_path_instruction + 1) % this->path_length;
	
	switch(this->path_directions[this->current_path_instruction])
	  {
	    case DIRECTION_NORTH:
	      this->goes_to = c_character::square_to_position(this->get_square_y() - this->path_steps[this->current_path_instruction],false);
		  break;

		case DIRECTION_EAST:
		  this->goes_to = c_character::square_to_position(this->get_square_x() + this->path_steps[this->current_path_instruction],true);
		  break;

		case DIRECTION_SOUTH: 
		  this->goes_to = c_character::square_to_position(this->get_square_y() + this->path_steps[this->current_path_instruction],false);
		  break;

	    case DIRECTION_WEST:
		  this->goes_to = c_character::square_to_position(this->get_square_x() - this->path_steps[this->current_path_instruction],true);
		  break;

        case DIRECTION_NONE:
		  this->waiting = true;
		  this->waiting_end = al_current_time() + 1.0 * this->path_steps[this->current_path_instruction];
		  break;
	  }

	
  }

//-----------------------------------------------

t_direction c_monster_character::get_next_move()
  { 
	bool next_instruction;

	if (this->path_length == 0)
	  return DIRECTION_NONE;

    if (this->waiting)                             // do nothing if waiting
	  {
		if (al_current_time() >= this->waiting_end)
		  {
		    this->waiting = false;
			this->next_instruction();
		  }

	    return DIRECTION_NONE;
	  }

	next_instruction = false;                      // whether to go to the next instruction

	switch(this->path_directions[this->current_path_instruction])
	  {
	    case DIRECTION_NORTH:
		  if (this->position_y <= this->goes_to)
		    next_instruction = true;

		  break;

		case DIRECTION_EAST:
		  if (this->position_x >= this->goes_to)
		    next_instruction = true;

		  break;

		case DIRECTION_SOUTH:
		  if (this->position_y >= this->goes_to)
		    next_instruction = true;

		  break;

	    case DIRECTION_WEST:
		  if (this->position_x <= this->goes_to)
		    next_instruction = true;

		  break;

		case DIRECTION_NONE:
		  this->waiting = true;
		  this->goes_to = this->position_x;
		  this->waiting_end = al_current_time() + this->path_steps[this->current_path_instruction] * 1.0; // set waiting time, 1 sec. for each step
		  
		  break;
	  }

	if (next_instruction)
	  {
		this->next_instruction();
	  }
	
	return this->path_directions[this->current_path_instruction];
  }

//-----------------------------------------------

void c_monster_character::add_path_instruction(t_direction direction, int number_of_steps)
  {
	if (this->path_length >= MAX_MONSTER_PATH_LENGTH)
      return;

	this->path_directions[this->path_length] = direction;
	this->path_steps[this->path_length] = number_of_steps;
	this->path_length++;
  }

//-----------------------------------------------

void c_monster_character::start_moving()
  {
	if (this->path_length == 0)
	  return;

	this->current_path_instruction = 0;

	this->current_path_instruction = -1;  // a little trick, the next instruction will be zero
	this->next_instruction();
  }

//-----------------------------------------------