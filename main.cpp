#include <iostream>
#include <vector>
#include <deque>
#include <fstream>

using deck = std::deque<int>;

const int number_of_decks = 8;
const int number_of_card_in_deck = 9;

const int minimal_value_card = 6;
const int maximal_value_card = 14;

std::vector<int> v;
std::vector<deck> cards_(number_of_decks);
std::vector<int> Open_cards;



void init() {
    std::ifstream in;
    in.open("/home/maxim/CLionProjects/untitled1/input.txt");

    for (int i = 0; i < number_of_decks; ++i) {
        for (int j = 0; j < number_of_card_in_deck; ++j) {
            int a;
            in >> a;
            cards_[i].push_back(a);
            v.push_back(a);
        }
    }

    for (int i = 0; i < cards_.size(); ++i) {

    }

    in.close();
//    for (int i = 6; i <= 14; i++) {
//        std::cout << i << " : " << std::count(v.begin(), v.end(), i) << std::endl;
//    }
}

void print_matrix(std::vector<deck>& cards){
    for (auto i : cards) {
        for(auto j : i){
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "---------------------------" << std::endl;
}

int counter = 0;

int random_moves(std::vector<deck>& cards, std::vector<int>& offset_){
    for (int i = 0; i < cards.size(); ++i) {
        int a = cards[i].back();
        for (int j = 0; j < cards.size(); ++j) {
            if (i != j) {
                int b = cards[j][cards.size() - 1 - offset_[j]];
                if (b - a == 1){
                    cards[j].push_back(a);
                    cards[i].pop_back();
                    offset_[j]++;
                    std::cout << "change from deck:" << a << "from " << i << "to "  << j << std::endl;
                    print_matrix(cards);
                    if (counter == 10)
                        abort();
                    counter++;
                    random_moves(cards, offset_);
                }
            }
        }
    }
}

int FirstOpen(std::vector<deck>& cards) {
    // должна выдавать первую открытую карту
}

int LastOpen(std::vector<deck>& cards) {
    // должна выдавать последнюю открытую карту
}

void swap(std::vector<int>& cards2, std::vector<int>& cards, int num_cards){
    std::deque<int> temp;
    for (int i = 0; i < num_cards; ++i) {
        temp.push_back(cards.back());
        cards.pop_back();
    }
    for (int i = 0; i < num_cards; ++i) {
        cards2.push_back(temp.front());
        temp.pop_front();
    }
}

bool brute_force(std::vector<deck>& position) {
    for (size_t j = 0; j < 100000; j++)
    {
        std::sort (position.begin (), position.end ());
        size_t empty_heaps = 0;
        for (size_t i = 0; i < number_of_decks - 1; i++)
        {
            if (position[i].empty()) {
                empty_heaps++;
                continue;
            }

            if (position[i + 1].empty () || FirstOpen(position[i]) == LastOpen(position[i + 1]) - 1)
            {
                swap(position[i + 1], position[i]);
            }
        }

        if (position[number_of_card_in_deck - 1].empty () && empty_heaps == number_of_card_in_deck - 1)
        {
            return true;
        }
    }

    return false;
}


signed main(){
    init();
    print_matrix(cards_);
//    print_matrix(cards);
    random_moves(cards_);
//    solve();
    return 0;
}