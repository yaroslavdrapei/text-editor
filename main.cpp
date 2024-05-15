#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DynamicArray {
    unsigned int capacity;
    char* array;
    unsigned int size;
} DynamicArray;

void create_dynamic_array(DynamicArray* dynamicArray) {
    dynamicArray->capacity = 16;
    dynamicArray->array = (char*)calloc(dynamicArray->capacity, sizeof(char));
    dynamicArray->size = 0;
}

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
        printf("Index is too large\n");
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
    char char_command[2];

    printf("Choose a command:");
    fgets(char_command, 3, stdin);

    // ascii subtraction method
    int result = atoi(char_command);

    // try getting rid of it and entering 23455
    // clearing stdin
    fflush(stdin);

    return result;
}

void append(DynamicArray* line) {
    char symbols[80];

    printf("Enter text to append:");
    fgets(symbols, 80, stdin);

    // -1 to avoid \n being added
    for (int i = 0; i < strlen(symbols)-1; i++) {
        arr_append(line, symbols[i]);
    }
}

void start_new_line(DynamicArray** lines, int* current_line) {
    if (*current_line == 19) {
        printf("You can't create more lines\n");
        return;
    }
    *current_line += 1;
    lines[*current_line] = (DynamicArray*)calloc(1, sizeof(DynamicArray));
    create_dynamic_array(lines[*current_line]);
    printf("%d\n", *current_line);
}

void load_file(DynamicArray* line) {
    FILE* pFile = fopen("text.txt", "r");

    char buffer[255];

    while (fgets(buffer, 255, pFile)) {
        for (int i = 0; i < strlen(buffer); i++) {
            arr_append(line, buffer[i]);
        }
    }

    fclose(pFile);

    printf("Text has been loaded successfully\n");
}

void save_in_file(DynamicArray* line) {
    FILE* pFile = fopen("text.txt", "w");

    if (pFile == nullptr) {
        printf("Error opening file!");
        return;
    }

    for (int i = 0; i < line->size; i++) {
        fprintf(pFile, "%c", line->array[i]);
    }

    arr_clear(line);

    fclose(pFile);

    printf("Text has been saved successfully\n");
}

void print_text(DynamicArray** lines, int current_line) {
    for (int i = 0; i <= current_line; i++) {
        DynamicArray* line = lines[i];
        for (int j = 0; j < line->size; j++) {
            printf("%c", line->array[j]);
        }
        printf("\n");
    }
}

void insert_by_index_and_line(DynamicArray** lines, int current_line) {
    int line_index;
    printf("Choose line:");
    scanf("%d", &line_index);

    fflush(stdin);

    if (line_index > current_line) {
        printf("This line has not been created\n");
        return;
    }

    int index;
    printf("Choose index:");
    scanf("%d", &index);

    fflush(stdin);

    char symbols[80];
    printf("Enter text to insert:");
    fgets(symbols, 80, stdin);

    fflush(stdin);

    for (int i = 0; i < strlen(symbols)-1; i++) {
        arr_insert(lines[line_index], symbols[i], index++);
    }
}

void search() {
    printf("This command is not implemented yet\n");
}

int main() {
    // for debug to work
    setbuf(stdout, 0);

    DynamicArray** lines = (DynamicArray**)calloc(20, sizeof(DynamicArray*));
    int current_line = -1;
    start_new_line(lines, &current_line);

    welcome();
    int command = get_command();
    while (command != 8) {
        switch (command) {
            case 1:
                append(lines[current_line]);
                break;
            case 2:
                start_new_line(lines, &current_line);
                break;
            case 3:
                load_file(lines[current_line]);
                break;
            case 4:
                save_in_file(lines[current_line]);
                break;
            case 5:
                print_text(lines, current_line);
                break;
            case 6:
                insert_by_index_and_line(lines, current_line);
                break;
            case 7:
                search();
                break;
            default:
                printf("No command with number %d\n", command);
                break;
        }
        command = get_command();
    }
}