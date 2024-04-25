#include "../include/HashTable.h"

int main() {
    // Создание хэш-таблицы
    HashTable<std::string, int> table(10);

    // Вставка элементов
    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("three", 3);

    // Вывод содержимого
    std::cout << "Initial Table:" << std::endl;
    table.print();

    // Проверка наличия элемента
    std::cout << "Contains 'two': " << std::boolalpha << table.contains(2) << std::endl;

    // Поиск элемента
    int* value = table.search("three");
    if (value) {
        std::cout << "Value of 'three': " << *value << std::endl;
    }
    else {
        std::cout << "Key 'three' not found" << std::endl;
    }

    // Вставка или присвоение значения по ключу
    table.insert_or_assign("three", 33);
    std::cout << "Table after insert_or_assign('three', 33):" << std::endl;
    table.print();

    // Удаление элемента
    table.erase("two");
    std::cout << "Table after erasing 'two':" << std::endl;
    table.print();

    // Количество элементов по ключу
    std::cout << "Count of 'three': " << table.count("three") << std::endl;


    HashTable<int, std::string> table1(5);

    // Вставка элементов, которые будут иметь коллизии
    table1.insert(5, "apple");
    table1.insert(11, "banana");

    // Вывод содержимого
    std::cout << "Table after inserting 'apple' and 'banana':" << std::endl;
    table1.print();

    // Попытка вставить элемент с коллизией
    table1.insert(20, "orange");

    // Вывод содержимого после попытки вставки элемента с коллизией
    std::cout << "Table after attempting to insert 'orange':" << std::endl;
    table1.print();


    // Проверка хэш-таблицы для целочисленных ключей и значений
    HashTable<int, int> table2(10);
    table2.insert(1, 1);
    table2.insert(3, -1);
    table2.insert(4, 4);
    table2.print();
    table2.insert(3, 2);
    std::cout << "Contains '-1': " << std::boolalpha << table2.contains(-1) << std::endl;
    table2.insert_or_assign(3, 3);
    table2.insert(0, 0);
    table2.erase(4);
    table2.print();


    HashTable<char, int> nums(1);

    std::string romanNumber = "MMXXIV";  // Римское число "2024"

    size_t decimalValue = nums.romanToDecimal(romanNumber);
    std::cout << "Roman number " << romanNumber << " in the decimal system: " << decimalValue << std::endl;


    return 0;
}
