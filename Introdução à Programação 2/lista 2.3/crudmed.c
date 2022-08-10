/*
 ============================================================================
 Name        : crudMedicos.c
 Autor       : Pablo Rafaelo Si <http://prafaelo.com>, Emanuele Baron
 Versão      : 1.0
 Copyright   : 26/11/2014
 Descrição   : Trabalho final da disciplina de LPG da Universidade do Estado
               de Santa Catarina - UDESC <http://www.cct.udesc.br>
 Professor   : Luciana Rita Guedes
 Título      : CRUD em C
 ============================================================================
 *
 * SUMÁRIO EXECUTIVO:
 *
 * A partir das estruturas de dados, construa um programa que permita o
 * gerenciamento básico deste cadastro simples com a utilização de arquivos binários.
 * Tal programa deve possibilitar:
 * 1. Inserir novos registros (um de cada vez);
 * 2. Remover registros existentes (um de cada vez);
 * 3. Alterar campos de registro (exceto o campo “chave” que identifica o registro);
 * 4. Exibir o conteúdo do cadastro (listagem completa, um registro em cada linha);
 * 5. Consultar registros pelo campo “chave”;
 * 6. Ordenar os registros em ordem crescente do campo “chave”;
 *
 * Condições:
 * a. O menu deverá ser implementado na função principal e as opções devem estar em
 * funções separadas
 * b. O campo chave é o campo da estrutura principal que identifica o registro como
 * único; por exemplo, num cadastro de estudantes, o nome do estudante ou o número de
 * matrícula poderiam ser (um ou outro) o campo chave.
 * c. A opção de inserir deve permitir cadastrar UM novo registro de cada vez, após
 * isso o programa volta a apresentar o menu. A inserção não deve permitir cadastrar
 * o campo “chave” repetido, isto é, se o registro já tiver sido cadastrado, deve
 * mostrar uma mensagem de aviso e solicitar os dados novamente.
 * d. A opção de remover deve perguntar qual registro deve ser apagado, através do
 * campo “chave” que identifica o registro. Caso o usuário digite um registro
 * inexistente, deve mostrar uma mensagem de aviso e pedir a informação novamente.
 * Sugere-se que para a remoção de registro utilize-se um arquivo auxiliar que receberá
 * todos os registros exceto aquele que deve ser removido. Ao final deve-se remover
 * (destruir) o arquivo velho e renomear o arquivo auxiliar com o mesmo nome do arquivo
 * velho. Não é obrigatório usar esta solução!
 * e. A opção de alterar também deve perguntar qual registro deve ser apagado através do
 * campo “chave”. Caso o usuário digite um registro inexistente, deve mostrar uma
 * mensagem de aviso e pedir a informação novamente. O usuário poderá alterar qualquer
 * informação do registro ou mesmo todas as informações de uma só vez, EXCETO o campo
 * chave, que não poderá ser alterado.
 * f. A opção de listar (exibir todos os registros) deve mostrar um relatório em tela
 * com um cabeçalho e com um registro em cada linha (se possível). Veja modelo abaixo:
 *
 * Listagem de Músicas Cadastradas
 *
 * Título		    Artista     	   Nacionalidade	Data Cadastramento
 * --------------	-----------------  ---------------	------------------
 * Carinhoso	    Pixinguinha		   Brasileira		11/10/2010
 * Love me do	    The Beatles		   Inglesa		    15/11/2010
 *
 * g. A opção de consultar um registro deve perguntar qual registro o usuário deseja
 * visualizar através do campo “chave”. Caso o usuário digite um registro inexistente,
 * deve mostrar uma mensagem de aviso e pedir a informação novamente.
 * h. A opção ordenar deve fazer com que os registros sejam ordenados em ordem ascendente
 * pelo campo “chave”.
 * i. O menu deve apresentar uma opção para sair do programa.
 * j. Use e abuse de funções por valor ou por referência mas em nenhuma hipótese faça uso
 * de variáveis globais. Use e abuse de funções da biblioteca padrão do C, mas tenha certeza
 * que conhece o seu comportamento.
 * k. Sugere-se o uso de fread e fwrite para leitura e gravação de dados no arquivo.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include <unistd.h> // <www.fifi.org/cgi-bin/man2html/usr/share/man/man2/access.2.gz>

/*constantes do programa*/
#define SIM 1
#define NAO 0
#define NOME_DO_ARQUIVO "medicos.bin"

/*modos de abertura do arquivo*/
#define SOMENTE_LEITURA_BINARIO "rb"
#define CRIA_LE_ESCREVE_BINARIO "a+b"
#define CRIA_LE_SOBRESCREVE_BINARIO "w+b"

/*estruturas do programa*/
typedef struct Data {
    int dia, mes, ano;
} Data;

typedef struct Medico {
    int unsigned numeroCrm; //chave
    char nome[20];
    char especialidade[15];
    int medicoCirurgiao;
    float valorAnuidadeCrm;
    Data dataDeCadastramento;
} Medico;

typedef struct Colecao {
	int tamanho;
	int crmDoMedicoEscolhido;
	void *matriz;
} Colecao;

/*funcoes do programa*/
int sairDoPrograma();
int inserirRegistro();
int removerRegistros();
int alterarRegistros();
int consultarRegistros();
void listarRegistros();
void ordenarRegistros();

Colecao consultarRegistro(int imprimeMsg);
void pedirMedico(Medico *medico, int pedeTodosOsCampos);
void cadastrarDiaMesAnoAtual(int *dia, int *mes, int *ano);
void mostrarMedico(Medico medico);
void mostrarMedicos(Medico *medicos, size_t tamanhoDaMatriz, int ordenado);
Colecao buscarMedicosNoArquivo (int crmDoMedico);
void mostrarCabecalhoDoMedico();
int perguntar(char *pergunta);

FILE *abrirArquivo(char *nomeDoArquivo, char *modoDeLeitura);
int verificaSeArquivoExiste(char *nomeDoArquivo, int modoDeAcesso);
void fecharArquivo(FILE *arquivo);

int main(void)
{

	//formata decimal com separador de virgula.
	setlocale(LC_NUMERIC, "pt_BR.utf-8");

	printf("Bem vindo!\n\n");

	while(SIM)
	{
		printf("Escolha a opcao desejada:\n");

		char opcao;
		printf("========= MENU =========\n");
		printf("0 - Sair\n");
		printf("1 - Inserir\n");
		printf("2 - Remover\n");
		printf("3 - Alterar\n");
		printf("4 - Consultar\n");
		printf("5 - Listar\n");
		printf("6 - Listar Ordenado Asc.\n");
		printf("========================\n\n");

		scanf("%s",&opcao);

		if(opcao=='0')
		{
			if (sairDoPrograma())
				break;
			printf("\nVoltando ao menu...\n\n");
			continue;
		}

		if(opcao=='1')
		{
			while(inserirRegistro());
			printf("\nVoltando ao menu...\n\n");
			continue;
		}

		if(opcao=='2')
		{
			while(removerRegistros());
			printf("\nVoltando ao menu...\n\n");
			continue;
		}

		if(opcao=='3')
		{
			while(alterarRegistros());
			printf("\nVoltando ao menu...\n\n");
			continue;
		}

		if(opcao=='4')
		{
			while(consultarRegistros());
			printf("\nVoltando ao menu...\n\n");
			continue;
		}

		if(opcao=='5')
		{
			listarRegistros();
			printf("\nVoltando ao menu...\n\n");
			continue;
		}

		if(opcao=='6')
		{
			ordenarRegistros();
			printf("\nVoltando ao menu...\n\n");
			continue;
		}

		printf("\nOpcao invalida, voltando ao menu...\n\n");
	}

	printf("\nAte logo!\n");

    return EXIT_SUCCESS;
}

int sairDoPrograma()
{
	return perguntar("Deseja sair do programa? (Sim/Nao)\n");
}

int inserirRegistro()
{

	Colecao medicoConsultado = consultarRegistro(NAO);
	if(medicoConsultado.tamanho==0)
	{
		Medico medico;
		medico.numeroCrm = medicoConsultado.crmDoMedicoEscolhido;

		pedirMedico(&medico, SIM);

		mostrarCabecalhoDoMedico();
		mostrarMedico(medico);

		if(perguntar(NULL))
		{
			FILE *arquivo = abrirArquivo(NOME_DO_ARQUIVO, CRIA_LE_ESCREVE_BINARIO);
			fwrite(&medico, sizeof(Medico), 1, arquivo);
			fecharArquivo(arquivo);

			printf("\nRegistro incluido com sucesso!\n");

			return NAO;
		}
		else
		{
			printf("\nDados descartados!\n");
			if(!perguntar("\nDeseja tentar novamente? (Sim/Nao)\n"))
				return NAO;
		}
	}
	else
	{
		printf("\nNúmero de CRM já existe cadastrado!\n");
		if(!perguntar("\nDeseja tentar novamente? (Sim/Nao)\n"))
			return NAO;
	}

	return SIM;
}

void pedirMedico(Medico *medico, int pedeTodosOsCampos)
{

	Medico medicoAlterado = *medico;

	if(pedeTodosOsCampos || perguntar("\nDeseja alterar o nome? (Sim/Nao)\n"))
	{
		fpurge(stdin);
		printf("Informe o nome do medico:\n");
		fgets(medicoAlterado.nome, 20, stdin);
		medicoAlterado.nome[strlen(medicoAlterado.nome)-1] = '\0'; //necessário pois fgets coloca \n no final da string

	}

	if(pedeTodosOsCampos || perguntar("\nDeseja alterar se é cirugião? (Sim/Nao)\n"))
	{
		printf("Informe se ele é cirurgião: (0 - Nao | 1 - Sim)\n");
		scanf("%i",&medicoAlterado.medicoCirurgiao);
	}

	if(pedeTodosOsCampos || perguntar("\nDeseja alterar a especialidade? (Sim/Nao)\n"))
	{
		fpurge(stdin);
		printf("Informe a especialidade:\n");
		fgets(medicoAlterado.especialidade, 15, stdin);
		medicoAlterado.especialidade[strlen(medicoAlterado.especialidade)-1]= '\0';
	}

	if(pedeTodosOsCampos || perguntar("\nDeseja alterar o valor da anuidade? (Sim/Nao)\n"))
	{
		printf("Informe o valor da anuidade do CRM:\n");
		scanf("%f",&medicoAlterado.valorAnuidadeCrm);
	}

	int diaAtual, mesAtual, anoAtual;
	cadastrarDiaMesAnoAtual(&diaAtual, &mesAtual, &anoAtual);
	medicoAlterado.dataDeCadastramento.dia = diaAtual;
	medicoAlterado.dataDeCadastramento.mes = mesAtual;
	medicoAlterado.dataDeCadastramento.ano = anoAtual;

	*medico = medicoAlterado;
}


void listarRegistros()
{
	Colecao colecaoDeMedicos = buscarMedicosNoArquivo(0);

	if(colecaoDeMedicos.tamanho > 0)
	{
		mostrarCabecalhoDoMedico();
		mostrarMedicos(colecaoDeMedicos.matriz, colecaoDeMedicos.tamanho, NAO);
	}
	else
		printf("\nNenhum médico localizado para listar!\n");
}

/**
 * @param crmDoMedico: == 0 - tudo
 * 					    > 0 - busca pelo CRM informado.
 */
Colecao buscarMedicosNoArquivo(int crmDoMedico)
{
	FILE *arquivo = abrirArquivo(NOME_DO_ARQUIVO, SOMENTE_LEITURA_BINARIO);

	Colecao colecaoDeMedicos;
	colecaoDeMedicos.tamanho=0;
	colecaoDeMedicos.crmDoMedicoEscolhido = crmDoMedico;

	Medico *medicos = (Medico *)malloc(sizeof(Medico));

	while(!feof(arquivo))
	{
		Medico medico;
		fread(&medico, sizeof(Medico), 1, arquivo);
		if((medico.numeroCrm == crmDoMedico || crmDoMedico == 0) && !feof(arquivo))
		{

			medicos = (Medico *)realloc(medicos, (colecaoDeMedicos.tamanho+1)*sizeof(Medico));

			medicos[colecaoDeMedicos.tamanho] = medico;
			colecaoDeMedicos.tamanho++;
		}
	}

	colecaoDeMedicos.matriz = medicos;

	fecharArquivo(arquivo);

	return colecaoDeMedicos;
}


int consultarRegistros()
{
	Colecao medicoConsultado = consultarRegistro(SIM);
	if(medicoConsultado.tamanho==0 && perguntar(NULL))
		return SIM;
	return NAO;
}

Colecao consultarRegistro(int imprimeMsg)
{
	int crmDoMedico=0;
	printf("Informe o numero do CRM:\n");
	scanf("%i", &crmDoMedico);

	Colecao colecaoDeMedicos = buscarMedicosNoArquivo(crmDoMedico);

	//verifica se achou algum médico
	if(colecaoDeMedicos.tamanho > 0)
	{
		mostrarCabecalhoDoMedico();
		mostrarMedicos(colecaoDeMedicos.matriz, colecaoDeMedicos.tamanho, NAO);
	}
	else
		if(imprimeMsg)
			printf("\nNenhum médico localizado com o código informado!\n");

	return colecaoDeMedicos;
}

void ordenarRegistros()
{
	Colecao colecaoDeMedicos = buscarMedicosNoArquivo(0);

	if(colecaoDeMedicos.tamanho > 0)
	{
		mostrarCabecalhoDoMedico();
		mostrarMedicos(colecaoDeMedicos.matriz, colecaoDeMedicos.tamanho, SIM);
	}
	else
		printf("\nNenhum médico localizado para listar!\n");
}

int alterarRegistros()
{
	Colecao medicoConsultado = consultarRegistro(SIM);

	if(medicoConsultado.tamanho > 0 && perguntar(NULL))
	{
		Medico *medico = medicoConsultado.matriz;

		pedirMedico(medico, NAO);

		mostrarCabecalhoDoMedico();
		mostrarMedico(*medico);

		if(perguntar("\nDeseja gravar a alteração acima? (Sim/Nao)\n"))
		{
			Colecao colecaoDeMedicosDoArquivo = buscarMedicosNoArquivo(0);

			Medico *atualColeCaoDeMedicosDoArquivo = colecaoDeMedicosDoArquivo.matriz;

			for(int i=0; i<colecaoDeMedicosDoArquivo.tamanho;i++)
			{
				if(atualColeCaoDeMedicosDoArquivo[i].numeroCrm == medico[0].numeroCrm)
				{
					atualColeCaoDeMedicosDoArquivo[i] = *medico;
				}
			}

			FILE *arquivo = abrirArquivo(NOME_DO_ARQUIVO, CRIA_LE_SOBRESCREVE_BINARIO);
			fwrite(atualColeCaoDeMedicosDoArquivo, (colecaoDeMedicosDoArquivo.tamanho)*sizeof(Medico), 1, arquivo);
			fecharArquivo(arquivo);

			printf("\nRegistro alterado com sucesso!\n");

			return NAO;
		}
		else
			if(!perguntar("\nDados descartados! Deseja tentar novamente? (Sim/Nao)\n"))
				return NAO;


	}
	else
		if(!perguntar("\nDeseja tentar novamente? (Sim/Nao)\n"))
			return NAO;

	return SIM;
}


int removerRegistros()
{
	Colecao medicoConsultado = consultarRegistro(SIM);

	if(medicoConsultado.tamanho > 0 && perguntar(NULL))
	{
		Colecao colecaoDeMedicosDoArquivo = buscarMedicosNoArquivo(0);

		Medico *atualColeCaoDeMedicosDoArquivo = colecaoDeMedicosDoArquivo.matriz;
		Medico novaColeCaoDeMedicosDoArquivo[colecaoDeMedicosDoArquivo.tamanho-1];

		int j=0;
		for(int i=0; i<colecaoDeMedicosDoArquivo.tamanho;i++)
		{
			if(atualColeCaoDeMedicosDoArquivo[i].numeroCrm != medicoConsultado.crmDoMedicoEscolhido)
			{
				novaColeCaoDeMedicosDoArquivo[j] = atualColeCaoDeMedicosDoArquivo[i];
				j++;
			}
		}

		FILE *arquivo = abrirArquivo(NOME_DO_ARQUIVO, CRIA_LE_SOBRESCREVE_BINARIO);
		fwrite(novaColeCaoDeMedicosDoArquivo, (colecaoDeMedicosDoArquivo.tamanho-1)*sizeof(Medico), 1, arquivo);
		fecharArquivo(arquivo);

		printf("\nRegistro removido com sucesso!\n");

		return NAO;
	}
	else
		if(!perguntar("\nDeseja tentar novamente? (Sim/Nao)\n"))
			return NAO;

	return SIM;
}

void cadastrarDiaMesAnoAtual(int *dia, int *mes, int *ano)
{
	time_t tempoCorrente = time(NULL);
	struct tm *dataAtual = localtime(&tempoCorrente);
	*dia=dataAtual->tm_mday;
	*mes=dataAtual->tm_mon+1;
	*ano=dataAtual->tm_year+1900;
}

void mostrarMedico(Medico medico)
{
	printf("%-21i", medico.numeroCrm);
	printf("%-21s", medico.nome);
	char *medicoCirurgiao;
	if (medico.medicoCirurgiao == SIM)
		medicoCirurgiao = "Sim";
	else
		medicoCirurgiao = "Nao";
	printf("%-21s", medicoCirurgiao);
	printf("%-21s", medico.especialidade);
	printf("R$%-19.2f", medico.valorAnuidadeCrm);
	printf("%i/", medico.dataDeCadastramento.dia);
	printf("%i/", medico.dataDeCadastramento.mes);
	printf("%i", medico.dataDeCadastramento.ano);
	printf("\n");
}

void mostrarMedicos(Medico *medicos, size_t tamanhoDaMatriz, int ordenado)
{
	if(ordenado)
	{
		Medico medicoAux;

		for(int i=0; i<tamanhoDaMatriz-1;i++)
		{
			for(int j=i+1; j<tamanhoDaMatriz;j++)
			{
				if(medicos[i].numeroCrm > medicos[j].numeroCrm)
				{
					medicoAux  = medicos[i];
					medicos[i] = medicos[j];
					medicos[j] = medicoAux;
				}
			}
		}
	}

	for(int i=0; i<tamanhoDaMatriz;i++)
	{
		mostrarMedico(medicos[i]);
	}
}

void mostrarCabecalhoDoMedico()
{
	printf("\n");
	printf("%-21s","Numero CRM");
	printf("%-21s","Nome");
	printf("%-21s","Cirurgiao");
	printf("%-21s","Especialidade");
	printf("%-21s","Vlr An. CRM");
	printf("%-21s","Data Cadastramento");
	printf("\n");
	for(int i=0; i<6; i++)
		printf("%-21s","____________________");
	printf("\n");
}


int perguntar(char *pergunta)
{
	if(pergunta==NULL)
		pergunta="\nDeseja continuar? (Sim/Nao)\n";

	printf("%s",pergunta);
	char resposta;
	scanf("%s", &resposta);
	fpurge(stdin); //limpa buffer de teclado

	if(toupper(resposta) == 'S')
		return SIM;
	if(toupper(resposta) == 'N')
		return NAO;

	printf("\nResposta invalida!\n");

	return NAO;
}

FILE *abrirArquivo(char *nomeDoArquivo, char *modoDeLeitura)
{
	FILE *arquivo;

	if(!verificaSeArquivoExiste(NOME_DO_ARQUIVO, F_OK))
	{
		printf("\nCriando banco de dados do programa...\n");
		arquivo = fopen(nomeDoArquivo, CRIA_LE_SOBRESCREVE_BINARIO);
		fecharArquivo(arquivo);
	}

	arquivo = fopen(nomeDoArquivo, modoDeLeitura);

	if(!arquivo)
	{
		printf("Ocorreu um problema na abertura do arquivo, encerrando programa!");
		exit(EXIT_FAILURE);
	}

	return arquivo;
}

void fecharArquivo(FILE *arquivo)
{
	fclose(arquivo);
}


int verificaSeArquivoExiste(char *nomeDoArquivo, int modoDeAcesso)
{
	if(access(nomeDoArquivo, F_OK) < 0)
	{
		return NAO; //arquivo não existe
	}
	return SIM; //arquivo existe
}