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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "string.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

#define PLAYER_MAX_LIFE 5
#define LINES_OF_BRICKS 5
#define BRICKS_PER_LINE 20

//----------------------------------------------------------------------------------
// Funcao compara para o qsort
//----------------------------------------------------------------------------------
typedef struct jogador
{
    char nome[10];
    int pontuacao;
    float tempo;
} jogador;

//----------------------------------------------------------------------------------
// Funcao compara para o qsort
//----------------------------------------------------------------------------------
int compara(const void *a, const void *b)
{
    jogador *n1 = (jogador *)a;
    jogador *n2 = (jogador *)b;

    if (n1->pontuacao == n2->pontuacao)
    {
        return n1->tempo - n2->tempo;
    }
    else
    {
        return -(n1->pontuacao - n2->pontuacao);
    }
}

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef struct Player
{
    Vector2 position;
    Vector2 size;
    int life;
} Player;

typedef struct Ball
{
    Vector2 position;
    Vector2 speed;
    int radius;
    bool active;
} Ball;

typedef struct Brick
{
    Vector2 position;
    bool active;
} Brick;

//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------
static const int screenWidth = 800;
static const int screenHeight = 450;

static bool gameOver = false;
static bool pause = false;

static Player player = {0};
static Ball ball = {0};
static Brick brick[LINES_OF_BRICKS][BRICKS_PER_LINE] = {0};
static Vector2 brickSize = {0};

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization logic
Texture2D back_jogo;
Image resback_jogo;

// Texture2D alien;
Image alien;
Texture2D alien_alien;
float inittime = 0;
int cont = 0;
void InitJogoScreen(void)
{
    cont = 0;
    inittime = GetTime();
    // TODO: Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 0;
    resback_jogo = LoadImage("resources/fundo.png");
    ImageResize(&resback_jogo, GetScreenWidth(), GetScreenHeight());
    back_jogo = LoadTextureFromImage(resback_jogo);

    brickSize = (Vector2){GetScreenWidth() / BRICKS_PER_LINE, 40};
    alien = LoadImage("resources/alien.png");
    ImageResize(&alien, brickSize.x, brickSize.y);
    alien_alien = LoadTextureFromImage(alien);

    // Initialize player
    player.position = (Vector2){screenWidth / 2, screenHeight * 7 / 8};
    player.size = (Vector2){screenWidth / 10, 20};
    player.life = PLAYER_MAX_LIFE;

    // Initialize ball
    ball.position = (Vector2){screenWidth / 2, screenHeight * 7 / 8 - 30};
    ball.speed = (Vector2){0, 0};
    ball.radius = 7;
    ball.active = false;

    // Initialize bricks
    int initialDownPosition = 50;

    for (int i = 0; i < LINES_OF_BRICKS; i++)
    {
        for (int j = 0; j < BRICKS_PER_LINE; j++)
        {
            brick[i][j].position = (Vector2){j * brickSize.x + brickSize.x / 2, i * brickSize.y + initialDownPosition};
            brick[i][j].active = true;
        }
    }
}

float timing = 0;
// Gameplay Screen Update logic
void UpdateJogoScreen(void)
{
    // TODO: Update GAMEPLAY screen variables here!
    // int cont=0;
    // Press enter or tap to change to ENDING screen
    /*if (IsKeyPressed(KEY_ENTER))
    {
        finishScreen = 1;
        PlaySound(fxCoin);
    }
   */

    if (!gameOver)
    {
        if (IsKeyPressed('P'))
            pause = !pause;
        if (!pause)
        {
            // Player movement logic
            if (IsKeyDown(KEY_LEFT))
                player.position.x -= 5;
            if ((player.position.x - player.size.x / 2) <= 0)
                player.position.x = player.size.x / 2;
            if (IsKeyDown(KEY_RIGHT))
                player.position.x += 5;
            if ((player.position.x + player.size.x / 2) >= screenWidth)
                player.position.x = screenWidth - player.size.x / 2;

            // Ball launching logic
            if (!ball.active)
            {
                if (IsKeyPressed(KEY_SPACE))
                {
                    ball.active = true;
                    ball.speed = (Vector2){0, -5};
                }
            }

            // Ball movement logic
            if (ball.active)
            {
                ball.position.x += ball.speed.x;
                ball.position.y += ball.speed.y;
            }
            else
            {
                ball.position = (Vector2){player.position.x, screenHeight * 7 / 8 - 30};
            }

            // Collision logic: ball vs walls
            if (((ball.position.x + ball.radius) >= screenWidth) || ((ball.position.x - ball.radius) <= 0))
                ball.speed.x *= -1;
            if ((ball.position.y - ball.radius) <= 0)
                ball.speed.y *= -1;
            if ((ball.position.y + ball.radius) >= screenHeight)
            {
                ball.speed = (Vector2){0, 0};
                ball.active = false;

                player.life--;
            }

            // Collision logic: ball vs player
            if (CheckCollisionCircleRec(ball.position, ball.radius,
                                        (Rectangle){player.position.x - player.size.x / 2, player.position.y - player.size.y / 2, player.size.x, player.size.y}))
            {
                if (ball.speed.y > 0)
                {
                    ball.speed.y *= -1;
                    ball.speed.x = (ball.position.x - player.position.x) / (player.size.x / 2) * 5;
                }
            }

            // Collision logic: ball vs bricks
            for (int i = 0; i < LINES_OF_BRICKS; i++)
            {
                for (int j = 0; j < BRICKS_PER_LINE; j++)
                {
                    if (brick[i][j].active)
                    {
                        // Hit below
                        if (((ball.position.y - ball.radius) <= (brick[i][j].position.y + brickSize.y / 2)) &&
                            ((ball.position.y - ball.radius) > (brick[i][j].position.y + brickSize.y / 2 + ball.speed.y)) &&
                            ((fabs(ball.position.x - brick[i][j].position.x)) < (brickSize.x / 2 + ball.radius * 2 / 3)) && (ball.speed.y < 0))
                        {
                            brick[i][j].active = false;
                            ball.speed.y *= -1;
                            cont++;
                        }
                        // Hit above
                        else if (((ball.position.y + ball.radius) >= (brick[i][j].position.y - brickSize.y / 2)) &&
                                 ((ball.position.y + ball.radius) < (brick[i][j].position.y - brickSize.y / 2 + ball.speed.y)) &&
                                 ((fabs(ball.position.x - brick[i][j].position.x)) < (brickSize.x / 2 + ball.radius * 2 / 3)) && (ball.speed.y > 0))
                        {
                            brick[i][j].active = false;
                            ball.speed.y *= -1;
                            cont++;
                        }
                        // Hit left
                        else if (((ball.position.x + ball.radius) >= (brick[i][j].position.x - brickSize.x / 2)) &&
                                 ((ball.position.x + ball.radius) < (brick[i][j].position.x - brickSize.x / 2 + ball.speed.x)) &&
                                 ((fabs(ball.position.y - brick[i][j].position.y)) < (brickSize.y / 2 + ball.radius * 2 / 3)) && (ball.speed.x > 0))
                        {
                            brick[i][j].active = false;
                            ball.speed.x *= -1;
                            cont++;
                        }
                        // Hit right
                        else if (((ball.position.x - ball.radius) <= (brick[i][j].position.x + brickSize.x / 2)) &&
                                 ((ball.position.x - ball.radius) > (brick[i][j].position.x + brickSize.x / 2 + ball.speed.x)) &&
                                 ((fabs(ball.position.y - brick[i][j].position.y)) < (brickSize.y / 2 + ball.radius * 2 / 3)) && (ball.speed.x < 0))
                        {
                            brick[i][j].active = false;
                            ball.speed.x *= -1;
                            cont++;
                        }
                    }
                }
            }

            // Game over logic

            if (player.life <= 0)
                gameOver = true, timing = GetTime() - inittime;
            else
            {
                gameOver = true;

                for (int i = 0; i < LINES_OF_BRICKS; i++)
                {
                    for (int j = 0; j < BRICKS_PER_LINE; j++)
                    {
                        if (brick[i][j].active)
                            gameOver = false;
                    }
                }
            }
        }
    }
    // else
    //{
    //   if (IsKeyPressed(KEY_ENTER))
    //{
    //   InitJogoScreen();
    //  gameOver = false;
    //}
    //}
}

#define MAX_INPUT_CHARS 9
char name[MAX_INPUT_CHARS + 1] = "\0"; // NOTE: One extra space required for null terminator char '\0'
int letterCount = 0;
bool mouseOnText = false;
int cont_jogos = 0;

// caixa de texto
Rectangle textBox = {320, 300, 140, 35};

// Gameplay Screen Draw logic
void DrawJogoScreen(void)
{
    // TODO: Draw GAMEPLAY screen here!
    // DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), PURPLE);
    // DrawTextEx(font, "JOGO", (Vector2){ 20, 10 }, font.baseSize*3, 4, MAROON);
    // DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);
    DrawTexture(back_jogo, 0, 0, WHITE);
    // ImageDrawRectangle(&alien, 20, 20, 30, 30, WHITE);

    ClearBackground(RAYWHITE);

    if (!gameOver)
    {
        // Draw player bar
        DrawRectangle(player.position.x - player.size.x / 2, player.position.y - player.size.y / 2, player.size.x, player.size.y, WHITE);

        // Draw player lives
        for (int i = 0; i < player.life; i++)
            DrawRectangle(20 + 40 * i, screenHeight - 30, 35, 10, LIGHTGRAY);

        // Draw ball
        DrawCircleV(ball.position, ball.radius, PINK);

        // Draw bricks
        for (int i = 0; i < LINES_OF_BRICKS; i++)
        {
            for (int j = 0; j < BRICKS_PER_LINE; j++)
            {
                if (brick[i][j].active)
                {
                    // DrawTexture(alien_alien,brickSize.x, brickSize.y,WHITE);
                    if ((i + j) % 2 == 0)
                        DrawTexture(alien_alien, brick[i][j].position.x - brickSize.x / 2, brick[i][j].position.y - brickSize.y / 2, WHITE);
                    else
                        DrawTexture(alien_alien, brick[i][j].position.x - brickSize.x / 2, brick[i][j].position.y - brickSize.y / 2, WHITE);
                }
            }
        }

        if (pause)
            DrawText("GAME PAUSED", screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2, screenHeight / 2 - 40, 40, WHITE);
    }
    else
    {
        DrawText(TextFormat("SUA PONTUAÇÃO FOI: %d", cont), 130, 220, 30, WHITE);
        DrawText(TextFormat("Seu tempo foi: %.0f s", timing), 130, 260, 30, WHITE);
        DrawText(TextFormat("Digite seu nickname: "), 130, 300, 30, WHITE);

        // Caixa de texto inteiro
        // DrawRectangleRec(textBox, WHITE);

        DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 45, WHITE);

        // DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 290, 320, 15, WHITE);

        //
        if (CheckCollisionPointRec(GetMousePosition(), textBox))
            mouseOnText = true;
        else
            mouseOnText = false;

        if (mouseOnText)
        {
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
                {
                    name[letterCount] = (char)key;
                    name[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
                    letterCount++;
                }

                key = GetCharPressed(); // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0)
                    letterCount = 0;
                name[letterCount] = '\0';
            }
        }
        else
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (mouseOnText)
            framesCounter++;
        else
            framesCounter = 0;

        if (mouseOnText)
        {
            // Aparece o underline de indicação para escrever o nome
            DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, BLACK);
            if (letterCount < MAX_INPUT_CHARS)
            {
                // Draw blinking underscore char
                if (((framesCounter / 20) % 2) == 0)
                    DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, BLACK);
            }
            else
                DrawText("Press BACKSPACE to delete chars...", 400, 360, 10, BLUE);
        }
        else
        {
            //"Deixa apagado"
            DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, WHITE);
        }

        // Só sai do jogo se apertar enter dps do game over e se a variável name não for null
        if (IsKeyPressed(KEY_ENTER) && name)
        {
            FILE *f;
            f = fopen("dados_usuarios.bin", "r+b");
            if (f == NULL)
            {
                jogador nulo ={"aaaaaaaaaa", 0, 0};
                f = fopen("dados_usuarios.bin", "w+b");
                for(int i = 0; i < 10; i++)
                    fwrite(&nulo, sizeof(jogador), 1, f);
                fclose(f);

                f = fopen("dados_usuarios.bin", "r+b");
            }
            jogador dados, ultimo;

            int acheiPosicao = 0, idx = -1, idxI = 0;
            while (fread(&dados, sizeof(jogador), 1, f) > 0)
            {
                if(acheiPosicao == 0 && dados.pontuacao == cont && dados.tempo < timing){
                    ultimo = dados;
                    printf("\n\nSai: %s %f %d\n\nEntra: %s %f %d\n\n", dados.nome, dados.tempo, dados.pontuacao, name, timing, cont);
                    strcpy(dados.nome,name);
                    dados.tempo = timing;
                    dados.pontuacao = cont;
                    idx = idxI;
                    fseek(f, -1 * sizeof(jogador), SEEK_CUR);
                    fwrite(&dados, sizeof(jogador), 1, f);
                    acheiPosicao = 1;
                }
                else if (acheiPosicao == 0 && dados.pontuacao < cont)
                {
                    ultimo = dados;
                    printf("\n\nSai: %s %f %d\n\nEntra: %s %f %d\n\n", dados.nome, dados.tempo, dados.pontuacao, name, timing, cont);
                    idx = idxI;
                    strcpy(dados.nome,name);
                    dados.tempo = timing;
                    dados.pontuacao = cont;
                    fseek(f, -1 * sizeof(jogador), SEEK_CUR);
                    fwrite(&dados, sizeof(jogador), 1, f);
                    acheiPosicao = 1;

                }
                else if(acheiPosicao){
                    fseek(f, -1 * sizeof(jogador), SEEK_CUR);
                    fwrite(&ultimo, sizeof(jogador), 1, f);
                    ultimo = dados;
                    
                }
                idxI++;
            }
            printf("\n\n\n\n%d\n\n\n\n", idx);
            // cont_jogos++;

            // qsort(dados, 10, sizeof(jogador), compara);
            fclose(f);

            finishScreen = 1;
            PlaySound(fxCoin);
        }
    }
}

// Texture2D texture = LoadTextureFromImage(alien);
//  DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 290, 300, 15, WHITE);
// DrawText(TextFormat("SUA PONTUAÇÃO FOI: %d", cont), GetScreenWidth()/2 - MeasureText("SUA PONTUAÇÃO FOI %d", cont, 50)/2, GetScreenHeight()/2 - 50, 50, WHITE);

bool IsAnyKeyPressed()
{
    bool keyPressed = false;
    int key = GetKeyPressed();

    if ((key >= 32) && (key <= 126))
        keyPressed = true;

    return keyPressed;
}

// Gameplay Screen Unload logic
void UnloadJogoScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
}

// Gameplay Screen should finish?
int FinishJogoScreen(void)
{
    return finishScreen;
}
