#ifndef MARKET_H
#define MARKET_H
#include <vector>

class Market {
    //std::vector<Card*> cartesVisibles;
    //std::vector<Card*> piocheDuMarche;
    //std::vector<ItemCard*> gemmesDeFeu;

public:
    Market();
    ~Market();
    //Card* getCard(int index);
    //Card* buyGem();
    void refill();
};

#endif