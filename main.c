#include "text_editor.h"

int main()
{
    int row = RowBias, col = ColBias, out_of_text = 0, out_of_program = 0 , mode, display_option, text_color=0, back_color=7;
    char char_arr[MaxRows][MaxLineSize] = {{'\0'}}, filename[100], ctrl;
do{
    mode = print_main_menu();
    switch(mode)
    {

//---------------------------------------- First Mode ---------------------------------------------------------------\\

        case 0: // NEW
            out_of_text = 0;
            print_char_window(char_arr, RowBias, ColBias, back_color, text_color);
            gotoxy(col,row);

        do{
        ctrl = getch();
        switch(ctrl)
        {
            case -32: // Extended key
            case 0:
                ctrl = getch();
                switch(ctrl)
                {
                    case 73: //PageUp
                        row = RowBias;
                        col = ColBias;
                        gotoxy(col,row);
                        break;

                    case 81: //PageDown
                        row = RowBias + last_row(char_arr);
                        col = ColBias + last_col(char_arr[row-RowBias]);
                        gotoxy(col,row);
                        break;

                    case 72: // Up Arrow
                        row --;
                        if (row < RowBias) row = RowBias;

                        if (col > ColBias + last_col(char_arr[row-RowBias]))
                            col = ColBias + last_col(char_arr[row-RowBias]);

                        gotoxy(col,row);
                        break;

                    case 80: // Down Arrow
                        row ++;
                        if (row > RowBias + last_row(char_arr))
                            row = RowBias + last_row(char_arr);

                        if (col > ColBias + last_col(char_arr[row-RowBias]))
                            col = ColBias + last_col(char_arr[row-RowBias]);

                        gotoxy(col,row);
                        break;

                    case 77: // Right Arrow
                        col ++;
                        if (col > ColBias + strlen(char_arr[row-RowBias]))
                        {
                            col = ColBias;
                            row ++;
                            if (row > RowBias + last_row(char_arr))
                            {
                                row = RowBias + last_row(char_arr);
                                col = ColBias + strlen(char_arr[row-RowBias]);
                            }

                        }
                        gotoxy(col,row);
                        break;

                    case 75: // Left Arrow
                        col --;
                        if (col<ColBias)
                        {
                            row --;
                            if (row < RowBias)
                            {
                                row = RowBias;
                                col = ColBias;
                            }
                            else
                                col = ColBias + strlen(char_arr[row-RowBias]);
                        }
                        gotoxy(col,row);
                        break;

                    case 71: // Home Key
                        col = ColBias;
                        gotoxy(col,row);
                        break;

                    case 79: // End Key
                        col = ColBias + last_col(char_arr[row-RowBias]);
                        gotoxy(col,row);
                        break;

                    case 83: // Delete Key
                        delete_char(char_arr[row-RowBias], col-ColBias);
                        gotoxy(ColBias,row); printf("%s", char_arr[row-RowBias]);for(int i = 0; i<(MaxLineSize-strlen(char_arr[row-RowBias])); i++) {printf(" ");} gotoxy(col,row);
                        break;
                    case 82: // Insert Key
                        insert_char(char_arr[row-RowBias],getch(),col-ColBias);
                        gotoxy(ColBias,row); printf("%s", char_arr[row-RowBias]);for(int i = 0; i<(MaxLineSize-strlen(char_arr[row-RowBias])); i++) {printf(" ");} gotoxy(col,row);
                        break;
                }
                break;

            case  8: // Backspace Key
                    delete_char(char_arr[row-RowBias], col - ColBias -1);
                    col --;
                    if (col<ColBias) col = ColBias;
                    gotoxy(ColBias,row); printf("%s", char_arr[row-RowBias]); for(int i = 0; i<(MaxLineSize-strlen(char_arr[row-RowBias])); i++) {printf(" ");} gotoxy(col,row);
                    break;

            case 13: // Enter key
                row ++;
                col = ColBias;
                if (row > RowBias + MaxRows) row = RowBias + MaxRows;
                gotoxy(col,row);
                break;

            case 27: // Escape key or Tab
            case 9:
                out_of_text = 1;
                textattr(0x07);
                break;

            default:
                if (col >= ColBias + MaxLineSize)
                {
                    col = ColBias;
                    row ++;
                }
                if (row >= RowBias + MaxRows)
                    row = RowBias + MaxRows;
                char_arr[row-RowBias][col-ColBias] = ctrl;
                gotoxy(col,row); printf("%c",ctrl);
                col ++;

        }

    } while(out_of_text == 0);

            break;

//---------------------------------------- Second Mode ---------------------------------------------------------------\\

        case 1: // DISPLAY
            textattr(0x60);
            printf("\n\nWanna Display:\n1.Current Text\n2.Open File\n");
            scanf("%d",&display_option);
            if(display_option == 2)
            {
                printf("Enter file name: ");
                scanf("%99s", filename);

                FILE *fp = fopen(filename, "r");
                if (!fp)
                {
                    printf("File not found. Creating a new file: %s\n", filename);
                    fp = fopen(filename, "w"); // create new empty file
                    fclose(fp);
                    
                }

                int row = 0;
                while (row < MaxRows && fgets(char_arr[row], MaxLineSize, fp))
                {
                    // Remove newline if exists
                    char_arr[row][strcspn(char_arr[row], "\n")] = '\0';
                    row++;
                }

                fclose(fp);
                print_char_array(char_arr, RowBias, 0);
            }


            else
                print_char_array(char_arr, RowBias, 0);
            getch();
            textattr(0x07);
            break;

//---------------------------------------- Third Mode ----------------------------------------------------------------\\

        case 2: //SAVE
            printf("\n\nEnter file name to save (e.g. output.txt): ");
            scanf("%99s", filename);

            FILE *fp = fopen(filename, "w");
            for (int i = 0; i < MaxRows; i++)
                if (strlen(char_arr[i]) > 0)
                    fprintf(fp, "%s\n", char_arr[i]);
            fclose(fp);
            printf("File Saved\n");
            getch();
            break;

//---------------------------------------- Fourth Mode ---------------------------------------------------------------\\

        case 3: // COLOR
            printf("\n\n\n");
            for(int i = 0; i < 8; i++)
            {
                printf("%d | ", i);
                textattr((i << 4));
                printf("     \n");
                textattr(0x07);
            }
            printf("\nEnter background color number (0-7): ");
            scanf("%d", &back_color);
            printf("Enter text color number (0-7): ");
            scanf("%d", &text_color);
            getch();
            break;

//---------------------------------------- Fifth Mode ----------------------------------------------------------------\\

        case 4: // EXIT
            clrscr();
            out_of_program = 1;
            break;
    }
} while(out_of_program == 0);

    return 0;
}
