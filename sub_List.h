#include <iostream>

//Описание структуры для класса List_sub

struct element{//Элемент массива
    std::string name;//Название товара
    int count;//Количество товара
};

struct sub_List{
    element array[100];
    int Cur;
    int array_count;//Количество элементов в массиве
};