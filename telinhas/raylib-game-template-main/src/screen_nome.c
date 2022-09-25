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
#define MAX_INPUT_CHARS     9

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

const int screenWidth = 800;
const int screenHeight = 450;

//----------------------------------------------------------------------------------
// Nome Screen Functions Definition

char name[MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
    int letterCount = 0;

    Rectangle textBox = { screenWidth/2.0f - 120, 200, 280, 70 };
    bool mouseOnText = false;

    //int framesCounter = 0;

    //SetTargetFPS(10);               // Set 
//----------------------------------------------------------------------------------

// Nome Screen Initialization logic
Texture2D back_nome;
Image resback_nome;
void InitNomeScreen(void)
{
    // TODO: Initialize Nome screen variables here!
    framesCounter = 0;
    finishScreen = 0;
    resback_nome = LoadImage("resources/fundo.png");
    ImageResize(&resback_nome, GetScreenWidth(), GetScreenHeight());
    back_nome = LoadTextureFromImage(resback_nome);
}

// Nome Screen Update logic
void UpdateNomeScreen(void)
{
    // TODO: Update Nome screen variables here!
    
     if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
        else mouseOnText = false;

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
                    name[letterCount+1] = '\0'; // Add null terminator at the end of the string.
                    letterCount++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                name[letterCount] = '\0';
            }
        }
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (mouseOnText) framesCounter++;
        else framesCounter = 0;

    // Press enter or tap to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER))
    {
        finishScreen = 1;
        PlaySound(fxCoin);
    }
}

// Gameplay Screen Draw logic
void DrawNomeScreen(void)
{
   
   ClearBackground(RAYWHITE);
   DrawTexture(back_nome, 0, 0, WHITE);
   //ImageClearBackground(back_nome, WHITE);

            DrawText("INSIRA SEU NOME", 270, 140, 30, WHITE);

            DrawRectangleRec(textBox, WHITE);
            if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, BLACK);
            else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, WHITE);

            DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 45, BLACK);

            DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 290, 300, 15, WHITE);

            if (mouseOnText)
            {
                if (letterCount < MAX_INPUT_CHARS)
                {
                    // Draw blinking underscore char
                    if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, BLACK);
                }
                else DrawText("Press BACKSPACE to delete chars...", 230, 350, 20, WHITE);
            }
    // TODO: Draw GAMEPLAY screen here!
    //DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), PURPLE);
    //DrawTextEx(font, "NOME", (Vector2){ 20, 10 }, font.baseSize*3, 4, MAROON);
    //DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);
    // DrawTexture(back_nome, 0, 0, WHITE);
     
     
}

bool IsAnyKeyPressed()
{
    bool keyPressed = false;
    int key = GetKeyPressed();

    if ((key >= 32) && (key <= 126)) keyPressed = true;

    return keyPressed;
}

// Nome Screen Unload logic
void UnloadNomeScreen(void)
{
    // TODO: Unload Nome screen variables here!
}


// Nome Screen should finish?
int FinishNomeScreen(void)
{
    return finishScreen;
}
