//FELIPE DO QUENTAL ANUNCIA��O 2018013960
//LAB 10 ECOP12


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX 15
#define TAM 30

typedef enum{false, true} bool;

typedef struct no{
char nome[30];
int matricula;
int fatBal;
struct no* esq;
struct no* dir;
}noAluno;

int i=0;

void rotacionarEsq(noAluno **no){
    noAluno *atual;
    atual = (*no)->dir;
    (*no)->dir = atual->esq;
    atual->esq = (*no);
    (*no)=atual;
    (*no)->fatBal = 0;
}

void rotacionarDir(noAluno **no){
    noAluno *atual;
    atual = (*no)->esq;
    (*no)->esq = atual->dir;
    atual->dir = (*no);
    (*no)=atual;
    (*no)->fatBal = 0;
}

noAluno* buscarMatricula(noAluno* raiz, int mat){
    int quant=1;
    noAluno *aux=raiz;
    while(aux!=NULL && mat!=aux->matricula){
        if(mat<aux->matricula){
            aux=aux->esq;
            quant++;
      }else{
            aux=aux->dir;
            quant++;
    }
  }
  printf("\n%d\n",quant);
  return aux;
}

int altura(noAluno* atual){
    int d=0,e=0;
    if(!atual) return 0;
    if(!atual->esq && !atual->dir) return 0;
    if(atual->esq) d = 1+altura(atual->esq);
    if(atual->dir) e = 1+altura(atual->dir);
    if(e>d) return e;
    else return d;
}

int fatorBalanceamento(noAluno* atual){
    int lh,rh;
    if(atual == NULL)
        return(0);
    if(atual->esq == NULL)
        lh = 0;
    else
        lh = 1 + altura(atual->esq);
    if(atual->dir == NULL)
        rh = 0;
    else
        rh = 1 + altura(atual->dir);
    return (rh - lh);
}

void inserirNoArvoreAVL(noAluno** noAtual , noAluno* novoNoAluno){
    if(*noAtual == NULL){
        *noAtual = novoNoAluno;
    }else{
        if(novoNoAluno->matricula < (*noAtual)->matricula){
            inserirNoArvoreAVL(&(*noAtual)->esq, novoNoAluno);
            if(fatorBalanceamento(*noAtual) == -2){
                if(novoNoAluno->matricula < (*noAtual)->esq->matricula){
                    rotacionarDir(noAtual);
                }else{
                    rotacionarEsq(&(*noAtual)->esq);
                    rotacionarDir(noAtual);
                }
            }
        }else{
            inserirNoArvoreAVL(&(*noAtual)->dir, novoNoAluno);
            if(fatorBalanceamento(*noAtual) == 2){
                if(novoNoAluno->matricula > (*noAtual)->dir->matricula){
                    rotacionarEsq(noAtual);
                }else{
                    rotacionarDir(&(*noAtual)->dir);
                    rotacionarEsq(noAtual);
                }
            }
        }
    }
    (*noAtual)->fatBal = fatorBalanceamento(*noAtual);
}

void inserirNoArvoreBinaria(noAluno** noAtual , noAluno* novoNoAluno){
    if(*noAtual == NULL){
        *noAtual = novoNoAluno;
    }else{
        if(novoNoAluno->matricula < (*noAtual)->matricula){
            inserirNoArvoreBinaria(&(*noAtual)->esq, novoNoAluno);
        }else{
            inserirNoArvoreBinaria(&(*noAtual)->dir, novoNoAluno);
        }
    }
}

void imprimeNoAluno(noAluno* no){
    printf("> Nome: %s\n", no->nome);
    printf("> Matricula: %d\n\n", no->matricula);
}

void destroi(noAluno* atual){
    if (atual != NULL){
        destroi(atual->esq);
        destroi(atual->dir);
        free(atual);
    }
}

void em_ordem(noAluno *no){
    if(no!=NULL){
        em_ordem(no->esq);
        imprimeNoAluno(no);
        printf("\n");
        em_ordem(no->dir);
    }
}

void mostra(noAluno *atual, int n){
    if(atual!=NULL){
        int i;
        mostra(atual->dir, n+1);
        for(i = 0; i < n; i++)
            printf("    ");
        printf("%d\n", atual->matricula);
        mostra(atual->esq, n+1);
    }
}

void mostraFatBal(noAluno *atual, int n){
    if(atual!=NULL){
        int i;
        mostraFatBal(atual->dir, n+1);
        for(i = 0; i < n; i++)
            printf("    ");
        printf("%d", atual->matricula);
        printf(" %d\n", atual->fatBal);
        mostraFatBal(atual->esq, n+1);
    }
}

void imprimeArvores(noAluno *arvAVL, noAluno *arvBinaria){
    printf("\n\nAVL  (deitada):");
    printf("(VERDE EH O FATOR DE BALANCEAMENTO)\n");
    printf("------------------------------------------\n");
    mostraFatBal(arvAVL, 0);

    printf("\n\nBINARIA  (deitada):\n");
    printf("------------------------------------------\n");
    mostra(arvBinaria, 0);
}

int main(int argc, char **argv){
    char opcao = '0';
    int i, mat;
    noAluno *novo, *novoAvl,*resp;
    noAluno *arvBinaria = NULL;
    noAluno *arvAVL = NULL;
    char listaNomes[MAX][TAM] = {"Adrielle", "Anderson", "Andressa", "Antonio", "Arno",
                                            "Augusto", "Barbara", "Bruno", "Calebe", "Cesar",
                                            "Cleiton", "Cynthia", "Daniel", "Daniel", "David"};

    int listaMatriculas[MAX]={1000, 2000, 3000, 4000, 5000, 6000, 6999, 6500, 6400, 6200, 7000, 8000, 8500, 8600, 9000};
    for(i = 0; i < MAX; i++){
        printf("\n\n\nTECLE ENTER PARA INSERIR O PROXIMO ELEMENTO...");
        getchar();
        novo = (noAluno*) malloc(sizeof(noAluno));
        novoAvl = (noAluno*) malloc(sizeof(noAluno));
        strcpy(novo->nome, listaNomes[i]);
        novo->matricula = listaMatriculas[i];
        novo->dir = NULL;
        novo->esq = NULL;
        strcpy(novoAvl->nome, listaNomes[i]);
        novoAvl->matricula = listaMatriculas[i];
        novoAvl->dir = NULL;
        novoAvl->esq = NULL;
        inserirNoArvoreBinaria(&arvBinaria, novo);
        inserirNoArvoreAVL(&arvAVL, novoAvl);
        system("cls");
        imprimeArvores(arvAVL, arvBinaria);
    }
    do{
        system("pause");
        getchar();
        system("cls");
        printf("\nMenu:");
        printf("\n1 - Buscar um Aluno na ARVORE BINARIA SIMPLES");
        printf("\n2 - Buscar um Aluno na  ARVORE AVL");
        printf("\n3 - Mostrar Fator de Balancemento dos nos da Arvore AVL");
        printf("\n0 - Sair");
        printf("\n");
        opcao = getch();
        system("cls");
        switch(opcao){
            case '1':
                imprimeArvores(arvAVL, arvBinaria);
                printf("\n------------------------------------------\n");
                printf("BUSCA ARVORE SIMPLES: Informe um Numero de matricula: ");
                scanf("%d", &mat);
                printf("\nUtilizando a arvore binaria simples:\n");
                printf("------------------------------------------\n");
                resp = buscarMatricula(arvBinaria, mat);
                if(resp == NULL){
                    printf("Aluno nao encontrado\n\n");
                }else{
                    printf("Aluno Encontrado:\n\n");
                    imprimeNoAluno(resp);
                }
                break;
            case '2':
                imprimeArvores(arvAVL, arvBinaria);
                printf("\n------------------------------------------\n");
                printf("BUSCA ARVORE AVL: Informe um Numero de matricula: ");
                scanf("%d", &mat);
                printf("\nUtilizando a arvore AVL:\n");
                printf("------------------------------------------\n");
                resp = buscarMatricula(arvAVL, mat);
                if(resp == NULL){
                    printf("Aluno nao encontrado\n\n");
                }else{
                    printf("Aluno Encontrado:\n\n");
                    imprimeNoAluno(resp);
                }
                break;
            case '3':
                printf("\n\nFator de balanceamento dos nos da arvore AVL:\n");
                printf("------------------------------------------\n");
                mostraFatBal(arvAVL, 0);
                break;
            default:
                if(opcao != '0') printf("\nOpcao Invalida!!!\n");
                break;
        }
    }while(opcao != '0');
    printf("Encerrando o programa...\n");
    destroi(arvBinaria);
    destroi(arvAVL);
 return 0;
}
