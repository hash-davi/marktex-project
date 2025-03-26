#include "./headers/Marktex_main.h"

#include <cstdio>
#include <conio.h>

using namespace std::literals;

void editor(string filename, fstream &txtFile);
void showText(string filename, fstream &txtFile);
unsigned long long getCharacterCount(string filename, fstream &txtFile);
int getLineCount(string filename, fstream &txtFile);
string getText(string filename, fstream &txtFile);

/*
int main(){

	return 0;
}
*/

void editor(string filename, fstream &txtFile) {
    string tempFilename{R"(..\\files\\temp\\temporary.txt)"};
    fstream temporaryFile(tempFilename);
    char keyInput{};
    if(temporaryFile.is_open()) {
        temporaryFile.close();
    }

    unsigned long long caretPosition{getCharacterCount(filename, txtFile)};
    string fileText{getText(filename, txtFile)};
    string textInput{};

    while(true) {
        fileText = getText(filename, txtFile);

        // Debug
        std::cout << "Caret: " << caretPosition << std::endl;
        std::cout << "Characters: " << getCharacterCount(filename, txtFile) << std::endl;
        // ------------------------------------------------------------------------------

        showText(filename, txtFile);
        txtFile.open(filename, std::ios_base::app);

        //if(kbhit()) { // Awaits for user input
            keyInput = getch();

            if(GetKeyState(VK_BACK) < 0) {
                if(fileText.empty() || caretPosition <= 0) {
                    caretPosition = 0;
                    //continue;
                }
                else {
                    fileText.erase(caretPosition - 1);
                    --caretPosition;
                    temporaryFile.open(tempFilename, std::ios_base::out);
                    temporaryFile << fileText;
                    temporaryFile.close();
                    txtFile.close();
                    remove(R"(..\\files\\test.txt)");
                    rename(R"(..\\files\\temp\\temporary.txt)", R"(..\\files\\test.txt)");
                    //break;
                }
            }
            else if(keyInput == 13) {
                txtFile << '\n';
                //break;
            }
            else {
                txtFile << keyInput;
                ++caretPosition;
                //break;
            }
        //}

        fileText = "";
        txtFile.close();
        system("cls");
    }
}

void showText(string filename, fstream &txtFile) {
    unsigned long long charCount{getCharacterCount(filename, txtFile)};
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

unsigned long long getCharacterCount(string filename, fstream &txtFile) {
    txtFile.open(filename, std::ios_base::in);
    string characters;
    unsigned long long charCount{};

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
