#include "../include/itemCard.hpp"
#include "../include/player.hpp"
#include "../include/game.hpp"
#include <iostream>

// Constructeur
ItemCard::ItemCard(const std::string& n, int c, Faction f, ItemCardName itemType)
    : Card(n, c, f), itemName(itemType), goldValue(0), combatValue(0) {
    
    // Configuration spécifique selon le type d'item
    switch(itemType) {
        case ItemCardName::RUBY:
            goldValue = 2;
            combatValue = 0;
            description = "Gain 2 gold";
            break;
        case ItemCardName::FIRE_GEM:
            goldValue = 1;
            combatValue = 0;
            description = "Gain 1 gold";
            break;
        case ItemCardName::GOLD:
            goldValue = 1;
            combatValue = 0;
            description = "Gain 1 gold";
            break;
    }
}

// Méthode play - effet principal de la carte
void ItemCard::play(Player* owner, Game* game) {
    std::cout << "Playing " << name << ": " << description << std::endl;
    
    // Ajouter l'or au joueur
    if (goldValue > 0) {
        owner->addGold(goldValue);
        std::cout << "Player gains " << goldValue << " gold" << std::endl;
    }
    
    // Ajouter le combat au joueur (si applicable)
    if (combatValue > 0) {
        owner->addCombat(combatValue);
        std::cout << "Player gains " << combatValue << " combat" << std::endl;
    }
}

// Méthode statique pour créer une carte Ruby
ItemCard* ItemCard::createRuby() {
    return new ItemCard("Ruby", 2, Faction::NEUTRE, ItemCardName::RUBY);
}
