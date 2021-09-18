/** @file cards.c
 *  @brief Funções do bot jogador de buraco
 *
 *  Este arquivo contém as funções utilizadas pelo bot jogador de buraco
 *  durante uma partida.
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

/** @brief Lê informações da entrada padrão
 *  @param line String destino para o que foi lido
 */
void readline(char *line) {
  fgets(line, MAX_LINE, stdin);
  int l = strlen(line) - 1;
  if (line[l] == '\n') {
    line[l] = '\0';
  }
}

/** @brief Ordena cartas em ordem crescente de naipe e valor
 *  @param someHand Conjunto de cartas recebido a ser ordenado
 *  @param handLength Quantidade de cartas recebida a serem ordenadas
 */
void sort(Card *someHand, int handLength) {
	Card aux;

  for (int i = 0; i < handLength - 1; i++) {
    for (int j = i + 1; j < handLength; j++) {
      if ((someHand[i].suit == someHand[j].suit &&
           someHand[i].value > someHand[j].value) ||
          someHand[i].suit > someHand[j].suit) {
        aux = someHand[i];
        someHand[i] = someHand[j];
        someHand[j] = aux;
      }
    }
  }
}

/** @brief Retorna o Value correspondente ao(s) caracter(s) recebido(s)
 *  @param strValue Valor da carta recebido em caracter(es) 
 *  @return Valor da carta retornado em Value 
 */
Value strToValue(char *strValue) {
  switch (strValue[0]) {
    case '2': return Two; break;
    case '3': return Three; break;
    case '4': return Four; break;
    case '5': return Five; break;
    case '6': return Six; break;
    case '7': return Seven; break;
    case '8': return Eight; break;
    case '9': return Nine; break;
    case '1': return Ten; break;
    case 'J': return Jack; break;
    case 'Q': return Queen; break;
    case 'K': return King; break;
    case 'A': return Ace; break;
    default: return 0;
  }
}

/** @brief Retorna o Suit correspondente ao símbolo Unicode recebido
 *  @param strSuit Naipe da carta recebido em símbolo Unicode 
 *  @return Naipe da carta retornado em Suit
 */
Suit strToSuit(char *strSuit) {
  if (strcmp(strSuit, "♥") == 0) {
    return Hearts;
  }
  else if (strcmp(strSuit, "♦") == 0) {
    return Diamonds;
  }
  else if (strcmp(strSuit, "♣") == 0) {
    return Clubs;
  }
  else if (strcmp(strSuit, "♠") == 0) {
    return Spades;
  }
  else {
    return NoCard;
  }
}

/** @brief Retorna o(s) caracter(es) correspondente(s) ao Value recebido
 *  @param value Valor da carta recebido em Value 
 *  @return Valor da carta retornado em caracter(es) 
 */
char* valueToStr(Value value) {
  char *strValue = calloc(4, sizeof(char));

  switch (value) {
    case Two: strcpy(strValue, "2"); break;
    case Three: strcpy(strValue, "3"); break;
    case Four: strcpy(strValue, "4"); break;
    case Five: strcpy(strValue, "5"); break;
    case Six: strcpy(strValue, "6"); break;
    case Seven: strcpy(strValue, "7"); break;
    case Eight: strcpy(strValue, "8"); break;
    case Nine: strcpy(strValue, "9"); break;
    case Ten: strcpy(strValue, "10"); break;
    case Jack: strcpy(strValue, "J"); break;
    case Queen: strcpy(strValue, "Q"); break;
    case King: strcpy(strValue, "K"); break;
    case Ace: strcpy(strValue, "A"); break;
    default: strcpy(strValue, "0");
  }

  return strValue;
}

/** @brief Retorna o símbolo Unicode correspondente ao Suit recebido 
 *  @param suit Naipe da carta recebido em Suit 
 *  @return Naipe da carta retornado em símbolo Unicode 
 */
char* suitToStr(Suit suit) {
  char *strSuit = calloc(4, sizeof(char));

  if (suit == Hearts) {
    strcpy(strSuit, "♥");
  }
  else if (suit == Diamonds) {
    strcpy(strSuit, "♦");
  }
  else if (suit == Clubs) {
    strcpy(strSuit, "♣");
  }
  else if (suit == Spades) {
    strcpy(strSuit, "♠");
  }
  else {
    strcpy(strSuit, "0");
  }

  return strSuit;
}

/** @brief Retorna a carta correspondente à string recebida
 *  @param cardInfos String de valor e naipe de uma carta
 *  @return Carta com o valor e o naipe recebidos
 */
Card strToCard(char *cardInfos) {
  Card myCard = {0};
  char strValue[3];
  char strSuit[4];

  if (cardInfos[0] == '1') {
    strncpy(strValue, cardInfos, 2);
    strcpy(strSuit, &cardInfos[2]);
  } 
  else {
    strncpy(strValue, cardInfos, 1);
    strcpy(strSuit, &cardInfos[1]);
  }

  myCard.value = strToValue(strValue);
  myCard.suit = strToSuit(strSuit);

  return myCard;
}

/** @brief Obtém cartas recebidas em forma de string
 *  @param line String que contém cartas
 *  @param myHand Conjunto de cartas destino das cartas recebidas
 *  @param handLength Número de cartas da myHand
 */
void getCards(char *line, Card *myHand, int *handLength) {
  char *cardInfos = strtok(line, "[] ");
  while (cardInfos != NULL) {
    myHand[*handLength] = strToCard(cardInfos);
    (*handLength)++;
    cardInfos = strtok(NULL, "[] ");
  }
}

/** @brief Obtém uma trinca de cartas de um conjunto de cartas recebido
 *  @param topTrashCard Carta a formar uma trinca com as demais
 *  @param myHand Conjunto de cartas recebido
 *  @param meld Conjunto de cartas destino da trinca obtida 
 *  @param meldQuantity Número de cartas da meld
 */
void formTriple(Card topTrashCard, Card *myHand, Card *meld, int *meldQuantity) {
  for (int i = 0; i < MAX_HAND - 1; i++) {
    Suit suit1 = myHand[i].suit;
    Suit suit2 = myHand[i + 1].suit;
    Suit suit3 = topTrashCard.suit;
    Value value1 = myHand[i].value;
    Value value2 = myHand[i + 1].value;
    Value value3 = topTrashCard.value;

    bool sameSuit = suit1 == suit2 && suit2 == suit3;
    bool sequence1 = value1 + 1 == value2 && value2 == value3 - 1;
    bool sequence2 = value1 + 1 == value3 && value3 == value2 - 1;
    bool sequence3 = value3 + 1 == value1 && value1 == value2 - 1;

    if (sameSuit && sequence1) {
      meld[0] = myHand[i];
      meld[1] = myHand[i + 1];
      meld[2] = topTrashCard;
 
      myHand[i].value = 0;
      myHand[i].suit = NoCard;
      myHand[i + 1].value = 0;
      myHand[i + 1].suit = NoCard;
      (*meldQuantity) += 2;
      break;
    }
    else if (sameSuit && sequence2) {
      meld[0] = myHand[i];
      meld[1] = topTrashCard;
      meld[2] = myHand[i + 1];

      myHand[i].value = 0;
      myHand[i].suit = NoCard;
      myHand[i + 1].value = 0;
      myHand[i + 1].suit = NoCard;
      (*meldQuantity) += 2;
      break;
    }
    else if (sameSuit && sequence3) {
      meld[0] = topTrashCard;
      meld[1] = myHand[i];
      meld[2] = myHand[i + 1];
 
      myHand[i].value = 0;
      myHand[i].suit = NoCard; 
      myHand[i + 1].value = 0;
      myHand[i + 1].suit = NoCard;
      (*meldQuantity) += 2;
      break;
    }
  }
}

/** @brief Obtém uma sequência de cartas de um conjunto de cartas recebido
 *  @param myHand Conjunto de cartas recebido
 *  @param meld Conjunto de cartas destino da sequência obtida 
 *  @param meldQuantity Número de cartas da meld
 */
void formMeld(Card *myHand, Card *meld, int *meldQuantity) {
  /** Checar se há sucessor */
  int index = 2;
  for (int i = 0; i < MAX_HAND; i++) {
    if (meld[index].value + 1 == myHand[i].value &&
        meld[index].suit == myHand[i].suit) {
      /** Adiciona sucessor */
      index++;
      (*meldQuantity)++;
      meld[index] = myHand[i];
      myHand[i].value = 0;
      myHand[i].suit = NoCard;
    }
  }

  /** Checar se há antecessor */
  int lastIndex = index + 1;
  index = 0;
  for (int i = MAX_HAND - 1; i >= 0; i--) {
    if (meld[index].value - 1 == myHand[i].value &&
        meld[index].suit == myHand[i].suit) {
      /** Adiciona antecessor */
      if (index == 0) {
        index = lastIndex;
      } 
      else {
        index++;
      }
      (*meldQuantity)++;
      meld[index] = myHand[i];
      myHand[i].value = 0;
      myHand[i].suit = NoCard;
    }
  }

  sort(meld, (*meldQuantity) + 1);
}

/** @brief Imprime GET_DISCARD
 *  @param topTrashCard Carta do topo do lixo a fazer sequência com as do meld
 *  @param meld Conjunto de cartas em sequência
 */
void printGetDiscard(Card topTrashCard, Card meld[]) {
  char *strValue;
  char *strSuit;
  
  printf("GET_DISCARD [ ");
  for (int i = 0; i < MAX_MELD; i++) {
    if (meld[i].value != topTrashCard.value && meld[i].value != 0) {
      strValue = valueToStr(meld[i].value);
      strSuit = suitToStr(meld[i].suit);

      printf("%s%s ", strValue, strSuit);

      free(strValue);
      free(strSuit);
    }
  }
  printf("]\n");
}

/** @brief Armazena um novo jogo baixado 
 *  @param droppedMelds Matriz dos jogos já baixados 
 *  @param droppedMeldsQuantity Quantidade de jogos já baixados
 *  @param meld Novo jogo a ser baixado
 */
Card** dropNewMeld(Card **droppedMelds, int *droppedMeldsQuantity, Card *meld) {
  /** Aloca um espaço para o jogo baixado */
  (*droppedMeldsQuantity)++;
  droppedMelds = realloc(droppedMelds, sizeof(Card*) * (*droppedMeldsQuantity));
  droppedMelds[*droppedMeldsQuantity - 1] = calloc(MAX_MELD, sizeof(Card));
  
  /** Guarda o jogo baixado no espaço alocado */
  for (int i = 0; i < MAX_MELD; i++) {
    droppedMelds[*droppedMeldsQuantity - 1][i] = meld[i];
  }
  
  return droppedMelds;
}

/** @brief Descarta uma carta da mão
 *  @param myHand Conjunto de cartas recebido
 */
void discardWorstCard(Card myHand[]) {
  Card worstCard = myHand[0];
  int  maxCardsDifference = 0;

  for (int i = 0; i < MAX_HAND - 1; i++) {
    if (myHand[i + 1].suit == myHand[i].suit &&
        myHand[i + 1].value - myHand[i].value > maxCardsDifference) {
      maxCardsDifference = myHand[i + 1].value - myHand[i].value;
      worstCard = myHand[i];
    }
  }

  for (int i = 0; i < MAX_HAND; i++) {
    if (myHand[i].suit == worstCard.suit &&
        myHand[i].value == worstCard.value) {
      myHand[i].value = 0;
      myHand[i].suit = NoCard;
      break;
    }
  }
  
  char *strValue = valueToStr(worstCard.value);
  char *strSuit = suitToStr(worstCard.suit);

  printf("DISCARD %s%s\n", strValue, strSuit);

  free(strValue);
  free(strSuit);
}

/** @brief Retorna a quantidade de cartas de um conjunto de cartas 
 *  @param setOfCards Conjunto de cartas a ser contado
 *  @param length Tamanho do setOfCards
 */
int countCards(Card *setOfCards, int length) {
  int cardsQuantity = 0;

  for (int i = 0; i < length; i++) {
    if (setOfCards[i].suit != NoCard && setOfCards[i].value != 0) {
      cardsQuantity++;
    }
  }

  return cardsQuantity;
}

/** @brief Adiciona uma carta no ínicio de um conjunto de cartas ordenado
 *  @param originSet Conjunto de cartas origem da carta a ser adicionada
 *  @param destinySet Conjunto de cartas destino da carta a ser adicionada
 *  @param meld Conjunto das cartas que foram adicionadas
 *  @param meldCardsQuantity Quantidade de cartas adicionadas
 */
void addFirst(Card *originSet, Card *destinySet,
              Card *meld, int *meldCardsQuantity) {
  int destinyCardsQuantity = countCards(destinySet, MAX_MELD);
  Card firstCard = destinySet[0];
  Card cardToAdd;

  if (destinyCardsQuantity < MAX_MELD) {
    for (int i = 0; i < MAX_HAND; i++) {
      cardToAdd = originSet[i];

      if (cardToAdd.suit == firstCard.suit &&
          cardToAdd.value + 1 == firstCard.value) {
        for (int i = destinyCardsQuantity; i > 0; i--) {
          destinySet[i] = destinySet[i - 1];
        }

        firstCard = cardToAdd;
        destinySet[0] = cardToAdd;
        meld[*meldCardsQuantity] = cardToAdd;
        (*meldCardsQuantity)++;
        originSet[i].value = 0;
        originSet[i].suit = NoCard;
      }
    }
  }
}

/** @brief Adiciona uma carta no final de um conjunto de cartas ordenado
 *  @param originSet Conjunto de cartas origem da carta a ser adicionada
 *  @param destinySet Conjunto de cartas destino da carta a ser adicionada
 *  @param meld Conjunto das cartas que foram adicionadas
 *  @param meldCardsQuantity Quantidade de cartas adicionadas
 */
void addLast(Card *originSet, Card *destinySet,
             Card *meld, int *meldCardsQuantity) {
  int destinyCardsQuantity = countCards(destinySet, MAX_MELD);
  Card lastCard = destinySet[destinyCardsQuantity - 1];
  Card cardToAdd;

  if (destinyCardsQuantity < MAX_MELD) {
    for (int i = 0; i < MAX_HAND; i++) {
      cardToAdd = originSet[i];
      
      if (cardToAdd.suit == lastCard.suit &&
          cardToAdd.value - 1 == lastCard.value) {
        lastCard = cardToAdd;
        destinySet[destinyCardsQuantity] = cardToAdd;
        destinyCardsQuantity++;
        meld[*meldCardsQuantity] = cardToAdd;
        (*meldCardsQuantity)++;
        originSet[i].value = 0;
        originSet[i].suit = NoCard;
      }
    }
  }
}

/** @brief Imprime o MELD_JOIN
 *  @param droppedMeldIndex Índice do conjunto no qual as cartas serão adicionadas
 *  @param meld Conjunto das cartas a serem imprimidas
 */
void printMeldJoin(int droppedMeldIndex, Card meld[]) {
  char *strValue;
  char *strSuit;
  
  printf("MELD_JOIN %i [ ", droppedMeldIndex);
  for (int i = 0; i < MAX_MELD; i++) {
    if (meld[i].value != 0 && meld[i].suit != NoCard) {
      strValue = valueToStr(meld[i].value);
      strSuit = suitToStr(meld[i].suit);

      printf("%s%s ", strValue, strSuit);

      free(strValue);
      free(strSuit);
    }
  }
  printf("]\n");
}

/** @brief Imprime o MELD_NEW
 *  @param meld Conjunto das cartas a serem imprimidas
 */
void printMeldNew(Card meld[]) {
  char *strValue;
  char *strSuit;
  
  printf("MELD_NEW [ ");
  for (int i = 0; i < MAX_MELD; i++) {
    if (meld[i].value != 0 && meld[i].suit != NoCard) {
      strValue = valueToStr(meld[i].value);
      strSuit = suitToStr(meld[i].suit);

      printf("%s%s ", strValue, strSuit);

      free(strValue);
      free(strSuit);
    }
  }
  printf("]\n");
}

/** @brief Reseta um conjunto de cartas
 *  @param meld Conjunto das cartas a ser resetado
 *  @param meldCardQuantity Quantidade de cartas do meld
 */
void clearMeld(Card *meld, int *meldCardQuantity) {
  for (int i = 0; i < MAX_MELD; i++) {
    meld[i].value = 0;
    meld[i].suit = NoCard;
  }
  *meldCardQuantity = 0;
}