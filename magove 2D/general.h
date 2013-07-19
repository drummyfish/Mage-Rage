#ifndef GENERAL
#define GENERAL

/**
 * General definitions and declarations.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
 */

#include <iostream>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"

typedef enum
  /**
   Possible directions in 2D space.
  */
  {
    DIRECTION_NORTH,
	DIRECTION_EAST,
	DIRECTION_SOUTH,
	DIRECTION_WEST
  } t_direction;

typedef enum
  /**
    Those are possible map environments.
  */
  {
	ENVIRONMENT_GRASS,
	ENVIRONMENT_DIRT,
	ENVIRONMENT_SNOW,
	ENVIRONMENT_CASTLE
  } t_environment;

typedef struct
  /**
    Holds info about one map square.
  */

  {
	int height;    /** square height, min is 0, max is 2 */
  } t_map_square;

#endif