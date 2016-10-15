<center> Relatório de MAC0121 - EP3 </center>
===================
Juliano Garcia de Oliveira					Nº USP: 9277086
-----------


----------


 <big> <b> 1. Especificação do Exercício  </b> </big>
<p align="justify" > O EP3 possui foco em algoritmos de ordenação. O propósito deste EP é, após ler um vetor de tamanho *n* da entrada padrão, que é considerado um vetor circular, e verificar se ele é ordenável através de sequências de 3-reversão. Se for possível ordenar, então deve-se imprimir a sequência de 3-reversões que ordena o vetor. Deve ser impresso "Nao e possivel" caso contrário.   </p>

 <big><b> 2. Algoritmo  </b></big>
<p align="justify" >O algoritmo implementado separa em vários casos de ordenação possíveis. A sequência das instruções (bem simplificada) é a seguinte:</p>

 - Ordena o vetor usando um ***heapSort***;
 -  Se o tamanho do vetor original for **par**:
    - Se a paridade entre o vetor original e o vetor ordenado são iguais, ordena o vetor original;
    - Senão, imprime "Nao e possivel" e finaliza a execução do programa;
 - Senão o tabuleiro é **ímpar**, então:
	- Ordena o vetor original e imprime os movimentos, já que é possível a ordenação.

<h3> A ordenação</h3>
O algoritmo usa 2 matrizes para fazer a ordenação. As duas matrizes são a matriz ***v*** e a matriz ***s***. Ambas são matrizes ***2 x n***, sendo que a primeira linha de cada matriz guarda os números propriamente ditos que compõe o vetor lido na entrada.
A matriz ***v*** é a matriz do vetor **original**, i.e. o vetor lido na entrada padrão.
A matriz ***s*** é a matriz do vetor **ordenado**.

O vetor ***v[0]*** é o vetor lido na entrada padrão.
O vetor ***v[1]*** pode ser duas coisas, dependendo do tamanho do vetor, e será explicado melhor abaixo.
O vetor ***s[0]*** é o vetor já ordenado.
O vetor ***s[1]*** é o vetor que armazena a posição onde o elemento **i** do vetor ordenado está no vetor original. Darei exemplos para melhor clarificação abaixo.


-  Vetor de tamanho **par**:

    Em um vetor de tamanho par, ao efetuar movimentos de 3-reversão, um elemento da posição **i** só pode chegar em posições de mesma paridade que **i**. Na prática, isto quer dizer que elementos que começaram em posição par no vetor original só podem chegar (através de 3-Rotação) em posições pares. E a mesma coisa para os ímpares, que só podem chegar em posições ímpares. Por exemplo, considere o vetor:

    1 2 3 4 6 5

    Para ordená-lo seria necessário trocar o número *5* com o *6*, mas como a posição de paridade deles são diferentes, é impossível ordenar este vetor usando 3-Reversão. É fácil perceber, por exemplo, que o *5* só pode trocar com o *2* e *4*, ou seja, só com posições ímpares (considerando que o vetor começa a ser contado do *0*);

    Para vetores pares, o vetor ***v[1]*** armazena a posição do elemento. Para o nosso exemplo, teríamos a seguinte disposição:

    ***v[0]***  =  1 2 3 4 6 5<br>
    ***v[1]***  =  0 1 2 3 4 5

    Em seguida, copia-se ***v[0]*** para ***s[0]*** e ***v[1]*** para ***s[1]***. Ordena-se a matriz ***s*** usando o *heapSort*, que ao trocar cada elemento de ***s[0]***, também troca os respectivos elementos de ***s[1]***. No final do *heapSort*, a matriz ***s*** está assim:

    ***s[0]***  = 1 2 3 4 5 6<br>
    ***s[1]***  = 0 1 2 3 5 4

    Para verificar se é possível ordenar ***v[0]***, eu simplesmente vejo se a paridade entre ***v[1]*** e ***s[1]*** é igual. Ou seja, verifico se o valor entre eles módulo 2 são iguais. O excerto de código abaixo faz essa verificação. Se ao final da iteração, *k* $\ne$ *n* , então alguma paridade é diferente, logo é impossível ordenar o vetor.
    ```c
    for (k = 0; k < n && (s[1][k] % 2 == v[1][k] % 2); k++);
    if (k != n)
        return false;
    ```
    Caso seja possível (a paridade entre ***v[1]*** e ***s[1]*** é igual), então faço um *bubbleSort* das posições pares do vetor e em seguida um outro *bubbleSort* das posições ímpares.
    Portanto, a complexidade neste caso é $\mathcal{O}(n\log{}n + n^2)$, que na prática é $\mathcal{O}(n^2)$ , pois é um *bubbleSort* no vetor inteiro de tamanho *n*. Como otimização, é feita uma verificação linear em cada etapa para saber se o vetor já está ordenado. Ou seja, se o vetor já está ordenado, não é executado o *bubbleSort*. E, se no final do primeiro *bubbleSort*, o vetor já está ordenado , ele já termina o programa, o que pode ser representado como $\mathcal{O}(n\log{}n +  \frac{n^2}{2} ) \approx  \mathcal{O}(\frac{n^2}{2} )$.



<br>

<big> <b> 3. Funções e estruturas de dados  </b> </big>
<p align="justify" >O EP consiste de 2 arquivos principais (excluindo o <i> header </i>):</p>

 - <i> restaUm.c </i>
 - <i> dataStructs.c </i>

<p align="justify" >Utiliza-se duas estruturas de dados principais (excluindo-se as já nativas do C, como vetores e matrizes):</p>

 - Pilha de movimentos : Armazena <i> structs </i> do tipo <i> pMovData </i> , que nada mais é que a coordenada da peça e o número do movimento executado;
 -  Vetor de posições : Armazena <i> structs </i> do tipo <i>pos</i>, que é uma posição (com um "<i>x</i>" e um "<i>y</i>") .

<p align="justify" >As funções possuem nomes bem autoexplicativos e são divididas em escopos distintos. A explicação de cada função está mais detalhada nos comentários do próprio código <i> restaUm.c </i>.</p>
<u><b> Resta um : </b> </u>

 - <b>Tabuleiro</b>
	 - <i>newBoard( )</i> : Cria o tabuleiro (matriz);
	 - <i>getBoardData( )</i> : Óbtem o número de peças e buracos vazios do tabuleiro, além de preencher um vetor de posições com as posições dos buracos vazios do tabuleiro.
 - <b>Resta Um e movimentos</b>
	 - <i>solvePeg( ) </i> : Função principal que resolve o Resta Um usando Backtrack e a pilha de movimentos;
	 - <i> doMove( )</i> : Move um peça se for possível;
	 - <i> undoMove( )</i> : Desfaz um movimento;
	 - <i> canMove( )</i> : Verifica se é possível efetuar um movimento;
	 - <i>isSolved( )</i> : Verifica se o tabuleiro está resolvido (também usa a função abaixo);
	 - <i>allPegsAreHoles( )</i> : Verifica se todos os buracos vazios estão ocupados por peças.

 - <b>Impressão e miscelânea</b>
	 - <i>printSolution( ) </i> : Imprime a solução de acordo com a especificação do EP2;
	 - <i> destroy( ) </i> : Libera a memória das estruturas de dados usadas no programa.

As funções do arquivo <i> dataStructs.c </i> são comuns e básicas e não precisam de descrição aqui.
<br>

<big> <b> 4. Otimização e resultados  </b> </big>
<p align="justify" >Primeiramente, as verificações básicas para descobrir se um tabuleiro é impossível não são tão necessárias, já que saem rapidamente do algoritmo de Backtrack, não sendo necessário escrever outra função somente para verificar isto. </p>

<p align="justify" >A maioria das otimizações executadas no EP2 foram para diminuir a utilização do <b> espaço </b> consumido pelo programa. A escolha dos tipos e como montar a pilha de movimentos foi feita pensando nesse fator. Temos os seguintes tipos e sua utilização:</p>

 - <i><b> minINT </b></i> : Usa o tipo "char" nativo do C. Como a matriz só é composta de 0, 1 ou -1, e os movimentos só podem ser 1, 2, 3 ou 4, todas essas variáveis não precisam ocupar o espaço que um <b> int </b> padrão ocuparia. Portanto, a matriz do tabuleiro e os movimentos possuem tipo <b> minINT </b>, para diminuir ao mínimo o consumo de espaço utilizado pelo programa.
 -  <i> <b>jCoord</b> </i>: A pilha dos movimentos só precisa de um inteiro <i>j</i> que é a coordenada de uma peça, diferentamente da maioria das implementações que provavelmente deve ter usado dois inteiros. A conversão do <i>j</i> para as coordenadas na matriz é simples e rápida, sendo simplesmente               " tab[<i>j/n</n>][<i>j%n</i>] " a coordenada correspondente, onde <i> n </n> é o número de colunas da matriz.

<p align="justify" >O problema do resta Um é <b> NP completo¹</b>, portanto não é trivial simplificar o problema. Achei vários modos de simplificar a árvore de possibilidades do programa.
</p>

<p align="justify" >O mais simples seria utilizar um <i>bitmask</i> para cada matriz que eu verificasse impossível de resolver. O <i>bitmask</i> da matriz seria armazenado em um <i> set </i> ou em uma <i> Hash Table </i>, e a cada iteração do algoritmo, verificar se o tabuleiro em questão está contido no meu <i> set / Hash Table </i>, e fazer o Backtracking caso estivesse. O problema é implementar tal simplificação na linguagem C, que não possui nenhum desses tipos (<i> set </i> e <i> Hash tables </i>) por padrão. Fiz um programa do Resta Um em Python que usava o tipo <i> set </i> do Python, mas para implementá-lo em C eu teria que ter conhecimentos de "Árvores Rubro negras" ou "Árvores de Busca", que ainda não vimos no curso. Portanto a melhor otimização que consegui achar ainda não possuo o conhecimento necessário para implementá-la.</p>
<p align="justify" >Outra otimização seria usar o que se chama <i> pagoda Function </i>² , que basicamente calcula uma soma usando a paridade das peças no tabuleiro. Não consegui achar muito mais sobre esta função, e o que achei valia apenas para casos quando temos apenas um buraco no tabuleiro. Por fim, outras otimizações usavam conceitos de programação linear e DFS, e no artigo <i> Integer Programming Based Algorithms for Peg Solitaire Problems </i> há a utilização de várias dessas técnicas avançadas, mas parecem muito avançados para a proposta deste EP e difícil de entender o funcionamento. </p>

<u><b> Testes e resultados : </b> </u>
<p align="justify" >Os testes feitos incluem a matriz 7  x 7 descrita no enunciado do EP2, matrizes menores para teste de funcionalidade e corretude ( 3 x 3 com várias configurações diferentes e 4 x 4 com 2 buracos). Para estes casos os resultados não demoram muito, levando na média 20 segundos para emitir a resposta quando fosse possível, e um pouco mais de tempo (cerca de 2 minutos) para casos impossíveis.
O tempo cresce rapidamente e se torna inviável para resolver tabuleiros com dimensões maiores que 8 x 8, ou ainda tabuleiros com dimensões menores porém com vários buracos vazios. Vários desses testes não terminaram após 1 hora de teste, quando foi abortada a execução do algoritmo. </p>

<p align="justify" >Os resultados foram satisfatórios para o tipo de técnica usada (Backtracking), já que esta técnica é conhecida por testar todas as possibilidades e não ser a mais eficiente de todas, o resultado não surpreende. A técnica de Backtracking foi aplicada corretamente e infelizmente por limitações de linguagem e (principalmente) do meu conhecimento, não consegui aplicar otimizações mais avançadas como o <i> Dynamic Programming </i> e <i> Memoization </i>, que consegui utilizar no EP1. </p>

<br>
<br>
<br>
<br>
<br>


<u> <b> Fontes: </b> </u>
<br>
 [1]: Uehara, R.; Iwata, S. (1990), "Generalized Hi-Q is NP-complete", Trans. IEICE, 73: 270–273 <br><br>
 [2]: Berlekamp, E. Conway, J. H. and Guy, R. K.: Winning Ways for Mathematical Plays. Academic Press London 1982  <br><br>
<a href="http://www.kurims.kyoto-u.ac.jp/~kyodo/kokyuroku/contents/pdf/1185-11.pdf">Integer Programming Based Algorithms for Peg Solitaire Problems </a>,  Masashi KIYOMI. Department of Mathematical Engineering and Information Physics, University of Tokyo. <br><br>
<a href="http://www.gibell.net/pegsolitaire/" > George's Peg solitaire Page . </a>
