#include "../include/HashTable.h"

int main() {
    // �������� ���-�������
    HashTable<std::string, int> table(10);

    // ������� ���������
    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("three", 3);

    // ����� �����������
    std::cout << "Initial Table:" << std::endl;
    table.print();

    // �������� ������� ��������
    std::cout << "Contains 'two': " << std::boolalpha << table.contains(2) << std::endl;

    // ����� ��������
    int* value = table.search("three");
    if (value) {
        std::cout << "Value of 'three': " << *value << std::endl;
    }
    else {
        std::cout << "Key 'three' not found" << std::endl;
    }

    // ������� ��� ���������� �������� �� �����
    table.insert_or_assign("three", 33);
    std::cout << "Table after insert_or_assign('three', 33):" << std::endl;
    table.print();

    // �������� ��������
    table.erase("two");
    std::cout << "Table after erasing 'two':" << std::endl;
    table.print();

    // ���������� ��������� �� �����
    std::cout << "Count of 'three': " << table.count("three") << std::endl;


    HashTable<int, std::string> table1(5);

    // ������� ���������, ������� ����� ����� ��������
    table1.insert(5, "apple");
    table1.insert(11, "banana");

    // ����� �����������
    std::cout << "Table after inserting 'apple' and 'banana':" << std::endl;
    table1.print();

    // ������� �������� ������� � ���������
    table1.insert(20, "orange");

    // ����� ����������� ����� ������� ������� �������� � ���������
    std::cout << "Table after attempting to insert 'orange':" << std::endl;
    table1.print();


    // �������� ���-������� ��� ������������� ������ � ��������
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

    std::string romanNumber = "MMXXIV";  // ������� ����� "2024"

    size_t decimalValue = nums.romanToDecimal(romanNumber);
    std::cout << "Roman number " << romanNumber << " in the decimal system: " << decimalValue << std::endl;


    return 0;
}
