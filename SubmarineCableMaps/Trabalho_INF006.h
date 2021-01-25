

typedef struct InfCab{//Guardará os dados em formato int e float
    int Nome;
    float Tamanho;
    int Peso;
    int GC;
    int Regiao;
}inf_cab;
typedef struct elemento Elem;
typedef struct elemento* Lista;

Lista* cria_lista();
int gerar_regioes(Lista* li, int qtd_cidades_por_regiao, int qtd_regioes);
int insere_lista_ordenada(Lista* li, inf_cab InformacoesCabos);
int insere_novo_elemento_ordenado(Lista* li, inf_cab dados_no_main);
int busca_cabo_existente(Lista* li, int caboBuscado);
int busca_regiao_existente(Lista* li, int existeRegiao);
int busca_na_lista(Lista* li, int nomeCabo, inf_cab *dados_no_main);
float peso_medio_regiao(Lista* li, int regiao);
float GC_medio_regiao(Lista* li, int regiao);
int remove_lista(Lista* li, int removeCabo, inf_cab *dados_no_main);
Lista* remove_lista_duplicados(Lista* li);
int tamanho_lista(Lista* li);
void imprime_lista(Lista* li);
Lista* carrregarArquivoLista(Lista* li);
void liberar_a_memoria(Lista *li);



