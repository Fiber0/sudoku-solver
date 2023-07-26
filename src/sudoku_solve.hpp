#ifndef SUDOKU_SOLVE_HPP
#define SUDOKU_SOLVE_HPP
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <cassert>


using namespace std;

class solve {
private:
    static void get_missing_nums_and_empty_spots(vector<vector<char>>& grid, uint8_t row_idx, unordered_set<char>& missing_nums, unordered_set<uint8_t>& blank_spots);
    
    static bool validate_solution(vector<unordered_set<char>>const& blocks);

    static void save_number_to_grid(vector<vector<char>>& grid, uint8_t row, uint8_t m_num, uint8_t idx, vector<unordered_set<char>>& blocks, vector<unordered_set<char>>& columns);
public:
    
    static void define_boards(vector<vector<char>>& grid, vector<unordered_set<char>>& blocks, vector<unordered_set<char>>& columns);

    static bool solve_sudoku(vector<vector<char>>& main_grid, vector<vector<char>> grid, vector<unordered_set<char>> blocks, vector<unordered_set<char>> columns);

    static bool validate_grid(vector<vector<char>>& grid);

    

};

void print_sudoku(const vector<vector<char>>& grid);

#endif