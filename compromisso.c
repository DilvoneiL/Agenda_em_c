#include "compromisso.h"

int inicializa_compromisso(TCOMPROMISSO* comp) {
	
	comp->status = A_SER_CUMPRIDO; //todo compromisso incializa com a ser cumprido
	comp->adiavel = false;         //adiavel sempre incializa com false
	comp->identificador = 0; 
	return comp->identificador;
} 

int altera_prioridade(TCOMPROMISSO* comp, int novaPri) {
	printf("\tPrioridade Atual do compromisso:%d \n",retorna_prioridade(*comp));
	printf("  Digite Uma Prioridade:\n");
	scanf("%d", &novaPri);
	if (novaPri < 1 || novaPri > 5) {
		printf("\tErro:Prioridade Inexistente\n");
		return 0;
	} else {
		comp->prioridade = novaPri;
		printf("\tSucesso: Prioridade Alterada Para:%d\n",comp->prioridade);
		return 1;
	}
}
	
int retorna_prioridade(TCOMPROMISSO comp) {  
	return comp.prioridade;
}

bool Eadiavel(TCOMPROMISSO* c, bool adiavel) { 
	if (c->tipo == AULA || c->tipo == EVENTO) {  
		c->adiavel = false;// ser for aula ou evento não podera ser adiado, outros compromisso podem ser adiados.
		return c->adiavel;
	} else {
		c->adiavel = adiavel; 	//bool recebe true pois o compromisso é adiavel;
		return c->adiavel;
	}
}

bool temConflito(TCOMPROMISSO comp1, TCOMPROMISSO comp2) { //prints devem ser substituido por uma variavel bool 0/1 talvez 
	int *comp1_duracao = malloc(sizeof(int)*4); //mes=0,dia=1,hora=2,minuto=3;
	int *comp2_duracao = malloc(sizeof(int)*4);
	comp1_duracao = calcula_duracao_final(comp1.duracao,comp1.data); 
	comp2_duracao = calcula_duracao_final(comp2.duracao,comp2.data);
	bool conflito=0;
	if(comp1.data.mes == comp2.data.mes || comp2.data.mes == comp1.data.mes){ // verfifica mes igual
		if(comp2.data.dia==comp1.data.dia || comp2.data.dia==comp1.data.dia){  //dia igual
			if((comp2.data.hora >= comp1.data.hora && comp2.data.hora < comp1_duracao[2]) || //entre as horas
			(comp1.data.hora >= comp2.data.hora && comp1.data.hora < comp2_duracao[2])){
				printf(" Resolve aqui\n");
				return conflito = true; //existe conflito
			
			}
			//horas iguais e minutos diferentes
			else if((comp1.data.hora == comp2.data.hora || comp1_duracao[2] == comp2.data.hora)||
			(comp2_duracao[2] == comp1.data.hora)){
				if((comp2.data.minuto>=comp1.data.minuto && comp2.data.minuto <= comp1_duracao[3]) || 
				(comp1.data.minuto>=comp2.data.minuto && comp1.data.minuto <=comp2_duracao[3])){
					return conflito = true;
				}
				else{
					return conflito = false;
				}

			}
			else{
				return conflito = false; //não tem conflito
			} 	
		}
		else{
			if(comp2.tipo == EVENTO || comp1.tipo == EVENTO){ //evento no mesmo mes
				if((comp2.data.dia>comp1.data.dia && comp2.data.dia<=comp1_duracao[1])|| //dia entre os dias do evento
				(comp2_duracao[1]>=comp1.data.dia && comp1.data.dia>comp2.data.dia)){
					if((comp2.data.hora > comp1.data.hora && comp2.data.hora < comp1_duracao[2])  //hora entre
					|| (comp1.data.hora > comp2.data.hora && comp1.data.hora < comp2_duracao[2])){
						return conflito=true;
					}
					else if((comp1.data.hora == comp2.data.hora || comp1_duracao[2] == comp2.data.hora)|| //mesma hora e minutos diferentes
					(comp2.data.hora == comp1.data.hora || comp2_duracao[2] == comp1.data.hora)){
						if((comp2.data.minuto>=comp1.data.minuto && comp2.data.minuto <= comp1_duracao[3]) ||
						(comp1.data.minuto>=comp2.data.minuto && comp1.data.minuto <= comp2_duracao[3])){
							return conflito = true;
						}
					}	
					else{
						return conflito = false;
					}
				}
				else {
					return conflito = false;
				}
			}
			else{
				return conflito = false;
			}
		}
	}
	else if(comp2.tipo == EVENTO || comp1.tipo == EVENTO){
		if(comp1_duracao[0]==comp2.data.mes || comp2_duracao[0]==comp1.data.mes){ //para eventos com virada de mes dia começa dia 30 e termina dia 1 do outro mes
			if(comp2.data.dia < comp1_duracao[1] || comp1.data.dia<comp2_duracao[1]){ // se o dia do outro compromisso é menor que o final do evento
				return conflito = true;
			}
			else if(comp2.data.dia == comp1_duracao[1] || comp1.data.dia == comp2_duracao[1]){ // se acaba no mesmo dia, diferença na hora
				if((comp2.data.hora > comp1.data.hora && comp2.data.hora < comp1_duracao[2]) ||
				(comp1.data.hora >= comp2.data.hora && comp1.data.hora < comp2_duracao[2])){
						return conflito=true;
				}
				else if((comp1.data.hora == comp2.data.hora || comp1_duracao[2] == comp2.data.hora)|| // se acaba na mesma hora diferença nos minutos
				(comp2.data.hora == comp1.data.hora || comp2_duracao[2] == comp1.data.hora)){
					if((comp2.data.minuto>comp1.data.minuto && comp2.data.minuto < comp1_duracao[3]) ||
					(comp1.data.minuto>comp2.data.minuto && comp1.data.minuto < comp2_duracao[3])){
						return conflito = true;
					}
				}	
				else{
					return conflito = false;
				}
			}
			else {
				return conflito = false; //não tem conflito
			}
		}
		else{
			return conflito = false;
		}
	}
	else{
		return conflito = false; //não tem conflito
	}

	free(comp1_duracao);
	free(comp2_duracao);
}

int atribuiStatus(TCOMPROMISSO* comp,status_compromiso status) { 
	Eadiavel(comp,true);
	if(status == ADIAVEL){
		if (comp->adiavel == true) {
			comp->status = status;
			return 1;
		} else { //quando não é adiavel o compromisso é cancelado
			comp->status = CANCELADO;
			return 0;
		}
	}
	else{
		comp->status = status;
		return 1;
	}
}

int retornaStatus(TCOMPROMISSO comp) {	 
	return comp.status;
}

void imprimecompromisso(TCOMPROMISSO *comp){ //imprime as informações do compromisso
	printf("\tID Do Compromisso: %d \n", comp->identificador);
    printf("\tTipo: %s \n", tipo_de_compromisso_string(comp->tipo));
    printf("\tData : %d / %d \n", comp->data.dia,comp->data.mes); //comp[x]->(vetor de struc).data(struc).dia(variavel).
	printf("\tHorario:  %d:%d\n", comp->data.hora,comp->data.minuto);
	
	int* Duracao = malloc(sizeof(int) * 3);
	converte_dia_hora_minuto(comp->duracao, Duracao);
	printf("\tDuracao = Dias:%d / Horas: %d e %d Minutos\n", Duracao[0], Duracao[1], Duracao[2]);
	printf("\tNome do Compromisso: %s\n",comp->nome_do_compromisso);  

	if(Eadiavel(comp,true)==false){
		printf("\tNao Pode Ser Adiado\n" );
	}
	else{
		printf("\tCompromisso Adiavel\n");
	}

	printf("\t%s\n\n",status_compromiso_string(comp->status));

	free(Duracao);
}
	
char * tipo_de_compromisso_string(tipo_de_compromisso t){ 
	switch(t){
		case ORIENTACAO:return "ORIENTACAO";
		case AULA:return "AULA";
		case COMPROMISSO_PARTICULAR:return "COMPROMISSO PARTICULAR";
		case EVENTO:return "EVENTO";
		case REUNIAO:return "REUNIAO";
		default: return "TIPO INVALIDO";

	}
}
char * status_compromiso_string(status_compromiso s){ 
	switch(s){
		case A_SER_CUMPRIDO:return "A_SER_CUMPRIDO";
		case ADIAVEL:return "ADIADO";
		case CANCELADO:return "CANCELADO";
		default: return "TIPO INVALIDO";

	}
}
int* calcula_duracao_final( int duracao_minutos,TDATA inicial) { //[0]=dia;[1]=hora;[2]=minuto duracao //ok
	int *duracao = malloc(sizeof(int)*3);
	converte_dia_hora_minuto(duracao_minutos,duracao);
	int *duracaofinal = malloc(sizeof(int)*4);//mes[0],dia[1],hora[2],minuto[3]	duracaofinal
	duracaofinal[3]=duracao[2]+inicial.minuto;
	duracaofinal[2]=duracao[1]+inicial.hora;
	duracaofinal[1]=duracao[0]+inicial.dia;
	duracaofinal[0]=inicial.mes;
	for(;duracaofinal[3]>=60;){ //80=20		//soma dos minutos maior que 60
		duracaofinal[2]+=1;		
		duracaofinal[3] -= 60;
	}
	for(;duracaofinal[2]>24;){ 		//se as horas são  maiores que 24, soma 1 no dia, e a hora recebe 1.
		duracaofinal[1] += 1; 				//hora final recebe 1 pois é maior que 24
		duracaofinal[2]-=24;
	}
	for(;duracaofinal[1] > 30;){
		duracaofinal[0]+=1;
		duracaofinal[1]-=30;	
	}
	free(duracao);
	return duracaofinal;
}

void converte_dia_hora_minuto(unsigned int duracao, int* duracao_dia_hora_minuto) {
	duracao_dia_hora_minuto[0] = duracao / 1440;//dia
	duracao = (duracao - (1440 * duracao_dia_hora_minuto[0]));
	duracao_dia_hora_minuto[1] = duracao / 60;//hora
	duracao_dia_hora_minuto[2] = duracao % 60;//minuto
}
