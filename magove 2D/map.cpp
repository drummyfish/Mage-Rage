/**
 * Map class implementation.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
 */

#include "map.h"

//--------------------------------------------------

int c_map::get_height(int x, int y)
  {
	  if (x > this->width || x < 0 ||
	    y > this->height || y < 0)
	    return 0;

	  return this->squares[x][y].height;
  }

//--------------------------------------------------

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
  }

//--------------------------------------------------

c_map::c_map()
  {
    // TEMPORARY CODE!!!!!!!!!!!!!!!!!!!!

	int i, j;

	this->width = 10;
	this->height = 10;
	
	for (j = 0; j < this->height; j++)
	  for (i = 0; i < this->width; i++)
	    {
		  this->squares[i][j].height = 0;
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

	this->set_environment(ENVIRONMENT_GRASS);
  
	this->player_characters[0] = new c_player_character(PLAYER_STAROVOUS);

	this->player_characters[0]->set_position(8.0,8.0);

	this->player_characters[1] = NULL;
	this->player_characters[2] = NULL;
  }

//--------------------------------------------------

c_map::~c_map()
  {
	int i;

	for (i = 0; i < 3; i++)                // free players
	  delete this->player_characters[i];
	                                       // free bitmaps
	al_destroy_bitmap(this->tile = NULL);
	al_destroy_bitmap(this->tile_cliff_south_1 = NULL);
	al_destroy_bitmap(this->tile_cliff_south_2 = NULL);
	al_destroy_bitmap(this->tile_cliff_southwest_1 = NULL);
	al_destroy_bitmap(this->tile_cliff_southwest_2 = NULL);
	al_destroy_bitmap(this->tile_cliff_southeast_1 = NULL);
	al_destroy_bitmap(this->tile_cliff_southeast_2 = NULL);
	al_destroy_bitmap(this->tile_cliff_west = NULL);
	al_destroy_bitmap(this->tile_cliff_east = NULL);
	al_destroy_bitmap(this->tile_cliff_north = NULL);
	al_destroy_bitmap(this->tile_cliff_northwest = NULL);
  }

//--------------------------------------------------

void c_map::draw(int x, int y)
  {
	int i, j, help_height;

	// we'll draw the map from ground level up, from north to south:

    for (help_height = 0; help_height < 3; help_height++)
      for (j = 0; j < this->height; j++)
        for (i = 0; i < this->width; i++)
		  if (this->squares[i][j].height == help_height)
		    {
			  al_draw_bitmap(this->tile,x + i * 64,y + j * 50 - 27 * help_height,0); // draw floor

			  if (help_height != 0)                                                  // draw cliffs
			    {
				  if (this->get_height(i,j + 1) == help_height - 1)                  // south
				    {
					  al_draw_bitmap(this->tile_cliff_south_1,x + i * 64,y + j * 50 - 27 * help_height + 50,0);
				      
					  if (this->get_height(i + 1,j + 1) != help_height &&
						this->get_height(i + 1,j) != help_height)                    // southeast 1
					    al_draw_bitmap(this->tile_cliff_southeast_1,x + i * 64 + 64,y + j * 50 - 27 * help_height + 50,0);
				    
					  if (this->get_height(i - 1,j + 1) != help_height &&
						  this->get_height(i - 1,j) != help_height)                  // southwest 1
					    al_draw_bitmap(this->tile_cliff_southwest_1,x + i * 64 - 10,y + j * 50 - 27 * help_height + 50,0);
				    }
				  else if (this->get_height(i,j + 1) == help_height - 2)
				    {
					  al_draw_bitmap(this->tile_cliff_south_2,x + i * 64,y + j * 50 - 27 * help_height + 50,0);

					  if (this->get_height(i + 1,j + 1) != help_height &&
						this->get_height(i + 1,j) != help_height)                    // southeast 2
					    al_draw_bitmap(this->tile_cliff_southeast_2,x + i * 64 + 64,y + j * 50 - 27 * help_height + 50,0);
				    
					  if (this->get_height(i - 1,j + 1) != help_height &&
						  this->get_height(i - 1,j) != help_height)                  // southwest 2
					    al_draw_bitmap(this->tile_cliff_southwest_2,x + i * 64 - 10,y + j * 50 - 27 * help_height + 50,0);
				    }

				  if (this->get_height(i,j - 1) != help_height)                      // north
				    {
                      al_draw_bitmap(this->tile_cliff_north,x + i * 64,y + j * 50 - 27 * help_height - 10,0);
				    
					  if (this->get_height(i + 1,j - 1) != help_height &&
						  this->get_height(i + 1,j) != help_height)                  // northeast
                        al_draw_bitmap(this->tile_cliff_northeast,x + i * 64 + 64,y + j * 50 - 27 * help_height - 10,0);

					  if (this->get_height(i - 1,j - 1) != help_height &&
						  this->get_height(i - 1,j) != help_height)                  // northwest
                        al_draw_bitmap(this->tile_cliff_northwest,x + i * 64 -10,y + j * 50 - 27 * help_height - 10,0);
				    }

			      if (this->get_height(i - 1,j) != help_height)                      // west
                    al_draw_bitmap(this->tile_cliff_west,x + i * 64 - 10,y + j * 50 - 27 * help_height,0);

				  if (this->get_height(i + 1,j) != help_height)                      // east
                    al_draw_bitmap(this->tile_cliff_east,x + i * 64 + 64,y + j * 50 - 27 * help_height,0);
			    }
		    }

	
	  this->player_characters[0]->draw(50,50);
  }

//--------------------------------------------------