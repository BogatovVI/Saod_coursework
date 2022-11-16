#include <utility>
#include "main_List.h"
#include "Input.h"

class List_main {
private:
    main_List* Head;//Голова главного списка
    std::string Name_firm;//Название торговой фирмы
public:
    List_main(){//Конструктор
        Head = new main_List;
        Head->vendor_name = "Заголовок.";
        Head->next = nullptr;
        Name_firm = "Должник.";
    }

    ~List_main(){//Деструктор
        main_List* Cur; main_List* Previous;
        Cur = Head->next;
        Previous = Head;
        while (Cur != nullptr){
            Previous->next = Cur->next;
            delete Cur;
            Cur = Head->next;
            Previous = Head;
        }
        delete Head;
    };

    void set_Head(main_List* head){//Set метод для заголовка
        Head = head;
    }

    main_List* get_Head(){//Get метод для заголовка
        return Head;
    }

    void set_Name_firm(std::string name_firm){//Set для названия торговой фирмы
        Name_firm = std::move(name_firm);
    }

    std::string get_Name_firm(){//Get для названия торговой фирмы
        return Name_firm;
    }

    bool isEmpty(){//Проверка на пустоту
        if (Head->next == nullptr){
            return true;
        }
        else{
            return false;
        }
    }

    void insert_main(std::string data){//Добавление в главный список
        main_List* Temp; main_List* Cur; main_List* Previous;
        if (isEmpty()){
            Temp = new main_List;
            Temp->vendor_name = data;
            Temp->next = nullptr;
            Head->next = Temp;
        }
        else{
            if (unique(data)){
                std::cout << "\nТакой поставщик уже есть.\n";
            }
            else {
                Temp = new main_List;
                Temp->vendor_name = data;
                Cur = Head->next;
                Previous = Head;
                while(Cur != nullptr){
                    if (Temp->vendor_name < Cur->vendor_name){//Вставка элемента перед большим по значению
                        Temp->next = Cur;
                        Previous->next = Temp;
                        break;
                    }
                    else{
                        Cur = Cur->next;
                        Previous = Previous->next;
                    }
                }
                //Вставка в конец
                Previous->next = Temp;
                Temp->next = Cur;
            }
        }
    }

    void insert_sub(std::string search, std::string data, int count){//Добавление в вспомогательный список
        main_List* Cur;
        if (!isEmpty()){
            Cur = Head->next;
            while(Cur != nullptr){
                if (search == Cur->vendor_name){
                    break;
                }
                else{
                    Cur = Cur->next;
                }
            }
            Cur->sub.insert(data, count);
        }
        else{
            std::cout << "\nГлавный список пуст.\n";
        }
    }

    void remove_main(){//Удаление элемента главного списка
        main_List* Cur; main_List* Previous;
        if (!isEmpty()){
            std::string search;
            std::cout << "\nВведите имя поставщика, которого хотите удалить >> ";
            getline(std::cin, search);
            int flag = 0;
            Cur = Head->next;
            Previous = Head;
            while(Cur != nullptr){
                if (Cur->vendor_name == search){
                    flag = 1;
                    break;
                }
                else{
                    Cur = Cur->next;
                    Previous = Previous->next;
                }
            }
            if (flag == 1){
                Previous->next = Cur->next;
                delete Cur;
            }
            else{
                std::cout << "\nПоставщик не найден.\n";
            }
        }
        else{
            std::cout << "\nПоставщики не найдены.\n";
        }
    }

    void remove_sub(){//Удаление элемента вспомогательного списка
        main_List* Cur; main_List* Previous;
        if (!isEmpty()){
            std::string search;
            int flag = 0;
            std::cout << "\nВведите имя поставщика, которого хотите найти >> ";
            getline(std::cin, search);
            Cur = Head->next;
            Previous = Head;
            while(Cur != nullptr){
                if (Cur->vendor_name == search){
                    flag = 1;
                    break;
                }
                else{
                    Cur = Cur->next;
                    Previous = Previous->next;
                }
            }
            if (flag == 1){
                Cur->sub.remove();
            }
            else{
                std::cout << "\nПоставщик не найден.\n";
            }
        }
        else{
            std::cout << "\nПоставщики не найдены.\n";
        }
    }

    bool find(std::string search){//Поиск элемента в главном списке
        main_List* Cur;
        Cur = Head->next;
        while(Cur != nullptr){
            if (Cur->vendor_name == search){
                return true;
            }
            else{
                Cur = Cur->next;
            }
        }
        return false;
    }

    void find_for_all(){//Поиск товара среди всех поставщиков
        if (!isEmpty()){
            main_List* Cur; std::string search; bool flag = false;
            std::cout << "\nВведите название товара >> ";
            getline(std::cin, search);
            Cur = Head->next;
            while(Cur != nullptr){
                if (Cur->sub.find(search)){
                    flag = true;
                    std::cout << "\nТовар есть у поставщика: " + Cur->vendor_name;
                }
                Cur = Cur->next;
            }
            if (flag){
                std::cout << "\n";
            }
            else{
                std::cout << "\nТовары не найдены.\n";
            }
        }
        else{
            std::cout << "\nПоставщики не найдены.\n";
        }
    }

    bool unique(std::string data){// Проверка на уникальность добавления поставщика
        if(find(data)){
            return true;
        }
        else {
            return false;
        }
    }

    void print(){
        main_List* Cur;
        if (!isEmpty()){
            Cur = Head->next;
            while(Cur != nullptr){
                std::cout << "----------------------------------------------------------------------------------\n";
                std::cout << "Поставщик: " << Cur->vendor_name;
                Cur->sub.print();
                Cur = Cur->next;
            }
        }
        else{
            std::cout << "\nПоставщики не найдены.\n";
        }
    }

    void print_file(std::ofstream &out){//Вывод в файл информации структуры
        main_List* Cur;
        if (!isEmpty()){
            Cur = Head->next;
            while(Cur != nullptr){
                out << "Поставщик: " << Cur->vendor_name << '\n';
                Cur->sub.print_file(out);
                Cur = Cur->next;
            }
        }
        else{
            std::cout << "\nПоставщики не найдены.\n";
        }
    }

    void read_file(std::ifstream &inp){//Считывание информации в структуру с файла
        std::string data, product, count, search;
        while(!inp.eof()){
            getline(inp, data);
            if (data.empty()){
                while(!inp.eof()){
                    getline(inp, product);
                    if (product.empty()){
                        break;
                    }
                    else{
                        getline(inp, count);
                        insert_sub(search, product, std::stoi(count));
                    }
                }
            }
            else{
                insert_main(data);
                search = data;
            }
        }
    }
};