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
#include <tuple>


/** ===============================================================================================
 *  CLASS DEFINITION
 */

class window
{
public:
    window(int h, int w, int y, int x);

    [[nodiscard]] int width() const;
    [[nodiscard]] int height() const;
    [[nodiscard]] std::tuple<int, int> get_yx() const;
    [[nodiscard]] std::tuple<int, int> get_max_yx() const;

    void set_color(short col_id);
    void set_attribute(int attrs, bool activated);
    void scrollok(bool activated = true);

    void box();
    void line(int n);

    void print(const std::string& message);
    void print(int y, int x, const std::string& message);
    void print(int y, const std::string& message);

    template<typename... args>
    void print(const std::string& format, args... va);

    template<typename... args>
    void print(int y, int x, const std::string& format, args... va);

    template<typename... args>
    void print(int y, const std::string& format, args... va);

    void erase();
    void refresh();


    static window create_centered(int width = 0, int height = 0);

public:
    WINDOW* win = nullptr;

protected:
    int h;
    int w;
};


/** ===============================================================================================
 *  MEMBER FUNCTIONS DEFINITIONS
 */

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

template<typename... args>
void window::print(int y, const std::string& format, args... va)
{
    // snprintf to NULL with length 0 is defined behavior and returns the number of characters that
    // would have been written.
    int len = std::snprintf(nullptr, 0, format.c_str(), va...);

    int x = std::max((width() - len) / 2, 0);

    return print(y, x, format, va...);
}


#endif // WINDOW_H
/**
 * ------------------------------------------------------------------------------------------------
 */
