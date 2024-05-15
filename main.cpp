#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DynamicArray {
    unsigned int capacity = 16;
    char* array = (char*)calloc(capacity, sizeof(char));
    unsigned int size = 0;
} DynamicArray;

void arr_resize(DynamicArray* dynamicArray) {
    dynamicArray->capacity *= 2;
    dynamicArray->array = (char*)realloc(dynamicArray->array, dynamicArray->capacity);
}

void arr_append(DynamicArray* dynamicArray, char chr) {
    if (dynamicArray->size > dynamicArray->capacity) {
        arr_resize(dynamicArray);
    }

    dynamicArray->array[dynamicArray->size] = chr;
    dynamicArray->size++;
}

void arr_insert(DynamicArray* dynamicArray, char chr, unsigned int index) {
    if (index > dynamicArray->size) {
        printf("Index is too large");
        return;
    }

    if (dynamicArray->size > dynamicArray->capacity) {
        arr_resize(dynamicArray);
    }

    for (int i = dynamicArray->size; i >= 0; i--) {
        if (index == i) {
            dynamicArray->array[i] = chr;
            dynamicArray->size++;
            break;
        }
        dynamicArray->array[i] = dynamicArray->array[i-1];
    }
}

void arr_clear(DynamicArray* dynamicArray) {
    free(dynamicArray->array);
    dynamicArray->size = 0;
    dynamicArray->capacity = 16;
    dynamicArray->array = (char*)calloc(dynamicArray->capacity, sizeof(char));
}

DynamicArray characters;

void welcome() {
    printf("Welcome to text editor!\n");
    printf("1 - append text\n");
    printf("2 - start new line\n");
    printf("3 - load file\n");
    printf("4 - save to file\n");
    printf("5 - print text\n");
    printf("6 - insert by index\n");
    printf("7 - search\n");
    printf("8 - exit\n");
}

int get_command() {
    char char_command[1];

    printf("Choose a command:");
    fgets(char_command, 2, stdin);

    // ascii subtraction method
    int result = char_command[0] - '0';

    // try getting rid of it and entering 23455
    // clearing stdin
    fflush(stdin);

    return result;
}

void append() {
    char symbols[80];

    printf("Enter text to append:");
    fgets(symbols, 80, stdin);

    // -1 to avoid \n being added
    for (int i = 0; i < strlen(symbols)-1; i++) {
        arr_append(&characters, symbols[i]);
    }
}

void start_new_line() {
    printf("This command is not implemented yet\n");
}

void load_file() {
    FILE* pFile = fopen("text.txt", "r");

    char buffer[255];

    while (fgets(buffer, 255, pFile)) {
        for (int i = 0; i < strlen(buffer); i++) {
            arr_append(&characters, buffer[i]);
        }
    }

    fclose(pFile);

    printf("Text has been loaded successfully\n");
}

void save_in_file() {
    FILE* pFile = fopen("text.txt", "a");

    if (pFile == nullptr) {
        printf("Error opening file!");
        return;
    }

    for (int i = 0; i < characters.size; i++) {
        fprintf(pFile, "%c", characters.array[i]);
    }

    arr_clear(&characters);

    fclose(pFile);

    printf("Text has been saved successfully\n");
}

void print_text() {
    for (int i = 0; i < characters.size; i++) {
        printf("%c", characters.array[i]);
    }

    printf("\n");
}

void insert_by_index() {
    int index;
    printf("Choose index:");
    scanf("%d", &index);

    fflush(stdin);

    char symbols[80];
    printf("Enter text to insert:");
    fgets(symbols, 80, stdin);

    fflush(stdin);

    for (int i = 0; i < strlen(symbols)-1; i++) {
        arr_insert(&characters, symbols[i], index++);
    }
}

void search() {
    printf("This command is not implemented yet\n");
}

void parse_input(int command) {
    switch (command) {
        case 1:
            append();
            break;
        case 2:
            start_new_line();
            break;
        case 3:
            load_file();
            break;
        case 4:
            save_in_file();
            break;
        case 5:
            print_text();
            break;
        case 6:
            insert_by_index();
            break;
        case 7:
            search();
            break;
        case 8:
            printf("Exiting...");
            break;
        default:
            printf("No command with number %d\n", command);
            break;
    }
}

int main() {
    // for debug to work
    setbuf(stdout, 0);
    welcome();
    int command = get_command();
    while (command != 8) {
        parse_input(command);
        command = get_command();
    }
}