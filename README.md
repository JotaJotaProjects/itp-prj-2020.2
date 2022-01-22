# :robot: BOTENILDSON
Bot jogador de Buraco feito por João Guilherme Lopes Alves da Costa e João Pedro Fonseca Dantas, alunos do Bacharelado em Tecnologia da Informação na UFRN, apresentado como projeto de conclusão da disciplina Introdução às Práticas de Programação, ministrada pelo Professor Andre Mauricio Cunha Campos, durante o período 2020.2.

Descrição do projeto: https://github.com/amccampos/itp-prj-2020.2

Alunos:
- João Guilherme Lopes Alves da Costa, matrícula 20200045609, turma DIM0133, T02 (246M34) <a href="https://github.com/joaoguilac">@joaoguilac</a>
- João Pedro Fonseca Dantas, matrícula 20200045162, turma DIM0133, T02 (246M34) <a href="https://github.com/jopefd">@jopefd</a>

## :pushpin: CHECKPOINT 1

Começamos o primeiro checkpoint com algumas jogatinas no [Buracoon](https://buracoon.com.br/) para compreendermos melhor como o jogo funciona. Em seguida, analisamos as regras que deveriam ser adotadas e, com bases nessas, estabelecemos quais seriam as ações de Botenildson:

- Ao ínicio da partida:
    - Ler seu identificador;
    - Receber suas cartas iniciais;
    - Ler a carta inicial do topo do lixo;
- A cada turno:
    - Verificar se a carta descartada pelo oponente faz jogo com as cartas de Botenildson;
        - Se sim, então pegar o lixo e baixar o jogo formado
        - Se não, então comprar uma carta do deque de compra
    - Verificar se é possível adicionar alguma carta a um jogo baixado
    - Verificar se é possível baixar um novo jogo
    - Descartar a pior carta da mão

Além disso, também analisamos o código-fonte base disponibilizado. Com ele, Botenildson realizava algumas das funções que nós listamos: as de leitura, compra e descarte de cartas. Portanto, voltamo-nos para as funções de verificação (quanto aos jogos) e de gravação (quanto às cartas), bem como para as estruturas de guardar os dados das cartas e da mão. Optamos, inicialmente, pela criação de três tipos: `Value` e `Suit` para o valor e o naipe das cartas, respectivamente, e `Hand` para uma mão de cartas. Os dois primeiros tipos foram preservados, mas escolhemos abandonar a [ideia do tipo `Hand`](##DIFICULDADES). Após isso, o foco principal do desenvolvimento foi [a função para o `GET_DISCARD`](##dificuldades).

## :pushpin: CHECKPOINT 2

Os principais avanços do checkpoint 2 foram a conclusão da função `formMeld` (responsável por formar um jogo) e a refatoração da código. Primeiramente, separamos as funções do código principal com um cabeçário `cards.h` para as suas assinaturas (bem como para os tipos e as constantes que criamos) e com um arquivo `cards.c` para a implementação das funções. Com isso, concluímos a modularização do código de Botenildson. Adicionalmente, reescrevemos alguns trechos tanto do código principal quanto das funções: removemos alguns parâmetros que poderiam ser isolados dentro das suas funções, e utilizamos mais retornos e passagem por referência (com arrays e ponteiros).

No CHECKPOINT 2 concentramos nossos esforços para baixar os jogos pelo GET_DISCARD, MELD_NEW e MELD_JOIN.

## :pushpin: VERSÃO FINAL

- Fizemos um arquivo `README.md` para a descrição do projeto. 
- Tentamos deixar o código o mais legível possível com nomes de funções e variáveis que façam sentido (declaramos variáveis e funções em inglês).
- Utilizamos documentação no formato doxygen.
- Dividimos os arquivos em três, um arquivo para o main (`botenildson.c`), um arquivo para as funções (`cards.c`) e um arquivo para declarações de constantes, structs e assinaturas das funções (`cards.h`).
- Conseguimos trabalhar no projeto com arranjos, ponteiros, alocação dinâmica e registros, como solicitado. 

## :exclamation: DIFICULDADES

### O tipo `Hand`

Descartamos essa idéia por causa da complexidade para fazer com que uma carta fosse inserida e ordenada, pois cada atributo desse tipo representava um naipe, de modo que era necessário repetir o mesmo código 4 vezes para que todos os naipes fossem contemplados numa verificação ou numa ordenação.

### Melé e Ás

Após algumas tentativas, não encontramos nenhuma abordagem que solucionasse o problema do jogo formado com um melé ou com um Ás (no início). Foi a maior dificuldade de implementação, pois quando tentávamos englobar jogos com melé e Ás no início tínhamos que fazer grandes alterações no código. Dessa forma, pelo tempo que não era tão favorável, decidimos seguir com o projeto sem a formação de jogos com melé e Ás no ínicio do jogo.

### MAX_LINE 200

Inicialmente, o tamanho máximo destinado a variável `line` era 200; contudo, percebemos que, certas vezes, a linha a ser lida era maior do que isso. O momento que a linha era maior que 200 era quando fazíamos um GET_DISCARD e o juíz retornava um grande número de cartas que não conseguíamos ler todas.

## :nut_and_bolt: SOLUÇÕES ADOTADAS

### Mão como um array de `Card`

Ao encarar uma mão como um array de `Card`, percebemos que foi mais fácil executar ações como a de ordenar e a de inserir uma carta, já que isso se tornou possível apenas com a inserção de uma carta na última posição da mão e, em seguida, com a ordenação da mão completa.

### Apenas jogos em sequência

Consideramos formar jogos cujas as cartas estejam em sequência.

### MAX_LINE 530

Analisamos o pior dos casos para a leitura da `line`: "e se todas as cartas fossem passadas para Botenildson?". Realizamos alguns cálculos levando em consideração a quantidade total de cartas em uma partida de baralho e a formatação da `line` (quantidade de espaços e chaves). Escolhemos o valor 530 para ser o novo tamanho máximo da `line`.

## ⏯️ COMPILAÇÃO E EXECUÇÃO

Para compilar e executar, é importante criar uma pasta para deixar os executáveis, caso você esteja no Linux basta digitar o comando (recomendamos criar a pasta com o nome bin):

```sh
mkdir bin
```

### COMPILAÇÃO

Para a compilação, utilizamos o GCC. Digite em seu terminal:

```sh
$ gcc source/botenildson.c source/cards.c -o bin/botenildson
```

Esse tipo de compilação é recomendado se não estivermos fazendo alterações em nossos arquivos e se não for um projeto muito grande, com muitos arquivos. De qualquer forma, a maneira mais adequada de compilação é utilizando os comandos do arquivo `Makefile`.

O Makefile é um arquivo onde você define um conjunto de regras de comandos para serem executados quando você dá uma instrução make. Ele é uma forma de automatizar o processo de compilação, principalmente quando você tem muitos arquivos para compilar em partes.

Para compilar todo o bot basta você ir para a pasta source (`cd source/`) e digitar no terminal:

```
make all
make clean (apaga os arquivos .o)
```

### EXECUÇÃO

Para você mesmo jogar uma partida de Buraco contra Botenildson é preciso ter o arquivo do juíz (`buraco.js`) e o arquivo do usuário (`user.js`) na pasta juntamente com os arquivos de Botenildson (`botenildson.c`, `cards.c` e `cards.h`).

Para executar uma partida, é necessário também ter um oponente. Caso não tenha, você pode executar uma partida na qual você mesmo joga contra Botenildson. Para a execução, utilizamos o Node.js, caso você não tenha o nodeJs instalado, pode fazê-lo a partir do endereço https://nodejs.org/pt-br/. O programa funciona com a versão 10 do Node ou mais recentes. Digite em seu terminal:

```sh
$ node lib/buraco.js bin/botenildson
```

Caso tenha o executável de outro oponente, basta adicionar ao código anterior o nome do executável do oponente:

```sh
$ node lib/buraco.js bin/botenildson bin/executavel_do_oponente
```

E se quiser ver a troca de mensagens entre os bots e o juíz, basta digitar `-d` antes dos executáveis de cada jogador:

```sh
$ node lib/buraco.js -d bin/botenildson bin/executavel_do_oponente
```

Deixamos o arquivo .c do bot base (`bot_base.c`), e para executar um jogo de Botenildson contra o bot base basta digitar os seguintes comandos no terminal:

```sh
$ gcc lib/bot_base.c -o bin/botbase (compilar o bot base)
$ node lib/buraco.js -d bin/botenildson bin/botbase (executar botenildson x bot base)
```

Além do mais, deixamos o arquivo `camp2.sh` que executa o Botenildson contra o bot base pra ver se algum dos dois causa algum erro de execução. Para executar o arquivo `camp2.sh` basta digitar no terminal `lib/camp2.sh`.

## 🤝 BOM JOGO!
Botenildson, João Guilherme e João Pedro desejam-vos um bom jogo!
