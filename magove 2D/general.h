#ifndef GENERAL_H
#define GENERAL_H

/**
 * General definitions and declarations.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
 */

#include <iostream>
#include <string>
#include <math.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"

#define MAP_MAX_WIDTH 30            // maximum map width in squares
#define MAP_MAX_HEIGHT 30           // maximum map height in squares

typedef enum
  {
	/**
      Possible directions in 2D space.
    */

    DIRECTION_NORTH,
	DIRECTION_EAST,
	DIRECTION_SOUTH,
	DIRECTION_WEST
  } t_direction;

typedef enum
  {
	/**
      Those are possible map environments.
    */

	ENVIRONMENT_GRASS,
	ENVIRONMENT_DIRT,
	ENVIRONMENT_SNOW,
	ENVIRONMENT_CASTLE
  } t_environment;

typedef enum
  {
	/**
      Possible player characters.
    */

	PLAYER_MIA,
	PLAYER_METODEJ,
	PLAYER_STAROVOUS
  } t_player_type;

typedef enum
  {
	SQUARE_NORMAL,
	SQUARE_WATER,
	SQUARE_ICE
  } t_square_type;

typedef struct
  {
	/**
      Holds info about one map square.
    */

	int height;         /** square height, min is 0, max is 2 */
	t_square_type type; /** square type, like normal, water, ice and so on. */ 
  } t_map_square;

typedef struct
  {
	/**
	  Holds information about input state, such as
	  keys being pressed, mouse position and so on.
	*/

	bool key_up;        /** key up */
	bool key_right;     /** key right */
	bool key_down;      /** key down */
	bool key_left;      /** key left */
	bool key_1;         /** key switch to player 1 */
	bool key_2;         /** key switch to player 2 */
	bool key_3;         /** key switch to player 3 */

	int mouse_x;        /** mouse x position */
	int mouse_y;        /** mouse y position */

  } t_input_state;

typedef enum
  {
	ANIMATION_NONE,
	ANIMATION_RUN,
	ANIMATION_CAST
  } t_animation_type;

typedef enum
  {
	/**
	  Possible map object types.
	*/

	OBJECT_TREE,
	OBJECT_CRATE,
	OBJECT_STONE,
	OBJECT_LEVER
  } t_object_type;
#endif