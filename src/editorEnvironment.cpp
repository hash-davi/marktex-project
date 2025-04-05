#include "./headers/Marktex_main.h"

#include <cstdio>
#include <conio.h>

void editor(string filename, fstream &txtFile);
void showText(string filename, fstream &txtFile);
uint64_t getCharCount(string filename, fstream &txtFile);
uint64_t getLineCount(string filename, fstream &txtFile);
std::vector<string> getTextLines(string filename, fstream &txtFile);
void fillTemporaryFile(string temporaryFileName, string filename, fstream &tempTxtFile);

typedef struct {
    uint64_t x{};
    uint64_t y{};
} caretStructure;

void editor(string filename, fstream &txtFile) {
    string tempFilename{R"(..\\files\\temp\\temporary.txt)"};
    fstream temporaryFile(tempFilename);
    char keyInput{};
    if(temporaryFile.is_open()) {
        temporaryFile.close();
    }

    std::vector<string> fileText = getTextLines(filename, txtFile);
    string currentLine{fileText.back()};
    caretStructure caretPosition = {.x = currentLine.length(), .y = fileText.size()};
    string textInput{};
    int64_t lastFileTextPosition{txtFile.tellg()};

    while(true) {
        fileText = getTextLines(filename, txtFile);
        lastFileTextPosition = txtFile.tellg();

        // Debug
        std::cout << "Line: " << caretPosition.y << std::endl;
        std::cout << "Column: " << caretPosition.x << std::endl;
        std::cout << "Current line: " << currentLine << std::endl;
        std::cout << "Last line index: " << fileText.size() - 1 << std::endl;
        std::cout << "File position: " << lastFileTextPosition << std::endl;
        std::cout << "Current line length: " << currentLine.length() << std::endl;
        std::cout << "Characters: " << getCharCount(filename, txtFile) << std::endl;
        // ------------------------------------------------------------------------------

        showText(filename, txtFile);
        txtFile.open(filename, std::ios_base::app);

        // User input
        keyInput = getch();

        if(GetKeyState(VK_BACK) < 0) {
            if(fileText.empty() || (caretPosition.x == 0 && caretPosition.y == 1)) {
                caretPosition.x = 0;
                caretPosition.y = 1;
            }
            else {
                if(caretPosition.x > 0) {
                    currentLine.erase(currentLine.begin() + caretPosition.x - 1);
                    --caretPosition.x;
                    if(currentLine.empty()) {
                        fileText.at(caretPosition.y - 1) = " ";
                    }
                    else {
                        fileText.at(caretPosition.y - 1) = currentLine;
                    }
                }
                else {
                    fileText.erase(fileText.begin() + caretPosition.y - 1);
                    --caretPosition.y;
                    currentLine.clear();
                    currentLine = fileText.at(caretPosition.y - 1);
                    caretPosition.x = currentLine.length();
                }
                temporaryFile.open(tempFilename, std::ios_base::out);
                for(auto t: fileText) {
                    temporaryFile << t;
                    if(t != fileText.back()) {
                        temporaryFile << '\n';
                    }
                }
                temporaryFile.close();
                txtFile.close();
                remove(R"(..\\files\\test.txt)");
                rename(R"(..\\files\\temp\\temporary.txt)", R"(..\\files\\test.txt)");
            }
        }
        else if(keyInput == 13) {
            txtFile << '\n';
            txtFile << R"(\)";
            ++caretPosition.y;
            fileText.resize(fileText.size() + 1);
            fileText.insert(fileText.begin() + caretPosition.y - 1, R"(\)");
            currentLine.clear();
            currentLine = fileText.at(caretPosition.y - 1);
            caretPosition.x = currentLine.length();
        }
        else {
            currentLine = fileText.at(caretPosition.y - 1);
            if(currentLine.compare(R"(\)") == 0) {
                currentLine.clear();
                fileText.insert(fileText.begin() + caretPosition.y - 1, currentLine);
            }
            currentLine += keyInput;
            txtFile << keyInput;
            ++caretPosition.x;
        }
        // ------------------------------------------------------------

        fileText.clear();
        txtFile.close();
        system("cls");
    }
}

void showText(string filename, fstream &txtFile) {
    uint64_t charCount{getCharCount(filename, txtFile)};
    uint64_t lineCount{getLineCount(filename, txtFile)};
    bool hasText{};

    txtFile.open(filename, std::ios_base::in);

    string buffer;
    uint64_t i{1};

    std::cout << "File path: " << filename << "\n\n";

    std::cout << "Character count: " << charCount << '\n';
    std::cout << "Line count: " << lineCount << "\n\n"; // Debug
    while(getline(txtFile, buffer)) {
        hasText = true;
        std::cout << i++ << ": " << buffer;

        if(i < lineCount + 1) {
            std::cout << '\n';
        }

    }
    if(!hasText) {
        std::cout << i << ": ";
    }

    txtFile.close();
}

uint64_t getCharCount(string filename, fstream &txtFile) {
    txtFile.open(filename, std::ios_base::in);
    string characters;
    uint64_t charCount{};

    while(getline(txtFile, characters)) {
        charCount += characters.length();
    }

    txtFile.close();

    return charCount;
}

uint64_t getLineCount(string filename, fstream &txtFile) {
    uint64_t lineCount{getTextLines(filename, txtFile).size()};

    return lineCount;
}

std::vector<string> getTextLines(string filename, fstream &txtFile) {
    txtFile.open(filename, std::ios_base::in);
    string text{};
    std::vector<string> textLines;

    int i{};
    if(txtFile.is_open()) {
        while(getline(txtFile, text)) {
            textLines.insert(textLines.begin() + i, text);
            ++i;
        }

        txtFile.close();

        if(textLines.empty()) {
            textLines.insert(textLines.begin(), " ");
        }
        return textLines;
    }
    else {
        exit(-1);
    }
}

void fillTemporaryFile(string temporaryFileName, string filename, fstream &tempTxtFile) {
    fstream txtFile(filename);
    tempTxtFile.open(temporaryFileName, std::ios_base::out);
    txtFile.open(filename, std::ios_base::in);

    string fileText{};

    while(getline(txtFile, fileText)) {
        tempTxtFile << fileText;
    }

    tempTxtFile.close();
    txtFile.close();
}
