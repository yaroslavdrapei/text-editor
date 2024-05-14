#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char value;
    struct Node* next;
} Node;

Node* create_node(char chr) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = chr;
    node->next = nullptr;
    return node;
}

void insert(Node* parentNode, char chr) {
    Node* node = create_node(chr);
    Node* current = parentNode;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = node;
}

Node* head;

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

    // strlen(symbols)-1 to avoid \n being added
    for (int i = 0; i < strlen(symbols)-1; i++) {
        if (head == nullptr) {
            head = create_node(symbols[i]);
            continue;
        }
        insert(head, symbols[i]);
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
            if (head == nullptr) {
                head = create_node(buffer[i]);
                continue;
            }
            insert(head, buffer[i]);
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

    Node* current = head;
    while (current != nullptr) {
        fprintf(pFile, "%c", current->value);
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    head = nullptr;

    fclose(pFile);

    printf("Text has been saved successfully\n");
}

void print_text() {
    Node* current = head;
    while (current != nullptr) {
        printf("%c", current->value);
        current = current->next;
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

    int idx = 0;
    Node* current = head;

    while (current != nullptr) {
        if (idx == index) {
            Node* prev = current->next;
            for (int i = 0; i < strlen(symbols) - 1; i++) {
                current->next = create_node(symbols[i]);
                current = current->next;
            }
            current->next = prev;
            break;
        }
        idx++;
        current = current->next;
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
    int command = get_command();
    while (command != 8) {
        parse_input(command);
        command = get_command();
    }
}