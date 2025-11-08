#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

#define MaxLineSize   90
#define MaxRows       20
#define RowBias       4
#define ColBias       0

// Cursor and console handling
void gotoxy(int x, int y);
void clrscr(void);
void textattr(int ForgC);
void SetColor(int ForgC);

// Text operations
void delete_char(char *char_array, int index);
void insert_char(char *char_array, char ch, int index);
int last_row(char arr[MaxRows][MaxLineSize]);
int last_col(char arr[MaxLineSize]);

// Printing
void print_char_array(char arr[MaxRows][MaxLineSize], int row_bias, int col_bias);
void print_char_window(char arr[MaxRows][MaxLineSize], int row_bias, int col_bias, int back_color, int text_color);

int print_main_menu(void);
void run_edit_mode(char char_arr[MaxRows][MaxLineSize], int *back_color, int *text_color, int row,int col);

#endif





void gotoxy(int x, int y)
{
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

void clrscr()
{
    system("cls");
}

void textattr(int ForgC)
{
    //system("COLOR ForgC"); //system("COLOR FC");
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, ForgC);
}

void SetColor(int ForgC)
{
     WORD wColor;
     //This handle is needed to get the current background attribute

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //csbi is used for wAttributes word

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //To mask out all but the background attribute, and to add the color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

void delete_char(char *char_array, int index)
{
    int i = index;
    while (char_array[i] != '\0')
    {
        char_array[i] = char_array[i + 1];
        i++;
    }
}

void insert_char(char *char_array, char ch, int index)
{
    int null_ter = 0;

    // Get the index of the null terminator
    while(char_array[null_ter] != '\0') null_ter++;

    for(int j = null_ter; j >= index; j--)
        char_array[j + 1] = char_array[j];

    char_array[index] = ch;
}

int last_row(char arr[MaxRows][MaxLineSize])
{
    int last = -1;
    for (int i = 0; i < MaxRows; i++)
    {
        if (arr[i][0] != '\0')
            last = i;
    }
    return (last == -1) ? 0 : last;
}

int last_col(char arr[MaxLineSize])
{
    for (int i = 0; i < MaxLineSize; i++)
        if(arr[i] == '\0')
            return i;
        return MaxLineSize;
}

void print_char_array(char arr[MaxRows][MaxLineSize], int row_bias, int col_bias) {
    for (int i = 0; i < MaxRows; i++)
    {
        gotoxy(col_bias, row_bias + i);
        for (int j = 0; j < MaxLineSize; j++)
        {
            if (arr[i][j] == '\0')
                putchar(' ');
            else
                putchar(arr[i][j]);
        }
    }
}


void print_char_window(char arr[MaxRows][MaxLineSize],int row_bias, int col_bias, int back_color, int text_color)
{
    if(back_color > 7) back_color = 0; // Convert to valid color
    if(text_color > 15) text_color = 7; // Convert to valid color
    textattr(((back_color & 0xF) << 4) | (text_color & 0xF));

    for (int i = 0; i < MaxRows; i++)
    {
        gotoxy(col_bias, row_bias + i);
        for (int j = 0; j < MaxLineSize; j++)
        {
            if (arr[i][j] == '\0')
                putchar(' ');
            else
                putchar(arr[i][j]);
        }
    }
    gotoxy(ColBias, RowBias);
}

int print_main_menu()
{
    int current_option = 0, out=0;
    char menu[5][8] = {"NEW", "DISPLAY", "SAVE", "COLOR", "EXIT"};
    char ctrl;

    clrscr();gotoxy(ColBias+38,0); printf("Main Menu");

    do{
        for(int i=0; i<5; i++)
        {
            if(i == 4) textattr(0x40);
            else if(i == current_option) textattr(0x70);
            else textattr(0x07);

            gotoxy(ColBias+20*i,2); printf("%s", menu[i]);
        }
        gotoxy(ColBias+20*current_option,2);
        textattr(0x07);
        ctrl = getch();
        switch(ctrl)
        {
            case 13: // Enter key
                textattr(0x20);
                gotoxy(ColBias+20*current_option,2);
                printf("%s", menu[current_option]);
                out = 1;
                break;
            case 9: //TAB
                current_option++;
                if(current_option>4)
                    current_option = 0;
                gotoxy(ColBias+20*current_option,2);

        }

    } while(out == 0);
    textattr(0x07);
    return current_option;
}

void run_edit_mode(char char_arr[MaxRows][MaxLineSize], int *back_color, int *text_color, int row,int col)
{
    int out_of_text = 0;
    int insert_flag = 1;
    char ctrl;

    print_char_window(char_arr, RowBias, ColBias, *back_color, *text_color);
    gotoxy(col, row);

    do {
        ctrl = getch();
        switch (ctrl)
        {
            case -32: // extended key
            case 0:
                ctrl = getch();
                switch (ctrl)
                {
                    case 73: // PageUp
                        row = RowBias;
                        col = ColBias;
                        break;

                    case 81: // PageDown
                        row = RowBias + last_row(char_arr);
                        col = ColBias + last_col(char_arr[row - RowBias]);
                        break;

                    case 72: // Up
                        row--;
                        if (row < RowBias) row = RowBias;
                        if (col > ColBias + last_col(char_arr[row - RowBias]))
                            col = ColBias + last_col(char_arr[row - RowBias]);
                        break;

                    case 80: // Down
                        row++;
                        if (row > RowBias + last_row(char_arr))
                            row = RowBias + last_row(char_arr);
                        if (col > ColBias + last_col(char_arr[row - RowBias]))
                            col = ColBias + last_col(char_arr[row - RowBias]);
                        break;

                    case 77: // Right
                        col++;
                        if (col > ColBias + strlen(char_arr[row - RowBias]))
                        {
                            col = ColBias;
                            row++;
                            if (row > RowBias + last_row(char_arr))
                            {
                                row = RowBias + last_row(char_arr);
                                col = ColBias + strlen(char_arr[row - RowBias]);
                            }
                        }
                        break;

                    case 75: // Left
                        col--;
                        if (col < ColBias)
                        {
                            row--;
                            if (row < RowBias)
                            {
                                row = RowBias;
                                col = ColBias;
                            }
                            else
                                col = ColBias + strlen(char_arr[row - RowBias]);
                        }
                        break;

                    case 71: // Home
                        col = ColBias;
                        break;

                    case 79: // End
                        col = ColBias + last_col(char_arr[row - RowBias]);
                        break;

                    case 83: // Delete
                        delete_char(char_arr[row - RowBias], col - ColBias);
                        gotoxy(ColBias, row);
                        printf("%-*s", MaxLineSize, char_arr[row - RowBias]);
                        break;

                    case 82: // Insert
                        insert_flag = !insert_flag;
                        break;
                }
                break;

            case 8: // Backspace
                delete_char(char_arr[row - RowBias], col - ColBias - 1);
                col--;
                if (col < ColBias)
                {
                    row--;
                    if (row < RowBias)
                    {
                        row = RowBias;
                        col = ColBias;
                    }
                    else
                        col = ColBias + strlen(char_arr[row - RowBias]);
                }
                gotoxy(ColBias, row);
                printf("%-*s", MaxLineSize, char_arr[row - RowBias]);
                break;

            case 13: // Enter
                row++;
                col = ColBias;
                if (row > RowBias + MaxRows - 1)
                    row = RowBias + MaxRows - 1;
                break;

            case 27: // ESC
            case 9:  // TAB
                out_of_text = 1;
                textattr(0x07);
                break;

            default: // Normal characters
                if (col >= ColBias + MaxLineSize)
                {
                    col = ColBias;
                    row++;
                }
                if (row >= RowBias + MaxRows)
                    row = RowBias + MaxRows - 1;

                if (insert_flag)
                {
                    insert_char(char_arr[row - RowBias], ctrl, col - ColBias); 
                    gotoxy(ColBias, row); printf("%-*s", MaxLineSize, char_arr[row - RowBias]);
                }
                else
                {
                    char_arr[row - RowBias][col - ColBias] = ctrl;
                    gotoxy(col, row); putchar(ctrl); 
                }
                col++;
        }

        gotoxy(col, row);

    } while (out_of_text == 0);
}

int menu(const char *options[], int n_options, int start_x, int start_y, int highlight_color, int normal_color)
{
    int current_option = 0;
    int out = 0;
    char ctrl;

    do {
        
        for (int i = 0; i < n_options; i++)
        {
            gotoxy(start_x, start_y + i);
            if (i == current_option)
            {
                textattr(highlight_color);
                printf("-> %s", options[i]);
            }
            else
            {
                textattr(normal_color);
                printf("   %s", options[i]);
            }
        }
        gotoxy(start_x, start_y + current_option);
        textattr(normal_color);

        ctrl = getch();
        switch(ctrl)
        {
            case -32:
            case 0:  // extended keys
                ctrl = getch();
                switch(ctrl)
                {
                    case 72: // Up arrow
                        current_option--;
                        if (current_option < 0)
                            current_option = n_options - 1;
                        break;

                    case 80: // Down arrow
                        current_option++;
                        if (current_option >= n_options)
                            current_option = 0;
                        break;
                }
                break;

            case 13: // Enter
                textattr(0x20);
                gotoxy(start_x, start_y + current_option);
                printf("-> %s", options[current_option]);
                out = 1;
                break;
        }

    } while (!out);

    textattr(normal_color);
    return current_option;
}

int color_menu(int is_background) {

    int current_option = 0;
    int out = 0;
    char ctrl;

    int start_x = ColBias+ 60;
    int start_y = 6;

    if(is_background)
        gotoxy(start_x, start_y - 2), printf("Background Color:");
    else
        gotoxy(start_x, start_y - 2), printf("Text Color:      ");

    int n_options = is_background ? 8 : 16;

    do {
        for (int i = 0; i < n_options; i++) {
            gotoxy(start_x+2, start_y + i);
            int color_code = is_background ? (i << 4) : i;
            textattr(color_code);

            if(is_background)
                printf("    "); 
            else
                printf(" AAA");
        }
        textattr(0x07);
        for (int i = 0; i < n_options; i++)
        {
            gotoxy(start_x, start_y + i);
            if (i == current_option)
                printf("->");
            else
                printf("  ");
        }
        gotoxy(start_x, start_y + current_option);

        ctrl = getch();
        switch(ctrl) {
            case -32: case 0:
                ctrl = getch();
                switch(ctrl) {
                    case 72: // Up
                        current_option--;
                        if(current_option < 0) current_option = n_options - 1;
                        break;
                    case 80: // Down
                        current_option++;
                        if(current_option >= n_options) current_option = 0;
                        break;
                }
                break;
            case 13: // Enter
                out = 1;
                break;
        }

    } while(!out);

    textattr(0x07);
    return current_option;
}