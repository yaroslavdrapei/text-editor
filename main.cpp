#include <stdio.h>

void append()
{
  printf("This command is not implemented yet\n");
}

void start_new_line()
{
  printf("This command is not implemented yet\n");
}

void load_file()
{
  printf("This command is not implemented yet\n");
}

void save_in_file()
{
  printf("This command is not implemented yet\n");
}

void print_text()
{
  printf("This command is not implemented yet\n");
}

void insert_by_index()
{
  printf("This command is not implemented yet\n");
}

void search()
{
  printf("This command is not implemented yet\n");
}

void parse_input(int command)
{
  switch (command)
  {
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

int main()
{
  int command;
  do {
    printf("Choose command: ");
    scanf("%d", &command);  

    parse_input(command);
  } while (command != 8);

  return 0;
}