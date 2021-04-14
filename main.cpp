#include <iostream>

#include <vector>

#include <unordered_map>

#include <string>

#include <fstream>

#include <stdio.h>

#include <string.h>

#include <sstream>

#include <iostream>
#include <regex>





class CourseTable {
public:
    int dp_start(size_t fifth_course) {
        std::vector<int> dp(100);

        for (auto &i: dp) {
            i = -1;
        }

        for (int i = 0; i < max_priority_ - 1; ++i) {
            for (auto&[key, value] : table_[i]) {
                if (table_[i].empty()) {
                    dp[key] = 0;
                }
            }
        }

        return lazy_dfs(fifth_course, dp, max_priority_ - 1);
    }

    int lazy_dfs(size_t key, std::vector<int>& dp, int level){
        if (dp[key] != -1){
            return dp[key] + 1;
        }

        int sum = 0;
        auto children = table_[level][key];
        for (auto& child : children)
        {
            sum += lazy_dfs(child, dp, levels[child]);
        }

        return sum + 1;
    }

private:
    using Dependence = std::vector<size_t>;
    using Level = std::unordered_map<size_t, Dependence>;
    using Table = std::vector<Level>;

    size_t max_priority_;
    Table table_;
    std::unordered_map<size_t, std::string> names;
    std::unordered_map<size_t, size_t> levels;

    friend std::ifstream& operator>>(std::ifstream& stream, CourseTable& table);
};

std::ifstream& operator>>(std::ifstream& stream, CourseTable& table)
{
    std::string cur_line;
    std::getline(stream, cur_line);
    sscanf(cur_line.c_str(), "%zd", &table.max_priority_);

    table.table_.resize(table.max_priority_);
    if (0 == table.max_priority_) {
        return stream;
    }


    size_t number_of_course = 0;

    auto str = new char[50];
    auto dependence = new char[50];
    for (size_t current_level = 0; current_level < table.max_priority_; current_level++) {
        std::getline(stream, cur_line);

        int read_bytes = 0;
        int bytes = 0;
        while (sscanf(cur_line.c_str() + read_bytes, " (%zd) %[^[] [%[^]]],%n", &number_of_course, str, dependence, &bytes) == 3) {
            table.names[number_of_course] = std::string(str);
            table.levels[number_of_course] = current_level;
            read_bytes += bytes;


            size_t read_dependence = 0;
            size_t bytes_to_add = 0;
            while (sscanf(dependence + bytes_to_add, "%zd,%n", &read_dependence, &bytes) == 1) {
                bytes_to_add += bytes;
                table.table_[current_level][number_of_course].push_back(read_dependence);
            }
        }
    }

    delete[] str;
    delete[] dependence;
    return stream;
}


int main (const int argc, const char** argv) {

    const int number_of_courses3 = 2; // количество кусов 3 уровня
    std::vector<size_t> course3(number_of_courses3); // номера кусов 3 уровня

    std::ifstream file_read;
    file_read.open(/*argv[1]*/"/home/maxim/CLionProjects/untitled1/cmake-build-debug/courses.csv");

    CourseTable table;

    file_read >> table;


    std::cout << table.dp_start(10) + table.dp_start(course3[0]) + table.dp_start(course3[1]);
    

    if (argc != 4) {
        std::cout << "На вход должно даваться 4 аргумента\n";
    }
}
