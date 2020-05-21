//
// Created by zugzvangg on 21.05.2020.
//
#include <ctime>
#include <iostream>

#ifndef RED_BLACK_TREE_TESTS_H
#define RED_BLACK_TREE_TESTS_H

unsigned int Searching(int n)
{
    unsigned int start_time =  clock(); // начальное время
    // здесь должен быть фрагмент кода, время выполнения которого нужно измерить
    unsigned int end_time = clock(); // конечное время
    unsigned int search_time = end_time - start_time;
    return search_time;// искомое время
}

int Inserting(int n)
{
    unsigned int start_time =  clock(); // начальное время
    // здесь должен быть фрагмент кода, время выполнения которого нужно измерить
    unsigned int end_time = clock(); // конечное время
    unsigned int search_time = end_time - start_time;
    return search_time;// искомое время
}

int Deleting(int n)
{
    unsigned int start_time =  clock(); // начальное время
    // здесь должен быть фрагмент кода, время выполнения которого нужно измерить
    unsigned int end_time = clock(); // конечное время
    unsigned int search_time = end_time - start_time;
    return search_time;// искомое время
}

int Max(int n)
{
    unsigned int start_time =  clock(); // начальное время
    // здесь должен быть фрагмент кода, время выполнения которого нужно измерить
    unsigned int end_time = clock(); // конечное время
    unsigned int search_time = end_time - start_time;
    return search_time;// искомое время
}


#endif //RED_BLACK_TREE_TESTS_H
