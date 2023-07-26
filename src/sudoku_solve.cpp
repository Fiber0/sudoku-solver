
#include "sudoku_solve.hpp"
//#include "tests.cpp"

    void solve::get_missing_nums_and_empty_spots(vector<vector<char>> &grid, uint8_t row_idx, unordered_set<char> &missing_nums, unordered_set<uint8_t> &blank_spots){
        for(uint8_t idx = 0; idx < 9; idx++){
            if (grid.at(row_idx).at(idx) == '.'){
                blank_spots.insert(idx);
            }
            else{
                missing_nums.erase(grid.at(row_idx).at(idx));
            }
        }
    }
    
    bool solve::validate_solution(vector<unordered_set<char>>const& blocks) {
        for (uint8_t block = 0; block < 9; block++) {
        
            if (blocks.at(block).size() < 9){
                return 0; 
            }
        
        }
        return 1;
    }
    
    void solve::save_number_to_grid(vector<vector<char>>& grid, uint8_t row, uint8_t m_num, uint8_t idx, vector<unordered_set<char>>& blocks, vector<unordered_set<char>>& columns) {
        grid.at(row).at(idx) = m_num;
        blocks.at((idx/3)+(row/3)*3).insert(m_num);
        columns.at(idx).insert(m_num);
    }

    
    // defines main grid in terms of it's columns and blocks
void solve::define_boards(vector<vector<char>>& grid, vector<unordered_set<char>>& blocks, vector<unordered_set<char>>& columns) {
    for (unordered_set<char>& b : blocks) {
        b.clear();
    }
    for (unordered_set<char>& c : columns) {
        c.clear();
    }
    for (int row = 0; row < 9; row++) {
        for(int col = 0; col < 9; col++){
            char ch = grid.at(row).at(col);
            if (ch == '.'){
                continue;
            }
            blocks.at((col/3)+(row/3)*3).insert(ch);
            columns.at(col).insert(ch);
        }
    }
}




bool solve::solve_sudoku(vector<vector<char>> &main_grid,vector<vector<char>> grid, vector<unordered_set<char>> blocks, vector<unordered_set<char>> columns){
    bool grid_not_filled = 1;
    while (grid_not_filled){
        grid_not_filled = 0;
        bool no_obvious_steps = 1;
        vector <uint8_t> possible_fits;
        vector <uint8_t> best_possible_fits(9);
        uint8_t best_num_to_guess;
        uint8_t best_num_to_guess_row;

        for(int row = 0; row < 9; row++){
            unordered_set<char> missing_nums_in_row = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
            unordered_set<uint8_t> empty_spots_in_row;
            
            get_missing_nums_and_empty_spots(grid, row, missing_nums_in_row, empty_spots_in_row);

            for(char m_num : missing_nums_in_row){
                possible_fits.clear();
                bool set_number =0 ;
                for (uint8_t b_spot : empty_spots_in_row) {
                    
                    if (blocks.at((b_spot / 3) + (row / 3) * 3).find(m_num) == blocks.at((b_spot / 3) + (row / 3) * 3).end() && columns.at(b_spot).find(m_num) == columns.at(b_spot).end()) {
                        if (possible_fits.size() == 0) {
                            possible_fits.emplace_back(b_spot);
                            set_number = 1;

                            
                        }
                        else if(!no_obvious_steps){
                            grid_not_filled = 1;
                            set_number = 0;
                            break;
                        }
                        else{
                            grid_not_filled = 1;
                            set_number = 0;
                            possible_fits.emplace_back(b_spot);

                        }
                    }
                }
                if (set_number){
                    save_number_to_grid(grid, row, m_num, possible_fits.at(0), blocks, columns);
                    no_obvious_steps = 0;
                    empty_spots_in_row.erase(possible_fits.at(0));
                }
                else if(possible_fits.size() < best_possible_fits.size()){
                    best_possible_fits = possible_fits;
                    best_num_to_guess = m_num;
                    best_num_to_guess_row  = row;
                }

            }
        }
        if(no_obvious_steps){
            for (uint8_t space : best_possible_fits) {
                save_number_to_grid(grid, best_num_to_guess_row, best_num_to_guess, space, blocks, columns);
                
                if (solve_sudoku(main_grid, grid, blocks, columns)) {
                    return 1;
                }
                
                grid.at(best_num_to_guess_row).at(space) = '.';
                blocks.at((space/3)+(best_num_to_guess_row/3)*3).erase(best_num_to_guess);
                columns.at(space).erase(best_num_to_guess);

            }

            break;
        }

    }
    if(validate_solution(blocks)){
        main_grid = grid;
        return 1;
    }
    return 0;
}

bool solve::validate_grid(vector<vector<char>>& grid) {
    for (int row = 0; row < 9; row++) {
        for(int col = 0; col < 9; col++){
            char ch = grid.at(row).at(col);
            if (ch == '.'){
                return 0;
            }
        }
    }
    return 1;
}

void print_sudoku(const vector<vector<char>>& grid) {
    cout << "\n|─────────────────────────────────────|" << endl;
    for (uint8_t i = 0; i < 9; i++) {
        cout << "| " << grid[i][0] << " | " << grid[i][1] << " | " << grid[i][2] << " || " << grid[i][3] << " | " << grid[i][4] << " | " << grid[i][5] <<
                " || " << grid[i][6] << " | " << grid[i][7] << " | " << grid[i][8] << " | \n";
        if (i != 8) {
            if ((i + 1) % 3 == 0 ) {
                cout << "|===|===|===||===|===|===||===|===|===|" << endl;
            }
            else  {
                cout << "|───|───|───||───|───|───||───|───|───|" << endl;
            }
        }
    }
    cout << "|─────────────────────────────────────|" << endl;
}



int main() {
    solve Solve;
    
    vector < vector<char>> board;
    
    vector<unordered_set<char>> blocks(9);
    vector<unordered_set<char>> columns(9);
    // for testing:
    //  test::complete_test(board, blocks, columns); 

    board = { {'.','.','.','8','.','.','.','.','9'},{'.','8','7','3','.','.','.','4','.'},{'6','.','.','7','.','.','.','.','.'},{'.','.','8','5','.','.','9','7','.'},{'.','.','.','.','.','.','.','.','.'},{'.','4','3','.','.','7','5','.','.'},{'.','.','.','.','.','3','.','.','.'},{'.','3','.','.','.','1','4','5','.'},{'4','.','.','.','.','2','.','.','1'} };

    solve::define_boards(board, blocks, columns);
    solve::solve_sudoku(board, board, blocks, columns);
    if (solve::validate_grid(board)) {
        cout << "\nDone:";
        print_sudoku(board);
    }
    else {
        cout << "!!! the sudoku you specified is unsolvable !!! \n";
    }
    
    return 0;
}
