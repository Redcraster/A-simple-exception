#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <stdexcept>

// Определение исключения
class bad_length : public std::exception {
public:
    const char* what() const noexcept override {
        return "Вы ввели слово запретной длины!";
    }
};

// Функция, проверяющая длину строки
int function(const std::string& str, int forbidden_length) {
    // Конвертируем строку UTF-8 в std::wstring
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wide_str = converter.from_bytes(str);
    
    int length = wide_str.length(); // Получаем количество символов

    if (length == forbidden_length) {
        throw bad_length();
    }
    return length;
}

int main() {
    int forbidden_length;
    std::cout << "Введите запретную длину: ";
    std::cin >> forbidden_length;
    std::cin.ignore();  // Очистка буфера ввода после ввода числа

    while (true) {
        std::string input;
        std::cout << "Введите слово: ";
        std::getline(std::cin, input);
        
        // Удаление пробельных символов в начале и конце строки
        input.erase(0, input.find_first_not_of(" \t\n\r\f\v"));
        input.erase(input.find_last_not_of(" \t\n\r\f\v") + 1);

        try {
            int length = function(input, forbidden_length);
            std::cout << "Длина слова \"" << input << "\" равна " << length << std::endl;
        } catch (const bad_length& e) {
            std::cout << e.what() << " До свидания" << std::endl;
            break;
        }
    }

    return 0;
}