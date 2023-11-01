#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

class NameGenerator {
public:
    NameGenerator(const std::string& characters, int maxLength, int minLength)
        : characters(characters), maxLength(maxLength), minLength(minLength) {}

    void GenerateNames(std::ofstream& logFile) {
        std::string currentName;
        int currentIndex = 0;

        while (currentIndex < maxLength) {
            if (currentName.length() >= minLength) {
                std::string folderName = currentName;
                if (folderName.length() > maxLength) {
                    folderName = folderName.substr(0, maxLength);
                }

                std::cout << "Создана папка [" << folderName << "]" << std::endl;
                logFile << "Создана папка [" << folderName << "]" << std::endl;

                std::time_t currentTime = std::time(nullptr);
                std::tm* localTime = std::localtime(&currentTime);

                char timeStr[20];
                std::strftime(timeStr, sizeof(timeStr), "%Y.%m.%d.%H.%M", localTime);

                for (int i = 0; i < maxLength; i++) {
                    std::string fileName = folderName + "_" + timeStr + ".txt";
                    std::cout << "В папке [" << folderName << "] создан файл [" << fileName << "]" << std::endl;
                    logFile << "В папке [" << folderName << "] создан файл [" << fileName << "]" << std::endl;
                }
            }

            currentName.push_back(characters[currentIndex]);
            currentIndex++;

            if (currentIndex == characters.length()) {
                if (currentName.length() == 0) {
                    break;
                }

                char lastChar = currentName.back();
                currentName.pop_back();

                while (!currentName.empty() && currentName.back() == lastChar) {
                    lastChar = currentName.back();
                    currentName.pop_back();
                }
            }
        }
    }

private:
    const std::string characters;
    const int maxLength;
    const int minLength;
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

    NameGenerator folderNameGenerator(folderChars, 2, folderCount);
    NameGenerator fileNameGenerator(fileChars, 2, fileCount);

    folderNameGenerator.GenerateNames(logFile);
    fileNameGenerator.GenerateNames(logFile);

    logFile.close();

    return 0;
}

