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
#include "window.h"

#include <ncurses.h>

#include <menu.h>

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

 bool check_terminal_color_support()
 {
    bool colors = has_colors();

    if (!colors)
    {
        printw("Terminal does not support colors!");
        getch();
    }

    return colors;
 }


 /** ===============================================================================================
  *  FUNCTION DEFINITIONS
  */

int main() {
    initialize_ncurses();
    check_terminal_color_support();

    window mainWin = window::create_centered();

    getch();

    deinitialize_ncurses();
    return 0;
}



/**
 * ------------------------------------------------------------------------------------------------
 * @}
 */