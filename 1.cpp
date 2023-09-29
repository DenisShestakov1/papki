#include <iostream> 
#include <fstream> 
#include <string>   
void generateNames(std::string uniqueChars, int length, std::string& name, std::ofstream& logFile, int& fileCount) {
    // Функция для генерации имен файлов и папок.

    for (char c : uniqueChars) { // Для каждого символа 'c' в строке 'uniqueChars' выполняем следующий блок кода.
        std::string newName = name + c; // Создаем новое имя, добавляя 'c' к текущему 'name'.

        if (length == 1) { // Если длина 'length' равна 1, то выполняем следующий блок кода (генерация имен файлов).
        
                std::cout << "Создан файл " << newName << std::endl; // Выводим сообщение о создании файла в консоль.
                logFile << "Создан файл " << newName << std::endl;   // Записываем сообщение о создании файла в файл лога.
                fileCount--; // Уменьшаем счетчик оставшихся файлов.
            
        }
        else { // Иначе (для длины 'length' больше 1) выполняем следующий блок кода (генерация имен папок).
            std::cout << "Создана папка " << newName << std::endl; // Выводим сообщение о создании папки в консоль.
            logFile << "Создана папка " << newName << std::endl;   // Записываем сообщение о создании папки в файл лога.

            // Рекурсивно генерируем имена для содержимого папки.
            generateNames(uniqueChars, length - 1, newName, logFile, fileCount);
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

    std::ofstream logFile("log.txt");

    std::string initialName; 
    generateNames(uniqueChars, folderCount, initialName, logFile, fileCount); 

    logFile.close();

    return 0;
}


    logFile.close();

    return 0;
}
