﻿/**
 * Map class implementation.
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

#include "map.h"
#include "map_object.h"

//-----------------------------------------------

void c_map::next_square(int x, int y, t_direction direction, int *next_x, int *next_y)
  {
	switch (direction)
	  {
	    case DIRECTION_NORTH:
		  *next_x = x;
		  *next_y = y - 1;
		  break;

		case DIRECTION_EAST:
		  *next_x = x + 1;
		  *next_y = y;
		  break;

		case DIRECTION_SOUTH:
		  *next_x = x;
		  *next_y = y + 1;
		  break;

		case DIRECTION_WEST:
		  *next_x = x - 1;
		  *next_y = y;
		  break;
	  }
  }

//-----------------------------------------------

int c_map::get_height(int x, int y)
  {
	int i, number_of_crates;
	int plus_elevator;          // if there is an elevator and is on, this will rise the height by 1
	int plus_water;

	if (x >= this->width || x < 0 ||
	  y >= this->height || y < 0)
	  return 0;

	number_of_crates = 0;

	plus_water = 0;

	if (this->get_square_type(x,y) == SQUARE_WATER)
	  plus_water = -1;

	for (i = 0; i < MAX_OBJECTS_PER_SQUARE; i++)
	  if (this->squares[x][y].map_objects[i] == NULL)
	    break;
	  else if (this->squares[x][y].map_objects[i]->get_type() == OBJECT_CRATE)
		number_of_crates++;

	plus_elevator = 0;

	for (i = 0; i < MAX_OBJECTS_PER_SQUARE; i++)
	  if (this->squares[x][y].map_objects[i] != NULL)
	    {
		  if (this->squares[x][y].map_objects[i]->get_type() == OBJECT_ELEVATOR &&
			this->squares[x][y].map_objects[i]->get_state() == OBJECT_STATE_ON)
		    plus_elevator = 1;
	    }
	  else
	    break;

	return this->squares[x][y].height + number_of_crates + plus_elevator + plus_water;
  }

//-----------------------------------------------

int c_map::get_terrain_height(int x, int y)
  {
    if (x >= this->width || x < 0 ||
	  y >= this->height || y < 0)
	  return 0;

	return this->squares[x][y].height;
  }

//-----------------------------------------------

t_square_type c_map::get_square_type(int x, int y)
  {
	if (x >= this->width || x < 0 || y >= this->height || y < 0)
	  return SQUARE_NORMAL;

	return this->squares[x][y].type;
  }

//-----------------------------------------------

bool c_map::set_environment(t_environment new_environment)
  {
	string help_string;
	bool success;

	success = true;

	this->environment = new_environment;

	switch (this->environment)
	  {
	    case ENVIRONMENT_GRASS: help_string = "grass"; break;
		case ENVIRONMENT_DIRT: help_string = "dirt"; break;
		case ENVIRONMENT_SNOW: help_string = "snow"; break;
		case ENVIRONMENT_CASTLE: help_string = "castle"; break;
		default: help_string = "grass"; break;
	  }

	this->tile = al_load_bitmap(("resources/tile_" + help_string + ".png").c_str());
	this->tile_cliff_south_1 = al_load_bitmap(("resources/tile_" + help_string + "_cliff_south_1.png").c_str());
	this->tile_cliff_south_2 = al_load_bitmap(("resources/tile_" + help_string + "_cliff_south_2.png").c_str());
	this->tile_cliff_southwest_1 = al_load_bitmap(("resources/tile_" + help_string + "_cliff_southwest_1.png").c_str());
	this->tile_cliff_southwest_2 = al_load_bitmap(("resources/tile_" + help_string + "_cliff_southwest_2.png").c_str());
	this->tile_cliff_southeast_1 = al_load_bitmap(("resources/tile_" + help_string + "_cliff_southeast_1.png").c_str());
	this->tile_cliff_southeast_2 = al_load_bitmap(("resources/tile_" + help_string + "_cliff_southeast_2.png").c_str());
	this->tile_cliff_west = al_load_bitmap(("resources/tile_" + help_string + "_cliff_west.png").c_str());
	this->tile_cliff_east = al_load_bitmap(("resources/tile_" + help_string + "_cliff_east.png").c_str());
	this->tile_cliff_north = al_load_bitmap(("resources/tile_" + help_string + "_cliff_north.png").c_str());
	this->tile_cliff_northwest = al_load_bitmap(("resources/tile_" + help_string + "_cliff_northwest.png").c_str());
	this->tile_cliff_northeast = al_load_bitmap(("resources/tile_" + help_string + "_cliff_northeast.png").c_str());
    this->tile_edge = al_load_bitmap(("resources/tile_" + help_string + "_edge.png").c_str());
	this->tile_water[0] = al_load_bitmap("resources/tile_water_1.png");
	this->tile_water[1] = al_load_bitmap("resources/tile_water_2.png");
	this->tile_water[2] = al_load_bitmap("resources/tile_water_3.png");
	this->tile_water[3] = al_load_bitmap("resources/tile_water_4.png");
	this->tile_water[4] = al_load_bitmap("resources/tile_water_5.png");
	this->tile_ice = al_load_bitmap("resources/tile_ice.png");
	this->tile_collapse = al_load_bitmap("resources/tile_collapse.png");
	this->tile_hole = al_load_bitmap("resources/tile_hole.png");   
	this->bitmap_crate_water = al_load_bitmap("resources/object_crate_water.png");

	if (!this->tile || !this->tile_cliff_south_1 || !this->tile_cliff_south_2 ||
	  !this->tile_cliff_southwest_1 || !this->tile_cliff_southwest_2 || !this->tile_cliff_southeast_1 ||
	  !this->tile_cliff_southeast_2 || !this->tile_cliff_west || !this->tile_cliff_east ||
	  !this->tile_cliff_north || !this->tile_cliff_northwest || !this->tile_cliff_northeast || 
	  !this->tile_edge || !this->tile_water[0] || !this->tile_water[1] || !this->tile_water[2] || 
	  !this->tile_water[3] || !this->tile_water[4] || !this->tile_ice || !this->tile_collapse ||
	  !this->tile_hole || !this->bitmap_crate_water)
	  return false;

	return true;
  }

//-----------------------------------------------

c_map::c_map(string filename, t_input_output_state *input_output_state, long int *global_time, int language)
  {
	this->change_flame_state = 0;
	this->language = language;
    this->current_player = 0;
	this->pressed_1 = false;
	this->pressed_2 = false;
	this->pressed_3 = false;  
	this->check_firecloak = false;
	this->current_player = 0;
	this->mouse_pressed = false;
	this->frame_count = 0;
	this->animation_frame = 0;
	this->text_is_displayed = false;
	this->time_before = 0.0; 
	this->global_time = global_time;
	this->flames_on = false;
    this->input_output_state = input_output_state;
	this->number_of_missiles = 0;
	this->screen_square_resolution[0] = this->input_output_state->screen_x / SQUARE_WIDTH + 1;
	this->screen_square_resolution[1] = this->input_output_state->screen_y / SQUARE_HEIGHT + 1;
	this->screen_square_position[0] = 0;
	this->screen_square_position[1] = 0;
	this->screen_pixel_position[0] = 0;
	this->screen_pixel_position[0] = 0;
	this->screen_square_end[0] = this->screen_square_resolution[0];
	this->screen_square_end[1] = this->screen_square_resolution[1];
	this->screen_center_x = this->input_output_state->screen_x / 2; 
    this->screen_center_y = this->input_output_state->screen_y / 2;
	this->oren_destroyed = false;
	this->time_difference = 0.0;

	portrait_x_positions[0] = 20;
	portrait_x_positions[1] = 170;
	portrait_x_positions[2] = 320;
	portrait_y_position = this->input_output_state->screen_y - 75;

	this->succesfully_loaded = this->load_from_file(filename);

	// center the map1:

	this->screen_square_position[0] = (this->width - this->screen_square_resolution[0]) / 2;
	this->screen_square_position[1] = (this->height - this->screen_square_resolution[1]) / 2;;
	this->screen_pixel_position[0] = this->screen_square_position[0] * SQUARE_WIDTH;
	this->screen_pixel_position[1] = this->screen_square_position[1] * SQUARE_HEIGHT;
	this->screen_square_end[0] = this->screen_square_position[0] + this->screen_square_resolution[0];
	this->screen_square_end[1] = this->screen_square_position[1] + this->screen_square_resolution[1];

	this->update_screen_position();

	this->check_buttons();
  }

//-----------------------------------------------

void c_map::add_map_object(c_map_object *map_object, int x, int y)
  {
	int i;

	if (x < 0 || x >= this->width || y < 0 || y > this->height)
	  return;

	for (i = 0; i < MAX_OBJECTS_PER_SQUARE; i++)       // find the first free place for the object
	  if (this->squares[x][y].map_objects[i] == NULL)
	    {
		  this->squares[x][y].map_objects[i] = map_object;
	      break;
	    }
  }

//-----------------------------------------------

string c_map::get_nth_substring(string from_what, int n)
  {
	int i;
	int current_n;
	string return_string;

	current_n = 0;
	return_string = "";

	for (i = 0; (unsigned int) i < from_what.length(); i++)
	  {
		if (from_what[i] == '|')
		  {
		    current_n++;
			continue;
		  }

        if (current_n == n)
		  return_string += from_what[i];
		else if (current_n > n)
		  break;
	  }

	return return_string;
  }

//-----------------------------------------------

void c_map::set_map_objects(string object_string)
  {
	int position, i;
	int numbers[5];
	string object_type, sign_string, help_string;
	c_map_object *help_object;

	for (position = 0; (unsigned int) position < object_string.size(); position++)
	  {
		if (object_string[position] == '(')   // object opening bracket
		  { 
			object_type = object_string.substr(position + 1,2);

			position += 3;

			for (i = 0; i < 5; i++) // load following numbers in the array
			  {
				position++;

				if ((unsigned int) position >= object_string.size() || object_string[position] == ')')
				  break;

				help_string = "";

				if (object_string[position] != '"')  // a number
				  {
					while (object_string[position] != ',' && object_string[position] != ')')
					  {
                        help_string += object_string[position];
						position++;
					  }

					numbers[i] = atoi(help_string.c_str());
				  }
				else  // loading sign text
				  {
					position++;

                    while (object_string[position] != '"' && object_string[position] != ')')
					  {
                        help_string += object_string[position];
						position++;
					  }

					position++;

					sign_string = help_string;
				  }

				if (object_string[position] == ')')
				  break;
			  }

			if (numbers[0] < 0 || numbers[0] >= this->width || numbers[1] < 0 || numbers[1] >= this->height)
			  continue;

			if (object_type.compare("ro") == 0)
			  this->add_map_object(new c_map_object(OBJECT_ROCK,-1,-1,this->global_time),numbers[0],numbers[1]);
			else if (object_type.compare("cr") == 0)
			  this->add_map_object(new c_map_object(OBJECT_CRATE,-1,-1,this->global_time),numbers[0],numbers[1]);
			else if (object_type.compare("ic") == 0)
			  this->add_map_object(new c_map_object(OBJECT_ICE,-1,-1,this->global_time),numbers[0],numbers[1]);
			else if (object_type.compare("tr") == 0)
			  this->add_map_object(new c_map_object(OBJECT_TREE,-1,-1,this->global_time),numbers[0],numbers[1]);
			else if (object_type.compare("st") == 0)
			  this->add_map_object(new c_map_object(OBJECT_STATUE,-1,-1,this->global_time),numbers[0],numbers[1]);
		    else if (object_type.compare("bu") == 0)
			  this->add_map_object(new c_map_object(OBJECT_BUTTON,numbers[2],numbers[3],this->global_time),numbers[0],numbers[1]);
			else if (object_type.compare("or") == 0)
              this->add_map_object(new c_map_object(OBJECT_OREN,-1,-1,this->global_time),numbers[0],numbers[1]);
		    else if (object_type.compare("kr") == 0)
              this->add_map_object(new c_map_object(OBJECT_KEY_RED,-1,-1,this->global_time),numbers[0],numbers[1]);
			else if (object_type.compare("kg") == 0)
              this->add_map_object(new c_map_object(OBJECT_KEY_GREEN,-1,-1,this->global_time),numbers[0],numbers[1]);
			else if (object_type.compare("kb") == 0)
              this->add_map_object(new c_map_object(OBJECT_KEY_BLUE,-1,-1,this->global_time),numbers[0],numbers[1]);
			else if (object_type.compare("si") == 0)
			  {
				help_object = new c_map_object(OBJECT_SIGN,-1,-1,this->global_time);
				help_object->set_sign_text(this->get_nth_substring(sign_string,this->language));
			    this->add_map_object(help_object,numbers[0],numbers[1]);
			  }
		    else if (object_type.compare("dh") == 0)
			  {
				help_object = new c_map_object(OBJECT_DOOR_HORIZONTAL,numbers[2],numbers[3],this->global_time);
			    this->add_map_object(help_object,numbers[0],numbers[1]);

			    if (numbers[4])
				  help_object->set_state(OBJECT_STATE_ON);
			  }
			else if (object_type.compare("dv") == 0)
			  {
				help_object = new c_map_object(OBJECT_DOOR_VERTICAL,numbers[2],numbers[3],this->global_time);
			    this->add_map_object(help_object,numbers[0],numbers[1]);

				if (numbers[4])
				  help_object->set_state(OBJECT_STATE_ON);
			  }
			else if (object_type.compare("fo") == 0)
			  this->add_map_object(new c_map_object(OBJECT_FOUNTAIN,-1,-1,&this->animation_frame),numbers[0],numbers[1]);
		    else if (object_type.compare("le") == 0)
			  {
				help_object = new c_map_object(OBJECT_LEVER,numbers[2],numbers[3],this->global_time);
			    this->add_map_object(help_object,numbers[0],numbers[1]);
			  
			    if (numbers[4])
				  help_object->set_state(OBJECT_STATE_ON);
			  }
			else if (object_type.compare("sn") == 0)
			  this->add_map_object(new c_map_object(OBJECT_STAIRS_NORTH,-1,-1,this->global_time),numbers[0],numbers[1]);
			else if (object_type.compare("fl") == 0)
			  {
                help_object = new c_map_object(OBJECT_FLAMES,numbers[2],numbers[3],this->global_time);
				this->add_map_object(help_object,numbers[0],numbers[1]);

				if (numbers[4])
				  help_object->set_state(OBJECT_STATE_ON);
			  }
			else if (object_type.compare("se") == 0)
			  this->add_map_object(new c_map_object(OBJECT_STAIRS_EAST,-1,-1,this->global_time),numbers[0],numbers[1]);
		    else if (object_type.compare("ss") == 0)
			  this->add_map_object(new c_map_object(OBJECT_STAIRS_SOUTH,-1,-1,this->global_time),numbers[0],numbers[1]);
			else if (object_type.compare("sw") == 0)
			  this->add_map_object(new c_map_object(OBJECT_STAIRS_WEST,-1,-1,this->global_time),numbers[0],numbers[1]);
		    else if (object_type.compare("f1") == 0)
			  this->add_map_object(new c_map_object(OBJECT_FLOWERS,-1,-1,this->global_time),numbers[0],numbers[1]);
			else if (object_type.compare("f2") == 0)
			  this->add_map_object(new c_map_object(OBJECT_FLOWERS2,-1,-1,this->global_time),numbers[0],numbers[1]);
		    else if (object_type.compare("c1") == 0)
			  this->add_map_object(new c_map_object(OBJECT_CARPET,-1,-1,this->global_time),numbers[0],numbers[1]);
		    else if (object_type.compare("c2") == 0)
			  this->add_map_object(new c_map_object(OBJECT_CARPET2,-1,-1,this->global_time),numbers[0],numbers[1]);  
		    else if (object_type.compare("bo") == 0)
			  this->add_map_object(new c_map_object(OBJECT_BONES,-1,-1,this->global_time),numbers[0],numbers[1]);
		    else if (object_type.compare("wl") == 0)
			  this->add_map_object(new c_map_object(OBJECT_WATER_LILY,-1,-1,this->global_time),numbers[0],numbers[1]);
		    else if (object_type.compare("ga") == 0)
			  this->add_map_object(new c_map_object(OBJECT_GATE,-1,-1,&this->animation_frame),numbers[0],numbers[1]);
		    else if (object_type.compare("tw") == 0)
			  this->add_map_object(new c_map_object(OBJECT_TREE_WINTER,-1,-1,&this->animation_frame),numbers[0],numbers[1]);
			else if (object_type.compare("el") == 0)
			  {
			    help_object = new c_map_object(OBJECT_ELEVATOR,numbers[2],numbers[3],this->global_time);
				this->add_map_object(help_object,numbers[0],numbers[1]);

				if (numbers[4])
				  help_object->set_state(OBJECT_STATE_ON);
			  }
			else if (object_type.compare("ts") == 0)
			  {
			    help_object = new c_map_object(OBJECT_TELEPORT_INPUT,numbers[2],-1,this->global_time);
				this->add_map_object(help_object,numbers[0],numbers[1]);
			  }
		    else if (object_type.compare("td") == 0)
			  {
			    help_object = new c_map_object(OBJECT_TELEPORT_OUTPUT,numbers[2],numbers[3],this->global_time);
				this->add_map_object(help_object,numbers[0],numbers[1]);
			  }
         }
	  }

	this->link_objects();
	this->record_buttons();
  }

//-----------------------------------------------

void c_map::set_monsters(string monster_string)
  {
	int position, x, y, i, steps;
	string monster_type, help_string;
	c_monster_character *help_monster;
	char direction_char;
	t_direction direction;

	this->number_of_monsters = 0;

	for (position = 0; (unsigned int) position < monster_string.size(); position++)
	  if (monster_string[position] == '(')   // opening bracket
	    {
           monster_type = monster_string.substr(position + 1,2);

		   position += 4;

		   help_string = monster_string.substr(position,2); // load x
		   
		   position += 2; 

		   if (help_string[1] == ',' || help_string[1] == ')')
		     {
			   help_string = help_string[0];
		     }
		   else
			 position++;

		   x = atoi(help_string.c_str());

		   help_string = monster_string.substr(position,2); // load y

		   position += 2;

		   if (help_string[1] == ',' || help_string[1] == ')')
		     {
			   help_string = help_string[0];
		     }
		   else
			 position++;

		   y = atoi(help_string.c_str());

		   if (monster_type.compare("gh") == 0)
			 help_monster = new c_monster_character(MONSTER_GHOST,x,y,this->global_time);
		   else
			 help_monster = new c_monster_character(MONSTER_TROLL,x,y,this->global_time);

		   this->monster_characters[this->number_of_monsters] = help_monster;
		   this->number_of_monsters++;

		   for (i = 0; i < MAX_MONSTER_PATH_LENGTH / 2; i++)    // load path
		     {
			   if ((unsigned int) position >= monster_string.length() || monster_string[position] == ',') // no path specified
				 break;

			   direction_char = monster_string[position];       // load direction

			   position += 2;

			   help_string = monster_string.substr(position,2); // load number of steps

			   if (help_string[1] == ',' || help_string[1] == ')')
		         {
			       help_string = help_string[0];
		         }
		       else
			     {
			       position++;
			     }

			   steps = atoi(help_string.c_str());

               position++;

			   switch (direction_char)
			     {
			       case 'n':
                     direction = DIRECTION_NORTH;
					 break;

				   case 'e':
                     direction = DIRECTION_EAST;
					 break;

				   case 's':
                     direction = DIRECTION_SOUTH;
					 break;

				   case 'w':
                     direction = DIRECTION_WEST;
					 break;

				   case '-':
                     direction = DIRECTION_NONE;
					 break;

			     }

			   help_monster->add_path_instruction(direction,steps);

			   if (monster_string[position] == ')') // closing bracket
			     {
				   position++;
				   break;
			     }

			   position++;
		     }

		   help_monster->start_moving();
	    }
  }

//-----------------------------------------------

string c_map::get_description()
  {
	return this->description;
  }

//-----------------------------------------------

bool c_map::load_from_file(string filename)
  {
	c_associative_array *associative_array;
	int i, j, k, next_player;
	bool all_ok;

	all_ok = true;
	associative_array = new c_associative_array();
	all_ok = associative_array->load_from_file(filename);

    if (!all_ok)
	  {
		delete associative_array;
	    return false;
	  }

	this->width = atoi(associative_array->get_text("width").c_str());       // set width and height
	this->height = atoi(associative_array->get_text("height").c_str());
	this->description = this->get_nth_substring(associative_array->get_text("description"),this->language);

	if (associative_array->get_text("environment").compare("grass") == 0)   // set environment
	  all_ok = this->set_environment(ENVIRONMENT_GRASS);
	else if (associative_array->get_text("environment").compare("dirt") == 0)
	  all_ok = this->set_environment(ENVIRONMENT_DIRT);
    else if (associative_array->get_text("environment").compare("snow") == 0)
	  all_ok = this->set_environment(ENVIRONMENT_SNOW);
    else
      all_ok = this->set_environment(ENVIRONMENT_CASTLE); 

	for (j = 0; j < this->height; j++)       // set terrain
	  for (i = 0; i < this->width; i++)
	    { 
		  switch (associative_array->get_text("heightmap")[j * this->width + i])
		    {
		      case '0':
				this->squares[i][j].height = 0;
			    break;
			  
			  case '1':
				this->squares[i][j].height = 1;
				break;

			  case '2':
				this->squares[i][j].height = 2;
				break;
		    }

		  switch (associative_array->get_text("typemap")[j * this->width + i])
		    {
		      case 'n':
				this->squares[i][j].type = SQUARE_NORMAL;
			    break;
			  
			  case 'w':
				this->squares[i][j].type = SQUARE_WATER;
				break;

			  case 'i':
				this->squares[i][j].type = SQUARE_ICE;
				break;

			  case 'c':
				this->squares[i][j].type = SQUARE_COLLAPSE;
				break;

			  case 'h':
				this->squares[i][j].type = SQUARE_HOLE;
				break;
		    }

		  this->squares[i][j].animation = NULL;

		  for (k = 0; k < MAX_OBJECTS_PER_SQUARE; k++)
		    {
		      this->squares[i][j].map_objects[k] = NULL;
		    }
		}

	next_player = 0;

	this->music_name = associative_array->get_text("music");

	if (associative_array->get_text("mia_x").compare("") == 0) // set players
	  this->player_characters[next_player] = NULL;
	else
	  {
	    this->player_characters[next_player] = new c_player_character(PLAYER_MIA,this->global_time); 
		this->player_characters[next_player]->set_square_position(atoi(associative_array->get_text("mia_x").c_str()),atoi(associative_array->get_text("mia_y").c_str()));
	    next_player++;
	  }

	if (associative_array->get_text("metodej_x").compare("") == 0)
	  this->player_characters[next_player] = NULL;
	else
	  {
	    this->player_characters[next_player] = new c_player_character(PLAYER_METODEJ,this->global_time); 
		this->player_characters[next_player]->set_square_position(atoi(associative_array->get_text("metodej_x").c_str()),atoi(associative_array->get_text("metodej_y").c_str()));
	    next_player++;
	  }

	if (associative_array->get_text("starovous_x").compare("") == 0)
	  this->player_characters[next_player] = NULL;
	else
	  {
	    this->player_characters[next_player] = new c_player_character(PLAYER_STAROVOUS,this->global_time); 
		this->player_characters[next_player]->set_square_position(atoi(associative_array->get_text("starovous_x").c_str()),atoi(associative_array->get_text("starovous_y").c_str()));
	  }

	this->set_map_objects(associative_array->get_text("objects")); // set objects

	this->set_monsters(associative_array->get_text("monsters")); // set monsters

	delete associative_array;

	// the map's loaded, now load resources

    this->animation_water_splash = new c_animation(this->global_time,"resources/animation_water_splash",5,-5,-5,2,true,"resources/water.wav",1.0);
	this->animation_refresh = new c_animation(this->global_time,"resources/animation_refresh",6,0,0,2,true,"resources/refresh.wav",0.5);
	this->animation_crate_shift_north = new c_animation(this->global_time,"resources/animation_crate_shift_north",3,0,-79,1,false,"",1.0);
	this->animation_collapse = new c_animation(this->global_time,"resources/animation_collapse",5,0,0,2,true,"resources/crack.wav",0.3);
	this->animation_melt = new c_animation(this->global_time,"resources/animation_melt",4,0,-27,5,false,"",0.0);
	this->animation_teleport = new c_animation(this->global_time,"resources/animation_teleport",5,0,-27,5,true,"resources/teleport.wav",0.4);
	this->animation_explosion = new c_animation(this->global_time,"resources/animation_explosion",7,0,-27,5,true,"resources/explosion.wav",0.3);
	this->animation_shadow_explosion = new c_animation(this->global_time,"resources/animation_shadow_explosion",6,0,-27,5,true,"resources/shadow_explosion.wav",0.4);

    this->spell_sounds_mia[0] = al_load_sample("resources/mia_cast.wav");
    this->spell_sounds_mia[1] = al_load_sample("resources/mia_cast2.wav");
	this->spell_sounds_metodej[0] = al_load_sample("resources/metodej_cast.wav");
    this->spell_sounds_metodej[1] = al_load_sample("resources/metodej_cast2.wav");
	this->spell_sounds_starovous[0] = al_load_sample("resources/starovous_cast.wav");
    this->spell_sounds_starovous[1] = al_load_sample("resources/starovous_cast2.wav"); 
	this->change_player_sound = al_load_sample("resources/change.wav");

	if (!this->animation_water_splash->is_succesfully_loaded())
	  return false;

	this->portrait_mia = al_load_bitmap("resources/portrait_mia.png");               // load portrait bitmaps
	this->portrait_metodej = al_load_bitmap("resources/portrait_metodej.png");
	this->portrait_starovous = al_load_bitmap("resources/portrait_starovous.png");
	this->portrait_selection = al_load_bitmap("resources/selection.png");

	this->spell_mia_1[0] = al_load_bitmap("resources/spell_1_mia_1.png");            // load spell bitmaps
	this->spell_mia_1[1] = al_load_bitmap("resources/spell_1_mia_2.png");
	this->spell_mia_1[2] = al_load_bitmap("resources/spell_1_mia_3.png");
	this->spell_mia_2[0] = al_load_bitmap("resources/spell_2_mia_1.png");
	this->spell_mia_2[1] = al_load_bitmap("resources/spell_2_mia_2.png");
	this->spell_mia_2[2] = al_load_bitmap("resources/spell_2_mia_3.png");
	this->spell_metodej_1[0] = al_load_bitmap("resources/spell_1_metodej_1.png");
	this->spell_metodej_1[1] = al_load_bitmap("resources/spell_1_metodej_2.png");
	this->spell_metodej_1[2] = al_load_bitmap("resources/spell_1_metodej_3.png");
	this->spell_starovous_1[0] = al_load_bitmap("resources/spell_1_starovous_1.png");
	this->spell_starovous_1[1] = al_load_bitmap("resources/spell_1_starovous_2.png");
	this->spell_starovous_1[2] = al_load_bitmap("resources/spell_1_starovous_3.png");
	this->spell_starovous_2[0] = al_load_bitmap("resources/spell_2_starovous_1.png");
	this->spell_starovous_2[1] = al_load_bitmap("resources/spell_2_starovous_2.png");
	this->spell_starovous_2[2] = al_load_bitmap("resources/spell_2_starovous_3.png");                            
	this->spell_icons[0] = al_load_bitmap("resources/icon_telekinesis.png");
	this->spell_icons[1] = al_load_bitmap("resources/icon_create_path.png");
	this->spell_icons[2] = al_load_bitmap("resources/icon_fireball.png");
	this->spell_icons[3] = al_load_bitmap("resources/icon_fire_cloak.png");
	this->spell_icons[4] = al_load_bitmap("resources/icon_light.png");
	this->spell_icons[5] = al_load_bitmap("resources/icon_heal.png");
	this->spell_icons[6] = al_load_bitmap("resources/icon_teleport.png");

	this->map_shadow_north = al_load_bitmap("resources/map_shadow_north.png");
	this->map_shadow_south = al_load_bitmap("resources/map_shadow_south.png");
	this->map_shadow_east = al_load_bitmap("resources/map_shadow_east.png");
	this->map_shadow_west = al_load_bitmap("resources/map_shadow_west.png");

	if (!this->portrait_mia || !this->portrait_metodej ||
		!this->portrait_starovous || !this->portrait_selection ||
		!this->spell_mia_1[0] || !this->spell_mia_1[1] ||
	    !this->spell_mia_1[2] || !this->spell_mia_2[0] ||
	    !this->spell_mia_2[1] || !this->spell_mia_2[2] ||
	    !this->spell_metodej_1[0] || !this->spell_metodej_1[1] ||
	    !this->spell_metodej_1[2] || !this->spell_starovous_1[0] ||
	    !this->spell_starovous_1[1] || !this->spell_starovous_1[2] ||
	    !this->spell_starovous_2[0] || !this->spell_starovous_2[1] ||
	    !this->spell_starovous_2[2] || !this->change_player_sound)
	  return false;

	for (i = 0; i < 7; i++)
	  if (this->spell_icons[i] == NULL)
		return false;

	this->text_font = al_load_ttf_font("resources/architects_daughter.ttf",20,0);  // load the font
	
	if (!this->text_font)
	  return false;

	return true;
  }

//-----------------------------------------------

void c_map::record_buttons()
  {
	int button_positions[512][2];        // buffer to hold button positions
	int i, j;

	this->number_of_buttons = 0;

	for (j = 0; j < this->height; j++)              // record all button positions
	  for (i = 0; i < this->width; i++)
		if (this->square_has_object(i,j,OBJECT_BUTTON))
		  {
			button_positions[this->number_of_buttons][0] = i;
			button_positions[this->number_of_buttons][1] = j;
			this->number_of_buttons++;
		  }

	this->button_positions_x = new int[this->number_of_buttons];
	this->button_positions_y = new int[this->number_of_buttons];

	for (i = 0; i < this->number_of_buttons; i++)
	  {
        this->button_positions_x[i] = button_positions[i][0];
		this->button_positions_y[i] = button_positions[i][1];
	  }
  }

//-----------------------------------------------

void c_map::update_monsters()
  { 
	int i;
	bool must_check_buttons;
	bool can_move;
	t_direction direction;

	must_check_buttons = false;

	for (i = 0; i < this->number_of_monsters; i++)
      if (this->monster_characters[i] != NULL)
	    {
		  direction = this->monster_characters[i]->get_next_move();
		  
		  can_move = false;

		  switch (direction)
		    {
		      case DIRECTION_EAST:
				if (this->monster_characters[i]->get_fraction_x() < 1 - CLIFF_DISTANCE_EAST_WEST)
			      can_move = true;
					
				break;

			  case DIRECTION_NORTH:
				if (this->monster_characters[i]->get_fraction_y() > CLIFF_DISTANCE_SOUTH)
			      can_move = true;
					
				break;

			  case DIRECTION_WEST:
				if (this->monster_characters[i]->get_fraction_x() > CLIFF_DISTANCE_EAST_WEST)
			      can_move = true;
					
				break;

			  case DIRECTION_SOUTH:
				if (this->monster_characters[i]->get_fraction_x() < 1 - CLIFF_DISTANCE_NORTH)
			      can_move = true;
					
				break;
		    }

		  if (direction != DIRECTION_NONE && (can_move || this->character_can_move_to_square(this->monster_characters[i],direction)))
		    {
			  this->move_character(this->monster_characters[i],direction);
		      must_check_buttons = true;
		    }
		  else
		    {
			  this->monster_characters[i]->stop_animation();
		    }
	    }
	  
	if (must_check_buttons)
      this->check_buttons();
  }

//-----------------------------------------------

void c_map::get_object_position(c_map_object *what, int *x, int *y)
  {
	int i, j, k;

	for (j = 0; j < this->height; j++)
	  for (i = 0; i < this->width; i++)
		for (k = 0; k < MAX_OBJECTS_PER_SQUARE; k++)
		  if (this->squares[i][j].map_objects[k] == NULL)
			break;
		  else if (this->squares[i][j].map_objects[k] == what)
		    {
			  *x = i;
			  *y = j;
			  return;
		    }

	*x = -1;
	*y = -1;
  }

//-----------------------------------------------

bool c_map::object_can_be_used(c_map_object *what)
  {
	int i, x, y;
	c_map_object *help_object;

	i = 0;

	while (true)
	  {
		help_object = what->get_controlled_object(i);
	    
		if (help_object == NULL)
		  break;

		if (help_object->get_type() == OBJECT_DOOR_HORIZONTAL ||
		  help_object->get_type() == OBJECT_DOOR_VERTICAL)
		  {
		    this->get_object_position(help_object,&x,&y);

		    if (this->square_has_character(x,y) || this->square_has_object(x,y,OBJECT_CRATE))
			  return false;
		  }

		i++;
	  }

	return true;
  }

//-----------------------------------------------

void c_map::display_animation(t_display_animation animation, int x, int y)
  {
	if (x < 0 || x >= this->width || y < 0 || y >= this->height)
	  return;

	switch (animation)
	  {
	    case DISPLAY_ANIMATION_WATER_SPLASH:
		  this->squares[x][y].animation = this->animation_water_splash;
		  this->animation_water_splash->play_animation(ANIMATION_IDLE);
		  break;

		case DISPLAY_ANIMATION_CRATE_SHIFT_NORTH:
		  this->squares[x][y].animation = this->animation_crate_shift_north;
		  this->animation_crate_shift_north->play_animation(ANIMATION_IDLE);
		  break;

		case DISPLAY_ANIMATION_COLLAPSE:
		  this->squares[x][y].animation = this->animation_collapse;
		  this->animation_collapse->play_animation(ANIMATION_IDLE);
		  break;

		case DISPLAY_ANIMATION_MELT:
		  this->squares[x][y].animation = this->animation_melt;
		  this->animation_melt->play_animation(ANIMATION_IDLE);
		  break;	

		case DISPLAY_ANIMATION_REFRESH:
		  this->squares[x][y].animation = this->animation_refresh;
		  this->animation_refresh->play_animation(ANIMATION_IDLE);
		  break;

		case DISPLAY_ANIMATION_TELEPORT:
		  this->squares[x][y].animation = this->animation_teleport;
		  this->animation_teleport->play_animation(ANIMATION_IDLE);
		  break;

		case DISPLAY_ANIMATION_EXPLOSION:
		  this->squares[x][y].animation = this->animation_explosion;
		  this->animation_explosion->play_animation(ANIMATION_IDLE);
		  break;

	    case DISPLAY_ANIMATION_SHADOW_EXPLOSION:
		  this->squares[x][y].animation = this->animation_shadow_explosion;
		  this->animation_shadow_explosion->play_animation(ANIMATION_IDLE);
		  break;
	  }
  }

//-----------------------------------------------
c_map::~c_map()
  {
	int i, j, k;

	for (j = 0; j < this->height; j++)              // destroy map objects
	  for (i = 0; i < this->width; i++)
		for (k = 0; k < MAX_OBJECTS_PER_SQUARE; k++)
		  {
		    if (this->squares[i][j].map_objects[k] != NULL)
			  delete this->squares[i][j].map_objects[k];
		  }

	for (i = 0; i < 3; i++)                         // destroy players
	  if (this->player_characters[i] != NULL)
		delete this->player_characters[i];

	for (i = 0; i < this->number_of_monsters; i++)  // destroy monsters
	  if (this->monster_characters[i] != NULL)
	    delete this->monster_characters[i];

	delete this->animation_water_splash;            // destroy animations                   
	delete this->animation_refresh;                              
	delete this->animation_crate_shift_north;                     
	delete this->animation_collapse;                               
	delete this->animation_melt;                                   
	delete this->animation_teleport;                              
	delete this->animation_explosion;                              
	delete this->animation_shadow_explosion;   

	al_destroy_bitmap(this->portrait_selection);    // destroy bitmaps
	al_destroy_bitmap(this->portrait_mia);      
	al_destroy_bitmap(this->portrait_metodej);   
	al_destroy_bitmap(this->portrait_starovous);       
	al_destroy_bitmap(this->tile);                     
	al_destroy_bitmap(this->tile_cliff_south_1);       
	al_destroy_bitmap(this->tile_cliff_south_2);        
	al_destroy_bitmap(this->tile_cliff_southwest_1);     
	al_destroy_bitmap(this->tile_cliff_southwest_2);     
	al_destroy_bitmap(this->tile_cliff_southeast_1);         
	al_destroy_bitmap(this->tile_cliff_southeast_2);          
	al_destroy_bitmap(this->tile_cliff_west);                 
	al_destroy_bitmap(this->tile_cliff_east);                  
	al_destroy_bitmap(this->tile_cliff_north);             
	al_destroy_bitmap(this->tile_cliff_northwest);          
	al_destroy_bitmap(this->tile_cliff_northeast);          
	al_destroy_bitmap(this->tile_edge);                      
	al_destroy_bitmap(this->tile_ice);                           
	al_destroy_bitmap(this->tile_collapse);                               
	al_destroy_bitmap(this->tile_hole);                              
	al_destroy_bitmap(this->bitmap_crate_water);                     

	al_destroy_bitmap(this->map_shadow_north);
	al_destroy_bitmap(this->map_shadow_south);
	al_destroy_bitmap(this->map_shadow_east);
	al_destroy_bitmap(this->map_shadow_west);

	for (i = 0; i < 5; i++)
	  al_destroy_bitmap(this->tile_water[i]);            

	for (i = 0; i < 3; i++)
	  {
	    al_destroy_bitmap(this->spell_mia_1[i]);                           
	    al_destroy_bitmap(this->spell_mia_2[i]);                         
		al_destroy_bitmap(this->spell_metodej_1[i]);        
	    al_destroy_bitmap(this->spell_starovous_1[i]);                  
	    al_destroy_bitmap(this->spell_starovous_2[i]); 
	  }

	for (i = 0; i < 7; i++)
	  al_destroy_bitmap(this->spell_icons[i]);   

	al_destroy_sample(this->change_player_sound);    // destroy sounds

	for (i = 0; i < 2; i++)
	  {
	    al_destroy_sample(this->spell_sounds_mia[i]);        
	    al_destroy_sample(this->spell_sounds_metodej[i]);                   
	    al_destroy_sample(this->spell_sounds_starovous[i]);                  
	  }

	al_destroy_font(this->text_font);               // destroy the font
  }

//-----------------------------------------------

void c_map::check_buttons()
  {
	int i, j;
	int nuber_of_objects;    // number of objects on one square
	c_map_object *help_object;
	bool is_pressed;

	for (i = 0; i < this->number_of_buttons; i++)
	  {
		is_pressed = false;

		for (j = 0; j < 3; j++)  // check if any player is standing on the square
		  if (this->player_characters[j] != NULL)
			if (this->player_characters[j]->get_square_x() == this->button_positions_x[i] &&
			    this->player_characters[j]->get_square_y() == this->button_positions_y[i])
			  {
				is_pressed = true;
				break; 
			  }
	    
		if (!is_pressed)
          for (j = 0; j < number_of_monsters; j++)  // check if any monster is standing on the square
		    if (this->monster_characters[j] != NULL)
			  if (this->monster_characters[j]->get_square_x() == this->button_positions_x[i] &&
			      this->monster_characters[j]->get_square_y() == this->button_positions_y[i])
			    {
				  is_pressed = true;
				  break;
			    }

		if (!is_pressed)
		  {
		    nuber_of_objects = 0;

	        for (j = 0; j < MAX_OBJECTS_PER_SQUARE; j++)
	          {
		        help_object = this->squares[this->button_positions_x[i]][this->button_positions_y[i]].map_objects[j];

				if (help_object != NULL && help_object->get_type() == OBJECT_CRATE)
		          {
			        nuber_of_objects++;
		          }
	          }

			if (nuber_of_objects >= 1)  // if there are crates, then press the button
			  is_pressed = true;
		  }

		for (j = 0; j < MAX_OBJECTS_PER_SQUARE; j++) // find the button and do actions
		  {
			help_object = this->squares[this->button_positions_x[i]][this->button_positions_y[i]].map_objects[j];

			if (help_object != NULL && help_object->get_type() == OBJECT_BUTTON && this->object_can_be_used(help_object))
			  {

				if (is_pressed)
				  {
					if (help_object->get_state() == OBJECT_STATE_OFF)
					  {
					    help_object->switch_state();
					    help_object->play_animation(ANIMATION_SWITCH_OFF);
						this->update_flames();
					  }
				  }
				else
				  {
					if (help_object->get_state() == OBJECT_STATE_ON)
					  {
						help_object->switch_state();
					    help_object->play_animation(ANIMATION_SWITCH_ON);
					    this->update_flames();
					  }
				  }
			  }
		  }
      }
  }

//-----------------------------------------------

bool c_map::crate_can_be_shifted(int x, int y, int height, t_direction direction)
  {
	int next_square[2];
	int i;

	if (x < 0 || x >= this->width || y < 0 || y >= this->height)
	  return false;

	this->next_square(x,y,direction,&next_square[0],&next_square[1]);

	if (next_square[0] < 0 || next_square[0] >= this->width ||      // check the map range
	  next_square[1] < 0 || next_square[1] >= this->height)
	  return false;

	if (!this->square_is_stepable(next_square[0],next_square[1]))
	  return false;

	if (this->get_height(x,y) - 1 != height)      // check if shifting from right height 
	  return false;

	if (this->square_has_character(x,y))
	  return false;

	if (this->square_has_character(next_square[0],next_square[1]))
	  return false;

	if (this->get_height(next_square[0],next_square[1]) > height)
	  return false;

	if (!this->door_can_be_passed(x,y,direction))               // door at the crate's square
	  return false;

	if (this->get_height(x,y) - 1 == this->get_height(next_square[0],next_square[1])) // door at the next square and the same height level
	  {
		return (this->door_can_be_passed(next_square[0],next_square[1],direction));
	  }
	else    // door that are on lower height level
	  {
		for (i = 0; i < MAX_OBJECTS_PER_SQUARE; i++)
		  if (this->squares[next_square[0]][next_square[1]].map_objects[i] != NULL &&
			(this->squares[next_square[0]][next_square[1]].map_objects[i]->get_type() == OBJECT_DOOR_HORIZONTAL ||
			this->squares[next_square[0]][next_square[1]].map_objects[i]->get_type() == OBJECT_DOOR_VERTICAL) &&
			this->squares[next_square[0]][next_square[1]].map_objects[i]->get_state() == OBJECT_STATE_OFF)
		    return false;
	  }

	return true;
  }

//-----------------------------------------------

bool c_map::square_has_character(int x, int y)
  {
	int i;

	for (i = 0; i < 3; i++)
	  if (this->player_characters[i] != NULL &&
	    this->player_characters[i]->get_square_x() == x &&
		this->player_characters[i]->get_square_y() == y)
		return true;

	for (i = 0; i < this->number_of_monsters; i++)
	  if (this->monster_characters[i] != NULL &&
		this->monster_characters[i]->get_square_x() == x &&
		this->monster_characters[i]->get_square_y() == y)
	    return true;

	return false;
  }

//-----------------------------------------------

void c_map::remove_object(int x, int y, int index)
  {
	int i;

	for (i = index + 1; i < MAX_OBJECTS_PER_SQUARE; i++)
	  {
		this->squares[x][y].map_objects[i - 1] = this->squares[x][y].map_objects[i];
		this->squares[x][y].map_objects[i] = NULL;
	  }
  }

//-----------------------------------------------

void c_map::shift_crate(int x, int y, t_direction direction)
  {
	int i;
	int next_square[2];

	for (i = 0; i < MAX_OBJECTS_PER_SQUARE; i++)
	  if (this->squares[x][y].map_objects[i] != NULL)
	    {
		  if (this->squares[x][y].map_objects[i]->get_type() == OBJECT_CRATE)
		    {
			  this->next_square(x,y,direction,&next_square[0],&next_square[1]);

			  switch(direction)
			    {
			      case DIRECTION_EAST:
					this->squares[x][y].map_objects[i]->play_animation(ANIMATION_SHIFT_EAST);
				    break;

			      case DIRECTION_WEST:
					this->squares[x][y].map_objects[i]->play_animation(ANIMATION_SHIFT_WEST);
				    break;

			      case DIRECTION_NORTH:
					this->squares[x][y].map_objects[i]->play_animation(ANIMATION_SHIFT_NORTH);
					this->display_animation(DISPLAY_ANIMATION_CRATE_SHIFT_NORTH,x,y);
				    break;

				  case DIRECTION_SOUTH:
					this->squares[x][y].map_objects[i]->play_animation(ANIMATION_SHIFT_SOUTH);
				    break;
			    }

			  if (this->get_square_type(next_square[0],next_square[1]) == SQUARE_WATER &&
				!this->square_has_object(next_square[0],next_square[1],OBJECT_CRATE))
			    this->display_animation(DISPLAY_ANIMATION_WATER_SPLASH,next_square[0],next_square[1]);
	
			  this->add_map_object(this->squares[x][y].map_objects[i],next_square[0],next_square[1]);
			  this->remove_object(x,y,i);  

			  break;
		    }
	    }
	  else
		break;

	this->check_buttons();
  }

//-----------------------------------------------

void c_map::link_objects()
  {
	int i, j, k, l, m, n, o;
	bool is_in_array;
	c_map_object *help_object, *help_object2;
	c_map_object *object_array[256];            // buffer to temporarily hold objects
	int array_length;

	for (j = 0; j < this->height; j++)
	  for (i = 0; i < this->width; i++)
		for (k = 0; k < MAX_OBJECTS_PER_SQUARE; k++)
		  {
			help_object = this->squares[i][j].map_objects[k];

		    if (help_object != NULL && help_object->is_input())
			  {
                array_length = 0;

				for (m = 0; m < this->height; m++)        // find the corresponding map object
	              for (l = 0; l < this->width; l++)
					for (n = 0; n < this->width; n++)
					  {
						help_object2 = this->squares[l][m].map_objects[n];

						if (help_object2 != NULL)
						  {
							if (!help_object2->is_input() &&
								help_object->compare_link_ids(help_object2))
							  {
								is_in_array = false;      // we have to check, if the object is already in the array

								for (o = 0; o < array_length; o++)
								  if (object_array[o] == help_object2)
								    {
									  is_in_array = true;
									  break;
								    }

								if (!is_in_array)
								  {
								    object_array[array_length] = help_object2;
								    array_length++;
								  }
							  }
						  }
						else
						  break;
					  }

			    help_object->add_controlled_objects(array_length,object_array);
		      }
		}
  }

//-----------------------------------------------

void c_map::update_map_object_states()
  {
  }

//-----------------------------------------------

bool c_map::must_have_border(t_square_type type1, t_square_type type2)
  {
	if (type1 == SQUARE_COLLAPSE || type1 == SQUARE_HOLE)
	  return (type2 != SQUARE_COLLAPSE && type2 != SQUARE_HOLE);
	
	return (type1 != type2);
  }

//-----------------------------------------------

void c_map::draw_borders(int x, int y, int plus_x, int plus_y)
  {
	int elevation, square_height;
	t_square_type square_type;

	square_type = this->squares[x][y].type;
	square_height = this->squares[x][y].height;
	elevation = square_height * ELEVATION;
			          
	if (this->must_have_border(this->get_square_type(x,y - 1),square_type)    // north border
	  || this->get_terrain_height(x,y - 1) != square_height)     
	  al_draw_bitmap(this->tile_edge,plus_x + x * SQUARE_WIDTH,plus_y + y * SQUARE_HEIGHT - elevation,0);

	if (this->must_have_border(this->get_square_type(x + 1,y),square_type)    // east border
	  || this->get_terrain_height(x + 1,y) != square_height)
      al_draw_bitmap(this->tile_cliff_west,plus_x + x * SQUARE_WIDTH + 54,plus_y + y * SQUARE_HEIGHT - elevation,0);

	if (this->must_have_border(this->get_square_type(x - 1,y),square_type)    // west border
	  || this->get_terrain_height(x - 1,y) != square_height)
      al_draw_bitmap(this->tile_cliff_east,plus_x + x * SQUARE_WIDTH,plus_y + y * SQUARE_HEIGHT - elevation,0);

	if (this->must_have_border(this->get_square_type(x,y + 1),square_type)    // south border
	  || this->get_terrain_height(x,y + 1) != square_height)
      al_draw_bitmap(this->tile_cliff_north,plus_x + x * SQUARE_WIDTH,plus_y + y * SQUARE_HEIGHT - elevation + 40,0);
  }

//-----------------------------------------------

void c_map::draw(int x, int y)
  {
	int i, j, k, help_height, elevation, number_of_crates, elevator_height, help_x, help_y;

	al_clear_to_color(al_map_rgb(0,0,0));      // clear the screen
	
	this->animation_frame = *this->global_time / 16;

	for (j = this->screen_square_position[1] - 1; j < this->screen_square_end[1] + 1; j++)                         // go through lines
	  { 
		if (j < 0 || j >= this->height)               // outside map boundaries - don't draw
	      continue;

        for (help_height = 0; help_height < 3; help_height++)  // go through all 3 height levels
	      { 		  
			elevation = help_height * ELEVATION;      // y offset caused by different height levels
	
			for (i = this->screen_square_position[0] - 1; i < this->screen_square_end[0] + 1; i++)                 // go through columns
			  { 
				if (i < 0 || i >= this->width) // outside map boundaries - don't draw
	              continue;

				if (this->squares[i][j].height == help_height)
		          {  
					help_x = x + i * SQUARE_WIDTH - this->screen_pixel_position[0];
					help_y = y + j * SQUARE_HEIGHT - elevation - this->screen_pixel_position[1];

			        switch (this->squares[i][j].type)
			          {
			            case SQUARE_NORMAL:                      // normal square
						  al_draw_bitmap(this->tile,help_x,help_y,0); // draw floor
						  break;

				        case SQUARE_WATER:                       // water square
					      al_draw_bitmap(this->tile_water[this->animation_frame % 5],help_x,help_y,0);			          
					      this->draw_borders(i,j,x - this->screen_pixel_position[0],y - this->screen_pixel_position[1]);
						  break;

						case SQUARE_ICE:                          // ice square
						  al_draw_bitmap(this->tile_ice,help_x,help_y,0);
						  this->draw_borders(i,j,x - this->screen_pixel_position[0],y - this->screen_pixel_position[1]);
						  break;

						case SQUARE_COLLAPSE:                     // collapse square
						  al_draw_bitmap(this->tile_collapse,help_x,help_y,0);
						  this->draw_borders(i,j,x - this->screen_pixel_position[0],y - this->screen_pixel_position[1]);
						  break;

						case SQUARE_HOLE:                         // hole
						  al_draw_bitmap(this->tile_hole,help_x,help_y,0);
						  this->draw_borders(i,j,x - this->screen_pixel_position[0],y - this->screen_pixel_position[1]);
						  break;
					  }
				
			        if (help_height != 3)                                                // draw south cliffs
				      {
				        if (this->get_terrain_height(i,j - 1) == help_height + 1)                    // south
					      {
							help_x = x + i * SQUARE_WIDTH - this->screen_pixel_position[0];
							help_y = y + j * SQUARE_HEIGHT - elevation - ELEVATION - this->screen_pixel_position[1];

				  	        al_draw_bitmap(this->tile_cliff_south_1,help_x,help_y,0);

							if (this->get_terrain_height(i + 1,j - 1) != this->get_terrain_height(i,j - 1) && i != this->width - 1)  // southeast 1
						      al_draw_bitmap(this->tile_cliff_southeast_1,x + i * SQUARE_WIDTH + SQUARE_WIDTH - this->screen_pixel_position[0],help_y,0);
				    
					        if (this->get_terrain_height(i - 1,j - 1) != this->get_terrain_height(i,j - 1) && i != 0)                // southwest 1
					          al_draw_bitmap(this->tile_cliff_southwest_1,x + i * SQUARE_WIDTH - 10 - this->screen_pixel_position[0],help_y,0);
					        
							if (i == 0)   // cut part of the cliff so it appears like it's in fog
							  {
                                al_draw_filled_rectangle(help_x - 10,help_y,help_x + 10,help_y + 30,al_map_rgb(0,0,0));
							  }
							else if (i == this->width - 1)
							  {
								al_draw_filled_rectangle(help_x + 55,help_y,help_x + 90,help_y + 30,al_map_rgb(0,0,0));
							  }
						  }
				        else if (this->get_terrain_height(i,j - 1) == help_height + 2)
					      {
							help_x = x + i * SQUARE_WIDTH - this->screen_pixel_position[0];
							help_y = y + j * SQUARE_HEIGHT - elevation - 54 - this->screen_pixel_position[1];

					        al_draw_bitmap(this->tile_cliff_south_2,help_x,help_y,0);

					        if (this->get_terrain_height(i + 1,j - 1) != this->get_terrain_height(i,j - 1) && i != this->width - 1)  // southeast 2
						      al_draw_bitmap(this->tile_cliff_southeast_2,x + i * SQUARE_WIDTH + SQUARE_WIDTH - this->screen_pixel_position[0],help_y,0);
				    
					        if (this->get_terrain_height(i - 1,j - 1) != this->get_terrain_height(i,j - 1) && i != 0)                // southwest 2
						      al_draw_bitmap(this->tile_cliff_southwest_2,x + i * SQUARE_WIDTH - 10 - this->screen_pixel_position[0],help_y,0);
					      
						    if (i == 0)   // cut part of the cliff so it appears like it's in the fog
							  {
                                al_draw_filled_rectangle(help_x - 10,help_y,help_x + 10,help_y + 60,al_map_rgb(0,0,0));
							  }
							else if (i == this->width - 1)
							  {
								al_draw_filled_rectangle(help_x + 55,help_y,help_x + 90,help_y + 60,al_map_rgb(0,0,0));
							  } 
						  }
				      }
			  
				    if (help_height != 0)                                               // draw other cliffs
				      {
				        if (this->get_terrain_height(i,j - 1) < help_height)                        // north
					      {
							help_x = x + i * SQUARE_WIDTH - this->screen_pixel_position[0];
							help_y = y + j * SQUARE_HEIGHT - elevation - 10 - this->screen_pixel_position[1];

					        al_draw_bitmap(this->tile_cliff_north,help_x,help_y,0);
				    
					        if (this->get_terrain_height(i + 1,j - 1) != help_height &&
						      this->get_terrain_height(i + 1,j) != help_height)                      // northeast
						     al_draw_bitmap(this->tile_cliff_northeast,x + i * SQUARE_WIDTH + SQUARE_WIDTH - this->screen_pixel_position[0],help_y,0);

					        if (this->get_terrain_height(i - 1,j - 1) != help_height &&
						      this->get_terrain_height(i - 1,j) != help_height)                      // northwest
						      al_draw_bitmap(this->tile_cliff_northwest,x + i * SQUARE_WIDTH - 10 - this->screen_pixel_position[0],help_y,0);

							if (i == 0) // fog
							  al_draw_filled_rectangle(help_x - 10,help_y + 5,help_x + 10,help_y + 10,al_map_rgb(0,0,0));
							else if (i == this->width - 1)
							  al_draw_filled_rectangle(help_x + 55,help_y + 5,help_x + 70,help_y + 10,al_map_rgb(0,0,0));
					      }

						if (this->get_terrain_height(i - 1,j) < help_height && i != 0)               // west
					      al_draw_bitmap(this->tile_cliff_west,x + i * SQUARE_WIDTH - 10 - this->screen_pixel_position[0],y + j * SQUARE_HEIGHT - elevation - this->screen_pixel_position[1],0);

						if (this->get_terrain_height(i + 1,j) < help_height && i != this->width - 1) // east
					      al_draw_bitmap(this->tile_cliff_east,x + i * SQUARE_WIDTH + SQUARE_WIDTH - this->screen_pixel_position[0],y + j * SQUARE_HEIGHT - elevation - this->screen_pixel_position[1],0);
				      }

					if (j == 0)                                                  // draw transition to background (dark fog)
					  {
						help_y = y + j * SQUARE_HEIGHT - elevation - this->screen_pixel_position[1] - 15;

						al_draw_bitmap(this->map_shadow_north,x + i * SQUARE_WIDTH - this->screen_pixel_position[0],help_y,0);
					  
					    if (this->get_terrain_height(i - 1,j) < help_height)
						  al_draw_bitmap(this->map_shadow_north,x + (i - 1) * SQUARE_WIDTH - this->screen_pixel_position[0],help_y,0);

						if (this->get_terrain_height(i + 1,j) < help_height)
						  al_draw_bitmap(this->map_shadow_north,x + (i + 1) * SQUARE_WIDTH - this->screen_pixel_position[0],help_y,0);  
					  }
					else if (j == this->height - 1)
					  {
						al_draw_bitmap(this->map_shadow_south,x + i * SQUARE_WIDTH - this->screen_pixel_position[0],y + j * SQUARE_HEIGHT - elevation - this->screen_pixel_position[1] + 15,0);
					  }

					if (i == 0)
					  {
						help_x = x + i * SQUARE_WIDTH - this->screen_pixel_position[0] - 15;

                        al_draw_bitmap(this->map_shadow_west,help_x,y + j * SQUARE_HEIGHT - elevation - this->screen_pixel_position[1],0);
					    al_draw_bitmap(this->map_shadow_west,help_x,y + (j + 1) * SQUARE_HEIGHT - elevation - this->screen_pixel_position[1],0);
					  }
					else if (i == this->width - 1)
				      {
						help_x = x + i * SQUARE_WIDTH - this->screen_pixel_position[0] + 15; 

                        al_draw_bitmap(this->map_shadow_east,help_x,y + j * SQUARE_HEIGHT - elevation - this->screen_pixel_position[1],0);
						al_draw_bitmap(this->map_shadow_east,help_x,y + (j + 1) * SQUARE_HEIGHT - elevation - this->screen_pixel_position[1],0); 
					  }
				  } 
			  }
	      }

		for (i = 0; i < this->screen_square_end[0] + 1; i++)      // draw the same line of objects (and animations)
	      {
			if (i < 0 || i >= this->width)
			  break;

			number_of_crates = 0;
			elevator_height = 0;

			for (k = 0; k < MAX_OBJECTS_PER_SQUARE; k++)
			  if (this->squares[i][j].map_objects[k] != NULL)
			    {
				  help_x = x + i * SQUARE_WIDTH - this->screen_pixel_position[0];

                  if (this->squares[i][j].map_objects[k]->get_type() == OBJECT_CRATE)  // draw crates one on another
				    {
					  if (this->get_square_type(i,j) == SQUARE_WATER)                  // if the crate is in the water, draw it differently
					    {
					      if (number_of_crates == 0) 
					        al_draw_bitmap(this->bitmap_crate_water,help_x,y + j * SQUARE_HEIGHT - this->squares[i][j].height * ELEVATION - this->screen_pixel_position[1],0); 
					      else
						    this->squares[i][j].map_objects[k]->draw(help_x,y + j * SQUARE_HEIGHT - (this->squares[i][j].height - 1) * ELEVATION - number_of_crates * ELEVATION - this->screen_pixel_position[1]);
					    }
					  else
					    this->squares[i][j].map_objects[k]->draw(help_x,y + j * SQUARE_HEIGHT - this->squares[i][j].height * ELEVATION - number_of_crates * ELEVATION - elevator_height - this->screen_pixel_position[1]);
				    
					  number_of_crates++;
				    }
				  else                                                                 // other map object type
				    { 
					  if (this->squares[i][j].map_objects[k]->get_type() == OBJECT_ELEVATOR)
					    if (this->squares[i][j].map_objects[k]->get_state() == OBJECT_STATE_ON)
					  	  elevator_height = ELEVATION;
			        
                      this->squares[i][j].map_objects[k]->draw(help_x, y + j * SQUARE_HEIGHT - this->squares[i][j].height * ELEVATION - this->screen_pixel_position[1]);
				    }
			    }
			  else
				break;

			if (this->squares[i][j].animation != NULL)    // draw animation on the square if there is any
			  if (this->squares[i][j].animation->get_playing_animation() != NULL)
                this->squares[i][j].animation->draw(x + i * SQUARE_WIDTH - this->screen_pixel_position[0], y + j * SQUARE_HEIGHT - this->squares[i][j].height * ELEVATION - this->screen_pixel_position[1]);
			  else
			    this->squares[i][j].animation = NULL;
	      }

		for (i = 0; i < 3; i++)                        // draw players
		  if (this->player_characters[i] != NULL && this->player_characters[i]->get_square_y() == j)
		    {
			  elevation = this->get_elevation_for_character(this->player_characters[i]);

			  this->player_characters[i]->draw((int) (x + this->player_characters[i]->get_position_x() * SQUARE_WIDTH - this->screen_pixel_position[0]),
			  (int) (y + this->player_characters[i]->get_position_y() * SQUARE_HEIGHT - this->screen_pixel_position[1]) - elevation);
		    }
 
		for (i = 0; i < this->number_of_monsters; i++) // draw monsters
		  if (this->monster_characters[i] != NULL && this->monster_characters[i]->get_square_y() == j)
		    { 
			  elevation = this->get_elevation_for_character(this->monster_characters[i]);
			  
			  this->monster_characters[i]->draw((int) (x + this->monster_characters[i]->get_position_x() * SQUARE_WIDTH - this->screen_pixel_position[0]),
			    (int) (y + this->monster_characters[i]->get_position_y() * SQUARE_HEIGHT - this->screen_pixel_position[1]) - elevation);
		    }
		
		for (i = 0; i < this->number_of_missiles; i++) // draw missiles
		  if (this->missiles[i].square_y == j)
		    {
			  elevation = this->missiles[i].height * ELEVATION;
			  al_draw_bitmap(this->missiles[i].bitmap,x + (int) (this->missiles[i].position_x * SQUARE_WIDTH) - this->screen_pixel_position[0], y + (int) (this->missiles[i].position_y * SQUARE_HEIGHT) - elevation - this->screen_pixel_position[1],0); 
		    }
	  }

	for (i = 0; i < 3; i++)                            // draw portraits
	  if (this->player_characters[i] == NULL)
	    {
		  break;
	    }
	  else
	    {
		  if (i == this->current_player)
			al_draw_bitmap(this->portrait_selection,x + this->portrait_x_positions[i] - 2,y + this->portrait_y_position - 3,0);

		  // draw the energy bar:
		  al_draw_filled_rectangle(x + 38 + this->portrait_x_positions[i],y + this->portrait_y_position + 20,x + this->portrait_x_positions[i] + 38 + this->player_characters[i]->get_magic_energy() * 18,y + this->portrait_y_position + 47,al_map_rgb(197,248,252));

		  switch (this->player_characters[i]->get_player_type())
		    {
		      case PLAYER_MIA:
				al_draw_bitmap(this->portrait_mia,x + this->portrait_x_positions[i],y + this->portrait_y_position,0);
				break;
			  
			  case PLAYER_METODEJ:
				al_draw_bitmap(this->portrait_metodej,x + this->portrait_x_positions[i],y + this->portrait_y_position,0);
			    break;

			  case PLAYER_STAROVOUS:
				al_draw_bitmap(this->portrait_starovous,x + this->portrait_x_positions[i],y + this->portrait_y_position,0);
		        break; 
		    }
	    }

	switch (this->player_characters[this->current_player]->get_player_type())  // draw spell icons
	  {
		case PLAYER_MIA:
		  al_draw_bitmap(this->spell_icons[0],x + 490,y + this->portrait_y_position + 10,0);
		  al_draw_bitmap(this->spell_icons[1],x + 550,y + this->portrait_y_position + 10,0);
		  break;
			  
		case PLAYER_METODEJ: 
		  al_draw_bitmap(this->spell_icons[2],x + 490,y + this->portrait_y_position + 10,0);
		  al_draw_bitmap(this->spell_icons[3],x + 550,y + this->portrait_y_position + 10,0);
		  break;

		case PLAYER_STAROVOUS:
		  al_draw_bitmap(this->spell_icons[4],x + 490,y + this->portrait_y_position + 10,0);
		  al_draw_bitmap(this->spell_icons[5],x + 550,y + this->portrait_y_position + 10,0);
		  break; 				
	  }

	al_draw_bitmap(this->spell_icons[6],x + 610,y + this->portrait_y_position + 10,0);

	if (this->text_is_displayed)              // draw displayed text
	  {
		al_draw_filled_rectangle(this->screen_center_x - (this->textbox_size[0] / 2),this->screen_center_y - 220,this->screen_center_x + (this->textbox_size[0] / 2),this->screen_center_y - 220 + this->textbox_size[1],al_map_rgba(94,47,0,220));

		for (i = 0; i < MAX_TEXT_LINES; i++)
		  {
			al_draw_text(this->text_font,al_map_rgb(0,0,0),this->screen_center_x + 1,this->screen_center_y - 200 + al_get_font_line_height(this->text_font) * i + 1,ALLEGRO_ALIGN_CENTRE,this->text_lines[i]); // text shadow
			al_draw_text(this->text_font,al_map_rgb(255,220,220),this->screen_center_x,this->screen_center_y - 200 + al_get_font_line_height(this->text_font) * i,ALLEGRO_ALIGN_CENTRE,this->text_lines[i]);
		  }
	  }

	if (this->input_output_state->key_cast_1) // highlight pressed spells
	  {
		al_draw_filled_rectangle(x + 493,y + this->portrait_y_position + 13,x + 525,y + this->portrait_y_position + 45,al_map_rgba(150,100,100,75));
	  }

	if (this->input_output_state->key_cast_2)
	  {
		al_draw_filled_rectangle(x + 553,y + this->portrait_y_position + 13,x + 585,y + this->portrait_y_position + 45,al_map_rgba(150,100,100,75));
	  }

	if (this->input_output_state->key_cast_3)
	  {
		al_draw_filled_rectangle(x + 613,y + this->portrait_y_position + 13,x + 645,y + this->portrait_y_position + 45,al_map_rgba(150,100,100,75));
	  }
  }

//-----------------------------------------------

int c_map::get_elevation_for_character(c_character *character)
  {
	int height, x, y, i;
	double fraction_x, fraction_y;

	x = character->get_square_x();
	y = character->get_square_y();
	fraction_x = character->get_fraction_x();
	fraction_y = character->get_fraction_y();

	height = this->get_height(x,y) * ELEVATION;

	if (this->square_has_object(x,y,OBJECT_STAIRS_NORTH) && fraction_y < 0.5)
	  height += (int) ((0.5 - fraction_y) * 35);
	else if (this->square_has_object(x,y,OBJECT_STAIRS_EAST) && fraction_x > 0.5)
	  height += (int) ((fraction_x - 0.5) * 35);
	else if (this->square_has_object(x,y,OBJECT_STAIRS_SOUTH) && fraction_y > 0.5)
	  height += (int) ((fraction_y - 0.5) * 35);
	else if (this->square_has_object(x,y,OBJECT_STAIRS_WEST) && fraction_x < 0.5)
	  height += (int) ((0.5 - fraction_x) * 35);

	for (i = 0; i < MAX_OBJECTS_PER_SQUARE; i++)             // check elevator animation
	  if (this->squares[x][y].map_objects[i] != NULL)
	    {
		  if (this->squares[x][y].map_objects[i]->get_type() == OBJECT_ELEVATOR)
		    {
			  if (this->squares[x][y].map_objects[i]->is_animating())
			    {
			      if (this->squares[x][y].map_objects[i]->get_state() == OBJECT_STATE_ON)
				    {
			  	      height -= ELEVATION;
					  height += this->squares[x][y].map_objects[i]->get_animation_frame() * 7;
				    }
				  else
				    {
					  height += ELEVATION;
					  height -= this->squares[x][y].map_objects[i]->get_animation_frame() * 7;
				    }
			    }
			  else
				break;
		    }
		  else
		    break;
	    }
	  else
		break;

	return height;
  }

//-----------------------------------------------

bool c_map::character_can_move_to_square(c_character *character, t_direction direction)
  {
	int square_position[2];                // player position in map squares
	int square_position_next[2];           // next square coordinations in player's direction
	t_object_type help_object_type;        // to checks stairs
	t_object_type help_object_type2;       // to checks stairs
	int height_difference;                 // height difference between start and destination squares
	bool returned_value;
	
	if (direction == DIRECTION_NONE)
	  return true;

	square_position[0] = character->get_square_x();
	square_position[1] = character->get_square_y();

	this->next_square(square_position[0],square_position[1],direction,
	  &square_position_next[0],&square_position_next[1]);

    switch (direction)
	  {
		case DIRECTION_NORTH:
		  help_object_type = OBJECT_STAIRS_NORTH;
		  help_object_type2 = OBJECT_STAIRS_SOUTH;
		  break;

		case DIRECTION_EAST:
		  help_object_type = OBJECT_STAIRS_EAST;
		  help_object_type2 = OBJECT_STAIRS_WEST;
		  break;

		case DIRECTION_WEST:
		  help_object_type = OBJECT_STAIRS_WEST;
		  help_object_type2 = OBJECT_STAIRS_EAST;
		  break;

		case DIRECTION_SOUTH:
		  help_object_type = OBJECT_STAIRS_SOUTH;
		  help_object_type2 = OBJECT_STAIRS_NORTH;
		  break;
	  }

	if (square_position_next[0] < 0 || square_position_next[0] >= this->width ||   // check map range
	  square_position_next[1] < 0 || square_position_next[1] >= this->height)
	  return false;

	if (this->get_square_type(square_position_next[0],square_position_next[1]) == SQUARE_HOLE)  // check holes
	  return false;

	if(!this->square_is_stepable(square_position_next[0],square_position_next[1])) // check stepable objects
	  return false;

	if (!this->door_can_be_passed(square_position_next[0],square_position_next[1],direction)) // checks doors at the next square
	  return false;

	if (!this->door_can_be_passed(square_position[0],square_position[1],direction))  // check doors at given position
	  return false;

	height_difference = this->get_height(square_position[0],square_position[1]) -  // check height difference
	  this->get_height(square_position_next[0],square_position_next[1]);

	returned_value = true;

	switch (height_difference)
	  {
	    case 0:        // no difference -> OK
		  if (this->get_height(square_position[0],square_position[1]) <                  // this prevents entering to water through cliff
	        this->get_terrain_height(square_position_next[0],square_position_next[1]))
	        returned_value = false;
		  break;

		case 1:        // source square is higher
		  returned_value = this->square_has_object(square_position_next[0],square_position_next[1],help_object_type2)
			&& this->get_height(square_position_next[0],square_position_next[1]) == this->get_terrain_height(square_position_next[0],square_position_next[1]);
		  break;

		case -1:       // source square is lower
		  returned_value = this->square_has_object(square_position[0],square_position[1],help_object_type)
		    && this->get_height(square_position_next[0],square_position_next[1]) == this->get_terrain_height(square_position_next[0],square_position_next[1]); 
		  break;
		   
		default:       // can't be accesed even by stairs
		  returned_value = false;
		  break;
	  }		  

	return returned_value; 
  }

//-----------------------------------------------

bool c_map::square_has_object(int x, int y, t_object_type object_type)
  { 
	int i;

    if (x >= this->width || x < 0 || y >= this->height ||
	  y < 0)
	  return false;

	for (i = 0; i < MAX_OBJECTS_PER_SQUARE; i++)
	  if (this->squares[x][y].map_objects[i] != NULL)
	    {
		  if (this->squares[x][y].map_objects[i]->get_type() == object_type)
		    return true;
	    }
	  else
		break;

	return false;
  }

//-----------------------------------------------

bool c_map::square_is_stepable(int x, int y)
  { 
	int i;

	if (x < 0 || x >= this->width ||
		y < 0 || y >= this->height)
	  return false;

	for (i = 0; i < MAX_OBJECTS_PER_SQUARE; i++)
      if (this->squares[x][y].map_objects[i] != NULL)
	    {
		  if (!this->squares[x][y].map_objects[i]->is_stepable())
		    return false;
	    }
	  else
		break;

	return true; 
  }

//-----------------------------------------------

void c_map::update_screen_position()
  {
	int player_position[2];
	int i, player_height;

	player_position[0] = this->player_characters[this->current_player]->get_square_x();
	player_position[1] = this->player_characters[this->current_player]->get_square_y();

	for (i = 0; i < 2; i++)    // check x and y
	  if (player_position[i] < this->screen_square_position[i] + 2)
	    {
	      this->screen_square_position[i] = player_position[i] - 1;
		  this->screen_square_end[i] = this->screen_square_position[i] + this->screen_square_resolution[i];

		   if (i == 0)
			this->screen_pixel_position[i] = ((this->screen_square_position[i] - 1) * SQUARE_WIDTH) + this->player_characters[this->current_player]->get_fraction_x() * SQUARE_WIDTH;
		  else
		    {
			  this->screen_pixel_position[i] = ((this->screen_square_position[i] - 1) * SQUARE_HEIGHT) + this->player_characters[this->current_player]->get_fraction_y() * SQUARE_HEIGHT;
		    
			  player_height = this->get_height(player_position[0],player_position[1]); // check camera shift due to height

			  this->screen_pixel_position[i] -= player_height * ELEVATION;
		    }
	    }
	  else if (player_position[i] >= this->screen_square_end[i] - 3)
	    {
	      this->screen_square_position[i] += player_position[i] - (this->screen_square_end[i] - 3);
		  this->screen_square_end[i] = this->screen_square_position[i] + this->screen_square_resolution[i];

		  if (i == 0)
			this->screen_pixel_position[i] = (this->screen_square_position[i] + this->player_characters[this->current_player]->get_fraction_x()) * SQUARE_WIDTH;
		  else
			this->screen_pixel_position[i] = (this->screen_square_position[i] + this->player_characters[this->current_player]->get_fraction_y()) * SQUARE_HEIGHT;
	    }
  }

//-----------------------------------------------

void c_map::shift_screen(int x, int y)
  {
	if (x > 0 && this->screen_square_end[0] > this->width + 16) // check map borders
	  return;
	else if (x < 0 && this->screen_pixel_position[0] < - 800)
	  return;
	else if (y > 0 && this->screen_square_end[1] > this->height + 10)
	  return;
	else if (y < 0 && this->screen_pixel_position[1] < - 640)
	  return;

	this->screen_pixel_position[0] += x;
	this->screen_pixel_position[1] += y;

	this->screen_square_position[0] = this->screen_pixel_position[0] / SQUARE_WIDTH;
	this->screen_square_position[1] = this->screen_pixel_position[1] / SQUARE_HEIGHT;

	this->screen_square_end[0] = this->screen_square_position[0] + this->screen_square_resolution[0];
	this->screen_square_end[1] = this->screen_square_position[1] + this->screen_square_resolution[1];
  }

//-----------------------------------------------

void c_map::move_character(c_character *character, t_direction direction)
  {
	int square_position[2];                // player position in map squares
	double step_length;
	bool moved;

	if (direction == DIRECTION_NONE)
	  return;
	
	step_length = this->time_difference * 2;//0.026;

	if (step_length > 0.025)  // so that player can't make too long steps and go through walls etc.
	  step_length = 0.025;

	moved = false;

	square_position[0] = character->get_square_x();
	square_position[1] = character->get_square_y();

	character->set_direction(direction);
	
	if (!character->is_animating())
	  {
		character->stop_animation();
		character->loop_animation(ANIMATION_RUN);
	  }
	
	switch (direction)
	  {
	    case DIRECTION_NORTH:
		  if (this->character_can_move_to_square(character,direction)
			|| character->get_fraction_y() > CLIFF_DISTANCE_SOUTH)
		    {
			  character->move_by(0.0,-1 * step_length);
		      moved = true;
		    }
		  break;

	    case DIRECTION_EAST:
		  if (this->character_can_move_to_square(character,direction)
			|| character->get_fraction_x() < 1 - CLIFF_DISTANCE_EAST_WEST) 
		    {
			  character->move_by(step_length,0.0);
		      moved = true;
		    }
		  
		  break;

	    case DIRECTION_WEST:
		  if (this->character_can_move_to_square(character,direction)
			|| character->get_fraction_x() > CLIFF_DISTANCE_EAST_WEST) 
		    {
			  character->move_by(-1 *step_length,0.0);
		      moved = true;
		    }
		  break;

	    case DIRECTION_SOUTH:
		  if (this->character_can_move_to_square(character,direction)
	    	|| character->get_fraction_y() < 1 - CLIFF_DISTANCE_NORTH)
		    { 
			  character->move_by(0.0,step_length);
		      moved = true;
		    }
		  break;
	  }
	
	if (character->get_playing_animation() == ANIMATION_SKATE && (!moved || this->get_square_type(character->get_square_x(),character->get_square_y()) != SQUARE_ICE))
	  {
		character->stop_animation();
	  }

	// adjust the position (so the character keeps a little distance from cliffs):
	
	if (direction != DIRECTION_NORTH &&
	  this->get_terrain_height(square_position[0],square_position[1])         
	  != this->get_terrain_height(square_position[0],square_position[1] - 1)
	  && character->get_fraction_y() < CLIFF_DISTANCE_SOUTH)
	  character->move_by(0.0,0.02);
	
	if (direction != DIRECTION_EAST &&
	  this->get_terrain_height(square_position[0],square_position[1])         
	  != this->get_terrain_height(square_position[0] + 1,square_position[1])
	  && character->get_fraction_x() > 1 - CLIFF_DISTANCE_EAST_WEST)
	  character->move_by(-0.02,0.0);

	if (direction != DIRECTION_WEST &&
	  this->get_terrain_height(square_position[0],square_position[1])         
	  != this->get_terrain_height(square_position[0] - 1,square_position[1])
	  && character->get_fraction_x() < CLIFF_DISTANCE_EAST_WEST)
	  character->move_by(0.02,0.0); 
	
	// the movement's done here, now do other things

	this->check_buttons();

	if (this->get_square_type(square_position[0],square_position[1]) == SQUARE_COLLAPSE)
	  {
		if (character->get_square_x() != square_position[0] ||
		  character->get_square_y() != square_position[1])
		  if (!this->square_has_character(square_position[0],square_position[1]))
		    {
			  this->set_square_type(square_position[0],square_position[1],SQUARE_HOLE);
		      this->display_animation(DISPLAY_ANIMATION_COLLAPSE,square_position[0],square_position[1]);
		    }
	  }
  }

//-----------------------------------------------

void c_map::set_square_type(int x, int y, t_square_type type)
  {
	if (x < 0 || x >= this->width ||
	  y < 0 || y >= this->height)
	  return;

	this->squares[x][y].type = type;
  }

//-----------------------------------------------

void c_map::display_text(string text, double duration)
  {
	int i, j, position, greatest_width, lines;
	bool end;

	position = 0;     // position in the text

	greatest_width = 0;
	lines = 0;
	end = false;

	for (i = 0; i < MAX_TEXT_LINES; i++) // delete all lines
	  this->text_lines[i][0] = 0;

	for (j = 0; j < MAX_TEXT_LINES; j++) // split the string into lines
	  {
	    for (i = 0; i < MAX_TEXT_CHARACTERS_PER_LINE - 1; i++)
		  {
			if (position >= (int) (text.length()))
			  {
			    this->text_lines[j][i] = 0;
				end = true;
			    break;
			  }

			if (i >= MAX_TEXT_CHARACTERS_PER_LINE - 10 && text[position] == ' ')
			  {
				position++;
			    break;
			  }
			else
			  {
			    this->text_lines[j][i] = text[position];
			    position++;
			  }
		  }

		this->text_lines[j][i] = 0;  // terminate the string

		if (al_get_text_width(this->text_font,this->text_lines[j]) > greatest_width)
		  greatest_width = al_get_text_width(this->text_font,this->text_lines[j]);
	  
	    if (end)
		  {
			lines = j + 1;
			break;
		  }
	  }

	textbox_size[0] = greatest_width + 50;
	textbox_size[1] = lines * al_get_font_line_height(this->text_font) + 50;

    this->text_is_displayed = true;
	this->text_end_time = al_current_time() + duration;
  }

//-----------------------------------------------

void c_map::update_missiles()
  {
	int i, j;
	int help_position[2];
	bool died;
	double step_length;

	step_length = this->time_difference * 4;

	for (i = 0; i < this->number_of_missiles; i++)
	  {
		died = false;

		this->missiles[i].square_y = c_character::position_to_square(this->missiles[i].position_y,false);
		this->missiles[i].square_x = c_character::position_to_square(this->missiles[i].position_x,true);

		switch (this->missiles[i].direction)
		  {
		    case DIRECTION_NORTH:
			  missiles[i].position_y -= step_length;
			  break;

			case DIRECTION_EAST:
			  missiles[i].position_x += step_length;
			  break;

			case DIRECTION_SOUTH:
			  missiles[i].position_y += step_length;
			  break;

			case DIRECTION_WEST:
			  missiles[i].position_x -= step_length;
			  break;
		  }

		if (this->get_height(this->missiles[i].square_x,this->missiles[i].square_y) > this->missiles[i].height ||
		  this->get_terrain_height(this->missiles[i].square_x,this->missiles[i].square_y) > this->missiles[i].height)
		    died = true;
		else if (!this->square_is_stepable(this->missiles[i].square_x,this->missiles[i].square_y) &&
		  this->get_height(this->missiles[i].square_x,this->missiles[i].square_y) == this->missiles[i].height)
		  {
		    died = true;
		  }
		else if (!this->door_can_be_passed(this->missiles[i].square_x,this->missiles[i].square_y,this->missiles[i].direction)
		  && this->get_height(this->missiles[i].square_x,this->missiles[i].square_y) == this->missiles[i].height)
		  died = true;
  
		switch (this->missiles[i].type)    // check the missile effect
		  {
		    case MISSILE_MIA_1:
		  	  if (this->square_has_object(this->missiles[i].square_x,this->missiles[i].square_y,OBJECT_CRATE) &&
		        this->crate_can_be_shifted(this->missiles[i].square_x,this->missiles[i].square_y,this->missiles[i].height,this->missiles[i].direction))
			    {
				  this->shift_crate(this->missiles[i].square_x,this->missiles[i].square_y,this->missiles[i].direction);
			      died = true;
			    }

			  break;

            case MISSILE_MIA_2:
			  if (this->get_square_type(this->missiles[i].square_x,this->missiles[i].square_y) == SQUARE_HOLE &&
			    this->get_terrain_height(this->missiles[i].square_x,this->missiles[i].square_y) == this->missiles[i].height)
			    {
				  this->set_square_type(this->missiles[i].square_x,this->missiles[i].square_y,SQUARE_COLLAPSE);
			      died = true;
			    }

			  break;

			case MISSILE_METODEJ_1:
			  if (this->square_has_object(this->missiles[i].square_x,this->missiles[i].square_y,OBJECT_ICE) &&
				this->get_terrain_height(this->missiles[i].square_x,this->missiles[i].square_y) == this->missiles[i].height)
			    {
				  for (j = 0; j < MAX_OBJECTS_PER_SQUARE; j++)
					if (this->squares[this->missiles[i].square_x][this->missiles[i].square_y].map_objects[j]->get_type() == OBJECT_ICE)
					  {
					    this->remove_object(this->missiles[i].square_x,this->missiles[i].square_y,j);
						this->display_animation(DISPLAY_ANIMATION_MELT,this->missiles[i].square_x,this->missiles[i].square_y);


					  	break;
					  }

			      died = true;
			    }

			    break;

			case MISSILE_STAROVOUS_1:
			  for (j = 0; j < this->number_of_monsters; j++)
			    {
				  if (this->monster_characters[j] != NULL
					&& this->monster_characters[j]->get_monster_type() == MONSTER_GHOST
					&& this->monster_characters[j]->get_square_x() == this->missiles[i].square_x
					&& this->monster_characters[j]->get_square_y() == this->missiles[i].square_y
					&& this->get_height(this->missiles[i].square_x,this->missiles[i].square_y) == this->missiles[i].height)
				    {
				  	  this->monster_characters[j] = NULL;
					  this->display_animation(DISPLAY_ANIMATION_SHADOW_EXPLOSION,this->missiles[i].square_x,this->missiles[i].square_y);
				      died = true;
				    }
			    }

			  if (this->square_has_object(this->missiles[i].square_x,this->missiles[i].square_y,OBJECT_OREN) && // killing oren
			    this->get_height(this->missiles[i].square_x,this->missiles[i].square_y) == this->missiles[i].height)
				this->oren_destroyed = true;

			  break;

			case MISSILE_STAROVOUS_2:
			  for (j = 0; j < 3; j++)
				if (this->player_characters[j] != NULL &&
				  this->player_characters[j]->get_square_x() == this->missiles[i].square_x &&
				  this->player_characters[j]->get_square_y() == this->missiles[i].square_y &&
				  this->get_height(this->missiles[i].square_x,this->missiles[i].square_y) == this->missiles[i].height &&
				  (this->player_characters[j]->get_player_type() == PLAYER_MIA ||
				  this->player_characters[j]->get_player_type() == PLAYER_METODEJ))
				  {
					this->player_characters[j]->change_magic_energy(1);
					died = true;
					this->display_animation(DISPLAY_ANIMATION_REFRESH,this->missiles[i].square_x,this->missiles[i].square_y);
					break;
				  }

			  break;
		  }

		if (this->missiles[i].position_x < 0 ||
		  this->missiles[i].position_x > this->width ||
		  this->missiles[i].square_y < 0 ||
		  this->missiles[i].square_y > this->height)
		  died = true;

		if (died)    // remove the missile
		  {
			  if (this->missiles[i].type == MISSILE_METODEJ_1) // display explosion
			  {
				switch (this->missiles[i].direction) // find the square that the missile was before
				  {
				    case DIRECTION_NORTH:
					  help_position[0] = this->missiles[i].square_x;
					  help_position[1] = this->missiles[i].square_y + 1;
					  break;

					case DIRECTION_SOUTH:
					  help_position[0] = this->missiles[i].square_x;
					  help_position[1] = this->missiles[i].square_y - 1;
					  break;

					case DIRECTION_EAST:
					  help_position[0] = this->missiles[i].square_x - 1;
					  help_position[1] = this->missiles[i].square_y;
					  break;

					case DIRECTION_WEST:
					  help_position[0] = this->missiles[i].square_x + 1;
					  help_position[1] = this->missiles[i].square_y;
					  break;
				  }

				this->display_animation(DISPLAY_ANIMATION_EXPLOSION,help_position[0],help_position[1]);
			  }

			for (j = i + 1; j < this->number_of_missiles; j++)
			  this->missiles[j - 1] = this->missiles[j];

			this->number_of_missiles--;
		  }
	  }
  }

//-----------------------------------------------

void c_map::switch_player(int player_number)
  {
	ALLEGRO_SAMPLE_ID sample_id;

	if (this->player_characters[player_number] == NULL)
	  return;

	if (this->player_characters[this->current_player]->get_playing_animation() != ANIMATION_SKATE) // skating mustn't be stopped
	  this->player_characters[this->current_player]->stop_animation();
    
	this->current_player = player_number;
	this->update_screen_position();
	al_play_sample(this->change_player_sound,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&sample_id);
  }

//-----------------------------------------------

void c_map::check_ice()
  {
	int i;
	
	for (i = 0; i < 3; i++)
	  if (this->player_characters[i] != NULL)
	    {
		  if (this->player_characters[i]->get_playing_animation() == ANIMATION_RUN && // first step on ice
		    this->get_square_type(this->player_characters[i]->get_square_x(),this->player_characters[i]->get_square_y()) == SQUARE_ICE)
		    { 
			  this->player_characters[i]->stop_animation();
			  this->player_characters[i]->loop_animation(ANIMATION_SKATE);
			  this->move_character(this->player_characters[i],this->player_characters[i]->get_direction());
		    }
		  else if (this->player_characters[i]->get_playing_animation() == ANIMATION_SKATE) // already skating
			{
			  this->move_character(this->player_characters[i],this->player_characters[i]->get_direction());
		      
			  if (!this->input_output_state->key_map_explore)  // don't mess with the camera if exploring
			    this->update_screen_position();
		    }
		}
  }

//-----------------------------------------------

t_game_state c_map::update()
  {  
	int i, offset;
	
	this->time_difference = al_current_time() - this->time_before;
	this->time_before = al_current_time();

	if (this->text_is_displayed && this->text_end_time <= al_current_time()) // erase the text displayed
	  {
		this->text_is_displayed = false;
	  }

	if (this->check_firecloak && al_current_time() >= this->fire_cloak_end_time)   // check fire cloak time and turn it off after it's duration's over
	  {
		for (i = 0; i < 3; i++)
		  if (this->player_characters[i] != NULL && this->player_characters[i]->get_player_type() == PLAYER_METODEJ)
			this->player_characters[i]->set_fire_cloak(false);

		this->check_firecloak = false;
	  }

	this->check_ice();
	this->update_missiles();
	this->update_monsters();

	this->draw(0,0);

	this->frame_count++;

	if (al_current_time() >= this->change_flame_state)
	  {
		this->flames_on = !this->flames_on;
		this->update_flames();
		change_flame_state = al_current_time() + 3; // next change in 3 seconds
	  }

	if (this->input_output_state->key_map_explore) // moving camera
	  {
		if (this->player_characters[this->current_player]->get_playing_animation() != ANIMATION_SKATE)
		  this->player_characters[this->current_player]->stop_animation();

		offset = (int) (this->time_difference * 1024);

		if (offset == 0)
		  offset = 1;

		if (this->input_output_state->key_left)
		  this->shift_screen(-1 * offset,0);
		else if (this->input_output_state->key_right)
		  this->shift_screen(offset,0);
		else if (this->input_output_state->key_up)
		  this->shift_screen(0,-1 * offset);
		else if (this->input_output_state->key_down)
		  this->shift_screen(0,offset);
	  }
	else if (this->player_characters[this->current_player]->get_playing_animation() != ANIMATION_SKATE) // moving player
	  {
		if (this->input_output_state->key_left)  
		  {
		    this->move_character(this->player_characters[this->current_player],DIRECTION_WEST);
		    this->update_screen_position();
		  }
		else if (this->input_output_state->key_right)
		  {
		    this->move_character(this->player_characters[this->current_player],DIRECTION_EAST);
		    this->update_screen_position();
		  }
		else if (this->input_output_state->key_down)
		  {
		    this->move_character(this->player_characters[this->current_player],DIRECTION_SOUTH);
		    this->update_screen_position();
		  }
		else if (this->input_output_state->key_up)
		  {
		    this->move_character(this->player_characters[this->current_player],DIRECTION_NORTH);
		    this->update_screen_position();
		  }
		else if (this->player_characters[this->current_player]->get_playing_animation() != ANIMATION_USE
		  && this->player_characters[this->current_player]->get_playing_animation() != ANIMATION_CAST)
		  {
			this->player_characters[this->current_player]->stop_animation();
		  }
	  }

	  if (this->input_output_state->key_1)     // switching players with keyboard
	    {
		  if (!this->pressed_1)
		    this->switch_player(0);

		  this->pressed_1 = true;
	    }
	  else
	    {
	  	  this->pressed_1 = false;
	    }
	  
	  if (this->input_output_state->key_2)
	    {
		  if (!this->pressed_2)
		    this->switch_player(1);

		  this->pressed_2 = true;
	    }
	  else
	    {
	  	  this->pressed_2 = false;
	    }
	  
	  if (this->input_output_state->key_3)
	    {
		  if (!this->pressed_3)
		    this->switch_player(2);  
		  
		  this->pressed_3 = true;
	    }
	  else
	    {
	  	  this->pressed_3 = false;
	    }

	if (this->input_output_state->key_use)
	  {
		this->use_key_press();
	  }
	  
	if (this->input_output_state->key_cast_1)
	  {
		this->cast_key_press(0);
	  }
	else if (this->input_output_state->key_cast_2)
	  {
		this->cast_key_press(1);
	  }
	else if (this->input_output_state->key_cast_3)
	  {
		this->cast_key_press(2);
	  }

	return this->check_game_state();
  }

//-----------------------------------------------

t_game_state c_map::check_game_state()
  {
	int i, j;
	bool won;
	int player_position[2];

	won = true; // assume victory

	if (this->input_output_state->key_back)
	  return GAME_STATE_PAUSE;

	if (this->oren_destroyed)
	  return GAME_STATE_WIN;

	for (i = 0; i < 3; i++)
	  if (this->player_characters[i] != NULL)
	    {
		  player_position[0] = this->player_characters[i]->get_square_x();
		  player_position[1] = this->player_characters[i]->get_square_y();

		  if (won && !this->square_has_object(this->player_characters[i]->get_square_x(),this->player_characters[i]->get_square_y(),OBJECT_GATE))
			won = false;

		  // check monsters:
		  for (j = 0; j < this->number_of_monsters; j++)
			if (this->monster_characters[j] != NULL &&
			  this->monster_characters[j]->get_square_x() == player_position[0] &&
			  this->monster_characters[j]->get_square_y() == player_position[1])
			  return GAME_STATE_LOSE;
		  
		  // check flames:
		  for (j = 0; j < MAX_OBJECTS_PER_SQUARE; j++)
			if ( this->squares[player_position[0]][player_position[1]].map_objects[j] != NULL &&
			  this->squares[player_position[0]][player_position[1]].map_objects[j]->get_type() == OBJECT_FLAMES &&
			  this->squares[player_position[0]][player_position[1]].map_objects[j]->get_state() == OBJECT_STATE_ON_ACTIVE &&
			  !this->player_characters[i]->fire_cloak_is_on())
			  return GAME_STATE_LOSE;
	    }

	return won ? GAME_STATE_WIN : GAME_STATE_PLAYING;
  }

//-----------------------------------------------

void c_map::fire_missile(int spell_number)
  {
	c_player_character *help_character;

	if (this->number_of_missiles >= MAX_MISSILES_ON_MAP)
	  return;

	help_character = this->player_characters[this->current_player];

	switch(help_character->get_player_type())
	  {
	    case PLAYER_MIA:
		  if (spell_number == 0)
		    {
			  this->missiles[this->number_of_missiles].type = MISSILE_MIA_1;
			  this->missiles[this->number_of_missiles].bitmap = this->spell_mia_1[0];
		    }
		  else
		    {
              this->missiles[this->number_of_missiles].type = MISSILE_MIA_2;
		      this->missiles[this->number_of_missiles].bitmap = this->spell_mia_2[0];
		    }

		  break;

		case PLAYER_METODEJ:
		  this->missiles[this->number_of_missiles].type = MISSILE_METODEJ_1;
		  this->missiles[this->number_of_missiles].bitmap = this->spell_metodej_1[0];
		  break;

	    case PLAYER_STAROVOUS:
		  if (spell_number == 0)
		    {
			  this->missiles[this->number_of_missiles].type = MISSILE_STAROVOUS_1;
		      this->missiles[this->number_of_missiles].bitmap = this->spell_starovous_1[0];
		    }
		  else
		    {
              this->missiles[this->number_of_missiles].type = MISSILE_STAROVOUS_2;
		      this->missiles[this->number_of_missiles].bitmap = this->spell_starovous_2[0];
		    }
		  break;
	  }

	this->missiles[this->number_of_missiles].direction = help_character->get_direction();
	this->missiles[this->number_of_missiles].position_x = help_character->get_position_x();
	this->missiles[this->number_of_missiles].position_y = help_character->get_position_y();
	this->missiles[this->number_of_missiles].square_y = help_character->get_square_y();
	this->missiles[this->number_of_missiles].square_x = help_character->get_square_x();
	this->missiles[this->number_of_missiles].height = this->get_height(help_character->get_square_x(),help_character->get_square_y());
  
	this->number_of_missiles++;
  }

//-----------------------------------------------

void c_map::cast_key_press(int spell_number)
  {
	ALLEGRO_SAMPLE_ID sample_id;
	int i, x, y;
	c_player_character *helping_player, *target_player;

	if (this->player_characters[this->current_player]->get_magic_energy() == 0)
	  return;                  // no magic energy

	if (this->player_characters[this->current_player]->get_playing_animation() == ANIMATION_SKATE) // can't cast while skating
	  return;

	if (this->player_characters[this->current_player]->get_playing_animation() == ANIMATION_CAST ||
	  this->player_characters[this->current_player]->get_playing_animation() == ANIMATION_USE)
	  return;

	if (spell_number == 0 || spell_number == 1)
	  {
	    this->player_characters[this->current_player]->change_magic_energy(-1);

	    switch(this->player_characters[this->current_player]->get_player_type()) // play the cast sound
	      {
	        case PLAYER_MIA:
		      al_play_sample(this->spell_sounds_mia[spell_number],0.5,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&sample_id);			
		  	  this->fire_missile(spell_number);
			  break;

		    case PLAYER_METODEJ:
			  if (spell_number == 0)
			    {
			      al_play_sample(this->spell_sounds_metodej[spell_number],0.5,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&sample_id);
		          this->fire_missile(spell_number);
			    }
			  else
			    { 
				  this->player_characters[this->current_player]->set_fire_cloak(false);
				  this->player_characters[this->current_player]->set_fire_cloak(true);
				  this->fire_cloak_end_time = al_current_time() + FIRE_CLOAK_DURATION;
				  this->check_firecloak = true;
			    }

			  break;

		    case PLAYER_STAROVOUS:
			  al_play_sample(this->spell_sounds_starovous[spell_number],0.5,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&sample_id);
		      this->fire_missile(spell_number);
			  break;
	      }
	  }
	else if (spell_number == 2) // teleport spell
	  {
		helping_player = NULL;  // player that helps summon the other player
		target_player = NULL;   // player being summoned

		x = this->player_characters[this->current_player]->get_square_x();
		y = this->player_characters[this->current_player]->get_square_y();

		for (i = 0; i < 3; i++)
		  if (i != this->current_player && this->player_characters[i] != NULL)
		    {
			  if (this->player_characters[i]->get_square_x() == x && this->player_characters[i]->get_square_y() == y)
				helping_player = this->player_characters[i];
			  else
				target_player = this->player_characters[i];
		    }

		  if (helping_player != NULL && target_player != NULL)
		    {
			  helping_player->change_magic_energy(-1);
			  helping_player->play_animation(ANIMATION_CAST);
			  this->player_characters[this->current_player]->change_magic_energy(-1);
			  target_player->set_position(x + 0.1,y - 0.8);
			  this->display_animation(DISPLAY_ANIMATION_TELEPORT,x,y);
		    }
	  }

	this->player_characters[this->current_player]->play_animation(ANIMATION_CAST);
  }

//-----------------------------------------------

void c_map::update_flames()
  {
	int i, j, k;

	for (j = 0; j < this->height; j++)
      for (i = 0; i < this->width; i++)
		for (k = 0; k < MAX_OBJECTS_PER_SQUARE; k++)
		  if (this->squares[i][j].map_objects[k] == NULL)
		    {
			  break;
		    }
		  else
		    { 
			  if (this->squares[i][j].map_objects[k]->get_type() == OBJECT_FLAMES)
			    {
				  if (this->squares[i][j].map_objects[k]->get_state() == OBJECT_STATE_ON ||
				    this->squares[i][j].map_objects[k]->get_state() == OBJECT_STATE_ON_ACTIVE)
			        {
				      if (this->flames_on)
				        {
				          this->squares[i][j].map_objects[k]->set_state(OBJECT_STATE_ON_ACTIVE);
					      this->squares[i][j].map_objects[k]->loop_animation(ANIMATION_IDLE);
				        }
				      else
				        {
					      this->squares[i][j].map_objects[k]->set_state(OBJECT_STATE_ON);
					      this->squares[i][j].map_objects[k]->stop_animation();
				        }
				    }
				  else
				    {
					  this->squares[i][j].map_objects[k]->stop_animation();
				    }
			    }
		    }
  }

//-----------------------------------------------

void c_map::use_key_press()
{ 
	int i;
	int facing_square[2];  // coordinations of the square the player is facing
	int coordinations[2];
	c_map_object *help_object;

	coordinations[0] = this->player_characters[this->current_player]->get_square_x();
    coordinations[1] = this->player_characters[this->current_player]->get_square_y();

	this->next_square(coordinations[0],coordinations[1],
	  this->player_characters[this->current_player]->get_direction(),
	  &facing_square[0],&facing_square[1]);

	if (this->square_has_object(coordinations[0],coordinations[1],OBJECT_TELEPORT_INPUT)) // check teleport
	  this->check_teleport();

	if (facing_square[0] >= 0 && facing_square[0] < this->width &&
      facing_square[1] >= 0 && facing_square[1] < this->height)
	    for (i = 0; i < MAX_OBJECTS_PER_SQUARE; i++)
	      {
		    help_object = this->squares[facing_square[0]][facing_square[1]].map_objects[i];

	        if (help_object != NULL)
	          {
		         if (help_object->get_type() == OBJECT_CRATE)
		           {
				     if (this->crate_can_be_shifted(facing_square[0],facing_square[1],this->get_height(coordinations[0],coordinations[1]),this->player_characters[this->current_player]->get_direction()))
			           {  
				         this->shift_crate(facing_square[0],facing_square[1],this->player_characters[this->current_player]->get_direction());
		                 this->player_characters[this->current_player]->play_animation(ANIMATION_CAST);
			           }
		           }
		         
				 if (this->get_height(facing_square[0],facing_square[1]) != this->get_height(coordinations[0],coordinations[1]))  // so that player can't use objects at different height levels
	               continue;
				 
				 if (help_object->get_type() == OBJECT_LEVER && !help_object->is_animating())
		           {
			         this->player_characters[this->current_player]->play_animation(ANIMATION_USE);

			     	 if (this->object_can_be_used(help_object))
			           help_object->use();
		           }
			     else if (help_object->get_type() == OBJECT_FOUNTAIN)
			       {
			     	 this->player_characters[this->current_player]->change_magic_energy(1);
			     	 this->display_animation(DISPLAY_ANIMATION_REFRESH,coordinations[0],coordinations[1]);
			       }
			     else if (help_object->get_type() == OBJECT_SIGN)
			       {
			     	 this->display_text(help_object->get_sign_text(),10);
			       }
			     else if (help_object->get_type() == OBJECT_KEY_RED || help_object->get_type() == OBJECT_KEY_GREEN || help_object->get_type() == OBJECT_KEY_BLUE)
			       {
			     	 this->remove_object(facing_square[0],facing_square[1],i);
					 this->display_animation(DISPLAY_ANIMATION_REFRESH,facing_square[0],facing_square[1]);
			       }
	           }
		     else
	           break;
	       }
  }

//-----------------------------------------------

void c_map::check_teleport()
  {
	int i, j, x, y;
	int position[2];
	c_map_object *help_object;

	position[0] = this->player_characters[this->current_player]->get_square_x();
	position[1] = this->player_characters[this->current_player]->get_square_y();

	for (i = 0; i < MAX_OBJECTS_PER_SQUARE; i++)
	  if (this->squares[position[0]][position[1]].map_objects[i] == NULL)
		break;
	  else if (this->squares[position[0]][position[1]].map_objects[i]->get_type() == OBJECT_TELEPORT_INPUT)
	    {
		  help_object = this->squares[position[0]][position[1]].map_objects[i]->get_controlled_object(0);

		  if (help_object == NULL)
			break;

		  for (y = 0; y < this->height; y++)  // find the output teleport
		    for (x = 0; x < this->width; x++)
			  for (j = 0; j < MAX_OBJECTS_PER_SQUARE; j++)
			    if (this->squares[x][y].map_objects[j] == NULL)
				  break;
				else if (this->squares[x][y].map_objects[j] == help_object && !this->square_has_object(x,y,OBJECT_CRATE))
				  {
					this->player_characters[this->current_player]->set_position(x + 0.1,y - 0.5);
					this->display_animation(DISPLAY_ANIMATION_TELEPORT,x,y);
					this->display_animation(DISPLAY_ANIMATION_TELEPORT,position[0],position[1]);
					this->update_screen_position();
				    break;
				  }

		  break;
	    }
  }
//-----------------------------------------------

 bool c_map::door_can_be_passed(int x, int y, t_direction direction)
   {
	  int i;

	  if (x < 0 || x >= this->width || y < 0 || y > this->height)
		return true;

	  for (i = 0; i < MAX_OBJECTS_PER_SQUARE; i++)
		if (this->squares[x][y].map_objects[i] == NULL)
		  return true;
		else if (this->squares[x][y].map_objects[i]->get_type() == OBJECT_DOOR_HORIZONTAL)
		  {
			return (this->squares[x][y].map_objects[i]->get_state() != OBJECT_STATE_OFF &&
			  direction != DIRECTION_EAST && direction != DIRECTION_WEST);
		  }
	    else if (this->squares[x][y].map_objects[i]->get_type() == OBJECT_DOOR_VERTICAL)
		  {
			return (this->squares[x][y].map_objects[i]->get_state() != OBJECT_STATE_OFF &&
			  direction != DIRECTION_NORTH && direction != DIRECTION_SOUTH);
		  }

	  return true;
   }

//-----------------------------------------------

string c_map::get_music_name()
  {
	return this->music_name;
  }

//-----------------------------------------------