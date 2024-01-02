#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include"compromisso.h"
#include"agenda.h"

int main(){
    TAGENDA agenda[P];
    char nome[M];
    int op,id_agenda, indice=-1;
    int duracao;
    int tamanho_agenda=0,id_compromisso;
    bool seleciona = false;
    int tipo;
    TDATA data;
        for(;;){
            printf(" ---Bem Vindo a agenda, digite o numero da acao a ser tomada---\n \n");
            printf("  1-Criar Agenda\n");
            printf("  2-Selecionar Agenda/Alternar Agenda\n");
            printf("  3-Inserir Compromisso\n");
            printf("  4-Altera Prioridade de um Compromisso\n");
            printf("  5-Atribuir Novo Status a um compromisso\n");
            printf("  6-Recuperar Agenda\n");
            printf("  7-Remover Compromisso\n");
            printf("  8-Numero de Adiados\n");
            printf("  9-Numero de Cancelados\n");
            printf("  10-Total de Compromissos\n");
            printf("  11-Imprime Cancelados\n");
            printf("  12-Imprime Adiados\n");
            printf("  13-Imprime a Cumprir\n");
            printf("  14-Imprime Agenda\n");
            printf("  15-Existem Conflitos?\n");
            printf("  16-Resolve Conflitos\n");
            printf("  0-Sair\n");
            scanf("%d", &op);
            if (op == 0 || op > 16 || op < 1){
                op != 0 ? printf("\tOpcao Incorreta!!") : printf("\tSAIR\n"); break;
            }
            else{
                if (op == 1){
                    printf("  Digite seu Nome:\n");
                    fscanf(stdin,"%s", nome);
                    printf("  Informe O Ano da Agenda:\n");
                    scanf("%d",&agenda[tamanho_agenda].ano);
                    cria_agenda(agenda+tamanho_agenda,tamanho_agenda+1,nome,agenda[tamanho_agenda].ano);
                    inicializa_compromisso(agenda[tamanho_agenda].compromisso);
                    tamanho_agenda++;
                }
                if(op == 2){
                    if(tamanho_agenda == 0){
                        printf("\tErro:Nenhuma Agenda Criada\n");
                    }
                    else{
                        printf("\tAgendas existentes:\n");
                        for(int i=0; i< tamanho_agenda ;i++){
                            printf("\tID:%d nome:%s ano:%d\n",agenda[i].id_agenda,agenda[i].nome_professor,agenda[i].ano);
                        }
                        printf("  Informe O ID Da Agenda Desejada:\n");
                        fflush(stdin);
                        scanf("%d",&id_agenda);
                        if(id_agenda >tamanho_agenda){
                            printf("\tErro: ID Incorreto\n"); 
                        }
                        else{
                            for(int i=0; i < tamanho_agenda; i++){
                                if(id_agenda == agenda[i].id_agenda){
                                indice=i;
                                }
                            }
                            seleciona = true;
                            printf("\tSucesso: Agenda selecionada.\n");
                        }
                    }
                }
                if(op == 3){
                    if(tamanho_agenda == 0){
                            printf("\tErro:Nenhuma Agenda Criada\n");
                        }
                    else if(tamanho_agenda != 0 && seleciona == false){
                        int aux;
                        printf("  Informe O ID Da Sua Agenda:\n");
                        fflush(stdin);
                        scanf("%d",&id_agenda);
                        for(int i=0; i < tamanho_agenda; i++){
                            if(id_agenda == agenda[i].id_agenda){
                                aux=i;
                            }
                            else{
                                seleciona = false;
                            }
                        }
                        if(aux != -1 && seleciona == false){
                            printf("  Digite O Nome Do Compromisso:\n");
                            fscanf(stdin,"%s", nome);
                            printf("  Informe O Tipo Do Compromisso: 1-ORIENTACAO 2-AULA 3-COMPROMISSO PARTICULAR 4-EVENTO 5-REUNIAO\n");
                            scanf("%d",&tipo);
                            for(;tipo > 5 || tipo < 1;){
                                printf("  Erro :Tipo Invalido\nDigite Novamente\n");
                                fflush(stdin);
                                scanf("%d",&tipo);
                            }
                            printf("  DATA:\n");
                            scanf("%d%d",&data.dia, &data.mes);
                            for(;(data.dia >30 || data.dia<1) ||(data.mes>12 || data.mes < 1);){
                                printf("  Erro:Data Invalida.\nDigite Novamente:\n");
                                fflush(stdin);
                                scanf("%d%d",&data.dia, &data.mes);
                            }
                            printf("  HORARIO:\n");
                            scanf("%d%d",&data.hora, &data.minuto);
                            for(;(data.hora>24 || data.hora<1)||(data.minuto>60 || data.minuto< 0);){
                                printf("  Erro:Horario Invalido.\nDigite Novamente\nHoras Validas:MAIORES QUE 1 E MENORES QUE 24\n");
                                fflush(stdin);
                                scanf("%d%d",&data.hora, &data.minuto);
                            }
                            printf("  Duracao Em Minutos:\n");
                            scanf("%d",&duracao);
                            if(duracao < 0){
                                duracao = duracao *(-1);
                            }

                            insere_compromisso(&agenda[aux],tipo,data,duracao,nome);
                        }
                        else{
                            for(int i=0; i< tamanho_agenda ;i++){
                                i= 0 ? printf("\tErro: ID Incorreto\nAgendas Existentes:\n"):0;
                                printf("ID:%d nome:%s ano:%d\n",agenda[i].id_agenda,agenda[i].nome_professor,agenda[i].ano);
                            }
                        }
                    }
                    else if(agenda[indice].id_agenda > 0 && agenda[indice].id_agenda < tamanho_agenda+1){
                        printf("\tAgenda De:%s Ano:%d ID:%d\n",agenda[indice].nome_professor, agenda[indice].ano, agenda[indice].id_agenda);
                        printf("  Digite O Nome Do Compromisso:\n");
                        fscanf(stdin,"%s", nome);
                        printf("  Informe O Tipo Do Compromisso: 1-ORIENTACAO 2-AULA 3-COMPROMISSO PARTICULAR 4-EVENTO 5-REUNIAO\n");
                        scanf("%d",&tipo);
                        for(;tipo > 5 || tipo < 1;){
                            printf("\tErro :Tipo Invalido\nDigite Novamente\n");
                            fflush(stdin);
                            scanf("%d",&tipo);
                        }
                        printf("  DATA:\n");
                        scanf("%d%d",&data.dia, &data.mes);
                        for(;(data.dia >30 || data.dia<1) ||(data.mes>12 || data.mes < 1);){
                            printf("\tErro:Data Invalida.\nDigite Novamente:\n");
                            fflush(stdin);
                            scanf("%d%d",&data.dia, &data.mes);
                        }
                        printf("  HORARIO:\n");
                        scanf("%d%d",&data.hora, &data.minuto);
                        for(;(data.hora>24 || data.hora<1)||(data.minuto>60 || data.minuto< 0);){
                            printf("  Erro:Horario Invalido.\nDigite Novamente\nHoras Validas:MAIORES QUE 1 E MENORES QUE 24\n");
                            fflush(stdin);
                            scanf("%d%d",&data.hora, &data.minuto);
                        }
                        printf("  Duracao Em Minutos:\n");
                        scanf("%d",&duracao);
                        if(duracao < 0){
                            duracao = duracao *(-1);
                        }

                        insere_compromisso(&agenda[indice],tipo,data,duracao,nome);
                    }
                }
                if(op == 4){
                    if(tamanho_agenda == 0){
                        printf("\tErro:Nenhuma Agenda Criada\n");
                    }
                    else if(indice == -1 && seleciona == false){
                        printf("\t***Selecione Uma Agenda***\n");
                    }
                    else{
                        printf("\tAgenda De:%s Ano:%d ID:%d\n",agenda[indice].nome_professor, agenda[indice].ano, agenda[indice].id_agenda);
                        printf("  Informe O ID Do Compromisso Para Alterar Sua Prioridade:\n");
                        scanf("%d",&id_compromisso);
                        for(int i=0 ;i<agenda->tamanho; i++){
                            if(agenda[indice].compromisso[i].identificador == id_compromisso){
                                altera_prioridade(&(agenda[indice].compromisso[i]),0);
                            }
                        }
                    }
                }
                if(op == 5){
                    if(tamanho_agenda == 0){
                        printf("\tErro:Nenhuma Agenda Criada\n");
                    }
                    else if(indice == -1 && seleciona == false){
                        printf("\t***Selecione Uma Agenda***\n");
                    }
                    else{
                        printf("\tAgenda De:%s Ano:%d ID:%d\n",agenda[indice].nome_professor, agenda[indice].ano, agenda[indice].id_agenda);
                        printf("  Informe O ID Do Compromisso Para Atribuir Um Novo Status:\n");
                        scanf("%d",&id_compromisso);
                        for(int i=0 ;i<agenda->tamanho; i++){
                            if(agenda[indice].compromisso[i].identificador == id_compromisso){
                                int novo_status;
                                printf("\tStatus Atual:%s\n",status_compromiso_string(agenda[indice].compromisso[i].status));
                                printf("  Para Alterar Digite Umas Destas Opcaos: 0-A_SER_CUMPRIDO  1-ADIADO  2-CANCELADO\n");
                                scanf("%d",&novo_status);
                                if(novo_status > 2 || novo_status < 0){
                                    printf("\tErro: Status Invalido\n");
                                }
                                else{
                                    atribuiStatus(&(agenda[indice].compromisso[i]),novo_status);
                                    printf("\tSucesso: Novo Status:%s\n",status_compromiso_string(agenda[indice].compromisso[i].status));
                                }
                            }
                        }
                    }
                }
                if(op == 6){
                    if(tamanho_agenda == 0){
                        printf("\tErro:Nenhuma Agenda Criada\n");
                    }
                    else if(indice == -1 && seleciona == false){
                        printf("\t***Selecione Uma Agenda***\n");
                    }
                    else if(tamanho_agenda != 0 && seleciona == true){
                        printf("\tAgenda De:%s Ano:%d ID:%d\n",agenda[indice].nome_professor, agenda[indice].ano, agenda[indice].id_agenda);
                        printf("  Digite Uma Data DIA/MES:\n");
                        scanf("%d%d",&data.dia,&data.mes);
                        for(;(data.dia >30 || data.dia<1) ||(data.mes>12 || data.mes < 1);){
                            printf("  Erro:Data Invalida.\nDigite Novamente:\n");
                            scanf("%d%d",&data.dia, &data.mes);
                        }
                        recuperaAgenda(&agenda[indice],data);
                    }
                }
                if(op == 7){
                    if(tamanho_agenda == 0){
                        printf("\tErro:Nenhuma Agenda Criada\n");
                    }
                    else if(indice == -1 && seleciona == false){
                        printf("\t***Selecione Uma Agenda***\n");
                    }
                    else if(tamanho_agenda != 0 && seleciona == true){
                        printf("\tAgenda De:%s Ano:%d ID:%d\n",agenda[indice].nome_professor, agenda[indice].ano, agenda[indice].id_agenda);
                        printf("  Informe O ID Do Compromisso A Ser Removido:");
                        scanf("%d",&id_compromisso);
                        remove_compromisso(id_compromisso,&agenda[indice]);
                    }
                }
                if(op == 8){
                    if(tamanho_agenda == 0){
                        printf("\tErro:Nenhuma Agenda Criada\n");
                    }
                    else if(indice == -1 && seleciona == false){
                        printf("\t***Selecione Uma Agenda***\n");
                    }
                    else if(tamanho_agenda != 0 && seleciona == true){
                        printf("\tAgenda De:%s Ano:%d ID:%d\n",agenda[indice].nome_professor, agenda[indice].ano, agenda[indice].id_agenda);
                        printf("Numero de compromissos adiados na agenda:%d \n",retorna_adiamentos(&agenda[indice]));
                    }
                }
                if(op==9){
                    if(tamanho_agenda == 0){
                        printf("\tErro:Nenhuma Agenda Criada\n");
                    }
                    else if(indice == -1 && seleciona == false){
                        printf("\t***Selecione Uma Agenda***\n");
                    }
                    else if(tamanho_agenda != 0 && seleciona == true){
                        printf("\tAgenda De:%s Ano:%d ID:%d\n",agenda[indice].nome_professor, agenda[indice].ano, agenda[indice].id_agenda);
                        printf("\tNumero de compromissos cancelados na agenda:%d \n",retorna_cancelamentos(&agenda[indice]));
                    }
                }
                if(op == 10){
                    if(tamanho_agenda == 0){
                        printf("\tErro:Nenhuma Agenda Criada\n");
                    }
                    else if(indice == -1 && seleciona == false){
                        printf("\t***Selecione Uma Agenda***\n");
                    }
                    else if(tamanho_agenda != 0 && seleciona == true){
                        printf("\tAgenda De:%s Ano:%d ID:%d\n",agenda[indice].nome_professor, agenda[indice].ano, agenda[indice].id_agenda);
                        printf("total de compromissos na agenda:%d \n",retorna_compromissos(&agenda[indice]));
                    }
                }
                if(op==11){
                    if(tamanho_agenda == 0){
                        printf("\tErro:Nenhuma Agenda Criada\n");
                    }
                    else if(indice == -1 && seleciona == false){
                        printf("\t***Selecione Uma Agenda***\n");
                    }
                    else if(tamanho_agenda == 0 && seleciona == true){
                        printf("\tAgenda De:%s Ano:%d ID:%d\n",agenda[indice].nome_professor, agenda[indice].ano, agenda[indice].id_agenda);
                        imprime_compromissos_cancelados(&agenda[indice]);
                    }
                }
                if(op==12){
                    if(tamanho_agenda == 0){
                        printf("\tErro:Nenhuma Agenda Criada\n");
                    }
                    else if(indice == 1 && seleciona == false){
                        printf("\t***Selecione Uma Agenda***\n");
                    }
                    else if(tamanho_agenda != 0 && seleciona == true){
                        printf("\tAgenda De:%s Ano:%d ID:%d\n",agenda[indice].nome_professor, agenda[indice].ano, agenda[indice].id_agenda);
                        imprime_compromissos_adiados(&agenda[indice]);
                    }
                }
                if(op==13){
                    if(tamanho_agenda == 0){
                        printf("\tErro:Nenhuma Agenda Criada\n");
                    }
                    else if(indice == -1 && seleciona == false){
                        printf("\t***Selecione Uma Agenda***\n");
                    }
                    else if(tamanho_agenda != 0 && seleciona == true){
                        printf("\tAgenda De:%s Ano:%d ID:%d\n",agenda[indice].nome_professor, agenda[indice].ano, agenda[indice].id_agenda);
                        imprime_compromissos_acumprir(&agenda[indice]);
                    }
                }
                if(op == 14){
                    if(tamanho_agenda == 0){
                        printf("\tErro:Nenhuma Agenda Criada\n");
                    }
                    else if(indice == -1 && seleciona == false){
                        printf("\t***Selecione Uma Agenda***\n");
                    }
                    else if(indice != -1 && seleciona == true){
                        printf("\tAgenda De:%s Ano:%d ID:%d\n",agenda[indice].nome_professor, agenda[indice].ano, agenda[indice].id_agenda);
                        imprime_agenda(&agenda[indice]);
                    }
                }
                if(op == 15){
                    if(tamanho_agenda == 0){
                        printf("\tErro:Nenhuma Agenda Criada\n");
                    }
                    else if(indice == -1 && seleciona == false){
                        printf("\t***Selecione Uma Agenda***\n");
                    }  
                    else{
                        int cout_conflitos=0;
                        bool conflitos;
                        printf("\tAgenda De:%s Ano:%d ID:%d\n",agenda[indice].nome_professor, agenda[indice].ano, agenda[indice].id_agenda);
                        for(int i=0; i<agenda[indice].tamanho ;i++){
                            for(int j=i+1; j<agenda[indice].tamanho; j++){
                              if(temConflito(agenda[indice].compromisso[i],agenda[indice].compromisso[j]) == 1){
                                cout_conflitos++;
                              }  
                            }
                        }
                        cout_conflitos > 0 ? printf("\tNumero de Conflitos Encontrados: %d\n",cout_conflitos):printf("\tSem Conflitos\n");
                    } 
                }
                if(op == 16){
                    if(tamanho_agenda == 0){
                        printf("\tErro:Nenhuma Agenda Criada\n");
                    }
                    else if(indice == -1 && seleciona == false){
                        printf("\t***Selecione Uma Agenda***\n");
                    }
                    else if(tamanho_agenda != 0 && seleciona == true){
                        printf("\tAgenda De:%s Ano:%d ID:%d\n",agenda[indice].nome_professor, agenda[indice].ano, agenda[indice].id_agenda);
                        resolve_conflito(&agenda[indice]);
                        printf("\tSucesso: Conflitos Resolvidos:\n");   
                    }
                }
            }
        }
    }
