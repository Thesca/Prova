/*
	curitiba 27/04/2023
	universidade positivo
	escola de tecnologia da informacao
	desenvolvimento de software
	prof jean diogo
	
	--------------------------------------------------------------------------
	
	PROVA 1 (2.0)
	
	INSTRUCOES
	
	analise o codigo abaixo e implemente as funcoes necessarias para que os testes feitos na funcao main funcionem (procure pelos "TODO" no codigo)
	voce pode adicionar codigo a vontade, mas a funcao main e as structs nao podem ser alteradas e nao sao permitidas variaveis globais
	
	toda a prova deve ser feita neste unico arquivo e ele deve ser submetido no blackboard ate o final da aula
	a prova eh individual e pode ser feita no seu proprio computador ou nos computadores do laboratorio
	eh permitida consulta a internet e ao material de aula, mas nao eh permitida comunicacao com colegas, uso de celular ou uso de chat-gpt
	tudo que for adicionado deve ser de sua autoria, plagio e cola implicarao na anulacao da nota
	eh permitido sair da sala durante a prova, desde que uma pessoa por vez
	
	CONTEXTO
	
	o mestre do santuario decidiu que no proximo torneio galatico os cavaleiros de ouro se enfrentarao entre si
	os cavaleiros decidiram fazer um sistema de apostas onde cada cavaleiro podera apostar dinheiros em quem sera o vencedor
	ninguem pode apostar em si mesmo, apenas os cavaleiros de ouro podem receber apostas, e cada cavaleiro pode fazer no maximo tres apostas
	(portanto auto-apostas, apostas em cavaleiros nao listados e apostas alem da terceira devem ser ignoradas)
	como em anime ninguem tem o mesmo nome, nao foram usados ids e os apostadores e apostados sao identificados por seus nomes
	como ninguem no santuario sabe programar, terceirizaram o problema para os alunos e alunas da positivo
	eleve seu cosmo e gabarite essa prova ou sera banido do reino de athena :)
	
	--------------------------------------------------------------------------
	
	INSIRA SEU NOME COMPLETO AQUI: Thiago Martins Escaliante
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aposta_t
{
	char * nome;
	double valor;
}
aposta_t;

typedef struct apostador_t
{
	char * nome;
	int count;
	aposta_t * apostas[3];
}
apostador_t;

apostador_t * constroi_apostador(char * nome)
{
	apostador_t * apostador = (apostador_t *) malloc(sizeof(apostador_t));
	apostador->nome = (char *) malloc(sizeof(char) * strlen(nome) + 1);
	strcpy(apostador->nome, nome);
	apostador->count = 0;
	apostador->apostas[0] = NULL;
	apostador->apostas[1] = NULL;
	apostador->apostas[2] = NULL;
	return apostador;
}

void fazer_aposta(apostador_t ** apostadores, int num_apostadores, char * apostador, char * aposta, double valor)
{
	//(0.5)
	aposta_t * apostaInsert = (aposta_t *) malloc(sizeof(aposta_t));
	apostaInsert->nome = (char *) malloc (sizeof(char) * strlen(aposta) + 1);
	if (strcmp(aposta, apostador) == 0) {
		printf("Nao e permitido apostar em si mesmo.\n");
		return;
	}
	for (int i = 0; i < num_apostadores; ++i) {
		if (strcmp(apostador, apostadores[i]->nome) == 0) {
			if (apostadores[i]->count > 2) {
				printf("Apostador %s ja atingiu o limite de apostas.\n", apostadores[i]->nome);
				break;
			}
			strcpy(apostaInsert->nome, aposta);
			apostaInsert->valor = valor;
			apostadores[i]->apostas[apostadores[i]->count] = apostaInsert;
			apostadores[i]->count++;
		}
	}
}

double get_valor_jogador(apostador_t ** apostadores, int num_apostadores, char * aposta)
{
	//(0.4)
	double valor = 0.0;
	for (int i = 0; i < num_apostadores; ++i) {
		for (int j = 0; j < apostadores[i]->count; ++j) {
			if (strcmp(apostadores[i]->apostas[j]->nome, aposta) == 0) {
				valor += apostadores[i]->apostas[j]->valor;
			}
		}
	}
	return valor;
}

char * get_jogador_mais_valioso(apostador_t ** apostadores, int num_apostadores)
{
	//(0.2)
	int valor, i;
	double maior = 0.0;

	for (i = 0; i < num_apostadores; ++i) {
		valor = get_valor_jogador(apostadores, num_apostadores, apostadores[i]->nome);
		if (valor > maior) {
			maior = valor;
		}
	}
	for (i = 0; i < num_apostadores; ++i) {
		valor = get_valor_jogador(apostadores, num_apostadores, apostadores[i]->nome);
		if (maior == valor) {
			break;
		}
	}
	return apostadores[i]->nome;
}

double get_media_apostas(apostador_t ** apostadores, int num_apostadores)
{
	//(0.4)
	printf("Entrou na GetMediaApostas.\n");
	double soma = 0;
	double media;
	double count = 0;
	for (int i = 0; i < num_apostadores; ++i) {
		for (int j = 0; j < apostadores[i]->count; ++j) {
			soma += apostadores[i]->apostas[j]->valor;
			count++;
		}
	}
	media = soma/count;
	return media;
}

int get_num_sem_aposta(apostador_t ** apostadores, int num_apostadores)
{
	//(0.5)
	int num = 0;
	int count = 0;
	double valor = 0.0;

	for (int i = 0; i < num_apostadores; ++i) {
		valor = get_valor_jogador(apostadores, num_apostadores, apostadores[i]->nome);
		if (valor == 0) {
			++count;
		}
	}
	return count;
}

int main()
{
	int const NUM_APOSTADORES = 12;
	
	apostador_t * apostadores[NUM_APOSTADORES];
	
	apostadores[0]  = constroi_apostador("aldebaran");
	apostadores[1]  = constroi_apostador("afrodite");
	apostadores[2]  = constroi_apostador("aioria");
	apostadores[3]  = constroi_apostador("aioros");
	apostadores[4]  = constroi_apostador("camus");
	apostadores[5]  = constroi_apostador("dohko");
	apostadores[6]  = constroi_apostador("mascara da morte");
	apostadores[7]  = constroi_apostador("milo");
	apostadores[8]  = constroi_apostador("mu");
	apostadores[9]  = constroi_apostador("saga");
	apostadores[10] = constroi_apostador("shaka");
	apostadores[11] = constroi_apostador("shura");
	
	fazer_aposta(apostadores, NUM_APOSTADORES, "aldebaran"       , "mu"              , 5.56);
	fazer_aposta(apostadores, NUM_APOSTADORES, "aldebaran"       , "dohko"           , 2.59);
	fazer_aposta(apostadores, NUM_APOSTADORES, "afrodite"        , "milo"            , 4.35);
	fazer_aposta(apostadores, NUM_APOSTADORES, "afrodite"        , "mascara da morte", 2.02);
	fazer_aposta(apostadores, NUM_APOSTADORES, "aioria"          , "aioros"          , 6.21);
	fazer_aposta(apostadores, NUM_APOSTADORES, "aioros"          , "aioria"          , 6.02);
	fazer_aposta(apostadores, NUM_APOSTADORES, "camus"           , "shaka"           , 5.51);
	fazer_aposta(apostadores, NUM_APOSTADORES, "dohko"           , "aldebaran"       , 8.00);
	fazer_aposta(apostadores, NUM_APOSTADORES, "mascara da morte", "aldebaran"       , 2.75);
	fazer_aposta(apostadores, NUM_APOSTADORES, "milo"            , "milo"            , 6.48);
	fazer_aposta(apostadores, NUM_APOSTADORES, "milo"            , "mascara da morte", 2.08);
	fazer_aposta(apostadores, NUM_APOSTADORES, "mu"              , "aldebaran"       , 4.12);
	fazer_aposta(apostadores, NUM_APOSTADORES, "mu"              , "dohko"           , 5.00);
	fazer_aposta(apostadores, NUM_APOSTADORES, "mu"              , "shaka"           , 2.07);
	fazer_aposta(apostadores, NUM_APOSTADORES, "saga"            , "afrodite"        , 1.26);
	fazer_aposta(apostadores, NUM_APOSTADORES, "saga"            , "kanon"           , 1.00);
	fazer_aposta(apostadores, NUM_APOSTADORES, "saga"            , "mascara da morte", 1.05);
	fazer_aposta(apostadores, NUM_APOSTADORES, "saga"            , "milo"            , 1.60);
	fazer_aposta(apostadores, NUM_APOSTADORES, "shaka"           , "mu"              , 5.74);
	fazer_aposta(apostadores, NUM_APOSTADORES, "shura"           , "dohko"           , 2.90);
	fazer_aposta(apostadores, NUM_APOSTADORES, "shura"           , "afrodite"        , 2.12);
	
	printf("-----\n");
	printf("o valor de apostas em aldebaran de touro foi %.2lf\n"            , get_valor_jogador(apostadores, NUM_APOSTADORES, "aldebaran"));
	printf("o valor de apostas em afrodite de peixes foi %.2lf\n"            , get_valor_jogador(apostadores, NUM_APOSTADORES, "afrodite"));
	printf("o valor de apostas em aioria de leao foi %.2lf\n"                , get_valor_jogador(apostadores, NUM_APOSTADORES, "aioria"));
	printf("o valor de apostas em aioros de sagitario foi %.2lf\n"           , get_valor_jogador(apostadores, NUM_APOSTADORES, "aioros"));
	printf("o valor de apostas em camus de aquario foi %.2lf\n"              , get_valor_jogador(apostadores, NUM_APOSTADORES, "camus"));
	printf("o valor de apostas em dohko de libra foi %.2lf\n"                , get_valor_jogador(apostadores, NUM_APOSTADORES, "dohko"));
	printf("o valor de apostas em mascara da morte de cancer foi %.2lf\n"    , get_valor_jogador(apostadores, NUM_APOSTADORES, "mascara da morte"));
	printf("o valor de apostas em milo de escorpiao foi %.2lf\n"             , get_valor_jogador(apostadores, NUM_APOSTADORES, "milo"));
	printf("o valor de apostas em mu de aries (melhor cavaleiro) foi %.2lf\n", get_valor_jogador(apostadores, NUM_APOSTADORES, "mu"));
	printf("o valor de apostas em saga de gemeos foi %.2lf\n"                , get_valor_jogador(apostadores, NUM_APOSTADORES, "saga"));
	printf("o valor de apostas em shaka de virgem foi %.2lf\n"               , get_valor_jogador(apostadores, NUM_APOSTADORES, "shaka"));
	printf("o valor de apostas em shura de capricornio foi %.2lf\n"          , get_valor_jogador(apostadores, NUM_APOSTADORES, "shura"));
	printf("-----\n");
	printf("a media de apostas foi %.2lf\n"                                  , get_media_apostas(apostadores, NUM_APOSTADORES));
	printf("o cavaleiro com maior valor de apostas foi \"%s\"\n"             , get_jogador_mais_valioso(apostadores, NUM_APOSTADORES));
	printf("o numero de cavaleiros que nao recebeu nenhuma aposta foi %i\n"  , get_num_sem_aposta(apostadores, NUM_APOSTADORES));
	printf("-----\n");
	
	return 0;
}

