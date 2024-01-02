#ifndef __COMPROMISSO_H
#define __COMPROMISSO_H

#include<stdlib.h>
#include <stdio.h>
#include<stdbool.h>
#include<string.h>
#define M 100

typedef enum {
 	ORIENTACAO = 1,
 	AULA,
 	COMPROMISSO_PARTICULAR,
 	EVENTO,
 	REUNIAO
 }tipo_de_compromisso;
	
typedef enum {
 	A_SER_CUMPRIDO,
 	ADIAVEL,
 	CANCELADO
 }status_compromiso;

typedef struct TDATA {
	int dia,mes;
	int hora, minuto;
}TDATA;

typedef struct compromisso{
	char nome_do_compromisso[M];
	int identificador;
	tipo_de_compromisso tipo;
	int prioridade; //pq existe o tipo de compromisso tem um grau de prioridade que pode ser alterado, porem seu tipo permanece.
	status_compromiso status;
	bool adiavel;
	TDATA data;
	unsigned int duracao;
}TCOMPROMISSO;

int inicializa_compromisso( TCOMPROMISSO* comp);
int altera_prioridade(TCOMPROMISSO* comp,int novaPri);
int retorna_prioridade(TCOMPROMISSO comp);
bool Eadiavel(TCOMPROMISSO *c, bool adiavel);
bool temConflito(TCOMPROMISSO comp1, TCOMPROMISSO comp2);
int atribuiStatus(TCOMPROMISSO* comp, status_compromiso status);
int retornaStatus(TCOMPROMISSO comp);
void imprimecompromisso(TCOMPROMISSO *comp);
char * tipo_de_compromisso_string(tipo_de_compromisso t);
char * status_compromiso_string(status_compromiso s);
int* calcula_duracao_final(int duracao_minutos,TDATA inicial);
void converte_dia_hora_minuto(unsigned int duracao, int* duracao_dia_hora_minuto);

#endif /* __COMPROMISSO_H */