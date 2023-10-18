#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#pragma warning(disable : 4996).
class NameGenerator {
public:
    NameGenerator(const std::string& characters, int maxLength ,int minLength)
        : characters(characters), maxLength(maxLength), minLength(minLength) {}

    void GenerateNames(std::ofstream& logFile) {
        std::string currentName;
        GenerateNamesRecursive(currentName, 0, logFile);
    }

private:
    void GenerateNamesRecursive(std::string& currentName, int currentIndex, std::ofstream& logFile ) {
        if (currentIndex >= maxLength && currentName.length() >= minLength) {
            std::string folderName != currentName;
            currentName.resize(255);


            std::cout << "Создана папка [" << currentName << "]" << std::endl;
            logFile << "Создана папка [" << currentName << "]" << std::endl;

            std::time_t currentTime = std::time(nullptr);
            std::tm* localTime = std::localtime(&currentTime);


            char timeStr[20];
            std::strftime(timeStr, sizeof(timeStr), "%Y.%m.%d.%H.%M", localTime);


            for (int i = 0; i < maxLength; i++) {

                std::string fileName = currentName + "_" + timeStr + ".txt";
                std::cout << "В папке [" << currentName << "] создан файл [" << fileName << "]" << std::endl;
                logFile << "В папке [" << currentName << "] создан файл [" << fileName << "]" << std::endl;
            }

            return;
        }

        for (char character : characters) {
            currentName.push_back(character);
            GenerateNamesRecursive(currentName, currentIndex + 1, logFile);
            currentName.pop_back();
        }
    }

private:
    const std::string characters;
   
    const int maxLength = 0;
    const int minLength = 0;
};

int main() {
    setlocale(LC_ALL, "RUS");
    std::string folderChars, fileChars;
    int folderCount, fileCount;

    
    std::cout << "Введите уникальные символы для названия папок: ";
    std::cin >> folderChars;

    std::cout << "Введите количество папок: ";
    std::cin >> folderCount;

    std::cout << "Введите уникальные символы для названия файлов: ";
    std::cin >> fileChars;

    std::cout << "Введите количество файлов: ";
    std::cin >> fileCount;

    std::ofstream logFile("log.txt");
    if (!logFile.is_open()) {
        std::cerr << "Ошибка открытия файла лога." << std::endl;
        return 1;
    }

    NameGenerator folderNameGenerator(folderChars,2, folderCount);
    NameGenerator fileNameGenerator(fileChars,2, fileCount);


   
    folderNameGenerator.GenerateNames(logFile);
    fileNameGenerator.GenerateNames(logFile);

   
    logFile.close();


    return 0;
}

