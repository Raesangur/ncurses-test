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

    int width() const;
    int height() const;

    void set_color(short col_id);

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

    void refresh();


    static window create_centered(int width = 0, int height = 0);

public:
    WINDOW* win = nullptr;

protected:
    int h;
    int w;
};


#endif // WINDOW_H
/**
 * ------------------------------------------------------------------------------------------------
 * @}
 */
