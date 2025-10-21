# RAPPORT DE PROJET - HERO REALMS
**4e année école d'ingénieurs -  Année 2025**  
**Matière : C++ - Interaction et programmation 2**

---

## 1. Contexte

Dans le cadre de la matière "C++ (1)", dans l'U.E. "Interaction et programmation 2", nous devons coder l'entièreté du jeu de cartes "Hero Realms". L'objectif de ce projet est de mettre en œuvre les connaissances en C++ qu'on a acquises durant la matière.

Hero Realms est un jeu de deck-building pour 2 à 4 joueurs où chaque joueur commence avec un deck de base identique et achète progressivement de nouvelles cartes depuis un marché central pour améliorer son deck. Le but est de réduire les points de vie de l'adversaire de 50 à 0.

Le projet doit respecter les principes de la programmation orientée objet en C++ : héritage, polymorphisme, encapsulation, et utiliser une architecture modulaire avec compilation séparée via Makefile.

---

## 2. Choix de conception

### 2.1 Architecture générale
Nous avons opté pour une architecture orientée objet classique avec séparation claire des responsabilités :

- **Classe Game** : Contrôleur principal gérant le déroulement de la partie, les tours de jeu et les interactions entre joueurs
- **Classe Player** : Représente un joueur avec sa main, ses decks (pioche/défausse), ses points de vie et ses ressources
- **Hiérarchie des cartes** : Classe abstraite `Card` avec trois spécialisations (`ActionCard`, `ItemCard`, `ChampionCard`)
- **Classe Market** : Gère le marché central avec les cartes disponibles à l'achat
- **Classe Deck** : Structure de données pour manipuler les piles de cartes
- **Classe Display** : Interface utilisateur avec coloration ANSI et affichage amélioré

### 2.2 Polymorphisme et héritage
```cpp
// Hiérarchie des cartes utilisant le polymorphisme
class Card {
public:
    virtual void play(Player* owner, Game* game) = 0;
    virtual void sacrifice(Player* owner, Game* game, bool fromEffects) = 0;
    // ...
};

class ActionCard : public Card { /* ... */ };
class ItemCard : public Card { /* ... */ };
class ChampionCard : public Card { /* ... */ };
```

### 2.3 Gestion des champions
Les champions représentent un défi particulier car ils :
- Restent en jeu entre les tours (contrairement aux autres cartes)
- Ont un système de défense persistante avec dégâts cumulés
- Peuvent être activés une fois par tour
- Possèdent des capacités spéciales (Garde, capacités alliées)

### 2.4 Factory Pattern pour les cartes
Chaque type de champion utilise des méthodes de création statiques pour centraliser leur configuration :
```cpp
static ChampionCard* createDarianMageDeGuerre();
static ChampionCard* createArkusDragonImperial();
```

---

## 3. Diagramme des classes

```
                    ┌─────────────┐
                    │    Game     │
                    │ (Contrôleur)│
                    └─────┬───────┘
                          │
        ┌─────────────────┼─────────────────┐
        │                 │                 │
   ┌────▼───┐        ┌────▼───┐        ┌───▼────┐
   │Player 1│        │Player 2│        │ Market │
   └────┬───┘        └────┬───┘        └───┬────┘
        │                 │                │
        │           ┌─────▼─────┐          │
        │           │   Deck    │◄─────────┘
        │           │(Pioche/   │
        │           │Défausse)  │
        │           └───────────┘
        │
    ┌───▼────────────────────────┐
    │         Card               │
    │      (abstraite)           │
    └───┬────────────────────────┘
        │
   ┌────┼────┬──────────────┬─────────────┐
   │         │              │             │
┌──▼──┐ ┌───▼───┐     ┌────▼────┐   ┌────▼────┐
│Item │ │Action │     │Champion │   │Display  │
│Card │ │Card   │     │Card     │   │(Utilitaire)│
└─────┘ └───────┘     └─────────┘   └─────────┘
```

**Rôles des classes principales :**
- **Game** : Orchestrateur des parties, gestion des tours, validation des actions
- **Player** : Encapsule l'état d'un joueur (vie, main, decks, champions en jeu)
- **Card** : Interface commune pour toutes les cartes avec méthodes virtuelles pures
- **Market** : Gestion du marché central et de la pioche commune
- **Deck** : Structure de données pour les piles de cartes avec mélange
- **Display** : Amélioration de l'interface utilisateur (couleurs, ASCII art)

---

## 4. Répartition du travail

**Note :** Ce projet a été réalisé en monôme.

### Phase 1 - Architecture de base
- Conception de la hiérarchie des classes
- Implémentation des classes `Card`, `Player`, `Game`
- Système de deck et pioche de base
- Makefile et structure du projet

### Phase 2 - Mécaniques de jeu
- Implémentation complète des cartes d'action et d'objet
- Système d'achat et de marché
- Mécaniques d'attaque et de défense
- Gestion des factions et capacités alliées

### Phase 3 - Système des champions
- Classe `ChampionCard` avec défense persistante
- Système d'activation et de désactivation
- Capacités spéciales (Garde, capacités uniques)
- Gestion des champions en jeu entre les tours

### Phase 4 - Améliorations et extensions
- Interface utilisateur avec couleurs ANSI
- Système de validation d'entrée sécurisée
- Système de sacrifice avancé
- Debug et tests approfondis

---

## 5. Explication du Makefile

### 5.1 Structure du Makefile
```makefile
# Compilateur et options
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -Iinclude

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
TARGET = hero_realms

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
```

### 5.2 Fonctionnalités
- **Compilation séparée** : Chaque fichier `.cpp` est compilé indépendamment en objet `.o`
- **Gestion automatique des sources** : `$(wildcard $(SRC_DIR)/*.cpp)` détecte tous les fichiers sources
- **Transformation des chemins** : `$(patsubst)` convertit les `.cpp` en `.o` dans le dossier build
- **Flags de compilation** : `-Wall -Wextra` pour les warnings, `-Werror` traite les warnings comme des erreurs
- **Inclusion des headers** : `-Iinclude` spécifie le répertoire des headers

### 5.3 Règles et dépendances
```makefile
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
```

### 5.4 Commandes disponibles
```bash
make          # Compilation complète (équivaut à make all)
make run      # Compilation + exécution du programme
make clean    # Nettoyage complet (objets + exécutable)
```

### 5.5 Dépendances
Aucune dépendance externe requise. Le projet utilise uniquement :
- Bibliothèque standard C++ (iostream, vector, string, algorithm)
- Headers système pour les couleurs ANSI (compatible Linux/Unix)

---

## 6. Fonctionnalités supplémentaires

### 6.1 Interface graphique améliorée ⭐⭐
- **Couleurs ANSI** : Chaque faction a sa couleur distinctive
- **ASCII Art** : Logo du jeu, barres de santé visuelles
- **Mise en page** : Tableaux encadrés, séparateurs graphiques
- **Feedback visuel** : Icônes pour les actions, états des cartes

### 6.2 Système de validation d'entrée ⭐
- **Gestion des erreurs** : Protection contre les entrées non-numériques
- **Messages d'erreur clairs** : Indication des plages valides
- **Récupération automatique** : Redemande de saisie en cas d'erreur

### 6.3 Système de champions avancé ⭐⭐⭐
- **Défense persistante** : Les dégâts restent entre les tours
- **Capacités spéciales** : Garde prioritaire, capacités uniques
- **Gestion d'état** : Activation/désactivation par tour
- **Debug avancé** : Traces détaillées pour le débogage

### 6.4 Système de sacrifice complet ⭐⭐
- **Sources multiples** : Main, cartes en jeu, champions
- **Validation** : Vérification des capacités de sacrifice
- **Interface unifiée** : Menu contextuel selon les options disponibles

---

## 7. Difficultés rencontrées

### 7.1 Gestion mémoire et pointeurs
**Problème :** Gestion complexe des pointeurs de cartes entre marché, mains et zones de jeu.

**Solution :** Adoption d'une politique claire : 
- Le marché possède les cartes initialement
- Transfer de propriété lors des achats (pas de copie)
- Destruction centralisée dans les destructeurs de `Player` et `Market`

### 7.2 Polymorphisme des cartes
**Problème :** Différenciation entre types de cartes (champions vs autres) pour le placement en jeu.

**Solution :** Utilisation de `dynamic_cast` pour identifier le type réel :
```cpp
ChampionCard* champion = dynamic_cast<ChampionCard*>(card);
if (champion) {
    championsEnJeu.push_back(champion);
} else {
    cartesEnJeu.push_back(card);
}
```

### 7.3 Persistance des champions
**Problème :** Les champions doivent persister entre les tours avec leur état (défense, activation).

**Solution :** 
- Séparation des vecteurs `cartesEnJeu` (temporaire) et `championsEnJeu` (persistent)
- Système double de défense (`defense` max et `defenseActuelle`)
- Réinitialisation d'état en début de tour

### 7.4 Debug des états d'activation
**Problème :** Inconsistances entre l'affichage debug et le comportement réel des champions.

**Investigation :** Découverte de multiples instances du même champion (marché vs pioche initiale).

**Résolution :** Suppression temporaire des champions de la pioche initiale pour isoler le problème.

### 7.5 Validation d'entrée utilisateur
**Problème :** Crash du programme lors de saisies non-numériques (lettres, caractères spéciaux).

**Solution :** Implémentation d'une fonction de validation robuste avec :
- Vérification du type d'entrée
- Nettoyage du buffer en cas d'erreur
- Messages d'erreur informatifs
- Redemande automatique

### 7.6 Complexité des effets de cartes
**Problème :** Certains effets de cartes nécessitent des interactions complexes entre plusieurs objets.

**Solution en cours :** Architecture modulaire permettant aux cartes d'interagir avec le contexte de jeu complet (Player, Game, Market).

---