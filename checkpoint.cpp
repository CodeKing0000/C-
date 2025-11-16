// std::getline(std::cin, s)
// setlocale(LC_ALL, "ru")

#include <iostream>
#include <string>
#include <vector>
#include <random>

std::string phrase_1_male = "Однажды, в одном королевстве, родился один, ничем не примечательный ребенок. Детство его прошло беззаботно, однако когда ему исполнилось 22 года, его королевство охватила война. Король погиб. И чтобы спасти королевство, он решил поднять восстание, однако ему нужны были деньги, и единственный выход был, это найти сокровище которое закопал давно погибший отец.";
std::string phrase_1_female = "Однажды, в одном королевстве, родился один, ничем не примечательный ребенок. Детство ее прошло беззаботно, однако когда ей исполнилось 22 года, ее королевство охватила война. Король погиб. И чтобы спасти королевство, она решила поднять восстание, однако ее нужны были деньги, и единственный выход был, это найти сокровище которое закопал давно погибший отец.";
std::string phrase_2_male = "Когда он нашел сокровище, он купил на эти деньги оружие и одежду людям. И вместе они смогли закончить войну, победив.";
std::string phrase_2_female = "Когда она нашела сокровище, она купила на эти деньги оружие и одежду людям. И вместе они смогли закончить войну, победив.";

int random_number(int size) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, size - 1);

        int random_number = distrib(gen);
        return random_number;
    }
int chest = random_number();

void game(int answer, int map, int sex, int phrase_2_male, int phrase_2_female) {
        
        if(0 <= answer < size) {
            while(map.at(answer) != 1) {
                std::cout << "Введите номер клетки: ";
                std::cin >> answer;
                if(map.at(answer) == 1) {
                std::cout << "Поздравляем! Вы нашли сундук с деньгами!" << "\n";
                    if(sex == "мужчина") {
                        std::cout << phrase_2_male;
                    }
                    if(sex == "женщина") {
                        std::cout << phrase_2_female;
                    }
                }
            }
        }
        else {
            abort();
        } 
}

int main() {
    int answer;
    int size;
    int chest;
    std::string sex;

    std::cout << "Игра Chest Quest" << "\n\n";
    std::cout << "Введите эти данные для комфортной игры:" << "\n";
    std::cout << "Пол персонажа 'мужчина' или 'женщина': ";
    std::cin >> sex;
    std::cout << "Размер игрового поля:";
    std::cin >> size;

    std::vector <int> map(size);
    random_number(size)
    map.at(chest) = 1;

    if(sex == "мужчина") {
        std::cout << phrase_1_male << "\n";
    }
    if(sex == "женщина") {
        std::cout << phrase_1_female << "\n";
    }
    game(answer, map, sex, phrase_2_male, phrase_2_female)

}
