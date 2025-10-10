#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "market.hpp"

class Player {
    std::string name;
    int health;
    //Deck* pioche;
    //Deck* defausse;
    //vector<Card*> main
    //vector<ChampionCard*> championsEnJeu;
    int goldReserve;
    int combatReserve;


public:
    Player(std::string nom);
    ~Player();
    std::string getName() const { return name; }
    int getHealth() const { return health; }
    int getCombat() const { return combatReserve; }
    int getGold() const { return goldReserve; }
    void initializeDeck();
    void showHand() const;
    void playCards();
    void buyCard(Market& market, bool godMode = false);
    void endTurn();
    void draw(int n);
    //void playCard(Card* c);
    void attack(Player* cible, int degats);
    //void buyCard(Market* marche, int index);
};

#endif