#ifndef MARKET_H
#define MARKET_H
#include <vector>

// Forward declarations
class Card;
class ItemCard;

class Market {
    std::vector<Card*> cartesVisibles;
    std::vector<Card*> piocheDuMarche;
    std::vector<ItemCard*> gemmesDeFeu;
    std::vector<Card*> cartesSacrifiees;

public:
    Market();
    ~Market();
    Card* getCard(int index);
    Card* buyGem();
    void refill();
    void display() const;
};

#endif