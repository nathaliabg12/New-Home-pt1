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
    p = fopen_e_teste("dadosusuarios.bin", "a+b");

    jogador bot;

    // char name[10] = "Pedro";
    // strcpy(bot.nome, name);
    // bot.pontuacao = 18;
    // bot.tempo = 8.0;
    
    // fwrite(&bot, sizeof(jogador), 1, p);

    while(fread(&bot, sizeof(jogador), 1, p) > 0)
    {
        printf("Nome: %s\n Pontuação: %d\n Tempo: %f\n", bot.nome, bot.pontuacao, bot.tempo);
    }

    fclose(p);
}