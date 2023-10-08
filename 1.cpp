#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996).
class NameGenerator {
public:
    NameGenerator(const std::string& characters, int maxLength)
        : characters(characters), maxLength(maxLength) {}

    void GenerateNames(std::ofstream& logFile) {
        std::string currentName;
        GenerateNamesRecursive(currentName, 0, logFile);
    }

private:
    void GenerateNamesRecursive(std::string& currentName, int currentIndex, std::ofstream& logFile) {
        if (currentIndex >= maxLength) {
            // Ограничиваем длину имени до 255 символов
            currentName.resize(255);

            // Создание папки
            std::cout << "Создана папка [" << currentName << "]" << std::endl;
            logFile << "Создана папка [" << currentName << "]" << std::endl;

            // Получение текущего времени
            std::time_t currentTime = std::time(nullptr);
            std::tm* localTime = std::localtime(&currentTime);

            // Форматирование времени для добавления к именам файлов
            char timeStr[20];
            std::strftime(timeStr, sizeof(timeStr), "%Y%m%d%H%M%S", localTime);

            // Создание файла в папке с добавлением времени
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
    const int maxLength;
};

int main() {
    setlocale(LC_ALL, "RUS");
    std::string folderChars, fileChars;
    int folderCount, fileCount;

    // Ввод символов для названия папок и файлов
    std::cout << "Введите уникальные символы для названия папок: ";
    std::cin >> folderChars;

    std::cout << "Введите количество папок: ";
    std::cin >> folderCount;

    std::cout << "Введите уникальные символы для названия файлов: ";
    std::cin >> fileChars;

    std::cout << "Введите количество файлов: ";
    std::cin >> fileCount;

    // Открываем файл лога для записи
    std::ofstream logFile("log.txt");
    if (!logFile.is_open()) {
        std::cerr << "Ошибка открытия файла лога." << std::endl;
        return 1;
    }

    NameGenerator folderNameGenerator(folderChars, folderCount);
    NameGenerator fileNameGenerator(fileChars, fileCount);


    // Передаем файл лога для записи
    folderNameGenerator.GenerateNames(logFile);
    fileNameGenerator.GenerateNames(logFile);

    // Закрываем файл лога
    logFile.close();


    return 0;
}
