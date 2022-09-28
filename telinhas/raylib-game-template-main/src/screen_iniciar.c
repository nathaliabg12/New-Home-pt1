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

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

//Não permite eu declarar a função aqui novamente diz que ela já está declarada, por isso eu tentei só deixar ela definida na screens.h, mas aí da outro problema e fala que eu tenho que incluir a biblioteca stdio em todos os arquivos

// FILE* fopen_e_teste(char* caminho, char* modo)
// {
//     FILE* f;
//     f = fopen(caminho, modo);
//     if(f == NULL)
//     {
//         perror("Erro ao encontrar ou ler arquivo.\n");
//         exit(1);
//     }
//     return f;
// }

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization logic
Texture2D back_tela4;
Image resback_tela4;
void InitIniciarScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 0;
    resback_tela4 = LoadImage("resources/tela4.png");
    ImageResize(&resback_tela4, GetScreenWidth(), GetScreenHeight());
    back_tela4 = LoadTextureFromImage(resback_tela4);
}

// Gameplay Screen Update logic
void UpdateIniciarScreen(void)
{
    // TODO: Update GAMEPLAY screen variables here!

    // Press enter or tap to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        finishScreen = 1;
        PlaySound(fxCoin);
    }
}

// Gameplay Screen Draw logic
void DrawIniciarScreen(void)
{
    FILE* ap;
    ap = fopen_e_teste("atual_usuario", "r");
    char n[10];
    // TODO: Draw GAMEPLAY screen here!
   //DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), PURPLE);
    //DrawTextEx(font, "GAMEPLAY SCREEN", (Vector2){ 20, 10 }, font.baseSize*3, 4, MAROON);
    //DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);
    DrawTexture(back_tela4, 0, 0, WHITE);

    fscanf(ap, "%s", n);
    DrawText(n, 275, 155, 30, WHITE);
}

// Gameplay Screen Unload logic
void UnloadIniciarScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
}

// Gameplay Screen should finish?
int FinishIniciarScreen(void)
{
    return finishScreen;
}
