#include "compromisso.h"
#define P 12 //total de professores
#define maxTam 365  //numero maximo de eventos em um ano

typedef struct TAGENDA {  //lista de compromissos(sequencia de eventos)
	int id_agenda;
	char nome_professor[M];
	int ano;
	int tamanho;
	TCOMPROMISSO compromisso[maxTam];
} TAGENDA;

void cria_agenda(TAGENDA *agenda,int idProf,char *nome_professor, int ano);  //nova_agenda ou insere_agenda ?
char recuperaAgenda(TAGENDA *agenda,TDATA data);
int insere_compromisso(TAGENDA *agenda,tipo_de_compromisso tipo, TDATA data,int duracao, char *nome); //insere_no_fim
int remove_compromisso(int id_compromisso, TAGENDA* agenda);
void imprime_agenda(TAGENDA *agenda);
int resolve_conflito(TAGENDA *agenda);
int retorna_adiamentos(TAGENDA* agenda);
int retorna_cancelamentos(TAGENDA* agenda);
int retorna_compromissos(TAGENDA* agenda);
void imprime_compromissos_adiados(TAGENDA* agenda);
void imprime_compromissos_cancelados(TAGENDA* agenda);
void imprime_compromissos_acumprir(TAGENDA* agenda);
TAGENDA* ordena_agenda(TAGENDA *agenda);