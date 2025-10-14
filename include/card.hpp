#ifndef CARD_H
#define CARD_H
#include <string>
#include "faction.hpp"
#include "cardId.hpp"

// Forward declarations pour éviter les dépendances circulaires
class Player;
class Game;

// Classe de base abstraite
class Card {
    protected:
        std::string name;
        int cost;
        Faction faction;
        CardId cardId;
        std::string description;
        
    public:
        Card(const std::string& n, int c, Faction f, CardId id);
        virtual ~Card() = default;
        
        // Getters
        std::string getName() const;
        int getCost() const;
        Faction getFaction() const;
        CardId getCardId() const;
        
        // Méthodes polymorphes
        virtual void play(Player* owner, Game* game) = 0;
        virtual void sacrifice(Player* owner, Game* game, bool fromEffects = false) = 0;
        virtual Faction getType() const = 0;
        virtual std::string getDescription() const;
};
    
#endif