#include "../include/itemCard.hpp"
#include "../include/faction.hpp"
#include <iostream>
#include <memory>



// Mock classes simples pour les tests
class MockPlayer {
private:
    int gold;
    int combat;
    
public:
    MockPlayer() : gold(0), combat(0) {}
    
    void addGold(int amount) {
        gold += amount;
        std::cout << "MockPlayer: Gold increased by " << amount << " (Total: " << gold << ")" << std::endl;
    }
    
    void addCombat(int amount) {
        combat += amount;
        std::cout << "MockPlayer: Combat increased by " << amount << " (Total: " << combat << ")" << std::endl;
    }
    
    int getGold() const { return gold; }
    int getCombat() const { return combat; }
};

class MockGame {
public:
    MockGame() {}
    void someGameMethod() {
        std::cout << "MockGame: Game method called" << std::endl;
    }
};

int main() {
    std::cout << "=== Test de la carte Ruby ===" << std::endl;
    
    // Créer une carte Ruby
    std::unique_ptr<ItemCard> ruby(ItemCard::createRuby());
    
    // Afficher les informations de la carte
    std::cout << "\nInformations de la carte:" << std::endl;
    std::cout << "Nom: " << ruby->getName() << std::endl;
    std::cout << "Coût: " << ruby->getCost() << std::endl;
    std::cout << "Faction: " << static_cast<int>(ruby->getFaction()) << std::endl;
    std::cout << "Description: " << ruby->getDescription() << std::endl;
    std::cout << "Valeur en or: " << ruby->getGoldValue() << std::endl;
    std::cout << "Valeur en combat: " << ruby->getCombatValue() << std::endl;
    std::cout << "Type d'item: " << static_cast<int>(ruby->getItemName()) << std::endl;
    
    // Créer des objets mock pour le test
    MockPlayer player;
    MockGame game;
    
    std::cout << "\nÉtat initial du joueur:" << std::endl;
    std::cout << "Or: " << player.getGold() << std::endl;
    std::cout << "Combat: " << player.getCombat() << std::endl;
    
    // Tester la méthode play
    std::cout << "\nJouer la carte Ruby:" << std::endl;
    ruby->play(reinterpret_cast<Player*>(&player), reinterpret_cast<Game*>(&game));
    
    std::cout << "\nÉtat final du joueur:" << std::endl;
    std::cout << "Or: " << player.getGold() << std::endl;
    std::cout << "Combat: " << player.getCombat() << std::endl;
    
    // Tester la méthode sacrifice
    std::cout << "\nTester le sacrifice:" << std::endl;
    ruby->sacrifice(reinterpret_cast<Player*>(&player), reinterpret_cast<Game*>(&game));
    
    std::cout << "\n=== Test terminé ===" << std::endl;
    
    return 0;
}
