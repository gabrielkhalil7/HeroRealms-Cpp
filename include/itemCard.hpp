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
        
    public:
        ItemCard(const std::string& n, int c, Faction f, CardId cardId);
        void play(Player* owner, Game* game) override;
        Faction getType() const override { return faction; }
        void sacrifice(Player* owner, Game* game, bool fromEffects = false) override;
        
        // Méthodes pour obtenir les valeurs
        int getGoldValue() const { return goldValue; }
        int getCombatValue() const { return combatValue; }
        
        // Méthodes statiques pour créer des cartes spécifiques
        static ItemCard* createOr();
        static ItemCard* createEpeeCourte();
        static ItemCard* createDague();
        static ItemCard* createRubis();
        static ItemCard* createGemmeDeFeu();
};

#endif