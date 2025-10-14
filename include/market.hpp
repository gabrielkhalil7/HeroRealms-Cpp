#ifndef MARKET_H
#define MARKET_H
#include <vector>

// Forward declarations
class Card;
class ItemCard;

class Market {
    std::vector<Card*> cartesVisibles; // Cartes visibles sur le marché
    std::vector<Card*> piocheDuMarche; // Pioche du marché
    std::vector<ItemCard*> gemmesDeFeu; // Gemmes de feu
    std::vector<Card*> cartesSacrifiees; // Cartes sacrifiées

public:
    Market();
    ~Market();
    Card* getCard(int index);
    Card* buyCard(int index);  // Acheter une carte du marché (la retire des cartes visibles)
    Card* buyGem();
    void refill();
    void display() const;
    void addSacrificedCard(Card* card) { cartesSacrifiees.push_back(card); }
};

#endif