#include <stdio.h>

typedef struct dados
{
    int codigo;
    char nome[50];
    float venda;
    int mes;
} vendedor;

void main ()
{
    FILE *arquivo;
    char vetor[] = {"dados.bin"};
    vendedor v;
    int opcao, tamanho = 50, quant = 0;

    do{
        printf("\n1 - Criar Arquivo");
        printf("\n2 - Incluir Vendedor");
        printf("\n3 - Excluir Vendedor");
        printf("\n4 - Alterar Vendendor");
        printf("\n5 - Imprimir Vendedores");
        printf("\n6 - Excluir Arquivo");
        printf("\n7 - Sair");
        printf("\nOpcao: ");
        scanf("%d", &opcao);
        fflush(stdin);

        switch(opcao)
        {
            case 1://Criar o arquivo de dados
                A1(arquivo);
                break;
            case 2://Incluir um determinado registro no arquivo
                A2(arquivo, vetor, quant, tamanho);
                break;
            case 3://Excluir um determinado vendedor no arquivo
                A3();
                break;
            case 4://Alterar o valor de uma venda no arquivo
                A4(arquivo, v,vetor);
                break;
            case 5://Imprimir os registros na saída padrão
                A5(arquivo, v);
                break;
            case 6://Excluir o arquivo de dados
                A6();
                break;
            case 7://Finalizar o programa
                break;
            default:
                if(opcao != 7)
                {
                    printf("\nOpcao invalida!!!");
                }
        }
    }while(opcao != 7);
}
void A1(FILE *arquivo)//criar o arquivo de dados
{
    
    arquivo=fopen("dados.bin", "wb");

    if(arquivo==NULL)
    {
        printf("\nErro na criacao do arquivo!");
    }
    else
    {
        printf("\nArquivo criado com sucesso!");
        fclose(arquivo);
    }
}
void A2(FILE *arquivo, vendedor **vetor, int quant, int tam)//Incluir um determinado registro no arquivo
{
    arquivo = fopen("dados.bin", "ab");
 
    if(arquivo==NULL)
    {
        printf("\nErro ao abrir o arquivo do arquivo!");
    }
    else
    {
        if(quant < tam)
        {
            vendedor *novo = malloc(sizeof(vendedor));
            printf("\nDigite o Codigo do Vendedor: ");
            printf("%d", novo->codigo);
            fflush(stdin);
            printf("\nDigite o nome do Vendedor: ");
            scanf("%49[^\n]", novo->nome);
            fflush(stdin);
            printf("\nVendas: ");
            scanf("%f", novo->venda);
            fflush(stdin);
            printf("\nMes(numero correspondente): ");
            printf("%d", novo->mes);
            fflush(stdin);
            vetor[quant] = novo;
            quant = quant + 1;
        }
        fclose(arquivo);
    }
}
void A3 ()//Excluir um determinado vendedor no arquivo
{
    printf("\nFunçao nao criada");
}
void A4(FILE *arquivo, vendedor c, char arq[])//Alterar o valor de uma venda no arquivo
{
    arquivo = fopen("dados.bin", "rb");
    int i;
    i = 1;
    int codigo;
 
    if(arquivo==NULL)
    {
        printf("\nErro ao abrir o arquivo do arquivo!");
    }
    else
    {
        vendedor *novo = malloc(sizeof(vendedor));
        printf("\nLista de vendedores:");
        printf("\n----------------------------");
        while(fread(&c, sizeof(vendedor), 1, arquivo))
        {
            printf("\n%d = %s", c.codigo, c.nome);
        }
        printf("\n----------------------------");
        printf("\nDigite o Codigo do Vendedor: ");
        printf("%d", novo->codigo);
        fflush(stdin);
        printf("\nDigite o Codigo do Vendedor: ");
        scanf("%4[^\n]", novo->codigo);
        fflush(stdin);
        printf("\nDigite o nome do Vendedor: ");
        scanf("%49[^\n]", novo->nome);
        fflush(stdin);
        printf("\nVendas: ");
        scanf("%f", novo->venda);
        fflush(stdin);
        printf("\nMes(numero correspondente): ");
        printf("%d", novo->mes);
        fflush(stdin);
        fseek(arquivo, codigo * sizeof(vendedor), SEEK_SET);
        fwrite(&c, sizeof(vendedor), 1, arquivo);
        fclose(arquivo);
    }
}
void A5 (FILE *arquivo, vendedor c)//Imprimir os registros na saída padrão 
{
    printf("\nLista de vendedores:");
        printf("\n------------------------------------------------------------------------------");
        while(fread(&c, sizeof(vendedor), 1, arquivo))
        {
            printf("\n%d", c.codigo);
            printf("\t%s", c.nome);
            printf("\t%.2f", c.venda);
            printf("\t%d", c.mes);
        }
        printf("\n-----------------------------------------------------------------------------");
}
void A6 ()//Excluir o arquivo de dados binarios
{
    printf("\nFunçao nao criada");
}
