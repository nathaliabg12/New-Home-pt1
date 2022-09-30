#include <stdio.h>
#include <stdlib.h>

typedef struct jogador
{
     char nome[10];
     int pontuacao;
     float tempo;    
 }jogador;


int main()
{
    FILE* f;
    f = fopen("dados_usuarios.bin", "rb"); 
    if(f == NULL)
    {
        perror("Problema ao encontrar ou abrir arquivo.\n");
        exit(1);
    }

    jogador prod;

    int i = 0;
    while ((!feof(f)))
    {
        fread(&prod, sizeof(jogador), 1, f);
        printf("Nome: %s  Pontuação: %d\n", prod.nome, prod.pontuacao);
        // i++;
        // if(i > 10)
        //     break;
    }

    fclose(f);
    
    
}
