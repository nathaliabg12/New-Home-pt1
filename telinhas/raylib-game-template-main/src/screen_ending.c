/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Ending Screen Functions Definitions (Init, Update, Draw, Unload)
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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "string.h"

typedef struct jogador
{
    char nome[10];
    int pontuacao;
    float tempo;
} jogador;

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

//----------------------------------------------------------------------------------
// Ending Screen Functions Definition
//----------------------------------------------------------------------------------

// Ending Screen Initialization logic
Texture2D back_rank;
Image resback_rank;
void InitEndingScreen(void)
{
    // TODO: Initialize ENDING screen variables here!
    framesCounter = 0;
    finishScreen = 0;
    
    resback_rank = LoadImage("resources/ranking.png");
    ImageResize(&resback_rank, GetScreenWidth(), GetScreenHeight());
    back_rank = LoadTextureFromImage(resback_rank);
}

// Ending Screen Update logic
void UpdateEndingScreen(void)
{
    // TODO: Update ENDING screen variables here!

    // Press enter or tap to return to TITLE screen
    if (IsKeyPressed(KEY_ENTER))
    {
        finishScreen = 1;
        PlaySound(fxCoin);
    }
}

// Ending Screen Draw logic
void DrawEndingScreen(void)
{
    //Abertura de arquivo
    DrawTexture(back_rank, 0, 0, WHITE);
    
    FILE *g;
    g = fopen("dados_usuarios.bin", "rb");
    jogador ranking; 
    //jogador imprimir[10];
    //int cont_jog=0;
    int pos_tela=0;


    //Leitura do arquivo
    while(fread(&ranking, sizeof(jogador), 1, g)>0){

       //Imprimindo os nomes pontuações e tempos na tela um abaixo do outro
       DrawText(TextFormat("Nome: %s    Pontuação: %d     Tempo: %.0f\n", ranking.nome, ranking.pontuacao, ranking.tempo), 130, 220+pos_tela, 20, WHITE);
        pos_tela+=20;

        
    }
    fclose(g);
    
}

// Ending Screen Unload logic
void UnloadEndingScreen(void)
{
    // TODO: Unload ENDING screen variables here!
}

// Ending Screen should finish?
int FinishEndingScreen(void)
{
    return finishScreen;
}
