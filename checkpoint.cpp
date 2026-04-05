#include <iostream>
#include <string>
#include <vector>

class Expense {

    protected:

    std::string name;
    int amount;

    public:

    Expense(std::string n, int a) : name(n), amount(a) {}
    virtual ~Expense() = default;

    virtual void get_category() = 0;

    void describe() {
        std::cout << name << std::endl;
        get_category();
        std::cout << amount << std::endl;
    }

    std::string get_name() { return name; }
    int get_amount() { return amount; }
    
};

class Groceries : public Expense {
    public:
    Groceries(std::string n, int a) : Expense(n, a) {}
    void get_category() override { std::cout << "Продукты питания" << std::endl; }
};
class Clothes : public Expense {
    public:
    Clothes(std::string n, int a) :  Expense(n, a) {}
    void get_category() override { std::cout << "Одежда" << std::endl; }
};

int main() {
    std::vector <Expense*> expenses;
    std::string cmd;
    bool a = true;

    while(a) {
        std::cout << "Metods: add, delete, list, total, exit" << std::endl;
        std::cout << "Metod: ";
        std::cin >> cmd;

        if(cmd == "add") {
            std::string temp_category;
            std::string temp_name;
            int temp_amount;
            std::cout << "Category ( clothes, groceries ): ";
            std::cin >> temp_category;
            std::cout << "Good: ";
            std::cin >> temp_name;
            std::cout << "Price: ";
            std::cin >> temp_amount;

            Expense* e = nullptr;

            if(temp_category == "clothes") {
                e = new Clothes(temp_name, temp_amount);
                expenses.push_back(e);
            }
            else if(temp_category == "groceries") {
               e = new Groceries(temp_name, temp_amount);
                expenses.push_back(e);
            }
            else {
                std::cout << "There is no such category!" << std::endl;
            }
        }

        else if(cmd == "delete") {
            std::string temp;
            std::cout << "Which expense do you want delete: ";
            std::cin >> temp;
            for(int i = 0; i < expenses.size(); i++) {
                if(expenses.at(i)->get_name() == temp) {
                    delete expenses.at(i);
                    std::cout << "Expence have already deleted!" << std::endl;
                }
            }
        }
        else if(cmd == "list") {
            int result;
            for(int i = 0; i < expenses.size(); i++) {
                std::cout << expenses.at(i)->get_name() << " - " << expenses.at(i)->get_amount() << std::endl;
                result += expenses.at(i)->get_amount();
            }
            std::cout << "Total: " << result << std::endl;
        }
        else if(cmd == "total") {
            int result;
            for(int i = 0; i < expenses.size(); i++) {
                result += expenses.at(i)->get_amount();
            }
            std::cout << "Total: " << result << std::endl;
        }
        else if(cmd == "exit") {
            a = false;
        }
        else {
            std::cout << "There is no such metod!" << std::endl;
        }
    }
}
// Задание: Семейный бюджет
// Идея
// Программа считает расходы семьи. Каждый тип расхода — отдельный класс. В конце — отчёт: сколько потратили,
// на что, у кого перерасход.

// Структура
// Базовый класс Expense:

// поля: name, amount
// виртуальный метод category() — возвращает строку
// describe() — выводит инфо


// работа с конолью через add …, delete, total, list