#include <iostream>
#include <vector>
#include <limits>

// Function declarations
void displayBoard(const std::vector<char>& board);
bool isWinner(const std::vector<char>& board, char player);
bool isBoardFull(const std::vector<char>& board);
int getPlayerMove(const std::vector<char>& board, char player);
void playGame();

int main() {
    char choice;
    do {
        playGame();
        std::cout << "Would you like to play again? (y/n): ";
        std::cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    std::cout << "Thanks for playing Tic-Tac-Toe! Goodbye!" << std::endl;
    return 0;
}

// Displays the Tic-Tac-Toe board
void displayBoard(const std::vector<char>& board) {
    std::cout << "\n";
    for (int i = 0; i < 9; i += 3) {
        std::cout << " " << board[i] << " | " << board[i + 1] << " | " << board[i + 2] << "\n";
        if (i < 6) std::cout << "---|---|---\n";
    }
    std::cout << "\n";
}

// Checks if the current player has won
bool isWinner(const std::vector<char>& board, char player) {
    // Winning combinations
    const int winPatterns[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
        {0, 4, 8}, {2, 4, 6}             // Diagonals
    };

    for (const auto& pattern : winPatterns) {
        if (board[pattern[0]] == player && board[pattern[1]] == player && board[pattern[2]] == player) {
            return true;
        }
    }
    return false;
}

// Checks if the board is full
bool isBoardFull(const std::vector<char>& board) {
    for (const char& cell : board) {
        if (cell != 'X' && cell != 'O') return false;
    }
    return true;
}

// Gets a valid move from the player
int getPlayerMove(const std::vector<char>& board, char player) {
    int move;
    while (true) {
        std::cout << "Player " << player << ", enter your move (1-9): ";
        std::cin >> move;

        // Validate input
        if (std::cin.fail() || move < 1 || move > 9 || board[move - 1] == 'X' || board[move - 1] == 'O') {
            std::cin.clear(); // Clear invalid input flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard input
            std::cout << "Invalid move! Please try again.\n";
        } else {
            return move - 1;
        }
    }
}

// Handles the game logic
void playGame() {
    std::vector<char> board(9); // Initialize the board with empty spaces
    for (int i = 0; i < 9; ++i) board[i] = '1' + i;

    char currentPlayer = 'X';
    bool gameWon = false;

    std::cout << "Welcome to Tic-Tac-Toe!" << std::endl;

    while (!isBoardFull(board)) {
        displayBoard(board);
        int move = getPlayerMove(board, currentPlayer);
        board[move] = currentPlayer;

        if (isWinner(board, currentPlayer)) {
            displayBoard(board);
            std::cout << "Congratulations! Player " << currentPlayer << " wins!\n";
            gameWon = true;
            break;
        }

        // Switch player
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    if (!gameWon) {
        displayBoard(board);
        std::cout << "It's a draw!\n";
    }
}