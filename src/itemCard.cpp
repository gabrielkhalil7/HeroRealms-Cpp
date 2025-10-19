#include "itemCard.hpp"
#include "player.hpp"
#include "game.hpp"
#include <iostream>

// Constructeur
ItemCard::ItemCard(const std::string& n, int c, Faction f, CardId cardId)
    : Card(n, c, f, cardId), goldValue(0), combatValue(0) {
    
    // Configuration spécifique selon le type de CardId
    switch(cardId) {
        case CardId::OR:
            goldValue = 1;
            combatValue = 0;
            description = "Gagne 1 or";
            break;
        case CardId::EPEE_COURTE:
            goldValue = 0;
            combatValue = 2;
            description = "Gagne 2 combat";
            break;
        case CardId::DAGUE:
            goldValue = 0;
            combatValue = 1;
            description = "Gagne 1 combat";
            break;
        case CardId::RUBIS:
            goldValue = 2;
            combatValue = 0;
            description = "Gagne 2 or";
            break;
        case CardId::GEMME_DE_FEU:
            goldValue = 2;
            combatValue = 0;
            description = "Gagne 2 or";
            break;
        default:
            goldValue = 0;
            combatValue = 0;
            description = "Objet inconnu";
            break;
    }
}

// Méthode play - effet principal de la carte
void ItemCard::play(Player* owner, Game* game) {
    (void)game; // Suppress unused parameter warning
    std::cout << "Joue " << name << ": " << description << std::endl;
    
    // Ajouter l'or au joueur
    if (goldValue > 0) {
        owner->addGold(goldValue);
        std::cout << "Le joueur gagne " << goldValue << " or" << std::endl;
    }
    
    // Ajouter le combat au joueur (si applicable)
    if (combatValue > 0) {
        owner->addCombat(combatValue);
        std::cout << "Le joueur gagne " << combatValue << " combat" << std::endl;
    }
}

// Méthode sacrifice - effet de sacrifice de la carte
void ItemCard::sacrifice(Player* owner, Game* game, bool fromEffects) {
    (void)game;  // Suppress unused parameter warning
    (void)fromEffects;  // Suppress unused parameter warning
    std::cout << "Sacrifice " << name << std::endl;
    
    // Effet spécial de sacrifice selon le type de carte
    switch(cardId) {
        case CardId::GEMME_DE_FEU:
            owner->addCombat(3);
            std::cout << "Effet de sacrifice de Gemme de feu: Le joueur gagne 3 combat" << std::endl;
            break;
        default:
            std::cout << "Pas d'effet de sacrifice spécial pour cette carte" << std::endl;
            break;
    }
}

// Méthodes statiques pour créer des cartes spécifiques
ItemCard* ItemCard::createOr() {
    return new ItemCard("Or", 1, Faction::NEUTRE, CardId::OR);
}

ItemCard* ItemCard::createEpeeCourte() {
    return new ItemCard("Épée courte", 4, Faction::NEUTRE, CardId::EPEE_COURTE);
}

ItemCard* ItemCard::createDague() {
    return new ItemCard("Dague", 4, Faction::NEUTRE, CardId::DAGUE);
}

ItemCard* ItemCard::createRubis() {
    return new ItemCard("Rubis", 2, Faction::NEUTRE, CardId::RUBIS);
}

ItemCard* ItemCard::createGemmeDeFeu() {
    return new ItemCard("Gemme de feu", 16, Faction::NEUTRE, CardId::GEMME_DE_FEU);
}
