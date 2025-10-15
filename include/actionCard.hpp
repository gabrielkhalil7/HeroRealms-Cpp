#ifndef ACTION_CARD_H
#define ACTION_CARD_H
#include "card.hpp"

// Forward declarations
class ChampionCard;

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
        void sacrifice(Player* owner, Game* game, bool fromEffects = false);
        
        // Méthodes pour gérer les effets spécifiques des cartes
        void executePrimaryEffect(Player* owner, Game* game);
        void genericPlayEffect(Player* owner);
        void executeAllyEffect(Player* owner, Game* game);
        bool canActivateAllyEffect(Player* owner) const;
        
    private:
        // Effets spécifiques pour chaque carte
        void taxationAllyEffect(Player* owner, Game* game);
        void serrerLesRangsPrimaryEffect(Player* owner, Game* game);
        void serrerLesRangsAllyEffect(Player* owner, Game* game);
        void recrutementPrimaryEffect(Player* owner, Game* game);
        void recrutementAllyEffect(Player* owner, Game* game);
        void intimidationAllyEffect(Player* owner, Game* game);
        void beneficeAllyEffect(Player* owner, Game* game);
        void commandementPrimaryEffect(Player* owner, Game* game);
        void dominationPrimaryEffect(Player* owner, Game* game);
        void dominationAllyEffect(Player* owner, Game* game);
        void ralliementDesTroupesAllyEffect(Player* owner, Game* game);
        void paroleDePuissancePrimaryEffect(Player* owner, Game* game);
        void paroleDePuissanceAllyEffect(Player* owner, Game* game);
        void potDeVinAllyEffect(Player* owner, Game* game);
        void menaceDeMortPrimaryEffect(Player* owner, Game* game);
        void menaceDeMortAllyEffect(Player* owner, Game* game);
        void fourberiePrimaryEffect(Player* owner, Game* game);
        void fourberieAllyEffect(Player* owner, Game* game);
        void bombeIncendiairePrimaryEffect(Player* owner, Game* game);
        void miseAPrixAllyEffect(Player* owner, Game* game);
        void casserEtPillerPrimaryEffect(Player* owner, Game* game);
        void energieSombreAllyEffect(Player* owner, Game* game);
        void sombreRecompensePrimaryEffect(Player* owner, Game* game);
        void sombreRecompenseAllyEffect(Player* owner, Game* game);
        void drainDeViePrimaryEffect(Player* owner, Game* game);
        void drainDeVieAllyEffect(Player* owner, Game* game);
        void contactMortelPrimaryEffect(Player* owner, Game* game);
        void contactMortelAllyEffect(Player* owner, Game* game);
        void laPutrefactionPrimaryEffect(Player* owner, Game* game);
        void laPutrefactionAllyEffect(Player* owner, Game* game);
        void maledictionElfiquePrimaryEffect(Player* owner, Game* game);
        void maledictionElfiqueAllyEffect(Player* owner, Game* game);
        void donElfiquePrimaryEffect(Player* owner, Game* game);
        void donElfiqueAllyEffect(Player* owner, Game* game);
        void donDeLaNaturePrimaryEffect(Player* owner, Game* game);
        void donDeLaNatureAllyEffect(Player* owner, Game* game);
        void sauvageriePrimaryEffect(Player* owner, Game* game);
        void etincellePrimaryEffect(Player* owner, Game* game);
        void etincelleAllyEffect(Player* owner, Game* game);
        void formeDeLoupPrimaryEffect(Player* owner, Game* game);

        // Fonction utilitaire pour compter les cartes d'une faction en jeu
        int countCardsInPlayByFaction(Player* owner, Faction faction) const;
        int countChampionsInPlay(Player* owner) const;
        int countActivatedChampionsInPlay(Player* owner) const;
        ChampionCard* chooseChampionToReady(Player* owner) const;
        ChampionCard* chooseChampionToStun(Player* opponent) const;  // Choisir un champion adverse à assommer
        Card* chooseCardFromDiscard(Player* owner) const;  // Choisir une carte de la défausse
        Card* chooseCardToSacrifice(Player* owner) const;  // Choisir une carte à sacrifier (main ou défausse)
        Card* chooseCardFromOpponentHand(Player* opponent) const;  // Choisir une carte de la main de l'adversaire
        Card* chooseCardFromOwnHand(Player* owner) const;  // Choisir une carte de sa propre main
        void sacrificeChosenCard(Player* owner, Game* game, Card* cardToSacrifice) const;  // Gérer le sacrifice d'une carte choisie
};

#endif