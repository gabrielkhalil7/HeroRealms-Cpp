#ifndef CHAMPION_CARD_H
#define CHAMPION_CARD_H
#include "card.hpp"

// Forward declarations
class Player;
class Game;

class ChampionCard : public Card {
    protected:
        int goldValue;
        int combatValue;
        int healthValue;
        int defense;
        bool isGuarding;
        bool isActivated;
        
    public:
        ChampionCard(const std::string& n, int c, Faction f, CardId id);
        void play(Player* owner, Game* game) override;
        void sacrifice(Player* owner, Game* game, bool fromEffects = false) override;
        Faction getType() const override { return faction; }
        
        // Méthodes spécifiques aux champions
        virtual void activateAbility(Player* owner, Game* game);
        void takeDamage(int damage);
        bool isAlive() const { return defense > 0; }
        void setGuarding(bool guard) { isGuarding = guard; }
        bool getGuarding() const { return isGuarding; }
        bool getActivated() const { return isActivated; }
        void setActivated(bool activated) { isActivated = activated; }
        

        // Imperial Champions
        static ChampionCard* createArkusDragonImperial();
        static ChampionCard* createDarianMageDeGuerre();
        static ChampionCard* createCristovLeJuste();
        static ChampionCard* createKrakaGrandPretre();
        static ChampionCard* createHommeDArmes();
        static ChampionCard* createMaitreWeyan();
        static ChampionCard* createPercepteurDeDime();
        // Guild Champions
        static ChampionCard* createBorgMercenaireOgre();
        static ChampionCard* createMyrosMageDeLaGuilde();
        static ChampionCard* createParovLExecuteur();
        static ChampionCard* createRakeMaitreAssassin();
        static ChampionCard* createRasmusLeContrebandier();
        static ChampionCard* createBanditDesRues();
        // Necros Champions
        static ChampionCard* createPretreDuCulte();
        static ChampionCard* createCultisteDeLaMort();
        static ChampionCard* createRaylaTisseuseDeFins();
        static ChampionCard* createKrythosMaitreVampire();
        static ChampionCard* createLysLInapparent();
        static ChampionCard* createTyrannorLeDevoreur();
        static ChampionCard* createVarrickLeNecromancien();
        // Wild Champions
        static ChampionCard* createBroelynTisseuseDeSorts();
        static ChampionCard* createCronLeBerserker();
        static ChampionCard* createLoupSinistre();
        static ChampionCard* createGrakGeantDeTempete();
        static ChampionCard* createGrognardOrc();
        static ChampionCard* createTorgenFendRoc();
        static ChampionCard* createChamanLoup();
};
#endif