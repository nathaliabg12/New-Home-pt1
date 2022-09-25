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
// Creditos Screen Functions Definition
//----------------------------------------------------------------------------------

// Creditos Screen Initialization logic
Texture2D back_credito;
Image resback_credito;
void InitCreditosScreen(void)
{
    // TODO: Initialize Creditos screen variables here!
    framesCounter = 0;
    finishScreen = 0;
    resback_credito = LoadImage("resources/fundo.png");
    ImageResize(&resback_credito, GetScreenWidth(), GetScreenHeight());
    back_credito = LoadTextureFromImage(resback_credito);
}

// Creditos Screen Update logic
void UpdateCreditosScreen(void)
{
    // TODO: Update Creditos screen variables here!

    // Press enter or tap to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        finishScreen = 1;
        PlaySound(fxCoin);
    }
}

// Creditos Screen Draw logic
void DrawCreditosScreen(void)
{
    // TODO: Draw Resultado screen here!
   DrawTexture(back_credito, 0, 0, WHITE);
   // DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), PURPLE);
    DrawTextEx(font, "CREDITOS", (Vector2){ 20, 10 }, font.baseSize*3, 4, WHITE);
   // DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);
     
}

// Creditos Screen Unload logic
void UnloadCreditosScreen(void)
{
    // TODO: Unload Resultado screen variables here!
}

// Creditos Screen should finish?
int FinishCreditosScreen(void)
{
    return finishScreen;
}
