/*
 * @author: Juliano Garcia de Oliveira
 * nº usp = 9277086
 * MAC0121
 * 28/11/2016
 * Header do gerenciador do jogo, que lê, processa, verifica e executa os
 * turnos de cada jogador.
 */
#ifndef _GAME_H_
#define _GAME_H_
#include "hexBoard.h"
#include "hexTypes.h"

/*
 * Function: gameLoop
 * --------------------------------------------------------
 * Implementa o loop de jogadas. O gameLoop (consultar a página
 * http://gameprogrammingpatterns.com/game-loop.html) é o loop que lê
 * e faz os movimentos de ambos os jogadores, até que haja um vencedor.
 * O loop faz uma jogada do computador, lê uma jogada da entrada padrão,
 * executa, atualiza o tabuleiro e volta para o início do loop, que só é
 * interrompido quando há vencedor.
 *
 * @args    board: O tabuleiro do jogo (HexBoard)
 *          player: O jogador que representa o computador (WHITE ou BLACK)
 *
 * @return
 */
void gameLoop(HexBoard *board, color myPlayer);
/*
 * Function: checkVictory
 * --------------------------------------------------------
 * Verifica se alguém venceu no jogo do tabuleiro passado como parâmetro.
 * Para ver se houve um vencedor, é executado um algoritmo de dijkstra de
 * uma extremidade a outra (que depende do tipo de jogador, segundo a
 * especificação do EP). Se foi possível achar um caminho de um lado até o
 * outro, então o jogador em questão venceu.
 *
 * @args    board: O tabuleiro do jogo (HexBoard)
 *
 * @return BLACK se o jogador BLACK ganhou. WHITE se o o jogador WHITE ganhou,
 *         ou NONE caso não haja vencedores.
 */
color checkVictory(HexBoard *board);
/*
 * Function: getOponentMove
 * --------------------------------------------------------
 * Lê uma entrada da jogada padrão e retorna o ID da jogada se ela for
 * válida. Se não for, pede uma nova entrada até que esta seja válida.
 * Há uma excessão para a pieRule nessa função.
 *
 * @args    board: O tabuleiro do jogo (HexBoard)
 *          p2: A cor do segundo jogador (BLACK ou WHITE)
 *
 * @return o ID do hexágono onde o p2 vai executar o movimento.
 */
int getOponentMove(HexBoard *board, color p2);

#endif
