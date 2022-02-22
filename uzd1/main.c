/*
    LSP 2110561
    1 užduotis, variantas - stack 
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <list.h>

int main()
{
    struct element *head = NULL;
    spausdink_menu();
    printf("\nIvesk skaiciu nuo 0 iki 6\n");
    kontrole_menu(head);
    return 0;
}

/*** skaiciaus validacija ***/
void read_number(int *number)
{
    while (scanf("%d", number) != 1 || getchar() != '\n')
    {
        scanf("%*[^\n]");
        printf("Netinkama ivestis\n");
    }
}