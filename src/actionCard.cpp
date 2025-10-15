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
            case CardId::COMMANDEMENT:
                description = "Gagnez 2 Or, 3 Combat et 4 Santé. Vous tirez une carte supplémentaire de votre pioche.";
                combatValue = 3;
                healthValue = 4;
                goldValue = 2;
                break;
            case CardId::DOMINATION:
                description = "Gagnez 6 Combat et 6 Santé et vous tirez une carte. Si vous avez un autre allié Impérial en jeu, vous pouvez préparer un champion.";
                combatValue = 6;
                healthValue = 6;
                break;
            case CardId::RALLIEMENT_DES_TROUPES:
                description = "Gagnez 4 Combat et 5 Santé. Si vous avez un autre allié Impérial en jeu, vous pouvez préparer un champion.";
                combatValue = 4;
                healthValue = 5;
                break;
            case CardId::PAROLE_DE_PUISSANCE:
                description = "Tirez 2 cartes. Si vous avez un autre allié Impérial en jeu, gagnez 5 Santé supplémentaires. Si vous sacrifiez la carte, vous gagnez 5 Combat supplémentaires.";
                break;
            case CardId::POT_DE_VIN:
                description = "Gagnez 3 Or. Si vous avez un autre allié de la Guilde en jeu, la prochaine carte Action que vous acheterez sera mise au dessus de votre pioche.";
                goldValue = 3;
                break;
            case CardId::MENACE_DE_MORT:
                description = "Gagnez 1 Combat et tirez une carte. Si vous avez un autre allié de la Guilde en jeu, vous pouvez assomer un champion adverse.";
                combatValue = 1;
                break;
            case CardId::FOURBERIE:
                description = "Gagnez 2 Or et tirez une carte. Si vous avez un autre allié de la Guilde en jeu, la prochaine carte que vous acheterez sera mise au dessus de votre pioche.";
                goldValue = 2;
                break;
            case CardId::BOMBE_INCENDIAIRE:
                description = "Gagnez 8 Combat, tirez une carte et assommez un champion adverse. Si vous sacrifiez la carte, vous gagnez 5 Combat supplémentaires.";
                combatValue = 8;
                break;
            case CardId::MISE_A_PRIX:
                description = "Gagnez 7 Combat. Si vous avez un autre allié de la Guilde en jeu, assommez un champion adverse.";
                combatValue = 7;
                break;
            case CardId::CASSER_ET_PILLER:
                description = "Gagnez 6 Combat. Vous pouvez prendre n'importe quelle carte de la défausse et la placer en haut de votre pioche.";
                combatValue = 6;
                break;
            case CardId::ENERGIE_SOMBRE:
                description = "Gagnez 7 Combat. Si vous avez un autre allié Nécros en jeu, tirez une carte supplémentaire.";
                combatValue = 7;
                break;
            case CardId::SOMBRE_RECOMPENSE:
                description = "Gagnez 3 Or et sacrifiez une carte de votre choix de votre main ou de votre défausse. Si vous avez un autre allié Nécros en jeu, gagnez 6 Combat supplémentaires.";
                goldValue = 3;
                break;
            case CardId::CONTACT_MORTEL:
                description = "Gagnez 2 Combat et sacrifiez une carte de votre choix de votre main ou de votre défausse. Si vous avez un autre allié Nécros en jeu, gagnez 2 Combat supplémentaires.";
                combatValue = 2;
                break;
            case CardId::DRAIN_DE_VIE:
                description = "Gagnez 8 Combat et sacrifiez une carte de votre choix de votre main ou de votre défausse. Si vous avez un autre allié Nécros en jeu, tirez une carte supplémentaire.";
                combatValue = 8;
                break;
            case CardId::LA_PUTREFACTION:
                description = "Gagnez 4 Combat et sacrifiez une carte de votre choix de votre main ou de votre défausse. Si vous avez un autre allié Nécros en jeu, gagnez 3 Combat supplémentaires.";
                combatValue = 4;
                break;
            case CardId::MALEDICTION_ELFIQUE:
                description = "Gagnez 6 Combat et défaussez une carte de votre adversaire. Si vous avez un autre allié Sauvage en jeu, gagnez 3 Combat supplémentaires.";
                combatValue = 6;
                break;
            case CardId::DON_ELFIQUE:
                description = "Gagnez 2 Or et vous avez le choix de tirer une carte (vous devez défaussez une carte de votre main si vous le faites). Si vous avez un autre allié Sauvage en jeu, gagnez 4 Combat supplémentaires.";
                goldValue = 2;
                break;
            case CardId::DON_DE_LA_NATURE:
                description = "Gagnez 4 Or. Si vous avez un autre allié Sauvage en jeu, défaussez une carte de votre adversaire. Si vous sacrifiez la carte, gagnez 4 Combat supplémentaires.";
                goldValue = 4;
                break;
            case CardId::SAUVAGERIE:
                description = "Gagnez 6 combat et vous avez le choix de tirer jusqu'à 2 cartes (vous devez défaussez une carte de votre main pour chaque carte piochée).";
                combatValue = 6;
                break;
            case CardId::ETINCELLE:
                description = "Gagnez 3 Combat et défaussez une carte de votre adversaire. Si vous avez un autre allié Sauvage en jeu, gagnez 2 Combat supplémentaires.";
                combatValue = 3;
                break;
            case CardId::FORME_DE_LOUP:
                description = "Gagnez 8 Combat et défaussez une carte de votre adversaire. Si vous sacrifiez la carte, défaussez une carte de votre adversaire.";
                combatValue = 8;
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
        case CardId::COMMANDEMENT:
            commandementPrimaryEffect(owner, game); //+2 gold, +3 combat, +4 santé, piocher une carte
            break;
        case CardId::DOMINATION:
            dominationPrimaryEffect(owner, game); //+6 combat, +6 santé, piocher une carte
            break;
        case CardId::RALLIEMENT_DES_TROUPES:
            genericPlayEffect(owner); //+4 combat, +5 santé
            break;
        case CardId::PAROLE_DE_PUISSANCE:
            paroleDePuissancePrimaryEffect(owner, game); //tirer 2 cartes
            break;
        case CardId::POT_DE_VIN:
            genericPlayEffect(owner); //+3 gold
            break;
        case CardId::MENACE_DE_MORT:
            menaceDeMortPrimaryEffect(owner, game); //+1 combat, piocher une carte
            break;
        case CardId::FOURBERIE:
            fourberiePrimaryEffect(owner, game); //+2 gold, piocher une carte
            break;
        case CardId::BOMBE_INCENDIAIRE:
            bombeIncendiairePrimaryEffect(owner, game); //+8 combat, piocher une carte, assommer un champion adverse
            break;
        case CardId::MISE_A_PRIX:
            genericPlayEffect(owner); //+7 combat
            break;
        case CardId::CASSER_ET_PILLER:
            casserEtPillerPrimaryEffect(owner, game); //+6 combat et prendre une carte de la défausse et la mettre en haut de la pioche
            break;
        case CardId::ENERGIE_SOMBRE:
            genericPlayEffect(owner); //+7 combat
            break;
        case CardId::SOMBRE_RECOMPENSE:
            sombreRecompensePrimaryEffect(owner, game); //+3 gold et sacrifier une carte de la main ou de la défausse
            break;
        case CardId::CONTACT_MORTEL:
            contactMortelPrimaryEffect(owner, game); //+2 combat et sacrifier une carte de la main ou de la défausse
            break;
        case CardId::DRAIN_DE_VIE:
            drainDeViePrimaryEffect(owner, game); //+8 combat et sacrifier une carte de la main ou de la défausse
            break;
        case CardId::LA_PUTREFACTION:
            laPutrefactionPrimaryEffect(owner, game); //+4 combat et sacrifier une carte de la main ou de la défausse
            break;
        case CardId::MALEDICTION_ELFIQUE:
            maledictionElfiquePrimaryEffect(owner, game); //+6 combat et défausser une carte de l'adversaire
            break;
        case CardId::DON_ELFIQUE:
            donElfiquePrimaryEffect(owner, game); //+2 gold et choix de piocher une carte (si oui défausser une carte de la main)
            break;
        case CardId::DON_DE_LA_NATURE:
            donDeLaNaturePrimaryEffect(owner, game); //+4 gold et défausser une carte de l'adversaire
            break;
        case CardId::SAUVAGERIE:
            sauvageriePrimaryEffect(owner, game); //+6 combat et choix de piocher jusqu'à 2 cartes (si oui défausser une carte de la main par carte piochée)
            break;
        case CardId::ETINCELLE:
            etincellePrimaryEffect(owner, game); //+3 combat et défausser une carte de l'adversaire
            break;
        case CardId::FORME_DE_LOUP:
            formeDeLoupPrimaryEffect(owner, game); //+8 combat et défausser une carte de l'adversaire
            break;
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
        case CardId::DOMINATION:
            dominationAllyEffect(owner, game);
            break;
        case CardId::RALLIEMENT_DES_TROUPES:
            ralliementDesTroupesAllyEffect(owner, game); 
            break;
        case CardId::PAROLE_DE_PUISSANCE:
            paroleDePuissanceAllyEffect(owner, game);
            break;
        case CardId::POT_DE_VIN:
            potDeVinAllyEffect(owner, game);
            break;
        case CardId::MENACE_DE_MORT:
            menaceDeMortAllyEffect(owner, game);
            break;
        case CardId::FOURBERIE:
            fourberieAllyEffect(owner, game);
            break;
        case CardId::MISE_A_PRIX:
            miseAPrixAllyEffect(owner, game);
            break;
        case CardId::ENERGIE_SOMBRE:
            energieSombreAllyEffect(owner, game);
            break;
        case CardId::SOMBRE_RECOMPENSE:
            sombreRecompenseAllyEffect(owner, game);
            break;
        case CardId::CONTACT_MORTEL:
            contactMortelAllyEffect(owner, game);
            break;
        case CardId::DRAIN_DE_VIE:
            drainDeVieAllyEffect(owner, game);
            break;
        case CardId::LA_PUTREFACTION:
            laPutrefactionAllyEffect(owner, game);
            break;
        case CardId::MALEDICTION_ELFIQUE:
            maledictionElfiqueAllyEffect(owner, game);
            break;
        case CardId::DON_ELFIQUE:
            donElfiqueAllyEffect(owner, game);
            break;
        case CardId::DON_DE_LA_NATURE:
            donDeLaNatureAllyEffect(owner, game);
            break;
        case CardId::ETINCELLE:
            etincelleAllyEffect(owner, game);
            break;
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

// === FONCTION POUR SACRIFIER UNE CARTE ===
void ActionCard::sacrifice(Player* owner, Game* game, bool fromEffects /*si cest un sacrifice qui vient d'une carte*/) {
    bool canBeSacrified = false;
    switch (cardId) {
        case CardId::INFLUENCE:
            owner->addCombat(3);
            std::cout << name << " sacrifiée : " << owner->getName() << " gagne 3 combat supplémentaires !" << std::endl;
            canBeSacrified = true;
            break;
        case CardId::PAROLE_DE_PUISSANCE:
            owner->addCombat(5);
            std::cout << name << " sacrifiée : " << owner->getName() << " gagne 5 combat supplémentaires !" << std::endl;
            canBeSacrified = true;
            break;
        case CardId::BOMBE_INCENDIAIRE:
            owner->addCombat(5);
            std::cout << name << " sacrifiée : " << owner->getName() << " gagne 5 combat supplémentaires !" << std::endl;
            canBeSacrified = true;
            break;
        case CardId::DON_DE_LA_NATURE:
            owner->addCombat(4);
            std::cout << name << " sacrifiée : " << owner->getName() << " gagne 4 combat supplémentaires !" << std::endl;
            canBeSacrified = true;
            break;
        case CardId::FORME_DE_LOUP:
        {
            // Choisir une carte dans la main de l'adversaire et la défausser
            Player* opponent = game->getOpponent(owner);
            Card* cardToDiscard = chooseCardFromOpponentHand(opponent);

            if (cardToDiscard != nullptr) {
                opponent->removeCardFromHand(cardToDiscard);
                opponent->addToDiscardPile(cardToDiscard);
                std::cout << "  Sacrifice Forme de loup: " << cardToDiscard->getName()
                        << " défaussée de la main de " << opponent->getName() << " !" << std::endl;
            } else {
                std::cout << "  Sacrifice Forme de loup: Aucune carte à défausser dans la main adverse." << std::endl;
            }
            canBeSacrified = true;
            break;
        }
        default:
            std::cout << "  Pas d'effet de sacrifice pour " << name << std::endl;
            break;
    }

    //On ne peut pas sacrifier une carte qui n'a pas d'effet de sacrifice
    if (!canBeSacrified && !fromEffects) {
        std::cout << "  Impossible de sacrifier " << name << " : pas d'effet de sacrifice." << std::endl;
        return;
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

// CARTE COMMANDEMENT
void ActionCard::commandementPrimaryEffect(Player* owner, Game* /*game*/) {
    owner->addGold(goldValue);
    owner->addCombat(combatValue);
    owner->addHealth(healthValue);
    owner->draw(1);
    std::cout << "  Commandement: " << owner->getName() << " gagne " << goldValue << " Or, " << combatValue << " Combat, " << healthValue << " Santé et pioche une carte." << std::endl;
}

// CARTE DOMINATION
void ActionCard::dominationPrimaryEffect(Player* owner, Game* /*game*/) {
    owner->addCombat(combatValue);
    owner->addHealth(healthValue);
    owner->draw(1);
    std::cout << "  Domination: " << owner->getName() << " gagne " << combatValue << " Combat, " << healthValue << " Santé et pioche une carte." << std::endl;
}
void ActionCard::dominationAllyEffect(Player* owner, Game* /*game*/) {
    // Préparer un champion (mettre isActivated à false)
    ChampionCard* championToReady = chooseChampionToReady(owner);
    
    if (championToReady != nullptr) {
        championToReady->setActivated(false); // Le champion n'est plus activé (il est préparé)
        std::cout << "  Domination (Allié Impérial): " << owner->getName() << " prépare le champion " << championToReady->getName() << " !" << std::endl;
    } else {
        std::cout << "  Domination (Allié Impérial): Aucun champion activé à préparer." << std::endl;
    }
}

// CARTE RALLIEMENT_DES_TROUPES
void ActionCard::ralliementDesTroupesAllyEffect(Player* owner, Game* /*game*/) {
    // Préparer un champion (mettre isActivated à false)
    ChampionCard* championToReady = chooseChampionToReady(owner);

    if (championToReady != nullptr) {
        championToReady->setActivated(false); // Le champion n'est plus activé (il est préparé)
        std::cout << "  Ralliement des troupes (Allié Impérial): " << owner->getName() << " prépare le champion " << championToReady->getName() << " !" << std::endl;
    } else {
        std::cout << "  Ralliement des troupes (Allié Impérial): Aucun champion activé à préparer." << std::endl;
    }
}

// CARTE PAROLE_DE_PUISSANCE
void ActionCard::paroleDePuissancePrimaryEffect(Player* owner, Game* /*game*/) {
    owner->draw(2);
    std::cout << "  Parole de puissance: " << owner->getName() << " pioche 2 cartes." << std::endl;
}
void ActionCard::paroleDePuissanceAllyEffect(Player* owner, Game* /*game*/) {
    owner->addHealth(5);
    std::cout << "  Parole de puissance (Allié Impérial): " << owner->getName() << " gagne 5 Santé supplémentaires !" << std::endl;
}

// CARTE POT_DE_VIN
void ActionCard::potDeVinAllyEffect(Player* owner, Game* /*game*/) {
    // Activer l'effet : la prochaine carte Action achetée ira au-dessus de la pioche
    owner->setNextActionCardToTopOfDeck(true);
    std::cout << "  Pot-de-Vin (Allié de la Guilde): " << owner->getName() << " - la prochaine carte Action achetée sera placée au-dessus de la pioche !" << std::endl;
}

// CARTE MENACE_DE_MORT
void ActionCard::menaceDeMortPrimaryEffect(Player* owner, Game* /*game*/) {
    owner->addCombat(combatValue);
    owner->draw(1);
    std::cout << "  Menace de mort: " << owner->getName() << " gagne " << combatValue << " Combat et pioche une carte." << std::endl;
}
void ActionCard::menaceDeMortAllyEffect(Player* owner, Game* game) {
    Player* opponent = game->getOpponent(owner);
    ChampionCard* championToStun = chooseChampionToStun(opponent);
    if (championToStun != nullptr) {
        opponent->stunChampion(championToStun);
        std::cout << "  Menace de Mort (Allié de la Guilde): " << owner->getName() << " assomme le champion " << championToStun->getName() << " de " << opponent->getName() << " !" << std::endl;
    } else {
        std::cout << "  Menace de Mort (Allié de la Guilde): Aucun champion adverse à assommer." << std::endl;
    }
}

// CARTE FOURBERIE (Deception)
void ActionCard::fourberiePrimaryEffect(Player* owner, Game* /*game*/) {
    owner->addGold(goldValue);
    owner->draw(1);
    std::cout << "  Fourberie: " << owner->getName() << " gagne " << goldValue << " Or et pioche une carte." << std::endl;
}
void ActionCard::fourberieAllyEffect(Player* owner, Game* /*game*/) {
    // Activer l'effet : la prochaine carte achetée (n'importe laquelle) ira au-dessus de la pioche
    owner->setNextAnyCardToTopOfDeck(true);
    std::cout << "  Fourberie (Allié de la Guilde): " << owner->getName() << " - la prochaine carte achetée sera placée au-dessus de la pioche !" << std::endl;
}

// CARTE BOMBE_INCENDIAIRE
void ActionCard::bombeIncendiairePrimaryEffect(Player* owner, Game* game) {
    owner->addCombat(combatValue);
    owner->draw(1);
    std::cout << "  Bombe incendiaire: " << owner->getName() << " gagne " << combatValue << " Combat et pioche une carte." << std::endl;

    // Assommer un champion adverse
    Player* opponent = game->getOpponent(owner);
    ChampionCard* championToStun = chooseChampionToStun(opponent);
    if (championToStun != nullptr) {
        opponent->stunChampion(championToStun);
        std::cout << "  Bombe incendiaire: " << owner->getName() << " assomme le champion " << championToStun->getName() << " de " << opponent->getName() << " !" << std::endl;
    } else {
        std::cout << "  Bombe incendiaire: Aucun champion adverse à assommer." << std::endl;
    }
}

// CARTE MISE A PRIX
void ActionCard::miseAPrixAllyEffect(Player* owner, Game* game) {
    Player* opponent = game->getOpponent(owner);
    ChampionCard* championToStun = chooseChampionToStun(opponent);
    if (championToStun != nullptr) {
        opponent->stunChampion(championToStun);
        std::cout << "  Mise à prix (Allié de la Guilde): " << owner->getName() << " assomme le champion " << championToStun->getName() << " de " << opponent->getName() << " !" << std::endl;
    } else {
        std::cout << "  Mise à prix (Allié de la Guilde): Aucun champion adverse à assommer." << std::endl;
    }
}

// CARTE CASSER_ET_PILLER
void ActionCard::casserEtPillerPrimaryEffect(Player* owner, Game* /*game*/) {
    owner->addCombat(combatValue);
    std::cout << "  Casser et piller: " << owner->getName() << " gagne " << combatValue << " Combat." << std::endl;
    
    // Prendre une carte de la défausse (qu'on choisit) et la mettre en haut de la pioche
    Card* chosenCard = chooseCardFromDiscard(owner);
    if (chosenCard != nullptr) {
        owner->moveCardFromDiscardToTopOfDeck(chosenCard);
        std::cout << "  Casser et piller: " << owner->getName() << " place " << chosenCard->getName() << " au-dessus de sa pioche." << std::endl;
    } else {
        std::cout << "  Casser et piller: Aucune carte disponible dans la défausse." << std::endl;
    }
}

// CARTE ENERGIE_SOMBRE
void ActionCard::energieSombreAllyEffect(Player* owner, Game* /*game*/) {
    owner->draw(1);
    std::cout << "  Énergie sombre (Allié Nécros): " << owner->getName() << " pioche une carte supplémentaire !" << std::endl;
}

// CARTE SOMBRE RECOMPENSE
void ActionCard::sombreRecompensePrimaryEffect(Player* owner, Game* game) {
    owner->addGold(goldValue);
    std::cout << "  Sombre récompense: " << owner->getName() << " gagne " << goldValue << " Or." << std::endl;
    
    // Sacrifier une carte de la main ou de la défausse
    Card* cardToSacrifice = chooseCardToSacrifice(owner);
    if (cardToSacrifice != nullptr) {
        sacrificeChosenCard(owner, game, cardToSacrifice);
    }
}
void ActionCard::sombreRecompenseAllyEffect(Player* owner, Game* /*game*/) {
    owner->addCombat(6);
    std::cout << "  Sombre récompense (Allié Nécros): " << owner->getName() << " gagne 6 Combat supplémentaires !" << std::endl;
}

// CARTE CONTACT MORTEL
void ActionCard::contactMortelPrimaryEffect(Player* owner, Game* game) {
    owner->addCombat(combatValue);
    std::cout << "  Contact mortel: " << owner->getName() << " gagne " << combatValue << " Combat." << std::endl;

    // Sacrifier une carte de la main ou de la défausse
    Card* cardToSacrifice = chooseCardToSacrifice(owner);
    if (cardToSacrifice != nullptr) {
        sacrificeChosenCard(owner, game, cardToSacrifice);
    }
}
void ActionCard::contactMortelAllyEffect(Player* owner, Game* /*game*/) {
    owner->addCombat(2);
    std::cout << "  Contact mortel (Allié Nécros): " << owner->getName() << " gagne 2 Combat supplémentaires !" << std::endl;
}

// CARTE DRAIN DE VIE
void ActionCard::drainDeViePrimaryEffect(Player* owner, Game* game) {
    owner->addCombat(combatValue);
    std::cout << "  Drain de vie: " << owner->getName() << " gagne " << combatValue << " Combat." << std::endl;

    // Sacrifier une carte de la main ou de la défausse
    Card* cardToSacrifice = chooseCardToSacrifice(owner);
    if (cardToSacrifice != nullptr) {
        sacrificeChosenCard(owner, game, cardToSacrifice);
    }
}
void ActionCard::drainDeVieAllyEffect(Player* owner, Game* /*game*/) {
    owner->draw(1);
    std::cout << "  Drain de vie (Allié Nécros): " << owner->getName() << " pioche une carte supplémentaire !" << std::endl;
}

// CARTE LA PUTREFACTION
void ActionCard::laPutrefactionPrimaryEffect(Player* owner, Game* game) {
    owner->addCombat(combatValue);
    std::cout << "  La Putréfaction: " << owner->getName() << " gagne " << combatValue << " Combat." << std::endl;

    // Sacrifier une carte de la main ou de la défausse
    Card* cardToSacrifice = chooseCardToSacrifice(owner);
    if (cardToSacrifice != nullptr) {
        sacrificeChosenCard(owner, game, cardToSacrifice);
    }
}
void ActionCard::laPutrefactionAllyEffect(Player* owner, Game* /*game*/) {
    owner->addCombat(3);
    std::cout << "  La Putréfaction (Allié Nécros): " << owner->getName() << " gagne 3 Combat supplémentaires !" << std::endl;
}

// CARTE MALEDICTION_ELFIQUE
void ActionCard::maledictionElfiquePrimaryEffect(Player* owner, Game* game) {
    owner->addCombat(combatValue);
    std::cout << "  Malédiction elfique: " << owner->getName() << " gagne " << combatValue << " Combat." << std::endl;
    
    // Choisir une carte dans la main de l'adversaire et la défausser
    Player* opponent = game->getOpponent(owner);
    Card* cardToDiscard = chooseCardFromOpponentHand(opponent);
    
    if (cardToDiscard != nullptr) {
        opponent->removeCardFromHand(cardToDiscard); // On retire la carte de la main de l'adversaire
        opponent->addToDiscardPile(cardToDiscard);
        std::cout << "  Malédiction elfique: " << cardToDiscard->getName() 
                  << " défaussée de la main de " << opponent->getName() << " !" << std::endl;
    } else {
        std::cout << "  Malédiction elfique: Aucune carte à défausser dans la main adverse." << std::endl;
    }
}
void ActionCard::maledictionElfiqueAllyEffect(Player* owner, Game* /*game*/) {
    owner->addCombat(3);
    std::cout << "  Malédiction elfique (Allié Sauvage): " << owner->getName() << " gagne 3 Combat supplémentaires !" << std::endl;
}

// CARTE DON_ELFIQUE
void ActionCard::donElfiquePrimaryEffect(Player* owner, Game* /*game*/) {
    owner->addGold(goldValue);
    std::cout << "  Don elfique: " << owner->getName() << " gagne " << goldValue << " Or." << std::endl;
    
    // Choix de piocher une carte (si oui, défausser une carte de la main)
    std::cout << "  Voulez-vous piocher une carte supplémentaire ? (vous devrez défausser une carte de votre main)" << std::endl;
    std::cout << "  1. Oui, piocher une carte" << std::endl;
    std::cout << "  2. Non, ne pas piocher" << std::endl;
    
    int choice;
    do {
        std::cout << "  Votre choix (1-2): ";
        std::cin >> choice;
    } while (choice < 1 || choice > 2);
    
    if (choice == 1) {
        // Le joueur choisit de piocher
        owner->draw(1);
        std::cout << "  Don elfique: " << owner->getName() << " pioche une carte." << std::endl;
        
        // Maintenant il doit défausser une carte de sa main
        Card* cardToDiscard = chooseCardFromOwnHand(owner);
        if (cardToDiscard != nullptr) {
            owner->removeCardFromHand(cardToDiscard);
            owner->addToDiscardPile(cardToDiscard);
            std::cout << "  Don elfique: " << cardToDiscard->getName() 
                      << " défaussée de la main de " << owner->getName() << "." << std::endl;
        } else {
            std::cout << "  Don elfique: Aucune carte à défausser." << std::endl;
        }
    } else {
        // Le joueur choisit de ne pas piocher
        std::cout << "  Don elfique: " << owner->getName() << " choisit de ne pas piocher de carte supplémentaire." << std::endl;
    }
}
void ActionCard::donElfiqueAllyEffect(Player* owner, Game* /*game*/) {
    owner->addCombat(4);
    std::cout << "  Don elfique (Allié Sauvage): " << owner->getName() << " gagne 4 Combat supplémentaires !" << std::endl;
}

// CARTE DON_DE_LA_NATURE
void ActionCard::donDeLaNaturePrimaryEffect(Player* owner, Game* /*game*/) {
    owner->addGold(goldValue);
    std::cout << "  Don de la nature: " << owner->getName() << " gagne " << goldValue << " Or." << std::endl;
}
void ActionCard::donDeLaNatureAllyEffect(Player* owner, Game* game) {
    // Choisir une carte dans la main de l'adversaire et la défausser
    Player* opponent = game->getOpponent(owner);
    Card* cardToDiscard = chooseCardFromOpponentHand(opponent);

    if (cardToDiscard != nullptr) {
        opponent->removeCardFromHand(cardToDiscard);
        opponent->addToDiscardPile(cardToDiscard);
        std::cout << "  Don de la nature (Allié Sauvage): " << cardToDiscard->getName()
                  << " défaussée de la main de " << opponent->getName() << " !" << std::endl;
    } else {
        std::cout << "  Don de la nature (Allié Sauvage): Aucune carte à défausser dans la main adverse." << std::endl;
    }
}

// CARTE SAUVAGERIE
void ActionCard::sauvageriePrimaryEffect(Player* owner, Game* /*game*/) {
    owner->addCombat(combatValue);
    std::cout << "  Sauvagerie: " << owner->getName() << " gagne " << combatValue << " Combat." << std::endl;

    // Choix de piocher jusqu'à 2 cartes (défausser une carte pour chaque carte piochée)
    std::cout << "  Combien de cartes voulez-vous piocher ? (vous devrez défausser une carte pour chaque carte piochée)" << std::endl;
    std::cout << "  0. Ne pas piocher" << std::endl;
    std::cout << "  1. Piocher 1 carte" << std::endl;
    std::cout << "  2. Piocher 2 cartes" << std::endl;

    int choice;
    do {
        std::cout << "  Votre choix (0-2): ";
        std::cin >> choice;
    } while (choice < 0 || choice > 2);

    if (choice == 0) {
        // Le joueur choisit de ne pas piocher
        std::cout << "  Sauvagerie: " << owner->getName() << " choisit de ne pas piocher de cartes supplémentaires." << std::endl;
    } else {
        // Le joueur choisit de piocher 1 ou 2 cartes
        for (int i = 0; i < choice; i++) {
            owner->draw(1);
            std::cout << "  Sauvagerie: " << owner->getName() << " pioche une carte (" << (i+1) << "/" << choice << ")." << std::endl;

            // Maintenant il doit défausser une carte de sa main
            Card* cardToDiscard = chooseCardFromOwnHand(owner);
            if (cardToDiscard != nullptr) {
                owner->removeCardFromHand(cardToDiscard);
                owner->addToDiscardPile(cardToDiscard);
                std::cout << "  Sauvagerie: " << cardToDiscard->getName()
                          << " défaussée de la main de " << owner->getName() << " (" << (i+1) << "/" << choice << ")." << std::endl;
            } else {
                std::cout << "  Sauvagerie: Aucune carte à défausser pour la carte " << (i+1) << "." << std::endl;
            }
        }
    }
}

// CARTE ETINCELLE
void ActionCard::etincellePrimaryEffect(Player* owner, Game* game) {
    owner->addCombat(combatValue);
    std::cout << "  Étincelle: " << owner->getName() << " gagne " << combatValue << " Combat." << std::endl;

    // Choisir une carte dans la main de l'adversaire et la défausser
    Player* opponent = game->getOpponent(owner);
    Card* cardToDiscard = chooseCardFromOpponentHand(opponent);
    
    if (cardToDiscard != nullptr) {
        opponent->removeCardFromHand(cardToDiscard); // On retire la carte de la main de l'adversaire
        opponent->addToDiscardPile(cardToDiscard);
        std::cout << "  Étincelle: " << cardToDiscard->getName() 
                  << " défaussée de la main de " << opponent->getName() << " !" << std::endl;
    } else {
        std::cout << "  Étincelle: Aucune carte à défausser dans la main adverse." << std::endl;
    }

}
void ActionCard::etincelleAllyEffect(Player* owner, Game* /*game*/) {
    owner->addCombat(2);
    std::cout << "  Étincelle (Allié Sauvage): " << owner->getName() << " gagne 2 Combat supplémentaires !" << std::endl;
}

// CARTE FORME_DE_LOUP
void ActionCard::formeDeLoupPrimaryEffect(Player* owner, Game* game) {
    owner->addCombat(combatValue);
    std::cout << "  Forme de loup: " << owner->getName() << " gagne " << combatValue << " Combat." << std::endl;

    // Choisir une carte dans la main de l'adversaire et la défausser
    Player* opponent = game->getOpponent(owner);
    Card* cardToDiscard = chooseCardFromOpponentHand(opponent);

    if (cardToDiscard != nullptr) {
        opponent->removeCardFromHand(cardToDiscard);
        opponent->addToDiscardPile(cardToDiscard);
        std::cout << "  Forme de loup: " << cardToDiscard->getName()
                  << " défaussée de la main de " << opponent->getName() << " !" << std::endl;
    } else {
        std::cout << "  Forme de loup: Aucune carte à défausser dans la main adverse." << std::endl;
    }

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

int ActionCard::countChampionsInPlay(Player *owner) const {
    return static_cast<int>(owner->getChampionsEnJeu().size());
}

int ActionCard::countActivatedChampionsInPlay(Player* owner) const {
    int count = 0;
    for (const ChampionCard* champion : owner->getChampionsEnJeu()) {
        if (champion->getActivated()) {
            count++;
        }
    }
    return count;
}

ChampionCard* ActionCard::chooseChampionToReady(Player* owner) const {
    std::vector<ChampionCard*> activatedChampions;
    
    // Collecter tous les champions activés
    for (ChampionCard* champion : owner->getChampionsEnJeu()) {
        if (champion->getActivated()) {
            activatedChampions.push_back(champion);
        }
    }
    
    if (activatedChampions.empty()) {
        return nullptr;
    }
    
    // Si il n'y a qu'un seul champion activé, le choisir automatiquement
    if (activatedChampions.size() == 1) {
        return activatedChampions[0];
    }
    
    // Sinon, permettre au joueur de choisir
    std::cout << "Choisissez un champion à préparer :" << std::endl;
    for (size_t i = 0; i < activatedChampions.size(); i++) {
        std::cout << (i + 1) << ". " << activatedChampions[i]->getName() << std::endl;
    }
    
    int choice;
    do {
        std::cout << "Votre choix (1-" << activatedChampions.size() << "): ";
        std::cin >> choice;
    } while (choice < 1 || choice > static_cast<int>(activatedChampions.size()));
    
    return activatedChampions[choice - 1];
}

// Méthode pour choisir un champion adverse à assommer
ChampionCard* ActionCard::chooseChampionToStun(Player* opponent) const {
    std::vector<ChampionCard*> targetableChampions = opponent->getTargetableChampions();
    
    if (targetableChampions.empty()) {
        return nullptr;
    }
    
    // Si il n'y a qu'un seul champion ciblable, le choisir automatiquement
    if (targetableChampions.size() == 1) {
        return targetableChampions[0];
    }
    
    // Sinon, permettre au joueur de choisir
    std::cout << "Choisissez un champion adverse à assommer :" << std::endl;
    for (size_t i = 0; i < targetableChampions.size(); i++) {
        std::cout << (i + 1) << ". " << targetableChampions[i]->getName();
        if (targetableChampions[i]->getGuarding()) {
            std::cout << " (Garde)";
        }
        std::cout << std::endl;
    }
    
    int choice;
    do {
        std::cout << "Votre choix (1-" << targetableChampions.size() << "): ";
        std::cin >> choice;
    } while (choice < 1 || choice > static_cast<int>(targetableChampions.size()));
    
    return targetableChampions[choice - 1];
}

Card* ActionCard::chooseCardFromDiscard(Player* owner) const {
    const std::vector<Card*>& discardPile = owner->getDiscardPile();
    
    if (discardPile.empty()) {
        std::cout << "La défausse de " << owner->getName() << " est vide." << std::endl;
        return nullptr;
    }
    
    // Si il n'y a qu'une seule carte dans la défausse, la choisir automatiquement
    if (discardPile.size() == 1) {
        return discardPile[0];
    }
    
    // Sinon, permettre au joueur de choisir
    std::cout << "Choisissez une carte de votre défausse :" << std::endl;
    for (size_t i = 0; i < discardPile.size(); i++) {
        std::cout << (i + 1) << ". " << discardPile[i]->getName() << std::endl;
    }
    
    int choice;
    do {
        std::cout << "Votre choix (1-" << discardPile.size() << "): ";
        std::cin >> choice;
    } while (choice < 1 || choice > static_cast<int>(discardPile.size()));
    
    return discardPile[choice - 1];
}

Card* ActionCard::chooseCardToSacrifice(Player* owner) const {
    const std::vector<Card*>& hand = owner->getHand();
    const std::vector<Card*>& discardPile = owner->getDiscardPile();
    
    // Vérifier si des cartes sont disponibles
    if (hand.empty() && discardPile.empty()) {
        std::cout << "Aucune carte disponible pour le sacrifice." << std::endl;
        return nullptr;
    }
    
    // Créer une liste combinée de toutes les cartes disponibles
    std::vector<Card*> availableCards;
    std::vector<std::string> cardSources;  // Pour identifier si c'est de la main ou de la défausse
    
    // Ajouter les cartes de la main
    for (Card* card : hand) {
        availableCards.push_back(card);
        cardSources.push_back("main");
    }
    
    // Ajouter les cartes de la défausse
    for (Card* card : discardPile) {
        availableCards.push_back(card);
        cardSources.push_back("défausse");
    }
    
    // Si il n'y a qu'une seule carte disponible, la choisir automatiquement
    if (availableCards.size() == 1) {
        std::cout << "Sacrifiant " << availableCards[0]->getName() 
                  << " de votre " << cardSources[0] << "." << std::endl;
        return availableCards[0];
    }
    
    // Sinon, permettre au joueur de choisir
    std::cout << "Choisissez une carte à sacrifier :" << std::endl;
    for (size_t i = 0; i < availableCards.size(); i++) {
        std::cout << (i + 1) << ". " << availableCards[i]->getName() 
                  << " (" << cardSources[i] << ")" << std::endl;
    }
    
    int choice;
    do {
        std::cout << "Votre choix (1-" << availableCards.size() << "): ";
        std::cin >> choice;
    } while (choice < 1 || choice > static_cast<int>(availableCards.size()));
    
    return availableCards[choice - 1];
}

Card* ActionCard::chooseCardFromOpponentHand(Player* opponent) const {
    const std::vector<Card*>& opponentHand = opponent->getHand();
    
    // Vérifier si l'adversaire a des cartes en main
    if (opponentHand.empty()) {
        std::cout << "La main de " << opponent->getName() << " est vide." << std::endl;
        return nullptr;
    }
    
    // Si il n'y a qu'une seule carte dans la main, la choisir automatiquement
    if (opponentHand.size() == 1) {
        std::cout << "Défaussant " << opponentHand[0]->getName() 
                  << " de la main de " << opponent->getName() << "." << std::endl;
        return opponentHand[0];
    }
    
    // Sinon, permettre au joueur de choisir (on révèle la main de l'adversaire)
    std::cout << "Choisissez une carte à défausser de la main de " << opponent->getName() << " :" << std::endl;
    for (size_t i = 0; i < opponentHand.size(); i++) {
        std::cout << (i + 1) << ". " << opponentHand[i]->getName() << std::endl;
    }
    
    int choice;
    do {
        std::cout << "Votre choix (1-" << opponentHand.size() << "): ";
        std::cin >> choice;
    } while (choice < 1 || choice > static_cast<int>(opponentHand.size()));
    
    return opponentHand[choice - 1];
}

Card* ActionCard::chooseCardFromOwnHand(Player* owner) const {
    const std::vector<Card*>& hand = owner->getHand();
    
    // Vérifier si le joueur a des cartes en main
    if (hand.empty()) {
        std::cout << "Votre main est vide." << std::endl;
        return nullptr;
    }
    
    // Si il n'y a qu'une seule carte dans la main, la choisir automatiquement
    if (hand.size() == 1) {
        std::cout << "Défaussant " << hand[0]->getName() 
                  << " de votre main." << std::endl;
        return hand[0];
    }
    
    // Sinon, permettre au joueur de choisir
    std::cout << "Choisissez une carte de votre main à défausser :" << std::endl;
    for (size_t i = 0; i < hand.size(); i++) {
        std::cout << (i + 1) << ". " << hand[i]->getName() << std::endl;
    }
    
    int choice;
    do {
        std::cout << "Votre choix (1-" << hand.size() << "): ";
        std::cin >> choice;
    } while (choice < 1 || choice > static_cast<int>(hand.size()));
    
    return hand[choice - 1];
}

void ActionCard::sacrificeChosenCard(Player* owner, Game* game, Card* cardToSacrifice) const {
    // Déterminer d'où vient la carte (main ou défausse)
    const std::vector<Card*>& hand = owner->getHand();
    const std::vector<Card*>& discardPile = owner->getDiscardPile();
    
    bool fromHand = false;
    bool fromDiscard = false;
    
    // Vérifier si la carte est dans la main
    for (Card* card : hand) {
        if (card == cardToSacrifice) {
            fromHand = true;
            break;
        }
    }
    
    // Vérifier si la carte est dans la défausse
    if (!fromHand) {
        for (Card* card : discardPile) {
            if (card == cardToSacrifice) {
                fromDiscard = true;
                break;
            }
        }
    }
    
    // Retirer la carte de son origine
    if (fromHand) {
        owner->removeCardFromHand(cardToSacrifice);
        std::cout << cardToSacrifice->getName() << " retiré de la main." << std::endl;
    } else if (fromDiscard) {
        owner->removeCardFromDiscard(cardToSacrifice);
        std::cout << cardToSacrifice->getName() << " retiré de la défausse." << std::endl;
    }
    
    // Exécuter l'effet de sacrifice s'il y en a un
    cardToSacrifice->sacrifice(owner, game, true);
}