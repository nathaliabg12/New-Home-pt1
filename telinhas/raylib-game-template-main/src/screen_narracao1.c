/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

//----------------------------------------------------------------------------------
// Narracao1 Screen Functions Definition
//----------------------------------------------------------------------------------

// Narracao1 Screen Initialization logic
Texture2D back_tela2;
Image resback_tela2;
void InitNarracao1Screen(void)
{
    // TODO: Initialize Narracao1 screen variables here!
    framesCounter = 0;
    finishScreen = 0;
    resback_tela2 = LoadImage("resources/tela2.png");
    ImageResize(&resback_tela2, GetScreenWidth(), GetScreenHeight());
    back_tela2 = LoadTextureFromImage(resback_tela2);
}

// Narracao1 Screen Update logic
void UpdateNarracao1Screen(void)
{
    // TODO: Update Narracao1 screen variables here!

    // Press enter or tap to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        finishScreen = 1;
        PlaySound(fxCoin);
    }
}

// Narracao1 Screen Draw logic
void DrawNarracao1Screen(void)
{
    // TODO: Draw Narracao1 screen here!
   // DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), PURPLE);
    //DrawTextEx(font, "GAMEPLAY SCREEN", (Vector2){ 20, 10 }, font.baseSize*3, 4, MAROON);
    //DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);
     DrawTexture(back_tela2, 0, 0, WHITE);
}

// Gameplay Screen Unload logic
void UnloadNarracao1Screen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
}

// Gameplay Screen should finish?
int FinishNarracao1Screen(void)
{
    return finishScreen;
}
