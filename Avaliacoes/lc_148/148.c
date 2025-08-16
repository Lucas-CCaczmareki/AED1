//leetcode 148, versão desenvolvida em casa
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* merge(struct ListNode* l, struct ListNode* r);
struct ListNode* sortList(struct ListNode* head);

int main () {
    struct ListNode n1, n2, n3, n4;
    n1.val = 4; n1.next = &n2;
    n2.val = 2; n2.next = &n3;
    n3.val = 1; n3.next = &n4;
    n4.val = 3; n4.next = NULL;

    struct ListNode* sorted_head = sortList(&n1);


    //Imprime a lista ordenada para verificar
    printf("Lista Ordenada: ");
    struct ListNode* current = sorted_head;
    while (current != NULL) {
        printf("%d -> ", current->val);
        current = current->next;
    }
    printf("NULL\n");
    
    system("pause"); //pra poder visualizar
    return 0;
}

struct ListNode* merge(struct ListNode* l, struct ListNode* r) {
    // Usa um nodo dummy para construir a lista ordenada com base nele
    struct ListNode dummy;
    // Usa um ponteiro "tail" pra saber onde inserir o próximo elemento
    struct ListNode* tail = &dummy;

    //Percorre as duas listas procurando o menor entre elas
    
    //************************* !!!! ***************************
    //Mostrar a lógica de percorrer pensada com um desenho
    //**********************************************************
    while(l != NULL && r != NULL) {
        if (l->val <= r->val) {
            //Se o valor do l for o menor, então ele é o primeiro da lista
            tail->next = l;
            l = l->next;
        } else {
            //Se o valor de r for o menor, linka ele
            tail->next = r;
            r = r->next;
        }
        //Após linkar o próximo nodo, move o tail pra ele
        tail = tail->next;
    }
    
    //Caso alguma das listas tenha mais elementos que a outra linka ele
    //(sempre é no máx 1 a +, por que dividimos no meio)
    if(l != NULL) {
        tail->next = l;
    } else if (r != NULL) {
        tail->next = r;
    }

    //Retorna a cabeça que o dummy aponta (a lista ordenada)
    return dummy.next;
    
}

struct ListNode* sortList(struct ListNode* head) {
    
    //Primeiro testa pra ver se a lista já veio ordenada
    if(head == NULL || head->next == NULL) {
        return head;
    }

    //Cria os 2 ponteiros auxiliares para percorrer a lista até a metade (slow & fast)
    //Slow percore de 1 em 1, e fast de 2 em 2. Quando fast chega ao fim, slow está no meio
    struct ListNode *slow = head; 
    struct ListNode *fast = head->next; //começa 1 na frente pra lógica funcionar com ímpares


    /* Exemplo da lógica
    * Agora slow ta na metade, mas imagine
    *  1 -> 2 -> 3 -> 4
    * Slow aponta pro 2, e para dividir a lista, right_head deve ser o 3.
    * A mesma lógica funciona para os ímpares.
    */

    //************************* !!!! ***************************
    // Mostrar a lógica dos ponteiros com um desenho
    //**********************************************************
    while (fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
    }

    //head se torna a lista à esquerda
    //right_head se torna a lista à direita
    struct ListNode *right_head = slow->next;
    
    //Quebra a lista entre parte direita e esquerda
    slow->next = NULL; 

    //************************* !!!! ***************************
    // Mostrar a lógica recursiva com um desenho
    //**********************************************************

    //Agora dividimos a lista de novo até sobrar 1 elementos só.
    struct ListNode *l = sortList(head);
    struct ListNode *r = sortList(right_head);

    //Pegamos os 2 elementos, ordenamos eles e juntamos numa lista só
    //Aqui retorna recursivamente as esquerda e direita
    return merge(l, r);
}