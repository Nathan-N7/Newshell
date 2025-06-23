# 🐚 Minishell

Este projeto foi desenvolvido como parte do currículo da 42. O objetivo é criar uma shell interativa que execute comandos, implemente funcionalidades básicas do Bash e trate entradas do usuário de forma robusta.

---

## 📘 Sobre o Projeto

O **Minishell** é uma implementação em C de um shell simples que simula o comportamento básico de um terminal Bash. Ele lê entradas do usuário, interpreta comandos, gerencia redirecionamentos, pipes, variáveis de ambiente, e executa programas de forma interativa.

---

## ⚙️ Funcionalidades

### ✅ Implementadas:

- Execução de comandos com caminho absoluto ou relativo
- Comandos encadeados com pipes (`|`)
- Redirecionamentos:
  - `>`  redireciona a saída para um arquivo (sobrescreve)
  - `>>` redireciona a saída para um arquivo (modo append)
  - `<`  redireciona a entrada de um arquivo
  - `<<` here-document (heredoc)
- Expansão de variáveis de ambiente (`$VAR`)
- Expansão do código de saída do último comando (`$?`)
- Suporte a aspas simples `'` e duplas `"`
- Leitura interativa com `readline` e histórico
- Tratamento de sinais:
  - `CTRL+C` → interrompe comando atual
  - `CTRL+D` → encerra o shell
  - `CTRL+\` → ignorado
- Built-ins:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

### 🚫 Não implementado:

- Curingas (`*`, `?`, etc.)
- Redirecionamento de stderr (`2>`, `2>>`)
- Operadores lógicos (`&&`, `||`)
- Histórico persistente entre sessões

---

## 🛠️ Compilação

Compile o projeto com o `make`:

make


Isso irá gerar o executável `./minishell`.

---

## ▶️ Como usar

Após compilar, execute com:

`./minishell`



Digite comandos normalmente como em um terminal bash. Exemplos:


- `echo Olá Mundo`
  - Olá Mundo


- `export NOME=42`
- `echo $NOME`
  - 42


- `cat arquivo.txt | grep erro > erros.txt`


`<< EOF`
> linha 1
> linha 2
> EOF


Para sair do shell, use:

`exit`

Ou pressione `CTRL+D`.

---

## 📌 Regras importantes (42)

- Não é permitido usar:
  - `system()`
  - `popen()`
  - `execvp()` ou derivados
- Apenas funções autorizadas pela 42 estão liberadas
- É obrigatório seguir a Norminette:
  - Máximo 25 linhas por função
  - Máximo 5 variáveis por função
  - Sem uso de `for`, ternário ou `switch`
- Sinais (`SIGINT`, `SIGQUIT`, `EOF`) devem ser tratados corretamente
- Built-ins devem funcionar sem spawn de processos externos
- O comportamento deve imitar o Bash sempre que possível

---

## 💬 Retorno de erros

O Minishell retorna códigos de erro conforme o Bash:

- `0` → sucesso
- `1` → erro geral
- `127` → comando não encontrado
- `126` → permissão negada ou comando não executável
- `258` → erro de sintaxe (ex: pipe no final)
