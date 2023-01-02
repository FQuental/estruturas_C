#include <stdio.h>
#include <stdlib.h>
#include <string.h>  //Biblioteca para usar strings
#include <stdbool.h> //biblioteca para usar Booleanos em C

#define MAX 100 //define MAX para ser usado como elemento de aleatoridade na MAIN

typedef struct no{ //estrutura do nó, tendo elementos menores a esquerda e elementos maiores a direita
  int elem;       //valor do elemento que está na arvore
  struct no *esq; //ponteiro para a subarvore a esquerda(filho menor)
  struct no *dir; //ponteiro para a subarvore a direita(filho maior)
}noArvBB;          //nome dado para a estrutura de no da arvore usada

noArvBB *raiz = NULL; //raiz inicial da arvore é nula(arvore está vazia), mas o primeiro nó foi criado já
int quant = 0; //quantidade de elementos da arvore

bool insereArvBB(int valor){ //funçao de inserção de um elemento na arvore binaria (essa função tem como trabalho receber um valor a ser inserido na arvore, entao a função percorre a arvore desde a Raiz, até achar um ramo que possa adicionar o valor novo, sempre analizando se o valor novo eh menor ou maior que o valor atual, para poder percorrer a arvore no sentido certo e adicionar o elemento respeitando a regra de uma BST)
  noArvBB *ant = NULL;        //ponteiro inicial do anterior começa em nulo,pois como ele está na raiz, não possui "alguem" a cima
  noArvBB *atual = raiz;      //ponteiro inicial na raiz da arvore(apontando para o começo da arvore) a raiz foi definida na linha 10
  noArvBB *novo = (noArvBB *) malloc(sizeof(noArvBB)); //ponteiro para o valor novo, lembrando de alocar na memoria(MALLOC) espaço para todos os parametros da estrutura que foi criada para cada nó

//copia valores para o novo nó:
  novo->elem = valor; //o novo nó recebe em seu elemento o valor que foi enviado para a função
  novo->esq = NULL;   //o novo nó recebe nulo como parametro de esquerda
  novo->dir = NULL;   //o novo nó recebe nulo como parametro de direita

  while((atual != NULL) && (valor != atual->elem)){ //while para percorrer a arvore e achar onde deve ser inserido o novo elemento da arvore
    ant = atual; //anterior receve atual
    if(valor <atual->elem){ //analisa se o elemento é menor que o atual, se for ele vai para o elemento da esquerda da arvore
      atual = atual->esq;
    }
    else{ //se não for menor, entao ele vai para o elemento da direita da arvore
      atual = atual->dir;
    }
  }
  if(ant == NULL){ //caso da arvore inicial, quando a Raiz vale null, isso percebe que a arvore estava vazia e ja a preenche com o 1 elemento
    raiz = novo;
  }
  else{
    if(atual == NULL){  //analisa se o valor atual for nulo, ele sabe que esta na "vaga" de uma nova folha da arvore

                            //a partir da linha 40 até a 46 será a implementação a folha nova da arvore, diferente das linhas 25 a 31 onde era percorrido somente a arvore até se chegar numa folha que vai ser tornar ramo por adicionar uma nova folha

      if(valor < ant->elem){ //compara com o anterior, a ramo(pai do ramo) para saber se o novo elemento deve ser implementado a esquerda(sendo menor que o pai)
        ant->esq = novo;
      }
      else{                //implementa a nova folha a direita da ramo anterior(pai do ramo) isso porque ele eh maior ou igual ao pai
        ant->dir = novo;
      }
    }
    else{
      return false; //retorna false se não for possivel implementar
    }
  }
  quant++; //incrementa +1 na variavel de quantidade de elementos na arvore antes
  return true; //retorna true se o elemento foi implementado
}

int quantArvBB(){ //função para mostrar o numero de elementos na arvore
  return quant;
}

bool buscaArvBB(int valor){ //função para buscar alguem na arvore (recebe como parametro o valor do elemento procurado)
  noArvBB *atual = raiz;   //inicializa uma instancia na raiz para usar no começo da busca
  while((atual!= NULL) && (valor != atual-> elem)){ //fica em loop percorrendo a arvore
    if(valor < atual->esq){ //compara o valor se é menor para ir a esquerda
            atual = atual->esq;
  }
  else                      //se nao for para esquerda entao ele percorre para a direita
    atual = atual->dir;
}
if ((atual != NULL) && (valor == atual->elem)) //quando ele sai do loop da linha 65, compara para ver se achou o valor na posição atual
  return true;                                 //retorna TRUE se o valor foi achado
else
return false;                                 //retorna FALSE, caso em que foi prercorrido a arvore toda e nao foi achado o valor
}

void imprimePreOrdemArvBB(noArvBB *n){ //função que imprime a arvore usando o parametro como RAIZ, indo da raiz até a folha mais a direita dps indo para a esquerda e voltando para ir a sub arvore a direita indo até a folha mais a esquerda da sub arvore a direita
  if(n != NULL){ //confere se á element na posição atual (por ser recursivo, pode se ir a uma folha que está vaiza)
    printf(" %d ", n->elem); //imprime o elemento
    imprimePreOrdemArvBB(n->esq); //chama a funçao recursivamente para acessar a subarvore a esquerda
    imprimePreOrdemArvBB(n->dir); //chama a funçao recursivamente para acessar a subarvore a direita
  }
}

noArvBB * removeRec(noArvBB *atual, int valor){ //funcao para remover um elemento enviado como parametro de forma recursiva, além de remover o elemento essa função balanceia a arvore para atualizar os ponteiros de toda a sub arvore que estava ligada a esse NÓ e tbm substitui esse antigo NÓ com um novo elemento se necessario
  noArvBB *filho, *antDirEsq, *atualDirEsq; //elementos que usaremos como axuliar para efetuar a remoção
  if(atual != NULL){                        //comparação para saber se não está numa folha vaiza da arvore
    if(valor < atual->elem){                //percorre a arvore recursivamente para a esquerda por ter um valor MENOR que o NÓ atual
      filho = removeRec(atual->esq,valor);
      atual->esq = filho;
      return atual;
    }
    else
    if(valor >atual->elem){                //percorre a arvore recursivamente para a direita por ter um valor MAIOR que o NÓ atual
      filho = removeRec(atual->dir, valor);
      atual->dir = filho;
      return atual;
    }
    else{
      quant--;                            //remove 1 da variavel que conta a quantidade de elementos

      if((atual->esq != NULL) && (atual->dir != NULL)){ //caso onde o elemento removido ser um NÓ pai de 2 subArvores, da esquerda e da direita (sera preciso balancear a sub arvore da esquerda e dps ligar a subarvore da direita)
        antDirEsq = atual;
        atualDirEsq = atual->dir;
        while(atualDirEsq->esq !=NULL){ //percorre a subArvore saindo da posição atual até a folha mais a esquerda
          antDirEsq = atualDirEsq;
          atualDirEsq = atualDirEsq->esq;
        }
        if (antDirEsq != atual){ //reconfigura toda a subArvore para os novos ponteiros
          antDirEsq->esq = atualDirEsq->dir;
          atualDirEsq->esq = atual->esq;
          atualDirEsq->dir = atual->dir;
        }
        else{
          atualDirEsq->esq = atual->esq;
        }
        free(atual);     //remove da memoria o NÓ da arvore, removendo nao somente o valor como tambem os antigos ponteiros
        return atualDirEsq;
      }


      else
        if((atual->esq==NULL)&&(atual->dir==NULL)){ //Achou o elemento sendo uma folha que nao tem NENHUM outro ramo ligado
          free(atual);                              //remove direto o NÓ sem precisar balancear a arvore
          return NULL;
        }
        else

          if(atual->esq != NULL){ //o NÓ a ser removido somente tem ramos para a esquerda(menores que ele), entao antes de remover o NÓ é preciso alocar o ponteiro para o membro filho da subArvore a esquerda
            filho = atual->esq;
            free(atual);
            return filho;
          }else{                 //o NÓ a ser removido somente tem ramos para a direita(maiores que ele), entao antes de remover o NÓ é preciso alocar o ponteiro para o membro filho da subArvore a direita

            filho = atual->dir;
            free(atual);
            return filho;
          }
    }
  }
  else{//caso não ache o elemento dps de percorrer a arvore toda
    return NULL;
  }
}

void removeArvBB(int valor){ //chama a função de remoção recorsiva, para facilitar a implementação na main
  raiz=removeRec(raiz,valor);
}


int main(int argc, char *argv[]){ //main usada para testar as funçoes feitas
  int aux, i;
  for(i=0; i<100; i++){ //vai inserir 100 elementos na arvore de forma aleatoria(criaçõ da arvore que começou totalmente vazia)
    aux = rand() %(MAX*2);
    if(insereArvBB(aux) == false){
      i--;
    }
  }
  printf("\nQuantidade de nos: %d\n", quantArvBB()); //imprime o numero de nós

  imprimePreOrdemArvBB(raiz); //imprime todos os elementos da arvore de forma PreOrdem(ainda se tem outros 2 jeitos de percorrer a arvore binaria)
  printf("\n");
  printf("Digite o valor a ser removido: "); //Pede para o usuaria um valor para remover da arvore
  scanf("%d", &aux);
  if(buscaArvBB(aux) == true){ //Procura se o elemento dado pelo usuario está na Arvore, se existir na arvore o elemento é removido da arvore
    printf("O valor %d existe na arvore\n", aux);
    removeArvBB(aux);         //chama a função para remover o elemento
  }else{                      //Caso não for encontrado o elemento, entao informa o usuario que o elemento não está na arvore
    printf("O valor %d nao existe na arvore\n", aux);
  }
  printf("\n");
  imprimePreOrdemArvBB(raiz);  //imprime novamente a arvore, agora atualizada sem o elemento na arvore e com as suas subArvores atualizadas tambem
  printf("\nQuantidade de nos: %d\n", quantArvBB()); //imprime o valor de nos atualizado apos a remoção do elemento da Arvore

  return 0; //fim do programa
}
