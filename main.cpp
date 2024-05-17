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
    dynamicArray->array = (char*)malloc(dynamicArray->capacity*sizeof(char));
    dynamicArray->array[0] = '\0';
    dynamicArray->size = 0;
}

void arr_resize(DynamicArray* dynamicArray) {
    dynamicArray->capacity *= 2;
    dynamicArray->array = (char*)realloc(dynamicArray->array, dynamicArray->capacity);
}

void arr_append(DynamicArray* dynamicArray, char chr) {
    // +1 for \0 char
    if (dynamicArray->size+1 > dynamicArray->capacity) {
        arr_resize(dynamicArray);
    }

    dynamicArray->array[dynamicArray->size] = chr;
    dynamicArray->size++;
    dynamicArray->array[dynamicArray->size] = '\0';
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
    create_dynamic_array(dynamicArray);
}

void arr2d_clear(DynamicArray** d2DynamicArray, int* current_line) {
    for (int i = 0; i <= *current_line; i++) {
        arr_clear(d2DynamicArray[i]);
    }

    *current_line = -1;
}

void get_substring(int start, int length, char string[], char* result) {
    for (int i = start; i < start+length; i++) {
        result[i-start] = string[i];
    }
    result[length] = '\0';
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
    lines[*current_line] = (DynamicArray*)malloc(sizeof(DynamicArray));
    create_dynamic_array(lines[*current_line]);
}

void load_file(DynamicArray** lines, int* current_line) {
    char path[80];
    printf("Enter the file name for loading:");
    fgets(path, 80, stdin);

    path[strlen(path)-1] = '\0';
    fflush(stdin);

    FILE* file = fopen(path, "r");

    if (file == nullptr) {
        printf("Error opening file!\n");
        return;
    }

    char buffer[255];

    arr2d_clear(lines, current_line);
    start_new_line(lines, current_line);

    DynamicArray* line = lines[*current_line];
    while (fgets(buffer, 255, file)) {
        for (int j = 0; j < strlen(buffer); j++) {
            if (buffer[j] == '\n') {
                start_new_line(lines, current_line);
                line = lines[*current_line];
                continue;
            }
            arr_append(line, buffer[j]);
        }
    }

    fclose(file);

    printf("Text has been loaded successfully\n");
}

void save_in_file(DynamicArray** lines, int* current_line) {
    char path[80];
    printf("Enter the file name for saving:");
    fgets(path, 80, stdin);

    path[strlen(path)-1] = '\0';
    fflush(stdin);

    FILE* file = fopen(path, "w");

    if (file == nullptr) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i <= *current_line; i++) {
        DynamicArray* line = lines[i];
        for (int j = 0; j < line->size; j++) {
            fprintf(file, "%c", line->array[j]);
        }

        // prevent extra new line
        if (i == *current_line) continue;
        fprintf(file, "%c", '\n');
    }

    fclose(file);

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

void search(DynamicArray** lines, int current_line) {
    char target_substr[80];
    printf("Enter text to search:");
    fgets(target_substr, 80, stdin);

    target_substr[strlen(target_substr)-1] = '\0';
    fflush(stdin);


    bool wasFound = false;

    for (int i = 0; i <= current_line; i++) {
        DynamicArray* line = lines[i];

        for (int j = 0; j < line->size; j++) {
            char substr[strlen(target_substr)];

            get_substring(j, strlen(target_substr), line->array, substr);

            if (!strcmp(substr, target_substr)) {
                if (!wasFound) {
                    printf("Text is present in following positions:\n");
                    wasFound = true;
                }
                printf("%d %d\n", i, j);
            }
        }
    }

    if (!wasFound) {
        printf("\"%s\" was not found\n", target_substr);
    }
}

int main() {
    // for debug to work
    setbuf(stdout, 0);
    DynamicArray** lines = (DynamicArray**)malloc(20*sizeof(DynamicArray*));
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
                printf("New line is started\n");
                break;
            case 3:
                load_file(lines, &current_line);
                break;
            case 4:
                save_in_file(lines, &current_line);
                break;
            case 5:
                print_text(lines, current_line);
                break;
            case 6:
                insert_by_index_and_line(lines, current_line);
                break;
            case 7:
                search(lines, current_line);
                break;
            default:
                printf("No command with number %d\n", command);
                break;
        }
        command = get_command();
    }
}