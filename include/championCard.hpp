class ChampionCard : public Card {
    protected:
        int defense;
        bool isGuarding;
        bool isActivated;
        
    public:
        ChampionCard(const std::string& n, int c, Faction f, int def);
        void play(Player* owner, Game* game) override;
        CardType getType() const override { return CardType::CHAMPION; }
        
        // Méthodes spécifiques aux champions
        virtual void activateAbility(Player* owner, Game* game);
        void takeDamage(int damage);
        bool isAlive() const { return defense > 0; }
        void setGuarding(bool guard) { isGuarding = guard; }
};