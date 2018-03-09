#ifndef PARAMETERS_H
#define PARAMETERS_H

#define WINDOW_SIZE_X 1200
#define WINDOW_SIZE_Y 600

#define SNAKE_CIRCLE_RADIUS 10
#define FOOD_CIRCLE_RADIUS 5

// EXACT background image size in pixels
#define BACKGROUND_SIZE_X 599
#define BACKGROUND_SIZE_Y 519

// GAME_SIZE = n times the background size
#define GAME_SIZE_X 5
#define GAME_SIZE_Y 5

#define MINIMAP_HEIGHT 120
#define SNAKE_CIRCLE_RADIUS_MINIMAP 2

#define FOOD_NUMBER 500

#define FOOD_PROBA 0.01
#define ADD_TAIL 4

#define INIT_LENGTH 40

#define LOW_SPEED 2
#define HIGH_SPEED 4
#define ROTATION_ANGLE 0.02

#define EPSILON 0.01

// Network Status Codes
#define OK 200
#define INIT 201
#define CONTROLLER 202
#define POSITION 203
#define END 204

#define DISCONNECT 405
#define GAME_FULL 406

#define SERVER_ADDRESS "localhost"
#define SERVER_PORT 8001
#define MAX_CONNECTIONS 100

#endif
