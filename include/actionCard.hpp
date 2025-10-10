class ActionCard : public Card {
    protected:
        int goldValue;
        int combatValue;
        int healthValue;
        
    public:
        ActionCard(const std::string& n, int c, Faction f);
        void play(Player* owner, Game* game) override;
        CardType getType() const override { return CardType::ACTION; }
        virtual void executeEffect(Player* owner, Game* game);
};