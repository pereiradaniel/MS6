#ifndef SDDS_MENU_H__
#define SDDS_MENU_H__
#include <iostream> 
using namespace std;
namespace sdds {
    const int MAX_NO_OF_ITEMS = 10;
    class Menu;
    class MenuItem {
    private:
        char* m_value;
    public:
        MenuItem() = default;
        MenuItem(const char* value);
        MenuItem(const MenuItem& mi) = delete;
        MenuItem& operator=(const MenuItem& mi) = delete;
        ~MenuItem();
        void display() const;
        friend class Menu;
    };

    class Menu {
        char* m_title;
        MenuItem* m_item[MAX_NO_OF_ITEMS]{};
        int m_noOfItems;
        int m_indentation;
    public:
        Menu();
        Menu(const char* title, int indentation = 0);
        ~Menu();
        Menu(const Menu&);
        Menu& operator=(const Menu& new_menu);
        const Menu& operator=(const char* title);
        operator bool() const;
        bool isEmpty() const;
        void display() const;
        void indent() const;
        void add(const char*);
        Menu& operator<<(const char* m_value);
        int run() const;
        operator int() const;
        void clear();
    };
}
#endif 

