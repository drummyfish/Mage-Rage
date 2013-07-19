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

c_map::c_map()
  {
    // TEMPORARY CODE!!!!!!!!!!!!!!!!!!!!

	int i, j;

	this->width = 10;
	this->height = 10;
	
	for (j = 0; j < this->height; j++)
	  for (i = 0; i < this->width; i++)
		this->squares[i][j].height = 0;

	this->squares[0][0].height = 1;

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
   
	this->environment = ENVIRONMENT_GRASS;

	this->tile = al_load_bitmap("resources/tile_grass.png");
	this->tile_cliff_south_1 = al_load_bitmap("resources/tile_grass_cliff_south_1.png");
	this->tile_cliff_south_2 = al_load_bitmap("resources/tile_grass_cliff_south_2.png");
	this->tile_cliff_southwest_1 = al_load_bitmap("resources/tile_grass_cliff_southwest_1.png");
	this->tile_cliff_southwest_2 = al_load_bitmap("resources/tile_grass_cliff_southwest_2.png");
	this->tile_cliff_southeast_1 = al_load_bitmap("resources/tile_grass_cliff_southeast_1.png");
	this->tile_cliff_southeast_2 = al_load_bitmap("resources/tile_grass_cliff_southeast_2.png");
	this->tile_cliff_west = al_load_bitmap("resources/tile_grass_cliff_west.png");
	this->tile_cliff_east = al_load_bitmap("resources/tile_grass_cliff_east.png");
	this->tile_cliff_north = al_load_bitmap("resources/tile_grass_cliff_north.png");
	this->tile_cliff_northwest = al_load_bitmap("resources/tile_grass_cliff_northwest.png");
	this->tile_cliff_northeast = al_load_bitmap("resources/tile_grass_cliff_northeast.png");
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
  }

//--------------------------------------------------