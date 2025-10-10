#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include "faction.hpp"

// Forward declarations
class Market;
class Deck;
class Card;
class ChampionCard;
class Game;

class Player {
    std::string name;
    int health;
    Deck* pioche; // Deck personnel (c'est la que les cartes sont piochées)
    Deck* defausse; // Deck de défausse
    std::vector<Card*> main; // Cartes en main (habituellement 5)
    std::vector<Card*> cartesEnJeu; // Cartes en jeu (actions et objets)
    std::vector<ChampionCard*> championsEnJeu; // Champions en jeu
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
    void playCard(int cardIndex, Game* game);  // Nouvelle méthode pour jouer une carte spécifique
    void attack(Player* cible, int degats);
    //void buyCard(Market* marche, int index);
    
    // Méthodes pour gérer les ressources
    void addGold(int amount);
    void addCombat(int amount);
    void addHealth(int amount);
    
    // Méthodes pour accéder aux cartes en jeu
    const std::vector<Card*>& getCartesEnJeu() const { return cartesEnJeu; }
    const std::vector<ChampionCard*>& getChampionsEnJeu() const { return championsEnJeu; }
    
    // Méthode utilitaire pour compter les cartes d'une faction en jeu
    int countCardsInPlayByFaction(Faction faction) const;
};

#endif  