#include "./headers/Marktex_main.h"

#include <cstdio>
#include <conio.h>

using namespace std::literals;

void editor(string filename, fstream &txtFile);
void showText(string filename, fstream &txtFile);
uint64_t getCharCount(string filename, fstream &txtFile);
uint64_t getLineCount(string filename, fstream &txtFile);
std::vector<string> getTextLines(string filename, fstream &txtFile);

typedef struct {
    uint64_t x{};
    uint64_t y{};
} caretStructure;

#ifdef FILE_CONTENT_CLASS
class FileContent {
    private:
        fstream *file;
        string fileName{};
        fstream *tempFile;
        std::vector<string> textLines;
        uint32_t caretX = 0;
        uint32_t caretY = 0;
        uint64_t characterCount{};
    public:
        FileContent(string _filename) {
            this->file->open(_filename, std::ios_base::in);
            this->tempFile->open(R"(..\\files\\temp\\temporary.txt)", std::ios_base::in);
            if(this->file->is_open()) {
                this->file->close();
            }
            if(this->tempFile->is_open()) {
                this->tempFile->close();
            }
        }
        void openTempFileAppend() {
            this->tempFile->open(R"(..\\files\\temp\\temporary.txt)", std::ios_base::app);
        }
        void closeTempFile() {
            this->tempFile->close();
        }
        fstream *getTempFile() {
            return this->tempFile;
        }
        void setFileName(string _filename) {
            this->fileName = _filename;
        }
        string getFileName() {
            return this->fileName;
        }
        void setTextLines() {
            string _lineText{};
            this->file->open(this->getFileName(), std::ios_base::in);

            int i{};
            while(getline(*this->file, _lineText)) {
                this->textLines[i++] = _lineText;
            }

            this->file->close();
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
            TxtFile.getTempFile() << '\n';
        }
        else if(GetKeyState(VK_BACK) & 0x8000) {
            if(TxtFile.getCaretX() != 0) {
                break;
            }
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

    std::vector<string> fileText = getTextLines(filename, txtFile);
    string currentLine{fileText.back()};
    caretStructure caretPosition = {.x = currentLine.length(), .y = fileText.size()};
    string textInput{};

    while(true) {
        fileText = getTextLines(filename, txtFile);

        // Debug
        std::cout << "Line: " << caretPosition.y << std::endl;
        std::cout << "Column: " << caretPosition.x << std::endl;
        std::cout << "Current line: " << currentLine << std::endl;
        std::cout << "Characters: " << getCharCount(filename, txtFile) << std::endl;
        // ------------------------------------------------------------------------------

        showText(filename, txtFile);
        txtFile.open(filename, std::ios_base::app);

        // User input
        keyInput = getch();

        if(GetKeyState(VK_BACK) < 0) {
            if(fileText.empty()) {
                caretPosition.x = 0;
                caretPosition.y = 0;
            }
            else {
                if(caretPosition.x > 0) {
                    currentLine.erase(currentLine.begin() + caretPosition.x - 1);
                    --caretPosition.x;
                    fileText.at(caretPosition.y - 1) = currentLine;
                }
                else {
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
            txtFile << ' ';
            ++caretPosition.y;
            caretPosition.x = 0;
            fileText.resize(fileText.size() + 1);
            currentLine.clear();
            currentLine = fileText.at(caretPosition.y - 1);
        }
        else {
            currentLine = fileText.at(caretPosition.y - 1);
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

    txtFile.open(filename, std::ios_base::in);

    string buffer;
    uint64_t i{1};

    std::cout << "File path: " << filename << "\n\n";

    std::cout << "Character count: " << charCount << '\n';
    std::cout << "Line count: " << lineCount << "\n\n"; // Debug
    while(getline(txtFile, buffer)) {
        std::cout << i++ << ": " << buffer;

        if(i < lineCount + 1) {
            std::cout << '\n';
        }

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

        return textLines;
    }
    else {
        exit(-1);
    }
}
#endif
