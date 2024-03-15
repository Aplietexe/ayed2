#include <assert.h>  /* assert() */
#include <stdbool.h> /* Tipo bool             */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdlib.h>  /* exit() y EXIT_FAILURE */

#define N 3  // trivia: tictactoe is a solved game for any N
#define CELL_MAX (N * N - 1)

void print_sep(int length) {
    printf("\t ");
    for (int i = 0; i < length; i++) printf("................");
    printf("\n");
}

void print_board(char board[N][N]) {
    int cell = 0;

    print_sep(N);
    for (int row = 0; row < N; ++row) {
        for (int column = 0; column < N; ++column) {
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(N);
    }
}

char get_winner(char board[N][N]) {
    char winner = '-';
    for (int i = 0; i < N; i++) {
        bool found_v = false, found_h = false;
        for (int j = 1; j < N; j++) {
            if (board[i][j] != board[i][0] || board[i][0] == '-') {
                found_h = true;
            }
            if (board[j][i] != board[0][i] || board[0][i] == '-') {
                found_v = true;
            }
        }
        if (!found_h) {
            winner = board[i][0];
            break;
        }
        if (!found_v) {
            winner = board[0][i];
            break;
        }
    }
    return winner;
}

bool has_free_cell(char board[N][N]) {
    bool free_cell = false;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == '-') {
                free_cell = true;
                break;
            }
        }
        if (free_cell) {
            break;
        }
    }

    return free_cell;
}

int main(void) {
    printf("TicTacToe\n");

    char board[N][N];  // missed opportunity to use GNU designated inits
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = '-';
        }
    }

    char turn = 'X';
    char winner = '-';
    int cell = 0;
    while (winner == '-' && has_free_cell(board)) {
        print_board(board);
        printf("\nTurno %c - Elija posición (número del 0 al %d): ",
               turn,
               CELL_MAX);
        int scanf_result = scanf("%d", &cell);
        if (scanf_result <= 0) {
            printf("Error al leer un número desde teclado\n");
            exit(EXIT_FAILURE);
        }
        if (cell >= 0 && cell <= CELL_MAX) {
            int row = cell / N;
            int column = cell % N;  // fixed typo
            if (board[row][column] == '-') {
                board[row][column] = turn;
                turn = turn == 'X' ? 'O' : 'X';
                winner = get_winner(board);
            } else {
                printf("\nCelda ocupada!\n");
            }
        } else {
            printf("\nCelda inválida!\n");
        }
    }
    print_board(board);
    if (winner == '-') {
        printf("Empate!\n");
    } else {
        printf("Ganó %c\n", winner);
    }
    return 0;
}
