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
	
	this->text_font = al_load_ttf_font("resources/benegraphic.ttf",40,0);
	
	this->menu_top = al_load_bitmap("resources/menu_top.png");
	this->menu_middle = al_load_bitmap("resources/menu_middle.png");
	this->menu_bottom = al_load_bitmap("resources/menu_bottom.png");
	this->menu_selection = al_load_bitmap("resources/menu_selection.png");
	this->info_background = NULL;
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

void c_menu::set_menu_items(string items[], int number_of_items)
  {
	int i;

	this->menu_type = MENU_TYPE_NORMAL;
	this->number_of_text_lines = number_of_items;

	if (items == NULL)
	  return;

	for (i = 0; i < number_of_items; i++)
	  this->text_lines[i] = items[i];
  }

//-----------------------------------------------

void c_menu::set_menu_info_screen(string image_path, string text_lines[], int number_of_lines)
  {
	int i;

	this->menu_type = MENU_TYPE_INFO;

	this->number_of_text_lines = number_of_lines;
	
	for (i = 0; i < number_of_lines; i++)
	  this->text_lines[i] = text_lines[i];

	this->info_background = al_load_bitmap(image_path.c_str());

	this->effect_time = al_current_time() + 1.0;
  }

//-----------------------------------------------

int c_menu::update()
  {
	int x, y, i, alpha_value;
	double time_difference;
	
	al_clear_to_color(al_map_rgb(255,255,255));

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
		  else if (this->io->key_right)
		    {
		      if (!this->pressed)
			    {
				  this->pressed = true;
			      return this->current_item;
			    }
		    }
		  else if (this->io->key_left)
		    {
		      if (!this->pressed)
			    {
			  	  this->pressed = true;
			      return this->number_of_text_lines - 1;
			    }
		    }
		  else
		    this->pressed = false;

		  // now draw the menu:

		  x = this->io->screen_x / 2 - 162;
		  y = 20;

		  al_draw_bitmap(this->menu_top,x,y,0);

		  al_draw_text(this->text_font,al_map_rgb(0,0,0),x + 75,y + 65,0,this->text_lines[0].c_str());

		  y += 101;

		  for (i = 0; i < this->number_of_text_lines - 2; i++)
		    {
		      al_draw_bitmap(this->menu_middle,x,y,0);
			  al_draw_text(this->text_font,al_map_rgb(0,0,0),x + 75,y + 12,0,this->text_lines[i + 1].c_str());
			  y += 58;
		    }
		  
		  al_draw_bitmap(this->menu_bottom,x,y,0);

		  if (this->number_of_text_lines >= 2)   // draw the last menu item
			al_draw_text(this->text_font,al_map_rgb(0,0,0),x + 75,y + 10,0,this->text_lines[this->number_of_text_lines - 1].c_str());

		  al_draw_bitmap(this->menu_selection,x - 65,85 + this->current_item * 55,0);  // highlight the selected item

		  break;

		case MENU_TYPE_INFO:

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

		  break;

		case MENU_TYPE_LEVEL_CHOOSE:
		  break;
	  }

	return -1;
  }

//-----------------------------------------------