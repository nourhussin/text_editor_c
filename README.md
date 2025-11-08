# Text Editor

This project is a simple terminal-based Text Editor implemented in C. It
supports basic editing features similar to a minimal Notepad. The
program provides a menu system to create, view, edit, and save text
files, with options to change text and background colors.

## Main Menu Features

1. NEW : 

        - Start a new editing session from scratch.

2. DISPLAY : 

        - View current edited text
        - Open and display an existing file
        - If the file does not exist, it is automatically created

3. SAVE : 

        - Save current text buffer to a file. 
        - The user enters the file name manually

4. COLOR :

        - Choose text and background colors.

5. EXIT :

        - Exit the program.


**Tab key**: Navigate between menu options.



## Text Editing Mode

The editor supports text navigation, insertion, and deletion using the
keyboard.

### Controls

| Key                   |  Function
|---------------        | --------------------------------------------------------
| Home                  | Move cursor to the first character of the current line
| End                   | Move cursor to the last character of the current line
| Page Up               | Move cursor to the first character in the text
| Page Down             | Move cursor to the last character in the text
| Arrow Keys   | Navigate characters and lines
| Delete       | Delete the current character
| Backspace    | Delete the previous character
| Insert       | Insert a character
| Enter        | Insert new line and move cursor down
| Esc          | Exit editing mode and return to display mode


## Bugs & Features to be improved

- [X] Separate NEW editor mode from DISPLAY editor mode.
- [X] DISPLAY window must go to last character.
- [X] NEW window must open a blank page whatever happened before.
- [X] Backspace Key must go to previous line in case being in first col.
- [X] Insert Mode using a flag not just char by char.
- [X] Menu for each options inside any window with the right spacing.
- [ ] Enter Key in the middle of line must move the next part of the line.
