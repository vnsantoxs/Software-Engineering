#include <stdio.h>

typedef struct
{
    char nome[50];
    char telefone[10];
}dados;
void main ()
{
    int opcao;
    dados contato;
    FILE *arquivo;
    
    A0(arquivo, contato);

    printf("1 - Inserir\n");
    printf("2 - Remover\n");
    printf("3 - Pesquisar\n");
    printf("4 - Listar contatos\n");
    printf("\nOpcao: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
        case 1:
            A1(arquivo, contato);
        break;
        case 2:
            printf("\nadd");
        break;
        case 3:
            printf("\nadd");
        break;
        case 4:
            A2(arquivo, contato);
        break;
        default:
            printf("\nOpcao invalida");
    }
}
void A0 (FILE *arquivo, dados contato)//cria o arquivo binario
{
    arquivo = fopen("contato.bin", "wb");
    fclose(arquivo);
}
void A1 (FILE *arquivo, dados contato)//adicionar
{
    arquivo = fdopen("contato.bin", "ab");

    if(arquivo != NULL)
    {
        printf("\nNome: ");
        gets(contato.nome);
        printf("\nTelefone: ");
        gets(contato.telefone);
        fwrite(&contato, sizeof(dados), 1, arquivo);
        fclose(arquivo);
    }
    else
    {
        printf("\nERRO");
    }
}
void A2 (FILE *arquivo, dados contato)//leitura de arquivos
{
    arquivo = fdopen("contato.bin", "rb");
    if(arquivo != NULL)
    {
        while (!feof(arquivo))
        {
            if (fread(&contato, sizeof(dados), 1, arquivo))
            {
                fread(&contato, sizeof(dados), 1, arquivo);
                printf("\nNome: %s", contato.nome);
                printf("\nTell: %s", contato.telefone);
            }
        }
        fclose(arquivo);
    }
    else
    {
        printf("\nERRO");
    }
}
