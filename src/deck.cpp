#include "../include/deck.hpp"
#include "../include/card.hpp"
#include <algorithm>
#include <random>
#include <chrono>

Deck::Deck() {}

Deck::~Deck() {
    for (Card* card : cards) {
        delete card;
    }
}

void Deck::addCard(Card* card) {
    cards.push_back(card);
}

void Deck::addCardToTop(Card* card) {
    cards.push_back(card);  // Ajouter au-dessus de la pioche (fin du vecteur = dessus de la pioche)
}

Card* Deck::drawCard() {
    if (cards.empty()) {
        return nullptr;
    }
    Card* drawnCard = cards.back();
    cards.pop_back();
    return drawnCard;
}

Card* Deck::removeCard(Card* cardToRemove) {
    auto it = std::find(cards.begin(), cards.end(), cardToRemove);
    if (it != cards.end()) {
        cards.erase(it);
        return cardToRemove;
    }
    return nullptr;
}

bool Deck::isEmpty() const {
    return cards.empty();
}

void Deck::shuffle() {
    // Utiliser un générateur basé sur le temps pour plus de randomness
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
}