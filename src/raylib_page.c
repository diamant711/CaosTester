/*******************************************************************************************
*
*   raylib [core] example - Basic window (adapted for HTML5 platform)
*
*   This example is prepared to compile for PLATFORM_WEB, PLATFORM_DESKTOP and PLATFORM_RPI
*   As you will notice, code structure is slightly diferent to the other examples...
*   To compile it for PLATFORM_WEB just uncomment #define PLATFORM_WEB at beginning
*
*   This example has been created using raylib 1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include <stdlib.h>

#include "../inc/raylib.h"
#include "../inc/jet.h"

#include "../inc/temperature_matrix.h"

#define PIXEL 4
#define WINDOW_WIDTH ((PIXEL*NX) + 3*NX)
#define WINDOW_HEIGHT ((PIXEL*NY) + 3*NY)
#define FPS 10

//#define PLATFORM_WEB

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
//const int screenWidth = 800;
//const int screenHeight = 450;
  unsigned int n_step = 0;
//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------

Color TtoC (double, double, double);

void UpdateDrawFrame(void);     // Update and Draw one frame

//----------------------------------------------------------------------------------
// Main Enry Point
//----------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Rayleigh-Benard convection");

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(FPS);
    //--------------------------------------------------------------------------------------

    // Main loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------

Color TtoC (double cold, double hot,  double t) {
/*
(x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min
*/
if ((t <= hot) && (t >= cold)) {
  int index = (t - cold) * (JETSIZE - 1) / ( hot - cold );
  return jet[index];
  } else {
      return (Color){0, 0, 0, 0};
  }
}

void UpdateDrawFrame(void)
{
  // Update
  //----------------------------------------------------------------------------------
  // TODO: Update your variables here
  if (n_step >= N_STEPS) {
    exit(0);
  }
  //----------------------------------------------------------------------------------

  // Draw
  //----------------------------------------------------------------------------------
  BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Rayleigh-Benard Convection", 190, 200, 20, LIGHTGRAY);

    for(unsigned int i = 0; i < NX; ++i) {
      for(unsigned int k = 0; k < NY; ++k) {
        DrawRectangle((WINDOW_WIDTH/2 - NX*PIXEL/2) + i*PIXEL, 
                      (WINDOW_HEIGHT/2 + NY*PIXEL/2) - k*PIXEL, 
                       PIXEL, PIXEL, TtoC(cold_temp, hot_temp, T[i][k][n_step]));
      }
    }
    int posY = 5;
    for(unsigned int i = 0; i < JETSIZE; ++i) {
       DrawRectangle(5, posY, 5, 1, jet[i]);
       posY += 1;
    }

  EndDrawing();
  //----------------------------------------------------------------------------------

  ++n_step;
}
