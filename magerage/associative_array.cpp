/**
 * Associative array class implementation.
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

#include "associative_array.h"

//-----------------------------------------------

c_associative_array::c_associative_array()
  {
	this->keys = new vector<string>();
	this->values = new vector<string>();
  }
  
//-----------------------------------------------

c_associative_array::~c_associative_array()
  {
	delete this->keys;
	delete this->values;
  }

//-----------------------------------------------
  
void c_associative_array::set_text(string identifier, string value)
  {
	this->delete_text(identifier); // delete the item if it already exists

	this->keys->push_back(identifier);
	this->values->push_back(value);
  }

 //----------------------------------------------

string c_associative_array::get_text(string identifier)
  {
	int i;
		  
	for(i = 0; (unsigned int) i < this->keys->size(); i++)
	  {
		if(this->keys->at(i).compare(identifier) == 0)
		  {
		    return this->values->at(i);
		  }
	  }

	return "";
  }

//-----------------------------------------------

void c_associative_array::delete_text(string identifier)
  { 
	int i;
	
	for(i = 0; (unsigned int) i < this->keys->size(); i++)
	  {
		if(this->keys->at(i).compare(identifier) == 0)
		  {
  		    this->values->erase(this->values->begin() + i,this->values->begin() + i + 1);
			this->keys->erase(this->values->begin() + i,this->values->begin() + i + 1);
		  }
	  }
  }

//-----------------------------------------------

bool c_associative_array::load_from_file(string file_name)
  {
	 ifstream file(file_name);
	 string line, key, value;
	 int i, separator_position;

	 if (!file.is_open())
	   return false;

	 this->keys->clear();
	 this->values->clear();

	 while (getline(file,line))
       { 
		 separator_position = 0;

		 for (i = 0; (unsigned int) i < line.length(); i++)
		   if (line[i] == ':')
		     {
				separator_position = i;
				break;
		     }

		 try
		   {
		     key = line.substr(0,i); 
		     value = line.substr(i + 1,line.length() - key.length());
             this->set_text(key,value);
		   }
		 catch(...)
		   {
		   }
       }

	 file.close();

	 return true;
  }

//-----------------------------------------------

bool c_associative_array::save_to_file(string file_name)
  {
	ofstream file(file_name);
	int i;

	if (!file.is_open())
	  return false;

	for (i = 0; (unsigned int) i < this->keys->size(); i++)
	  {
		file << this->keys->at(i) << ":" << this->values->at(i) << endl;
	  }

	file.close();

	return true;
  }

//-----------------------------------------------