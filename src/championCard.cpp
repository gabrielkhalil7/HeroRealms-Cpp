#include "../include/championCard.hpp"
#include "../include/player.hpp"
#include "../include/game.hpp"
#include <iostream>
#include <algorithm>

ChampionCard::ChampionCard(const std::string& n, int c, Faction f, CardId id) 
    : Card(n, c, f, id), goldValue(0), combatValue(0), healthValue(0), defense(0), defenseActuelle(0), isGuarding(false), isActivated(false) {
        // initialisation des descriptions
        switch (id) {
            // ========== IMPERIAL CHAMPIONS ==========
            case CardId::ARKUS_DRAGON_IMPERIAL:
                description = "{Dépense}: Gagnez 5 Combat et piochez une carte. Si vous avez un autre allié Impérial en jeu, gagnez 6 Santé supplémentaires.";
                defense = 6;
                combatValue = 5;
                healthValue = 6;
                isGuarding = true;
                break;
            case CardId::DARIAN_MAGE_DE_GUERRE:
                description = "{Dépense}: Gagnez 3 Combat ou gagnez 4 Santé.";
                defense = 5;
                combatValue = 3;
                healthValue = 4;
                isGuarding = false;
                break;
            case CardId::CRISTOV_LE_JUSTE:
                description = "{Dépense}: Gagnez 2 Combat et gagnez 3 Santé. Si vous avez un autre allié Impérial en jeu, piochez une carte.";
                defense = 5;
                combatValue = 2;
                healthValue = 3;
                isGuarding = true;
                break;
            case CardId::KRAKA_GRAND_PRETRE:
                description = "{Dépense}: Gagnez 2 Santé et piochez une carte. Si vous avez un autre allié Impérial en jeu, gagnez 2 Santé pour chaque champion que vous avez en jeu.";
                defense = 6;
                healthValue = 2;
                isGuarding = false;
                break;
            case CardId::HOMME_D_ARMES:
                description = "{Dépense}: Gagnez 2 Combat +1 Combat pour chaque autre garde que vous avez en jeu.";
                defense = 4;
                combatValue = 2;
                isGuarding = true;
                break;
            case CardId::MAITRE_WEYAN:
                description = "{Dépense}: Gagnez 3 Combat +1 Combat pour chaque autre champion que vous avez en jeu.";
                defense = 4;
                combatValue = 3;
                isGuarding = true;
                break;
            case CardId::PERCEPTEUR_DE_DIME:
                description = "{Dépense}: Gagnez 1 Or ou gagnez 1 Santé pour chaque champion que vous avez en jeu.";
                defense = 3;
                goldValue = 1;
                healthValue = 1;
                isGuarding = false;
                break;
                
            // ========== GUILD CHAMPIONS ==========
            case CardId::BORG_MERCENAIRE_OGRE:
                description = "{Dépense}: Gagnez 4 Combat.";
                defense = 6;
                combatValue = 4;
                isGuarding = true;
                break;
            case CardId::MYROS_MAGE_DE_LA_GUILDE:
                description = "{Dépense}: Gagnez 3 Or. Si vous avez un autre allié de la Guilde en jeu, gagnez 4 Combat.";
                defense = 3;
                goldValue = 3;
                combatValue = 4;
                isGuarding = true;
                break;
            case CardId::PAROV_L_EXECUTEUR:
                description = "{Dépense}: Gagnez 3 Combat. Si vous avez un autre allié de la Guilde en jeu, piochez une carte.";
                defense = 5;
                combatValue = 3;
                isGuarding = true;
                break;
            case CardId::RAKE_MAITRE_ASSASSIN:
                description = "{Dépense}: Gagnez 4 Combat. Vous pouvez assommer un champion ciblé.";
                defense = 7;
                combatValue = 4;
                isGuarding = false;
                break;
            case CardId::RASMUS_LE_CONTREBANDIER:
                description = "{Dépense}: Gagnez 2 Or. Si vous avez un autre allié de la Guilde en jeu, placez la prochaine carte que vous achetez ce tour au-dessus de votre pioche.";
                defense = 5;
                goldValue = 2;
                isGuarding = false;
                break;
            case CardId::BANDIT_DES_RUES:
                description = "{Dépense}: Gagnez 1 Or ou gagnez 2 Combat.";
                defense = 4;
                goldValue = 1;
                combatValue = 2;
                isGuarding = false;
                break;
                
            // ========== NECROS CHAMPIONS ==========
            case CardId::PRETRE_DU_CULTE:
                description = "{Dépense}: Gagnez 1 Or ou gagnez 1 Combat. Si vous avez un autre allié Nécros en jeu, gagnez 4 Combat.";
                defense = 4;
                goldValue = 1;
                combatValue = 4;
                isGuarding = false;
                break;
            case CardId::CULTISTE_DE_LA_MORT:
                description = "{Dépense}: Gagnez 2 Combat.";
                defense = 3;
                combatValue = 2;
                isGuarding = true;
                break;
            case CardId::RAYLA_TISSEUSE_DE_FINS:
                description = "{Dépense}: Gagnez 3 Combat. Si vous avez un autre allié Nécros en jeu, piochez une carte.";
                defense = 4;
                combatValue = 3;
                isGuarding = false;
                break;
            case CardId::KRYTHOS_MAITRE_VAMPIRE:
                description = "{Dépense}: Gagnez 3 Combat. Vous pouvez sacrifier une carte de votre main ou défausse pour gagner 3 Combat supplémentaires.";
                defense = 6;
                combatValue = 3;
                isGuarding = false;
                break;
            case CardId::LYS_L_INAPPARENT:
                description = "{Dépense}: Gagnez 2 Combat. Vous pouvez sacrifier une carte de votre main ou défausse pour gagner 2 Combat supplémentaires.";
                defense = 5;
                combatValue = 2;
                isGuarding = true;
                break;
            case CardId::TYRANNOR_LE_DEVOREUR:
                description = "{Dépense}: Gagnez 4 Combat. Vous pouvez sacrifier jusqu'à deux cartes de votre main ou défausse. Si vous avez un autre allié Nécros en jeu, piochez une carte.";
                defense = 6;
                combatValue = 4;
                isGuarding = true;
                break;
            case CardId::VARRICK_LE_NECROMANCIEN:
                description = "{Dépense}: Prenez un champion de votre défausse et placez-le au-dessus de votre pioche. Si vous avez un autre allié Nécros en jeu, piochez une carte.";
                defense = 3;
                isGuarding = false;
                break;
                
            // ========== WILD CHAMPIONS ==========
            case CardId::BROELYN_TISSEUSE_DE_SAVOIRS:
                description = "{Dépense}: Gagnez 2 Or. Si vous avez un autre allié Sauvage en jeu, l'adversaire défausse une carte.";
                defense = 6;
                goldValue = 2;
                isGuarding = false;
                break;
            case CardId::CRON_LE_BERSERKER:
                description = "{Dépense}: Gagnez 5 Combat. Si vous avez un autre allié Sauvage en jeu, piochez une carte.";
                defense = 6;
                combatValue = 5;
                isGuarding = false;
                break;
            case CardId::LOUP_TERRIFIANT:
                description = "{Dépense}: Gagnez 3 Combat. Si vous avez un autre allié Sauvage en jeu, gagnez 4 Combat.";
                defense = 5;
                combatValue = 3;
                isGuarding = true;
                break;
            case CardId::GRAK_GEANT_DE_LA_TEMPETE:
                description = "{Dépense}: Gagnez 6 Combat. Vous pouvez piocher une carte. Si vous le faites, défaussez une carte. Si vous avez un autre allié Sauvage en jeu, piochez une carte puis défaussez une carte.";
                defense = 7;
                combatValue = 6;
                isGuarding = true;
                break;
            case CardId::GROGNARD_ORQUE:
                description = "{Dépense}: Gagnez 2 Combat. Si vous avez un autre allié Sauvage en jeu, piochez une carte.";
                defense = 3;
                combatValue = 2;
                isGuarding = true;
                break;
            case CardId::TORGEN_BRISE_PIERRE:
                description = "{Dépense}: Gagnez 4 Combat. L'adversaire défausse une carte.";
                defense = 7;
                combatValue = 4;
                isGuarding = true;
                break;
            case CardId::SHAMANE_DES_LOUPS:
                description = "{Dépense}: Gagnez 2 Combat +1 Combat pour chaque autre carte Sauvage que vous avez en jeu.";
                defense = 4;
                combatValue = 2;
                isGuarding = false;
                break;
            default:
                description = "Champion non definie.";
                break;
        }
        
        defenseActuelle = defense;
}

void ChampionCard::play(Player* owner, Game* game) {
    std::cout << owner->getName() << " joue le champion " << name << std::endl;
    std::cout << "Defense: " << defenseActuelle;
    if (isGuarding) {
        std::cout << " (Garde)";
    }
    std::cout << std::endl;
    
    // Quand un champion est joué depuis la main, il est automatiquement activé ce tour-ci
    std::cout << "\n🛡️  " << name << " active immédiatement sa capacité:" << std::endl;
    activateAbility(owner, game);
}

void ChampionCard::sacrifice(Player* owner, Game* game, bool fromEffects) {
    // Les champions ne peuvent pas être sacrifiés volontairement, 
    // seulement par des effets de cartes (fromEffects = true)
    if (!fromEffects) {
        std::cout << "Impossible de sacrifier " << name << " : les champions ne peuvent pas être sacrifiés volontairement." << std::endl;
        return;
    }
    
    // Les champions peuvent avoir des effets spéciaux quand ils sont sacrifiés
    switch (cardId) {
        // Pour l'instant, aucun champion n'a d'effet de sacrifice spécial
        // Mais on peut en ajouter ici plus tard
        default:
            std::cout << name << " sacrifié (aucun effet spécial)" << std::endl;
            break;
    }

    // Retirer le champion du jeu et l'ajouter à la zone de sacrifice
    // Le champion doit être retiré de la zone des champions en jeu
    auto& championsEnJeu = owner->getChampionsEnJeu();
    auto it = std::find(championsEnJeu.begin(), championsEnJeu.end(), this);
    if (it != championsEnJeu.end()) {
        championsEnJeu.erase(it);
        std::cout << "Champion " << name << " retiré du jeu de " << owner->getName() << std::endl;
    }
    
    // Ajouter à la zone de sacrifice
    owner->removeCardFromPlay(this);
    game->getMarket()->addSacrificedCard(this);
}

void ChampionCard::activateAbility(Player* owner, Game* game) {    
    if (isActivated) {
        std::cout << name << " a déjà été activé ce tour." << std::endl;
        return;
    }
    
    std::cout << owner->getName() << " active " << name << std::endl;
    
    // Execute the champion's expend ability based on card type
    switch (cardId) {
        // ========== IMPERIAL CHAMPIONS ==========
        case CardId::ARKUS_DRAGON_IMPERIAL:
            (void)game;  // Not needed for Arkus
            // Primary effect: +5 combat and draw a card
            owner->addCombat(combatValue);  // combatValue = 5
            std::cout << "Gagne " << combatValue << " Combat" << std::endl;
            
            owner->draw(1);
            std::cout << "Pioche 1 carte" << std::endl;
            
            // Check for Imperial ally effect
            if (owner->countCardsInPlayByFaction(Faction::IMPERIAL) > 1) {  // >1 because this champion counts
                owner->addHealth(healthValue);  // healthValue = 6
                std::cout << "Effet allié Impérial: Gagne " << healthValue << " Santé supplémentaires" << std::endl;
            }
            break;
            
        case CardId::DARIAN_MAGE_DE_GUERRE:
            (void)game;
            std::cout << "Choisissez: (1) Gagner " << combatValue << " Combat OU (2) Gagner " << healthValue << " Santé: ";
            int darianChoice;
            std::cin >> darianChoice;
            if (darianChoice == 1) {
                owner->addCombat(combatValue);
                std::cout << "Gagne " << combatValue << " Combat" << std::endl;
            } else {
                owner->addHealth(healthValue);
                std::cout << "Gagne " << healthValue << " Santé" << std::endl;
            }
            break;
            
        case CardId::CRISTOV_LE_JUSTE:
            (void)game;
            owner->addCombat(combatValue);
            std::cout << "Gagne " << combatValue << " Combat" << std::endl;
            owner->addHealth(healthValue);
            std::cout << "Gagne " << healthValue << " Santé" << std::endl;
            if (owner->countCardsInPlayByFaction(Faction::IMPERIAL) > 1) {
                owner->draw(1);
                std::cout << "Effet allié Impérial: Pioche 1 carte" << std::endl;
            }
            break;
            
        case CardId::KRAKA_GRAND_PRETRE:
            (void)game;
            owner->addHealth(healthValue);
            std::cout << "Gagne " << healthValue << " Santé" << std::endl;
            owner->draw(1);
            std::cout << "Pioche 1 carte" << std::endl;
            if (owner->countCardsInPlayByFaction(Faction::IMPERIAL) > 1) {
                int championCount = owner->getChampionsEnJeu().size();
                int bonusHealth = healthValue * championCount;
                owner->addHealth(bonusHealth);
                std::cout << "Effet allié Impérial: Gagne " << bonusHealth << " Santé (" << healthValue << " x " << championCount << " champions)" << std::endl;
            }
            break;
            
        case CardId::HOMME_D_ARMES: {
            (void)game;
            int guardCount = 0;
            for (const auto* champ : owner->getChampionsEnJeu()) {
                if (champ != this && champ->getGuarding()) {
                    guardCount++;
                }
            }
            int totalCombat = combatValue + guardCount;
            owner->addCombat(totalCombat);
            std::cout << "Gagne " << totalCombat << " Combat (" << combatValue << " base";
            if (guardCount > 0) {
                std::cout << " + " << guardCount << " autres gardes";
            }
            std::cout << ")" << std::endl;
            break;
        }
            
        case CardId::MAITRE_WEYAN: {
            (void)game;
            int otherChampions = owner->getChampionsEnJeu().size() - 1;
            int totalCombat = combatValue + otherChampions;
            owner->addCombat(totalCombat);
            std::cout << "Gagne " << totalCombat << " Combat (" << combatValue << " base";
            if (otherChampions > 0) {
                std::cout << " + " << otherChampions << " autres champions";
            }
            std::cout << ")" << std::endl;
            break;
        }
            
        case CardId::PERCEPTEUR_DE_DIME:
            (void)game;
            std::cout << "Choisissez: (1) Gagner " << goldValue << " Or OU (2) Gagner " << healthValue << " Santé par champion: ";
            int percepteurChoice;
            std::cin >> percepteurChoice;
            if (percepteurChoice == 1) {
                owner->addGold(goldValue);
                std::cout << "Gagne " << goldValue << " Or" << std::endl;
            } else {
                int championCount = owner->getChampionsEnJeu().size();
                int totalHealth = healthValue * championCount;
                owner->addHealth(totalHealth);
                std::cout << "Gagne " << totalHealth << " Santé (" << healthValue << " x " << championCount << " champions)" << std::endl;
            }
            break;
            
        // ========== GUILD CHAMPIONS ==========
        case CardId::BORG_MERCENAIRE_OGRE:
            (void)game;
            owner->addCombat(combatValue);
            std::cout << "Gagne " << combatValue << " Combat" << std::endl;
            break;
            
        case CardId::MYROS_MAGE_DE_LA_GUILDE:
            (void)game;
            owner->addGold(goldValue);
            std::cout << "Gagne " << goldValue << " Or" << std::endl;
            if (owner->countCardsInPlayByFaction(Faction::GUILDE) > 1) {
                owner->addCombat(combatValue);
                std::cout << "Effet allié Guilde: Gagne " << combatValue << " Combat" << std::endl;
            }
            break;
            
        case CardId::PAROV_L_EXECUTEUR:
            (void)game;
            owner->addCombat(combatValue);
            std::cout << "Gagne " << combatValue << " Combat" << std::endl;
            if (owner->countCardsInPlayByFaction(Faction::GUILDE) > 1) {
                owner->draw(1);
                std::cout << "Effet allié Guilde: Pioche 1 carte" << std::endl;
            }
            break;
            
        case CardId::RAKE_MAITRE_ASSASSIN: {
            owner->addCombat(combatValue);
            std::cout << "Gagne " << combatValue << " Combat" << std::endl;
            
            Player* opponent = game->getOpponent(owner);
            auto targetable = opponent->getTargetableChampions();
            if (!targetable.empty()) {
                std::cout << "Voulez-vous assommer un champion? (1=Oui, 0=Non): ";
                int choice;
                std::cin >> choice;
                if (choice == 1) {
                    std::cout << "Champions adverses:" << std::endl;
                    for (size_t i = 0; i < targetable.size(); i++) {
                        std::cout << (i+1) << ". " << targetable[i]->getName() << std::endl;
                    }
                    std::cout << "Quel champion assommer? (1-" << targetable.size() << "): ";
                    int champChoice;
                    std::cin >> champChoice;
                    if (champChoice >= 1 && champChoice <= static_cast<int>(targetable.size())) {
                        opponent->stunChampion(targetable[champChoice - 1]);
                    }
                }
            }
            break;
        }
            
        case CardId::RASMUS_LE_CONTREBANDIER:
            (void)game;
            owner->addGold(goldValue);
            std::cout << "Gagne " << goldValue << " Or" << std::endl;
            if (owner->countCardsInPlayByFaction(Faction::GUILDE) > 1) {
                owner->setNextAnyCardToTopOfDeck(true);
                std::cout << "Effet allié Guilde: La prochaine carte achetée ira au-dessus de votre pioche" << std::endl;
            }
            break;
            
        case CardId::BANDIT_DES_RUES:
            (void)game;
            std::cout << "Choisissez: (1) Gagner " << goldValue << " Or OU (2) Gagner " << combatValue << " Combat: ";
            int banditChoice;
            std::cin >> banditChoice;
            if (banditChoice == 1) {
                owner->addGold(goldValue);
                std::cout << "Gagne " << goldValue << " Or" << std::endl;
            } else {
                owner->addCombat(combatValue);
                std::cout << "Gagne " << combatValue << " Combat" << std::endl;
            }
            break;
            
        // ========== NECROS CHAMPIONS ==========
        case CardId::PRETRE_DU_CULTE:
            (void)game;
            std::cout << "Choisissez: (1) Gagner " << goldValue << " Or OU (2) Gagner 1 Combat: ";
            int pretreChoice;
            std::cin >> pretreChoice;
            if (pretreChoice == 1) {
                owner->addGold(goldValue);
                std::cout << "Gagne " << goldValue << " Or" << std::endl;
            } else {
                owner->addCombat(1);
                std::cout << "Gagne 1 Combat" << std::endl;
            }
            if (owner->countCardsInPlayByFaction(Faction::NECROS) > 1) {
                owner->addCombat(combatValue);
                std::cout << "Effet allié Nécros: Gagne " << combatValue << " Combat" << std::endl;
            }
            break;
            
        case CardId::CULTISTE_DE_LA_MORT:
            (void)game;
            owner->addCombat(combatValue);
            std::cout << "Gagne " << combatValue << " Combat" << std::endl;
            break;
            
        case CardId::RAYLA_TISSEUSE_DE_FINS:
            (void)game;
            owner->addCombat(combatValue);
            std::cout << "Gagne " << combatValue << " Combat" << std::endl;
            if (owner->countCardsInPlayByFaction(Faction::NECROS) > 1) {
                owner->draw(1);
                std::cout << "Effet allié Nécros: Pioche 1 carte" << std::endl;
            }
            break;
            
        case CardId::KRYTHOS_MAITRE_VAMPIRE: {
            owner->addCombat(combatValue);
            std::cout << "Gagne " << combatValue << " Combat" << std::endl;
            
            std::cout << "Voulez-vous sacrifier une carte pour +3 Combat? (1=Oui, 0=Non): ";
            int krythosChoice;
            std::cin >> krythosChoice;
            if (krythosChoice == 1) {
                std::cout << "Choisir depuis: (1=Main, 2=Défausse, 0=Annuler): ";
                int source;
                std::cin >> source;
                if (source == 1 && !owner->getHand().empty()) {
                    std::cout << "Cartes en main:" << std::endl;
                    for (size_t i = 0; i < owner->getHand().size(); i++) {
                        std::cout << (i+1) << ". " << owner->getHand()[i]->getName() << std::endl;
                    }
                    std::cout << "Quelle carte sacrifier? (1-" << owner->getHand().size() << "): ";
                    int cardChoice;
                    std::cin >> cardChoice;
                    if (cardChoice >= 1 && cardChoice <= static_cast<int>(owner->getHand().size())) {
                        Card* card = owner->getHand()[cardChoice - 1];
                        card->sacrifice(owner, game, true);
                        owner->removeCardFromHand(card);
                        owner->addCombat(3);
                        std::cout << "Gagne 3 Combat supplémentaires!" << std::endl;
                    }
                } else if (source == 2 && !owner->getDiscardPile().empty()) {
                    std::cout << "Cartes en défausse:" << std::endl;
                    const auto& discard = owner->getDiscardPile();
                    for (size_t i = 0; i < discard.size(); i++) {
                        std::cout << (i+1) << ". " << discard[i]->getName() << std::endl;
                    }
                    std::cout << "Quelle carte sacrifier? (1-" << discard.size() << "): ";
                    int cardChoice;
                    std::cin >> cardChoice;
                    if (cardChoice >= 1 && cardChoice <= static_cast<int>(discard.size())) {
                        Card* card = const_cast<Card*>(discard[cardChoice - 1]);
                        card->sacrifice(owner, game, true);
                        owner->removeCardFromDiscard(card);
                        owner->addCombat(3);
                        std::cout << "Gagne 3 Combat supplémentaires!" << std::endl;
                    }
                }
            }
            break;
        }
            
        case CardId::LYS_L_INAPPARENT: {
            (void)game;
            owner->addCombat(combatValue);
            std::cout << "Gagne " << combatValue << " Combat" << std::endl;
            
            std::cout << "Voulez-vous sacrifier une carte pour +2 Combat? (1=Oui, 0=Non): ";
            int lysChoice;
            std::cin >> lysChoice;
            if (lysChoice == 1) {
                std::cout << "Choisir depuis: (1=Main, 2=Défausse, 0=Annuler): ";
                int source;
                std::cin >> source;
                if (source == 1 && !owner->getHand().empty()) {
                    std::cout << "Cartes en main:" << std::endl;
                    for (size_t i = 0; i < owner->getHand().size(); i++) {
                        std::cout << (i+1) << ". " << owner->getHand()[i]->getName() << std::endl;
                    }
                    std::cout << "Quelle carte sacrifier? (1-" << owner->getHand().size() << "): ";
                    int cardChoice;
                    std::cin >> cardChoice;
                    if (cardChoice >= 1 && cardChoice <= static_cast<int>(owner->getHand().size())) {
                        Card* card = owner->getHand()[cardChoice - 1];
                        card->sacrifice(owner, game, true);
                        owner->removeCardFromHand(card);
                        owner->addCombat(2);
                        std::cout << "Gagne 2 Combat supplémentaires!" << std::endl;
                    }
                } else if (source == 2 && !owner->getDiscardPile().empty()) {
                    std::cout << "Cartes en défausse:" << std::endl;
                    const auto& discard = owner->getDiscardPile();
                    for (size_t i = 0; i < discard.size(); i++) {
                        std::cout << (i+1) << ". " << discard[i]->getName() << std::endl;
                    }
                    std::cout << "Quelle carte sacrifier? (1-" << discard.size() << "): ";
                    int cardChoice;
                    std::cin >> cardChoice;
                    if (cardChoice >= 1 && cardChoice <= static_cast<int>(discard.size())) {
                        Card* card = const_cast<Card*>(discard[cardChoice - 1]);
                        card->sacrifice(owner, game, true);
                        owner->removeCardFromDiscard(card);
                        owner->addCombat(2);
                        std::cout << "Gagne 2 Combat supplémentaires!" << std::endl;
                    }
                }
            }
            break;
        }
            
        case CardId::TYRANNOR_LE_DEVOREUR: {
            owner->addCombat(combatValue);
            std::cout << "Gagne " << combatValue << " Combat" << std::endl;
            
            std::cout << "Voulez-vous sacrifier des cartes? (1=Oui, 0=Non): ";
            int tyrannorChoice;
            std::cin >> tyrannorChoice;
            if (tyrannorChoice == 1) {
                for (int i = 0; i < 2; i++) {
                    std::cout << "Sacrifice " << (i+1) << "/2 - Choisir: (1=Main, 2=Défausse, 0=Arrêter): ";
                    int source;
                    std::cin >> source;
                    if (source == 0) break;
                    if (source == 1 && !owner->getHand().empty()) {
                        std::cout << "Cartes en main:" << std::endl;
                        for (size_t j = 0; j < owner->getHand().size(); j++) {
                            std::cout << (j+1) << ". " << owner->getHand()[j]->getName() << std::endl;
                        }
                        std::cout << "Quelle carte? (1-" << owner->getHand().size() << "): ";
                        int cardChoice;
                        std::cin >> cardChoice;
                        if (cardChoice >= 1 && cardChoice <= static_cast<int>(owner->getHand().size())) {
                            Card* card = owner->getHand()[cardChoice - 1];
                            card->sacrifice(owner, game, true);
                            owner->removeCardFromHand(card);
                        }
                    } else if (source == 2 && !owner->getDiscardPile().empty()) {
                        std::cout << "Cartes en défausse:" << std::endl;
                        const auto& discard = owner->getDiscardPile();
                        for (size_t j = 0; j < discard.size(); j++) {
                            std::cout << (j+1) << ". " << discard[j]->getName() << std::endl;
                        }
                        std::cout << "Quelle carte? (1-" << discard.size() << "): ";
                        int cardChoice;
                        std::cin >> cardChoice;
                        if (cardChoice >= 1 && cardChoice <= static_cast<int>(discard.size())) {
                            Card* card = const_cast<Card*>(discard[cardChoice - 1]);
                            card->sacrifice(owner, game, true);
                            owner->removeCardFromDiscard(card);
                        }
                    }
                }
            }
            if (owner->countCardsInPlayByFaction(Faction::NECROS) > 1) {
                owner->draw(1);
                std::cout << "Effet allié Nécros: Pioche 1 carte" << std::endl;
            }
            break;
        }
            
        case CardId::VARRICK_LE_NECROMANCIEN: {
            (void)game;
            const auto& discard = owner->getDiscardPile();
            std::vector<ChampionCard*> championsInDiscard;
            for (Card* card : discard) {
                ChampionCard* champ = dynamic_cast<ChampionCard*>(card);
                if (champ) championsInDiscard.push_back(champ);
            }
            if (!championsInDiscard.empty()) {
                std::cout << "Champions en défausse:" << std::endl;
                for (size_t i = 0; i < championsInDiscard.size(); i++) {
                    std::cout << (i+1) << ". " << championsInDiscard[i]->getName() << std::endl;
                }
                std::cout << "Quel champion récupérer? (1-" << championsInDiscard.size() << ", 0=Aucun): ";
                int choice;
                std::cin >> choice;
                if (choice >= 1 && choice <= static_cast<int>(championsInDiscard.size())) {
                    owner->moveCardFromDiscardToTopOfDeck(championsInDiscard[choice - 1]);
                }
            } else {
                std::cout << "Aucun champion en défausse." << std::endl;
            }
            if (owner->countCardsInPlayByFaction(Faction::NECROS) > 1) {
                owner->draw(1);
                std::cout << "Effet allié Nécros: Pioche 1 carte" << std::endl;
            }
            break;
        }
        
        // ========== WILD CHAMPIONS ==========
        case CardId::BROELYN_TISSEUSE_DE_SAVOIRS: {
            (void)game;
            owner->addGold(goldValue);
            std::cout << "Gagne " << goldValue << " Or" << std::endl;
            if (owner->countCardsInPlayByFaction(Faction::SAUVAGE) > 1) {
                Player* opponent = game->getOpponent(owner);
                if (!opponent->getHand().empty()) {
                    std::cout << "L'adversaire doit défausser une carte." << std::endl;
                    // Opponent chooses which card to discard
                    std::cout << "Adversaire, cartes en main:" << std::endl;
                    for (size_t i = 0; i < opponent->getHand().size(); i++) {
                        std::cout << (i+1) << ". " << opponent->getHand()[i]->getName() << std::endl;
                    }
                    std::cout << "Quelle carte défausser? (1-" << opponent->getHand().size() << "): ";
                    int discardChoice;
                    std::cin >> discardChoice;
                    if (discardChoice >= 1 && discardChoice <= static_cast<int>(opponent->getHand().size())) {
                        Card* discarded = opponent->getHand()[discardChoice - 1];
                        opponent->removeCardFromHand(discarded);
                        opponent->addToDiscardPile(discarded);
                        std::cout << "L'adversaire défausse " << discarded->getName() << std::endl;
                    }
                }
            }
            break;
        }
            
        case CardId::CRON_LE_BERSERKER:
            (void)game;
            owner->addCombat(combatValue);
            std::cout << "Gagne " << combatValue << " Combat" << std::endl;
            if (owner->countCardsInPlayByFaction(Faction::SAUVAGE) > 1) {
                owner->draw(1);
                std::cout << "Effet allié Sauvage: Pioche 1 carte" << std::endl;
            }
            break;
            
        case CardId::LOUP_TERRIFIANT:
            (void)game;
            owner->addCombat(combatValue);
            std::cout << "Gagne " << combatValue << " Combat" << std::endl;
            if (owner->countCardsInPlayByFaction(Faction::SAUVAGE) > 1) {
                owner->addCombat(4);
                std::cout << "Effet allié Sauvage: Gagne 4 Combat supplémentaires" << std::endl;
            }
            break;
            
        case CardId::GRAK_GEANT_DE_LA_TEMPETE: {
            owner->addCombat(combatValue);
            std::cout << "Gagne " << combatValue << " Combat" << std::endl;
            
            std::cout << "Voulez-vous piocher puis défausser une carte? (1=Oui, 0=Non): ";
            int grakChoice;
            std::cin >> grakChoice;
            if (grakChoice == 1) {
                owner->draw(1);
                if (!owner->getHand().empty()) {
                    std::cout << "Cartes en main:" << std::endl;
                    for (size_t i = 0; i < owner->getHand().size(); i++) {
                        std::cout << (i+1) << ". " << owner->getHand()[i]->getName() << std::endl;
                    }
                    std::cout << "Quelle carte défausser? (1-" << owner->getHand().size() << "): ";
                    int discardChoice;
                    std::cin >> discardChoice;
                    if (discardChoice >= 1 && discardChoice <= static_cast<int>(owner->getHand().size())) {
                        Card* card = owner->getHand()[discardChoice - 1];
                        owner->removeCardFromHand(card);
                        owner->addToDiscardPile(card);
                    }
                }
            }
            
            if (owner->countCardsInPlayByFaction(Faction::SAUVAGE) > 1) {
                owner->draw(1);
                std::cout << "Effet allié Sauvage: Pioche 1 carte" << std::endl;
                if (!owner->getHand().empty()) {
                    std::cout << "Cartes en main:" << std::endl;
                    for (size_t i = 0; i < owner->getHand().size(); i++) {
                        std::cout << (i+1) << ". " << owner->getHand()[i]->getName() << std::endl;
                    }
                    std::cout << "Quelle carte défausser? (1-" << owner->getHand().size() << "): ";
                    int discardChoice;
                    std::cin >> discardChoice;
                    if (discardChoice >= 1 && discardChoice <= static_cast<int>(owner->getHand().size())) {
                        Card* card = owner->getHand()[discardChoice - 1];
                        owner->removeCardFromHand(card);
                        owner->addToDiscardPile(card);
                    }
                }
            }
            break;
        }
            
        case CardId::GROGNARD_ORQUE:
            (void)game;
            owner->addCombat(combatValue);
            std::cout << "Gagne " << combatValue << " Combat" << std::endl;
            if (owner->countCardsInPlayByFaction(Faction::SAUVAGE) > 1) {
                owner->draw(1);
                std::cout << "Effet allié Sauvage: Pioche 1 carte" << std::endl;
            }
            break;
            
        case CardId::TORGEN_BRISE_PIERRE: {
            owner->addCombat(combatValue);
            std::cout << "Gagne " << combatValue << " Combat" << std::endl;
            
            Player* opponent = game->getOpponent(owner);
            if (!opponent->getHand().empty()) {
                std::cout << "L'adversaire doit défausser une carte." << std::endl;
                std::cout << "Adversaire, cartes en main:" << std::endl;
                for (size_t i = 0; i < opponent->getHand().size(); i++) {
                    std::cout << (i+1) << ". " << opponent->getHand()[i]->getName() << std::endl;
                }
                std::cout << "Quelle carte défausser? (1-" << opponent->getHand().size() << "): ";
                int discardChoice;
                std::cin >> discardChoice;
                if (discardChoice >= 1 && discardChoice <= static_cast<int>(opponent->getHand().size())) {
                    Card* discarded = opponent->getHand()[discardChoice - 1];
                    opponent->removeCardFromHand(discarded);
                    opponent->addToDiscardPile(discarded);
                    std::cout << "L'adversaire défausse " << discarded->getName() << std::endl;
                }
            }
            break;
        }
            
        case CardId::SHAMANE_DES_LOUPS:
            (void)game;
            owner->addCombat(combatValue);
            std::cout << "Gagne " << combatValue << " Combat" << std::endl;
            {
                int wildCount = owner->countCardsInPlayByFaction(Faction::SAUVAGE);
                if (wildCount > 1) {
                    int bonusCombat = wildCount - 1;
                    owner->addCombat(bonusCombat);
                    std::cout << "Gagne " << bonusCombat << " Combat supplémentaire pour " << (wildCount - 1) << " autre(s) carte(s) Sauvage(s)" << std::endl;
                }
            }
            break;
       
        default:
            std::cout << "Ce champion n'a pas d'effet d'activation défini." << std::endl;
            break;
    }
    
    // Mark as activated for this turn
    isActivated = true;
}

void ChampionCard::takeDamage(int damage) {
    defenseActuelle -= damage;
    if (defenseActuelle < 0) {
        defenseActuelle = 0;
    }
}

// ========================================
// FACTORY METHODS FOR CREATING CHAMPIONS
// ========================================

// ========== IMPERIAL CHAMPIONS ==========
ChampionCard* ChampionCard::createArkusDragonImperial() {
    return new ChampionCard("Arkus, Dragon Impérial", 8, Faction::IMPERIAL, CardId::ARKUS_DRAGON_IMPERIAL);
}

ChampionCard* ChampionCard::createDarianMageDeGuerre() {
    return new ChampionCard("Darian, Mage de Guerre", 4, Faction::IMPERIAL, CardId::DARIAN_MAGE_DE_GUERRE);
}

ChampionCard* ChampionCard::createCristovLeJuste() {
    return new ChampionCard("Cristov le Juste", 5, Faction::IMPERIAL, CardId::CRISTOV_LE_JUSTE);
}

ChampionCard* ChampionCard::createKrakaGrandPretre() {
    return new ChampionCard("Kraka, Grand Prêtre", 6, Faction::IMPERIAL, CardId::KRAKA_GRAND_PRETRE);
}

ChampionCard* ChampionCard::createHommeDArmes() {
    return new ChampionCard("Homme d'Armes", 3, Faction::IMPERIAL, CardId::HOMME_D_ARMES);
}

ChampionCard* ChampionCard::createMaitreWeyan() {
    return new ChampionCard("Maître Weyan", 4, Faction::IMPERIAL, CardId::MAITRE_WEYAN);
}

ChampionCard* ChampionCard::createPercepteurDeDime() {
    return new ChampionCard("Percepteur de Dîme", 2, Faction::IMPERIAL, CardId::PERCEPTEUR_DE_DIME);
}

// ========== GUILD CHAMPIONS ==========
ChampionCard* ChampionCard::createBorgMercenaireOgre() {
    return new ChampionCard("Borg, Mercenaire Ogre", 6, Faction::GUILDE, CardId::BORG_MERCENAIRE_OGRE);
}

ChampionCard* ChampionCard::createMyrosMageDeLaGuilde() {
    return new ChampionCard("Myros, Mage de la Guilde", 5, Faction::GUILDE, CardId::MYROS_MAGE_DE_LA_GUILDE);
}

ChampionCard* ChampionCard::createParovLExecuteur() {
    return new ChampionCard("Parov l'Exécuteur", 5, Faction::GUILDE, CardId::PAROV_L_EXECUTEUR);
}

ChampionCard* ChampionCard::createRakeMaitreAssassin() {
    return new ChampionCard("Rake, Maître Assassin", 7, Faction::GUILDE, CardId::RAKE_MAITRE_ASSASSIN);
}

ChampionCard* ChampionCard::createRasmusLeContrebandier() {
    return new ChampionCard("Rasmus le Contrebandier", 4, Faction::GUILDE, CardId::RASMUS_LE_CONTREBANDIER);
}

ChampionCard* ChampionCard::createBanditDesRues() {
    return new ChampionCard("Bandit des Rues", 3, Faction::GUILDE, CardId::BANDIT_DES_RUES);
}

// ========== NECROS CHAMPIONS ==========
ChampionCard* ChampionCard::createPretreDuCulte() {
    return new ChampionCard("Prêtre du Culte", 3, Faction::NECROS, CardId::PRETRE_DU_CULTE);
}

ChampionCard* ChampionCard::createCultisteDeLaMort() {
    return new ChampionCard("Cultiste de la Mort", 2, Faction::NECROS, CardId::CULTISTE_DE_LA_MORT);
}

ChampionCard* ChampionCard::createRaylaTisseuseDeFins() {
    return new ChampionCard("Rayla, Tisseuse de Fins", 4, Faction::NECROS, CardId::RAYLA_TISSEUSE_DE_FINS);
}

ChampionCard* ChampionCard::createKrythosMaitreVampire() {
    return new ChampionCard("Krythos, Maître Vampire", 7, Faction::NECROS, CardId::KRYTHOS_MAITRE_VAMPIRE);
}

ChampionCard* ChampionCard::createLysLInapparent() {
    return new ChampionCard("Lys l'Inapparent", 6, Faction::NECROS, CardId::LYS_L_INAPPARENT);
}

ChampionCard* ChampionCard::createTyrannorLeDevoreur() {
    return new ChampionCard("Tyrannor le Dévoreur", 8, Faction::NECROS, CardId::TYRANNOR_LE_DEVOREUR);
}

ChampionCard* ChampionCard::createVarrickLeNecromancien() {
    return new ChampionCard("Varrick le Nécromancien", 5, Faction::NECROS, CardId::VARRICK_LE_NECROMANCIEN);
}

// ========== WILD CHAMPIONS ==========
ChampionCard* ChampionCard::createBroelynTisseuseDeSorts() {
    return new ChampionCard("Broelyn Tisseuse de Savoirs", 4, Faction::SAUVAGE, CardId::BROELYN_TISSEUSE_DE_SAVOIRS);
}

ChampionCard* ChampionCard::createCronLeBerserker() {
    return new ChampionCard("Cron le Berserker", 6, Faction::SAUVAGE, CardId::CRON_LE_BERSERKER);
}

ChampionCard* ChampionCard::createLoupTerrifiant() {
    return new ChampionCard("Loup Terrifiant", 5, Faction::SAUVAGE, CardId::LOUP_TERRIFIANT);
}

ChampionCard* ChampionCard::createGrakGeantDeTempete() {
    return new ChampionCard("Grak Géant de Tempête", 8, Faction::SAUVAGE, CardId::GRAK_GEANT_DE_LA_TEMPETE);
}

ChampionCard* ChampionCard::createGrognardOrc() {
    return new ChampionCard("Grognard Orque", 3, Faction::SAUVAGE, CardId::GROGNARD_ORQUE);
}

ChampionCard* ChampionCard::createTorgenFendRoc() {
    return new ChampionCard("Torgen Brise-Pierre", 7, Faction::SAUVAGE, CardId::TORGEN_BRISE_PIERRE);
}

ChampionCard* ChampionCard::createChamanLoup() {
    return new ChampionCard("Shamane des Loups", 2, Faction::SAUVAGE, CardId::SHAMANE_DES_LOUPS);
}