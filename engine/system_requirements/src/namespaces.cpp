#include "../includes/namespaces.hpp"



#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include <vector>

#include <termios.h>
#include <unistd.h>

#include <sys/utsname.h> // get devices info
#include <sys/sysctl.h>






namespace ui {
    using std::string;
    using std::cout;
    
     extern const string RESET       = "\033[0m";
     extern const string BOLD        = "\033[1m";
     extern const string DIM         = "\033[2m";
     extern const string ITALIC      = "\033[3m";
     extern const string UNDERLINE   = "\033[4m";
     extern const string BLINK       = "\033[5m";
     extern const string REVERSE     = "\033[7m";
     extern const string HIDDEN_TEXT = "\033[8m";
     extern const string STRIKE      = "\033[9m";


     extern const string BLACK    = "\033[30m";
     extern const string RED     = "\033[31m";
     extern const string GREEN   = "\033[32m";
     extern const string YELLOW  = "\033[33m";
     extern const string BLUE    = "\033[34m";
     extern const string MAGENTA = "\033[35m";
     extern const string CYAN    = "\033[36m";


     extern const string BG_BLACK    = "\033[40m";
     extern const string BG_RED      = "\033[41m";
     extern const string BG_GREEN    = "\033[42m";
     extern const string BG_YELLOW   = "\033[43m";
     extern const string BG_BLUE     = "\033[44m";
     extern const string BG_MAGENTA  = "\033[45m";
     extern const string BG_CYAN     = "\033[46m";
     extern const string BG_WHITE    = "\033[47m";
     extern const string BG_DEFAULT  = "\033[49m";


    void  intro() {
        cout << BOLD;
        cout << RED << "   ____  __  " << YELLOW << "        " << GREEN << "          " << CYAN << "      " << BLUE << "         __\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        cout << RED << "  / __ \\/ /  " << YELLOW << "   _ _  _" << GREEN << "_ __   " << CYAN << " ____ " << MAGENTA << " ____  " << BLUE << "   / /_\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        cout << RED << " / /_/ / _ \\ " << YELLOW << "  / ʼ |" << GREEN << "/ // /" << CYAN << "   /_  / " << MAGENTA << "/  __`| " << BLUE << " / __ \\\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        cout << RED << " \\____/_//_/ " << YELLOW << " /_/_/" << GREEN << "/_/_//   " << CYAN << "  / /_ " << MAGENTA << "/ /_/ |" << BLUE <<" / / / /\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        
        cout << RED << "             " << YELLOW << "      " << GREEN << ",__//     " << CYAN << "/___/ " << MAGENTA << "\\____ \\" << BLUE << "/_/ /_/" << RESET;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        
        cout << "\n\n\n\n";
    
        cout << BOLD << ITALIC <<  "Welcome to Oh my ZAH!" << RESET;
        
//        cout << "\n\n";
        
//        cout << "[Press enter to start the system]";
        
        cout << "\n\n";
    }
};





namespace file_system {
    using std::string;
    using std::flush;
    using std::cout;

    void appendToFile(string text, string fileName) {
        std::ofstream outFile;
        
        outFile.open(fileName, std::ios::app);
        
        if (outFile.is_open()) {
            outFile << text << std::endl;
            outFile.close();
        } else {
            std::cerr << "File opening error!" << std::endl;
        }
    }


    void readFromFile(std::string fileName) {
        std::ifstream inFile(fileName);
        
        if (inFile.is_open()) {
            std::string line;
            while (std::getline(inFile, line)) cout << line  << "\n" << flush;
            inFile.close();
        }
        else cout << "\n" << "file is not found" << flush;
    }

};





namespace system {
    using std::cout;
    using std::flush;
    using std::string;

        
    void visualAlert() {
        cout << "\033[?5h" << flush;
        usleep(100000);
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


    string get_path_manual(bool full) {
        string path = "";

        char temp[1024];
        if (getcwd(temp, sizeof(temp)) != nullptr) {
            path = std::string(temp);
        } else {
            return "error";
        }
        char sep = '/'; // for UNIX (mac is UNIX based system)

        if (!full) {
            size_t lastSlash = path.find_last_of(sep);
            
            if (lastSlash != std::string::npos && lastSlash != path.length() - 1) {
                return path.substr(lastSlash + 1);
            }
        }
        
        return path;
    }
    
};
