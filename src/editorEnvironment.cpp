#include "./headers/Marktex_main.h"

#include <cstdio>

using namespace std::literals;

void editor(string filename, fstream &txtFile);
void showText(string filename, fstream &txtFile);
int getCharacterCount(string filename, fstream &txtFile);
int getLineCount(string filename, fstream &txtFile);
string getText(string filename, fstream &txtFile);

/*
int main(){

	return 0;
}
*/

void editor(string filename, fstream &txtFile) {
    string tempFilename{"..\\files\\temp\\temporary.txt"};
    fstream temporaryFile(tempFilename);
    if(temporaryFile.is_open()) {
        temporaryFile.close();
    }

    int caretPosition{getCharacterCount(filename, txtFile)};
    string fileText{getText(filename, txtFile)};
    string textInput{};

    while(true) {
        fileText = getText(filename, txtFile);
        showText(filename, txtFile);
        txtFile.open(filename, std::ios_base::app);

        //while(true) { // Awaits for user input
            if(GetKeyState(VK_BACK) & 0x8000) {
                if(fileText.empty() || caretPosition <= 0) {
                    caretPosition = 0;
                    //break;
                }
                else {
                    fileText.erase(caretPosition - 1);
                    --caretPosition;
                    temporaryFile.open(tempFilename, std::ios_base::out);
                    temporaryFile << fileText;
                    temporaryFile.close();
                    txtFile.close();
                    remove("..\\files\\test.txt");
                    rename("..\\files\\temp\\temporary.txt", "..\\files\\test.txt");
                    //break;
                }
            }
            else if(GetKeyState(VK_RETURN) & 0x8000) {
                txtFile << '\n';
                //break;
            }
            else {
                getline(std::cin, textInput);
                txtFile << textInput;
                //break;
            }
        // }

        fileText = "";
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

string getText(string filename, fstream &txtFile) {
    txtFile.open(filename, std::ios_base::in);
    string text{};
    string fileText{};

    while(getline(txtFile, text)) {
        fileText += text;
    }

    txtFile.close();

    return fileText;
}
