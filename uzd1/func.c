#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <list.h>
#define DATA_SIZE 32
#define INT_VALUE 1
#define FLOAT_VALUE 2
#define STRING_VALUE 3

/*** grazinama steko virsunes reiksme ***/
int peek(element *head)
{
    if(head != NULL)
    {
        return *(int*)head->data;
    }
    
    // priesingu atveju, sarasas yra tuscias
    else
    {
        printf("Klaida, sarasas yra tuscias!\n");
        exit(1);
    }
}

/*** spausdiname saraso dydi ***/
int saraso_dydis(element *head)
{   
    assert(head != NULL);
    int size = 0;
    while (head != NULL)
    {
        size++;
        head = head->next;
    }
    return size;
}

/*** Menu valdymas ***/
void kontrole_menu(element *head)
{   
    int number;
    int size;
    char buff[DATA_SIZE];
    do
    {       
        read_number(&number);
        switch (number)
        {
            case 0:              
                // sukuriame tuscia steka (esanti istriname)
                if(head != NULL)
                {
                    delete_list(&head);
                }
                printf("Naujas stekas sukurtas\n");
                break;

            case 1:
                // idedame nauja elementa i steka
                printf("Iveskite duomenis:\t");
                gets(buff);
                push(&head, buff);
                break;

            case 2:
                // isimame elementa is steko
                if(head == NULL)
                {
                    printf("Klaida, sarasas yra tuscias!\n");
                }                
                else
                {
                    pop(&head);
                }
                break;

            case 3:
                // konsoles valymas
                system("cls");
                spausdink_menu();
                break;

            case 4:
                // spausdiname steko elementu kieki
                if(head == NULL)
                {
                    printf("Klaida, sarasas yra tuscias!\n");
                }
                else
                {
                    size = saraso_dydis(head);
                    printf("Saraso dydis: %d\n", size);
                }                
                break;

            case 5:
                if(head == NULL)
                {
                    printf("Klaida, sarasas yra tuscias!\n");
                }
                else
                {
                    print_list(head);
                }
                break;

            case 6:
                // programos terminavimas
                printf("Pabaiga\n");
                if(head != NULL)
                {
                    delete_list(&head);
                }
                exit(0);   

            default:
                // netinkamai ivestas menu nr.
                printf("Netinkamas menu numeris!\n");
                break;
        }
        printf("\nIvesk skaiciu nuo 0 iki 6\n");
    } while (number != 6);    
}

/*** spausdiname sarasa ***/
void print_list(element *head)
{
    int i = 1;
    puts("*****************************************");
    puts("Spausdiname sarasa:");
    while ( head != NULL )
    {
        printf( "%d elementas yra ", i);
        if (head->type == 1)
        {
            printf("%d\n", *(int*)head->data);
        }
        if (head->type == 2)
        {
            printf("%lf\n", *(double*)head->data);
        }
        if (head->type == 3)
        {
            printf("%s\n", (char*)head->data);
        }
        head = head->next;
        i++;
    }
}

/*** atskleidziame duomenu tipa ***/
void find_type(int *type, int *len, void *ptr)
{   
	char *number = ptr;
    char *foo;

    double d = strtod(number, &foo);
    // tikriname, ar tai yra char duomenu tipo masyvas
    if (foo == number)
    {
        *type = STRING_VALUE;
        *len = strlen((char*)ptr);
    }

    // tikriname, ar tai yra char duomenu tipo masyvas
    else if (foo[strspn(foo, " \t\r\n")] != '\0') 
    {
        *type = STRING_VALUE;
        *len = strlen((char*)ptr);
    }

    // isrinkame tarp int ir float duomenu tipo
    else
    { 
        int flag = 0;
        int length = strlen((char*)ptr);
        while(length --)
        {
            if(*(char *)(ptr + length) == '.')
            {
                flag = 1;
                break;
            }
        }
        if(flag)
        {
            *type = FLOAT_VALUE;
            *len = sizeof(double);
            return;
        }

        else
        {
            *type = INT_VALUE;
            *len = sizeof(int);
        }
    }
}

/*** isisame is steko elementa ***/
void pop(element **head)
{
    element *temp = *head;
    (*head) = (*head)->next;
    if(temp->data != NULL)
    {
        free(temp->data);
    }
    free(temp);
}

/*** idedame nauja elementa i steka ***/
void push(element **head, void *ptr)
{
    // Allokuojame duomenis strukturai
    element *new = (element*)malloc(sizeof(element));
    int len;
    int type;

    find_type(&type, &len, ptr);

    new->data = malloc(len);
    new->next = (*head);

    int iptr;
    double fptr;
    new->type = type;

    if(type == 1)
    {
        iptr = atoi((char*)ptr);
        ptr = &iptr;
    }
    else if (type == 2)
    {
        fptr = atof((char*)ptr);
        ptr = &fptr;
    }

    // iskonvertuoti duomenys irasomi i netipizuota rodykle
    for(int i = 0; i < len; i++)
    {
        *(char*)(new->data + i) = *(char*)(ptr + i);
    }
    
    if (type == 3)
    {
        *(char *)(new->data + len) = '\0';
    }
    // atnaujinamas ,,headerio" adresas
    (*head) = new;   
}

/*** atlaisviname atminti ***/
void delete_list(element **head)
{   
    assert(*head != NULL);
    element *einamasis;
    element *pabaiga = *head;

    // Sarasa naikinsime nuo galo, todel randame paskutinio simbolio adresa
    while (pabaiga->next != NULL)
    {
        pabaiga = pabaiga->next;
    }

    // Naikiname nuo galo
    while (*head != NULL)
    {
        einamasis = *head;
        if (pabaiga != *head)
        {
            while (einamasis->next != pabaiga)
            {
                einamasis = einamasis->next;
            }
            pabaiga = einamasis;
            if(einamasis->next->data != NULL)
            {
                free(einamasis->next->data);
            }
            free(einamasis->next);
        }

        // Naikiname paskutini likusi simboli
        else
        {   
            if(einamasis->data != NULL)
            {
                free(einamasis->data);
            }
            free(einamasis);
            *head = NULL;
            pabaiga = NULL;
        }
    }
}

/*** Menu valdymo spausdinimas ***/
void spausdink_menu()
{
    printf("Menu:\n");
    printf("0   sukurti tuscia steka\n");
    printf("1   ideti nauja elementa i steka\n");
    printf("2   isimti elementa is steko\n");
    printf("3   isvalo konsole\n");
    printf("4   saraso dydis\n");
    printf("5   spausdinti sarasa\n");
    printf("6   isejimas\n");
}