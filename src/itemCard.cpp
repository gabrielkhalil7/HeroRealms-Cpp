#include "../include/itemCard.hpp"
#include "../include/player.hpp"
#include "../include/game.hpp"
#include <iostream>

// Constructeur
ItemCard::ItemCard(const std::string& n, int c, Faction f, CardId itemType)
    : Card(n, c, f, itemType), goldValue(0), combatValue(0), itemName(itemType) {
    
    // Configuration spécifique selon le type d'item
    switch(itemType) {
        case CardId::RUBIS:
            goldValue = 2;
            combatValue = 0;
            description = "Gain 2 gold";
            break;
        case CardId::GEMME_DE_FEU:
            goldValue = 1;
            combatValue = 0;
            description = "Gain 1 gold";
            break;
        case CardId::OR:
            goldValue = 1;
            combatValue = 0;
            description = "Gain 1 gold";
            break;
        default:
            goldValue = 0;
            combatValue = 0;
            description = "Item générique";
            break;
    }
}

// Méthode play - effet principal de la carte
void ItemCard::play(Player* owner, Game* /* game */) {
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

void ItemCard::sacrifice(Player* owner, Game* game, bool /*fromEffects*/) {
    // Par défaut, les objets n'ont pas d'effet de sacrifice spécial
    std::cout << name << " sacrifié (aucun effet spécial)" << std::endl;
    owner->removeCardFromPlay(this);
    game->getMarket()->addSacrificedCard(this);
}

// Méthode statique pour créer une carte Ruby
ItemCard* ItemCard::createRuby() {
    return new ItemCard("Ruby", 2, Faction::NEUTRE, CardId::RUBIS);
}
