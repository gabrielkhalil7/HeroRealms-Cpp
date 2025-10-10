#include "../include/card.hpp"

Card::Card(const std::string& n, int c, Faction f, CardId id) 
    : name(n), cost(c), faction(f), cardId(id) {
}

std::string Card::getName() const {
    return name;
}

int Card::getCost() const {
    return cost;
}

Faction Card::getFaction() const {
    return faction;
}

CardId Card::getCardId() const {
    return cardId;
}

std::string Card::getDescription() const {
    return description;
}