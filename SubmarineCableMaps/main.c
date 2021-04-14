#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Trabalho_INF006.h"
//Interface com o Usuário.
int main(){
    inf_cab dados_no_main;
    Lista* li = cria_lista();
    carrregarArquivoLista(li);
    remove_lista_duplicados(li);
    int qtd_cidades_por_regiao;

    int opcao;
    int tamanho;
    int nomeCabo;
    int consulta;
    int remove;

    do{
        printf("\n ============== MENUS ==============\n\n");
        printf("\n 1- Numero total de cidades/cabos\n\n");
        printf("\n 2- Buscar cidades/cabos na lista\n\n");
        printf("\n 3- Criar regioes\n\n");
        printf("\n 4- Remover uma cidade/cabo especifico da lista\n\n");
        printf("\n 5- Imprimir cidades/cabos da lista\n\n");
        printf("\n 6- Inserir uma nova cidade/cabo na lista\n\n");
        printf("\n 7- Obter peso medio da regiao\n\n");
        printf("\n 8- Obter GC medio da regiao\n\n");
        printf("\n 0- SAIR\n\n");
        printf("\nEscolha uma das opcoes do MENU: ");
        scanf("%d", &opcao);
        printf("\n====================================\n\n");

        switch(opcao){
            case 1:
                tamanho = tamanho_lista(li);
                printf("\nNumero total de cidades/cabos = %d\n\n", tamanho);
                
            break;
            case 2:
                printf("\nDigite o nome da cidade/cabo a ser consultado na lista: ");
                scanf("%d", &nomeCabo);
                consulta = busca_na_lista(li, nomeCabo, &dados_no_main);
                if(consulta == 1){
                    printf("\n ===  Informacoes da cidade/cabo CONSULTADO ===\n\n");
                    printf("\tNome da cidade/cabo = %d\n",nomeCabo);
                    printf("\tTamanho do cabo = %.2f\n", dados_no_main.Tamanho);
                    printf("\tPeso do cabo/cidade = %d\n", dados_no_main.Peso);
                    printf("\tGrau de conectividade do cabo/cidade = %d\n", dados_no_main.GC);
                    printf("\tRegiao do cabo/cidade = %d\n", dados_no_main.Regiao);
                    printf("===================================================\n\n");
                    
                }
                else{
                    printf("\nCabo/cidade nao encontrada na lista!\n");
                    
                }
            break;
            case 3:;
                int qtd_regioes;
                printf("\nInforme a quantidade de regioes (deve ser um numero divisor de 500 (Ex.: 5, 10, 20, 25, 50, 100, etc), maior que 1 e menor que %d): ", tamanho_lista(li));
                scanf("%d", &qtd_regioes);
                if(qtd_regioes == 0){
                    printf("\nA quantidade de regioes informada foi igual a zero! Crie pelo menos uma regiao! Volte para a opcao 3 do menu!\n\n");
                    
                    break;
                }else if(qtd_regioes > tamanho_lista(li)){
                    printf("\nA quantidade de regioes informada eh superior ao numero de cidades/cabos (%d)! Volte para a opcao 3 do menu!\n\n", tamanho_lista(li));
                    
                    break;
                }else if(500 % qtd_regioes != 0){
                    printf("\nA quantidade de regioes informada nao eh um divisor de 500! Volte para a opcao 3 do menu!\n\n");
                    
                    break;
                }else{
                    qtd_cidades_por_regiao = tamanho_lista(li)/qtd_regioes;//O valor da constante CIDADES do c�digo "GeradorMassaDados.c" (500) dividido por 25 (qtd de regioes) resultar� em uma divis�o exata.
                    int regioes_Geradas;
                    regioes_Geradas = gerar_regioes(li, qtd_cidades_por_regiao, qtd_regioes);
                    if(regioes_Geradas == 1){
                        printf("\nRegioes criadas com sucesso!!\n");
                        
                    }else{
                        printf("\nFalha na criacao das regioes!!\n");
                        
                    }
                }
            break;
            case 4:
                printf("\nDigite o nome da cidade/cabo a ser removido da lista: ");
                scanf("%d", &nomeCabo);
                remove = remove_lista(li, nomeCabo, &dados_no_main);
                if (remove == 1){
                    printf("\nCidade/cabo removido com sucesso!\n");
                    printf("\n ===  Informacoes da cidade/cabo REMOVIDO  ===\n\n");
                    printf("\tNome da cidade/cabo = %d\n",nomeCabo);
                    printf("\tTamanho do cabo = %.2f\n", dados_no_main.Tamanho);
                    printf("\tPeso da cidade/cabo = %d\n", dados_no_main.Peso);
                    printf("\tGrau de conectividade da cidade/cabo = %d\n", dados_no_main.GC);
                    printf("\tRegiao da cidade/cabo = %d\n", dados_no_main.Regiao);
                    
                }
                else{
                    printf("\nNao existe a cidade/cabo informado!");
                    
                }
            break;
            case 5:
                imprime_lista(li);
                
            break;
            case 6:
                printf("\nInforme a regiao do novo cabo (de 1 a %d): ", qtd_regioes);
                scanf("%d", &dados_no_main.Regiao);
                printf("\nDigite o nome do novo cabo/cidade: ");
                scanf("%d", &dados_no_main.Nome);
                printf("\nDigite o comprimento do novo cabo/cidade: ");
                scanf("%f", &dados_no_main.Tamanho);
                printf("\nDigite o GC do novo cabo/cidade: ");
                scanf("%d", &dados_no_main.GC);
                switch(dados_no_main.GC){
                    case 1 ... 5:
                        dados_no_main.Peso = dados_no_main.GC * 15;
                    break;
                    case 6 ... 10:
                        dados_no_main.Peso = dados_no_main.GC * 25;
                    break;
                    case 11 ... 20:
                        dados_no_main.Peso = dados_no_main.GC * 45;
                    break;
                    default:
                        dados_no_main.Peso = dados_no_main.GC * 60;
                    break;
                }

                int insere = insere_novo_elemento_ordenado(li, dados_no_main);
                if (insere == 1){
                    printf("\nCidade/cabo inserido com sucesso!\n");
                    
                }else if(insere == 2){
                    printf("\nA cidade/cabo informado ja existe!\n");
                    
                }else if(insere == 3){
                    printf("\nA regiao informada para o cabo/cidade nao existe!\n");
                   
                }else if(insere == 4){
                    printf("\nO usuario ainda nao criou nenhuma regiao! Va ao item '3- Criar regioes' do menu para efetuar a operacao.\n");
                    
                }
                else{
                    printf("\nN�o foi possivel inserir o novo cabo/cidade!\n");
                    
                }
            break;
            case 7:;
                int regiao;
                float peso_medio;
                printf("\nInforme a regiao da qual deseja obter o peso medio (de 1 a %d): ", qtd_regioes);
                scanf("%d", &regiao);
                peso_medio = peso_medio_regiao(li, regiao);
                if(peso_medio == 0){
                    printf("\nRegiao no localizada\n!");
                    
                }else{
                    printf("\nO peso medio da regiao %d eh %.2f\n", regiao, peso_medio);
                    
                }
            break;
            case 8:;
                float GC_medio;
                printf("\nInforme a regiao da qual deseja obter o GC medio(de 1 a %d): ", qtd_regioes);
                scanf("%d", &regiao);
                GC_medio = GC_medio_regiao(li, regiao);
                if(GC_medio == 0){
                    printf("\nRegiao no localizada\n!");
                    
                }else{
                    printf("\nO GC medio da regiao %d eh %.2f\n", regiao, GC_medio);
                    
                }
            break;
            case 0:
                liberar_a_memoria(li);
                printf("\nO programa foi finalizado! Aperte ENTER para fechar a janela!\n\n");
            break;
            default:
            printf("\nOPCAO INVALIDA!\n");
            
        }
    }while(opcao != 0);

    return 0;
}
