#include "../include/deck.hpp"
#include "../include/card.hpp"

Deck::Deck() {}

Deck::~Deck() {
    for (Card* card : cards) {
        delete card;
    }
}

void Deck::addCard(Card* card) {
    cards.push_back(card);
}

Card* Deck::drawCard() {
    if (cards.empty()) {
        return nullptr;
    }
    Card* drawnCard = cards.back();
    cards.pop_back();
    return drawnCard;
}

bool Deck::isEmpty() const {
    return cards.empty();
}