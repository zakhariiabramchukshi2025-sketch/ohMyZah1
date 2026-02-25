
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include <vector>
                 
#include "engine/system_requirements/includes/input_config.hpp" // input reading part
#include "engine/system_requirements/includes/namespaces.hpp" // for namespaces


#include <termios.h>
#include <unistd.h>


#include <sys/utsname.h> // get devices info
#include <sys/sysctl.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::flush;
using std::vector;



string trim(const string s) {
    size_t first = s.find_first_not_of(" \t\n\r");
    
    if (first == string::npos) return "";
    
    size_t last = s.find_last_not_of(" \t\n\r");

    return s.substr(first, (last - first + 1));
}






void tabAutocomplite(string& currentInput) {
    if (trim(currentInput) != "command" && trim(currentInput) != "pyvo" && trim(currentInput) != "cd" && trim(currentInput) != "") {
        cout << "\n[No suggestions]" << flush;
        std::cout << "\a" << std::flush;
        return;
    }

    vector<string> options;
    
    if (trim(currentInput) == "command") {
        options.push_back("option_1");
        options.push_back("option_2");
        options.push_back("option_2");
        options.push_back("option_2");
        
    }
    
    else if (trim(currentInput) == "pyvo") {
        options.push_back("info");
        options.push_back("--version");
        options.push_back("--update");
        options.push_back("--upgrade");
        
    }
    
    else if (trim(currentInput) == "cd") {
        options.push_back("teka_1");
        options.push_back("teka_2");
        options.push_back("teka_3");
        options.push_back("teka_4");
        options.push_back("teka_5");
        options.push_back("teka_6");
        options.push_back("teka_7");
        options.push_back("teka_8");
    }
    
    
    if (trim(currentInput) == "") {
        options.push_back("command");
        options.push_back("pyvo");
        options.push_back("cd");
    }
    
    
    
    
    
    int selected = 0; // selected by user index
    
    while (true) {
        cout << "\n";
    
        for (int i = 0; i < options.size(); i++) {
            if (i == selected) {
                cout << " " << ui::RED << ui::DIM << ui::UNDERLINE << options[i] << ui::RESET << " ";
            } else {
                cout << " " << ui::CYAN << options[i] << ui::RESET << " ";
            }
        }

        cout << "\r\033[A" << flush; // getting back on the line of input

        int k = getRawKey(); // getting input key
        if (k == 9) {
            selected = (selected + 1) % options.size();
        }
        

        
        else if (k == 27 || k == 32539) {
            int next1 = getRawKey();
            int next2 = getRawKey();
            if (next1 == 91 || next1 == 32603 ) {
                if (next2 == 65 || next2 == 32577) selected = (selected + 2) % options.size();
                if (next2 == 66 || next2 == 32578) selected = (selected - 2) % options.size();
                if (next2 == 67 || next2 == 32579) selected = (selected + 1) % options.size();
                if (next2 == 68 || next2 == 32580) selected = (selected - 1) % options.size();
            }
        }

        else if (k == 10 || k == 13) { // ENTER
            cout << "\n\033[K" << flush; // clearing the line under main line
            cout << "\033[A" << flush;    // getting back on the main line
            
            currentInput = trim(currentInput) +  " " + options[selected];
            break;
        }
        
        
        else continue; // anything else  ///// changed
        
    }
}




void enterPressed(string currentInput) {
    system_func::visualAlert();
    
    if (currentInput == "") return;
    
    file_system::appendToFile(currentInput);
    
    if (currentInput == "q!") return;
    if (currentInput == "a!") return;
    
    if (currentInput == "-h") file_system::readFromFile();

    if (currentInput == "clear") {
        std::cout << "\033[2J\033[H" << std::flush;
        return;
    }
    
    if (currentInput == "pwd") {
        std::cout << system_func::get_path_manual(1) << std::flush;
        return;
    }
    
    
    
    cout << "ERROR: " << currentInput << " is not defined as command\n";
    
}










string readLine(string prompt) {
    string userInputBuffer = "";
    string path = system_func::get_path_manual();

    cout << prompt << flush;

    while (true) {
        int k = getRawKey();

//        system_func::systemAlert("FUCK YEAH IT WORKS", k);
        
        if (k == 27 || k == 32539) {
            int next1 = getRawKey();
            int next2 = getRawKey();
            if (next1 == 91 || next1 == 32603 ) {
                if (next2 == 65 || next2 == 32577) cout << "[UP ARROW]\n";
                if (next2 == 66 || next2 == 32578) cout << "[DOWN ARROW]\n";
                if (next2 == 67 || next2 == 32579) cout << "[RIGHT ARROW]\n";
                if (next2 == 68 || next2 == 32580) cout << "[LEFT ARROW]\n";
            }
        }
        else if (k == 9 || k == 32521) {
//            cout << "[TAB]\n";
            tabAutocomplite(userInputBuffer);
//            testOfFunc();
            cout << "\n" << prompt << userInputBuffer << flush;
        }
    
        else if (k == 10 || k == 13 || k == 32522) {
            cout << "\n";
            enterPressed(userInputBuffer);
            return userInputBuffer;
        }
        else if (k == 127 || k == 8 || k == 32639) {
            if (!userInputBuffer.empty()) {
                userInputBuffer.pop_back();
                cout << "\b \b" << flush;
            }
        }
        else if (k >= 32 && k <= 126){
            userInputBuffer += (char)k;
            cout << (char)k << flush;
//            cout << k;
        }
    }
}




int main() {
    ui::intro();

    while (true) {
        string input = readLine(ui::YELLOW + "-> " + ui::CYAN + system_func::get_path_manual() + ui::YELLOW + " > " + ui::RESET);

        if (input == "exit" || checkForSpecials(input) == 1) {
            break;
        }

        if (checkForSpecials(input) == 2) {
            cout << "admin rights is yours master" << endl;
        }

        // Логіка звичайної команди
        youEnteredFunc(input);
    }

    return 0;
}
