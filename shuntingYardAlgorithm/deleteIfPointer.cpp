/*
source:
https://stackoverflow.com/questions/27604915/c-templates-how-to-conditionally-delete-values-by-stdis-pointer
*/

#include <iostream>

template <class T>
void deleteIfPointer(T const & t){
}

template <class T>
void deleteIfPointer(T* const t){
    delete t;
}

// template <class T>
// void deleteIfPointer(T** t){
//     // std::cout << "a pointer\n" << *t;
    
//     delete *t;
//     delete t;
// }
