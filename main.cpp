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
    win.scrollok();

    win.erase();
    win.box();

    auto [y, _] = win.get_max_yx();
    int maxItems = std::max(0, y - 4);

    int highlightedItem = 0;
    for(int i = 0; currentMenu->begin() + i < currentMenu->end(); i++)
    {
        if (currentMenu->get(i)->is_highlighted())
        {
            highlightedItem = i;
            break;
        }
    }

    int start = std::max(0, highlightedItem - maxItems + 4);
    int end = std::min(static_cast<int>(currentMenu->size()), start + maxItems);

    win.print(0, currentMenu->get_name());

    for (int i = start; i < end; i++)
    {
        const menu_entry* displayedMenu = currentMenu->get(i);
        if (displayedMenu->is_highlighted())
        {
            win.set_attribute(A_STANDOUT, true);
        }
        win.print(i + 2 - start, 5, displayedMenu->display());
        win.set_attribute(A_STANDOUT, false);
    }

    if (static_cast<int>(currentMenu->size()) >= maxItems)
    {
        win.print(win.height() - 3, 2, "|");
        win.print(win.height() - 2, 2, "v");
    }
}


int handle_inputs(menu_manager* menus)
{
    constexpr int ESC = 0x1B;

    int ch = getch();
    if (menus->size() < 1 || menus->top() == nullptr)
    {
        return -1;
    }

    menu_entry& currentMenu = *menus->top();
    bool inputRestriction = currentMenu.has_input_field();

    if (!inputRestriction)
    {
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

            case ESC:
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
    }
    else
    {
        // Return to old menu on ESC or ENTER
        if (ch == ESC || ch == '\n')
        {
            menus->pop();
            return 0;
        }
        currentMenu.input_character(ch);
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

    menu_manager* mm = menu_manager::get();
    mm->add<menu_top_entry>("Main Menu")
        ->add<menu_top_option_entry>("Setup git")
            ->add<menu_option_entry>("Configure ssh key for authentication")
            ->add<menu_option_entry>("Configure ssh key for signing")
            ->finish()
        ->add<menu_top_option_entry>("Setup zsh")
            ->add<menu_option_entry>("Install zsh")
            ->add<menu_option_entry>("Download zsh configuration")
            ->finish()
        ->add<menu_top_option_entry>("Setup neofetch")
            ->add<menu_option_entry>("Install neofetch")
            ->add<menu_option_entry>("Download neofetch configuration")
            ->finish()
        ->add<menu_top_option_entry>("Setup btop")
            ->add<menu_option_entry>("Install btop")
            ->add<menu_option_entry>("Download btop configuration")
            ->finish()
        ->add<menu_top_option_entry>("Setup kde")
            ->add<menu_option_entry>("Install kde")
            ->add<menu_option_entry>("Download kde configuration")
            ->finish()
        ->add<menu_top_option_entry>("Setup micro")
            ->add<menu_option_entry>("Install micro")
            ->add<menu_option_entry>("Download micro configuration")
            ->finish()
        ->add<menu_top_option_entry>("Setup python")
            ->add<menu_option_entry>("Install python")
            ->add<menu_option_entry>("Install pip")
            ->add<menu_option_entry>("Create alternative link to python3")
            ->finish()
        ->add<menu_top_entry>("Install packages")
            ->add<menu_top_option_entry>("C++ development")
                ->add_file<menu_option_entry>("packages/cpp-dev.txt")
                ->finish()
            ->finish()
        ;

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
