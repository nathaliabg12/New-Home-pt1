/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Title Screen Functions Definitions (Init, Update, Draw, Unload)
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
// Titulo Screen Functions Definition
//----------------------------------------------------------------------------------

// Titulo Screen Initialization logic
Texture2D back_tela1;
Image resback_tela1;
void InitTituloScreen(void)
{
    // TODO: Initialize Titulo screen variables here!
    framesCounter = 0;
    finishScreen = 0;
    resback_tela1 = LoadImage("resources/tela1.png");
    ImageResize(&resback_tela1, GetScreenWidth(), GetScreenHeight());
    back_tela1 = LoadTextureFromImage(resback_tela1);
}

// Titulo Screen Update logic
void UpdateTituloScreen(void)
{
    // TODO: Update Titulo screen variables here!

    // Press enter or tap to change to narracao1 screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        //finishScreen = 1;   // OPTIONS
        finishScreen = 2;   // GAMEPLAY
        PlaySound(fxCoin);
    }
}

// Titulo Screen Draw logic
void DrawTituloScreen(void)
{
    // TODO: Draw Titulo screen here!
    //DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), GREEN);
    //DrawTextEx(font, "TITLE SCREEN", (Vector2){ 20, 10 }, font.baseSize*3, 4, DARKGREEN);
    //DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);
    DrawTexture(back_tela1, 0, 0, WHITE);
}

// Titulo Screen Unload logic
void UnloadTituloScreen(void)
{
    // TODO: Unload Titulo screen variables here!
}

// Titulo Screen should finish?
int FinishTituloScreen(void)
{
    return finishScreen;
}
