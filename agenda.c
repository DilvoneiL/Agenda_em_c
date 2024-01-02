#include"agenda.h"
#include "compromisso.h"


void cria_agenda(TAGENDA *agenda, int idProf, char* nome_professor, int ano) {
  agenda->id_agenda = idProf;
  strcpy(agenda->nome_professor, nome_professor);
  agenda->ano = ano;
  agenda->tamanho = 0;
  printf("Seu ID:%d - nome:%s - ano:%d\n",agenda->id_agenda,agenda->nome_professor,agenda->ano);
}
char recuperaAgenda(TAGENDA *agenda,TDATA data){ 
	int numero_de_compromissos = 0;
	for(int i=0;i < agenda->tamanho;i++){
		if((agenda->compromisso[i].data.mes > data.mes) || agenda->compromisso[i].data.mes == data.dia && agenda->compromisso[i].data.dia ){
			numero_de_compromissos++;
		}
	}
	return printf("\tNome:%s ano:%d Numero de Compromissos apos %d/%d: %d\n",agenda->nome_professor, agenda->ano,data.dia, data.mes,numero_de_compromissos);
}

int insere_compromisso(TAGENDA *agenda,tipo_de_compromisso tipo, TDATA data, int duracao, char *nome){ //agenda [0].
	if (agenda->tamanho == maxTam){
		printf("\tErro: Agenda cheia\n");
		return 0;
	}
	else{
		strcpy(agenda->compromisso[agenda->tamanho].nome_do_compromisso, nome);
		agenda->compromisso[agenda->tamanho].tipo = tipo;
		agenda->compromisso[agenda->tamanho].prioridade = tipo;//grau de prioridade começa igual do tipo, mas pode ser alterado
		agenda->compromisso[agenda->tamanho].data = data;
		agenda->compromisso[agenda->tamanho].duracao = duracao;
		agenda->compromisso[agenda->tamanho].identificador = (agenda->tamanho)+1;
		printf("\tSucesso: ID do compromisso %d\n",agenda->compromisso[agenda->tamanho].identificador); 
		agenda->tamanho++;
		return 1;
	}
}
int remove_compromisso(int id_compromisso, TAGENDA* agenda) {
	int indice;
	TCOMPROMISSO comp;
	if (agenda->tamanho == 0) {
		printf("Erro: Posicao Nao Existe\n");
		return 0; 
	}
	else if(id_compromisso > agenda->tamanho || id_compromisso < 1){ //pq o id está ordem crescente começando do 1. 
		printf("Erro: ID Passado %d\n", id_compromisso);
		printf("ID's Validos 1-%d\n", agenda->tamanho);
		return 0;
	}
	comp = agenda -> compromisso[agenda->tamanho]; // retirar 5 , 1 a 10, enquanto 5<10 maximo de compromisso
	for (indice = id_compromisso; indice <= agenda->tamanho; indice++){
		agenda->compromisso[indice-1] = agenda->compromisso[indice];
	}
	agenda->tamanho--;
	printf("Sucesso: Compromisso Removido ID:%d\n",id_compromisso);
	return 1;
}
void imprime_agenda(TAGENDA *agenda){ //tem que organizar os compromissos para imprimir, falta parte mais importante.
	TCOMPROMISSO comp_indice;
	ordena_agenda(agenda);
	for(int i=0; i < agenda->tamanho; i++){
		for(int j=i+1;j < agenda->tamanho;j++){
			if(agenda->compromisso[i].data.mes == agenda->compromisso[j].data.mes && 
			agenda->compromisso[i].data.dia == agenda->compromisso[j].data.dia &&
			agenda->compromisso[i].data.hora == agenda->compromisso[j].data.hora && 
			agenda->compromisso[i].data.minuto == agenda->compromisso[j].data.minuto){
				if(agenda->compromisso[i].prioridade < agenda->compromisso[j].prioridade){
					comp_indice = agenda->compromisso[i];
					agenda->compromisso[i] = agenda->compromisso[j];		
					agenda->compromisso[j] = comp_indice;
				}
				else if(agenda->compromisso[i].prioridade == agenda->compromisso[j].prioridade){
					switch(agenda->compromisso[j].tipo){
						case EVENTO:
							comp_indice =agenda->compromisso[i];    // i = j-1   0 1 2 
							agenda->compromisso[i] = agenda->compromisso[j];		
							agenda->compromisso[j] = comp_indice;
							break;
						case REUNIAO:
							if(agenda->compromisso[i].tipo != EVENTO){
								comp_indice = agenda->compromisso[i];
								agenda->compromisso[i] = agenda->compromisso[j];		
								agenda->compromisso[j] = comp_indice;
								break;
							}
							else{
								break;
							}
						case AULA:
							if(agenda->compromisso[i].tipo != EVENTO && agenda->compromisso[i].tipo != REUNIAO){
								comp_indice =agenda->compromisso[i];
								agenda->compromisso[i] = agenda->compromisso[j];		
								agenda->compromisso[j] = comp_indice;
								break;
							}
							else{
								break;
							}
						case ORIENTACAO:
							if(agenda->compromisso[i].tipo != EVENTO && agenda->compromisso[i].tipo != REUNIAO){
								if(agenda->compromisso[i].tipo != AULA && agenda->compromisso[i].tipo != ORIENTACAO){
									comp_indice =agenda->compromisso[i];
									agenda->compromisso[i] = agenda->compromisso[j];		
									agenda->compromisso[j] = comp_indice;
									break;
								}
							}
							else{
								break;
							}
						case COMPROMISSO_PARTICULAR:
							if(agenda->compromisso[i].tipo != EVENTO && agenda->compromisso[i].tipo != REUNIAO){
								if(agenda->compromisso[i].tipo != AULA && agenda->compromisso[i].tipo != ORIENTACAO){
									comp_indice =agenda->compromisso[i];
									agenda->compromisso[i] = agenda->compromisso[j];		
									agenda->compromisso[j] = comp_indice;
									break;
								}
							}
							else{
								break;
							}
						default:
							break; 
					}	
				}
			}
		}
	}

	for(int i=0;i < agenda->tamanho;i++){
		imprimecompromisso(&(agenda->compromisso[i]));
	}
}
int resolve_conflito(TAGENDA *agenda){
	bool conflito;
	for(int i=0; i < agenda->tamanho; i++){
		for(int j=i+1;j < agenda->tamanho;j++){
			conflito = temConflito(agenda->compromisso[i],agenda->compromisso[j]);
			if(conflito == true){/*1° priodidade 2°inicio 3°EVENTO REUNIAO AULA ORIENTACAO COMPROMISSO_PARTICULAR*/
				if(agenda->compromisso[i].prioridade > agenda->compromisso[j].prioridade){ 
					atribuiStatus(&(agenda->compromisso[j]),ADIAVEL);
				}
				else if(agenda->compromisso[i].prioridade < agenda->compromisso[j].prioridade){
					atribuiStatus(&(agenda->compromisso[i]),ADIAVEL);
					break; //se o i foi adiado ou cancelado não preciso comparar mais ele, já pulo para o i+1;
				}
				else if(agenda->compromisso[i].prioridade == agenda->compromisso[j].prioridade){
					if(agenda->compromisso[i].data.mes == agenda->compromisso[j].data.mes && 
					agenda->compromisso[i].data.dia == agenda->compromisso[j].data.dia &&
					agenda->compromisso[i].data.hora == agenda->compromisso[j].data.hora && 
					agenda->compromisso[i].data.minuto == agenda->compromisso[j].data.minuto){
						switch(agenda->compromisso[i].tipo){
							case EVENTO:
								atribuiStatus(&(agenda->compromisso[j]),ADIAVEL); //1 e 2 
								break;
							case REUNIAO:
								if(agenda->compromisso[j].tipo == EVENTO){
									atribuiStatus(&(agenda->compromisso[i]),ADIAVEL);
									break;
								}
								else{
									atribuiStatus(&(agenda->compromisso[j]),ADIAVEL);
									break;
								}
							case AULA:
								if(agenda->compromisso[j].tipo == EVENTO || agenda->compromisso[j].tipo == REUNIAO){
									atribuiStatus(&(agenda->compromisso[i]),ADIAVEL);
									break;
								}
								else{
									atribuiStatus(&(agenda->compromisso[j]),ADIAVEL);
									break;
								}
							case ORIENTACAO:
								if(agenda->compromisso[j].tipo == EVENTO || agenda->compromisso[j].tipo == REUNIAO){
									atribuiStatus(&(agenda->compromisso[i]),ADIAVEL);
									break;
								}
								else if(agenda->compromisso[j].tipo == AULA){
									atribuiStatus(&(agenda->compromisso[i]),ADIAVEL);
									break;
								}
								else{
									atribuiStatus(&(agenda->compromisso[j]),ADIAVEL);
									break;
								}
							case COMPROMISSO_PARTICULAR:
								if(agenda->compromisso[j].tipo == EVENTO || agenda->compromisso[j].tipo == REUNIAO){
									atribuiStatus(&(agenda->compromisso[i]),ADIAVEL);
									break;
								}
								else if(agenda->compromisso[j].tipo == AULA || agenda->compromisso[j].tipo == ORIENTACAO){
									atribuiStatus(&(agenda->compromisso[i]),ADIAVEL);
									break;
								}
								else{
									atribuiStatus(&(agenda->compromisso[j]),ADIAVEL);
									break;
								}
							default:
								printf("\tErro: Tipo Invalido");
								break; 
						}
					}
					else{
						ordena_agenda(agenda);
						atribuiStatus(&(agenda->compromisso[j]),ADIAVEL);
					}
				}
			}
		}
	}
}
int retorna_cancelamentos(TAGENDA* agenda) {
	int numero_de_compromissos = 0;
	for(int i=0;i < agenda->tamanho;i++){
		if(agenda->compromisso[i].status == CANCELADO){
		numero_de_compromissos++;
		}
	}
	return numero_de_compromissos;
}

int retorna_adiamentos(TAGENDA* agenda) { 
	int numero_de_compromissos = 0;
	for(int i=0;i < agenda->tamanho;i++){
		if(agenda->compromisso[i].status == ADIAVEL){
		numero_de_compromissos++;
		}
	}
	return numero_de_compromissos;
}
int retorna_compromissos(TAGENDA* agenda) { 
    int numero_de_compromissos = 0;
    for(int i=0;i < agenda->tamanho;i++){
        numero_de_compromissos++;
    }
    return numero_de_compromissos;
}
void imprime_compromissos_adiados(TAGENDA* agenda){ 
	for(int i=0;i < agenda->tamanho;i++){
		if(agenda->compromisso[i].status == ADIAVEL){
		imprimecompromisso(&(agenda->compromisso[i]));
		}
	}
}

void imprime_compromissos_cancelados(TAGENDA* agenda){
	for(int i=0;i < agenda->tamanho;i++){
		if(agenda->compromisso[i].status == CANCELADO){
		imprimecompromisso(&(agenda->compromisso[i]));
		}
	}
}

void imprime_compromissos_acumprir(TAGENDA* agenda){ 
	for(int i=0;i < agenda->tamanho;i++){
		if(agenda->compromisso[i].status == A_SER_CUMPRIDO){
		imprimecompromisso(&(agenda->compromisso[i]));
		}
	}
}
TAGENDA* ordena_agenda(TAGENDA *agenda){
	TCOMPROMISSO comp_indice;

	for(int i=0; i < agenda->tamanho; i++){
		for(int j=i+1;j < agenda->tamanho;j++){
			if(agenda->compromisso[i].data.mes > agenda->compromisso[j].data.mes){ //[0]30/1 30/2[1]  30/3[2]
			comp_indice = agenda->compromisso[i];
			agenda->compromisso[i] = agenda->compromisso[j];		
			agenda->compromisso[j] = comp_indice;			
			}
			else if(agenda->compromisso[i].data.mes == agenda->compromisso[j].data.mes){
				if(agenda->compromisso[i].data.dia > agenda->compromisso[j].data.dia){
					comp_indice =agenda->compromisso[i];
					agenda->compromisso[i] = agenda->compromisso[j];		
					agenda->compromisso[j] = comp_indice;	
				}
				else if(agenda->compromisso[i].data.dia == agenda->compromisso[j].data.dia){
					if(agenda->compromisso[i].data.hora > agenda->compromisso[i].data.hora){
						comp_indice =agenda->compromisso[i];
						agenda->compromisso[i] = agenda->compromisso[j];		
						agenda->compromisso[j] = comp_indice;
					}
					else if(agenda->compromisso[i].data.hora == agenda->compromisso[i].data.hora){
						if(agenda->compromisso[i].data.minuto > agenda->compromisso[i].data.minuto){
							comp_indice =agenda->compromisso[i];
							agenda->compromisso[i] = agenda->compromisso[j];		
							agenda->compromisso[j] = comp_indice;
						}
					}
				}
			}
		}
	}
	return agenda;
}
