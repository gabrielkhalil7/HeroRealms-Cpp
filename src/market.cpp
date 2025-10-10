#include "../include/market.hpp"
#include "../include/card.hpp"
#include "../include/itemCard.hpp"

Market::Market() {

}

Market::~Market() {

}

Card* Market::getCard(int index) {
    return cartesVisibles[index];
}

Card* Market::buyGem() {
    return gemmesDeFeu.back();
}

void Market::refill() {

}