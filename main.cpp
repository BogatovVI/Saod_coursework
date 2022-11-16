#include <iostream>
#include <fstream>
#include "List_main.h"
#include "Input.h"

int main() {
    List_main listMain;
    int menu, count;
    std::string data, search;
    std::cout << "Торговая фирма: " + listMain.get_Name_firm() << "\n";
    while(true){
        std::cout << "----------------------------------------------------------------------------------";
        std::cout << "\n1: Вывод данных.\n2: Добавить поставщика.\n3: Добавить товар.\n4: Удалить поставщика."
                  << "\n5: Удалить товар.\n6: Записать в файл.\n7: Считать с файла."
                     "\n8: Поиск поставщика.\n9: Поиск товара."
                     "\n0: Выход."
                  << "\nВыберите действие ";
        menu = input_int();
        if (menu == 1){
            listMain.print();
        }
        else if (menu == 2){
            std::cout << "\nВведите поставщика >> ";
            getline(std::cin, data);
            listMain.insert_main(data);
        }
        else if (menu == 3){
            std::cout << "\nВведите имя поставщика для поиска >> ";
            getline(std::cin, search);
            if (listMain.find(search)){
                std::cout << "\nВведите название товара >> ";
                getline(std::cin, data);
                std::cout << "\nВведите количество товара ";
                count = input_int();
                listMain.insert_sub(search, data, count);
            }
            else{
                std::cout << "\nПоставщик не найден.\n";
            }
        }
        else if (menu == 4){
            listMain.remove_main();
        }
        else if (menu == 5){
            listMain.remove_sub();
        }
        else if (menu == 6){
            try{
                std::ofstream out("/Users/vladislavbogatov/Desktop/Учеба/Саод курсовая /Output.txt");
                listMain.print_file(out);
                out.close();
            }
            catch (const std::exception &ex){
                std::cout << "\nОшибка записи в файл.\n";
            }
        }
        else if (menu == 7){
            try{
                std::ifstream inp("/Users/vladislavbogatov/Desktop/Учеба/Саод курсовая /Input.txt");
                listMain.read_file(inp);
                inp.close();
            }
            catch (const std::exception &ex){
                std::cout << "\nОшибка записи в файл.\n";
            }
        }
        else if (menu == 8){
            std::cout << "\nВведите поставщика >> ";
            getline(std::cin, data);
            if(listMain.find(data)){
                std::cout << "\nПоставщик " + data + " есть в списке.\n";
            }
            else{
                std::cout << "\nПоставщик не найден.\n";
            }
        }
        else if (menu == 9){
            listMain.find_for_all();
        }
        else if (menu == 0){
            return 0;
        }
        else{
            std::cout << "\nНеправильный ввод.\n";
        }
    }
}

int input_int() {//Функция проверки на ввод данных
    int in;
    while (true) {
        std::cout << ">> ";
        std::cin >> in;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Введите корректное значение.\n";
            continue;
        }
        std::cin.ignore(32767, '\n');
        if (std::cin.gcount() > 1) {
            std::cout << "Введите корректное значение.\n";
            continue;
        }
        break;
    }
    return in;
}