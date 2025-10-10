#ifndef ACTION_CARD_H
#define ACTION_CARD_H
#include "card.hpp"

class ActionCard : public Card {
    protected:
        // Ces valeurs seront utilisées pour les effets de base
        int goldValue;
        int combatValue;
        int healthValue;
        
    public:
        ActionCard(const std::string& n, int c, Faction f, CardId id);
        void play(Player* owner, Game* game) override;
        Faction getType() const override { return faction; }
        
        // Méthodes pour gérer les effets spécifiques des cartes
        void executePrimaryEffect(Player* owner, Game* game);
        void executeAllyEffect(Player* owner, Game* game);
        bool canActivateAllyEffect(Player* owner) const;
        
    private:
        // Effets spécifiques pour chaque carte
        void taxationPrimaryEffect(Player* owner, Game* game);
        void taxationAllyEffect(Player* owner, Game* game);
        
        // Fonction utilitaire pour compter les cartes d'une faction en jeu
        int countCardsInPlayByFaction(Player* owner, Faction faction) const;
};

#endif