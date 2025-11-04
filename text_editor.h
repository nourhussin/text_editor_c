#include <stdio.h>
#include <stdlib.h>
#include "D:\Nour_Hussin\Career_Electronics\ITI 9 Months\C\Day2\MyLibrary.h"
#include <conio.h>
#include <string.h>

#define MaxLineSize   90
#define MaxRows       20
#define RowBias       4
#define ColBias       0

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
    for (int i = 0; i < MaxRows; i++)
        if(arr[i][0] == '\0')
            return i-1;
        return MaxRows;
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
    int current_row, current_col;

    if(back_color > 7) back_color = 0; // Convert to valid color
    if(text_color > 7) text_color = 7; // Convert to valid color
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
