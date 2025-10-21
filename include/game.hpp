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
    
    // Méthodes pour les actions du joueur
    void playCardFromHand(Player* currentPlayer);
    void readCardDescription(Player* currentPlayer);
    void buyCardFromMarket(Player* currentPlayer);
    void attackTarget(Player* currentPlayer);
    void sacrificeCard(Player* currentPlayer);
    void useChampionAbility(Player* currentPlayer);
    
    // Fonction utilitaire pour une saisie sécurisée
    static int getSafeInput(int min = 0, int max = 100);
    
    // getters et setters
    Player* getJoueur1() const { return joueur1; }
    Player* getJoueur2() const { return joueur2; }
    Player* getOpponent(Player* player) const;  // Nouvelle méthode pour obtenir l'adversaire
    Market* getMarket() const { return marche; }
    bool isGodMode() const { return godMode; }
    void setGodMode(bool mode) { godMode = mode; }
};

#endif