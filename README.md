# ♟️ terminal-chess

A lightweight, two-player chess game that runs entirely in your terminal — no dependencies, no GUI, just C and a board.

---

## Features

- Full two-player chess (White vs Black, alternating turns)
- All standard pieces: Pawns, Rooks, Knights, Bishops, Queens, and Kings
- Legal move validation for every piece type
- Pawn two-square opening moves
- Clear ASCII board with labeled rows and columns
- Win detection by King capture
- Simple `row col` input (e.g. `2 5`)
- `back` to reselect a piece, `quit` to exit anytime

## Getting Started

### Prerequisites

- A C compiler (GCC or Clang)
- A terminal

### Build & Run

```bash
gcc -o chess chess.c
./chess
```

## How to Play

The board is displayed after every move. Pieces are labeled with two-letter codes:

| Code | Piece        |
|------|--------------|
| WP   | White Pawn   |
| WR   | White Rook   |
| WN   | White Knight |
| WB   | White Bishop |
| WQ   | White Queen  |
| WK   | White King   |
| BP–BK | Black equivalents |

**Input format:** enter the row then the column, separated by a space.

```
White, pick a piece (row col): 2 5
Where to move? (row col, or 'back'): 4 5
```

- Type `back` to reselect a different piece
- Type `quit` to exit the game

The game ends when a King is captured.

## Project Structure

```
chess.c   — everything: board setup, move validation, input parsing, game loop
```

## License

Copyright (c) 2026 — All rights reserved by the project authors.

This project was created as part of an academic course at **Usman Institute of Technology**. Redistribution, reproduction, or reuse of any part of this codebase without explicit written permission from the authors is not permitted.

**Project Team:**

| Student ID   | Name             | Role   |
|--------------|------------------|--------|
| 26SP-040-SE  | Talha Bin Khalid | Leader |
| 26SP-016-SE  | Bareera          | Member |
| 26SP-007-SE  | Anousha          | Member |
| 26SP-020-SE  | Sadiq            | Member |
| 26SP-023-SE  | Samana           | Member |
