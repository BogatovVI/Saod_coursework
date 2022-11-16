#include "sub_List.h"

class List_sub {
private:
    sub_List* subList;
public:
    List_sub(){//Конструктор
        subList = new sub_List;
        subList->array_count = 0;
        subList->Cur = -1;
    }

    ~List_sub(){//Деструктор
        delete subList;
    }

    void set_subList(sub_List* sub){//Set метод для subList
        subList = sub;
    }

    sub_List* get_subList(){//Get метод для subList
        return subList;
    }

    bool isEmpty(){//Проверка на пустоту
        if (subList->array_count == 0){
            return true;
        }
        else{
            return false;
        }
    }

    bool isFull(){//Проверка на полноту
        if (subList->array_count == 100){
            return true;
        }
        else{
            return false;
        }
    }

    void insert(std::string data, int count) {//Добавления элемента
        if (isEmpty()) {// добавление первого
            subList->array[0].name = data;
            subList->array[0].count = count;
            subList->array_count++;
        }
        else if (!isEmpty() && !isFull()) {
            if(unique(data)){
                std::cout << "\nТакой товар уже есть у данного поставщика.\n";
            }
            else {
                for (int n = 0; n <= subList->array_count; n++) {
                    if (n == subList->array_count) {//Вставка в конец массива
                        subList->array[subList->array_count].name = data;
                        subList->array[subList->array_count].count = count;
                        subList->array_count++;
                        break;
                    }
                    if (data < subList->array[n].name) {//Вставка между элементами
                        for (int i = subList->array_count; i > n; i--) {
                            subList->array[i].name = subList->array[i - 1].name;
                            subList->array[i].count = subList->array[i - 1].count;
                        }
                        subList->array[n].name = data;
                        subList->array[n].count = count;
                        subList->array_count++;
                        break;
                    }
                }
            }
        }
        else {
            std::cout << "\nСписок полон.\n";
        }
    }

    void remove() {//Удаления элемента
        std::string data;
        if (!isEmpty()) {
            std::cout << "\nВведите товар, который хотите удалить >> ";
            getline(std::cin, data);
            if (find(data)) {
                for (int i = subList->Cur; i < subList->array_count; i++) {
                    subList->array[i].name = subList->array[i + 1].name;
                    subList->array[i].count = subList->array[i + 1].count;
                }
                subList->array_count--;
            }
            else{
                std::cout << "\nТовар не найден.\n";
            }
        }
        else {
            std::cout << "\nСписок пуст.\n";
        }
    }

    void print() {//Функция вывода списка на экран
        if (!isEmpty()) {
            for (int i = 0; i < subList->array_count; i++) {
                std::cout << "\nТовар: " <<subList->array[i].name << "  ";
                std::cout << "Количество: " << subList->array[i].count;
            }
            std::cout << '\n';
        }
        else {
            std::cout << "\nТовары у данного поставщика отсутствуют.\n";
        }
    }

    bool unique(std::string data){//Проверка на уникальность
        if (find(data)){
            return true;
        }
        else {
            return false;
        }
    }

    bool find(std::string data) {
        if (!isEmpty()) {
            subList->Cur = -1;
            for (int i = 0; i < subList->array_count; i++) {
                if (subList->array[i].name == data) {
                    subList->Cur = i;
                    return true;
                }
            }
        }
        else {
            subList->Cur = -1;
            return false;
        }
    }

    void print_file(std::ofstream &out){
        if (!isEmpty()) {
            for (int i = 0; i < subList->array_count; i++) {
                out << "Товар: " << subList->array[i].name << "  ";
                out << "Количество: " << subList->array[i].count << "\n\n";
            }
        }
        else{
            out << "Товары у данного поставщика отсутствуют.\n";
        }
    }
};