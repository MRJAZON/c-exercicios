# Gerenciador de Arquivos em C

Simulação de um sistema de arquivos em memória, usando **lista encadeada** e **alocação dinâmica** (`malloc`/`free`). Menu interativo no terminal.

## Funcionalidades

- Criar arquivo (nome e tamanho em bytes), recusando nomes duplicados
- Listar arquivos
- Buscar arquivo por nome
- Remover arquivo por nome
- Ver o armazenamento total ocupado

## Conceitos praticados

- `struct` com ponteiro para o próximo elemento (lista encadeada)
- Alocação dinâmica com `malloc` e verificação de `NULL`
- Liberação de memória com `free`, inclusive ao encerrar o programa
- Ponteiro para ponteiro (`struct Arquivo **inicio`) para alterar o início da lista dentro de funções
- Remoção no início, meio e fim da lista
- Leitura segura de entrada (`%499s`, validação do retorno do `scanf`, limpeza do buffer)

## Zero vazamento de memória

Testado com o Valgrind:

```
valgrind --leak-check=full ./gerenciador
```

Resultado:

```
All heap blocks were freed -- no leaks are possible
ERROR SUMMARY: 0 errors from 0 contexts
```

## Como compilar e rodar

```
gcc -Wall -Wextra -g main.c -o gerenciador
./gerenciador
```

## Limitações conhecidas

- Nomes de arquivo não podem conter espaços (a leitura usa `%s`).
- O tamanho de cada arquivo é um `int`, então o limite por arquivo é cerca de 2 GB.