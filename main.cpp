/**
 * ===============================================================================================
 * @file    main.cpp
 * @author  Pascal-Emmanuel Lachance
 * @p       <a href="https://www.github.com/Raesangur">Raesangur</a>
 * @p       <a href="https://www.raesangur.com/">https://www.raesangur.com/</a>
 *
 * @brief   A quick test of ncurses features in C++ to make TUI.
 *          Just a small test sample project to learn about the library before using it for more!
 *
 * ------------------------------------------------------------------------------------------------
 * @copyright Copyright (c) 2023 Pascal-Emmanuel Lachance | Raesangur
 *
 * @par License: <a href="https://opensource.org/license/mit/"> MIT </a>
 *               This project is released under the MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON INFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * ------------------------------------------------------------------------------------------------
 * @details
 * I am currently following this tutorial:
 * https://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5
 * ===============================================================================================
 */

/** ===============================================================================================
 *  INCLUDES
 */
#include <ncurses.h>

#include <menu.h>

#include <stdlib.h>
#include <string.h>


 /** ===============================================================================================
  *  FUNCTION DEFINITIONS
  */

int main() {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // Initialize colors
    if(has_colors() == FALSE)
    {	endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);

    // Set up menu items
    const char* menu_items[] = {"Option 1", "Option 2", "Option 3", "Quit"};
    int num_items = sizeof(menu_items) / sizeof(menu_items[0]);
    int current_item = 0;

    // Get screen dimensions
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // Define window dimensions
    int win_width = 30;
    int win_height = num_items + 4; // 4 is for padding

    // Calculate window position
    int win_x = (max_x - win_width) / 2;
    int win_y = (max_y - win_height) / 2;

    // Create window
    WINDOW* menu_win = newwin(win_height, win_width, win_y, win_x);

    wbkgd(menu_win, COLOR_PAIR(1));

    // Display menu
    int key;
    do {
        /*
        for (int i = 0; i < num_items; i++) {
            if (i == current_item) {
                attron(A_REVERSE);
            }
            printw("%s\n", menu_items[i]);
            attroff(A_REVERSE);
        }
        */
        box(menu_win, 0, 0);
        for (int i = 0; i < num_items; i++) {
            if (i == current_item) {
                wattron(menu_win, A_REVERSE);
            }
            mvwprintw(menu_win, i + 2, 2, "%s", menu_items[i]);
            wattroff(menu_win, A_REVERSE);
        }

        wrefresh(menu_win);

        key = getch();

        switch (key) {
            case KEY_UP:
                current_item--;
                if (current_item < 0) {
                    current_item = num_items - 1;
                }
                break;
            case KEY_DOWN:
                current_item++;
                if (current_item >= num_items) {
                    current_item = 0;
                }
                break;
            default:
                break;
        }

    } while (key != '\n' && key != 'q');

    // Process selection
    if (key == '\n') {
        clear();
        printw("You selected: %s\n", menu_items[current_item]);
        refresh();
        getch();
    }

    // Cleanup ncurses
    endwin();

    return 0;
}



/**
 * ------------------------------------------------------------------------------------------------
 * @}
 */