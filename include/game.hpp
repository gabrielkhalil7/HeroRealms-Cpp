#ifndef GAME_H
#define GAME_H
#include "player.hpp"

class Game {
    Player* joueur1, joueur2;
    //Market* marche;
    bool godMode;

public:
    Game();
    ~Game();
    void start() const;
    void playTurn() const;
    bool isFinished() const;
};

#endif