#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Trabalho_INF006.h"

struct elemento{
    inf_cab dados;
    struct elemento *prox;
};

Lista* cria_lista(){
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

Lista* carrregarArquivoLista(Lista* li){
    char *result; //Guardará os dados do arquivo txt antes da separação dos mesmos em razão do ";".
    char *token; //Guardará os dados do arquivo txt após da separação dos mesmos em razão do ";".
    char linha[50]; //Guardará cada linha do arquivo txt.
    inf_cab InformacoesCabos; //Struct que guardará os dados extraídos dos arquivos txt, mas convertidos em int e float.
    InformacoesCabos.Nome = 0;
    InformacoesCabos.Tamanho = 0;
    InformacoesCabos.Peso = 0;
    InformacoesCabos.GC = 0;
    FILE *arq;//Abrindo o arquivo txt.
    if((arq = fopen("maDados.txt", "rt")) == NULL){
        printf("Erro ao abrir o arquivo.\n");
    }
    //int i = 0; //Variável incrementadora do vetor principal.
    while (!feof(arq)){
        result = fgets(linha, sizeof(linha), arq); //Capturando os dados do arquivo txt sem a separação pelo ";".
        if (result){
            token = strtok(result, " ;"); //Separando os dados pelo ";".
        }
        int j = 0; //Variável incrementadora do vetor/ponteiro "token".
        //Guardará os dados em formato char
        char Nome[6];
        char Tamanho[15];
        char Peso[6];
        char GC[6];
        while( token != NULL ){//Gravação na struct de char e , depois, na struct de int e float.
            switch(j){
                case 0:
                    InformacoesCabos.Nome = atoi(strcpy(Nome, token));
                    //printf("Nome = %d\n", InformacoesCabos.Nome);
                break;
                case 1:
                    InformacoesCabos.Tamanho = atof(strcpy(Tamanho, token));
                    //printf("Tamanho = %f\n", InformacoesCabos.Tamanho);
                break;
                case 2:
                    InformacoesCabos.Peso = atoi(strcpy(Peso, token));
                    //printf("Peso = %d\n", InformacoesCabos.Peso);
                break;
                case 3:
                    InformacoesCabos.GC = atoi(strcpy(GC, token));
                    //printf("GC = %d\n", InformacoesCabos.GC);
                break;
            }
            token = strtok(NULL, " ;");
            j++;
        }
        insere_lista_ordenada(li, InformacoesCabos);
    }
    fclose(arq);
    return li;
}

int gerar_regioes(Lista* li, int qtd_cidades_por_regiao, int qtd_regioes){
    int contador = 0, k = 1, k2 = 1;
    Elem *no = *li;
    Elem *no2 = *li;
    while(no != NULL){
        if(k <= qtd_regioes){
            no->dados.Regiao = k;
            no = no->prox;
            contador = contador + 1;
            if(contador == qtd_cidades_por_regiao){
                k = k + 1;
                contador = 0;
            }
        }else if(k > qtd_regioes){
            while(no != NULL){
                if(k2 < qtd_regioes){
                    no->dados.Regiao = k2;
                    no = no->prox;
                    k2 = k2 + 1;
                }else if(k2 == qtd_regioes){
                    no->dados.Regiao = k2;
                    no = no->prox;
                }
            }
        }
    }
    if(no != NULL)
        return 0;
    else{
        return 1;
    }
}

int insere_lista_ordenada(Lista* li, inf_cab InformacoesCabos){
    if(li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = InformacoesCabos;
    no->dados.Regiao = 0;
    if(li == NULL){//lista vazia: insere início
        no->prox = NULL;
        li = &no;
        return 1;
    }
    else{
        Elem *ant, *atual = *li;
        while(atual != NULL && atual->dados.Nome <= InformacoesCabos.Nome){
            ant = atual;
            atual = atual->prox;
        }
        if(atual == *li){//insere início
            no->prox = (*li);
            *li = no;
        }else{
            no->prox = atual;
            ant->prox = no;
        }
        return 1;
    }
}

int insere_novo_elemento_ordenado(Lista* li, inf_cab dados_no_main){
    if(li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;

    int caboBuscado = dados_no_main.Nome;
    int resultadoCaboBuscado = busca_cabo_existente(li, caboBuscado);
    if(resultadoCaboBuscado == 1){
        return 2;
    }

    int existeRegiao = dados_no_main.Regiao;
    int resultadoExisteRegiao = busca_regiao_existente(li, existeRegiao);
    if(resultadoExisteRegiao == 0){
        return 3;
    }else if(resultadoExisteRegiao == 2){
        return 4;
    }

    no->dados.Nome = dados_no_main.Nome;
    no->dados.Tamanho = dados_no_main.Tamanho;
    no->dados.Peso = dados_no_main.Peso;
    no->dados.GC = dados_no_main.GC;
    no->dados.Regiao = dados_no_main.Regiao;

    if(li == NULL){//lista vazia: insere início
        no->prox = NULL;
        li = &no;
        return 1;
    }
    else{
        Elem *ant, *atual = *li;
        while(atual != NULL && atual->dados.Nome <= dados_no_main.Nome){
            ant = atual;
            atual = atual->prox;
        }
        if(atual == *li){//insere início
            no->prox = (*li);
            *li = no;
        }else{
            no->prox = atual;
            ant->prox = no;
        }
        return 1;
    }
}

int busca_cabo_existente(Lista* li, int caboBuscado){
    Elem *no = *li;
    while(no != NULL && no->dados.Nome != caboBuscado){
        no = no->prox;
    }
    if(no == NULL){
        return 0;
    }else{
        return 1;
    }
}

int busca_regiao_existente(Lista* li, int existeRegiao){
    Elem *no = *li;
    while(no != NULL && no->dados.Regiao != existeRegiao){
        no = no->prox;
    }
    if((*li)->dados.Regiao == 0){
        return 2;
    }else if(no == NULL){
        return 0;
    }else{
        return 1;
    }
}

int busca_na_lista(Lista* li, int nomeCabo, inf_cab *dados_no_main){
    if(li == NULL)
        return 0;
    Elem *no = *li;
    while(no != NULL && no->dados.Nome != nomeCabo){
        no = no->prox;
    }
    if(no == NULL)
        return 0;
    else{
        *dados_no_main = no->dados;
        return 1;
    }
}

float peso_medio_regiao(Lista* li, int regiao){
    if(li == NULL)
        return 0;
    Elem *no = *li;
    float total_peso_regiao = 0, ocorrencia_cabo_regiao = 0, media_peso;
    while(no != NULL){
        if(regiao == no->dados.Regiao){
            total_peso_regiao = total_peso_regiao + no->dados.Peso;
            ocorrencia_cabo_regiao = ocorrencia_cabo_regiao + 1;
        }
        no = no->prox;
    }
    media_peso = total_peso_regiao/ocorrencia_cabo_regiao;
    if(ocorrencia_cabo_regiao == 0)
        return 0;
    else{
        return media_peso;
    }
}

float GC_medio_regiao(Lista* li, int regiao){
    if(li == NULL)
        return 0;
    Elem *no = *li;
    float total_GC_regiao = 0, ocorrencia_cabo_regiao = 0, media_GC;
    while(no != NULL){
        if(regiao == no->dados.Regiao){
            total_GC_regiao = total_GC_regiao + no->dados.GC;
            ocorrencia_cabo_regiao = ocorrencia_cabo_regiao + 1;
        }
        no = no->prox;
    }
    media_GC = total_GC_regiao/ocorrencia_cabo_regiao;
    if(ocorrencia_cabo_regiao == 0)
        return 0;
    else{
        return media_GC;
    }
}

int remove_lista(Lista* li, int removeCabo, inf_cab *dados_no_main){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;
    Elem *ant, *no = *li;
    while(no != NULL && no->dados.Nome != removeCabo){
        ant = no;
        no = no->prox;
    }
    if(no == NULL)//não encontrado
        return 0;

    if(no == *li){//remover o primeiro?
        *li = no->prox;
        *dados_no_main = no->dados;
    }else{
        ant->prox = no->prox;
        *dados_no_main = no->dados;
    }
    free(no);
    return 1;
}

Lista* remove_lista_duplicados(Lista* li){
    Elem *anterior, *atual, *seguinte;
    for(atual = *li; atual != NULL; atual = atual->prox){
        anterior = NULL;
        for(seguinte = atual->prox; seguinte != NULL; ){
            if(atual->dados.Nome == seguinte->dados.Nome){
                if(anterior == NULL){
                    atual->prox = seguinte->prox;
                }else{
                    anterior->prox = seguinte->prox;
                }
                Elem *remover = seguinte;
                seguinte = seguinte->prox;
                free(remover);
            }else{
                anterior = seguinte;
                seguinte = seguinte->prox;
            }
        }
    }
    return li;
}

int tamanho_lista(Lista* li){
    if(li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

void imprime_lista(Lista* li){
    if(li == NULL)
        return;
    Elem* no = *li;
    while(no != NULL){
        printf("%d ; %.2f ; %d ; %d ; %d\n", no->dados.Nome, no->dados.Tamanho, no->dados.Peso, no->dados.GC, no->dados.Regiao);
        no = no->prox;
        //system("pause");
    }
}

void liberar_a_memoria(Lista *li){
     if(li != NULL ){
     Elem *no;
     while( (*li) != NULL ){
           no = *li;
           *li = (*li)->prox;
           free(no);
       }
       free(li);
    }
}

