//
//  main.c
//  C++(HomeTasks)
//
//  Created by Egor Safronov on 10.09.16.
//  Copyright © 2016 Egor Safronov. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int id;
    char *name;
    char *phone;
    bool avail;
} person;

person *a;
int size = 0;       //размер
int n = 0;          //текущий номер
int id_now = 0;     //последний id
int not_avail = 0;  //количество недоступных
char *filename;
FILE *f_null = NULL;//станд_поток
bool is_read = false;
bool need_to_find = false;

void alloc_extra_space() {
    if (size == n) {
        person *temp_a = (person *) malloc(sizeof(person *) * (n - not_avail) * 2);
        int temp_i = 0;
        for (int i = 0; i < size; i++) {
            if (a[i].avail) {
                temp_a[temp_i++] = a[i];
            }
        }
        size = (n - not_avail) * 2;
        n = --temp_i;
        not_avail = 0;
        free(a);
        a = temp_a;
    }
}

void save() {
    if (is_read) {
        return;
    }
    FILE * f_temp;
    f_temp = fopen(filename, "w+");
    for (int i = 0; i < n; i++) {
        if (a[i].avail) {
            fprintf(f_temp, "%d %s %s\n", a[i].id, a[i].name, a[i].phone);
        }
    }
    fclose(f_temp);
    return;
    
}

void create(int id, char *name, char *phone) {
    alloc_extra_space();
    person temp_person;
    temp_person.id = id;
    temp_person.name = name;
    temp_person.phone = phone;
    temp_person.avail = true;
    a[n++] = temp_person;
    save();
    return;
}

void delete(int id) {
    for (int i = 0; i < n; i++) {
        if (a[i].id == id) {
            a[i].avail = false;
            save();
            return;
        }
    }
}

char *read_s(FILE * f_temp) {
    bool is_null;
    if (f_temp == NULL) {
        is_null = true;
    } else {
        is_null = false;
    }
    char *str_temp = (char *) malloc(sizeof(char) * 30);
    char x;
    if (is_null) {
        scanf("%c", &x);
    } else {
        fscanf(f_temp, "%c", &x);
    }
    int i_temp = 0;
    while (x != '\n') {
        str_temp[i_temp++] = x;
        if (i_temp == strlen(str_temp)) {
            str_temp = (char *) realloc(str_temp, sizeof(char) * (strlen(str_temp) + 1));
            if (is_null) {
                scanf("%c", &x);
            } else {
                fscanf(f_temp, "%c", &x);
            }
        }
    }
    str_temp[i_temp] = '\0';
    return str_temp;
}

void init() {
    FILE * f;
    f = fopen(filename, "a+");
    is_read = true;
    int id;
    char *name;
    char *phone;
    while (fscanf(f, "%d", &id) != EOF) {
        fscanf(f, "%*c");
        name = read_s(f);
        phone = read_s(f);
        create(id, name, phone);
        if (id >= id_now) {
            id_now = id + 1;
        }
    }
    is_read = false;
    fclose(f);
    return;
}


char *name_to_normal(char *str) {
    char *temp = (char *) malloc(sizeof(char) * strlen(str));
    for (int i = 0; i < strlen(str); i++) {
        temp[i] = str[i];
        if (temp[i] >= 'a') {
            temp[i] -= 'a' - 'A';
        }
    }
    temp[strlen(str) + 1] = '\0';
    return temp;
}

char *phone_to_normal(char *str) {
    char *temp = (char *) malloc(sizeof(char) * strlen(str));
    int i_temp = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (isdigit(str[i])) {
            temp[i_temp++] = str[i];
        }
    }
    temp[i_temp] = '\0';
    return temp;
}

void find() {
    char *str;
    str = read_s(f_null);
    bool is_name = isalpha(str[0]);
    if (is_name) {
        str = name_to_normal(str);
    } else {
        str = phone_to_normal(str);
    }
    for (int i = 0; i < n; i++) {
        need_to_find = false;
        if (is_name && (strstr(name_to_normal(a[i].name), str) != NULL)) {
            need_to_find = true;
        } else if (!is_name && (strcmp(str, phone_to_normal(a[i].phone)) == 0)) {
            need_to_find = true;
        }
        if (need_to_find) {
            printf("%d %s %s\n", a[i].id, a[i].name, a[i].phone);
        }
    }
    return;
}

int main(int argc, char **args) {
    if (argc > 0) {
        filename = args[1];
    } else {
        filename = "error";
    }

    size = 10;
    a = (person *) malloc(sizeof(person) * size);
    
    init();
    int main_id;
    char *main_name;
    char *main_phone;
    char *main_str;
    char command[15];
    
    while (1) {
        scanf("%s%*c", command);
        if (strcmp(command, "find") == 0) {
            find();
            continue;
        }
        if (strcmp(command, "create") == 0) {
            main_name = read_s(f_null);
            main_phone = read_s(f_null);
            create(id_now++, main_name, main_phone);
            continue;
        }
        if (strcmp(command, "delete") == 0) {
            scanf("%d", &main_id);
            delete(main_id);
            continue;
        }
        if (strcmp(command, "change") == 0) {
            scanf("%d%*c", &main_id);
            scanf("%s%*c", command);
            main_str = read_s(f_null);
            for (int i = 0; i < n; i++) {
                if ((a[i].id == main_id) && (a[i].avail)) {
                    if (command[1] == 'a') {
                        a[i].name = command;
                    } else {
                        a[i].phone = command;
                    }
                    break;
                }
            }
            save();
            continue;
        }
        if (strcmp(command, "exit") == 0) {
            save();
            for (int i = 0; i < n; i++) {
                free(a[i].name);
                free(a[i].phone);
            }
            free(a);
            return 0;
        }
        printf("Error: Incorrect input!");
        return 0;
    }
    
    return 0;
}
