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
#include "colors.h"
#include "menu.h"
#include "window.h"

#include <ncurses.h>

#include <menu.h>

#include <stack>
#include <stdlib.h>
#include <string.h>


/** ===============================================================================================
 *  FUNCTION DECLARATIONS
 */
void initialize_ncurses()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
}

void deinitialize_ncurses()
{
    endwin();
}


void format_main(window& win)
{
    attron(A_BOLD);

    win.print(0, {"Bon matin"});

    wmove(win.win, 1, 1);
    win.line(win.width() - 2);
    attroff(A_BOLD);

    win.print(win.height() - 3, {"Press 'q' to quit."});
    win.print(win.height() - 2, {"Arrow keys to navigate the menu. Press 'ENTER' to enter submenu."});
    win.print(win.height() - 1, {"Press 'ESC' to exit menu. Press 'SPACE' to select an option."});
}

void format_menu(window& win, menu& currentMenu)
{
    static int counter = 0;
    win.erase();
    win.box();

    win.print({"%d"}, counter++);
}


int handle_inputs(window& menuWin, std::stack<menu*>& menus)
{
    int ch = getch();
    if (menus.size() < 1)
    {
        return -1;
    }

    menu& currentMenu = *menus.top();

    switch(ch)
    {
        case 'q':
            return -1;

        case ' ':   // SPACE
            if (currentMenu.selected()->can_highlight())
            {
                currentMenu.selected()->highlight();
            }
            break;
        case KEY_ENTER:      // ENTER
            if (currentMenu.selected()->can_enter())
            {
                menus.emplace(currentMenu.selected());
            }
            break;
        case 0x1B:      // ESC
            if (menus.size() <= 1)
                return -1;
            else
                menus.pop();
            break;
        case KEY_UP:
            menuWin.print("UP");
                currentMenu.move_up();
            break;
        case KEY_DOWN:
            menuWin.print("DOWN");
                currentMenu.move_down();
            break;

        default:
            return 0;
    }

    return 0;
}


/** ===============================================================================================
 *  FUNCTION DEFINITIONS
 */

int main() {
    initialize_ncurses();

    window mainWin = window::create_centered(-1, -1);
    window menuWin = window::create_centered();

    if (enable_colors())
    {
        configure_background_colors();
        mainWin.set_color(1);
        menuWin.set_color(2);
    }

    format_main(mainWin);

    std::stack<menu*> menus;
    while(true)
    {
        if (handle_inputs(menuWin, menus) == -1)
        {
            break;
        }

        format_menu(menuWin, *menus.top());
    }

    deinitialize_ncurses();
    return 0;
}


/**
 * ------------------------------------------------------------------------------------------------
 */
