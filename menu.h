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
#include <memory>
#include <string>
#include <vector>


/** ===============================================================================================
 *  CLASS DEFINITION
 */

class menu_entry
{
protected:
    menu_entry(const std::string& name) : m_name{name} {}

public:
    [[nodiscard]] virtual menu_entry* highlighted_entry() const;

    virtual void move_up();
    virtual void move_down();

    [[nodiscard]] virtual bool can_enter() const;
    [[nodiscard]] virtual bool can_select() const;
    [[nodiscard]] virtual bool is_selected() const;
    virtual void select();
    virtual void deselect();

    virtual void input_character(char c);
    [[nodiscard]] virtual bool has_input_field() const;

    [[nodiscard]] bool is_highlighted() const;
    void highlight();
    void dehighlight();

    [[nodiscard]] std::string display() const;
    [[nodiscard]] std::string get_name() const;


protected:
    bool m_highlighted = false;

    std::string m_name;
};


class menu_text_entry : public menu_entry
{
public:
    menu_text_entry(const std::string& name) : menu_entry{name} {}
};


class menu_option_entry : public virtual menu_entry
{
public:
    menu_option_entry(const std::string& name) : menu_entry{name} {}

    [[nodiscard]] virtual bool can_select() const
    {
        return true;
    }

    [[nodiscard]] virtual bool is_selected() const
    {
        return m_selected;
    }
    
    void virtual select()
    {
        m_selected = true;
    }

    void virtual deselect()
    {
        m_selected = false;
    }

protected:
    bool m_selected = false;
};


class menu_top_entry : public virtual menu_entry
{
public:
    menu_top_entry(const std::string& name) : menu_entry{name} {}

    void add(menu_entry* newEntry)
    {
        m_submenus.push_back(newEntry);
        if (m_submenus.size() == 1)
        {
            m_submenus[0]->highlight();
        }
    }

    [[nodiscard]] virtual menu_entry* highlighted_entry() const
    {
        return m_submenus[m_currentMenu];
    }

    virtual void move_up()
    {
        if (m_currentMenu > 0)
        {
            m_submenus[m_currentMenu]->dehighlight();
            m_currentMenu--;
            m_submenus[m_currentMenu]->highlight();
        }
    }
    virtual void move_down()
    {
        if (m_currentMenu < m_submenus.size() - 1)
        {
            m_submenus[m_currentMenu]->dehighlight();
            m_currentMenu++;
            m_submenus[m_currentMenu]->highlight();
        }
    }

    [[nodiscard]] virtual bool can_enter() const
    {
        return true;
    }


    [[nodiscard]] const auto begin() const
    {
        return m_submenus.begin();
    }
    [[nodiscard]] const auto end() const
    {
        return m_submenus.end();
    }
    [[nodiscard]] std::size_t size() const
    {
        return m_submenus.size();
    }
    [[nodiscard]] const menu_entry* get(std::size_t index) const
    {
        return m_submenus[index];
    }

public:
    std::size_t m_currentMenu = 0;
    std::vector<menu_entry*> m_submenus{};
};

class menu_top_option_entry: public menu_top_entry, public menu_option_entry
{
public:
    menu_top_option_entry(const std::string& name) : menu_entry{name}, menu_top_entry{name}, menu_option_entry{name} {}

    [[nodiscard]] menu_entry* highlighted_entry() const final;

    void move_up() final;
    void move_down() final;

    [[nodiscard]] bool can_enter() const final;
    [[nodiscard]] bool can_select() const final;

    [[nodiscard]] bool is_selected() const final;


    void virtual select()
    {
        menu_option_entry::select();
        for(menu_entry* menu : m_submenus)
        {
            if (menu->can_select())
            {
                menu->select();
            }
        }
    }

    void virtual deselect()
    {
        menu_option_entry::deselect();
        for(menu_entry* menu : m_submenus)
        {
            if (menu->can_select())
            {
                menu->deselect();
            }
        }
    }
};


#endif  // MENU_H
/**
 * ------------------------------------------------------------------------------------------------
 */
