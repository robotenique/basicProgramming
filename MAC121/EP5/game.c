/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 28/11/2016
 * Implementação do gerenciador do jogo, que lê, processa, verifica e executa
 * os turnos de cada jogador.
 */
#include <stdio.h>
#include <time.h>
#include "game.h"
#include "pathFind.h"
#include "hexAI.h"
#define MAX_DEPTH 4


/* Protótipo de Funções locais */
color gamePlay(HexBoard *board, color player);
int gameDecide(HexBoard *board, color player, int maxDepth);


void gameLoop(HexBoard *board, color myPlayer) {
    int p2Move;
    color winner, p2;
    winner = NONE;
    if(myPlayer == WHITE)
        p2 = BLACK;
    else
        p2 = WHITE;
    /* Joga até que haja um vencedor */
    for(;;) {
        if(board->player == myPlayer) {
            /* Faz um movimento */
            winner = gamePlay(board, myPlayer);
            /* Verifica se houve vencedor */
            if(winner != NONE) {
                printf("%c ganhou\n",(winner == WHITE) ? 'b' : 'p');
                return;
            }
        }
        fflush(stdin);
        p2Move = getOponentMove(board, p2);
        if(board->turnN == 2 && board->hexs[p2Move].color != NONE &&
           myPlayer == WHITE) {
            /* Foi usada a pieRule pelo player2 */
            p2 = WHITE;
            myPlayer = BLACK;
        }
        else {
            /* Jogada comum */
            setHexagonColor(p2Move, board, p2);
            if(board->player == WHITE)
                board->player = BLACK;
            else
                board->player = WHITE;
        }
        board->turnN++;
    }
}

color checkVictory(HexBoard *board) {
    DjkStorage *djkS;
    DjkPath *djkPath;
    color winner;

    winner = NONE;
    /* OBS: Lembrar que o board está transposto, então as condições de
     * vitória de cada jogador também estão "invertidas"
     */

    /* Verificando condições de vitória (BLACK) */
    djkS = dijkstra(board, boardGetTopBorder(board), boardGetBotBorder(board),
                    0x04, 1, 1, 1);
    djkPath = djkGetPath(djkS, -1);
    if(djkPath->length > 0)
        winner = BLACK;
    djkDestroyPath(djkPath);
    djkDestroy(djkS);

    if(winner == BLACK)
        return winner;

    /* Verificando condições de vitória (WHITE) */
    djkS = dijkstra(board, boardGetRightBorder(board), boardGetLeftBorder(board),
                    0x02, 1, 1, 1);
    djkPath = djkGetPath(djkS, -1);
    if(djkPath->length > 0)
        winner = WHITE;
    djkDestroyPath(djkPath);
    djkDestroy(djkS);

    return winner;
}

int getOponentMove(HexBoard *board, color p2) {
    int x, y, id;
    do {
    scanf("%d %d", &x, &y);
    id = y*N_SIZE + x;
    }
    while ( y > 13 || x > 13 || y < 0 || x < 0 ||
            !isHexagonValid(id, board) ||
            (isHexagonPlayable(id, board) != 1 && board->turnN != 2));
    return id;
}

/*
 * Function: gamePlay
 * --------------------------------------------------------
 * Checa se há algum vencedor no jogo. Se não há, decide qual jogada
 * fazer, executa a jogada e altera o tabuleiro, imprimindo a jogada.
 *
 * @args    board: Um tabuleiro hexagonal (HexBoard)
 *          player: O jogador atual (WHITE ou BLACK)
 *
 * @return Se houve algum vencedor, retorna WHITE / BLACK, dependendo
 *         de quem venceu. Se apenas fez um movimento normal, retorna NONE.
 */
color gamePlay(HexBoard *board, color player) {
    int move;
    color winner = checkVictory(board);
    if(winner == WHITE || winner == BLACK)
        return winner;
    move = gameDecide(board, player, MAX_DEPTH);
    setHexagonColor(move, board, player);
    board->turnN++;
    if(board->player == WHITE)
        board->player = BLACK;
    else
        board->player = WHITE;

    printf("%d %d\n",move%board->size,move/board->size);
    boardPrint(board);
    return NONE;
}

/*
 * Function: gameDecide
 * --------------------------------------------------------
 * Decide qual jogada fazer, e retorna essa jogada. Se está nos turnos
 * iniciais, a jogada é escolhida de modo aleatório ou tenta pegar o meio.
 * Se o turno é < 10, há uma pequena chance de que a jogada seja aleatória.
 * Senão, é feita uma execução do algoritmo de Minmax para decidir uma jogada.
 *
 * @args    board: Um tabuleiro hexagonal (HexBoard)
 *          player: O jogador atual (WHITE ou BLACK)
 *          maxDepth: A profundidade máxima da game Tree (padrao = 4)
 *
 * @returno ID do hexágono para fazer a jogada.
 */
int gameDecide(HexBoard *board, color player, int maxDepth) {
    int bestM, i, j;
    HexBoard *dup;
    bestM = -1;
    if(board->turnN < 3) {
        /* Tenta pegar uma posição em quadrantes diferentes */
        if(player == WHITE && board->turnN == 1) {
            do {
                i = (rand()%1000)%4;
                j = (rand()%1000)%(4 - i);
                if((rand()%1000)%2 < 1) {
                    i = board->size - 1 - i;
                    j = board->size - 1 - j;
                }
                bestM = j*board->size + i;
            } while(!isHexagonPlayable(bestM, board));
            return bestM;
        }
        else if(player == BLACK) {
            bestM = board->size*board->size/2;
            while(!isHexagonPlayable(bestM, board))
                bestM = (board->size*board->size*(rand()/(1.0 + RAND_MAX)));
            return bestM;
        }
    }


    /* Coloca um pouco de aleatoriedade no jogo :)  */
    if(board->turnN < 10 && (rand()%1000) < 50) {
        bestM = (board->size*board->size*(rand()/(1.0 + RAND_MAX)));
        while(!isHexagonPlayable(bestM, board))
            bestM = (board->size*board->size*(rand()/(1.0 + RAND_MAX)));
        return bestM;
    }
    /* Duplica o tabuleiro e executa o algoritmo MTDf na cópia */
    dup = cloneHexBoard(board);
    MTDfRun(dup, player, maxDepth, &bestM);
    destroyHexBoard(dup);

    /* Se algoritmo falhou, escolhe uma jogada aleatória */
    if(!isHexagonPlayable(bestM, board))
        while(!isHexagonPlayable(bestM, board))
            bestM = (board->size*board->size*(rand()/(1.0 + RAND_MAX)));

    return bestM;
}
