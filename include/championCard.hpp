#ifndef CHAMPION_CARD_H
#define CHAMPION_CARD_H
#include "card.hpp"

// Forward declarations
class Player;
class Game;

class ChampionCard : public Card {
    protected:
        int defense;
        bool isGuarding;
        bool isActivated;
        
    public:
        ChampionCard(const std::string& n, int c, Faction f, CardId id, int def);
        void play(Player* owner, Game* game) override;
        Faction getType() const override { return faction; }
        
        // Méthodes spécifiques aux champions
        virtual void activateAbility(Player* owner, Game* game);
        void takeDamage(int damage);
        bool isAlive() const { return defense > 0; }
        void setGuarding(bool guard) { isGuarding = guard; }
};
#endif