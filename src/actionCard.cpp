#include "../include/actionCard.hpp"
#include "../include/player.hpp"
#include "../include/game.hpp"
#include "../include/championCard.hpp"
#include <iostream>

ActionCard::ActionCard(const std::string& n, int c, Faction f, CardId id) 
    : Card(n, c, f, id), goldValue(0), combatValue(0), healthValue(0) {
        // initialisation des descriptions
        switch (id) {
            case CardId::TAXATION:
                description = "Gagnez 2 Or. Si vous avez un autre allié Impérial en jeu, gagnez 6 Santé supplémentaires.";
                goldValue = 2;
                break;
            case CardId::SERRER_LES_RANGS:
                description = "Gagnez 5 Combat. +2 Combat par champion actuellement en jeu. Si vous avez un autre allié Impérial en jeu, gagnez 6 Santé supplémentaires.";
                combatValue = 5;
                break;
            case CardId::RECRUTEMENT:
                description = "Gagnez 2 Or et 3 Santé. +1 Santé par champion actuellement en jeu. Si vous avez un autre allié Impérial en jeu, gagnez 1 Or supplémentaire.";
                goldValue = 2;
                healthValue = 3;
                break;
            case CardId::INTIMIDATION:
                description = "Gagnez 5 Combat. Si vous avez un autre allié de la Guilde en jeu, gagnez 2 Or supplémentaires.";
                combatValue = 5;
                break;
            case CardId::BENEFICE:
                description = "Gagnez 2 Or. Si vous avez un autre allié de la Guilde en jeu, gagnez 4 Combat supplémentaires.";
                goldValue = 2;
                break;
            case CardId::INFLUENCE:
                description = "Gagnez 3 Or. Si vous sacrifiez la carte, vous gagnez 3 Combat supplémentaires.";
                goldValue = 3;
                break;

            default:
                description = "Carte d'action générique.";
                break;
        }
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
            genericPlayEffect(owner); //+2 gold
            break;
        case CardId::SERRER_LES_RANGS:
            serrerLesRangsPrimaryEffect(owner, game); //+5 combat +2 par champion
            break;
        case CardId::RECRUTEMENT:
            recrutementPrimaryEffect(owner, game); //+2 gold +3 santé +1 santé par champion
            break;
        case CardId::INTIMIDATION:
            genericPlayEffect(owner); //+5 combat
            break;
        case CardId::BENEFICE:
            genericPlayEffect(owner); //+2 gold
            break;
        case CardId::INFLUENCE:
            genericPlayEffect(owner); //+3 gold
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
        case CardId::SERRER_LES_RANGS:
            serrerLesRangsAllyEffect(owner, game);
            break;
        case CardId::RECRUTEMENT:
            recrutementAllyEffect(owner, game);
            break;
        case CardId::INTIMIDATION:
            intimidationAllyEffect(owner, game);
            break;
        case CardId::BENEFICE:
            beneficeAllyEffect(owner, game);
            break;
        // Ajouter d'autres cartes ici au fur et à mesure
        default:
            std::cout << "  Pas d'effet allié pour " << name << std::endl;
            break;
    }
}

bool ActionCard::canActivateAllyEffect(Player* owner) const {
    // Compter le nombre de cartes de la même faction en jeu (y compris cette carte)
    int cardsOfSameFaction = countCardsInPlayByFaction(owner, faction);
    return cardsOfSameFaction >= 2;
}

void ActionCard::sacrifice(Player* owner, Game* game) {
    switch (cardId) {
        case CardId::INFLUENCE:
            owner->addCombat(3);
            std::cout << name << " sacrifiée : " << owner->getName() << " gagne 3 combat supplémentaires !" << std::endl;
            break;

        default:
            std::cout << "  Pas d'effet de sacrifice pour " << name << std::endl;
            break;
    }
    
    // Retirer la carte du jeu et l'ajouter à la zone de sacrifice
    owner->removeCardFromPlay(this);
    game->getMarket()->addSacrificedCard(this);
}

// === FONCTION GENERIQUE POUR JOUER UNE CARTE DANS LE JEU (celles qui JUSTE rajoutent des golds, de la vie ou du combat)===
void ActionCard::genericPlayEffect(Player* owner) {
    if (goldValue > 0) {
        owner->addGold(goldValue);
        std::cout << name << " : " << owner->getName() << " gagne " << goldValue << " gold" << std::endl;
    }
    if (combatValue > 0) {
        owner->addCombat(combatValue);
        std::cout << name << " : " << owner->getName() << " gagne " << combatValue << " combat" << std::endl;
    }
    if (healthValue > 0) {
        owner->addHealth(healthValue);
        std::cout << name << " : " << owner->getName() << " gagne " << healthValue << " vie" << std::endl;
    }
}

// == EFFETS SPECIFIQUES DE TOUTES LES CARTES ==
// CARTE TAXATION
void ActionCard::taxationAllyEffect(Player* owner, Game* /*game*/) {
    owner->addHealth(6);
    std::cout << "  Taxation (Allié Impérial): " << owner->getName() << " gagne 6 Santé supplémentaires !" << std::endl;
}

// CARTE SERRER_LES_RANGS
void ActionCard::serrerLesRangsPrimaryEffect(Player* owner, Game* /*game*/) {
    int championsInPlay = countChampionsInPlay(owner);
    int totalCombat = combatValue + (2 * championsInPlay);
    owner->addCombat(totalCombat);
    std::cout << "  Serrer les rangs: " << owner->getName() << " gagne " << totalCombat << " combat (5 de base + 2 par champion en jeu)" << std::endl;
}
void ActionCard::serrerLesRangsAllyEffect(Player* owner, Game* /*game*/) {
    owner->addHealth(6);
    std::cout << "  Serrer les rangs (Allié Impérial): " << owner->getName() << " gagne 6 Santé supplémentaires !" << std::endl;
}

// CARTE RECRUTEMENT
void ActionCard::recrutementPrimaryEffect(Player* owner, Game* /*game*/) {
    int championsInPlay = countChampionsInPlay(owner);
    int totalHealth = healthValue + championsInPlay; // +1 santé par champion en jeu
    owner->addHealth(totalHealth);
    owner->addGold(goldValue);
    std::cout << "  Recrutement: " << owner->getName() << " gagne " << goldValue << " Or et " << totalHealth << " Santé (3 de base + 1 par champion en jeu)" << std::endl;
}
void ActionCard::recrutementAllyEffect(Player* owner, Game* /*game*/) {
    owner->addGold(1);
    std::cout << "  Recrutement (Allié Impérial): " << owner->getName() << " gagne 1 Or supplémentaire !" << std::endl;
}

// CARTE INTIMIDATION
void ActionCard::intimidationAllyEffect(Player* owner, Game* /*game*/) {
    owner->addGold(2);
    std::cout << "  Intimidation (Allié de la Guilde): " << owner->getName() << " gagne 2 Or supplémentaires !" << std::endl;
}

// CARTE BENEFICE
void ActionCard::beneficeAllyEffect(Player* owner, Game* /*game*/) {
    owner->addCombat(4);
    std::cout << "  Bénéfice (Allié de la Guilde): " << owner->getName() << " gagne 4 Combat supplémentaires !" << std::endl;
}

// CARTE INFLUENCE













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

int ActionCard::countChampionsInPlay(Player *owner) const {
    return static_cast<int>(owner->getChampionsEnJeu().size());
}