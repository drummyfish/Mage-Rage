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
#include <stdlib.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_native_dialog.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define MAP_MAX_WIDTH 30                /** maximum map width in squares */
#define MAP_MAX_HEIGHT 30               /** maximum map height in squares */
#define CLIFF_DISTANCE_SOUTH 0.4        /** character collision distance with south cliff (in fraction of one square) */
#define CLIFF_DISTANCE_NORTH 0.1        /** character collision distance with north cliff (in fraction of one square) */
#define CLIFF_DISTANCE_EAST_WEST 0.25   /** character collision distance with east and west cliff (in fraction of one square) */
#define MAX_OBJECTS_PER_SQUARE 5        /** maximum number of objects on one square */
#define MAX_ANIMATION_FRAMES 10         /** maximum number of frames for the c_animation object */
#define MAX_MISSILES_ON_MAP 32          /** maximum number of missiles on the map at given time */
#define MAX_MAGIC_ENERGY 5              /** maximum amount of magic energy for a player */
#define MAX_TEXT_CHARACTERS_PER_LINE 32 /** maximum characters in a displayed text line */
#define MAX_TEXT_LINES 16               /** maximum number of text lines */
#define FIRE_CLOAK_DURATION 10.0        /** duration of fire cloak spell in seconds */
#define MAX_MONSTER_PATH_LENGTH 32      /** maximum length of monster path in "instructions" (array length) */
#define MAX_MONSTERS_ON_MAP 32          /** maximum number of monsters on the map */

using namespace std;

typedef enum
  {
	/**
      Possible directions in 2D space.
    */

    DIRECTION_NORTH,
	DIRECTION_EAST,
	DIRECTION_SOUTH,
	DIRECTION_WEST,
	DIRECTION_NONE
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

	bool key_up;          /** key up */
	bool key_right;       /** key right */
	bool key_down;        /** key down */
	bool key_left;        /** key left */
	bool key_1;           /** key switch to player 1 */
	bool key_2;           /** key switch to player 2 */
	bool key_3;           /** key switch to player 3 */
	bool key_use;         /** key used to manipulate map objects */
	bool key_cast_1;      /** key used to cast spell 1 */
	bool key_cast_2;      /** key used to cast spell 2 */
	bool key_cast_3;      /** key used to cast spell 3 */
	bool key_map_explore; /** key used to move camera freely to explore the map */
	bool mouse_1;         /** mouse button 1 */

	int mouse_x;          /** mouse x position */
	int mouse_y;          /** mouse y position */

	int screen_x;         /** screen resolution x */
	int screen_y;         /** screen resolution y */
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
	ANIMATION_SWITCH_OFF,
	ANIMATION_SKATE
  } t_animation_type;

typedef enum  
  {
	/**
	  Possible displayable animations.
	*/

	DISPLAY_ANIMATION_WATER_SPLASH,
	DISPLAY_ANIMATION_CRATE_SHIFT_NORTH,
	DISPLAY_ANIMATION_COLLAPSE,
	DISPLAY_ANIMATION_MELT,
	DISPLAY_ANIMATION_REFRESH,
	DISPLAY_ANIMATION_TELEPORT,
	DISPLAY_ANIMATION_EXPLOSION,
	DISPLAY_ANIMATION_SHADOW_EXPLOSION
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
	OBJECT_GATE,               /** gate - a gate player must reach in the level */
    OBJECT_SIGN,               /** sign - can display a text */
    OBJECT_TELEPORT_INPUT,     /** teleport which can be stepped into */
	OBJECT_TELEPORT_OUTPUT,    /** teleport in which the player appears rntering the input teleport */
	OBJECT_FLOWERS,            /** flowers (only decoration) */
	OBJECT_FLOWERS2,           /** another flowers (only decoration) */
	OBJECT_BONES,              /** bones (only decoration) */
	OBJECT_CARPET,             /** carpet (only decoration) */
	OBJECT_CARPET2,            /** another carpet (only decoration) */
	OBJECT_WATER_LILY,         /** water lily (water decoration) */
	OBJECT_KEY_RED,            /** red key (part of storyline) */ 
	OBJECT_KEY_GREEN,          /** green key (part of storyline) */
	OBJECT_KEY_BLUE            /** blue key (part of storyline) */
  } t_object_type;

typedef enum
  {
	/**
	  Possible spell missiles.
	*/

	MISSILE_MIA_1,
	MISSILE_MIA_2,
	MISSILE_METODEJ_1,
	MISSILE_STAROVOUS_1,
	MISSILE_STAROVOUS_2
  } t_missile_type; 

typedef enum
  {
	/**
	  Possible monster types.
	*/

	MONSTER_GHOST,          /** can be killed with white magic */
	MONSTER_TROLL           /** can't be killed */
  } t_monster_type;

typedef enum
  {
	/**
	  Possible game states
	*/

	GAME_STATE_PLAYING,
	GAME_STATE_WIN,
	GAME_STATE_LOSE,
	GAME_STATE_PAUSE
  } t_game_state;

#endif