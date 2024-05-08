#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum class PieceType {
    Pawn,
    Rook,
    Knight,
    Bishop,
    Queen,
    King
};

template<typename T>
class Board {
private:
    vector<vector<T>> board;
    int size;

public:
    Board(int n) : size(n) {
        board.resize(size, vector<T>(size));
    }

    void clear() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                board[i][j] = 0;
            }
        }
    }

    void setPiece(int row, int col, T value) {
        board[row][col] = value;
    }

    void setMoves(int row, int col, T value) {
        if (row >= 0 && row < size && col >= 0 && col < size) {
            if (board[row][col] != 2) {
                board[row][col] = value;
            }
        }
    }

    void print() {
        cout << " ";
        for (char c = 'a'; c < 'a' + size; c++) {
            cout << c << " ";
        }
        cout << endl;

        for (int i = size - 1; i >= 0; i--) {
            cout << i + 1 << " ";
            for (int j = 0; j < size; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }
};

void calculateMoves(Board<int>& board, PieceType piece, int row, int col) {
    board.clear();
    board.setPiece(row, col, 2);

    switch (piece) {
        case PieceType::Pawn:
            board.setMoves(row + 1, col, 1);
            break;
        case PieceType::Rook:
            for (int i = row + 1; i < 8; i++) {
                board.setMoves(i, col, 1);
            }
            for (int i = row - 1; i >= 0; i--) {
                board.setMoves(i, col, 1);
            }
            for (int j = col + 1; j < 8; j++) {
                board.setMoves(row, j, 1);
            }
            for (int j = col - 1; j >= 0; j--) {
                board.setMoves(row, j, 1);
            }
            break;
        case PieceType::Knight:
            board.setMoves(row + 2, col + 1, 1);
            board.setMoves(row + 2, col - 1, 1);
            board.setMoves(row - 2, col + 1, 1);
            board.setMoves(row - 2, col - 1, 1);
            board.setMoves(row + 1, col + 2, 1);
            board.setMoves(row + 1, col - 2, 1);
            board.setMoves(row - 1, col + 2, 1);
            board.setMoves(row - 1, col - 2, 1);
            break;
        case PieceType::Bishop:
            for (int i = 1; i < 8; i++) {
                board.setMoves(row + i, col + i, 1);
                board.setMoves(row + i, col - i, 1);
                board.setMoves(row - i, col + i, 1);
                board.setMoves(row - i, col - i, 1);
            }
            break;
        case PieceType::Queen:
            for (int i = row + 1; i < 8; i++) {
                board.setMoves(i, col, 1);
            }
            for (int i = row - 1; i >= 0; i--) {
                board.setMoves(i, col, 1);
            }
            for (int j = col + 1; j < 8; j++) {
                board.setMoves(row, j, 1);
            }
            for (int j = col - 1; j >= 0; j--) {
                board.setMoves(row, j, 1);
            }
            for (int i = 1; i < 8; i++) {
                board.setMoves(row + i, col + i, 1);
                board.setMoves(row + i, col - i, 1);
                board.setMoves(row - i, col + i, 1);
                board.setMoves(row - i, col - i, 1);
            }
            break;
        case PieceType::King:
            board.setMoves(row + 1, col, 1);
            board.setMoves(row - 1, col, 1);
            board.setMoves(row, col + 1, 1);
            board.setMoves(row, col - 1, 1);
            board.setMoves(row + 1, col + 1, 1);
            board.setMoves(row + 1, col - 1, 1);
            board.setMoves(row - 1, col + 1, 1);
            board.setMoves(row - 1, col - 1, 1);
            break;
    }
}

int main() {
    Board<int> board(8);
    string pieceStr;
    string position;

    cout << "Enter the piece (Pawn, Rook, Knight, Bishop, Queen, King): ";
    cin >> pieceStr;
    PieceType piece;
    if (pieceStr == "Pawn") {
        piece = PieceType::Pawn;
    } else if (pieceStr == "Rook") {
        piece = PieceType::Rook;
    } else if (pieceStr == "Knight") {
        piece = PieceType::Knight;
    } else if (pieceStr == "Bishop") {
        piece = PieceType::Bishop;
    } else if (pieceStr == "Queen") {
        piece = PieceType::Queen;
    } else if (pieceStr == "King") {
        piece = PieceType::King;
    } else {
        cout << "Invalid piece!" << endl;
        return 0;
    }

    cout << "Enter the position (e.g., e4): ";
    cin >> position;

    int col = position[0] - 'a';
    int row = position[1] - '1';

    calculateMoves(board, piece, row, col);
    board.print();

    return 0;
}