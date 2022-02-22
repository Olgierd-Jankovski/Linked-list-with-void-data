#ifndef LIST_H
#define LIST_H

/*
paleidimas per cmd
gcc -o list main.c func.c -I.
*/

/*** Saraso strukturos apibrezimas ***/
typedef struct element 
{
    struct element *next;
    void *data;
    int type;
} element;

/*** Funkcijos ***/
int saraso_dydis(element *head);

void read_number(int *number);

void kontrole_menu(element *head);

void spausdink_menu();

void delete_list(element **head);

void push (element **head, void *ptr);

void print_list(element *head);

void find_type(int *type, int *len, void *ptr);

void pop(element **head);

int peek(element *head);

#endif