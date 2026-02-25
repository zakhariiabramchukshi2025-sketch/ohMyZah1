#pragma once


#include <string>

namespace ui {
    using std::string;


    extern const string RESET;
    extern const string BOLD;
    extern const string DIM;
    extern const string ITALIC;
    extern const string UNDERLINE;
    extern const string BLINK;
    extern const string REVERSE;
    extern const string HIDDEN_TEXT;
    extern const string STRIKE;


    extern const string BLACK;
    extern const string RED;
    extern const string GREEN;
    extern const string YELLOW;
    extern const string BLUE;
    extern const string MAGENTA;
    extern const string CYAN;


    extern const string BG_BLACK;
    extern const string BG_RED;
    extern const string BG_GREEN;
    extern const string BG_YELLOW;
    extern const string BG_BLUE;
    extern const string BG_MAGENTA;
    extern const string BG_CYAN;
    extern const string BG_WHITE;
    extern const string BG_DEFAULT;

        

    void intro();
};



namespace file_system {
    using std::string;


    void appendToFile(string text, string fileName = "./logs/command_log.txt");
    void readFromFile(std::string fileName = "./logs/command_log.txt");

};

