#include "./headers/Marktex_main.h"

#include "editorEnvironment.cpp"

void mainScreen();
/*
void readLine(string filename, fstream &txtFile);
void writeLine(string filename, fstream &txtFile);
int getTextLength(string filename, fstream &txtFile);
std::vector<string> getTextLines(string filename, fstream &txtFile);
string getText(string filename, fstream &txtFile);
*/
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
        std::cin >> filename;
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
                filePath = "..\\files\\" + filename;
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


/*
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

        mainScreen();
    }
    else {
        std::cout << "Error opening file. Please try again.\n";
        system("pause");
        system("cls");
        mainScreen();
    }
}

void writeLine(string filename, fstream &txtFile) {
    int keyCounter{getTextLength(filename, txtFile) + 1};
    std::vector<string> textLines = getTextLines(filename, txtFile);

    txtFile.open(filename, std::ios_base::app);

    if(txtFile.is_open()) {
        string textInput{};

        std::cout << "\nText: ";

        for(int i = 0; i < 50; i++) {
            std::cout << textLines[i] << '\n';
        }


        getline(std::cin, textInput);
        fileText += textInput;
        keyCounter += textInput.length();
        txtFile << textInput;


        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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

int getTextLength(string filename, fstream &txtFile) {
    return getText(filename, txtFile).length();
}

std::vector<string> getTextLines(string filename, fstream &txtFile) {
    txtFile.open(filename, std::ios_base::in);
    string fileText{};
    std::vector<string> wholeText;

    int i{};

    while(getline(txtFile, fileText)) {
        wholeText[i] += fileText;
        ++i;
    }

    txtFile.close();

    return wholeText;
}

string getText(string filename, fstream &txtFile) {
    txtFile.open(filename, std::ios_base::in);
    string fileText{};
    string wholeText{};

    while(getline(txtFile, fileText)) {
        wholeText += fileText;
    }

    txtFile.close();

    return wholeText;
}
*/

void leaveProgram() {
    std::cout << "Thank you for using our app!" << std::endl;
    exit(0);
}
