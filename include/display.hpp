#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <string>
#include <iostream>
#include <vector>
#include "faction.hpp"

class Display {
public:
    // Codes couleur ANSI
    static const std::string RESET;
    static const std::string BOLD;
    static const std::string UNDERLINE;
    
    // Couleurs de base
    static const std::string RED;
    static const std::string GREEN;
    static const std::string YELLOW;
    static const std::string BLUE;
    static const std::string MAGENTA;
    static const std::string CYAN;
    static const std::string WHITE;
    static const std::string BLACK;
    
    // Couleurs de fond
    static const std::string BG_RED;
    static const std::string BG_GREEN;
    static const std::string BG_YELLOW;
    static const std::string BG_BLUE;
    static const std::string BG_MAGENTA;
    static const std::string BG_CYAN;
    static const std::string BG_WHITE;
    static const std::string BG_BLACK;
    
    // Méthodes d'affichage
    static void clearScreen();
    static void printTitle();
    static void printSeparator(const std::string& title = "", const std::string& symbol = "=", int width = 50);
    static void printBox(const std::string& content, const std::string& color = "");
    static void printCenteredText(const std::string& text, int width = 50);
    
    // Couleurs par faction
    static std::string getFactionColor(Faction faction);
    static std::string getFactionSymbol(Faction faction);
    
    // ASCII Art
    static void printGameBoard();
    static void printCardFrame(const std::string& name, const std::string& cost, const std::string& faction, bool selected = false);
    static void printHealthBar(int currentHealth, int maxHealth = 50);
    static void printResourceDisplay(int gold, int combat);
};

#endif