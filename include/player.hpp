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
    bool nextActionCardToTopOfDeck; // Flag pour l'effet Pot-de-Vin
    bool nextAnyCardToTopOfDeck; // Flag pour l'effet Fourberie


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
    std::vector<ChampionCard*>& getChampionsEnJeu() { return championsEnJeu; }
    const std::vector<Card*>& getHand() const { return main; }  // Accéder à la main
    
    // Méthode utilitaire pour compter les cartes d'une faction en jeu
    int countCardsInPlayByFaction(Faction faction) const;
    
    // Méthodes pour retirer des cartes
    void removeCardFromHand(Card* card);
    void removeCardFromPlay(Card* card);
    
    // Méthode helper pour les tests
    void addCardToPlay(Card* card);
    
    // Méthodes pour l'effet Pot-de-Vin
    void setNextActionCardToTopOfDeck(bool value) { nextActionCardToTopOfDeck = value; }
    bool isNextActionCardToTopOfDeck() const { return nextActionCardToTopOfDeck; }
    void addCardToTopOfDeck(Card* card);  // Nouvelle méthode pour ajouter une carte au-dessus de la pioche
    
    // Méthodes pour l'effet Fourberie
    void setNextAnyCardToTopOfDeck(bool value) { nextAnyCardToTopOfDeck = value; }
    bool isNextAnyCardToTopOfDeck() const { return nextAnyCardToTopOfDeck; }
    
    // Méthodes pour assommer des champions
    void stunChampion(ChampionCard* champion);  // Assommer un champion (l'envoyer en défausse)
    std::vector<ChampionCard*> getTargetableChampions() const;  // Obtenir les champions attaquables (selon règles des Gardes)
    bool hasGuardingChampions() const;  // Vérifier s'il y a des champions avec Garde
    
    // Méthodes de combat
    void useCombat(int amount);  // Utiliser une certaine quantité de Combat
    void takeDamage(int damage);  // Subir des dégâts
    
    // Méthodes pour accéder à la défausse
    const std::vector<Card*>& getDiscardPile() const;
    void addToDiscardPile(Card* card);  // Ajouter une carte à la défausse
    void removeCardFromDiscard(Card* card);  // Retirer une carte de la défausse
    Card* moveCardFromDiscardToTopOfDeck(Card* card);  // Retirer une carte de la défausse et la mettre au-dessus de la pioche
};

#endif  