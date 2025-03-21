#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>

using std::string;
using std::fstream;

void mainScreen();
void readLine(string filename, fstream &txtFile);
void writeLine(string filename, fstream &txtFile);

int main() {

    mainScreen();

    return 0;
}

void mainScreen() {
    fstream testFile;
    static string filename{};
    char choice{};

    if(filename == "") {
        std::cout << "Enter filename: ";
        std::cin >> filename;
        filename = "..\\files\\" + filename;
    }
    else {
        std::cout << "Do you wish to open another file? Type [y] if so or [n] otherwise. ";
        std::cin >> choice;

        switch(tolower(choice)) {
            case 'y':
                std::cout << "Enter filename: ";
                std::cin >> filename;
                filename = "..\\files\\" + filename;
                break;
            case 'n':
                break;
        }
    }

    std::cout << "Type [r] if you wish to read the file or [w] to write in it: ";
    std::cin >> choice;

    switch(tolower(choice)) {
        case 'r':
            readLine(filename, testFile);
            break;
        case 'w':
            writeLine("..\\files\\test.txt", testFile);
            break;
        default:
            std::cout << "You didn't type a valid character. Please try again" << std::endl;
            mainScreen();
            break;
    }
}

void readLine(string filename, fstream &txtFile) {
    txtFile.open(filename, std::ios_base::in);

    if(txtFile.is_open()) {
        std::cout << '\n' << "Text:\n";
        string textOutput{};
        int i{1};

        while(getline(txtFile, textOutput)) {
            std::cout << i << ": " << textOutput << '\n';
            i++;
        }
        i = 1;

        txtFile.close();
    }
    else {
        std::cout << "Error opening file. Please try again.\n";
        system("pause");
        system("cls");
        mainScreen();
    }
}

void writeLine(string filename, fstream &txtFile) {
    txtFile.open(filename, std::ios_base::app);

    if(txtFile.is_open()) {
        string keyInput{};

        std::cout << "\nInput: ";

        do {
            std::cin >> keyInput;
            txtFile << keyInput;
        } while(!keyInput.compare("\n"));

        txtFile.close();
    }
    else {
        std::cout << "Error opening file. Please try again.\n";
        system("pause");
        system("cls");
        mainScreen();
    }

    system("cls");
    mainScreen();
}
