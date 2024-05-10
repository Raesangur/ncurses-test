/**
 * ===============================================================================================
 * @file    menuManager.cpp
 * @author  Pascal-Emmanuel Lachance
 * @p       <a href="https://www.github.com/Raesangur">Raesangur</a>
 * @p       <a href="https://www.raesangur.com/">https://www.raesangur.com/</a>
 *
 * @brief   Singleton with ownership of all menus, allows for searching and getting menus.
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
#include "menu-manager.h"


/** ===============================================================================================
 *  SINGLETON INSTANCE
 */
menu_manager* menu_manager::m_instance = nullptr;


template<>
submenu_manager* submenu_manager::add<menu_top_entry>(const std::string_view name)
{
    m_child = std::make_unique<submenu_manager>(m_mm, this);
    return m_mm->add<menu_top_entry, true>(name, m_child.get());
}

template<>
submenu_manager* submenu_manager::add<menu_top_option_entry>(const std::string_view name)
{
    m_child = std::make_unique<submenu_manager>(m_mm, this);
    return m_mm->add<menu_top_option_entry, true>(name, m_child.get());
}


/**
 * ------------------------------------------------------------------------------------------------
 */
