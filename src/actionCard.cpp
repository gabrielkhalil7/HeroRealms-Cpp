#include "../include/actionCard.hpp"
#include "../include/player.hpp"
#include "../include/game.hpp"
#include "../include/championCard.hpp"
#include <iostream>

ActionCard::ActionCard(const std::string& n, int c, Faction f, CardId id) 
    : Card(n, c, f, id), goldValue(0), combatValue(0), healthValue(0) {
}

void ActionCard::play(Player* owner, Game* game) {
    std::cout << owner->getName() << " joue " << name << std::endl;

    // Exécuter l'effet primaire de la carte
    executePrimaryEffect(owner, game);
    
    // Vérifier et exécuter l'effet allié si possible
    if (canActivateAllyEffect(owner)) {
        executeAllyEffect(owner, game);
    }
    
}

void ActionCard::executePrimaryEffect(Player* owner, Game* game) {
    switch (cardId) {
        case CardId::TAXATION:
            taxationPrimaryEffect(owner, game);
            break;
        // Ajouter d'autres cartes ici au fur et à mesure
        default:
            // Effet par défaut basé sur les valeurs de base
            if (goldValue > 0) owner->addGold(goldValue);
            if (combatValue > 0) owner->addCombat(combatValue);
            if (healthValue > 0) owner->addHealth(healthValue);
            break;
    }
}

void ActionCard::executeAllyEffect(Player* owner, Game* game) {
    switch (cardId) {
        case CardId::TAXATION:
            taxationAllyEffect(owner, game);
            break;
        // Ajouter d'autres cartes ici au fur et à mesure
        default:
            // Pas d'effet allié par défaut
            break;
    }
}

bool ActionCard::canActivateAllyEffect(Player* owner) const {
    // Compter le nombre de cartes de la même faction en jeu (y compris cette carte)
    int cardsOfSameFaction = countCardsInPlayByFaction(owner, faction);
    return cardsOfSameFaction >= 2;
}

// === EFFETS SPÉCIFIQUES DE TAXATION ===
void ActionCard::taxationPrimaryEffect(Player* owner, Game* game) {
    owner->addGold(2);
    std::cout << "  Taxation: " << owner->getName() << " gagne 2 gold" << std::endl;
}
void ActionCard::taxationAllyEffect(Player* owner, Game* game) {
    owner->addGold(2);
    std::cout << "  Taxation (Allié Impérial): " << owner->getName() << " gagne 2 gold supplémentaires" << std::endl;
}

// === MÉTHODE UTILITAIRE ===
int ActionCard::countCardsInPlayByFaction(Player* owner, Faction faction) const {
    int count = 0;
    
    // Compter les cartes d'action/objet en jeu
    for (const Card* card : owner->getCartesEnJeu()) {
        if (card->getFaction() == faction) {
            count++;
        }
    }
    
    // Compter les champions en jeu
    for (const ChampionCard* champion : owner->getChampionsEnJeu()) {
        if (champion->getFaction() == faction) {
            count++;
        }
    }
    
    return count;
}