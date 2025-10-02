#ifndef PLAYER_H
#define PLAYER_H
#include <string>

class Player {
    std::string name;
    int health;
    //Deck* pioche;
    //Deck* defausse;
    //vector<Card*> main
    //vector<Champion*> championsEnJeu;
    int goldReserve;
    int combatReserve;


public:
    Player(std::string nom);
    ~Player();
    void draw(int n);
    //void playCard(Card* c;
    void attack(Player* cible, int degats);
    //void buyCard(Market* marche, int index);
};

#endif