/*******************************************************************************************
*
*   raylib [core] example - Storage save/load values (adapted for HTML5 platform)
*
*   This example has been created using raylib 1.4 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

#if defined(PLATFORM_ANDROID)
    #include "android_native_app_glue.h"
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
int screenWidth = 800;
int screenHeight = 450;

int score = 0;
int hiscore = 0;

int framesCounter = 0;

// NOTE: Storage positions must start with 0, directly related to file memory layout
typedef enum { STORAGE_SCORE = 0, STORAGE_HISCORE } StorageData;

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void);     // Update and Draw one frame

//----------------------------------------------------------------------------------
// Main Enry Point
//----------------------------------------------------------------------------------
#if defined(PLATFORM_ANDROID)
void android_main(struct android_app *app) 
#else
int main(void)
#endif
{
    // Initialization
    //--------------------------------------------------------------------------------------
#if defined(PLATFORM_ANDROID)
    InitWindow(screenWidth, screenHeight, app);
#else
    InitWindow(screenWidth, screenHeight, "raylib [core] example - storage save/load values");
#endif

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
 
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
#if !defined(PLATFORM_ANDROID)
    return 0;
#endif
}

void UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    if (IsKeyPressed(KEY_R))
    {
        score = GetRandomValue(1000, 2000);
        hiscore = GetRandomValue(2000, 4000);
    }
    
    if (IsKeyPressed(KEY_ENTER))
    {
        StorageSaveValue(STORAGE_SCORE, score);
        StorageSaveValue(STORAGE_HISCORE, hiscore);
    }
    else if (IsKeyPressed(KEY_SPACE))
    {
        // NOTE: If requested position could not be found, value 0 is returned
        score = StorageLoadValue(STORAGE_SCORE);
        hiscore = StorageLoadValue(STORAGE_HISCORE);
    }
    
    framesCounter++;
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText(FormatText("SCORE: %i", score), 280, 130, 40, MAROON);
        DrawText(FormatText("HI-SCORE: %i", hiscore), 210, 200, 50, BLACK);
        
        DrawText(FormatText("frames: %i", framesCounter), 10, 10, 20, LIME);
        
        DrawText("Press R to generate random numbers", 220, 40, 20, LIGHTGRAY);
        DrawText("Press ENTER to SAVE values", 250, 310, 20, LIGHTGRAY);
        DrawText("Press SPACE to LOAD values", 252, 350, 20, LIGHTGRAY);

    EndDrawing();
    //----------------------------------------------------------------------------------
}