/**
 * Map class implementation.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
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

	if (x > this->width || x < 0 ||
	  y > this->height || y < 0)
	  return 0;

	number_of_crates = 0;

	for (i = 0; i < MAX_OBJECTS_PER_SQUARE; i++)
	  if (this->squares[x][y].map_objects[i] == NULL)
	    break;
	  else if (this->squares[x][y].map_objects[i]->get_type() == OBJECT_CRATE)
		number_of_crates++;

	return this->squares[x][y].height + number_of_crates;
  }

//-----------------------------------------------

int c_map::get_terrain_height(int x, int y)
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

	if (!this->tile || !this->tile_cliff_south_1 || !this->tile_cliff_south_2 ||
	  !this->tile_cliff_southwest_1 || !this->tile_cliff_southwest_2 || !this->tile_cliff_southeast_1 ||
	  !this->tile_cliff_southeast_2 || !this->tile_cliff_west || !this->tile_cliff_east ||
	  !this->tile_cliff_north || !this->tile_cliff_northwest || !this->tile_cliff_northeast || 
	  !this->tile_edge || !this->tile_water[0] || !this->tile_water[1] || !this->tile_water[2] || 
	  !this->tile_water[3] || !this->tile_water[4] || !this->tile_ice || !this->tile_collapse ||
	  !this->tile_hole)
	  return false;

	return true;
  }

//-----------------------------------------------

c_map::c_map(string filename, t_input_state *input_state, long int *global_time)
  {  
    this->current_player = 0;
	this->animation_frame = 0;
	this->time_before = 0.0;
	this->global_time = global_time;
    this->input_state = input_state;
	this->succesfully_loaded = this->load_from_file(filename);

	this->portrait_mia = al_load_bitmap("resources/portrait_mia.png");
	this->portrait_metodej = al_load_bitmap("resources/portrait_metodej.png");
	this->portrait_starovous = al_load_bitmap("resources/portrait_starovous.png");
	this->portrait_selection = al_load_bitmap("resources/selection.png");

	if (!this->portrait_mia || !this->portrait_metodej ||
		!this->portrait_starovous || !this->portrait_selection)
	  this->succesfully_loaded = false;
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

	if (!this->set_environment(ENVIRONMENT_GRASS))
	  return false;

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

	this->squares[9][0].type = SQUARE_ICE;
	this->squares[9][1].type = SQUARE_ICE;
	this->squares[8][1].type = SQUARE_ICE;

	this->squares[9][4].type = SQUARE_COLLAPSE;
	this->squares[9][5].type = SQUARE_COLLAPSE;
	this->squares[8][5].type = SQUARE_COLLAPSE;

	this->squares[8][6].type = SQUARE_HOLE;
	this->squares[8][7].type = SQUARE_HOLE;

	this->squares[7][7].height = 2;
	this->squares[7][6].height = 2;

	this->squares[2][5].height = 1;

	this->player_characters[0] = new c_player_character(PLAYER_STAROVOUS,this->global_time);
	this->player_characters[1] = new c_player_character(PLAYER_MIA,this->global_time);
	this->player_characters[2] = new c_player_character(PLAYER_METODEJ,this->global_time);

	if (!this->player_characters[0]->is_succesfully_loaded() ||
		!this->player_characters[1]->is_succesfully_loaded() ||
		!this->player_characters[2]->is_succesfully_loaded())
	  {
		cerr << "ERROR: the player character wasn't succesfully loaded." << endl;
	  }
	
	this->player_characters[0]->set_position(8.0,8.0);
	this->player_characters[1]->set_position(6.0,8.0);
	this->player_characters[2]->set_position(4.0,8.0);

	c_map_object *help_objects[100];

	help_objects[0] = new c_map_object(OBJECT_CRATE,0,this->global_time);
	help_objects[1] = new c_map_object(OBJECT_STAIRS_EAST,0,this->global_time);
	help_objects[2] = new c_map_object(OBJECT_DOOR_HORIZONTAL,0,this->global_time);
	help_objects[3] = new c_map_object(OBJECT_DOOR_VERTICAL,0,this->global_time);
	help_objects[4] = new c_map_object(OBJECT_LEVER,0,this->global_time);
	help_objects[5] = new c_map_object(OBJECT_BUTTON,0,this->global_time);
	help_objects[6] = new c_map_object(OBJECT_FOUNTAIN,0,&this->animation_frame);
	help_objects[7] = new c_map_object(OBJECT_TREE,0,this->global_time);
	help_objects[8] = new c_map_object(OBJECT_TREE_WINTER,0,this->global_time);
	help_objects[9] = new c_map_object(OBJECT_ROCK,0,this->global_time);
	help_objects[10] = new c_map_object(OBJECT_CRATE,0,this->global_time);

	for (i = 0; i < 11; i++)
	  if (!help_objects[i]->is_succesfully_loaded())
		cerr << "ERROR: the object isn't successfully loaded." << endl;

	this->add_map_object(help_objects[0],5,5);
	this->add_map_object(help_objects[1],3,3);
	this->add_map_object(help_objects[2],3,7);
	this->add_map_object(help_objects[4],2,7);
	this->add_map_object(help_objects[5],9,9);
	this->add_map_object(help_objects[3],4,8);
	this->add_map_object(help_objects[6],8,2);

	this->add_map_object(help_objects[7],2,9);
	this->add_map_object(help_objects[8],4,9);
	this->add_map_object(help_objects[9],5,9);
	this->add_map_object(help_objects[10],3,6);

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
					  {
					    help_object->switch_state();
					    help_object->play_animation(ANIMATION_SWITCH_OFF);
					  }
				  }
				else
				  {
					if (help_object->get_state() == OBJECT_STATE_ON)
					  {
						help_object->switch_state();
					    help_object->play_animation(ANIMATION_SWITCH_ON);
					  }
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
			  this->add_map_object(this->squares[x][y].map_objects[i],next_square[0],next_square[1]);
			  this->remove_object(x,y,i);
		    }
	    }
	  else
		break;
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
	elevation = square_height * 27;
			          
	if (this->must_have_border(this->get_square_type(x,y - 1),square_type)    // north border
	  || this->get_terrain_height(x,y - 1) != square_height)     
	  al_draw_bitmap(this->tile_edge,plus_x + x * 64,plus_y + y * 50 - elevation,0);

	if (this->must_have_border(this->get_square_type(x + 1,y),square_type)    // east border
	  || this->get_terrain_height(x + 1,y) != square_height)
      al_draw_bitmap(this->tile_cliff_west,plus_x + x * 64 + 54,plus_y + y * 50 - elevation,0);

	if (this->must_have_border(this->get_square_type(x - 1,y),square_type)    // west border
	  || this->get_terrain_height(x - 1,y) != square_height)
      al_draw_bitmap(this->tile_cliff_east,plus_x + x * 64,plus_y + y * 50 - elevation,0);

	if (this->must_have_border(this->get_square_type(x,y + 1),square_type)    // south border
	  || this->get_terrain_height(x,y + 1) != square_height)
      al_draw_bitmap(this->tile_cliff_north,plus_x + x * 64,plus_y + y * 50 - elevation + 40,0);
  }

//-----------------------------------------------

void c_map::draw(int x, int y)
  {
	int i, j, k, help_height, elevation, number_of_crates;
	al_clear_to_color(al_map_rgb(0,0,0));      // clear the screen
	this->animation_frame = *this->global_time / 16;
	
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

				        case SQUARE_WATER:                       // water square
					      al_draw_bitmap(this->tile_water[this->animation_frame % 5],x + i * 64,y + j * 50 - elevation,0);			          
					      this->draw_borders(i,j,x,y);
						  break;

						case SQUARE_ICE:                          // ice square
						  al_draw_bitmap(this->tile_ice,x + i * 64,y + j * 50 - elevation,0);
						  this->draw_borders(i,j,x,y);
						  break;

						case SQUARE_COLLAPSE:                     // collapse square
						  al_draw_bitmap(this->tile_collapse,x + i * 64,y + j * 50 - elevation,0);
						  this->draw_borders(i,j,x,y);
						  break;

						case SQUARE_HOLE:                         // hole
						  al_draw_bitmap(this->tile_hole,x + i * 64,y + j * 50 - elevation,0);
						  this->draw_borders(i,j,x,y);
						  break;
					  }
					
			        if (help_height != 3)                                                    // draw south cliffs
				      {
				        if (this->get_terrain_height(i,j - 1) == help_height + 1)                    // south
					      {
				  	        al_draw_bitmap(this->tile_cliff_south_1,x + i * 64,y + j * 50 - elevation - 27,0);
				      
					        if (this->get_terrain_height(i + 1,j - 1) != this->get_terrain_height(i,j - 1))  // southeast 1
						      al_draw_bitmap(this->tile_cliff_southeast_1,x + i * 64 + 64,y + j * 50 - elevation - 27,0);
				    
					        if (this->get_terrain_height(i - 1,j - 1) != this->get_terrain_height(i,j - 1))  // southwest 1
					          al_draw_bitmap(this->tile_cliff_southwest_1,x + i * 64 - 10,y + j * 50 - elevation - 27,0);
					      }
				        else if (this->get_terrain_height(i,j - 1) == help_height + 2)
					      {
					        al_draw_bitmap(this->tile_cliff_south_2,x + i * 64,y + j * 50 - elevation - 54,0);

					        if (this->get_terrain_height(i + 1,j - 1) != this->get_terrain_height(i,j - 1))  // southeast 2
						      al_draw_bitmap(this->tile_cliff_southeast_2,x + i * 64 + 64,y + j * 50 - elevation - 54,0);
				    
					        if (this->get_terrain_height(i - 1,j - 1) != this->get_terrain_height(i,j - 1))  // southwest 2
						      al_draw_bitmap(this->tile_cliff_southwest_2,x + i * 64 - 10,y + j * 50 - elevation - 54,0);
					      }
				      }
					  
				    if (help_height != 0)                                                  // draw other cliffs
				      {
				        if (this->get_terrain_height(i,j - 1) < help_height)                       // north
					      {
					        al_draw_bitmap(this->tile_cliff_north,x + i * 64,y + j * 50 - elevation - 10,0);
				    
					        if (this->get_terrain_height(i + 1,j - 1) != help_height &&
						      this->get_terrain_height(i + 1,j) != help_height)                    // northeast
						     al_draw_bitmap(this->tile_cliff_northeast,x + i * 64 + 64,y + j * 50 - elevation - 10,0);

					        if (this->get_terrain_height(i - 1,j - 1) != help_height &&
						      this->get_terrain_height(i - 1,j) != help_height)                    // northwest
						      al_draw_bitmap(this->tile_cliff_northwest,x + i * 64 -10,y + j * 50 - elevation - 10,0);
					      }

				        if (this->get_terrain_height(i - 1,j) < help_height)                       // west
					      al_draw_bitmap(this->tile_cliff_west,x + i * 64 - 10,y + j * 50 - elevation,0);

				        if (this->get_terrain_height(i + 1,j) < help_height)                       // east
					      al_draw_bitmap(this->tile_cliff_east,x + i * 64 + 64,y + j * 50 - elevation,0);
		        
				      } 
				  } 
			  }
	      }

		for (i = 0; i < this->width; i++)      // draw the same line of objects
	      {
			number_of_crates = 0;

			for (k = 0; k < MAX_OBJECTS_PER_SQUARE; k++)
			  if (this->squares[i][j].map_objects[k] != NULL)
                if (this->squares[i][j].map_objects[k]->get_type() == OBJECT_CRATE) // draw crates one on another
				  {
				    this->squares[i][j].map_objects[k]->draw(x + i * 64, y + j * 50 - this->squares[i][j].height * 27 - number_of_crates * 27);
				    number_of_crates++;
				  }
				else
				  this->squares[i][j].map_objects[k]->draw(x + i * 64, y + j * 50 - this->squares[i][j].height * 27);
			  
			  else
				break;
	      }
	
		for (i = 0; i < 3; i++)                // draw players
		  if (this->player_characters[i] != NULL && this->player_characters[i]->get_square_y() == j)
		    {
			  elevation = this->get_elevation_for_character(this->player_characters[i]);

			  this->player_characters[i]->draw((int) (x + this->player_characters[i]->get_position_x() * 64),
			  (int) (y + this->player_characters[i]->get_position_y() * 50) - elevation);
		    }
	  }
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

	if(!this->square_is_stepable(square_position_next[0],square_position_next[1])) // check stepable objects
	  return false;

	height_difference = this->get_height(square_position[0],square_position[1]) -  // check height differences
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

void c_map::move_character(c_character *character, t_direction direction)
  {
	int square_position[2];                // player position in map squares
	double step_length;

	step_length = 0.026;

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
	
	// the movement's done, now handle interaction with objects

	square_position[0] = character->get_square_x();
	square_position[1] = character->get_square_y();

	this->check_buttons();
  }

//-----------------------------------------------

void c_map::update()
  { 
	this->time_difference = al_current_time() - this->time_before;
	
	this->draw(50,75);
	
	if (this->input_state->key_left)
	  this->move_character(this->player_characters[this->current_player],DIRECTION_WEST);
	else if (this->input_state->key_right)
	  this->move_character(this->player_characters[this->current_player],DIRECTION_EAST);
	else if (this->input_state->key_down)
	  this->move_character(this->player_characters[this->current_player],DIRECTION_SOUTH);
	else if (this->input_state->key_up)
	  this->move_character(this->player_characters[this->current_player],DIRECTION_NORTH);
	else if (this->player_characters[this->current_player]->get_playing_animation() != ANIMATION_CAST)
	  {
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
		this->use_key_press();
	  }
	  
	this->time_before = al_current_time();
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

	for (i = 0; i < MAX_OBJECTS_PER_SQUARE; i++)
	  {
		help_object = this->squares[facing_square[0]][facing_square[1]].map_objects[i];

	    if (help_object != NULL)
	      {
		    if (help_object->get_type() == OBJECT_CRATE)
		      {
			    if (this->crate_can_be_shifted(facing_square[0],facing_square[1],this->player_characters[this->current_player]->get_direction()))
			      {  
				    this->shift_crate(facing_square[0],facing_square[1],this->player_characters[this->current_player]->get_direction());
		            this->player_characters[this->current_player]->play_animation(ANIMATION_CAST);
			      }
		      }
		    else if (help_object->get_type() == OBJECT_LEVER && !help_object->is_animating())
		      {
			    this->player_characters[this->current_player]->play_animation(ANIMATION_CAST);
			    help_object->use();
		      }
	      }
		else
	      break;
	  }
  }

//-----------------------------------------------