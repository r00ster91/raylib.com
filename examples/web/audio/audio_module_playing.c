/*******************************************************************************************
*
*   raylib [audio] example - Module playing (streaming)
*
*   NOTE: This example requires OpenAL Soft library installed
*
*   This example has been created using raylib 1.5 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

#if defined(PLATFORM_ANDROID)
    #include "android_native_app_glue.h"
#endif

#define MAX_CIRCLES 32

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef struct {
    Vector2 position;
    float radius;
    float alpha;
    float speed;
    Color color;
} CircleWave;

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
int screenWidth = 800;
int screenHeight = 450;

Color colors[14] = { ORANGE, RED, GOLD, LIME, BLUE, VIOLET, BROWN, LIGHTGRAY, PINK,
                     YELLOW, GREEN, SKYBLUE, PURPLE, BEIGE };

// Creates ome circles for visual effect
CircleWave circles[MAX_CIRCLES];

Music xm;

float timePlayed = 0.0f;
static bool pause = false;

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
    InitWindow(screenWidth, screenHeight, "raylib [audio] example - module playing (streaming)");
#endif

    InitAudioDevice();              // Initialize audio device
    
    for (int i = MAX_CIRCLES - 1; i >= 0; i--)
    {
        circles[i].alpha = 0.0f;
        circles[i].radius = GetRandomValue(10, 40);
        circles[i].position.x = GetRandomValue(circles[i].radius, screenWidth - circles[i].radius);
        circles[i].position.y = GetRandomValue(circles[i].radius, screenHeight - circles[i].radius);
        circles[i].speed = (float)GetRandomValue(1, 100)/20000.0f;
        circles[i].color = colors[GetRandomValue(0, 13)];
    }

    xm = LoadMusicStream("resources/mini1111.xm");
    
    PlayMusicStream(xm);            // Play module stream
    
#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadMusicStream(xm);          // Unload music stream buffers from RAM
    
    CloseAudioDevice();             // Close audio device (music streaming is automatically stopped)

    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
#if !defined(PLATFORM_ANDROID)
    return 0;
#endif
}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    UpdateMusicStream(xm);        // Update music buffer with new stream data
    
    // Restart music playing (stop and play)
    if (IsKeyPressed(KEY_SPACE)) 
    {
        StopMusicStream(xm);
        PlayMusicStream(xm);
    }
    
    // Pause/Resume music playing 
    if (IsKeyPressed(KEY_P))
    {
        pause = !pause;
        
        if (pause) PauseMusicStream(xm);
        else ResumeMusicStream(xm);
    }
    
    // Get timePlayed scaled to bar dimensions
    timePlayed = GetMusicTimePlayed(xm)/GetMusicTimeLength(xm)*(screenWidth - 40);
        
    for (int i = MAX_CIRCLES - 1; i >= 0; i--)
    {
        circles[i].alpha += circles[i].speed;
        circles[i].radius += circles[i].speed*10.0f;
        
        if (circles[i].alpha > 1.0f) circles[i].speed *= -1;
        
        if (circles[i].alpha <= 0.0f)
        {
            circles[i].alpha = 0.0f;
            circles[i].radius = GetRandomValue(10, 40);
            circles[i].position.x = GetRandomValue(circles[i].radius, screenWidth - circles[i].radius);
            circles[i].position.y = GetRandomValue(circles[i].radius, screenHeight - circles[i].radius);
            circles[i].color = colors[GetRandomValue(0, 13)];
            circles[i].speed = (float)GetRandomValue(1, 100)/20000.0f;
        }
    }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);
        
        for (int i = MAX_CIRCLES - 1; i >= 0; i--)
        {
            DrawCircleV(circles[i].position, circles[i].radius, Fade(circles[i].color, circles[i].alpha));
        }
        
        // Draw time bar
        DrawRectangle(20, screenHeight - 20 - 12, screenWidth - 40, 12, LIGHTGRAY);
        DrawRectangle(20, screenHeight - 20 - 12, (int)timePlayed, 12, MAROON);
        DrawRectangleLines(20, screenHeight - 20 - 12, screenWidth - 40, 12, GRAY);

    EndDrawing();
    //----------------------------------------------------------------------------------
}