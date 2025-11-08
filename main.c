#include "text_editor.h"

int main()
{
//------------------------------------------ Variables --------------------------------------------------------
    int row = RowBias, col = ColBias;
    int out_of_text = 0, out_of_program = 0 ;
    int mode, display_option, color_option;
    int text_color = 0, back_color = 7;
    char char_arr[MaxRows][MaxLineSize] = {{'\0'}};
    char filename[100]={'\0'};
    char ctrl;

    do{
        mode = print_main_menu();
        switch(mode){
//---------------------------------------- First Mode ---------------------------------------------------------------
        case 0: // NEW

            run_edit_mode(char_arr, &back_color, &text_color);
            break;
            
//---------------------------------------- Second Mode --------------------------------------------------------------
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

//---------------------------------------- Third Mode ----------------------------------------------------------------
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

//---------------------------------------- Fourth Mode ---------------------------------------------------------------
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

//---------------------------------------- Fifth Mode ----------------------------------------------------------------
        case 4: // EXIT
            clrscr();
            out_of_program = 1;
            break;
        }
    } while(out_of_program == 0);
return 0;
}