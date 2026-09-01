# Sistema de alunos

Este projeto é um sistema simples para cadastrar, listar, atualizar, buscar e consultar alunos de uma turma. A ideia principal é manter os dados em memória e também salvar tudo em um arquivo binário chamado `lista_alunos.bin`.

O fluxo básico do programa é:

1. O programa inicia em `main()`.
2. Ele tenta carregar os alunos já salvos no arquivo para a memória.
3. Se o arquivo ainda não existir, o sistema cria esse arquivo.
4. O usuário navega por um menu com as opções do sistema.
5. Quando um aluno é cadastrado ou atualizado, os dados são gravados no arquivo e a memória é recarregada.

---

## Estrutura principal

A estrutura usada para cada aluno está em `aluno.h`:

```c
typedef struct
{
    char nome[40];
    char situacao[10];
    int matricula;
    int faltas;
    float media;
    float p1;
    float p2;
} Aluno;
```

Cada aluno guarda:

- nome
- matrícula
- prova 1
- prova 2
- média
- faltas
- situação (Aprovado ou Reprovado)

A turma pode ter até 40 alunos.

---

## Fluxo do programa ao iniciar

A função `main()` fica em `aluno.c` e é o ponto de entrada do sistema.

### O que ela faz

- cria as variáveis `opcao`, `qtd_alunos` e `flag_cadastro`
- chama `carregarAlunos()` para tentar carregar os alunos do arquivo para memória
- chama `gera_arquivo_aluno()` para garantir que o arquivo exista
- entra em um loop de menu
- executa a opção escolhida pelo usuário
- ao final, libera a memória com `free(lista_alunos)`

### Lógica de carregamento inicial

Quando o programa abre, ele não começa vazio. Em vez disso, o vetor de structs é carregado com o conteúdo do arquivo binário.

Isso acontece assim:

```c
Aluno *lista_alunos = carregarAlunos(&qtd_alunos, &flag_cadastro, DADOS_ALUNOS);
```

Ou seja, o programa lê os dados que já estão gravados e os coloca em memória para a aplicação trabalhar com eles.

---

## Função por função

## `main()` - arquivo `aluno.c`

### Objetivo

Controlar o menu principal do programa e orquestrar as operações do sistema.

### Fluxo

1. tenta carregar os alunos salvos no disco
2. garante que o arquivo exista
3. mostra o menu para o usuário
4. realiza a opção escolhida
5. repete até o usuário sair
6. libera a memória alocada antes de fechar o programa

### Lógica importante

- `flag_cadastro` informa se já existe pelo menos um aluno carregado
- `qtd_alunos` guarda quantos alunos estão na memória/arquivo
- `lista_alunos` é um ponteiro para um vetor dinâmico de alunos

---

## `gera_arquivo_aluno()` - arquivo `aluno_init.c`

### Objetivo

Criar o arquivo de dados do aluno, caso ele ainda não exista.

### Fluxo

1. tenta abrir o arquivo em modo leitura (`"rb"`)
2. se o arquivo já existir, apenas retorna
3. se não existir, abre em modo escrita binária (`"wb"`)
4. fecha o arquivo
5. informa ao usuário que o arquivo foi criado

### Lógica importante

Essa função evita que o programa tente abrir um arquivo inexistente e quebra o programa.

---

## `carregarAlunos()` - arquivo `aluno_read.c`

### Objetivo

Ler todos os alunos armazenados no arquivo binário e carregar para a memória.

### Fluxo

1. abre o arquivo em modo binário (`"rb"`)
2. chama `fseek(arquivo, 0, SEEK_END)` para ir para o fim do arquivo
3. chama `ftell(arquivo)` para saber o tamanho em bytes
4. chama `rewind(arquivo)` para voltar ao início
5. calcula quantos alunos há no arquivo usando:

```c
*qtd_alunos = tamanho_arquivo / sizeof(Aluno);
```

6. se a quantidade for zero, o arquivo está vazio
7. aloca memória dinamicamente com `malloc()`:

```c
Aluno *alunos = (Aluno *)malloc(*qtd_alunos * sizeof(Aluno));
```

8. lê os dados do arquivo com `fread()`
9. fecha o arquivo
10. retorna o ponteiro para o vetor carregado

### Lógica do `malloc`

`malloc` serve para reservar espaço na memória RAM em tempo de execução.

No caso do projeto:

- o programa não sabe quantos alunos vão existir no arquivo antes de abri-lo
- então ele calcula essa quantidade primeiro
- depois aloca exatamente o espaço necessário para guardar todos os registros

Exemplo:

```c
Aluno *alunos = malloc(qtd_alunos * sizeof(Aluno));
```

Se `qtd_alunos = 10`, ele reservará espaço suficiente para 10 registros do tipo `Aluno`.

### Uso de `fseek`, `ftell` e `fclose`

- `fseek`: move o cursor do arquivo para uma posição específica
- `SEEK_END`: indica o fim do arquivo
- `ftell`: retorna a posição atual do cursor em bytes
- `fclose`: fecha o arquivo depois que foi usado

Esses comandos são importantes para saber o tamanho do arquivo e não perder o controle do fluxo de leitura.

---

## `cadastrarAlunos()` - arquivo `aluno_write.c`

### Objetivo

Permitir que o usuário grave um novo aluno no sistema.

### Fluxo

1. abre o arquivo para verificar quantos alunos já existem
2. usa `fseek` e `ftell` para saber o tamanho atual do arquivo
3. calcula `qtd_alunos`
4. verifica se a turma já chegou a 40 alunos
5. lê os dados do aluno
6. valida matrícula duplicada
7. calcula a média:

```c
aluno.media = (aluno.p1 + aluno.p2) / 2.0f;
```

8. define a situação:

```c
if ((aluno.media >= 6) && (aluno.faltas <= 20))
    strcpy(aluno.situacao, "Aprovado");
else
    strcpy(aluno.situacao, "Reprovado");
```

9. abre o arquivo em modo de append (`"ab"`) para adicionar o aluno no final
10. grava o registro com `fwrite()`
11. fecha o arquivo
12. atualiza a quantidade de alunos
13. recarrega os alunos do arquivo para memória usando `carregarAlunos()`

### Lógica do limite de 40 alunos

A verificação é feita assim:

```c
*qtd_alunos = (int)(tamanho_arquivo / sizeof(Aluno));

if (*qtd_alunos >= 40)
{
    printf("Limite de 40 alunos atingido.\n");
    return lista_alunos;
}
```

Ou seja, o programa lê o tamanho do arquivo, divide pelo tamanho de um `Aluno`, e descobre quantos registros existem. Isso é o que determina se ainda é possível cadastrar mais alunos.

---

## `verificarMatricula()` - arquivo `aluno_find.c`

### Objetivo

Verificar se a matrícula informada já existe.

### Fluxo

- percorre o vetor de alunos
- compara cada matrícula com a matrícula digitada
- se encontrar, retorna `1`
- se não encontrar, retorna `0`

### Lógica importante

Esse controle impede que duas pessoas tenham a mesma matrícula no sistema.

---

## `retornarPosicao()` - arquivo `aluno_find.c`

### Objetivo

Encontrar a posição de um aluno no vetor a partir de sua matrícula.

### Fluxo

- percorre o vetor
- compara as matrículas
- quando encontrar, retorna o índice
- se não encontrar, retorna `-1`

Essa função é usada nas buscas por matrícula.

---

## `contarAprovados()` e `contarReprovados()` - arquivo `aluno_find.c`

### Objetivo

Contar quantos alunos estão aprovados e quantos estão reprovados.

### Fluxo

- percorre todos os alunos
- verifica as condições da situação
- incrementa o contador correspondente

### Condição de aprovação

```c
aluno[i].media >= 6.0 && aluno[i].faltas <= 20
```

### Condição de reprovação

```c
aluno[i].media < 6.0 || aluno[i].faltas > 20
```

Essas funções são usadas depois pela função de consulta de situação.

---

## `exibirAlunos()` - arquivo `aluno_read.c`

### Objetivo

Imprimir todos os alunos cadastrados.

### Fluxo

1. verifica se há alunos cadastrados
2. percorre o vetor inteiro
3. mostra os dados de cada aluno
4. imprime nome, matrícula, notas, média, faltas e situação

### Lógica importante

Se `flag_cadastro` for `false`, o programa informa que ainda não existem alunos registrados.

---

## `exibirAluno()` - arquivo `aluno_read.c`

### Objetivo

Mostrar os dados de um único aluno.

### Fluxo

- recebe um registro do tipo `Aluno`
- imprime todas as informações daquele aluno
- é usada pelas funções de busca e listagem específica

---

## `exibirAlunosAprovados()` e `exibirAlunosReprovados()` - arquivo `aluno_read.c`

### Objetivo

Filtrar e mostrar apenas os alunos aprovados ou reprovados.

### Fluxo

- percorre todos os alunos
- verifica a condição
- chama `exibirAluno()` para mostrar cada aluno correspondente

---

## `consultaSituacao()` - arquivo `aluno_read.c`

### Objetivo

Permitir ao usuário consultar alunos aprovados ou reprovados.

### Fluxo

1. mostra menu com opções:
   - exibir aprovados
   - exibir reprovados
   - sair
2. lê a escolha do usuário
3. chama `contarAprovados()` ou `contarReprovados()`
4. se houver registros, imprime a quantidade e os dados dos alunos
5. se não houver, informa que não existe aluno na situação pedida

---

## `consultaAluno()` - arquivo `aluno_read.c`

### Objetivo

Permitir busca por aluno usando matrícula ou nome.

### Fluxo

1. mostra as opções de busca
2. se escolher matrícula, chama `exibirPeloID()`
3. se escolher nome, chama `exibirPeloNome()`
4. imprime o resultado da busca

---

## `exibirPeloID()` e `exibirPeloNome()` - arquivo `aluno_read.c`

### Objetivo

Buscar aluno em específico.

### Fluxo

- `exibirPeloID()` usa `retornarPosicao()` para encontrar no vetor
- `exibirPeloNome()` percorre todos os alunos e compara nomes com `strcmp()`
- se encontrar, mostra os dados
- se não encontrar, informa que não foi encontrado

---

## `atualizar_aluno()` - arquivo `aluno_update.c`

### Objetivo

Atualizar dados ou notas de um aluno já cadastrado.

### Fluxo

1. verifica se há alunos cadastrados
2. pergunta qual matrícula será atualizada
3. valida se a matrícula existe
4. mostra os dados do aluno encontrado
5. pergunta se o usuário deseja atualizar:
   - dados do aluno
   - notas do aluno
6. chama `atualizar_dados()` ou `atualizar_notas()`
7. regrava o vetor inteiro no arquivo binário

### Lógica importante

Como o sistema salva os dados em arquivo, ao atualizar a estrutura em memória, o programa escreve tudo de volta no arquivo para manter o estado consistente.

---

## `atualizar_dados()` - arquivo `aluno_update.c`

### Objetivo

Alterar informações gerais do aluno.

### Fluxo

- pede novo nome
- pede nova matrícula
- pede número de faltas
- pede prova 1 e prova 2
- recalcula a média
- atualiza a situação conforme a regra do sistema

---

## `atualizar_notas()` - arquivo `aluno_update.c`

### Objetivo

Alterar apenas as notas do aluno.

### Fluxo

- lê nova nota da prova 1
- lê nova nota da prova 2
- recalcula a média
- recalcula a situação

---

## `limpaBuffer()` - arquivo `aluno_util.c`

### Objetivo

Limpar o buffer do teclado após um `scanf()`.

### Fluxo

```c
void limpaBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
```

### Por que isso é necessário

Depois de ler um número com `scanf()`, o teclado pode ficar com `\n` armazenado no buffer. Isso faz com que a próxima leitura de texto, por exemplo com `fgets()`, pule direto. Então `limpaBuffer()` elimina esse caractere e evita erros de entrada.

---

## `removeEnter()` - arquivo `aluno_util.c`

### Objetivo

Remover a quebra de linha da string lida com `fgets()`.

### Fluxo

```c
void removeEnter(char string[])
{
    string[strcspn(string, "\n")] = '\0';
}
```

### Por que isso é necessário

Quando o usuário digita um nome com `fgets()`, a string normalmente vem com um `\n` no final. Isso quebra a lógica da impressão e do armazenamento. Por isso, `removeEnter()` substitui esse `\n` por `\0`, que significa fim da string.

---

## Lógica de persistência em arquivo

O sistema usa arquivo binário para guardar os registros. Isso significa que os dados do tipo `Aluno` são gravados “crus” na memória do disco, em um formato binário, não em texto puro.

A lógica geral é:

- `fopen(..., "wb")` para criar/escrever arquivo
- `fopen(..., "ab")` para acrescentar mais alunos
- `fwrite()` para gravar um registro
- `fread()` para ler os registros de volta para memória

Esse modelo permite que o programa recupere os dados da última vez que foi executado.

---

## Resumo do fluxo do sistema

1. o programa abre e verifica se o arquivo existe
2. se existir, ele o lê e carrega em memória
3. o usuário usa o menu para cadastrar, listar, buscar ou atualizar
4. ao salvar, o arquivo é atualizado
5. o programa sempre recalcula a média e a situação de cada aluno
6. a turma tem um limite máximo de 40 alunos
7. a memória dinâmica é usada para armazenar os alunos em tempo de execução

---

## Observação importante

Este programa foi desenvolvido com a ideia de manter a lógica modular, separando cada parte em arquivos específicos:

- `aluno.c` → fluxo principal
- `aluno_init.c` → criação do arquivo
- `aluno_write.c` → cadastro
- `aluno_read.c` → leitura, busca e exibição
- `aluno_update.c` → atualização
- `aluno_find.c` → busca e contagem
- `aluno_util.c` → utilidades gerais
- `aluno.h` → definição da estrutura e protótipos

Essa separação facilita o entendimento e a manutenção do código.
