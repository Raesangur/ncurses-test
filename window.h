/**
 * ===============================================================================================
 * @file    window.h
 * @author  Pascal-Emmanuel Lachance
 * @p       <a href="https://www.github.com/Raesangur">Raesangur</a>
 *
 * @brief   A wrapper class around a ncurses windows.
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
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * ===============================================================================================
 */
#ifndef WINDOW_H
#define WINDOW_H


/** ===============================================================================================
 *  INCLUDES
 */
#include <ncurses.h>

#include <string>


/** ===============================================================================================
 *  CLASS DEFINITION
 */

class window
{
public:
    window(int h, int w, int y, int x);

    void box();

    void print(const std::string& message);
    void print(int y, int x, const std::string& message);

    template<typename... args>
    void print(const std::string& format, args... va);

    template<typename... args>
    void print(int y, int x, const std::string& format, args... va);

    void refresh();


    static window create_centered(int width = 0, int height = 0);

protected:
    WINDOW* win = nullptr;
};


/** ===============================================================================================
 *  MEMBER FUNCTIONS DEFINITION
 */
window::window(int h, int w, int y, int x)
{
    win = ::newwin(h, w, y, x);
    ::refresh();
}

void window::box()
{
    ::box(win, 0, 0);
    refresh();
}

void window::print(const std::string& message)
{
    wprintw(win, "%s", message.c_str());
    refresh();
}

void window::print(int y, int x, const std::string& message)
{
    mvwprintw(win, y, x, "%s", message.c_str());
    refresh();
}

template<typename... args>
void window::print(const std::string& format, args... va)
{
    wprintw(win, format.c_str(), va...);
    refresh();
}

template<typename... args>
void window::print(int y, int x, const std::string& format, args... va)
{
    mvwprintw(win, y, x, format.c_str(), va...);
    refresh();
}


void window::refresh()
{
    ::wrefresh(win);
}


window window::create_centered(int width, int height)
{
    constexpr double scaling_factor = 0.75;

    int maxy = 0;
    int maxx = 0;
    getmaxyx(stdscr, maxy, maxx);

    if (width == 0 && height == 0)
    {
        width  = static_cast<int>(scaling_factor * maxx);
        height = static_cast<int>(scaling_factor * maxy);
    }

    window mainWin{height, width, std::max((maxy - height) / 2, 0), std::max((maxx - width) / 2, 0)};
    mainWin.box();
    mainWin.print(1, 1, "X: %d \t Y: %d", maxx, maxy);

    return mainWin;
}


#endif // WINDOW_H
/**
 * ------------------------------------------------------------------------------------------------
 * @}
 */