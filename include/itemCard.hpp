#ifndef ITEM_CARD_H
#define ITEM_CARD_H
#include "card.hpp"

// Forward declarations
class Player;
class Game;

class ItemCard : public Card {
    protected:
        int goldValue;
        int combatValue;
        
    public:
        ItemCard(const std::string& n, int c, Faction f, CardId id);
        void play(Player* owner, Game* game) override;
        Faction getType() const override { return faction; }
        virtual void sacrifice(Player* owner, Game* game);
};

#endif