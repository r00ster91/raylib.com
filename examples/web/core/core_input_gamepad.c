/*******************************************************************************************
*
*   raylib [core] example - Gamepad input
*
*   NOTE: This example requires a Gamepad connected to the system
*         raylib is configured to work with the following gamepads: 
*                - Xbox 360 Controller (Xbox 360, Xbox One)
*                - PLAYSTATION(R)3 Controller 
*         Check raylib.h for buttons configuration
*
*   This example has been created using raylib 1.7 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2017 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

#if defined(PLATFORM_ANDROID)
    #include "android_native_app_glue.h"
#endif

// NOTE: Gamepad name ID depends on drivers and OS
#if defined(PLATFORM_RPI)
    #define XBOX360_NAME_ID     "Microsoft X-Box 360 pad"
    #define PS3_NAME_ID         "PLAYSTATION(R)3 Controller"
#else
    #define XBOX360_NAME_ID     "Xbox 360 Controller"
    #define PS3_NAME_ID         "PLAYSTATION(R)3 Controller"
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
int screenWidth = 800;
int screenHeight = 450;

Texture2D texPs3Pad;
Texture2D texXboxPad;

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
    InitWindow(screenWidth, screenHeight, "raylib [core] example - gamepad input");
#endif

    texPs3Pad = LoadTexture("resources/ps3.png");
    texXboxPad = LoadTexture("resources/xbox.png");
    
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
    UnloadTexture(texPs3Pad);
    UnloadTexture(texXboxPad);
    
    CloseWindow();        // Close window and OpenGL context
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
    // ...
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);
        
        if (IsGamepadAvailable(GAMEPAD_PLAYER1))
        {
            DrawText(FormatText("GP1: %s", GetGamepadName(GAMEPAD_PLAYER1)), 10, 10, 10, BLACK);

            if (IsGamepadName(GAMEPAD_PLAYER1, XBOX360_NAME_ID))
            {
                DrawTexture(texXboxPad, 0, 0, DARKGRAY);
                
                // Draw buttons: xbox home
                if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_XBOX_BUTTON_HOME)) DrawCircle(394, 89, 19, RED);

                // Draw buttons: basic
                if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_XBOX_BUTTON_START)) DrawCircle(436, 150, 9, RED);
                if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_XBOX_BUTTON_SELECT)) DrawCircle(352, 150, 9, RED);
                if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_XBOX_BUTTON_X)) DrawCircle(501, 151, 15, BLUE);
                if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_XBOX_BUTTON_A)) DrawCircle(536, 187, 15, LIME);
                if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_XBOX_BUTTON_B)) DrawCircle(572, 151, 15, MAROON);
                if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_XBOX_BUTTON_Y)) DrawCircle(536, 115, 15, GOLD);
                
                // Draw buttons: d-pad
                DrawRectangle(317, 202, 19, 71, BLACK);
                DrawRectangle(293, 228, 69, 19, BLACK);
                if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_XBOX_BUTTON_UP)) DrawRectangle(317, 202, 19, 26, RED);
                if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_XBOX_BUTTON_DOWN)) DrawRectangle(317, 202 + 45, 19, 26, RED);
                if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_XBOX_BUTTON_LEFT)) DrawRectangle(292, 228, 25, 19, RED);
                if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_XBOX_BUTTON_RIGHT)) DrawRectangle(292 + 44, 228, 26, 19, RED);
                
                // Draw buttons: left-right back
                if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_XBOX_BUTTON_LB)) DrawCircle(259, 61, 20, RED);
                if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_XBOX_BUTTON_RB)) DrawCircle(536, 61, 20, RED);

                // Draw axis: left joystick
                DrawCircle(259, 152, 39, BLACK);
                DrawCircle(259, 152, 34, LIGHTGRAY);
                DrawCircle(259 + (GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_XBOX_AXIS_LEFT_X)*20), 
                           152 - (GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_XBOX_AXIS_LEFT_Y)*20), 25, BLACK);
                
                // Draw axis: right joystick
                DrawCircle(461, 237, 38, BLACK);
                DrawCircle(461, 237, 33, LIGHTGRAY);
                DrawCircle(461 + (GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_XBOX_AXIS_RIGHT_X)*20), 
                           237 - (GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_XBOX_AXIS_RIGHT_Y)*20), 25, BLACK);

                // Draw axis: left-right triggers
                DrawRectangle(170, 30, 15, 70, GRAY);
                DrawRectangle(604, 30, 15, 70, GRAY);              
                DrawRectangle(170, 30, 15, (((1.0f + GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_XBOX_AXIS_LT))/2.0f)*70), RED);
                DrawRectangle(604, 30, 15, (((1.0f + GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_XBOX_AXIS_RT))/2.0f)*70), RED);
                
                //DrawText(FormatText("Xbox axis LT: %02.02f", GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_XBOX_AXIS_LT)), 10, 40, 10, BLACK);
                //DrawText(FormatText("Xbox axis RT: %02.02f", GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_XBOX_AXIS_RT)), 10, 60, 10, BLACK);
            }
            else if (IsGamepadName(GAMEPAD_PLAYER1, PS3_NAME_ID))
            {
                DrawTexture(texPs3Pad, 0, 0, DARKGRAY);

                // Draw buttons: ps
                if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_PS3_BUTTON_PS)) DrawCircle(396, 222, 13, RED);
                
                // Draw buttons: basic
                if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_PS3_BUTTON_SELECT)) DrawRectangle(328, 170, 32, 13, RED);
                if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_PS3_BUTTON_START)) DrawTriangle((Vector2){ 436, 168 }, (Vector2){ 436, 185 }, (Vector2){ 464, 177 }, RED);
                if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_PS3_BUTTON_TRIANGLE)) DrawCircle(557, 144, 13, LIME);
                if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_PS3_BUTTON_CIRCLE)) DrawCircle(586, 173, 13, RED);
                if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_PS3_BUTTON_CROSS)) DrawCircle(557, 203, 13, VIOLET);
                if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_PS3_BUTTON_SQUARE)) DrawCircle(527, 173, 13, PINK);

                // Draw buttons: d-pad
                DrawRectangle(225, 132, 24, 84, BLACK);
                DrawRectangle(195, 161, 84, 25, BLACK);
                if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_PS3_BUTTON_UP)) DrawRectangle(225, 132, 24, 29, RED);
                if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_PS3_BUTTON_DOWN)) DrawRectangle(225, 132 + 54, 24, 30, RED);
                if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_PS3_BUTTON_LEFT)) DrawRectangle(195, 161, 30, 25, RED);
                if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_PS3_BUTTON_RIGHT)) DrawRectangle(195 + 54, 161, 30, 25, RED);
                
                // Draw buttons: left-right back buttons
                if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_PS3_BUTTON_L1)) DrawCircle(239, 82, 20, RED);
                if (IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_PS3_BUTTON_R1)) DrawCircle(557, 82, 20, RED);

                // Draw axis: left joystick
                DrawCircle(319, 255, 35, BLACK);
                DrawCircle(319, 255, 31, LIGHTGRAY);
                DrawCircle(319 + (GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_PS3_AXIS_LEFT_X)*20), 
                           255 + (GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_PS3_AXIS_LEFT_Y)*20), 25, BLACK);
                
                // Draw axis: right joystick
                DrawCircle(475, 255, 35, BLACK);
                DrawCircle(475, 255, 31, LIGHTGRAY);
                DrawCircle(475 + (GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_PS3_AXIS_RIGHT_X)*20), 
                           255 + (GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_PS3_AXIS_RIGHT_Y)*20), 25, BLACK);

                // Draw axis: left-right triggers
                DrawRectangle(169, 48, 15, 70, GRAY);
                DrawRectangle(611, 48, 15, 70, GRAY);              
                DrawRectangle(169, 48, 15, (((1.0f - GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_PS3_AXIS_L2))/2.0f)*70), RED);
                DrawRectangle(611, 48, 15, (((1.0f - GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_PS3_AXIS_R2))/2.0f)*70), RED);
            }
            else
            {
                DrawText("- GENERIC GAMEPAD -", 280, 180, 20, GRAY);
                
                // TODO: Draw generic gamepad
            }
            
            DrawText(FormatText("DETECTED AXIS [%i]:", GetGamepadAxisCount(GAMEPAD_PLAYER1)), 10, 50, 10, MAROON); 
            
            for (int i = 0; i < GetGamepadAxisCount(GAMEPAD_PLAYER1); i++)
            {
                DrawText(FormatText("AXIS %i: %.02f", i, GetGamepadAxisMovement(GAMEPAD_PLAYER1, i)), 20, 70 + 20*i, 10, DARKGRAY);
            }
            
            if (GetGamepadButtonPressed() != -1) DrawText(FormatText("DETECTED BUTTON: %i", GetGamepadButtonPressed()), 10, 430, 10, RED);
            else DrawText("DETECTED BUTTON: NONE", 10, 430, 10, GRAY);
        }
        else
        {
            DrawText("GP1: NOT DETECTED", 10, 10, 10, GRAY);
            
            DrawTexture(texXboxPad, 0, 0, LIGHTGRAY);
        }

    EndDrawing();
    //----------------------------------------------------------------------------------
}