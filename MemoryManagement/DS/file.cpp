//
// Created by kevin on 09/09/17.
//

#include "file.h"
#include <string>

/*
 * @brief constructor nulo de file<T>
 * Ejemplo:
    file<T> nulo;
 */
template <class T>
file<T>::file() {
    {
        data = NULL;
        size = 0;
        key = "";
        contador = 0;
        referenciado = false;
    }
}

/*
 * @brief constructor para un objeto file<T>
 * @param d es de tipo T y es el dato a dar
 * @param s es de tipo int y es el tamano del data
 * @param k es de tipo string y es la key
 * Ejemplo:
    file<int> abc(1997,4,"nacimiento");
 */
template <class T>
file<T>::file(T d, int s, std::string k) {
    size = s;
    data = d;
    dataPtr = (T*)malloc(size);
    dataPtr = &data;
    key = k;
    contador = 0;
    referenciado = true;
}

/*
 * @brief fija el data de tipo T al file, ademas suma al contador
 * @param d de tipo T
 */
template <class T>
void file<T>::setData(T d) {
    contador++;
    data = d;
    dataPtr = (T*)calloc(data,size);
}

/*
 * @brief obtiene el data en el file gracias al puntero de este
 * @return un tipo T con el data guardado
 */
template <class T>
T& file<T>::getData() {
    contador++;
    return *dataPtr;
}

/*
 * @brief el destructor de la clase
 */
template <class T>
file<T>::~file() {

}

/*
 * @brief indica el contador de la veces a las que ha sido accesado un objeto
 */
template <class T>
int file<T>::getContador() {
    return contador;
}

/*
 * @brief revisa si el file esta o no referenciando algo
 */
template <class T>
void file<T>::checkReferenciado() {
    if (*dataPtr == NULL || size == 0){
        clear();
        referenciado = false;
    }
}

/*
 * @brief indica si esta o no referenciado
 * @return 1 esta referenciado || 0 no esta referenciado
 */
template <class T>
bool file<T>::getReferenciado() {
    return referenciado;
}

/*
 * @brief limpia la memoria que tenia asignada un puntero, indica que no esta referenciado y fija el size a 0
 */
template <class T>
void file<T>::clear() {
    free(dataPtr);
    referenciado = false;
    size = 0;
}

/*
 * @brief Revisa si esa key ya esta asignada al file
 * @param other la key a compara
 * @return 1 esa key si es la del file || 0 esa key no es la del file
 */
template <class T>
bool file<T>::compareKey(std::string other) {
    if(other == key){
        return true;
    }else{
        return false;
    }

}

/*
 * @brief obtener la key del file
 * @return un string con la key del file
 */
template <class T>
std::string file<T>::getKey(){
    return key;
}

/*
 * @brief aumenta en 1 el contador del file
 */
template <class T>
void file<T>::increaseContador() {
    contador++;
}

/*
 * @brief fija el contador en 0
 */
template <class T>
void file<T>::resetContador() {
    contador = 0;
}