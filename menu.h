/**
 * ===============================================================================================
 * @file    menu.h
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
#ifndef MENU_H
#define MENU_H

/** ===============================================================================================
 *  INCLUDES
 */
#include <ncurses.h>

#include <memory>
#include <string>
#include <vector>


/** ===============================================================================================
 *  CLASS DEFINITION
 */

class menu_entry
{
public:
    menu_entry(const std::string& name) : m_name{name} {}

    [[nodiscard]] virtual menu_entry* highlighted_entry() const = 0;

    virtual void move_up() = 0;
    virtual void move_down() = 0;

    [[nodiscard]] virtual bool can_enter() const = 0;
    [[nodiscard]] virtual bool can_select() const = 0;

    [[nodiscard]] virtual bool is_selected() const = 0;
    virtual void select() = 0;
    virtual void deselect() = 0;

    void highlight()
    {
        m_highlighted = true;
    }

    void dehighlight()
    {
        m_highlighted = false;
    }

    [[nodiscard]] std::string display() const
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

    [[nodiscard]] std::string get_name() const
    {
        return m_name;
    }

protected:
    bool m_highlighted = false;

    std::string m_name;
};


class menu_text_entry : public menu_entry
{
public:
    menu_text_entry(const std::string& name) : menu_entry{name} {}

    [[nodiscard]] menu_entry* highlighted_entry() const final
    {
        return nullptr;
    }

    void move_up() final{}
    void move_down() final{}

    [[nodiscard]] bool can_enter() const final
    {
        return false;
    }

    [[nodiscard]] bool can_select() const final
    {
        return false;
    }

    [[nodiscard]] bool is_selected() const final
    {
        return false;
    }

    void select() final{}
    void deselect() final{}
};


class menu_option_entry : public menu_entry
{
public:
    menu_option_entry(const std::string& name) : menu_entry{name} {}

    [[nodiscard]] virtual menu_entry* highlighted_entry() const
    {
        return nullptr;
    }

    void virtual move_up() {}
    void virtual move_down() {}

    [[nodiscard]] virtual bool can_enter() const
    {
        return false;
    }

    [[nodiscard]] bool can_select() const final
    {
        return true;
    }

    [[nodiscard]] bool is_selected() const final
    {
        return m_selected;
    }
    
    void select() final
    {
        m_selected = true;
    }

    void deselect() final
    {
        m_selected = false;
    }

protected:
    bool m_selected = false;
};

class menu_top_entry : public menu_entry
{
public:
    menu_top_entry(const std::string& name) : menu_entry{name} {}

    void add(std::unique_ptr<menu_entry> newEntry)
    {
        m_submenus.push_back(std::move(newEntry));
    }

    [[nodiscard]] menu_entry* highlighted_entry() const final
    {
        return m_submenus[m_currentMenu].get();
    }

    void move_up() final
    {
        if (m_currentMenu > 0)
        {
            m_submenus[m_currentMenu]->dehighlight();
            m_currentMenu--;
            m_submenus[m_currentMenu]->highlight();
        }
    }
    void move_down()
    {
        if (m_currentMenu < m_submenus.size())
        {
            m_submenus[m_currentMenu]->dehighlight();
            m_currentMenu++;
            m_submenus[m_currentMenu]->highlight();
        }
    }

    [[nodiscard]] bool can_enter() const final
    {
        return true;
    }

    [[nodiscard]] bool can_select() const
    {
        return false;
    }

    [[nodiscard]] bool is_selected() const
    {
        return false;
    }
    
    void select(){}
    void deselect(){}

    [[nodiscard]] const auto begin() const
    {
        return m_submenus.begin();
    }
    [[nodiscard]] const auto end() const
    {
        return m_submenus.end();
    }
    [[nodiscard]] const menu_entry* get(std::size_t index) const
    {
        return m_submenus[index].get();
    }

public:
    std::size_t m_currentMenu = 0;
    std::vector<std::unique_ptr<menu_entry>> m_submenus{};
};


#endif  // MENU_H
/**
 * ------------------------------------------------------------------------------------------------
 */
