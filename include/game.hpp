#ifndef GAME_H
#define GAME_H
#include "player.hpp"
#include "market.hpp"

class Game {
    Player* joueur1;
    Player* joueur2;
    Market* marche;
    bool godMode;

public:
    Game(const std::string& player1Name, const std::string& player2Name);
    ~Game();
    void start();
    void playTurn(Player* currentPlayer);
    bool isFinished() const;
    // getters et setters
    Player* getJoueur1() const { return joueur1; }
    Player* getJoueur2() const { return joueur2; }
    Market* getMarket() const { return marche; }
    bool isGodMode() const { return godMode; }
    void setGodMode(bool mode) { godMode = mode; }
};

#endif