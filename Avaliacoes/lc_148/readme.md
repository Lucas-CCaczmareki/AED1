# Lucas Cavallin Caczmareki
# TURMA M1

## Leet code 148: Sort List
Given the head of a linked list, return the list after sorting it in ascending order.

Example 1:
Input: head = [4,2,1,3]
Output: [1,2,3,4]

Example 2:
Input: head = [-1,5,3,4,0]
Output: [-1,0,3,4,5]

## O que foi feito em aula
    - Relembrei como manipular as linked lists
    - Criei uma função main para testes
    - Consegui dividir a linked list em esquerda e direita
        * A divisão, infelizmente, era feita de forma ineficiente, criando novas listas com os elementos da original
        * Além disso eu percorria toda a lista para descobrir seu tamanho e depois percorria de novo preenchendo as outras listas.
    - Lógica recursiva para divisão implementada.
    - Lógica para juntar as listas divididas (merge) implementada.
        * Novamente, como eu usava listas criadas, isso dava todo tipo de problema e era ineficiente.
        * Também tornava o programa bem difícil de controlar, tendo vários segmentations faults que eu não consegui nem tratar por falta de tempo.

## Uso de IA
    - Explicação da complexidade
    - Ajuda para descobrir como resolver os problemas encontrados em aula de forma mais eficiente
        * Lógica do ponteiro slow e fast
        * Lógica do dummy e tail.
    - Entender como o código funcionava em alguns casos que ficaram confusos pra mim. 

## O que foi feito em casa
    - Refinamento do merge:
        * Implementar o dummy e o tail para resolver o problema de linkar a lista ordenada
        * Otimizando a memória (agora eu só reconecto as posições da lista ao invés de criar novas)
    
    - Refinamento do sort:
        * Implementar a lógica dos ponteiros slow e fast
        * Com essa lógica, já não se tornou mais necessário criar outras listas pra armazenas as divisões.

## Solução(ões) do editorial:
    Não estão disponíveis gratuitamente.
