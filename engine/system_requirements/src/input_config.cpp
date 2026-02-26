#import  "../includes/input_config.hpp"

#include <iostream>

#include <termios.h>
#include <unistd.h>

#include <sys/utsname.h> // get devices info
#include <sys/sysctl.h>

using std::string;
using std::cout;

int getRawKey() {
//#ifdef _WIN32
//    return _getch();
//#else
    struct termios oldt, newt;
    unsigned char ch; // unsigned makes char diapason 2 times wider and deletes negative numbers (no need)
    tcgetattr(STDIN_FILENO, &oldt); // writing up all old settings of user's terminal
    newt = oldt; // copying
    newt.c_lflag &= ~(ICANON | ECHO); // getting rid of echo because we need to control our input
    
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // setting new options
    
    ssize_t n = read(STDIN_FILENO, &ch, 1); // getting ascii code of user's input into char
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // returning old options
    
    return (n > 0) ? (int)ch : -1; // EOF + piping problems solved
//#endif
}



int checkForSpecials(string userInput) {
    if (userInput == "q!") return 1;
    if (userInput == "a!") return 2;
    return 0;
}



void youEnteredFunc(string userInput) {
    if (userInput == "") return;
    cout << "\nYou've entered: " << userInput << "\n";
}



string trim(const string s) {
    size_t first = s.find_first_not_of(" \t\n\r");
    
    if (first == string::npos) return "";
    
    size_t last = s.find_last_not_of(" \t\n\r");

    return s.substr(first, (last - first + 1));
}

