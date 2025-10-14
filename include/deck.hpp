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
    void addCard(Card* card);  // Ajouter une carte au bas du deck
    void addCardToTop(Card* card);  // Ajouter une carte au-dessus du deck
    Card* drawCard();
    Card* removeCard(Card* cardToRemove);  // Retirer une carte spécifique du deck
    bool isEmpty() const;
    void shuffle();  // Nouvelle méthode pour mélanger le deck
    size_t size() const { return cards.size(); }
    const std::vector<Card*>& getCards() const { return cards; }  // Accès en lecture seule aux cartes
};

#endif  