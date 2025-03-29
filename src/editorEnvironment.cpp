#include "./headers/Marktex_main.h"

#include <cstdio>
#include <conio.h>

using namespace std::literals;

void editor(string filename, fstream &txtFile);
void showText(string filename, fstream &txtFile);
unsigned long long getCharacterCount(string filename, fstream &txtFile);
int getLineCount(string filename, fstream &txtFile);
string getText(string filename, fstream &txtFile);

#define FILE_CONTENT_CLASS

#ifdef FILE_CONTENT_CLASS
class FileContent {
    private:
        fstream file{};
        string fileName{};
        fstream tempFile{};
        std::vector<string> textLines;
        uint32_t caretX = 0;
        uint32_t caretY = 0;
        uint64_t characterCount{};
    public:
        FileContent(string _filename) {
            this->file.open(_filename, std::ios_base::in);
            this->tempFile.open(R"(..\\files\\temp\\temporary.txt)", std::ios_base::in);
            if(this->file.is_open()) {
                this->file.close();
            }
            if(this->tempFile.is_open()) {
                this->tempFile.close();
            }
        }
        void openAppend() {
            this->file.open(this->getFileName(), std::ios_base::app);
        }
        void closeFile() {
            this->file.close();
        }
        fstream getFile() {
            return this->file;
        }
        void setFileName(string _filename) {
            this->fileName = _filename;
        }
        string getFileName() {
            return this->fileName;
        }
        void setTextLines() {
            string _lineText{};
            this->file.open(this->getFileName(), std::ios_base::in);

            int i{};
            while(getline(this->file, _lineText)) {
                this->textLines[i++] = _lineText;
            }

            this->file.close();
        }
        std::vector<string> getTextLines() {
            if(this->textLines.empty()) {
                this->setTextLines();
            }
            return this->textLines;
        }
        uint64_t getCharacterCount() {
            for(auto x: this->getTextLines()) {
                this->characterCount += x.length();
            }

            return this->characterCount;
        }
        void showFileContent() {
            std::cout << "File path: " << this->getFileName() << std::endl;
            std::cout << "Character count: " << this->getCharacterCount();

            uint64_t i{};
            for(i = 0; i < this->getTextLines().size(); ++i) {
                std::cout << i + 1 << this->getTextLines().at(i);

                if(i < this->getTextLines().size() - 1) {
                    std::cout << '\n';
                }
            }
        }
        uint32_t getCaretX() {
            return this->caretX;
        }
        uint32_t getCaretY() {
            return this->caretY;
        }
        void setCaretPosition() {
            string lastLine = this->getTextLines().back();
            uint32_t _caretX = this->getCaretX();
            _caretX = lastLine.length();
        }
};

void editFile(FileContent TxtFile) {
    char keyInput{};

    TxtFile.setTextLines();

    while(true) {
        TxtFile.showFileContent();

        if(keyInput == 13) {
            TxtFile.getFile() << '\n';
        }
        else if(GetKeyState(VK_BACK) & 0x8000) {
            if()
        }
    }
}


#endif // FILE_CONTENT_CLASS

#ifndef FILE_CONTENT_CLASS
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

unsigned long long getCharCount(string filename, fstream &txtFile) {
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
#endif
