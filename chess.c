#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int board[8][8];
int turn;

void setupBoard() {
  int r, c;
  int row0[] = {8, 9, 10, 11, 12, 10, 9, 8};
  int row7[] = {2, 3, 4, 5, 6, 4, 3, 2};

  for (r = 0; r < 8; r++) {
    for (c = 0; c < 8; c++) {
      board[r][c] = 0;
    }
  }

  for (c = 0; c < 8; c++) {
    board[0][c] = row0[c];
  }
  for (c = 0; c < 8; c++) {
    board[1][c] = 7;
  }
  for (c = 0; c < 8; c++) {
    board[6][c] = 1;
  }
  for (c = 0; c < 8; c++) {
    board[7][c] = row7[c];
  }

  turn = 0;
}
void printBoard() {
  int r, c;
  const char *labels[] = {"..", "WP", "WR", "WN", "WB", "WQ", "WK",
                          "BP", "BR", "BN", "BB", "BQ", "BK"};

  printf("\n");
  printf("      1    2    3    4    5    6    7    8\n");
  printf("    +----+----+----+----+----+----+----+----+\n");
  for (r = 0; r < 8; r++) {
    printf("  %d |", 8 - r);

    for (c = 0; c < 8; c++) {
      printf(" %s |", labels[board[r][c]]);
    }

    printf("\n");
    printf("    +----+----+----+----+----+----+----+----+\n");
  }
  printf("\n");
}

bool isWhite(int p) { return p >= 1 && p <= 6; } // check the number between 1 and 6? if yes then white piece 
bool isBlack(int p) { return p >= 7 && p <= 12; } // check the number between 7 and 12? if yes then white piece 

bool pathClear(int fc, int fr, int tc, int tr) {
  int sc = 0, sr = 0;
  if (tc > fc) sc = 1;
  if (tc < fc) sc = -1;
  if (tr > fr) sr = 1;
  if (tr < fr) sr = -1;

  int c = fc + sc, r = fr + sr;
  while (c != tc || r != tr) {
    if (board[r][c] != 0) return false;
    c += sc;
    r += sr;
  }
  return true;
}

bool isLegalMove(int fc, int fr, int tc, int tr) {
  if (tc < 0 || tc > 7 || tr < 0 || tr > 7) return false;
  if (fc == tc && fr == tr) return false;

  int moving = board[fr][fc];
  int target = board[tr][tc];

  if (moving == 0) return false;
  if (turn == 0 && !isWhite(moving)) return false;
  if (turn == 1 && !isBlack(moving)) return false;
  if (target != 0 && isWhite(moving) && isWhite(target)) return false;
  if (target != 0 && isBlack(moving) && isBlack(target)) return false;

  int dc = tc - fc;
  int dr = tr - fr;

  if (moving == 1) {
    if (dc == 0 && dr == -1 && target == 0) return true;
    if (dc == 0 && dr == -2 && fr == 6 && target == 0 && board[5][fc] == 0)
      return true;
    if (abs(dc) == 1 && dr == -1 && target != 0) return true;
  }
  if (moving == 7) {
    if (dc == 0 && dr == 1 && target == 0) return true;
    if (dc == 0 && dr == 2 && fr == 1 && target == 0 && board[2][fc] == 0)
      return true;
    if (abs(dc) == 1 && dr == 1 && target != 0) return true;
  }
  if (moving == 2 || moving == 8)
    if (tc == fc || tr == fr) return pathClear(fc, fr, tc, tr);

  if (moving == 3 || moving == 9)
    if ((abs(dc) == 2 && abs(dr) == 1) || (abs(dc) == 1 && abs(dr) == 2))
      return true;

  if (moving == 4 || moving == 10)
    if (abs(dc) == abs(dr)) return pathClear(fc, fr, tc, tr);

  if (moving == 5 || moving == 11)
    if (tc == fc || tr == fr || abs(dc) == abs(dr))
      return pathClear(fc, fr, tc, tr);

  if (moving == 6 || moving == 12)
    if (abs(dc) <= 1 && abs(dr) <= 1) return true;

  return false;
}

bool parseInput(const char *input, int *col, int *row) {
  while (isspace((unsigned char)*input)) input++;
  if (!isdigit((unsigned char)*input)) return false;
  int r = *input++ - '0';

  while (isspace((unsigned char)*input)) input++;
  if (!isdigit((unsigned char)*input)) return false;
  int c = *input - '0';

  if (r < 1 || r > 8 || c < 1 || c > 8) return false;

  *row = 8 - r;
  *col = c - 1;
  return true;
}

int main() {
  char input[64];
  int fc, fr, tc, tr;

  setupBoard();
  printBoard();

  while (1) {
    const char *player = (turn == 0) ? "White" : "Black";

  pickPiece:
    printf("  %s, pick a piece (row col): ", player);
    fflush(stdout);

    if (fgets(input, sizeof(input), stdin) == NULL) break;
    input[strcspn(input, "\n")] = '\0';

    if (strcmp(input, "quit") == 0) {
      printf("  Bye!\n");
      break;
    }

    if (!parseInput(input, &fc, &fr)) {
      printf("  Type two numbers like:  2 5\n");
      goto pickPiece;
    }

    int piece = board[fr][fc];

    if (piece == 0) {
      printf("  That square is empty!\n");
      goto pickPiece;
    }
    if (turn == 0 && !isWhite(piece)) {
      printf("  That's a Black piece, it's White's turn!\n");
      goto pickPiece;
    }
    if (turn == 1 && !isBlack(piece)) {
      printf("  That's a White piece, it's Black's turn!\n");
      goto pickPiece;
    }

    printf("  Where to move? (row col, or 'back'): ");
    fflush(stdout);

  pickDestination:
    if (fgets(input, sizeof(input), stdin) == NULL) break;
    input[strcspn(input, "\n")] = '\0';

    if (strcmp(input, "quit") == 0) {
      printf("  Bye!\n");
      goto done;
    }
    if (strcmp(input, "back") == 0) goto pickPiece;

    if (!parseInput(input, &tc, &tr)) {
      printf("  Type two numbers like:  4 5: ");
      goto pickDestination;
    }

    if (!isLegalMove(fc, fr, tc, tr)) {
      printf("  That's not a valid move, try again: ");
      goto pickDestination;
    }

    int captured = board[tr][tc];

    board[tr][tc] = board[fr][fc];
    board[fr][fc] = 0;
    turn = 1 - turn;

    printBoard();

    if (captured == 6) {
      printf("  Black wins! The White King has been captured!\n");
      break;
    }
    if (captured == 12) {
      printf("  White wins! The Black King has been captured!\n");
      break;
    }
  }

done:
  return 0;
}