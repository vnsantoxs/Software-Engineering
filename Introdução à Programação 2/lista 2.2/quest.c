#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char nome[50];
    int tell;
}Contato;

int main()
{
    Contato *agenda[50];
    char arquivo[] = {"agenda.txt"};
    char arquivo2[] = {"agenda.dat"};
    int opcao, tam = 50, quant = 0;

    do{
        printf("\n0 - Sair");
        printf("\n1 - Cadastrar");
        printf("\n2 - Deletar");
        printf("\n3 - Imprimir");
        printf("\n4 - Pesquisar");
        printf("\t5 - Ler contatos");

        scanf("%d", &opcao);
        getchar();
        switch(opcao){
        case 1:
            quant += A1(agenda, quant, tam);
            break;
        case 2:
            printf("\nFunçao indisponivel");
            break;
        case 3:
            A3(agenda, quant);
            break;
        case 4:
            printf("\nFunçao indisponivel");
            break;
        case 5:
            quant = A5(agenda, arquivo);
            break;
        default:
            if(opcao != 0)
                printf("\nOpcao invalida!");
        }
    }while(opcao != 0);

    return 0;
}
int A1 (Contato **c, int quant, int tam)
{
    if(quant < tam){
        Contato *novo = malloc(sizeof(Contato));

        printf("\nNome: ");
        scanf("%49[^\n]", novo->nome);
        printf("\nTell: ");
        scanf("%d", &novo->tell);
        getchar();
        c[quant] = novo;
        return 1;
    }
    else{
        printf("\nERRO\n");
        return 0;
    }
}
void A3(Contato **c, int quant){
    int i;

    printf("\n\t\tLista de Contatos:\n");
    printf("\t--------------------------------\n");
    for(i = 0; i < quant; i++)
    {
        printf("\t%d = %s\t%d\n", i, c[i]->nome, c[i]->tell);
    }
    printf("\t--------------------------------\n");
}
int A5(Contato **c, char arq[])
{
    FILE *file = fopen(arq, "r");
    int quant = 0, i;
    Contato *novo = malloc(sizeof(Contato));

    if(file){
        fscanf(file, "%d\n", &quant);
        for(i = 0; i < quant; i++){
            //fgets(novo->nome, 50, file);
            fscanf(file, "%49[^\n]", novo->nome);
            fscanf(file, "%d\n", &novo->tell);
            c[i] = novo;
            novo = malloc(sizeof(Contato));
        }
        fclose(file);
    }
    else
        printf("\nERRO\n");
    return quant;
}


