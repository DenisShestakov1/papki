#include <iostream> 
#include <fstream> 
#include <string>   
void generateNames(std::string uniqueChars, int length, std::string& name, std::ofstream& logFile, int& fileCount) {
   

    for (char c : uniqueChars) {
        std::string newName = name + c; 

        if (length == 1) { 
        
                std::cout << "Создан файл " << newName << std::endl; 
                logFile << "Создан файл " << newName << std::endl;  
                fileCount--; 
            
        }
        else { 
            std::cout << "Создана папка " << newName << std::endl; 
            logFile << "Создана папка " << newName << std::endl;   

       
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
