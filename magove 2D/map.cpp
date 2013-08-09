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

c_map::c_map(string filename, t_input_output_state *input_output_state, long int *global_time)
  {
    this->current_player = 0;
	this->pressed_1 = false;
	this->pressed_2 = false;
	this->pressed_3 = false;  
	this->mouse_pressed = false;
	this->frame_count = 0;
	this->animation_frame = 0;
	this->text_is_displayed = false;
	this->time_before = 0.0; 
	this->global_time = global_time;
	this->flames_on = false;
    this->input_output_state = input_output_state;
	this->number_of_missiles = 0;
	this->screen_square_resolution[0] = this->input_output_state->screen_x / 64 + 1;
	this->screen_square_resolution[1] = this->input_output_state->screen_y / 50 + 1;
	this->screen_square_position[0] = 0;
	this->screen_square_position[1] = 0;
	this->screen_pixel_position[0] = 0;
	this->screen_pixel_position[0] = 0;
	this->screen_square_end[0] = this->screen_square_resolution[0];
	this->screen_square_end[1] = this->screen_square_resolution[1];
	this->screen_center_x = this->input_output_state->screen_x / 2; 
    this->screen_center_y = this->input_output_state->screen_y / 2;

	portrait_x_positions[0] = 20;
	portrait_x_positions[1] = 170;
	portrait_x_positions[2] = 320;
	portrait_y_position = this->input_output_state->screen_y - 75;

	this->succesfully_loaded = this->load_from_file(filename);
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
	string help_string;

	this->width = 30;
	this->height = 30;

	if (!this->set_environment(ENVIRONMENT_GRASS))
	  return false;

	for (j = 0; j < this->height; j++)
	  for (i = 0; i < this->width; i++)
	    {
		  this->squares[i][j].height = 0;
		  this->squares[i][j].type = SQUARE_NORMAL;
		  this->squares[i][j].height = NULL;
		  this->squares[i][j].animation = NULL;

		  for (k = 0; k < MAX_OBJECTS_PER_SQUARE; k++)
		    this->squares[i][j].map_objects[k] = NULL;
	    }

	this->squares[0][0].height = 2;
	this->squares[1][0].height = 2;
	this->squares[2][0].height = 2;
	this->squares[3][0].height = 2;
	this->squares[4][0].height = 2;
	this->squares[5][0].height = 2;
	this->squares[6][0].height = 2;
	this->squares[0][1].height = 2;
	this->squares[1][1].height = 2;
	this->squares[2][1].height = 2;
	this->squares[3][1].height = 2;
	this->squares[4][1].height = 2;
	this->squares[5][1].height = 2;
	this->squares[6][1].height = 2;
	this->squares[2][6].height = 2;
	this->squares[3][6].height = 2;
	this->squares[2][0].height = 2;
	this->squares[2][1].height = 2;
	this->squares[2][2].height = 2;
	this->squares[3][0].height = 2;
	this->squares[3][1].height = 2;
	this->squares[3][2].height = 2;
	this->squares[0][8].height = 2;

	this->squares[0][2].height = 1;
	this->squares[1][2].height = 1;
	this->squares[2][2].height = 1;
	this->squares[0][3].height = 1;
	this->squares[1][3].height = 1;
	this->squares[2][3].height = 1;
	this->squares[8][0].height = 1; 

	this->squares[29][29].height = 2;
	this->squares[28][29].height = 2;
	this->squares[27][29].height = 1;

	this->squares[0][1].type = SQUARE_WATER;
	this->squares[4][2].type = SQUARE_WATER;
	this->squares[5][2].type = SQUARE_WATER;

	this->squares[1][6].type = SQUARE_WATER;
	this->squares[2][6].type = SQUARE_WATER;
	this->squares[3][6].type = SQUARE_WATER;
	this->squares[1][7].type = SQUARE_WATER;
	this->squares[2][7].type = SQUARE_WATER;
	this->squares[3][7].type = SQUARE_WATER;
	this->squares[1][8].type = SQUARE_WATER;
	this->squares[2][8].type = SQUARE_WATER;
	this->squares[3][8].type = SQUARE_WATER;

	this->squares[10][10].type = SQUARE_HOLE;
	this->squares[10][11].type = SQUARE_HOLE;
	this->squares[10][12].type = SQUARE_HOLE;
	this->squares[9][10].type = SQUARE_HOLE;
	this->squares[9][11].type = SQUARE_COLLAPSE;
	this->squares[9][12].type = SQUARE_HOLE;

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

	this->add_map_object(new c_map_object(OBJECT_CRATE,0,0,this->global_time),5,0);
	this->add_map_object(new c_map_object(OBJECT_CRATE,0,0,this->global_time),4,1);
	this->add_map_object(new c_map_object(OBJECT_CRATE,0,0,this->global_time),5,6);
	this->add_map_object(new c_map_object(OBJECT_CRATE,0,0,this->global_time),5,7);
	this->add_map_object(new c_map_object(OBJECT_CRATE,0,0,this->global_time),5,8);
	this->add_map_object(new c_map_object(OBJECT_CRATE,0,0,this->global_time),7,6);
	this->add_map_object(new c_map_object(OBJECT_CRATE,0,0,this->global_time),7,7);
	this->add_map_object(new c_map_object(OBJECT_CRATE,0,0,this->global_time),7,8);
	this->add_map_object(new c_map_object(OBJECT_FLAMES,1,0,this->global_time),9,2);
	this->add_map_object(new c_map_object(OBJECT_FLAMES,0,0,this->global_time),9,4);

	this->add_map_object(new c_map_object(OBJECT_TELEPORT_INPUT,10,-1,this->global_time),2,10);
	this->add_map_object(new c_map_object(OBJECT_TELEPORT_OUTPUT,10,-1,this->global_time),3,12);

	c_map_object *sign;

	sign = new c_map_object(OBJECT_SIGN,0,0,this->global_time);

	sign->set_sign_text("TEXT NA ZNACCE! Zde muze byt vase reklama. Volejte 0123456789.");

	this->add_map_object(sign,2,12);

	this->add_map_object(new c_map_object(OBJECT_FOUNTAIN,0,0,&this->animation_frame),10,8);
	this->add_map_object(new c_map_object(OBJECT_GATE,0,0,&this->animation_frame),12,8);

	this->add_map_object(new c_map_object(OBJECT_STAIRS_NORTH,0,0,this->global_time),1,2);
	this->add_map_object(new c_map_object(OBJECT_STAIRS_NORTH,0,0,this->global_time),1,4);
	this->add_map_object(new c_map_object(OBJECT_STAIRS_NORTH,0,0,this->global_time),3,2);
	this->add_map_object(new c_map_object(OBJECT_STAIRS_WEST,0,0,this->global_time),7,0);

	this->add_map_object(new c_map_object(OBJECT_LEVER,1,-1,this->global_time),8,7);
	this->add_map_object(new c_map_object(OBJECT_LEVER,1,2,this->global_time),8,8);
	this->add_map_object(new c_map_object(OBJECT_LEVER,2,-1,this->global_time),8,9);

	this->add_map_object(new c_map_object(OBJECT_BUTTON,1,-1,this->global_time),8,13);

	this->add_map_object(new c_map_object(OBJECT_DOOR_HORIZONTAL,1,-1,this->global_time),6,7);
	this->add_map_object(new c_map_object(OBJECT_DOOR_HORIZONTAL,2,-1,this->global_time),6,8);
	this->add_map_object(new c_map_object(OBJECT_DOOR_HORIZONTAL,1,2,this->global_time),6,9);
	this->add_map_object(new c_map_object(OBJECT_DOOR_VERTICAL,1,2,this->global_time),6,2);

	this->add_map_object(new c_map_object(OBJECT_ICE,-1,-1,this->global_time),5,12);

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
	
	this->animation_water_splash = new c_animation(this->global_time,"resources/animation_water_splash",5,-5,-5,2,true,"resources/water.wav",1.0);
	this->animation_refresh = new c_animation(this->global_time,"resources/animation_refresh",6,0,0,2,true,"resources/refresh.wav",0.5);
	this->animation_crate_shift_north = new c_animation(this->global_time,"resources/animation_crate_shift_north",3,0,-79,1,false,"",1.0);
	this->animation_collapse = new c_animation(this->global_time,"resources/animation_collapse",5,0,0,2,true,"resources/crack.wav",0.3);
	this->animation_melt = new c_animation(this->global_time,"resources/animation_melt",4,0,-27,5,false,"",0.0);

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
	  }
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
		  
			if (help_object != NULL && help_object->get_type() == OBJECT_BUTTON && this->object_can_be_used(help_object))
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

bool c_map::crate_can_be_shifted(int x, int y, int height, t_direction direction)
  {
	int next_square[2];
	int i;

	if (x < 0 || x >= this->width || y < 0 || y >= this->height)
	  return false;

	this->next_square(x,y,direction,&next_square[0],&next_square[1]);

	if (next_square[0] < 0 || next_square[0] >= this->width ||
	  next_square[1] < 0 || next_square[1] >= this->height)
	  return false;

	if (!this->square_is_stepable(next_square[0],next_square[1]))
	  return false;

	if (this->get_height(x,y) - 1 != height)      // check if shifting from right height 
	  return false;

	if (this->square_has_character(next_square[0],next_square[1]))
	  return false;

	if (this->get_height(next_square[0],next_square[1]) > height)
	  return false;

	if (this->get_height(x,y) - 1 == this->get_height(next_square[0],next_square[1])) // check door (at the same height level)
	  {
        for (i = 0; i < MAX_OBJECTS_PER_SQUARE; i++)
		  if (this->squares[next_square[0]][next_square[1]].map_objects[i] != NULL)
		    {
		      if (this->squares[next_square[0]][next_square[1]].map_objects[i]->get_type() == OBJECT_DOOR_HORIZONTAL)
		        {
			      if (direction == DIRECTION_EAST || direction == DIRECTION_WEST ||
				    this->squares[next_square[0]][next_square[1]].map_objects[i]->get_state() == OBJECT_STATE_OFF)
				    return false;
		        }
		      else if (this->squares[next_square[0]][next_square[1]].map_objects[i]->get_type() == OBJECT_DOOR_VERTICAL)
		        {
			     if (direction == DIRECTION_NORTH || direction == DIRECTION_SOUTH ||
				    this->squares[next_square[0]][next_square[1]].map_objects[i]->get_state() == OBJECT_STATE_OFF)
				    return false;
		        }
		    }
		  else if (this->squares[x][y].map_objects[i] != NULL)   // check doors at the crate's square
		    {
			  if (this->squares[x][y].map_objects[i]->get_type() == OBJECT_DOOR_HORIZONTAL)
		        {
			      if (direction == DIRECTION_EAST || direction == DIRECTION_WEST)
				    return false;
		        }
		      else if (this->squares[x][y].map_objects[i]->get_type() == OBJECT_DOOR_VERTICAL)
		        {
			     if (direction == DIRECTION_NORTH || direction == DIRECTION_SOUTH)
				   return false;
		        }
		    }
		  else
			break;
	  }
	else    // checks door that are on lower height level
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
  }

//-----------------------------------------------

void c_map::link_objects()
  {
	int i, j, k, l, m, n, o;
	bool is_in_array;
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
	int i, j, k, help_height, elevation, number_of_crates, elevator_height;
	al_clear_to_color(al_map_rgb(0,0,0));      // clear the screen
	this->animation_frame = *this->global_time / 16;

	for (j = this->screen_square_position[1] - 1; j < this->screen_square_end[1] + 1; j++)                         // go through lines
	  { 
		if (j < 0 || j >= this->height)
	      continue;

        for (help_height = 0; help_height < 3; help_height++)  // go through all 3 heights
	      { 

			elevation = help_height * 27;
	
			for (i = this->screen_square_position[0] - 1; i < this->screen_square_end[0] + 1; i++)                 // go through columns
			  { 
				if (i < 0 || i >= this->width)
	              continue;

				if (this->squares[i][j].height == help_height)
		          { 
			        switch (this->squares[i][j].type)
			          {
			            case SQUARE_NORMAL:                      // normal square
						  al_draw_bitmap(this->tile,x + i * 64 - this->screen_pixel_position[0],y + j * 50 - elevation - this->screen_pixel_position[1],0); // draw floor
						  break;

				        case SQUARE_WATER:                       // water square
					      al_draw_bitmap(this->tile_water[this->animation_frame % 5],x + i * 64 - this->screen_pixel_position[0],y + j * 50 - elevation - this->screen_pixel_position[1],0);			          
					      this->draw_borders(i,j,x - this->screen_pixel_position[0],y - this->screen_pixel_position[1]);
						  break;

						case SQUARE_ICE:                          // ice square
						  al_draw_bitmap(this->tile_ice,x + i * 64 - this->screen_pixel_position[0],y + j * 50 - elevation - this->screen_pixel_position[1],0);
						  this->draw_borders(i,j,x - this->screen_pixel_position[0],y - this->screen_pixel_position[1]);
						  break;

						case SQUARE_COLLAPSE:                     // collapse square
						  al_draw_bitmap(this->tile_collapse,x + i * 64 - this->screen_pixel_position[0],y + j * 50 - elevation - this->screen_pixel_position[1],0);
						  this->draw_borders(i,j,x - this->screen_pixel_position[0],y - this->screen_pixel_position[1]);
						  break;

						case SQUARE_HOLE:                         // hole
						  al_draw_bitmap(this->tile_hole,x + i * 64 - this->screen_pixel_position[0],y + j * 50 - elevation - this->screen_pixel_position[1],0);
						  this->draw_borders(i,j,x - this->screen_pixel_position[0],y - this->screen_pixel_position[1]);
						  break;
					  }
					
			        if (help_height != 3)                                                    // draw south cliffs
				      {
				        if (this->get_terrain_height(i,j - 1) == help_height + 1)                    // south
					      {
				  	        al_draw_bitmap(this->tile_cliff_south_1,x + i * 64 - this->screen_pixel_position[0],y + j * 50 - elevation - 27 - this->screen_pixel_position[1],0);
				      
					        if (this->get_terrain_height(i + 1,j - 1) != this->get_terrain_height(i,j - 1))  // southeast 1
						      al_draw_bitmap(this->tile_cliff_southeast_1,x + i * 64 + 64 - this->screen_pixel_position[0],y + j * 50 - elevation - 27 - this->screen_pixel_position[1],0);
				    
					        if (this->get_terrain_height(i - 1,j - 1) != this->get_terrain_height(i,j - 1))  // southwest 1
					          al_draw_bitmap(this->tile_cliff_southwest_1,x + i * 64 - 10 - this->screen_pixel_position[0],y + j * 50 - elevation - 27 - this->screen_pixel_position[1],0);
					      }
				        else if (this->get_terrain_height(i,j - 1) == help_height + 2)
					      {
					        al_draw_bitmap(this->tile_cliff_south_2,x + i * 64 - this->screen_pixel_position[0],y + j * 50 - elevation - 54 - this->screen_pixel_position[1],0);

					        if (this->get_terrain_height(i + 1,j - 1) != this->get_terrain_height(i,j - 1))  // southeast 2
						      al_draw_bitmap(this->tile_cliff_southeast_2,x + i * 64 + 64 - this->screen_pixel_position[0],y + j * 50 - elevation - 54 - this->screen_pixel_position[1],0);
				    
					        if (this->get_terrain_height(i - 1,j - 1) != this->get_terrain_height(i,j - 1))  // southwest 2
						      al_draw_bitmap(this->tile_cliff_southwest_2,x + i * 64 - 10 - this->screen_pixel_position[0],y + j * 50 - elevation - 54 - this->screen_pixel_position[1],0);
					      }
				      }
					  
				    if (help_height != 0)                                                  // draw other cliffs
				      {
				        if (this->get_terrain_height(i,j - 1) < help_height)                       // north
					      {
					        al_draw_bitmap(this->tile_cliff_north,x + i * 64 - this->screen_pixel_position[0],y + j * 50 - elevation - 10 - this->screen_pixel_position[1],0);
				    
					        if (this->get_terrain_height(i + 1,j - 1) != help_height &&
						      this->get_terrain_height(i + 1,j) != help_height)                    // northeast
						     al_draw_bitmap(this->tile_cliff_northeast,x + i * 64 + 64 - this->screen_pixel_position[0],y + j * 50 - elevation - 10 - this->screen_pixel_position[1],0);

					        if (this->get_terrain_height(i - 1,j - 1) != help_height &&
						      this->get_terrain_height(i - 1,j) != help_height)                    // northwest
						      al_draw_bitmap(this->tile_cliff_northwest,x + i * 64 -10 - this->screen_pixel_position[0],y + j * 50 - elevation - 10 - this->screen_pixel_position[1],0);
					      }

				        if (this->get_terrain_height(i - 1,j) < help_height)                       // west
					      al_draw_bitmap(this->tile_cliff_west,x + i * 64 - 10 - this->screen_pixel_position[0],y + j * 50 - elevation - this->screen_pixel_position[1],0);

				        if (this->get_terrain_height(i + 1,j) < help_height)                       // east
					      al_draw_bitmap(this->tile_cliff_east,x + i * 64 + 64 - this->screen_pixel_position[0],y + j * 50 - elevation - this->screen_pixel_position[1],0);
		        
				      } 
				  } 
			  }
	      }

		for (i = 0; i < this->width; i++)      // draw the same line of objects (and animations)
	      {
			number_of_crates = 0;
			elevator_height = 0;

			for (k = 0; k < MAX_OBJECTS_PER_SQUARE; k++)
			  if (this->squares[i][j].map_objects[k] != NULL)
                if (this->squares[i][j].map_objects[k]->get_type() == OBJECT_CRATE) // draw crates one on another
				  {
					if (this->get_square_type(i,j) == SQUARE_WATER) // if the crate is in the water, draw it differently
					  {
					    if (number_of_crates == 0) 
					      al_draw_bitmap(this->bitmap_crate_water,x + i * 64 - this->screen_pixel_position[0], y + j * 50 - this->squares[i][j].height * 27 - this->screen_pixel_position[1],0); 
					    else
						  this->squares[i][j].map_objects[k]->draw(x + i * 64 - this->screen_pixel_position[0], y + j * 50 - (this->squares[i][j].height - 1) * 27 - number_of_crates * 27 - this->screen_pixel_position[1]);
					  }
					else
					  this->squares[i][j].map_objects[k]->draw(x + i * 64 - this->screen_pixel_position[0], y + j * 50 - this->squares[i][j].height * 27 - number_of_crates * 27 - elevator_height - this->screen_pixel_position[1]);
				    
					number_of_crates++;
				  }
				else
				  {
					if (this->squares[i][j].map_objects[k]->get_type() == OBJECT_ELEVATOR)
					  if (this->squares[i][j].map_objects[k]->get_state() == OBJECT_STATE_ON)
						elevator_height = 27;

				    this->squares[i][j].map_objects[k]->draw(x + i * 64 - this->screen_pixel_position[0], y + j * 50 - this->squares[i][j].height * 27 - this->screen_pixel_position[1]);
				  }
			  else
				break;

			if (this->squares[i][j].animation != NULL)
			  if (this->squares[i][j].animation->get_playing_animation() != NULL)
                this->squares[i][j].animation->draw(x + i * 64 - this->screen_pixel_position[0], y + j * 50 - this->squares[i][j].height * 27 - this->screen_pixel_position[1]);
			  else
			    this->squares[i][j].animation = NULL;
	      }
	
		for (i = 0; i < 3; i++)                // draw players
		  if (this->player_characters[i] != NULL && this->player_characters[i]->get_square_y() == j)
		    {
			  elevation = this->get_elevation_for_character(this->player_characters[i]);

			  this->player_characters[i]->draw((int) (x + this->player_characters[i]->get_position_x() * 64 - this->screen_pixel_position[0]),
			  (int) (y + this->player_characters[i]->get_position_y() * 50 - this->screen_pixel_position[1]) - elevation);
		    }

		for (i = 0; i < this->number_of_missiles; i++) // draw missiles
		  if (this->missiles[i].square_y == j)
		    {
			  elevation = this->missiles[i].height * 27;
			  al_draw_bitmap(this->missiles[i].bitmap,x + (int) (this->missiles[i].position_x * 64) - this->screen_pixel_position[0], y + (int) (this->missiles[i].position_y * 50) - elevation - this->screen_pixel_position[1],0); 
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

	if (this->text_is_displayed)    // draw text
	  {
		for (i = 0; i < MAX_TEXT_LINES; i++)
		  {
			al_draw_text(this->text_font,al_map_rgb(0,0,0),this->screen_center_x + 1,this->screen_center_y - 200 + 30 * i + 1,ALLEGRO_ALIGN_CENTRE,this->text_lines[i]); // text shadow
			al_draw_text(this->text_font,al_map_rgb(255,220,220),this->screen_center_x,this->screen_center_y - 200 + 30 * i,ALLEGRO_ALIGN_CENTRE,this->text_lines[i]);
		  }
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

	height = this->get_height(x,y) * 27;

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
			  	      height -= 27;
					  height += this->squares[x][y].map_objects[i]->get_animation_frame() * 7;
				    }
				  else
				    {
					  height += 27;
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
	int i;
	int square_position_next[2];           // next square coordinations in player's direction
	t_object_type help_object_type;        // to checks stairs
	t_object_type help_object_type2;       // to checks stairs
	int height_difference;                 // height difference between start and destination squares
	bool returned_value;
	
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

	for (i = 0; i < MAX_OBJECTS_PER_SQUARE; i++)                                   // check doors
      if (this->squares[square_position_next[0]][square_position_next[1]].map_objects[i] == NULL)
		break;
	  else
		if (this->squares[square_position_next[0]][square_position_next[1]].map_objects[i]->get_type() == OBJECT_DOOR_HORIZONTAL)
		  {
			if (this->squares[square_position_next[0]][square_position_next[1]].map_objects[i]->get_state() == OBJECT_STATE_OFF ||
			  direction == DIRECTION_EAST || direction == DIRECTION_WEST)
			  return false;
			else
			  break;
		  }
		else if (this->squares[square_position_next[0]][square_position_next[1]].map_objects[i]->get_type() == OBJECT_DOOR_VERTICAL)
		  {
		    if (this->squares[square_position_next[0]][square_position_next[1]].map_objects[i]->get_state() == OBJECT_STATE_OFF ||
			  direction == DIRECTION_NORTH || direction == DIRECTION_SOUTH)
			  return false;
			else
			  break;
		  }

	if (this->square_has_object(square_position[0],square_position[1],OBJECT_DOOR_HORIZONTAL) &&   // check door at player's square
	  (direction == DIRECTION_EAST || direction == DIRECTION_WEST))
	  return false;
	else if (this->square_has_object(square_position[0],square_position[1],OBJECT_DOOR_VERTICAL) && 
	  (direction == DIRECTION_NORTH || direction == DIRECTION_SOUTH))
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
	int i;

	player_position[0] = this->player_characters[this->current_player]->get_square_x();
	player_position[1] = this->player_characters[this->current_player]->get_square_y();

	for (i = 0; i < 2; i++)    // check x and y
	  if (player_position[i] < this->screen_square_position[i] + 2)
	    {
	      this->screen_square_position[i] = player_position[i] - 1;
		  this->screen_square_end[i] = this->screen_square_position[i] + this->screen_square_resolution[i];

		   if (i == 0)
			this->screen_pixel_position[i] = ((this->screen_square_position[i] - 1) * 64) + this->player_characters[this->current_player]->get_fraction_x() * 64;
		  else
			this->screen_pixel_position[i] = ((this->screen_square_position[i] - 1) * 50) + this->player_characters[this->current_player]->get_fraction_y() * 50;
	    }
	  else if (player_position[i] >= this->screen_square_end[i] - 3)
	    {
	      this->screen_square_position[i] += player_position[i] - (this->screen_square_end[i] - 3);
		  this->screen_square_end[i] = this->screen_square_position[i] + this->screen_square_resolution[i];

		  if (i == 0)
			this->screen_pixel_position[i] = (this->screen_square_position[i] + this->player_characters[this->current_player]->get_fraction_x()) * 64;
		  else
			this->screen_pixel_position[i] = (this->screen_square_position[i] + this->player_characters[this->current_player]->get_fraction_y()) * 50;
	    }
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
		  if (this->character_can_move_to_square(character,direction)
			|| character->get_fraction_y() > CLIFF_DISTANCE_SOUTH) 
			character->move_by(0.0,-1 * step_length);
		  break;

	    case DIRECTION_EAST:
		  if (this->character_can_move_to_square(character,direction)
			|| character->get_fraction_x() < 1 - CLIFF_DISTANCE_EAST_WEST) 
			character->move_by(step_length,0.0);
		  break;

	    case DIRECTION_WEST:
		  if (this->character_can_move_to_square(character,direction)
			|| character->get_fraction_x() > CLIFF_DISTANCE_EAST_WEST) 
			character->move_by(-1 *step_length,0.0);
		  break;

	    case DIRECTION_SOUTH:
		  if (this->character_can_move_to_square(character,direction)
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
	
	// the movement's done here, now do other things

	this->update_screen_position();
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
	int i, j, position;

	position = 0;     // position in the text

	for (j = 0; j < MAX_TEXT_LINES; j++) // split the string into lines
	  {
	    for (i = 0; i < MAX_TEXT_CHARACTERS_PER_LINE - 1; i++)
		  {
			if (position >= (int) (text.length() - 1))
			  {
			    this->text_lines[j][i] = 0;
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

		this->text_lines[j][i + 1] = 0;  // terminate the string
	  }

    this->text_is_displayed = true;
	this->text_end_time = al_current_time() + duration;
  }

//-----------------------------------------------

void c_map::update_missiles()
  {
	int i, j;
	bool died;

	for (i = 0; i < this->number_of_missiles; i++)
	  {
		died = false;

		// position computing is the same as in player get_square_y() - could be done better :/ (make a static method in c_character!!!)
		this->missiles[i].square_y = c_character::position_to_square(this->missiles[i].position_y,false); //  this->missiles[i].square_y > -0.3 ? floor(this->missiles[i].position_y + 0.3) + 1 : 0;
		this->missiles[i].square_x = c_character::position_to_square(this->missiles[i].position_x,true);  //floor(this->missiles[i].position_x + 0.3);

		switch (this->missiles[i].direction)
		  {
		    case DIRECTION_NORTH:
			  missiles[i].position_y -= 0.1;
			  break;

			case DIRECTION_EAST:
			  missiles[i].position_x += 0.1;
			  break;

			case DIRECTION_SOUTH:
			  missiles[i].position_y += 0.1;
			  break;

			case DIRECTION_WEST:
			  missiles[i].position_x -= 0.1;
			  break;
		  }

		if (this->get_height(this->missiles[i].square_x,this->missiles[i].square_y) > this->missiles[i].height ||
		  this->get_terrain_height(this->missiles[i].square_x,this->missiles[i].square_y) > this->missiles[i].height)
		  died = true;

		switch (this->missiles[i].type)    // check the missile effect
		  {
		    case MISSILE_MIA_1:
			  if (this->square_has_object(this->missiles[i].square_x,this->missiles[i].square_y,OBJECT_CRATE) &&
			      this->crate_can_be_shifted(this->missiles[i].square_x,this->missiles[i].square_y,this->missiles[i].height,this->missiles[i].direction))
				this->shift_crate(this->missiles[i].square_x,this->missiles[i].square_y,this->missiles[i].direction);

			  break;

            case MISSILE_MIA_2:
			  if (this->get_square_type(this->missiles[i].square_x,this->missiles[i].square_y) == SQUARE_HOLE)
			    {
				  this->set_square_type(this->missiles[i].square_x,this->missiles[i].square_y,SQUARE_COLLAPSE);
			      died = true;
			    }

			  break;

			case MISSILE_METODEJ_1:
			  if (this->square_has_object(this->missiles[i].square_x,this->missiles[i].square_y,OBJECT_ICE))
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

			case MISSILE_STAROVOUS_2:
			  for (j = 0; j < 3; j++)
				if (this->player_characters[j] != NULL &&
				  this->player_characters[j]->get_square_x() == this->missiles[i].square_x &&
				  this->player_characters[j]->get_square_y() == this->missiles[i].square_y &&
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

	this->player_characters[this->current_player]->stop_animation();
    this->current_player = player_number;
	this->update_screen_position();
	al_play_sample(this->change_player_sound,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&sample_id);
  }

//-----------------------------------------------

void c_map::update()
  {
	this->time_difference = al_current_time() - this->time_before;
	
	if (this->text_is_displayed && this->text_end_time <= al_current_time()) // erase the text displayed
	  {
		this->text_is_displayed = false;
	  }

	this->update_missiles();

	this->draw(0,0);
	
	this->frame_count++;

	if (this->frame_count % 128 == 0)
	  {
		this->flames_on = !this->flames_on;
		this->update_flames();
	  }

	if (this->input_output_state->mouse_1)  // switching players with mouse
	  {
		if (!this->mouse_pressed)
		  {
			if (this->input_output_state->mouse_y > this->portrait_y_position &&
			  this->input_output_state->mouse_y < this->portrait_y_position + 50)
			  {
			    if (this->input_output_state->mouse_x > this->portrait_x_positions[0] &&
				  this->input_output_state->mouse_x < this->portrait_x_positions[0] + 150)
				  this->switch_player(0);
				else if (this->input_output_state->mouse_x > this->portrait_x_positions[1] &&
				  this->input_output_state->mouse_x < this->portrait_x_positions[1] + 150)
				  this->switch_player(1);
				else if (this->input_output_state->mouse_x > this->portrait_x_positions[2] &&
				  this->input_output_state->mouse_x < this->portrait_x_positions[2] + 150)
				  this->switch_player(2);
			  }
		  }

		this->mouse_pressed = true;
	  }
	else
	  this->mouse_pressed = false;

	if (this->input_output_state->key_left)  // moving player
	  this->move_character(this->player_characters[this->current_player],DIRECTION_WEST);
	else if (this->input_output_state->key_right)
	  this->move_character(this->player_characters[this->current_player],DIRECTION_EAST);
	else if (this->input_output_state->key_down)
	  this->move_character(this->player_characters[this->current_player],DIRECTION_SOUTH);
	else if (this->input_output_state->key_up)
	  this->move_character(this->player_characters[this->current_player],DIRECTION_NORTH);
	else if (this->player_characters[this->current_player]->get_playing_animation() != ANIMATION_USE
	  && this->player_characters[this->current_player]->get_playing_animation() != ANIMATION_CAST)
	  {
		this->player_characters[this->current_player]->stop_animation();
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

	this->time_before = al_current_time();
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

	if (this->player_characters[this->current_player]->get_magic_energy() == 0)
	  return;                  // no magic energy

	if (this->player_characters[this->current_player]->get_playing_animation() == ANIMATION_CAST ||
	  this->player_characters[this->current_player]->get_playing_animation() == ANIMATION_USE)
	  return;

	if (spell_number == 0 || spell_number == 1)
	  switch(this->player_characters[this->current_player]->get_player_type()) // play the cast sound
	    {
	      case PLAYER_MIA:
		    al_play_sample(this->spell_sounds_mia[spell_number],0.5,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&sample_id);			
			this->fire_missile(spell_number);
			break;

		  case PLAYER_METODEJ:
			al_play_sample(this->spell_sounds_metodej[spell_number],0.5,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&sample_id);
		    this->fire_missile(spell_number);
			break;

		  case PLAYER_STAROVOUS:
			al_play_sample(this->spell_sounds_starovous[spell_number],0.5,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,&sample_id);
		    this->fire_missile(spell_number);
			break;
	    }

	this->player_characters[this->current_player]->change_magic_energy(-1);
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
			  if (this->squares[i][j].map_objects[k]->get_type() == OBJECT_FLAMES &&
				(this->squares[i][j].map_objects[k]->get_state() == OBJECT_STATE_ON ||
				this->squares[i][j].map_objects[k]->get_state() == OBJECT_STATE_ON_ACTIVE))
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
				if (this->crate_can_be_shifted(facing_square[0],facing_square[1],this->get_height(coordinations[0],coordinations[1]),this->player_characters[this->current_player]->get_direction()))
			      {  
				    this->shift_crate(facing_square[0],facing_square[1],this->player_characters[this->current_player]->get_direction());
		            this->player_characters[this->current_player]->play_animation(ANIMATION_CAST);
			      }
		      }
		    else if (help_object->get_type() == OBJECT_LEVER && !help_object->is_animating())
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
	      }
		else
	      break;
	  }

	if (this->square_has_object(coordinations[0],coordinations[1],OBJECT_TELEPORT_INPUT)) // check teleport
	  this->check_teleport();
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
				else if (this->squares[x][y].map_objects[j] == help_object)
				  {
					this->player_characters[this->current_player]->set_position(x + 0.1,y - 0.5);
					this->update_screen_position();
				    break;
				  }

		  break;
	    }
  }
//-----------------------------------------------