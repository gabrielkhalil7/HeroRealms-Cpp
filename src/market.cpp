#include "../include/market.hpp"
#include "../include/card.hpp"
#include "../include/actionCard.hpp"
#include "../include/itemCard.hpp"
#include <iostream>
#include <algorithm> 
#include <random>

Market::Market() { // initialisation du marche par defaut (remplissage des cartes)
    // Initialisation des vecteurs
    cartesVisibles = std::vector<Card*>();
    piocheDuMarche = std::vector<Card*>();
    gemmesDeFeu = std::vector<ItemCard*>();
    cartesSacrifiees = std::vector<Card*>();

    // TOUTES LES CARTES DU MARCHE
    // 16 gemmes de feu
    ItemCard* gemmesDeFeu1 = new ItemCard("Gemme de feu", 2, Faction::NEUTRE, CardId::GEMME_DE_FEU);
    ItemCard* gemmesDeFeu2 = new ItemCard("Gemme de feu", 2, Faction::NEUTRE, CardId::GEMME_DE_FEU);
    ItemCard* gemmesDeFeu3 = new ItemCard("Gemme de feu", 2, Faction::NEUTRE, CardId::GEMME_DE_FEU);
    ItemCard* gemmesDeFeu4 = new ItemCard("Gemme de feu", 2, Faction::NEUTRE, CardId::GEMME_DE_FEU);
    ItemCard* gemmesDeFeu5 = new ItemCard("Gemme de feu", 2, Faction::NEUTRE, CardId::GEMME_DE_FEU);
    ItemCard* gemmesDeFeu6 = new ItemCard("Gemme de feu", 2, Faction::NEUTRE, CardId::GEMME_DE_FEU);
    ItemCard* gemmesDeFeu7 = new ItemCard("Gemme de feu", 2, Faction::NEUTRE, CardId::GEMME_DE_FEU);
    ItemCard* gemmesDeFeu8 = new ItemCard("Gemme de feu", 2, Faction::NEUTRE, CardId::GEMME_DE_FEU);
    ItemCard* gemmesDeFeu9 = new ItemCard("Gemme de feu", 2, Faction::NEUTRE, CardId::GEMME_DE_FEU);
    ItemCard* gemmesDeFeu10 = new ItemCard("Gemme de feu", 2, Faction::NEUTRE, CardId::GEMME_DE_FEU);
    ItemCard* gemmesDeFeu11 = new ItemCard("Gemme de feu", 2, Faction::NEUTRE, CardId::GEMME_DE_FEU);
    ItemCard* gemmesDeFeu12 = new ItemCard("Gemme de feu", 2, Faction::NEUTRE, CardId::GEMME_DE_FEU);
    ItemCard* gemmesDeFeu13 = new ItemCard("Gemme de feu", 2, Faction::NEUTRE, CardId::GEMME_DE_FEU);
    ItemCard* gemmesDeFeu14 = new ItemCard("Gemme de feu", 2, Faction::NEUTRE, CardId::GEMME_DE_FEU);
    ItemCard* gemmesDeFeu15 = new ItemCard("Gemme de feu", 2, Faction::NEUTRE, CardId::GEMME_DE_FEU);
    ItemCard* gemmesDeFeu16 = new ItemCard("Gemme de feu", 2, Faction::NEUTRE, CardId::GEMME_DE_FEU);
    gemmesDeFeu.push_back(gemmesDeFeu1);
    gemmesDeFeu.push_back(gemmesDeFeu2);
    gemmesDeFeu.push_back(gemmesDeFeu3);
    gemmesDeFeu.push_back(gemmesDeFeu4);
    gemmesDeFeu.push_back(gemmesDeFeu5);
    gemmesDeFeu.push_back(gemmesDeFeu6);
    gemmesDeFeu.push_back(gemmesDeFeu7);
    gemmesDeFeu.push_back(gemmesDeFeu8);
    gemmesDeFeu.push_back(gemmesDeFeu9);
    gemmesDeFeu.push_back(gemmesDeFeu10);
    gemmesDeFeu.push_back(gemmesDeFeu11);
    gemmesDeFeu.push_back(gemmesDeFeu12);
    gemmesDeFeu.push_back(gemmesDeFeu13);
    gemmesDeFeu.push_back(gemmesDeFeu14);
    gemmesDeFeu.push_back(gemmesDeFeu15);
    gemmesDeFeu.push_back(gemmesDeFeu16);


    ActionCard* taxation1 = new ActionCard("Taxation", 1, Faction::IMPERIAL, CardId::TAXATION);
    ActionCard* taxation2 = new ActionCard("Taxation", 1, Faction::IMPERIAL, CardId::TAXATION);
    ActionCard* taxation3 = new ActionCard("Taxation", 1, Faction::IMPERIAL, CardId::TAXATION);
    ActionCard* serrerLesRangs = new ActionCard("Serrer les rangs", 3, Faction::IMPERIAL, CardId::SERRER_LES_RANGS);
    ActionCard* recrutement = new ActionCard("Recrutement", 2, Faction::IMPERIAL, CardId::RECRUTEMENT);
    ActionCard* recrutement2 = new ActionCard("Recrutement", 2, Faction::IMPERIAL, CardId::RECRUTEMENT);
    ActionCard* recrutement3 = new ActionCard("Recrutement", 2, Faction::IMPERIAL, CardId::RECRUTEMENT);
    ActionCard* intimidation = new ActionCard("Intimidation", 2, Faction::GUILDE, CardId::INTIMIDATION);
    ActionCard* intimidation2 = new ActionCard("Intimidation", 2, Faction::GUILDE, CardId::INTIMIDATION);
    ActionCard* benefice = new ActionCard("Bénéfice", 1, Faction::GUILDE, CardId::BENEFICE);
    ActionCard* benefice2 = new ActionCard("Bénéfice", 1, Faction::GUILDE, CardId::BENEFICE);
    ActionCard* benefice3 = new ActionCard("Bénéfice", 1, Faction::GUILDE, CardId::BENEFICE);
    ActionCard* influence = new ActionCard("Influence", 2, Faction::NECROS, CardId::INFLUENCE);
    ActionCard* influence2 = new ActionCard("Influence", 2, Faction::NECROS, CardId::INFLUENCE);
    ActionCard* influence3 = new ActionCard("Influence", 2, Faction::NECROS, CardId::INFLUENCE);
    ActionCard* commandement = new ActionCard("Commandement", 5, Faction::IMPERIAL, CardId::COMMANDEMENT);
    ActionCard* domination = new ActionCard("Domination", 7, Faction::IMPERIAL, CardId::DOMINATION);
    ActionCard* ralliementDesTroupes = new ActionCard("Ralliement des troupes", 4, Faction::IMPERIAL, CardId::RALLIEMENT_DES_TROUPES);
    ActionCard* paroleDePuissance = new ActionCard("Parole de puissance", 6, Faction::IMPERIAL, CardId::PAROLE_DE_PUISSANCE);
    ActionCard* potDeVin = new ActionCard("Pot-de-Vin", 3, Faction::GUILDE, CardId::POT_DE_VIN);
    ActionCard* potDeVin2 = new ActionCard("Pot-de-Vin", 3, Faction::GUILDE, CardId::POT_DE_VIN);
    ActionCard* potDeVin3 = new ActionCard("Pot-de-Vin", 3, Faction::GUILDE, CardId::POT_DE_VIN);
    ActionCard* menaceDeMort = new ActionCard("Menace de mort", 4, Faction::GUILDE, CardId::MENACE_DE_MORT);
    ActionCard* fourberie = new ActionCard("Fourberie", 5, Faction::GUILDE, CardId::FOURBERIE);
    ActionCard* bombeIncendiaire = new ActionCard("Bombe incendiaire", 8, Faction::GUILDE, CardId::BOMBE_INCENDIAIRE);
    ActionCard* miseAPrix = new ActionCard("Mise à prix", 4, Faction::GUILDE, CardId::MISE_A_PRIX);
    ActionCard* casserEtPiller = new ActionCard("Casser et piller", 6, Faction::GUILDE, CardId::CASSER_ET_PILLER);
    ActionCard* energieSombre = new ActionCard("Énergie sombre", 4, Faction::NECROS, CardId::ENERGIE_SOMBRE);
    ActionCard* sombreRecompense = new ActionCard("Sombre récompense", 5, Faction::NECROS, CardId::SOMBRE_RECOMPENSE);
    ActionCard* contactMortel = new ActionCard("Contact mortel", 1, Faction::NECROS, CardId::CONTACT_MORTEL);
    ActionCard* contactMortel2 = new ActionCard("Contact mortel", 1, Faction::NECROS, CardId::CONTACT_MORTEL);
    ActionCard* contactMortel3 = new ActionCard("Contact mortel", 1, Faction::NECROS, CardId::CONTACT_MORTEL);
    ActionCard* drainDeVie = new ActionCard("Drain de vie", 6, Faction::NECROS, CardId::DRAIN_DE_VIE);
    ActionCard* laPutrefaction = new ActionCard("La Putréfaction", 3, Faction::NECROS, CardId::LA_PUTREFACTION);
    ActionCard* laPutrefaction2 = new ActionCard("La Putréfaction", 3, Faction::NECROS, CardId::LA_PUTREFACTION);
    ActionCard* maledictionElfique = new ActionCard("Malédiction elfique", 3, Faction::SAUVAGE, CardId::MALEDICTION_ELFIQUE);
    ActionCard* melectionElfique2 = new ActionCard("Malédiction elfique", 3, Faction::SAUVAGE, CardId::MALEDICTION_ELFIQUE);
    ActionCard* donElfique = new ActionCard("Don elfique", 2, Faction::SAUVAGE, CardId::DON_ELFIQUE);
    ActionCard* donElfique2 = new ActionCard("Don elfique", 2, Faction::SAUVAGE, CardId::DON_ELFIQUE);
    ActionCard* donElfique3 = new ActionCard("Don elfique", 2, Faction::SAUVAGE, CardId::DON_ELFIQUE);
    ActionCard* donDeLaNature = new ActionCard("Don de la Nature", 4, Faction::SAUVAGE, CardId::DON_DE_LA_NATURE);
    ActionCard* sauvagerie = new ActionCard("Sauvagerie", 6, Faction::SAUVAGE, CardId::SAUVAGERIE);
    ActionCard* etincelle = new ActionCard("Étincelle", 1, Faction::SAUVAGE, CardId::ETINCELLE);
    ActionCard* etincelle2 = new ActionCard("Étincelle", 1, Faction::SAUVAGE, CardId::ETINCELLE);
    ActionCard* etincelle3 = new ActionCard("Étincelle", 1, Faction::SAUVAGE, CardId::ETINCELLE);
    ActionCard* formeDeLoup = new ActionCard("Forme de loup", 5, Faction::SAUVAGE, CardId::FORME_DE_LOUP);
    // a suivre ...

    // AJOUT DES CARTES DANS LA PIOCHE DU MARCHE
    piocheDuMarche.push_back(taxation1);
    piocheDuMarche.push_back(taxation2);
    piocheDuMarche.push_back(taxation3);
    piocheDuMarche.push_back(serrerLesRangs);
    piocheDuMarche.push_back(recrutement);
    piocheDuMarche.push_back(recrutement2);
    piocheDuMarche.push_back(recrutement3);
    piocheDuMarche.push_back(intimidation);
    piocheDuMarche.push_back(intimidation2);
    piocheDuMarche.push_back(benefice);
    piocheDuMarche.push_back(benefice2);
    piocheDuMarche.push_back(benefice3);
    piocheDuMarche.push_back(influence);
    piocheDuMarche.push_back(influence2);
    piocheDuMarche.push_back(influence3);
    piocheDuMarche.push_back(commandement);
    piocheDuMarche.push_back(domination);
    piocheDuMarche.push_back(ralliementDesTroupes);
    piocheDuMarche.push_back(paroleDePuissance);
    piocheDuMarche.push_back(potDeVin);
    piocheDuMarche.push_back(potDeVin2);
    piocheDuMarche.push_back(potDeVin3);
    piocheDuMarche.push_back(menaceDeMort);
    piocheDuMarche.push_back(fourberie);
    piocheDuMarche.push_back(bombeIncendiaire);
    piocheDuMarche.push_back(miseAPrix);
    piocheDuMarche.push_back(casserEtPiller);
    piocheDuMarche.push_back(energieSombre);
    piocheDuMarche.push_back(sombreRecompense);
    piocheDuMarche.push_back(contactMortel);
    piocheDuMarche.push_back(contactMortel2);
    piocheDuMarche.push_back(contactMortel3);
    piocheDuMarche.push_back(drainDeVie);
    piocheDuMarche.push_back(laPutrefaction);
    piocheDuMarche.push_back(laPutrefaction2);
    piocheDuMarche.push_back(maledictionElfique);
    piocheDuMarche.push_back(melectionElfique2);
    piocheDuMarche.push_back(donElfique);
    piocheDuMarche.push_back(donElfique2);
    piocheDuMarche.push_back(donElfique3);
    piocheDuMarche.push_back(donDeLaNature);
    piocheDuMarche.push_back(sauvagerie);
    piocheDuMarche.push_back(etincelle);
    piocheDuMarche.push_back(etincelle2);
    piocheDuMarche.push_back(etincelle3);
    piocheDuMarche.push_back(formeDeLoup);

    // Mélanger la pioche du marché
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(piocheDuMarche.begin(), piocheDuMarche.end(), g);

    // On pioche les 5 premières cartes pour les cartes visibles
    for (int i = 0; i < 5 && !piocheDuMarche.empty(); ++i) {
        cartesVisibles.push_back(piocheDuMarche.back());
        piocheDuMarche.pop_back();
    }

}

Market::~Market() {

}

Card* Market::getCard(int index) {
    return cartesVisibles[index];
}

Card* Market::buyCard(int index) {
    if (index < 0 || index >= static_cast<int>(cartesVisibles.size())) {
        return nullptr;
    }
    Card* boughtCard = cartesVisibles[index];
    cartesVisibles.erase(cartesVisibles.begin() + index);
    refill();  // Remplir à nouveau le marché
    return boughtCard;
}

Card* Market::buyGem() {
    if (gemmesDeFeu.empty()) {
        return nullptr;
    }
    Card* gem = gemmesDeFeu.back();
    gemmesDeFeu.pop_back();
    return gem;
}

// Affiche les cartes visibles sur le marché
void Market::display() const {
    std::cout << " === Marché ================ " << std::endl;
    for (size_t i = 0; i < cartesVisibles.size(); ++i) {
        std::cout << "|" << i + 1 << ". " << cartesVisibles[i]->getName() << " (Coût: " << cartesVisibles[i]->getCost() << " Or)" << std::endl;
    }
    std::cout << "|6. Gemmes de feu disponibles: " << gemmesDeFeu.size() << std::endl;
    std::cout << " ============================= " << std::endl;
}

// Remplit le marché si il y a moins de 5 cartes visibles
void Market::refill() {
    while (cartesVisibles.size() < 5 && !piocheDuMarche.empty()) {
        cartesVisibles.push_back(piocheDuMarche.back());
        piocheDuMarche.pop_back();
    }
}