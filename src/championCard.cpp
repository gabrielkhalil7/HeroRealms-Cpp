#include "../include/championCard.hpp"

ChampionCard::ChampionCard(const std::string& n, int c, Faction f, CardId id) 
    : Card(n, c, f, id), isGuarding(false), isActivated(false) {
        // initialisation des descriptions
        switch (id) {
            case CardId::KRYTHOS_MAITRE_VAMPIRE:
                description = "Gagnez 3 de Combat et vous avez le choix de sacrifier une carte de votre main ou de votre défausse pour gagner 3 Combat supplémentaires.";
                defense = 6;
                combatValue = 3;
                break;
            default:
                description = "Champion non definie.";
                break;
        }
}