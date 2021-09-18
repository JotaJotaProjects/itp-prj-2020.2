/**
 * @file cards.h
 * @brief Assinaturas de funções e declarações de constantes e tipos
 *
 *  @author João Pedro Fonseca Dantas
 *  @author João Guilherme Lopes Alves da Costa
 *  @see https://github.com/amccampos/itp-prj-2020.2
 */

#ifndef CARDS_H
#define CARDS_H

/******************************************************************************
 * Constantes
 *****************************************************************************/

/** Tamanho máximo de uma linha da entrada-padrão */
#define MAX_LINE 530
/** Tamanho máximo do identificador do bot */
#define ID_SIZE 20
/** Tamanho máximo de uma mão de cartas */
#define MAX_HAND 104
/** Tamanho máximo de um jogo do mesmo naipe */
#define MAX_MELD 14

/******************************************************************************
 * Tipos
 *****************************************************************************/

typedef enum {
	Two = 2, Three, Four,
  Five, Six, Seven,
  Eight, Nine, Ten,
  Jack, Queen, King, Ace
} Value;

typedef enum {
	Hearts, Diamonds, Clubs, Spades, NoCard
} Suit;

typedef struct {
	Value value;
	Suit suit;
} Card;

/******************************************************************************
 * Assinaturas de funções
 *****************************************************************************/

void   readline(char *line);
void   sort(Card *someHand, int handLength);
Value  strToValue(char *strValue);
Suit   strToSuit(char *strSuit);
char*  valueToStr(Value value);
char*  suitToStr(Suit suit);
Card   strToCard(char *cardInfos);
void   getCards(char *line, Card *myHand, int *handLength);
void   formTriple(Card topTrashCard, Card *myHand, Card *meld,
                  int *meldQuantity);
void   formMeld(Card *myHand, Card *meld, int *meldQuantity);
void   printGetDiscard(Card topTrashCard, Card meld[]);
Card** dropNewMeld(Card **droppedMelds, int *droppedMeldsQuantity, Card *meld);
void discardWorstCard(Card myHand[]);
int countCards(Card *setOfCards, int length);
void addFirst(Card *originSet, Card *destinySet, Card *meld, int *meldCardsQuantity);
void addLast(Card *originSet, Card *destinySet, Card *meld, int *meldCardsQuantity);
void printMeldJoin(int droppedMeldIndex, Card meld[]);
void printMeldNew(Card meld[]);
void clearMeld(Card *meld, int *meldCardQuantity);

#endif