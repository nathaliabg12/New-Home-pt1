/*****ARQUIVO PARA CRIAÇÃO DE DADOS FAKE NO ARQUIVO BINÁRIO ******/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct 
{
    char nome[10];
    int pontuacao;
    float tempo;    
} jogador;

FILE* fopen_e_teste(char* caminho, char* modo)
{
    FILE* f;
    f = fopen(caminho, modo);
    if(f == NULL)
    {
        perror("Erro ao encontrar arquivo.\n");
        exit(1);
    }
}


int main()
{
    FILE* p;
    FILE* at;
    p = fopen_e_teste("dadosusuarios.bin", "a+b");
    at = fopen_e_teste("atual_usuario.txt", "w");

    jogador bot;

    char name[10] = "Joan";
    strcpy(bot.nome, name);
    bot.pontuacao = 15;
    bot.tempo = 10.5;

    fwrite(&bot, sizeof(jogador), 1, p);
    fputs(name, at);

    fclose(at);
    fclose(p);
}