/**
 * ===============================================================================================
 * @file    menuManager.h
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
#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H


/** ===============================================================================================
 *  INCLUDES
 */
#include "menu.h"

#include <map>
#include <memory>
#include <stack>
#include <string>
#include <vector>


/** ===============================================================================================
 *  CLASS DEFINITION
 */

class menu_manager
{
public:
    using menuptr_t = std::unique_ptr<menu_entry>;
protected:
    menu_manager() {};

public:
    menu_manager(const menu_manager&) = delete;
    menu_manager(const menu_manager&&) = delete;
    void operator=(const menu_manager&) = delete;

    [[nodiscard]] static menu_manager* menu_manager::get()
    {
        if (m_instance == nullptr)
        {
            m_instance = new menu_manager;
        }
        return m_instance;
    }


    [[nodiscard]] menu_entry* top() const
    {
        return m_menuStack.empty() ? nullptr : m_menuStack.top();
    }

    [[nodiscard]] std::size_t size() const
    {
        return m_menuStack.size();
    }

    void pop()
    {
        m_menuStack.pop();
    }

    void set_top(menu_entry* newTopEntry)
    {
        m_menuStack.push(newTopEntry);
    }


    template<typename T>
    menu_manager* add(const std::string& name)
    {
        auto [it, _] = m_menuMap.emplace(name, std::make_unique<T>(name));

        if (m_menuStack.empty())
        {
            m_menuStack.push(std::get<menuptr_t>(*it).get());
        }

        return this;
    }

protected:
    static menu_manager* m_instance;
    std::stack<menu_entry*> m_menuStack;
    std::map<std::string, menuptr_t> m_menuMap;
};


#endif  // MENU_MANAGER_H
/**
 * ------------------------------------------------------------------------------------------------
 */
