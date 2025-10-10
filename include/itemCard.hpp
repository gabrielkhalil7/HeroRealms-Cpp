#ifndef ITEMCARD_H
#define ITEMCARD_H

#include "card.hpp"

class ItemCard : public Card {
    protected:
        int goldValue;
        int combatValue;
        ItemCardName itemName;
        
    public:
        ItemCard(const std::string& n, int c, Faction f, ItemCardName itemType);
        void play(Player* owner, Game* game) override;
        CardType getType() const override { return CardType::ITEM; }
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