#include <pdcurses.h>
#include <stdlib.h>
#include "../containers/dynamic_array.h"
#include "../data_types/integer.h"
#include "../data_types/complex.h"

void integer_menu() {
    DynamicArray* arr = array_initialize(5, GetIntFieldInfo());
    int in_progress = 1;
    int value;
    while (in_progress) {
        clear();
        printw("INTEGER NUMBERS\n");
        printw("Current array: ");
        if (arr->size == 0) {
            printw("[]");
        } else {
            printw("[");
            for (size_t i = 0; i < arr->size; i++) {
                printw("%d", *(int*)arr->data[i]);
                if (i < arr->size - 1) printw(", ");
            }
            printw("]");
        }
        printw("\n1. Add element\n");
        printw("2. Remove last\n");
        printw("3. Back\n");
        printw("Choose:\n");
        refresh();
        switch(getch()) {
            case '1':
                printw("\nEnter number: ");
                refresh();
                scanw("%d", &value);
                int* new_elem = malloc(sizeof(int));
                *new_elem = value;
                array_push_back(arr, new_elem);
                getch();
                break;
            case '2':
                if (arr->size > 0) array_remove_by_index(arr, arr->size - 1);
                getch();
                break;  
            case '3':
                in_progress = 0;
                break;
        }
    }
    array_destroy(arr);
}

int main() {
    initscr();
    noecho();
    int mode = 0;
    int in_progress = 1;
    while (in_progress) {
        clear();
        printw("DYNAMIC ARRAY FOR INTEGER AND COMPLEX NUMBERS\n");
        printw("1. Integer numbers\n");
        printw("2. Complex numbers\n");
        printw("3. Exit\n");
        printw("Choose a mode:\n");
        switch(getch()) {
            case '1':
                integer_menu();
                break;
            case '2':
                clear();
                printw("Complex numbers\n");
                printw("Press any key to exit");
                refresh();
                getch();
                break;
            case '3':
                in_progress = 0;
                break;
        }
    }
    endwin();
    return 0;
}