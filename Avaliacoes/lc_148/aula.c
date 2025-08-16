//leetcode 148

#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* merge(struct ListNode* l, struct ListNode* r);
struct ListNode* sortList(struct ListNode* head);

int main () {
    struct ListNode head, n2, n3, n4;
    head.val = 4;
    head.next = &n2;

    n2.val = 2;
    n2.next = &n3;

    n3.val = 1;
    n3.next = &n4;

    n4.val = 3;
    n4.next = NULL;


    //printf("%d", head.val);
    
    sortList(&head);
    
    system("pause");
}

//struct ListNode* mergeSort(struct ListNode* head);

struct ListNode* merge(struct ListNode* l, struct ListNode* r) {
    //Aqui a gente pode receber:
    //2 listas com 1 único elemento
    //2 listas com 2 elementos.
    struct ListNode result;
    struct ListNode *aux = &result;

    //O grande problema agora é conseguir fazer isso ser genérico pra 1 elemento, ou vários
    //Eu precisaria fazer tudo acima num loop ...?
    //Vamos imaginar o seguinte caso l= 1,3 | r= 2,4
    //Eu comparo os primeiros e vejo o menor, coloco no result, avanço o l,
    //Compara o l avançado com o r atrás, coloca o r, avança o r
    //Compara os 2, coloca o maior, depois o menor.
    //Mas e o teste de parada?
    //Se 1 deles só for null e o outro tiver diferente de null, adiciona o outro no result até que os 2 sejam null
    //Se os 2 são null, quebra o loop


    //Vamos tratar o primeiro caso
    
    while(l != NULL || r != NULL) {
        //O grande problema agora de novo é: como eu defino o result.next?
        struct ListNode a;
        aux->next = &a;
        if(l != NULL && r != NULL) {
            if (l->val <= r->val) {
                aux->val = l->val;
                l = l->next;
            } else {
                aux->val = r->val;
                r = r->next;
            }
        } else if (l != NULL && r == NULL) {
            aux->val = l->val;
            l = l->next;
        } else if (l == NULL && r != NULL) {
            aux->val = r->val;
            r = r->next;
        }
        aux = aux->next;
    }
    
    //acho que ta dando errado mas acabou o tempo
    return &result;
    
}

struct ListNode* sortList(struct ListNode* head) {
    //Como o array tá em uma ordem aleatória (eu não sei como ele chega), a melhor pedida seria o merge sort
    //Já que o desempenho dele era similar em qualquer tipo (até onde eu lembro).

    //Pra implementar o merge sort eu preciso dividir o vetor (lista) na metade
    //Depois fazer isso recursivamente até chegar nos elementos únicos
    //E ai ordenar individualmente e ir colando os resultados

    struct ListNode *aux = head; //ponteiro auxiliar pra percorrer a lista
    struct ListNode *aux2;
    struct ListNode left_head;
    struct ListNode right_head;

    //Vou tentar dividir o vetor recursivamente primeiro
    int tam = 0;
    int tam_left = 0;
    int tam_right = 0;

    //Encontra o tamanho da lista (esse provavelmente não é o melhor jeito de fazer isso)
    while (aux->next != NULL) {
        //printf("%d", aux->val);
        //aux = aux->next;
        tam++;
        aux = aux->next;
        
    }
    //Por que quando chega no último elemento, ele aponta pro NULL, e sai sem somar.
    if(tam != 0) {
        tam++;
    }

    //preenche a lista da esquerda
    tam_left = tam/2;
    aux = head;
    aux2 = &left_head;
    for(int i = 0; i < tam_left; i++) {
        aux2->val = aux->val;
        aux2->next = aux->next;
        
        aux = aux->next;
        aux2 = aux2->next;
    }

    //aqui aux tá  head do direito na teoria
    //preenche o da direita
    //aux = aux->next;
    aux2 = &right_head;
    while(aux2->next != NULL) {
        aux2->val = aux->val;
        aux2->next = aux->next;
        
        aux = aux->next;
        aux2 = aux2->next;
    }

    /*Testando se eles foram divididos mesmo
    aux = &left_head;
    aux2 = &right_head;
    for(int i = 0; i < tam; i++) {
        if(i < tam_left) {
            printf("%d", aux->val);
            aux = aux->next;
        } else {
            printf("%d", aux2->val);
            aux2 = aux2->next;
        }
    }
    */

    //Agora eu faço a chamada recursiva até ter um nodo só e volto ordenando;
    //O grande problema é como?

    struct ListNode *l = sortList(&left_head);
    struct ListNode *r = sortList(&right_head);

    //Ta, vamos imaginar que chegamos e no topo da pilha aqui eu recebi uma lista com um único elemento e ordeno
    //Depois retorno a lista reordenada com os 2 juntos.
    merge(l, r);
    

    //printf("%d", tam);
    return ;
}