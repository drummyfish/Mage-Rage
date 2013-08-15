/**
 * Associative array class implementation.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
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

	 while (getline(file, line))
       {
		 separator_position = 0;

		 for (i = 0; (unsigned int) i < line.length(); i++)
		   if (line[i] == ':')
		     {
				separator_position = i;
				break;
		     }

		 key = line.substr(0,i);
		 value = line.substr(i + 1,line.length() - key.length());

		 this->set_text(key,value);
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