/* 
 * N-Queens Problem: 
 * Place N queens on an NxN chess board so that no queen can attack another.
 * Queens can attack horizontally, vertically, and diagonally.
 * 
 * Board Representation:
 * While a chess board is typically visualized as a 2D grid, we can efficiently
 * represent a valid queens solution as a 1D array where:
 * - The index represents the row (0 to N-1)
 * - The value represents the column position of the queen in that row (0 to N-1)
 * 
 * For example, with N=5, a valid solution visualized in 2D would be:
 * 
 *   0 1 2 3 4
 * __________
 * 0 | . . . . Q
 * 1 | . Q . . .
 * 2 | . . . Q .
 * 3 | Q . . . .
 * 4 | . . Q . .
 * 
 * The 1D representation of this solution would be:
 * board[0] = 4 (row 0, column 4)
 * board[1] = 1 (row 1, column 1)
 * board[2] = 3 (row 2, column 3)
 * board[3] = 0 (row 3, column 0)
 * board[4] = 2 (row 4, column 2)
 * 
 * This 1D representation is both memory efficient and simplifies our backtracking
 * algorithm, as we know each row will contain exactly one queen.
 */

 #include <stdio.h>
 #include <stdlib.h>
 
 void print_board_visual(int *board, int n)
 {
     printf("\nSolution:\n");
     
     // Print column headers
     printf("  ");
     for (int col = 0; col < n; col++) {
         printf("%d ", col);
     }
     printf("\n  ");
     
     // Print top border
     for (int col = 0; col < n; col++) {
         printf("__");
     }
     printf("\n");
     
     // Print board with queens
     for (int row = 0; row < n; row++) {
         printf("%d |", row);
         for (int col = 0; col < n; col++) {
             if (board[row] == col) {
                 printf("Q ");
             } else {
                 printf(". ");
             }
         }
         printf("\n");
     }
     
     // Print the 1D representation
     printf("\n1D representation: ");
     for (int row = 0; row < n - 1; row++) {
         printf("%d ", board[row]);
     }
     printf("%d\n", board[n - 1]);
     
     printf("------------------------\n");
 }
 
 int is_safe(int board[], int n, int row, int col)
 {
     // We dont have to check the horizontal
     // because solve_nqueens gets called with row + 1 each iteration,
     
     // Check the vertical
     for (int i = 0; i < row; i++)
         if (board[i] == col)
             return (0);
     
     // Check the first diagonal, the one shaped like this: '\'
     // by decrementing both row and col each step
     for (int i = row, j = col; j >= 0 && i >= 0; i--, j--)
         if (board[i] == j)
             return (0);
     
     // Check the anti-diagonal, the one shaped like this: '/'
     // by decrementing row and increment col each step
     for (int i = row, j = col; j < n && i >= 0; i--, j++)
         if (board[i] == j)
             return (0);
     
     return (1);
 }
 
 void solve_nqueens(int board[], int n, int row, int *solution_count)
 {
     // Base case: if row equals n it means all queens were placed
     // which also means a valid solution was found, we print it and return
     if (row == n) {
         (*solution_count)++;
         printf("\nSolution #%d:", *solution_count);
         print_board_visual(board, n);
         return;
     }
     
     for (int col = 0; col < n; col++) {
         // Check if the current position is safe before placing
         if (is_safe(board, n, row, col)) {
             
             // Place a queen at (row, col)
             board[row] = col;
             
             // Call solve_nqueens again but this time with row + 1
             solve_nqueens(board, n, row + 1, solution_count);
             
             // Backtrack
             board[row] = -1;
         }
     }
 }
 
 int main(int ac, char *av[])
 {
     if (ac != 2) {
         printf("Usage: %s N\nWhere N is the size of the board and number of queens.\n", av[0]);
         return (1);
     }
     
     int n = atoi(av[1]);
     
     if (n <= 0) {
         printf("Error: N must be a positive integer\n");
         return (1);
     }
     
     printf("Solving N-Queens for %d x %d board...\n", n, n);
     
     // Allocate the 1D array
     int *board = malloc(sizeof(int) * n);
     if (!board) {
         printf("Error: Memory allocation failed\n");
         return (1);
     }
     
     // Initialize the board with -1 to represent an empty row
     for (int y = 0; y < n; y++) {
         board[y] = -1;
     }
     
     int solution_count = 0;
     solve_nqueens(board, n, 0, &solution_count);
     
     printf("\nTotal solutions found: %d\n", solution_count);
     
     free(board);
     return (0);
 }