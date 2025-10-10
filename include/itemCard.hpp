#ifndef ITEMCARD_H
#define ITEMCARD_H

#include "card.hpp"

// Forward declarations
class Player;
class Game;


class ItemCard : public Card {
    protected:
        int goldValue;
        int combatValue;
        ItemCardName itemName;
        
    public:
        ItemCard(const std::string& n, int c, Faction f, ItemCardName itemType);
        void play(Player* owner, Game* game) override;
        Faction getType() const override { return faction; }
        virtual void sacrifice(Player* owner, Game* game);
        
        // Getter pour le type d'item
        ItemCardName getItemName() const { return itemName; }
        
        // Méthodes pour obtenir les valeurs
        int getGoldValue() const { return goldValue; }
        int getCombatValue() const { return combatValue; }
        
        // Méthode statique pour créer des cartes spécifiques
        static ItemCard* createRuby();
};

#endif