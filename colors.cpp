/**
 * ===============================================================================================
 * @file    colors.cpp
 * @author  Pascal-Emmanuel Lachance
 * @p       <a href="https://www.github.com/Raesangur">Raesangur</a>
 * @p       <a href="https://www.raesangur.com/">https://www.raesangur.com/</a>
 *
 * @brief   A utility file to adjust colors
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
 * ===============================================================================================
 */

/** ===============================================================================================
 *  INCLUDES
 */
#include "colors.h"


/** ===============================================================================================
 *  CONSTANTS
 */

constexpr int STDSCR_COLORS = 1;


/** ===============================================================================================
 *  FUNCTION DEFINITIONS
 */

bool enable_colors()
{
    bool colors = has_colors();

    if (!colors)
    {
        printw("Terminal does not support colors!");
        getch();
    }
    else
    {
        start_color();
    }

    return colors;
}

void configure_background_colors(window& mainWin)
{
    init_pair(STDSCR_COLORS, COLOR_WHITE, COLOR_BLUE);
    mainWin.set_color(STDSCR_COLORS);
}


/**
 * ------------------------------------------------------------------------------------------------
 * @}
 */
