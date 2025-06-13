# Lucas Cavallin Caczmareki
# TURMA M1

# Agenda pBuffer

Faça uma agenda com o seguinte menu:
1- Adicionar Pessoa (Nome, Idade, email)
2- Remover Pessoa
3- Buscar Pessoa
4- Listar todos
5- Sair
 
O desafio é não poder criar variáveis e sim um buffer de memória (void *pBuffer). Nisso vocês terão que fazer o trabalho que o Sistema Operacional faz para vocês ao organizar a memória.
 
Regras:
Nenhuma variável pode ser declarada em todo o programa, somente ponteiros. Todos os dados do programa devem ser guardados dentro do pBuffer.

Nem mesmo como parâmetro de função. Só ponteiros que apontam para dentro do pBuffer.

Exemplo do que não pode: int c; char a; int v[10];  void Funcao(int parametro)
Não pode usar struct em todo o programa.

O tamanho da área de dados precisa crescer conforme o input.

# Possíveis melhoria
+ Validação de dados. Do tipo, o usuário não poder escrever algo que não seja número na idade.
Adaptar o programa pra poder receber mais dados diferentes de input. (a lógica atual funciona apenas com os que foram pedidos).

# Sobre pesquisa e uso de IA
A IA foi usada para debuggar o programa, achar errinhos toscos e brainstorm de ideias.
Pesquisei algumas funções de C, seus parâmetros e retornos; Também pesquisei sobre algumas estruturas de dados e dei uma revisada nelas pra escolher a que eu utilizaria.

# 
