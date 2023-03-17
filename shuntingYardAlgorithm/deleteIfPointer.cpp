/*
source:
https://stackoverflow.com/questions/27604915/c-templates-how-to-conditionally-delete-values-by-stdis-pointer
*/

template <class T>
void deleteIfPointer(const T& t){
}

template <class T>
void deleteIfPointer(T* t){
    delete t;
}
