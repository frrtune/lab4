#include <pdcurses.h>
#include <stdlib.h>
#include "ui.h"
#include "../containers/dynamic_array.h"
#include "../data_types/integer.h"
#include "../data_types/complex.h"

void integer_menu() {
    DynamicArray* arr = array_initialize(5, GetIntFieldInfo());
    int in_progress = 1;
    int value;
    char buff[15];
    while (in_progress) {
        clear();
        printw("INTEGER NUMBERS\n");
        printw("Current array: ");
        if (arr->size == 0) {
            printw("[]");
        } else {
            printw("[");
            for (size_t i = 0; i < arr->size; i++) {
                int* current = (int*)((char*)arr->data + (arr->info->size * i));
                printw("%d", *current);
                if (i < arr->size - 1) printw(", ");
            }
            printw("]");
        }
        printw("\n1. Add element\n");
        printw("2. Remove last\n");
        printw("3. Back\n");
        printw("Choose:\n");
        refresh();
        int ch = getch();
        switch(ch) {
            case '1':
                echo();
                curs_set(1);
                printw("\nEnter number: ");
                refresh();
                scanw("%s", buff);
                noecho();
                curs_set(0);
                char* endptr;
                errno = 0;
                long value = strtol(buff, &endptr, 10); 
                int* new_elem = malloc(sizeof(int));
                *new_elem = value;
                array_push_back(arr, new_elem);
                refresh();
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

void complex_menu() {
    DynamicArray* arr = array_initialize(5, GetComplexFieldInfo());
    int in_progress = 1;
    char re_buff[15];
    char im_buff[15];
    while (in_progress) {
        clear();
        printw("COMPLEX NUMBERS\n");
        printw("Current array: ");
        if (arr->size == 0) {
            printw("[]");
        } else {
            printw("[");
            for (size_t i = 0; i < arr->size; i++) {
                Complex* current = (Complex*)((char*)arr->data + (arr->info->size * i));
                printw("%d", current->Re);
                if (current->Im >= 0) {
                    printw("+ %di", current -> Im);
                } else {
                    printw("%di", current -> Im);
                }
                if (i < arr->size - 1) printw(", ");
            }
            printw("]");
        }
        printw("\n1. Add element\n");
        printw("2. Remove last\n");
        printw("3. Back\n");
        printw("Choose:\n");
        refresh();
        int ch = getch();
        switch(ch) {
            case '1':
                echo();
                curs_set(1);
                printw("\nEnter the real part of a number: ");
                refresh();
                scanw("%s", re_buff);
                printw("\nEnter the imaginary part of a number: ");
                refresh();
                scanw("%s", im_buff);
                noecho();
                curs_set(0);
                char* endptr1;
                char* endptr2;
                errno = 0;
                long re_value = strtol(re_buff, &endptr1, 10);
                long im_value = strtol(re_buff, &endptr2, 10);
                if (errno == 0 && endptr1 == "\0" && endptr2 == "\0"){
                    Complex* new_elem = malloc(sizeof(Complex));
                    new_elem->Re = re_value;
                    new_elem->Im = im_value;
                    array_push_back(arr, new_elem);
                } else {
                    printw("Error: invalud input");
                    refresh();
                    getch();
                }
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

void open_ui() {
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
                complex_menu();
                break;
            case '3':
                in_progress = 0;
                break;
        }
    }
    endwin();
}