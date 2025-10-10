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
};

#endif