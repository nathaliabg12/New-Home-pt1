// /**********************************************************************************************
// *
// *   raylib - Advance Game template
// *
// *   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
// *
// *   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
// *
// *   This software is provided "as-is", without any express or implied warranty. In no event
// *   will the authors be held liable for any damages arising from the use of this software.
// *
// *   Permission is granted to anyone to use this software for any purpose, including commercial
// *   applications, and to alter it and redistribute it freely, subject to the following restrictions:
// *
// *     1. The origin of this software must not be misrepresented; you must not claim that you
// *     wrote the original software. If you use this software in a product, an acknowledgment
// *     in the product documentation would be appreciated but is not required.
// *
// *     2. Altered source versions must be plainly marked as such, and must not be misrepresented
// *     as being the original software.
// *
// *     3. This notice may not be removed or altered from any source distribution.
// *
// **********************************************************************************************/
// #include "stdio.h"
// #include "stdlib.h"
// #include "string.h"
// #include "raylib.h"
// #include "screens.h"
// // #define MAX_INPUT_CHARS     9

// //----------------------------------------------------------------------------------
// // Module Variables Definition (local)
// //----------------------------------------------------------------------------------
// static int framesCounter = 0;
// static int finishScreen = 0;

// const int screenWidth = 800;
// const int screenHeight = 450;

// //----------------------------------------------------------------------------------
// //Criação da struct para o usuário
// typedef struct 
// {
//     char nome[10];
//     int pontuacao;
//     float tempo;    
// } jogador;

// jogador atual_player;

// //Função para abertura e leitura do arquivo
// // FILE* fopen_e_teste(char* caminho, char* modo)
// // {
// //     FILE* f;
// //     f = fopen(caminho, modo);
// //     if(f == NULL)
// //     {
// //         perror("Erro ao encontrar ou ler arquivo.\n");
// //         exit(1);
// //     }
// //     return f;
// // }



// // Nome Screen Functions Definition

//     // char name[MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
//     // int letterCount = 0;

//     // Rectangle textBox = { screenWidth/2.0f - 120, 200, 280, 70 };
//     // bool mouseOnText = false;

//     //int framesCounter = 0;

//     //SetTargetFPS(10);               // Set 
// //----------------------------------------------------------------------------------

// // Nome Screen Initialization logic
// Texture2D back_nome;
// Image resback_nome;
// void InitNomeScreen(void)
// {
//     // TODO: Initialize Nome screen variables here!
//     framesCounter = 0;
//     finishScreen = 0;
//     resback_nome = LoadImage("resources/fundo.png");
//     ImageResize(&resback_nome, GetScreenWidth(), GetScreenHeight());
//     back_nome = LoadTextureFromImage(resback_nome);
// }

// // Nome Screen Update logic
// void UpdateNomeScreen(void)
// {
//     // TODO: Update Nome screen variables here!
    
//      if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
//         else mouseOnText = false;

//         if (mouseOnText)
//         {
//             // Set the window's cursor to the I-Beam
//             SetMouseCursor(MOUSE_CURSOR_IBEAM);

//             // Get char pressed (unicode character) on the queue
//             int key = GetCharPressed();

//             // Check if more characters have been pressed on the same frame
//             while (key > 0)
//             {
//                 // NOTE: Only allow keys in range [32..125]
//                 if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
//                 {
//                     name[letterCount] = (char)key;
//                     name[letterCount+1] = '\0'; // Add null terminator at the end of the string.
//                     letterCount++;
//                 }

//                 key = GetCharPressed();  // Check next character in the queue
//             }

//             if (IsKeyPressed(KEY_BACKSPACE))
//             {
//                 letterCount--;
//                 if (letterCount < 0) letterCount = 0;
//                 name[letterCount] = '\0';
//             }
//         }
//         else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

//         if (mouseOnText) framesCounter++;
//         else framesCounter = 0;

//         if(IsKeyPressed(KEY_ENTER))
//         {
//             finishScreen = 1;
//             PlaySound(fxCoin);
//         }
// }

// // Gameplay Screen Draw logic
// void DrawNomeScreen(void)
// {
//     FILE* p;
//     FILE* at;
//     p = fopen("dadosusuarios.bin", "ab+");
//     if(p == NULL)
//     {
//         perror("Erro ao encontrar ou ler arquivo.\n");
//         exit(1);
//     }

//     //Tentei com a função do raylib e não deu certo
//     // char* nome_arquivo = "atual_usuario.txt";
//     // LoadFileText(nome_arquivo);

//     at = fopen("atual_usuario.txt", "w");
//     if(at == NULL)
//     {
//         perror("Erro ao encontrar ou ler arquivo.\n");
//         exit(1);
//     }

//     jogador player;

//     //variável para incrementar caso algum nome seja igual ao nome do usuário
//     int contnames = 0;

//     ClearBackground(RAYWHITE);
//     DrawTexture(back_nome, 0, 0, WHITE);
    
//     DrawText("INSIRA SEU NOME", 270, 140, 30, WHITE);

//     //Caixa de texto inteiro
//     DrawRectangleRec(textBox, WHITE);

//     DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 45, BLACK);

//     DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 290, 300, 15, WHITE);


//     //
//     if (mouseOnText)
//     {
//         //Aparece o underline de indicação para escrever o nome
//         DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, BLACK);
//         if (letterCount < MAX_INPUT_CHARS)
//         {
//             // Draw blinking underscore char
//             if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, BLACK);
//         }
//         else DrawText("Press BACKSPACE to delete chars...", 230, 350, 20, WHITE);
//     }
//     else 
//     {
//         //"Deixa apagado"
//         DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, WHITE); 
//     }


//     // Press enter or tap to change to ENDING screen
//     // if (IsKeyPressed(KEY_ENTER))
//     // {


//         // while(fread(&player, sizeof(jogador), 1, p) > 0 && !contnames)
//         // {
//         //     //Se o nome for encontrado alguma vez não precisa mais fazer a leitura do resto do arquivo
//         //     if(player.nome == name)
//         //         contnames++;
//         // }

//         // //Caso não exista realmente nenhum nome como aquele registrado ele será escrito agora
//         // strcpy(atual_player.nome, name);
//         // if(!contnames)
//         // {
//         //     fwrite(&atual_player, sizeof(jogador), 1, p);
//         //     printf("DE BOA:  %s escrito com sucesso!\n\n", atual_player.nome);
//         // }
        
//         // char newname[10];
//         // strcpy(newname, name);
//         // printf("NEWNAME: %s\n\n", newname);
//         // // int result = SaveFileText(nome_arquivo, newname);
//         // int result = fputs(newname, at);
//         // if(result == EOF)
//         //     printf("ALERTA: Erro na gravação do arquivo");

//     //     finishScreen = 1;
//     //     PlaySound(fxCoin);
//     // }
        
//     fclose(at);
//     fclose(p);
// }

// bool IsAnyKeyPressed()
// {
//     bool keyPressed = false;
//     int key = GetKeyPressed();

//     if ((key >= 32) && (key <= 126)) keyPressed = true;

//     return keyPressed;
// }

// // Nome Screen Unload logic
// void UnloadNomeScreen(void)
// {
//     // TODO: Unload Nome screen variables here!
// }


// // Nome Screen should finish?
// int FinishNomeScreen(void)
// {
//     return finishScreen;
// }
