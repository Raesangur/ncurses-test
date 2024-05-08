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
#include "menu-manager.h"
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

void format_menu(window& win, const menu_top_entry* currentMenu)
{
    win.erase();
    win.box();

    win.print(0, currentMenu->get_name());

    for (int i = 0; currentMenu->begin() + i < currentMenu -> end(); i++)
    {
        const menu_entry* displayedMenu = currentMenu->get(i);
        if (displayedMenu->is_highlighted())
        {
            win.set_attribute(A_STANDOUT, true);
        }
        win.print(i + 2, 5, displayedMenu->display());
        win.set_attribute(A_STANDOUT, false);
    }
}


int handle_inputs(menu_manager* menus)
{
    int ch = getch();
    if (menus->size() < 1 || menus->top() == nullptr)
    {
        return -1;
    }

    menu_entry& currentMenu = *menus->top();

    switch(ch)
    {
        case 'q':
            return -1;

        case ' ':
            if (currentMenu.highlighted_entry()->can_select())
            {
                if (currentMenu.highlighted_entry()->is_selected())
                {
                    currentMenu.highlighted_entry()->deselect();
                }
                else
                {
                    currentMenu.highlighted_entry()->select();
                }
            }
            break;

        case '\n':
            if (currentMenu.highlighted_entry()->can_enter())
            {
                menu_entry* newMenu = currentMenu.highlighted_entry();
                if (newMenu != nullptr)
                {
                    menus->set_top(newMenu);
                }
            }
            break;

        case 0x1B:      // ESC
            if (menus->size() <= 1)
                return -1;
            else
                menus->pop();
            break;

        case KEY_UP:
            currentMenu.move_up();
            break;
            
        case KEY_DOWN:
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

    std::vector<std::unique_ptr<menu_entry>> menuVector;
    menuVector.push_back(std::make_unique<menu_top_entry>("Main Menu"));
    menuVector.push_back(std::make_unique<menu_option_entry>("Test1"));
    menuVector.push_back(std::make_unique<menu_option_entry>("Test2"));
    menuVector.push_back(std::make_unique<menu_option_entry>("Test3"));

    menu_top_entry* mainMenu = dynamic_cast<menu_top_entry*>(menuVector[0].get());
    mainMenu->add(menuVector[1].get());
    mainMenu->add(menuVector[2].get());
    // mainMenu->add(menuVector[3].get());

    menu_top_option_entry otherMenu{"chad menu"};
    otherMenu.add(menuVector[3].get());
    mainMenu->add(&otherMenu);

    // auto mainMenu = menuManager.add<menu_top_entry>("Main Menu")
    //     .add<menu_option_entry>("Test1")
    //     .add<menu_option_entry>("Test2")
    //     .add<menu_option_entry>("Test3")
    //     .add<menu_top_option_entry>("Chad Menu")
    //     .add<menu_option_entry>("Test 4")
    //     .finish()
    //     .add<menu_text_entry>("This cannot be selected!");
    
    menu_manager* mm = menu_manager::get();
    mm->add<menu_top_entry>("Main menu");

    while(true)
    {
        menu_top_entry* currentMenu = dynamic_cast<menu_top_entry*>(mm->top());
        format_menu(menuWin, currentMenu);

        if (handle_inputs(mm) == -1)
        {
            break;
        }
    }

    deinitialize_ncurses();
    return 0;
}


/**
 * ------------------------------------------------------------------------------------------------
 */
