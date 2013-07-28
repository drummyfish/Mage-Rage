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

#define MAP_MAX_WIDTH 30                /// maximum map width in squares
#define MAP_MAX_HEIGHT 30               /// maximum map height in squares
#define CLIFF_DISTANCE_SOUTH 0.4        /// character collision distance with south cliff (in fraction of one square)
#define CLIFF_DISTANCE_NORTH 0.1        /// character collision distance with north cliff (in fraction of one square)
#define CLIFF_DISTANCE_EAST_WEST 0.25   /// character collision distance with east and west cliff (in fraction of one square) 
#define MAX_OBJECTS_PER_SQUARE 5        /// maximum number of objects on one square

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
	OBJECT_STATE_ON,
	OBJECT_STATE_OFF
  } t_object_state;

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
	bool key_use;       /** key used to manipulate map objects */

	int mouse_x;        /** mouse x position */
	int mouse_y;        /** mouse y position */

  } t_input_state;

typedef enum
  {
	ANIMATION_NONE,
	ANIMATION_IDLE,
	ANIMATION_RUN,
	ANIMATION_CAST,
	ANIMATION_SHIFT_NORTH,
	ANIMATION_SHIFT_EAST,
	ANIMATION_SHIFT_SOUTH,
	ANIMATION_SHIFT_WEST,
	ANIMATION_SWITCH_ON,
	ANIMATION_SWITCH_OFF
  } t_animation_type;

typedef enum
  {
	/**
	  Possible map object types.
	*/

	OBJECT_TREE,
	OBJECT_CRATE,
	OBJECT_STONE,
	OBJECT_LEVER,
	OBJECT_BUTTON,
	OBJECT_STAIRS_NORTH,
	OBJECT_STAIRS_EAST,
	OBJECT_STAIRS_SOUTH,
	OBJECT_STAIRS_WEST,
	OBJECT_DOOR_HORIZONTAL,
	OBJECT_DOOR_VERTICAL,
	OBJECT_FOUNTAIN
  } t_object_type;
#endif