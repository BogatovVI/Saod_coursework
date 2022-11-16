#include "List_sub.h"

//Описание структуры для класса List_main

struct main_List{
    std::string vendor_name;//Имя поставщика
    List_sub sub;//Вспомогательный список
    main_List* next;//Указатель на следующий элемент
};