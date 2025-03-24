#include "./headers/Marktex_main.h"

void editor(string filename, fstream &txtFile);
void showText(string filename, fstream &txtFile);
int getCharacterCount(string filename, fstream &txtFile);
int getLineCount(string filename, fstream &txtFile);

/*
int main(){

	return 0;
}
*/

void editor(string filename, fstream &txtFile) {
    string textInput{};

    while(true) {
        showText(filename, txtFile);
        txtFile.open(filename, std::ios_base::app);

        getline(std::cin, textInput);
        txtFile << textInput;

        txtFile.close();
        system("cls");
    }
}

void showText(string filename, fstream &txtFile) {
    int charCount{getCharacterCount(filename, txtFile)};
    int lineCount{getLineCount(filename, txtFile)};

    txtFile.open(filename, std::ios_base::in);

    string buffer;
    int i{1};

    std::cout << "File path: " << filename << "\n\n";

    std::cout << "Character count: " << charCount << '\n';
    while(getline(txtFile, buffer)) {
        std::cout << i++ << ": " << buffer;

        if(i < lineCount) {
            std::cout << '\n';
        }

    }

    txtFile.close();
}

int getCharacterCount(string filename, fstream &txtFile) {
    txtFile.open(filename, std::ios_base::in);
    string characters;
    int charCount{};

    while(getline(txtFile, characters)) {
        charCount += characters.length();
    }

    txtFile.close();

    return charCount;
}

int getLineCount(string filename, fstream &txtFile) {
    txtFile.open(filename, std::ios_base::in);
    int i{1};
    int lineCounter{};
    string lineText;

    while(getline(txtFile, lineText)) {
        lineCounter += i++;
    }

    txtFile.close();

    return lineCounter;
}
