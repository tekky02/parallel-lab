#include "sudoku.hpp"
// header files

using namespace std;

static constexpr int size = 9;

namespace sudoku {

bool check(vector<vector<char>> const &matrix, int row, int col, char num) {
    for (int i = 0; i < size; i++) {
        if (matrix[row][i] == num) return false;
        if (matrix[i][col] == num) return false;
        if (matrix[(row / 3) * 3 + i / 3][(col / 3) * 3 + i % 3] == num)
            return false;
    }
    return true;
}

bool backtrack(vector<vector<char>> &matrix, int row, int col) {
    if (row == size) {
        return true;
    }

    if (col == size) {
        return backtrack(matrix, row + 1, 0);
    }
    for (int i = row; i < size; i++) {
        for (int j = col; j < size; j++) {
            if (matrix[i][j] != '-') {
                return backtrack(matrix, i, j + 1);
            }

/// 每个节点作的选择相互独立，可以并行化
#pragma omp parallel for
            for (int num = '1'; num <= '9'; num++) {
                if (!check(matrix, i, j, num)) continue;
                matrix[i][j] = num;
                if (backtrack(matrix, i, j + 1)) {
                    return true;
                }
                matrix[i][j] = '-';
            }
            return false;
        }
    }
    return false;
}

void solveSudoku(vector<vector<char>> &matrix) {
    // Timer timer;
    backtrack(matrix, 0, 0);
}

}  // namespace sudoku
