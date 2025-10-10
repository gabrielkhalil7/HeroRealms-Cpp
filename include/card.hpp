// Classe de base abstraite
class Card {
    protected:
        std::string name;
        int cost;
        Faction faction;
        std::string description;
        
    public:
        Card(const std::string& n, int c, Faction f);
        virtual ~Card() = default;
        
        // Getters
        std::string getName() const;
        int getCost() const;
        Faction getFaction() const;
        
        // Méthodes polymorphes
        virtual void play(Player* owner, Game* game) = 0;
        virtual CardType getType() const = 0;
        virtual std::string getDescription() const;
};
    