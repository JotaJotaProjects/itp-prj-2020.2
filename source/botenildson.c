/** @file botenildson.c
 *  @brief Um bot jogador de buraco
 *
 *  Este arquivo contem o código principal do bot jogador de buraco e compreende
 *  as etapas principais do jogo: 1) o recebimento do identificador do bot para
 *  a partida e das cartas iniciais (da mão e do topo do lixo); 2) a análise de
 *  um possível jogo com a carta do topo do lixo ou a compra de uma carta do 
 *  deque; 3) a adição de uma carta a um jogo já baixado; 4) o baixar de um novo
 *  jogo; e 5) o descarte de uma das cartas da mão do bot.
 *
 *  @author João Pedro Fonseca Dantas
 *  @author João Guilherme Lopes Alves da Costa
 *  @see https://github.com/amccampos/itp-prj-2020.2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cards.h"

int main() {
  
  /*****************************************************************************
   * Declarações e Configurações
   ****************************************************************************/

  char line[MAX_LINE];
  char myId[ID_SIZE];
  char command[15];
  char cardInfos[6];
  int  meldQuantity = 0;
  int  myHandCardsQuantity = 0;
  int  droppedMeldsQuantity = 0;
  int  droppedMeldCardsQuantity = 0;
  Card topTrashCard;
  Card meld[MAX_MELD] = {0};
  Card myHand[MAX_HAND] = {0};
  Card **droppedMelds = NULL;

  setbuf(stdin, NULL);
  setbuf(stdout, NULL);
  setbuf(stderr, NULL);

  /*****************************************************************************
   * Início da Partida
   ****************************************************************************/

  readline(line);
  readline(line);
  strncpy(myId, line, ID_SIZE);

  readline(line);
  getCards(line, myHand, &myHandCardsQuantity);
  sort(myHand, myHandCardsQuantity);

  readline(line);
  topTrashCard = strToCard(line);

  for (int i = 0; i < MAX_MELD; i++) {
    meld[i].suit = NoCard;
  }

  /*****************************************************************************
   * Turnos
   ****************************************************************************/

  while (true) {
    do {
      readline(line);
      sscanf(line, "%s", command);

      if (strcmp(command, "DISCARD") == 0) {     
        sscanf(line, "%s %s", command, cardInfos);
        topTrashCard = strToCard(cardInfos);
      }
    } while (strcmp(line, myId));

    formTriple(topTrashCard, myHand, meld, &meldQuantity);
    formMeld(myHand, meld, &meldQuantity);
    
    sort(myHand, myHandCardsQuantity);
    myHandCardsQuantity -= meldQuantity;
    
    if (meld[0].value != 0) {
      printGetDiscard(topTrashCard, meld);
      droppedMelds = dropNewMeld(droppedMelds, &droppedMeldsQuantity, meld);
    } 
    else {
      printf("GET_STOCK\n");
    }

    readline(line);
    getCards(line, myHand, &myHandCardsQuantity);
    sort(myHand, myHandCardsQuantity);
    clearMeld(meld, &meldQuantity);
    
    for (int i = 0; i < droppedMeldsQuantity; i++) {
      droppedMeldCardsQuantity = countCards(droppedMelds[i], MAX_MELD);
      if (droppedMeldCardsQuantity < 7) {
        addFirst(myHand, droppedMelds[i], meld, &meldQuantity);
        addLast(myHand, droppedMelds[i], meld, &meldQuantity);
        if (meld[0].value != 0) {
          printMeldJoin(i, meld);
          sort(myHand, myHandCardsQuantity);
          myHandCardsQuantity -= meldQuantity;
          clearMeld(meld, &meldQuantity);
        }
      }
    }

    for (int i = 0; i < MAX_HAND; i++) {
      formTriple(myHand[i], myHand, meld, &meldQuantity);
      if (meldQuantity > 0) {
        meldQuantity++;
        formMeld(myHand, meld, &meldQuantity);
        printMeldNew(meld);
        droppedMelds = dropNewMeld(droppedMelds, &droppedMeldsQuantity, meld);
        myHand[i].value = 0;
        myHand[i].suit = NoCard;
        sort(myHand, myHandCardsQuantity);
        myHandCardsQuantity -= meldQuantity;
        clearMeld(meld, &meldQuantity);
      }
    }

    for (int i = 0; i < droppedMeldsQuantity; i++) {
      droppedMeldCardsQuantity = countCards(droppedMelds[i], MAX_MELD);
      if (droppedMeldCardsQuantity < MAX_MELD) {
        addFirst(myHand, droppedMelds[i], meld, &meldQuantity);
        addLast(myHand, droppedMelds[i], meld, &meldQuantity);
        if (meld[0].value != 0) {
          printMeldJoin(i, meld);
          sort(myHand, myHandCardsQuantity);
          myHandCardsQuantity -= meldQuantity;
          clearMeld(meld, &meldQuantity);
        }
      }
    }

    discardWorstCard(myHand);
    sort(myHand, myHandCardsQuantity);
    myHandCardsQuantity--;

  }

  /*****************************************************************************
   * Fim do programa
   ****************************************************************************/

  return 0;
}