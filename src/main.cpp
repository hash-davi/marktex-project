#include "./headers/Marktex_main.h"

#include "editorEnvironment.cpp"

void mainScreen();
void leaveProgram();

constexpr int maxBuffer = 100;

int main() {

    mainScreen();

    return 0;
}

void mainScreen() {
    fstream existingFile;
    string filename{};
    static string filePath{};
    char choice{};


    if(filename.empty()) {
        std::cout << "Enter filename: ";
        getline(std::cin, filename);
        filePath = R"(..\\files\\)" + filename;

        existingFile.open(filePath, std::ios_base::in);
        if(existingFile.is_open()) {
            existingFile.close();
        }
        else {
            std::cout << "There is no such file. Please try again.\n";
            filename.clear();
            mainScreen();
        }
    }
    else {
        std::cout << "Do you wish to open another file? Type [y] if so or [n] otherwise. ";
        std::cin >> choice;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch(tolower(choice)) {
            case 'y':
                std::cout << "Enter filename: ";
                std::cin >> filename;
                filePath = R"(..\\files\\)" + filename;
                break;
            case 'n':
                break;
            default:
                std::cout << "You typed an invalid character. Please try again." << std::endl;
                system("pause");
                system("cls");
                mainScreen();
        }
    }


    std::cout << "Type [y] if you wish to edit the file or [n] if you want to leave: ";
    std::cin >> choice;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch(tolower(choice)) {
        case 'y':
            system("cls");
            editor(filePath, existingFile);
            break;
        case 'n':
            leaveProgram();
            break;
        default:
            std::cout << "You didn't type a valid character. Please try again" << std::endl;
            mainScreen();
            break;
    }
}

void leaveProgram() {
    std::cout << "Thank you for using our app!" << std::endl;
    exit(0);
}
