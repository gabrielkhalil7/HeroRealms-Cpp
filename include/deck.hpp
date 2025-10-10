#ifndef DECK_H
#define DECK_H
#include <vector>

// Forward declaration
class Card;

class Deck {
    std::vector<Card*> cards;

public:
    Deck();
    Deck(std::vector<Card*> initialCards) : cards(initialCards) {}
    ~Deck();
    void addCard(Card* card);
    Card* drawCard();
    bool isEmpty() const;
};

#endif  