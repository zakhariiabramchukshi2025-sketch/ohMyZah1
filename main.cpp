
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



void appendToFile(string text, string fileName = "./logs/command_log.txt") {
    std::ofstream outFile;
    
    outFile.open(fileName, std::ios::app);

    if (outFile.is_open()) {
        outFile << text << std::endl;
        outFile.close();
    } else {
        std::cerr << "File opening error!" << std::endl;
    }
}


void readFromFile(std::string fileName = "./logs/command_log.txt") {
    std::ifstream inFile(fileName);

        if (inFile.is_open()) {
            std::string line;
            while (std::getline(inFile, line)) cout << line  << "\n" << flush;
            inFile.close();
        }
        else cout << "\n" << "file is not found" << flush;
}

    
        
        
    
        
    









void visualAlert() {
    // Включаємо інверсію всього екрану на мить
    cout << "\033[?5h" << flush;
    usleep(100000); // пауза 0.1 сек (потрібен #include <unistd.h>)
    // Вимикаємо інверсію
    cout << "\033[?5l" << flush;
}

void systemAlert(string title, string message) {
    string cmd = "osascript -e 'display alert \"" + title + "\" message \"" + message + "\"' &";
    system(cmd.c_str());
}


void systemAlert(string title, int message) {
    string cmd = "osascript -e 'display alert \"" + title + "\" message \"" + std::to_string(message) + "\"' &";
    system(cmd.c_str());
}





string trim(const string s) {
    size_t first = s.find_first_not_of(" \t\n\r");
    
    if (first == string::npos) return "";
    
    size_t last = s.find_last_not_of(" \t\n\r");

    return s.substr(first, (last - first + 1));
}







string get_path_manual(bool full = false) {
    string path = "";
    
    #ifdef _WIN32
        char buffer[MAX_PATH];
        if (GetCurrentDirectory(MAX_PATH, buffer)) {
            path = std::string(buffer);
        } else {
            return "error";
        }
        char sep = '\\';
    #else
        char temp[1024];
        if (getcwd(temp, sizeof(temp)) != nullptr) {
            path = std::string(temp);
        } else {
            return "error";
        }
        char sep = '/'; // Роздільник для Unix (Mac)
    #endif

    if (!full) {
        size_t lastSlash = path.find_last_of(sep);
        
        // Перевіряємо, чи це не корінь (наприклад, "/" на Mac або "C:\" на Win)
        if (lastSlash != std::string::npos && lastSlash != path.length() - 1) {
            return path.substr(lastSlash + 1);
        }
    }

    return path;
}








void testOfFunc() {
    cout << "YO MAN THIS IS CRAZY!!!";
}

int checkForSpecials(string userInput) {
    if (userInput == "q!") return 1;
    if (userInput == "a!") return 2;
    return 0;
}

void youEnteredFunc(string userInput) {
    if (userInput == "") return;
    cout << "\nВи ввели: " << userInput << "\n";
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
        
        
//        else if (k == 27) { // ESC - якщо юзер передумав вибирати
//            cout << "\n\033[K" << flush; // clearing the line under main line
//            cout << "\033[A" << flush;    // getting back on the main line
//            cout << ui::BLUE << "FUUUUUUUUUUUUUUUUUUH"  << ui::RESET << flush;    // getting back on the main line
//            break;
//        }
        
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
    visualAlert();
    
    if (currentInput == "") return;
    
    appendToFile(currentInput);
    
    if (currentInput == "q!") return;
    if (currentInput == "a!") return;
    
    if (currentInput == "-h") readFromFile();

    if (currentInput == "clear") {
        std::cout << "\033[2J\033[H" << std::flush;
        return;
    }
    
    if (currentInput == "pwd") {
        std::cout << get_path_manual(1) << std::flush;
        return;
    }
    
    
    
    cout << "ERROR: " << currentInput << " is not defined as command\n";
    
}










string readLine(string prompt) {
    string userInputBuffer = "";
    string path = get_path_manual();

    cout << prompt << flush;

    while (true) {
        int k = getRawKey();

//        systemAlert("FUCK YEAH IT WORKS", k);
        
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
        string input = readLine(ui::YELLOW + "-> " + ui::CYAN + get_path_manual() + ui::YELLOW + " > " + ui::RESET);

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















//std::system("afplay /System/Library/Sounds/Bottle.aiff &");
//system("afplay /System/Library/Sounds/Basso.aiff &")Глибокий глухий звук (помилка)
//system("afplay /System/Library/Sounds/Blow.aiff &")Звук видування повітря
//system("afplay /System/Library/Sounds/Bottle.aiff &")Дзвінкий звук пляшки
//system("afplay /System/Library/Sounds/Frog.aiff &")Квакання (смішно для помилок)
//system("afplay /System/Library/Sounds/Funk.aiff &")Стандартний фанк-клік
//system("afplay /System/Library/Sounds/Hero.aiff &")Тріумфальний звук (успіх команди)
//system("afplay /System/Library/Sounds/Morse.aiff &")Азбука Морзе













//int main() {
//    ui::intro();
//
//
//    string path = get_path_manual();
//
//
//    string userInputBuffer = "";
//
//
//    while (true) {
//        int k = getRawKey();
//
//
//
//        if (k == 27 || k == 32539) { // Початок ESC-послідовності
//            int next1 = getRawKey();
//            int next2 = getRawKey();
//            if (next1 == 91 || next1 == 32603 ) {
//                if (next2 == 65 || next2 == 32577) cout << "[UP ARROW]\n";
//                if (next2 == 66 || next2 == 32578) cout << "[DOWN ARROW]\n";
//                if (next2 == 67 || next2 == 32579) cout << "[RIGHT ARROW]\n";
//                if (next2 == 68 || next2 == 32580) cout << "[LEFT ARROW]\n";
//            }
//        }
//        else if (k == 9 || k == 32521) {
//            cout << "[TAB]\n";
//            cout << "\t1) HELL WORLD " << path << "\n";
//            cout << "\t2) HELL WORLD2\n";
//            cout << "\t3) HELL WORLD3\n";
//            cout << "\t4) HELL WORLD4\n";
//            testOfFunc();
//            cout << "\n";
//        }
//
//        else if (k == 10 || k == 13 || k == 32522) {
//            cout << "[Enter]\n";
//            youEnteredFunc(userInputBuffer);
//            if (checkForSpecials(userInputBuffer) == 1) break;
//            if (checkForSpecials(userInputBuffer) == 2) {
//                cout << "admin rights is yours master\n";
//            }
//            cout << ">>> ";
//
//
//            userInputBuffer = "";
//
//        }
//
//        else if (k == 127 || k == 8 || k == 32639) {
//            //            cout << "[Backspace]";
//            if (!userInputBuffer.empty()) {
//                userInputBuffer.pop_back();
//            }
//
//            cout << "\b \b" << flush;
//        }
//
//        else if (k >= 32 && k <= 126){
////            cout << "Key pressed: " << (char)k << " (code: " << k << ")";
//            userInputBuffer += (char)k;
//            cout << (char)k << flush;
////            cout << k;
//
//        }
//    }
//
//    return 0;
//}
