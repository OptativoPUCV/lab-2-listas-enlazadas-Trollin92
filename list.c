#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List * new = (List *)malloc(sizeof(List));
    assert(new != NULL);
    new->head = NULL;
    new->tail = NULL;
    new->current = NULL;
    return new;
}

void * firstList(List * list) {
    if (list->head == NULL || list == NULL) {
        return NULL;
    }
    list->current = list->head;
    void * nodito = list->current->data;
    return nodito;
}

void * nextList(List * list) {
    if (list == NULL || list->current == NULL || list->current->next == NULL) {
        return NULL;
    }
    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    if (list == NULL || list->current == NULL) {
        return NULL;
    }
    while (1){
        if (list->current->next == NULL) {
            return list->current->data;
            break;
        }
        else list->current = list->current->next;
    }
    return NULL;
}

void * prevList(List * list) {
    if (list == NULL || list->current == NULL || list->current->prev == NULL) {
        return NULL;
    }
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node * new = createNode(data);
    if (list->head == NULL) {
        list->head = new;
        list->tail = new;
    }
    else {
        new -> next = list->head;
        list->head->prev = new;
        list->head = new;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if (list->current == NULL){
        list->current->data = data;
    }
    else {
        Node * new = createNode(data);
        if (list->current->next == NULL) {
            list->current->next = new;
            new->prev = list->current;
            list->tail = new;
        }
        else {
            new->next = list->current->next;
            new->prev = list->current;
            list->current->next->prev = new;
            list->current->next = new;
        }
        list->current = new;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (list->current == NULL) {
        return NULL;
    }
    void * dato = list->current -> data;
    if(list->current->prev == NULL) {
        list->head = list->current->next;
        if (list->head != NULL) list->head->prev = NULL;
        free(list->current);
        list->current = list->head;
    } else if (list->current->next == NULL){
        list->tail = list->current->prev;
        if (list->tail != NULL) list->tail->next = NULL;
        free(list->current);
        list->current = list->tail;
    } else {
        list->current->prev->next = list->current->next;
        list->current->next->prev = list->current->prev;
        free(list->current);
        list->current = list->current->next;
        //:)
    }
    return dato;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}
