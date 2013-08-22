/**
 * Menu class implementation.
 *
 * authors: Miloslav Číž
 * year: 2013
 */

#include "menu.h"

//-----------------------------------------------

c_menu::c_menu(t_input_output_state *input_output_state)
  {
	this->current_item = 0;
	this->menu_type = MENU_TYPE_NORMAL;
	this->number_of_levels = 0;
	this->number_of_text_lines = 0;
	this->io = input_output_state;
	this->pressed = false;
	
	this->text_font = al_load_ttf_font("resources/benegraphic.ttf",38,0);
	
	this->menu_top = al_load_bitmap("resources/menu_top.png");
	this->menu_middle = al_load_bitmap("resources/menu_middle.png");
	this->menu_bottom = al_load_bitmap("resources/menu_bottom.png");
	this->menu_selection = al_load_bitmap("resources/menu_selection.png");
	this->info_background = NULL;

	level_number_positions_x[0] = 270;
	level_number_positions_y[0] = 390;
	level_number_positions_x[1] = 350;
	level_number_positions_y[1] = 390;
	level_number_positions_x[2] = 270;
	level_number_positions_y[2] = 310;
	level_number_positions_x[3] = 350;
	level_number_positions_y[3] = 310;
	level_number_positions_x[4] = 490;
	level_number_positions_y[4] = 200;
	level_number_positions_x[5] = 465;
	level_number_positions_y[5] = 220;
	level_number_positions_x[6] = 435;
	level_number_positions_y[6] = 230;
	level_number_positions_x[7] = 390;
	level_number_positions_y[7] = 240;
	level_number_positions_x[8] = 140;
	level_number_positions_y[8] = 360;
	level_number_positions_x[9] = 160;
	level_number_positions_y[9] = 310;
	level_number_positions_x[10] = 195;
	level_number_positions_y[10] = 280;
	level_number_positions_x[11] = 230;
	level_number_positions_y[11] = 240;
	level_number_positions_x[12] = 280;
	level_number_positions_y[12] = 255;
	level_number_positions_x[13] = 330;
	level_number_positions_y[13] = 255;
	level_number_positions_x[14] = 280;
	level_number_positions_y[14] = 220;
	level_number_positions_x[15] = 330;
	level_number_positions_y[15] = 220;
	level_number_positions_x[16] = 270;
	level_number_positions_y[16] = 180;
	level_number_positions_x[17] = 340;
	level_number_positions_y[17] = 180;
	level_number_positions_x[18] = 270;
	level_number_positions_y[18] = 150;
	level_number_positions_x[19] = 340;
	level_number_positions_y[19] = 150;
	level_number_positions_x[20] = 270;
	level_number_positions_y[20] = 120;
	level_number_positions_x[21] = 340;
	level_number_positions_y[21] = 120;
  }

//-----------------------------------------------

c_menu::~c_menu()
  {
	al_destroy_bitmap(this->menu_top);
    al_destroy_bitmap(this->menu_middle);
	al_destroy_bitmap(this->menu_bottom);
	al_destroy_bitmap(this->menu_selection);
	al_destroy_font(this->text_font);
  }

//-----------------------------------------------

void c_menu::set_menu_items(string items[], int number_of_items, string title, bool keep_cursor)
  {
	int i;

	if (!keep_cursor || this->menu_type != MENU_TYPE_NORMAL)
	  this->current_item = 0;
	
	this->title = title;
	this->menu_type = MENU_TYPE_NORMAL;
	this->number_of_text_lines = number_of_items;

	if (items == NULL)
	  return;

	for (i = 0; i < number_of_items; i++)
	  this->text_lines[i] = items[i];
  }

//-----------------------------------------------

void c_menu::set_menu_info_screen(string image_path, string text_lines[], int number_of_lines, double duration, unsigned char bg_red, unsigned char bg_green, unsigned char bg_blue)
  {
	int i;

	this->menu_type = MENU_TYPE_INFO;

	this->bg_color[0] = bg_red;
	this->bg_color[1] = bg_green;
	this->bg_color[2] = bg_blue;

	this->number_of_text_lines = number_of_lines;
	
	for (i = 0; i < number_of_lines; i++)
	  this->text_lines[i] = text_lines[i];

	if (image_path.length() != 0)
	  this->info_background = al_load_bitmap(image_path.c_str());
	else
	  this->info_background = NULL;

	this->effect_time = al_current_time() + 1.0;
	this->fading_in = true;
	this->fading_out = false;

	if (duration < 0.0)
	  this->screen_end_time = -1.0;
	else
	  this->screen_end_time = al_current_time() + duration;
  }

//-----------------------------------------------

void c_menu::set_menu_choose_level(int number_of_levels)
  {
	this->current_item = 0;
	this->menu_type = MENU_TYPE_LEVEL_CHOOSE;
	this->number_of_levels = number_of_levels;
	this->info_background = al_load_bitmap("resources/castle.png");
  }

//-----------------------------------------------

int c_menu::update()
  {
	int x, y, i, alpha_value, return_value;
	double time_difference;

	return_value = -1;

	switch (this->menu_type)
	  {
	    case MENU_TYPE_NORMAL:

		  if (this->io->key_down)
		    {
		      if (!this->pressed)
			    this->current_item++;

			  this->pressed = true;

			  if (this->current_item >= this->number_of_text_lines)
			    this->current_item = this->number_of_text_lines - 1;
		    }
		  else if (this->io->key_up)
		    {
		      if (!this->pressed)
			    this->current_item--;
			
			  this->pressed = true;

			  if (this->current_item < 0)
			    this->current_item = 0;
		    }
		  else if (this->io->key_right || this->io->key_use)
		    {
		      if (!this->pressed)
			    {
				  this->pressed = true;
			      return_value = this->current_item;
			    }
		    }
		  else if (this->io->key_left || this->io->key_back)
		    {
		      if (!this->pressed)
			    {
			  	  this->pressed = true;
			      return_value = this->number_of_text_lines - 1;
			    }
		    }
		  else
		    this->pressed = false;

		  // now draw the menu:

		  al_clear_to_color(al_map_rgb(255,255,255));
		  al_draw_text(this->text_font,al_map_rgb(200,200,200),5,5,0,VERSION);

		  x = this->io->screen_x / 2 - 162;
		  y = 20;

		  al_draw_bitmap(this->menu_top,x,y,0);
		  al_draw_text(this->text_font,al_map_rgb(200,100,100),x + 55,y - 10,0,this->title.c_str());
		  al_draw_text(this->text_font,al_map_rgb(0,0,0),x + 60,y + 65,0,this->text_lines[0].c_str());

		  y += 101;

		  for (i = 0; i < this->number_of_text_lines - 2; i++)
		    {
		      al_draw_bitmap(this->menu_middle,x,y,0);
			  al_draw_text(this->text_font,al_map_rgb(0,0,0),x + 60,y + 12,0,this->text_lines[i + 1].c_str());
			  y += 58;
		    }
		  
		  al_draw_bitmap(this->menu_bottom,x,y,0);

		  if (this->number_of_text_lines >= 2)   // draw the last menu item
			al_draw_text(this->text_font,al_map_rgb(0,0,0),x + 60,y + 10,0,this->text_lines[this->number_of_text_lines - 1].c_str());

		  al_draw_bitmap(this->menu_selection,x - 65,85 + this->current_item * 55,0);  // highlight the selected item

		  break;

		case MENU_TYPE_INFO:

		  // check if the screen should disappear:

		  if (this->screen_end_time < 0.0)
		    {
			  if (!this->fading_in && !this->fading_out && (this->io->key_use || this->io->key_down ||
				this->io->key_left || this->io->key_up || this->io->key_right || this->io->key_use ||
				this->io->key_back))
		        { 
			      this->fading_out = true;
			      this->effect_time = al_current_time();
		        }
		    }
		  else
		    { 
		      if (!this->fading_in && !this->fading_out && this->screen_end_time < al_current_time())
			    {
				  this->fading_out = true;
			      this->effect_time = al_current_time();
			    }
		    }

		  // draw the screen:

		  al_clear_to_color(al_map_rgb(this->bg_color[0],this->bg_color[1],this->bg_color[2]));

		  x = this->io->screen_x / 2;
		  
		  if (this->info_background != NULL)
			x -= al_get_bitmap_width(this->info_background) / 2;

		  y = 20;

		  if (this->info_background != NULL)
			al_draw_bitmap(this->info_background,x,y,0);

		  y = this->io->screen_y - this->number_of_text_lines * 50;

		  x = this->io->screen_x / 2;

		  for (i = 0; i < this->number_of_text_lines; i++)
		    {
			  al_draw_text(this->text_font,al_map_rgb(0,0,0),x,y,ALLEGRO_ALIGN_CENTRE,this->text_lines[i].c_str());
		      y += 50;  
		    }

		  // the fade in effect:

		  if (fading_in)
		    {
			  time_difference = this->effect_time - al_current_time();
		    
			  if (time_difference > 0)
		        {
			      alpha_value = time_difference * 255;

			      if (alpha_value > 255)
			        alpha_value = 255;
			      else if (alpha_value < 0)
				    alpha_value = 0;

		          al_draw_filled_rectangle(0,0,this->io->screen_x - 1,this->io->screen_y - 1,al_map_rgba(0,0,0,alpha_value));
		        }
			  else
				fading_in = false;
		    }
		  else if (fading_out)
		    {
			  time_difference = al_current_time() - this->effect_time;

			  alpha_value = time_difference * 255;

			  if (alpha_value > 255)
				return 1;

			  al_draw_filled_rectangle(0,0,this->io->screen_x - 1,this->io->screen_y - 1,al_map_rgba(0,0,0,alpha_value));
		    }

		  break;

		case MENU_TYPE_LEVEL_CHOOSE:
          if (this->io->key_down)
		    {
		      if (!this->pressed)
			    this->current_item--;

			  this->pressed = true;

			  if (this->current_item < 0)
				this->current_item = this->number_of_levels;
		    }
		  else if (this->io->key_up)
		    {
		      if (!this->pressed)
			    this->current_item++;
			
			  this->pressed = true;

			  if (this->current_item > this->number_of_levels)
			    this->current_item = 0;
		    }
		  else if (this->io->key_right || this->io->key_use)
		    { 
			  if (!this->pressed)
			    { 
			      return_value = this->current_item;
			      this->pressed = true;
			    }
		    } 
		  else if (this->io->key_left || this->io->key_back)
		    {
			  if (!this->pressed)
			    {
			      return_value = this->number_of_levels + 1;
			      this->pressed = true;
			    }
		    }
		  else
		    this->pressed = false;
		  
		  al_clear_to_color(al_map_rgb(41,43,38));
		  x = this->io->screen_x / 2 - 320;
		  al_draw_bitmap(this->info_background,x,0,0);

		  for (i = 0; i < this->number_of_levels; i++) // draw level numbers
		    {
			  if (i == this->current_item)
                al_draw_filled_circle(x + this->level_number_positions_x[i] + 17,this->level_number_positions_y[i] + 20,20,al_map_rgb(255,0,0));

			  al_draw_text(this->text_font,al_map_rgb(0,0,0),x + this->level_number_positions_x[i],this->level_number_positions_y[i],0,to_string((long long) i + 1).c_str());
		    }

		  if (this->current_item == this->number_of_levels)
		    al_draw_filled_rectangle(x + 310,500,x + 370,540,al_map_rgb(255,0,0));

		  al_draw_text(this->text_font,al_map_rgb(0,0,0),x + 320,500,0,"intro");

		  break;
	  }

	return return_value;
  }

//-----------------------------------------------