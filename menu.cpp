/**
 * ===============================================================================================
 * @file    menu.cpp
 * @author  Pascal-Emmanuel Lachance
 * @p       <a href="https://www.github.com/Raesangur">Raesangur</a>
 * @p       <a href="https://www.raesangur.com/">https://www.raesangur.com/</a>
 *
 * @brief   The menu class allows navigation across menus
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
#include "menu.h"


/** ===============================================================================================
 *  MENU_ENTRY MEMBER FUNCTION DEFINITIONS
 */

[[nodiscard]] menu_entry* menu_entry::highlighted_entry() const
{
    return nullptr;
}


[[nodiscard]] bool menu_entry::can_enter() const
{
    return false;
}

[[nodiscard]] bool menu_entry::can_select() const
{
    return false;
}

[[nodiscard]] bool menu_entry::is_selected() const
{
    return false;
}


void menu_entry::move_up() {}
void menu_entry::move_down() {}

void menu_entry::select() {}
void menu_entry::deselect() {}

void menu_entry::input_character(char c) {}

[[nodiscard]] bool menu_entry::has_input_field() const
{
    return false;
}


[[nodiscard]] bool menu_entry::is_highlighted() const
{
    return m_highlighted;
}

void menu_entry::highlight()
{
    m_highlighted = true;
}

void menu_entry::dehighlight()
{
    m_highlighted = false;
}


[[nodiscard]] std::string menu_entry::display() const
{
    std::string preamble = "   ";
    std::string postamble = "";
    
    if (can_select())
    {
        if (is_selected())
        {
            preamble = "[*]";
        }
        else
        {
            preamble = "[ ]";
        }
    }
    if (can_enter())
    {
        postamble = "--->";
    }

    return preamble + " " + m_name + " " + postamble;
}

[[nodiscard]] std::string menu_entry::get_name() const
{
    return m_name;
}


/** ===============================================================================================
 *  MENU_TOP_OPTION_ENTRY MEMBER FUNCTION DEFINITIONS
 */

[[nodiscard]] menu_entry* menu_top_option_entry::highlighted_entry() const
{
    return menu_top_entry::highlighted_entry();
}

void menu_top_option_entry::move_up()
{
    return menu_top_entry::move_up();
}
void menu_top_option_entry::move_down()
{
    return menu_top_entry::move_down();
}


[[nodiscard]] bool menu_top_option_entry::can_enter() const
{
    return menu_top_entry::can_enter();
}
[[nodiscard]] bool menu_top_option_entry::can_select() const
{
    return menu_option_entry::can_select();
}

[[nodiscard]] bool menu_top_option_entry::is_selected() const
{
    return menu_option_entry::is_selected();
}

/**
 * ------------------------------------------------------------------------------------------------
 */
