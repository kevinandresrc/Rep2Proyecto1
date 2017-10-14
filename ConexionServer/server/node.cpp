//
// Created by kevin on 09/09/17.
//

#include "file.h"
#include <string>

/*
 * Ejemplo de como empezar una lista:
    file<int> abc(1997,4,"nacimiento");
    struct Node<int>* head = NULL;
    listAppend(&head,abc);
    file<int> cba(2017,4,"actual");
    listAppend(&head,cba);
 */

/*
template <class T>
void listAppend(struct Node<T>** head_ref, file<T> new_data);
void printList(struct Node<T> *node);
void listDelete(struct Node<T> **head_ref, std::string key);
int listSize(struct Node<T>* head);
file<T> listSearch(struct Node<T>* head, std::string x);
bool listContain(struct Node<T>* head, std::string x);
void listChange(struct Node<T>* head, std::string x, T newData);
void listDeleteFile(struct Node<T> **head_ref, int position);
int listGetPosFile(struct Node<T>* head, std::string x);
file<T> listGet(struct Node<T>* head, int k);
void MergeSort(struct Node<T>** headRef);
void FrontBackSplit(struct Node<T>* source, struct Node<T>** frontRef, struct Node<T>** backRef);
void listClear(struct Node<T>* head);
void listReset(struct Node<T>* head);
file<T> getCache(struct Node<T>* head, int num);
void resetAccesos(struct Node<T>* head);
*/


template <class T>
struct Node{
    file<T> data;
    struct Node* next;
};

/*
 * @brief Agrega un file<T> al final de la lista
 * @param Node<T>** head_ref es la head de la lista(&head)
 * @param new_data objeto file a agregar
 */
template <class T>
void listAppend(struct Node<T>** head_ref, file<T> new_data)
{
    struct Node<T>* new_node = (struct Node<T>*) malloc(sizeof(struct Node<T>));
    struct Node<T> *last = *head_ref;
    new_node->data  = new_data;
    new_node->next = NULL;
    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
    return;
}

/*
 * @brief Imprime la lista
 * @param *node es la head de la lista(head)
 */
template <class T>
void printList(struct Node<T> *node)
{
    while (node != NULL)
    {
        std::cout<<node->data.getKey()<<" , ";
        node = node->next;
    }
    std::cout<< "" <<std::endl;
}

/*
 * @brief Elimina un nodo de la lista, obteniendo el key del nodo por eliminar
 * @param **head_ref es la head de la lista(&head)
 * @param key la llave a buscar y eliminar
 */
template <class T>
void listDelete(struct Node<T> **head_ref, std::string key)
{
    struct Node<T>* temp = *head_ref, *prev;
    if (temp != NULL && temp->data.getKey() == key)
    {
        *head_ref = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->data.getKey() != key)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;
    prev->next = temp->next;
    free(temp);
}

/*
 * @brief obtiene el largo de la lista
 * @param head la head de la lista(head)
 * @return int con el tamano de la lista
 */
template <class T>
int listSize(struct Node<T>* head)
{
    int count = 0;
    struct Node<T>* current = head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

/*
 * @brief busca un elemento en la lista
 * @param head la head de la lista(head)
 * @param x el string key a buscar
 * @return file solicitado
 */
template <class T>
file<T> listSearch(struct Node<T>* head, std::string x)
{
    struct Node<T>* current = head;
    while (current != NULL)
    {
        if (current->data.getKey() == x) {
            current->data.increaseContador();
            return current->data;
        }
        current = current->next;
    }
    return file<T>();
}

/*
 * @brief revisa si exite un elemento en la lista con la misma key
 * @param head la head de la lista(head)
 * @param x el key a revisar si existe o no en la lista
 * @return 1 si esta || 0 no esta
 */
template <class T>
bool listContain(struct Node<T>* head, std::string x){
    struct Node<T>* current = head;
    while (current != NULL)
    {
        if (current->data.getKey() == x) {
            return true;
        }
        current = current->next;
    }
    return false;
}

/*
 * @brief cambia el data en el nodo con la key dada
 * @param head la head de la lista(head)
 * @param x la key por buscar
 * @param newData el nuevo dato a poner a el file de la key dada
 */
template <class T>
void listChange(struct Node<T>* head, std::string x, T newData){
    struct Node<T>* current = head;
    while (current != NULL)
    {
        if (current->data.getKey() == x)
            current->data.setData(newData);
        current = current->next;
    }
}

/*
 * @brief elimina un nodo de la lista de acuerdo a la posicion dada
 * @param **head_ref la head de la lista(&head)
 * @param position la posicion del nodo a eliminar
 */
template <class T>
void listDeleteFile(struct Node<T> **head_ref, int position)
{
    if (*head_ref == NULL)
        return;

    struct Node<T>* temp = *head_ref;

    if (position == 0)
    {
        *head_ref = temp->next;
        free(temp);
        return;
    }

    for (int i=0; temp!=NULL && i<position-1; i++)
        temp = temp->next;

    if (temp == NULL || temp->next == NULL)
        return;

    struct Node<T> *next = temp->next->next;

    free(temp->next);

    temp->next = next;
}

/*
 * @brief obtiene la posicion de un file en la lista
 * @param *head la head de la lista(head)
 * @param x el key a buscar en la lista
 */
template <class T>
int listGetPosFile(struct Node<T>* head, std::string x){
    int pos = 0;
    struct Node<T>* current = head;
    while (current != NULL)
    {
        if (current->data.getKey() == x)
            return pos;
        current = current->next;
        pos++;
    }
    return -1;

}


/*
 * @brief obtiene el archivo en una determina posicion
 * @param *head la head de la lista (head)
 * @param k el int de la posicion a buscar en la lista
 */
template <class T>
file<T> listGet(struct Node<T>* head, int k){
    int pos = 0;
    struct Node<T>* current = head;
    while (pos != k)
    {
        current = current->next;
        pos++;
    }
    return current->data;
}

/*
 * @brief ordena la lista de mayor a menor, de acuerdo a su contador de veces accesado
 * @param **headRef la head de la lista(&head)
 */
template <class T>
void MergeSort(struct Node<T>** headRef)
{
    struct Node<T>* head = *headRef;
    struct Node<T>* a;
    struct Node<T>* b;
    if ((head == NULL) || (head->next == NULL))
    {
        return;
    }
    FrontBackSplit(head, &a, &b);
    MergeSort(&a);
    MergeSort(&b);
    *headRef = SortedMerge(a, b);
}

/*
 * Parte del metodo MergeSort
 */
template <class T>
struct Node<T>* SortedMerge(struct Node<T>* a, struct Node<T>* b)
{
    struct Node<T>* result = NULL;

    if (a == NULL)
        return(b);
    else if (b==NULL)
        return(a);

    if (a->data.getContador() >= b->data.getContador())
    {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else
    {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return(result);
}

/*
 * Parte del metodo MergeSort
 */
template <class T>
void FrontBackSplit(struct Node<T>* source, struct Node<T>** frontRef, struct Node<T>** backRef)
{
    struct Node<T>* fast;
    struct Node<T>* slow;
    if (source==NULL || source->next==NULL)
    {
        *frontRef = source;
        *backRef = NULL;
    }
    else
    {
        slow = source;
        fast = source->next;

        while (fast != NULL)
        {
            fast = fast->next;
            if (fast != NULL)
            {
                slow = slow->next;
                fast = fast->next;
            }
        }

        *frontRef = source;
        *backRef = slow->next;
        slow->next = NULL;
    }
}

/*
 * @brief elimina de la lista todos los nodos que no han sido accedidos
 * @param *head la head de la lista(head)
 */
template <class T>
void listClear(struct Node<T>* head){
    struct Node<T>* current = head;
    int aux = 0;
    while (aux<listSize(head) && current!=NULL){
        if(current->data.getContador() == 0){
            current = current->next;
            listDeleteFile(&head,aux);
        }else{
            aux++;
            current = current->next;
        }
    }

}

/*
 * @brief resetea la lista
 * @param *head la head de la lista(head)
 */
template <class T>
void listReset(struct Node<T>* head){
    struct Node<T>* current = head;
    int aux = 0;
    while (aux<=listSize(head) && current!=NULL){
        current = current->next;
        listDeleteFile(&head,aux);
    }
}

/*
 * @brief obtiene un file de acuerdo a la posicion de la lista, se debe aplicar en la lista luego de ordenarla
 * y se le debe indicar en cual posicion se desea obtener para la cache
 * @param *head la head de la lista(head)
 * @param num el int de la posicion en la lista a obtener
 * @return file<T> de esa posicion en la lista
 */
template <class T>
file<T> getCache(struct Node<T>* head, int num){
    struct Node<T>* current = head;
    while(num!=0 && current!=NULL){
        current = current->next;
        num--;
    }
    return current->data;
}

/*
 * @brief devuelve todos los nodos a 0 como veces accesados
 * @param *head la head de la lista(head)
 */
template <class T>
void resetAccesos(struct Node<T>* head){
    struct Node<T>* current = head;
    while (current != NULL)
    {
        current->data.resetContador();
        current = current->next;
    }
}