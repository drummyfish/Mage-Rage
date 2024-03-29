﻿/**
 * Menu class implementation.
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
	this->easter_egg_started = -1.0;
	
	this->text_font = al_load_ttf_font("resources/benegraphic.ttf",38,0);
	
	this->menu_top = al_load_bitmap("resources/menu_top.png");
	this->menu_middle = al_load_bitmap("resources/menu_middle.png");
	this->menu_bottom = al_load_bitmap("resources/menu_bottom.png");
	this->menu_selection = al_load_bitmap("resources/menu_selection.png");
	this->menu_border = al_load_bitmap("resources/menu_border.png");
	this->easter_egg = al_load_bitmap("resources/awesome.png");
	this->click_sound = al_load_sample("resources/menu_click.wav");
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
	al_destroy_bitmap(this->menu_border);
	al_destroy_bitmap(this->easter_egg);
	al_destroy_font(this->text_font);
	al_destroy_sample(this->click_sound);
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
	this->current_item = number_of_levels - 1;  // select the last level
	this->menu_type = MENU_TYPE_LEVEL_CHOOSE;
	this->number_of_levels = number_of_levels;
	this->info_background = al_load_bitmap("resources/castle.png");
  }

//-----------------------------------------------

int c_menu::update()
  {
	int x, y, i, alpha_value, return_value, border1_x, border2_x, border_y, red, green, blue, highlight_offset_x, highlight_offset_y;
	double time_difference;
	bool end;

	return_value = -1;

	switch (this->menu_type)
	  {
	    case MENU_TYPE_NORMAL:

		  if (this->io->key_down)
		    {
		      if (!this->pressed)
			    {
			      this->current_item++;
				  al_play_sample(this->click_sound,0.4,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
			    }

			  this->pressed = true;

			  if (this->current_item >= this->number_of_text_lines)
			    this->current_item = this->number_of_text_lines - 1;
		    }
		  else if (this->io->key_up)
		    {
		      if (!this->pressed)
			    {
			      this->current_item--;
			      al_play_sample(this->click_sound,0.4,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
			    }
			
			  this->pressed = true;

			  if (this->current_item < 0)
			    this->current_item = 0;
		    }
		  else if (this->io->key_right || this->io->key_use)
		    {
		      if (!this->pressed)
			    {
				  this->pressed = true;
				  al_play_sample(this->click_sound,0.4,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
			      return_value = this->current_item;
			    }
		    }
		  else if (this->io->key_left || this->io->key_back)
		    {
		      if (!this->pressed)
			    {
			  	  this->pressed = true;
				  al_play_sample(this->click_sound,0.4,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
			      return_value = this->number_of_text_lines - 1;
			    }
		    }
		  else
		    this->pressed = false;

		  // now draw the menu:

		  border1_x = 40;
		  border2_x = this->io->screen_x - 83;
		  border_y = -134 + ((int) (al_current_time() * 100)) % 134;

		  highlight_offset_x = (int) (sin(al_current_time()) * 10);
          highlight_offset_y = (int) (cos(al_current_time()) * 10);

		  al_clear_to_color(al_map_rgb(255,255,255));

		  while (border_y < this->io->screen_y)
		    {
			  al_draw_bitmap(this->menu_border,border1_x,border_y,0);
			  al_draw_bitmap(this->menu_border,border2_x,border_y,0);
			  border_y += 134;
		    }

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

		  al_draw_bitmap(this->menu_selection,x - 65 + highlight_offset_x,85 + this->current_item * 55 + highlight_offset_y,0);  // highlight the selected item

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

		  if (this->fading_in)
		    {
			  time_difference = this->effect_time - al_current_time();
		    
			  if (time_difference > 0)
		        {
			      alpha_value = time_difference * 255;

			      if (alpha_value > 255)
			        alpha_value = 255;
			      else if (alpha_value < 0)
				    alpha_value = 0;

		          al_draw_filled_rectangle(0,0,this->io->screen_x,this->io->screen_y,al_map_rgba(0,0,0,alpha_value));
		        }
			  else
				this->fading_in = false;
		    }
		  
		  if (this->fading_out)
		    {
			  time_difference = al_current_time() - this->effect_time;

			  alpha_value = time_difference * 255;

			  end = false;

			  if (alpha_value > 255)
			    {
				  alpha_value = 255;
				  end = true;
			    }
			  else if (alpha_value < 0)
				alpha_value = 0;

			  al_draw_filled_rectangle(0,0,this->io->screen_x,this->io->screen_y,al_map_rgba(0,0,0,alpha_value));
		    
		      if (end)
				return 1;
		    }

		  break;

		case MENU_TYPE_LEVEL_CHOOSE:
          if (this->io->key_down)
		    {
		      if (!this->pressed)
			    {
				  al_play_sample(this->click_sound,0.4,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
			      this->current_item--;
			    }

			  this->pressed = true;

			  if (this->current_item < 0)
				this->current_item = this->number_of_levels;
		    }
		  else if (this->io->key_up)
		    {
		      if (!this->pressed)
			    {
				  al_play_sample(this->click_sound,0.4,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
			      this->current_item++;
			    }

			  this->pressed = true;

			  if (this->current_item > this->number_of_levels)
			    this->current_item = 0;
		    }
		  else if (this->io->key_right || this->io->key_use)
		    { 
			  if (!this->pressed)
			    { 
			      return_value = this->current_item;
				  al_play_sample(this->click_sound,0.4,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
			      this->pressed = true;
			    }
		    } 
		  else if (this->io->key_left || this->io->key_back)
		    {
			  if (!this->pressed)
			    {
			      return_value = this->number_of_levels + 1;
				  al_play_sample(this->click_sound,0.4,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
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

	if (this->easter_egg_started >= 0.0) // display easter egg
	  {
		time_difference = al_current_time() - this->easter_egg_started;

		if (time_difference <= 2.0)
		  al_draw_bitmap(this->easter_egg,(int) (-112 + (time_difference / 2) * (this->io->screen_x / 3)),20,0);
		else if (time_difference <= 4.0)
		  {
		    al_draw_bitmap(this->easter_egg,this->io->screen_x / 3 - 112,20,0); 
				
			switch((int) (al_current_time() * 5) % 10) // some random colors for the text
			  {
			    case 0: red = 0; green = 55; blue = 0; break;
			    case 1: red = 50; green = 0; blue = 63; break;
			    case 2: red = 170; green = 55; blue = 80; break;
			    case 3: red = 7; green = 10; blue = 244; break;
			    case 4: red = 30; green = 180; blue = 25; break;
			    case 5: red = 0; green = 113; blue = 0; break;
			    case 6: red = 0; green = 55; blue = 10; break;
			    case 7: red = 256; green = 0; blue = 190; break;
			    case 8: red = 30; green = 200; blue = 50; break;
			    case 9: red = 200; green = 200; blue = 180; break;
			  }

			al_draw_text(this->text_font,al_map_rgb(red,green,blue),this->io->screen_x / 3 - 200,2,0,"HELLO!");
		  }
		else if (time_difference <= 6.0)
		  al_draw_bitmap(this->easter_egg,(int) (-112 + (1 - ((time_difference - 4) / 2)) * this->io->screen_x / 3),20,0);
		else
		  this->easter_egg_started = -1;
	  }

	return return_value;
  }

//-----------------------------------------------

void c_menu::display_easter_egg()
  {
	if (this->easter_egg_started >= 0.0)
	  return;

	this->easter_egg_started = al_current_time(); // two seconds for the easter egg
  }

//-----------------------------------------------