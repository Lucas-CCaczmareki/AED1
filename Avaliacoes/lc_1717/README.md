# Lucas Cavallin Caczmareki
# TURMA M1

## Leet code 1717: Maximum Score From Removing Substrings
You are given a string s and two integers x and y. You can perform two types of operations any number of times.

- Remove substring "ab" and gain x points.
For example, when removing "ab" from "cabxbae" it becomes "cxbae".

- Remove substring "ba" and gain y points.
For example, when removing "ba" from "cabxbae" it becomes "cabxe".
Return the maximum points you can gain after applying the above operations on s.

Example:
Input: s = "cdbcbbaaabab", x = 4, y = 5
Output: 19

Explanation:
* Remove the "ba" underlined in "cdbcbbaaabab". Now, s = "cdbcbbaaab" and 5 points are added to the score.
* Remove the "ab" underlined in "cdbcbbaaab". Now, s = "cdbcbbaa" and 4 points are added to the score.
* Remove the "ba" underlined in "cdbcbbaa". Now, s = "cdbcba" and 5 points are added to the score.
* Remove the "ba" underlined in "cdbcba". Now, s = "cdbc" and 5 points are added to the score.
Total score = 5 + 4 + 5 + 5 = 19.

## O que foi feito em aula:
Em aula, eu consegui finalizar a lógica/estratégia para resolver o problema (num comentário chamado brainstorm está o passo a passo que eu pensei pra resolver). A estratégia que eu usei foi retirar primeiro a subpalavra de maior pontuação usando uma pilha: eu colocaria caracter por caracter na pilha comparando se o caracter colocado e o próximo caracter da palavra formariam uma subpalavra válida, se formassem eu pulava ele e dava um pop. Se não, eu empilhava ele. Depois eu colocava a string que sobrou na pilha em ordem inversa (devido ao comportamento da pilha) em outra pilha e retirava a outra subpalavra seguindo a mesma lógica.

Eu não consegui implementar o código inteiro em aula devido ao tempo, só a primeira passada.

## O que foi feito em casa:
Em casa, eu tentei finalizar a implementação, ela estava funcionando mas cheia de bugs, alguns deles:
- Segmentation fault, eu tentava acessar espaços de memória inválido com a lógica de "próximo caracter"
- O programa não considerava que ao retirar uma subpalavra, a próxima ser colocada e que se tornou o top formavam uma subpalavra válida. Isso foi corrigido mas causou um problema de código duplicado.
- Erro misterioso na segunda passada, ao fazer um pop que esvaziava a pilha auxiliar (a invertida) o top pegava um valor aleatório da memória o que acabava quebrando o programa indefinidamente. Sinceramente, não entendi direito o que tava acontecendo, eram tantos acessos irrestritos que a minha cabeça embaralhou (aqui eu comecei a usar a IA pra entender o que fazer).
- Soma de pontuação faltando. Eu não incrementava a pontuação num dos casos duplicados da primeira passada.

### Refazendo o código em casa:
Aqui eu parei pra pensar, li algumas dicas que a IA tinha me dado para arrumar o código, como:
- Colocar mais segurança e validação na criação e acesso à pilha.
- Simplificar a lógica das passadas
- Tirar a lógica de acessar o próximo caracter pra olhar só pro atual.
- Mudar o loop da segunda passada

Eu peguei essas dicas e reescrevi o código. A principal mudança foi a ordem de retirar as subpalavras, antes, eu tirava com base no topo da pilha e o próximo caracter, mas uma forma bem mais simples é: comparar o topo da pilha (caracter anterior) com o caracter atual. Isso arrumava os bugs de acesso irrestrito e tratava as subpalavras que poderiam se formar caso fosse feita uma remoção. (já que agora eu não comparava com o próximo e não pulava iterações com o i++).

Após reescrever o código o erro misterioso da segunda passada parou de acontecer e tudo correu bem.

## Complexidade
### Complexidade de tempo
Assumindo como n o tamanho da string s.
O primeiro loop percorre a string s até o seu final, todas operações dentro tem custo O(1), e o loop tem N iterações. O que me deixa com N * O(1) = O(N). O tempo sobe conforme a o tamanho da string aumenta.

O segundo loop depende do tamanho da pilha (a string que sobra após remover as primeiras subpalavras). No pior caso, ela ainda tem N, ou seja, não removeu nada. Então esse loop vai rodar N vezes, com operações O(1) (não dependem do tamanho do N). O que me deixa com N * O(1) = O(N).

Combinando os 2 loops temos O(N) + O(N) = O(2N). Simplificando isso, o crescimento em tempo ainda é linear conforme N, a complexidade final é O(N).

### Complexidade de espaço
Quanta memória vai ser alocada em relação a N (tamanho da string s).
Na primeira passada, stack_size tem o tamanho de N. Se não tiver nenhum par (pior caso), armazenamos N caracteres. Ou seja, o espaço alocado é proporcional à N. O(N).

Na segunda passada, a segunda stack é do tamanho da string que sobrou. No pior caso ela tem tamanho N, então de novo o espaço é O(N).

Combinando os 2 fica O(2N) que simplifica de novo pra O(N).

## Solução do editorial
### Solução 2: Greedy way sem stack
Reescreve a própria string original somando os pontos.
Usa um ponteiro de escrita e outra de leitura.
Vai copiando os caracteres pro início e se formam um par, volta o cursor de escrita em 2 posições e soma a pontuação.

Faz isso em 2 passadas, uma pra tirar as de maior valor e depois outra pra tirar a de menor valor.

Essa solução tenta economizar o processo de criar uma nova pilha.

### Solução 3: Counting
Essa solução tenta não usar memória nenhuma e só contar os pontos com base no número de a's e b's. Ele percorre a string contando quantos a's, e se tiver algum a ele tenta formar o par de maior valor, e diminui a quantidade de as sobrando e soma o score, se não tem a sobrando, ele aumenta a quantidade de b sobrando. No final, ele tem uma contagem de quantos a's e b's ficaram sobrando sem formar os pares de maior valor e a partir disso ele sabe quantos de menor valor foram formados.

## Uso de IA
Tentei usar a IA só como último recurso (no caso de que eu já não sabia mais o que tava acontecendo). Ai eu usei as dicas dela pra tentar entender o que tava acontecendo e arrumar o código.