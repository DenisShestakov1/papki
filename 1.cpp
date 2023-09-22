#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void generateNames(std::string uniqueChars, int length, std::vector<std::string>& names) {
    if (length == 0) {
        return;
    }
    for (char c : uniqueChars) {
        std::string name(1, c);
        names.push_back(name);

        if (length > 1) {
            std::vector<std::string> subNames;
            generateNames(uniqueChars, length - 1, subNames);

            for (const std::string& subName : subNames) {
                names.push_back(name + subName);
            }

        }
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    std::string uniqueChars;
    int folderCount, fileCount;

    std::cout << "Введите уникальные символы для названия папок: ";
    std::cin >> uniqueChars;

    std::cout << "Введите количество папок: ";
    std::cin >> folderCount;

    std::cout << "Введите количество файлов: ";
    std::cin >> fileCount;

    if (uniqueChars.length() == 0 || folderCount < 1 || fileCount < 1) {
        std::cout << "Ошибка: Некорректный ввод данных." << std::endl;
        return 1;
    }

    std::vector<std::string> folderNames;
    std::vector<std::string> fileNames;

    generateNames(uniqueChars, folderCount, folderNames);
    generateNames(uniqueChars, fileCount, fileNames);

    std::ofstream logFile("log.txt");
    int i = 0;
    for (const std::string& folderName : folderNames) {
        if (i >= folderCount) break;
        int j = 0;
        std::cout << "Создана папка " << folderName << std::endl;
        logFile << "Создана папка " << folderName << std::endl;

        for (const std::string& fileName : fileNames) {
            if (j >= fileCount) break;
            std::cout << "В папке " << folderName << " создан файл " << fileName << std::endl;
            logFile << "В папке " << folderName << " создан файл " << fileName << std::endl;
            j++;
        }
        i++;
    }

    logFile.close();

    return 0;
}
