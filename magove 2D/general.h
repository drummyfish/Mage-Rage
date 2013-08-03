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
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define MAP_MAX_WIDTH 30                //* maximum map width in squares */
#define MAP_MAX_HEIGHT 30               //* maximum map height in squares */
#define CLIFF_DISTANCE_SOUTH 0.4        //* character collision distance with south cliff (in fraction of one square) */
#define CLIFF_DISTANCE_NORTH 0.1        //* character collision distance with north cliff (in fraction of one square) */
#define CLIFF_DISTANCE_EAST_WEST 0.25   //* character collision distance with east and west cliff (in fraction of one square) */
#define MAX_OBJECTS_PER_SQUARE 5        //* maximum number of objects on one square */
#define MAX_ANIMATION_FRAMES 10         //* maximum number of frames for the c_animation object */

using namespace std;

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
	OBJECT_STATE_ON,            /** switched on */
	OBJECT_STATE_OFF,           /** sqitched off */
	OBJECT_STATE_ON_ACTIVE      /** switched on and active (for example bursting flames) */
  } t_object_state;

typedef struct
  {
	/**
	  Holds information about input state, such as
	  keys being pressed, mouse position and so on.
	  Also stores information about the screen.
	*/

	bool key_up;        /** key up */
	bool key_right;     /** key right */
	bool key_down;      /** key down */
	bool key_left;      /** key left */
	bool key_1;         /** key switch to player 1 */
	bool key_2;         /** key switch to player 2 */
	bool key_3;         /** key switch to player 3 */
	bool key_use;       /** key used to manipulate map objects */
	bool key_cast_1;    /** key used to cast spell 1 */
	bool key_cast_2;    /** key used to cast spell 2 */
	bool key_cast_3;    /** key used to cast spell 3 */

	int mouse_x;        /** mouse x position */
	int mouse_y;        /** mouse y position */

	int screen_x;       /** screen resolution x */
	int screen_y;       /** screen resolution y */
  } t_input_output_state;

typedef enum
  {
	/**
	  Possible animation types for objects that
	  can play multiple types of animations.
	*/

	ANIMATION_NONE,
	ANIMATION_IDLE,
	ANIMATION_RUN,
	ANIMATION_CAST,
	ANIMATION_USE,
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
	  Possible displayable animations.
	*/

	DISPLAY_ANIMATION_WATER_SPLASH,
	DISPLAY_ANIMATION_CRATE_SHIFT_NORTH
  } t_display_animation;

typedef enum
  {
	/**
	  Possible map object types.
	*/

	OBJECT_TREE,               /** tree - only blocks way */
	OBJECT_TREE_WINTER,        /** winter tree - only blocks way */
	OBJECT_ROCK,               /** rock - only blocks way */
	OBJECT_CRATE,              /** crate - can be shifted and walked on */
	OBJECT_LEVER,              /** lever - can be switched on or off */
	OBJECT_BUTTON,             /** button - can be switched on or off by standing on it */
	OBJECT_STAIRS_NORTH,       /** stairs north - allow access to different height levels */
	OBJECT_STAIRS_EAST,        /** stairs east - allow access to different height levels */
	OBJECT_STAIRS_SOUTH,       /** stairs south - allow access to different height levels */
	OBJECT_STAIRS_WEST,        /** stairs west - allow access to different height levels */
	OBJECT_DOOR_HORIZONTAL,    /** horizontal door - can be opened or closed by other objects */
	OBJECT_DOOR_VERTICAL,      /** vertical door - can be opened or closed by other objects */
	OBJECT_FOUNTAIN,           /** fountain - regenerates player's magic energy */
	OBJECT_FLAMES,             /** flames - bursts flames when on */
	OBJECT_ELEVATOR,           /** elevator - elevator controlled by other objects */
	OBJECT_ICE,                /** ice - blocks way but can be melted */
	OBJECT_GATE                /** gate - a gate player must reach in the level */
  } t_object_type;
#endif