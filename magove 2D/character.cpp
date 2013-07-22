/**
 * Character class implementation file.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
 */

#include "character.h"

//--------------------------------------------------

void c_character::move_by(double x, double y)
  {
	this->position_x += x;
	this->position_y += y;
  }

//--------------------------------------------------

void c_character::set_direction(t_direction direction)
  {
	this->direction = direction;
  }

//--------------------------------------------------

void c_character::set_position(double x, double y)
  {
	this->position_x = x;
	this->position_y = y;
  }

//--------------------------------------------------

double c_character::get_position_x()
  {
	return this->position_x;
  }
	
//--------------------------------------------------

double c_character::get_position_y()
  {
	return this->position_y;
  }

//--------------------------------------------------

int c_character::get_square_x()
  {
	return floor(this->position_x + 0.3);
  }

//--------------------------------------------------

int c_character::get_square_y()
  {
	return floor(this->position_y + 0.3) + 1;
  }

//--------------------------------------------------