#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>  // для std::setw и std::setfill
#include <cryptopp/sha.h> // SHA-256
#include <cryptopp/hex.h> // кодирование в hex
#include <cryptopp/files.h> // для FileSource

using namespace CryptoPP;
using namespace std;

// Функция для хэширования содержимого файла
string hashFile(const string& filename) {
    try {
        // Объект для хранения хэша
        string digest;

        // Создаем объект SHA256 на стеке
        SHA256 sha256;

        // Чтение файла и хэширование его содержимого
        FileSource file(
            filename.c_str(), 
            true, 
            new HashFilter(
                sha256, // Передаем ссылку на объект SHA256
                new HexEncoder(new StringSink(digest))
            )
        );

        return digest;
    } catch (const CryptoPP::Exception& e) {
        cerr << "Ошибка при хэшировании: " << e.what() << endl;
        return "";
    } catch (const ifstream::failure& e) {
        cerr << "Ошибка чтения файла: " << e.what() << endl;
        return "";
    }
}

int main(int argc, char* argv[]) {
    // Проверяем наличие аргументов командной строки
    if (argc != 2) {
        cerr << "Использование: " << argv[0] << " <путь к файлу>" << endl;
        return 1;
    }

    string filename = argv[1];

    // Вызываем функцию для хэширования файла
    string hash = hashFile(filename);

    // Выводим хэш файла
    cout << "Хэш файла " << filename << ": " << hash << endl;

    return 0;
}
