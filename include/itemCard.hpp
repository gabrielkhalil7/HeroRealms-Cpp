class ItemCard : public Card {
    protected:
        int goldValue;
        int combatValue;
        
    public:
        ItemCard(const std::string& n, int c, Faction f);
        void play(Player* owner, Game* game) override;
        CardType getType() const override { return CardType::ITEM; }
        virtual void sacrifice(Player* owner, Game* game);
};