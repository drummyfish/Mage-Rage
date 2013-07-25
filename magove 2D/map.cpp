/**
 * Map class implementation.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
 */

#include "map.h"
#include "map_object.h"

//-----------------------------------------------

int c_map::get_height(int x, int y)
  {
	if (x > this->width || x < 0 ||
	  y > this->height || y < 0)
	  return 0;

	return this->squares[x][y].height;
  }

//-----------------------------------------------

t_square_type c_map::get_square_type(int x, int y)
  {
	if (x > this->width || x < 0 || y > this->height || y < 0)
	  return SQUARE_NORMAL;

	return this->squares[x][y].type;
  }

//-----------------------------------------------

void c_map::set_environment(t_environment new_environment)
  {
	string help_string;

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

	
  }

//-----------------------------------------------

c_map::c_map(string filename, t_input_state *input_state)
  {
    this->current_player = 0;
	this->animation_frame = 0;
	this->time_before = 0.0;
    this->input_state = input_state;
	this->load_from_file(filename);
	this->set_environment(ENVIRONMENT_SNOW);
	
	this->portrait_mia = al_load_bitmap("resources/portrait_mia.png");
	this->portrait_metodej = al_load_bitmap("resources/portrait_metodej.png");
	this->portrait_starovous = al_load_bitmap("resources/portrait_starovous.png");
	this->portrait_selection = al_load_bitmap("resources/selection.png");
  }

//-----------------------------------------------

void c_map::add_map_object(c_map_object *map_object, int x, int y)
  {
	int i;

	for (i = 0; i < MAX_OBJECTS_PER_SQUARE; i++)       // find the first free place for the object
	  if (this->squares[x][y].map_objects[i] == NULL)
	    {
		  this->squares[x][y].map_objects[i] = map_object;
	      break;
	    }
  }

//-----------------------------------------------

bool c_map::load_from_file(string filename)
  { // TEMPORARY CODE!!!!!!!!!!!!!
	int i, j, k;
	int button_positions[512][2];        // buffer to hold button positions

	this->width = 10;
	this->height = 10;

	this->set_environment(ENVIRONMENT_GRASS);

	for (j = 0; j < this->height; j++)
	  for (i = 0; i < this->width; i++)
	    {
		  this->squares[i][j].height = 0;
		  this->squares[i][j].type = SQUARE_NORMAL;
		  this->squares[i][j].height = NULL;

		  for (k = 0; k < MAX_OBJECTS_PER_SQUARE; k++)
		    this->squares[i][j].map_objects[k] = NULL;
	    }

	this->squares[0][0].height = 0;
	this->squares[1][0].height = 1;
	this->squares[2][0].height = 2;
	this->squares[2][1].height = 1;
	this->squares[3][0].height = 1;
	this->squares[6][2].height = 2;
	this->squares[5][2].height = 2;
	this->squares[4][2].height = 2;
	this->squares[5][3].height = 1;
	this->squares[5][4].height = 1;
	this->squares[5][5].height = 1;
	this->squares[4][3].height = 1;
	this->squares[0][5].height = 2;
	this->squares[0][6].height = 2;
	this->squares[1][6].height = 2;
	this->squares[7][7].type = SQUARE_WATER;
	this->squares[6][7].type = SQUARE_WATER;
	this->squares[7][6].type = SQUARE_WATER;
	this->squares[7][7].height = 2;
	this->squares[7][6].height = 2;

	this->squares[2][5].height = 1;

	this->tile = NULL;
	this->tile_cliff_south_1 = NULL;
	this->tile_cliff_south_2 = NULL;
	this->tile_cliff_southwest_1 = NULL;
	this->tile_cliff_southwest_2 = NULL;
	this->tile_cliff_southeast_1 = NULL;
	this->tile_cliff_southeast_2 = NULL;
	this->tile_cliff_west = NULL;
	this->tile_cliff_east = NULL;
	this->tile_cliff_north = NULL;
	this->tile_cliff_northwest = NULL;
	this->tile_cliff_northeast = NULL;
	this->tile_edge = NULL;

	for (i = 0; i < 5; i++)
	  this->tile_water[i] = NULL;

	this->player_characters[0] = new c_player_character(PLAYER_STAROVOUS);
	this->player_characters[1] = new c_player_character(PLAYER_MIA);
	this->player_characters[2] = new c_player_character(PLAYER_METODEJ);

	this->player_characters[0]->set_position(8.0,8.0);
	this->player_characters[1]->set_position(6.0,8.0);
	this->player_characters[2]->set_position(4.0,8.0);

	this->add_map_object(new c_map_object(OBJECT_CRATE,0),5,5);
	this->add_map_object(new c_map_object(OBJECT_STAIRS_EAST,0),3,3);
	
	c_map_object *aaa = new c_map_object(OBJECT_DOOR_HORIZONTAL,1);
	this->add_map_object(aaa,3,7);

	this->add_map_object(new c_map_object(OBJECT_LEVER,1),2,7);
	this->add_map_object(new c_map_object(OBJECT_BUTTON,1),9,9);

	this->add_map_object(new c_map_object(OBJECT_DOOR_VERTICAL,1),4,8);

	this->link_objects();

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

	return true;
  }

//-----------------------------------------------

c_map::~c_map()
  {
  }

//-----------------------------------------------

void c_map::shift_crate(int x, int y, t_direction direction)
  {
  }

//-----------------------------------------------

void c_map::check_buttons(long int global_time)
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
		  {
		    nuber_of_objects = 0;

	        for (j = 0; j < MAX_OBJECTS_PER_SQUARE; j++)
	          {
		        help_object = this->squares[this->button_positions_x[i]][this->button_positions_y[i]].map_objects[j];

		        if (help_object != NULL)
		          {
			        nuber_of_objects++;
		          }
		        else
		          break;
	          }

			if (nuber_of_objects > 1)  // if there are more objects than just the button
			  is_pressed = true;
		  }

		for (j = 0; j < MAX_OBJECTS_PER_SQUARE; j++) // find the button and do actions
		  {
			help_object = this->squares[this->button_positions_x[i]][this->button_positions_y[i]].map_objects[j];
		  
		    if (help_object != NULL && help_object->get_type() == OBJECT_BUTTON)
			  {
                if (is_pressed)
				  {
					if (help_object->get_state() == OBJECT_STATE_OFF)
					  help_object->switch_state(global_time);
				  }
				else
				  {
					if (help_object->get_state() == OBJECT_STATE_ON)
					  help_object->switch_state(global_time);
				  }
			  }
		  }
      }
}

//-----------------------------------------------

bool c_map::crate_can_be_shifted(int x, int y, t_direction direction)
  {
	return true;
  }

//-----------------------------------------------

void c_map::link_objects()
  {
	int i, j, k, l, m, n;
	c_map_object *help_object, *help_object2;
	c_map_object *object_array[256];            // buffer to temporarily hold object
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
						      help_object->get_link_id() == help_object2->get_link_id())
							  {
								object_array[array_length] = help_object2;
								array_length++;
							  }
						  }
						else
						  break;
					  }

			    help_object->add_controlled_objects(array_length,object_array);
		      }
		    else
		      break;
		}
  }

//-----------------------------------------------

void c_map::update_map_object_states(long int global_time)
  {
  }

//-----------------------------------------------

void c_map::draw(int x, int y, long int global_time)
  { 
	int i, j, k, help_height, elevation;

	
	al_clear_to_color(al_map_rgb(0,0,0));      // clear the screen
	this->animation_frame = global_time / 32;

	for (j = 0; j < this->height; j++)                         // go through lines
	  {
        for (help_height = 0; help_height < 3; help_height++)  // go through all 3 heights
	      {
			elevation = help_height * 27;
				
			for (i = 0; i < this->height; i++)                 // go through columns
			  { 
				if (this->squares[i][j].height == help_height)
		          { 
			        switch (this->squares[i][j].type)
			          {
			            case SQUARE_NORMAL:                      // normal square
					      al_draw_bitmap(this->tile,x + i * 64,y + j * 50 - elevation,0); // draw floor
					      break;

				        case SQUARE_WATER:      // water
					      al_draw_bitmap(this->tile_water[this->animation_frame % 5],x + i * 64,y + j * 50 - elevation,0);
			          
					      if (this->get_square_type(i,j - 1) != SQUARE_WATER   // north border
						    || this->get_height(i,j - 1) != help_height)     
                            al_draw_bitmap(this->tile_edge,x + i * 64,y + j * 50 - elevation,0);

					      if (this->get_square_type(i + 1,j) != SQUARE_WATER   // east border
						    || this->get_height(i + 1,j) != help_height)
                            al_draw_bitmap(this->tile_cliff_west,x + i * 64 + 54,y + j * 50 - elevation,0);

					      if (this->get_square_type(i - 1,j) != SQUARE_WATER   // west border
						    || this->get_height(i - 1,j) != help_height)
                            al_draw_bitmap(this->tile_cliff_east,x + i * 64,y + j * 50 - elevation,0);

					      if (this->get_square_type(i,j + 1) != SQUARE_WATER   // south border
						    || this->get_height(i,j + 1) != help_height)
                            al_draw_bitmap(this->tile_cliff_north,x + i * 64,y + j * 50 - elevation + 40,0);
					      
						  break;
					  }
					
			        if (help_height != 3)                                                    // draw south cliffs
				      {
				        if (this->get_height(i,j - 1) == help_height + 1)                    // south
					      {
				  	        al_draw_bitmap(this->tile_cliff_south_1,x + i * 64,y + j * 50 - elevation - 27,0);
				      
					        if (this->get_height(i + 1,j - 1) != this->get_height(i,j - 1))  // southeast 1
						      al_draw_bitmap(this->tile_cliff_southeast_1,x + i * 64 + 64,y + j * 50 - elevation - 27,0);
				    
					        if (this->get_height(i - 1,j - 1) != this->get_height(i,j - 1))  // southwest 1
					          al_draw_bitmap(this->tile_cliff_southwest_1,x + i * 64 - 10,y + j * 50 - elevation - 27,0);
					      }
				        else if (this->get_height(i,j - 1) == help_height + 2)
					      {
					        al_draw_bitmap(this->tile_cliff_south_2,x + i * 64,y + j * 50 - elevation - 54,0);

					        if (this->get_height(i + 1,j - 1) != this->get_height(i,j - 1))  // southeast 2
						      al_draw_bitmap(this->tile_cliff_southeast_2,x + i * 64 + 64,y + j * 50 - elevation - 54,0);
				    
					        if (this->get_height(i - 1,j - 1) != this->get_height(i,j - 1))  // southwest 2
						      al_draw_bitmap(this->tile_cliff_southwest_2,x + i * 64 - 10,y + j * 50 - elevation - 54,0);
					      }
				      }
					  
				    if (help_height != 0)                                                  // draw other cliffs
				      {
				        if (this->get_height(i,j - 1) < help_height)                       // north
					      {
					        al_draw_bitmap(this->tile_cliff_north,x + i * 64,y + j * 50 - elevation - 10,0);
				    
					        if (this->get_height(i + 1,j - 1) != help_height &&
						      this->get_height(i + 1,j) != help_height)                    // northeast
						     al_draw_bitmap(this->tile_cliff_northeast,x + i * 64 + 64,y + j * 50 - elevation - 10,0);

					        if (this->get_height(i - 1,j - 1) != help_height &&
						      this->get_height(i - 1,j) != help_height)                    // northwest
						      al_draw_bitmap(this->tile_cliff_northwest,x + i * 64 -10,y + j * 50 - elevation - 10,0);
					      }

				        if (this->get_height(i - 1,j) < help_height)                       // west
					      al_draw_bitmap(this->tile_cliff_west,x + i * 64 - 10,y + j * 50 - elevation,0);

				        if (this->get_height(i + 1,j) < help_height)                       // east
					      al_draw_bitmap(this->tile_cliff_east,x + i * 64 + 64,y + j * 50 - elevation,0);
		        
				      } 
				  } 
			  }
	      }

		for (i = 0; i < this->width; i++)      // draw the same line of objects
	      {
			for (k = 0; k < MAX_OBJECTS_PER_SQUARE; k++)
			  if (this->squares[i][j].map_objects[k] != NULL)
				this->squares[i][j].map_objects[k]->draw(x + i * 64, y + j * 50 - this->squares[i][j].height * 27,global_time);
			  else
				break;
	      }

		for (i = 0; i < 3; i++)                // draw players
		  if (this->player_characters[i] != NULL && this->player_characters[i]->get_square_y() == j)
		    {
			  elevation = this->get_elevation_for_character(this->player_characters[i]);

			  this->player_characters[i]->draw((int) (x + this->player_characters[i]->get_position_x() * 64),
			  (int) (y + this->player_characters[i]->get_position_y() * 50) - elevation,global_time);
		    }
	  }
/*
	for (i = 0; i < 3; i++)                                 // draw portraits
	  if (this->player_characters[i] != NULL)
		{
		  if (this->current_player == i)
            al_draw_bitmap(this->portrait_selection,8 + i * 150,7,0);

			switch (this->player_characters[i]->get_player_type())            
			  {
			    case PLAYER_MIA:
                  al_draw_bitmap(this->portrait_mia,10 + i * 150,10,0);
			      break;

				case PLAYER_METODEJ:
                  al_draw_bitmap(this->portrait_metodej,10 + i * 150,10,0);
			      break;

				case PLAYER_STAROVOUS:
                  al_draw_bitmap(this->portrait_starovous,10 + i * 150,10,0);
			      break;
			  }		
		}  */
  }

//-----------------------------------------------

int c_map::get_elevation_for_character(c_character *character)
  {
	int height, x, y;
	double fraction_x, fraction_y;

	x = character->get_square_x();
	y = character->get_square_y();
	fraction_x = character->get_fraction_x();
	fraction_y = character->get_fraction_y();

	height = this->get_height(x,y) * 27;

	if (this->square_has_object(x,y,OBJECT_STAIRS_NORTH) && fraction_y < 0.5)
	  height += (int) ((0.5 - fraction_y) * 35);
	else if (this->square_has_object(x,y,OBJECT_STAIRS_EAST) && fraction_x > 0.5)
	  height += (int) ((fraction_x - 0.5) * 35);
	else if (this->square_has_object(x,y,OBJECT_STAIRS_SOUTH) && fraction_y > 0.5)
	  height += (int) ((fraction_y - 0.5) * 35);
	else if (this->square_has_object(x,y,OBJECT_STAIRS_WEST) && fraction_x < 0.5)
	  height += (int) ((0.5 - fraction_x) * 35);

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

	square_position[0] = character->get_square_x();
	square_position[1] = character->get_square_y();

    switch (direction)
	  {
		case DIRECTION_NORTH:
          square_position_next[0] = square_position[0];
          square_position_next[1] = square_position[1] - 1;
		  help_object_type = OBJECT_STAIRS_NORTH;
		  help_object_type2 = OBJECT_STAIRS_SOUTH;
		  break;

		case DIRECTION_EAST:
          square_position_next[0] = square_position[0] + 1;
          square_position_next[1] = square_position[1];
		  help_object_type = OBJECT_STAIRS_EAST;
		  help_object_type2 = OBJECT_STAIRS_WEST;
		  break;

		case DIRECTION_WEST:
          square_position_next[0] = square_position[0] - 1;
          square_position_next[1] = square_position[1];
		  help_object_type = OBJECT_STAIRS_WEST;
		  help_object_type2 = OBJECT_STAIRS_EAST;
		  break;

		case DIRECTION_SOUTH:
          square_position_next[0] = square_position[0];
          square_position_next[1] = square_position[1] + 1;
		  help_object_type = OBJECT_STAIRS_SOUTH;
		  help_object_type2 = OBJECT_STAIRS_NORTH;
		  break;
	  }

	if (square_position_next[0] < 0 || square_position_next[0] >= this->width ||   // check map range
	  square_position_next[1] < 0 || square_position_next[1] >= this->height)
	  return false;

	if(!this->square_is_stepable(square_position_next[0],square_position_next[1])) // check stepable objects
	  return false;

	height_difference = this->get_height(square_position[0],square_position[1]) -  // check terrain height differences
	  this->get_height(square_position_next[0],square_position_next[1]);

	switch (height_difference)
	  {
	    case 0:        // no difference -> OK
		  return true;
		  break;

		case 1:        // source square is higher
		  return this->square_has_object(square_position_next[0],square_position_next[1],help_object_type2);
		  break;

		case -1:       // source square is lower  
			return this->square_has_object(square_position[0],square_position[1],help_object_type); 
		  break;
		   
		default:       // can't be accesed even by stairs
		  return false;
		  break;
	  }		  

	return true; 
  }

//-----------------------------------------------

bool c_map::square_has_object(int x, int y, t_object_type object_type)
  { 
	int i;

    if (x > this->width || x < 0 || y > this->height ||
	  this->height < 0)
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

void c_map::move_character(c_character *character, t_direction direction, long int global_time)
  {
	int square_position[2];                // player position in map squares
	int i;
	double step_length;
	c_map_object *help_object;

	step_length = 0.026;

	square_position[0] = character->get_square_x();
	square_position[1] = character->get_square_y();

	character->set_direction(direction);
	
	if (!character->is_animating())
	  {
		character->stop_animation();
		character->loop_animation(ANIMATION_RUN,global_time);
	  }

	switch (direction)
	  {
	    case DIRECTION_NORTH:
		  if (character_can_move_to_square(character,direction)
			|| character->get_fraction_y() > CLIFF_DISTANCE_SOUTH) 
			character->move_by(0.0,-1 * step_length);
		  break;

	    case DIRECTION_EAST:
		  if (character_can_move_to_square(character,direction)
			|| character->get_fraction_x() < 1 - CLIFF_DISTANCE_EAST_WEST) 
			character->move_by(step_length,0.0);
		  break;

	    case DIRECTION_WEST:
		  if (character_can_move_to_square(character,direction)
			|| character->get_fraction_x() > CLIFF_DISTANCE_EAST_WEST) 
			character->move_by(-1 *step_length,0.0);
		  break;

	    case DIRECTION_SOUTH:
		  if (character_can_move_to_square(character,direction)
			|| character->get_fraction_y() < 1 - CLIFF_DISTANCE_NORTH) 
			character->move_by(0.0,step_length);
		  break;
	  }

	// adjust the position (so the character keeps a little distance from cliffs):
	
	if (direction != DIRECTION_NORTH &&
	  this->get_height(square_position[0],square_position[1])         
	  != this->get_height(square_position[0],square_position[1] - 1)
	  && character->get_fraction_y() < CLIFF_DISTANCE_SOUTH)
	  character->move_by(0.0,0.02);
	
	if (direction != DIRECTION_EAST &&
	  this->get_height(square_position[0],square_position[1])         
	  != this->get_height(square_position[0] + 1,square_position[1])
	  && character->get_fraction_x() > 1 - CLIFF_DISTANCE_EAST_WEST)
	  character->move_by(-0.02,0.0);

	if (direction != DIRECTION_WEST &&
	  this->get_height(square_position[0],square_position[1])         
	  != this->get_height(square_position[0] - 1,square_position[1])
	  && character->get_fraction_x() < CLIFF_DISTANCE_EAST_WEST)
	  character->move_by(0.02,0.0); 
	
	// the movement's done, now handle interaction with objects

	square_position[0] = character->get_square_x();
	square_position[1] = character->get_square_y();

	this->check_buttons(global_time);
  }

//-----------------------------------------------

void c_map::update(long int global_time)
  {
	this->time_difference = al_current_time() - this->time_before;

	this->draw(50,75,global_time);
	
	if (this->input_state->key_left)
	  this->move_character(this->player_characters[this->current_player],DIRECTION_WEST,global_time);
	else if (this->input_state->key_right)
	  this->move_character(this->player_characters[this->current_player],DIRECTION_EAST,global_time);
	else if (this->input_state->key_down)
	  this->move_character(this->player_characters[this->current_player],DIRECTION_SOUTH,global_time);
	else if (this->input_state->key_up)
	  this->move_character(this->player_characters[this->current_player],DIRECTION_NORTH,global_time);
	else
	  {
		this->player_characters[this->current_player]->stop_animation();
		this->player_characters[this->current_player]->stop_animation();
	  }

	if (this->input_state->key_1)        // switching players
	  {
		this->player_characters[this->current_player]->stop_animation();
	    this->current_player = 0;
	  }
	else if (this->input_state->key_2)
	  {
		this->player_characters[this->current_player]->stop_animation();
	    this->current_player = 1;
	  }
	else if (this->input_state->key_3)
	  {
		this->player_characters[this->current_player]->stop_animation();
		this->current_player = 2;
	  }

	if (this->input_state->key_use)
	  {
		this->use_key_press(global_time);
	  }
	  
	this->time_before = al_current_time();
  }

//-----------------------------------------------

void c_map::use_key_press(long int global_time)
  {
	int i;
	int facing_square[2];  // coordinations of the square the player is facing
	int coordinations[2];
	c_map_object *help_object;

	coordinations[0] = this->player_characters[this->current_player]->get_square_x();
    coordinations[1] = this->player_characters[this->current_player]->get_square_y();

	switch(this->player_characters[this->current_player]->get_direction())
	  {
	    case DIRECTION_NORTH:
		  facing_square[0] = coordinations[0];
		  facing_square[1] = coordinations[1] - 1;
		  break;

		case DIRECTION_EAST:
		  facing_square[0] = coordinations[0] + 1;
		  facing_square[1] = coordinations[1];
		  break;

		case DIRECTION_SOUTH:
		  facing_square[0] = coordinations[0];
		  facing_square[1] = coordinations[1] + 1;
		  break;

		case DIRECTION_WEST:
		  facing_square[0] = coordinations[0] - 1;
		  facing_square[1] = coordinations[1];
		  break;
	  }

	for (i = 0; i < MAX_OBJECTS_PER_SQUARE; i++)
	  if (this->squares[facing_square[0]][facing_square[1]].map_objects[i] != NULL)
	    {
		  help_object = this->squares[facing_square[0]][facing_square[1]].map_objects[i];

		  if (!help_object->is_animating())
		    {
			  help_object->use(global_time);
		    }
	    }
	  else
	    break;
  }

//-----------------------------------------------