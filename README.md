# Tetris

A terminal-based Tetris game written in C, running natively on Windows via the Win32 console API with full ANSI color support.

## ✨ Features

- **Classic Tetris gameplay** — all 7 tetrominoes (I, O, T, S, Z, J, L)
- **Hold piece** — swap the current piece into reserve at any time
- **5-piece queue** — see the next 5 upcoming pieces
- **Ghost piece** — shows where the current piece will land
- **Line clears** — single, double, triple, and Tetris (4-line)
- **Progressive difficulty** — speed increases every 10 lines
- **Score system** — points for soft drops, hard drops, and line clears
- **Colorful ANSI rendering** — each tetromino has its own color
- **Main menu** with keyboard navigation
- **Leaderboard** *(coming soon)*

## 🎮 Controls

| Key | Action |
|-----|--------|
| `←` / `A` | Move left |
| `→` / `D` | Move right |
| `↓` / `S` | Soft drop |
| `↑` / `W` | Rotate |
| `Space` | Hard drop |
| `Q` | Hold piece |
| `Esc` | Quit to menu |

## 🏗️ Building

### Requirements

- [GCC (MinGW)](https://www.mingw-w64.org/) or any C11-compatible compiler
- Windows (Win32 console API is used for input and cursor control)
- `make`

### Build

```bash
make
```

### Run

```bash
./tetris.exe
```

### Clean

```bash
make clean
```

## 📁 Project Structure

```
tetris/
├── include/
│   ├── Board.h
│   ├── Game.h
│   ├── Input.h
│   ├── Piece.h
│   ├── Tetromino.h
│   └── renderer/
│       ├── GameRenderer.h
│       ├── LeaderboardRenderer.h
│       ├── MenuRenderer.h
│       └── Renderer.h
├── src/
│   ├── Board.c
│   ├── Game.c
│   ├── Input.c
│   ├── main.c
│   ├── Piece.c
│   ├── Tetromino.c
│   └── renderer/
│       ├── GameRenderer.c
│       ├── LeaderboardRenderer.c
│       ├── MenuRenderer.c
│       └── Renderer.c
├── Makefile
└── README.md
```

## 🧮 Scoring

| Action | Points |
|--------|--------|
| Soft drop (per row) | `1 × level` |
| Hard drop (per row) | `2 × level` |
| Single (1 line) | `100 × level` |
| Double (2 lines) | `300 × level` |
| Triple (3 lines) | `500 × level` |
| Tetris (4 lines) | `800 × level` |

## 🚧 Roadmap

- [x] Core Tetris gameplay
- [x] Hold piece
- [x] Next piece queue (5 pieces)
- [x] Ghost piece
- [x] Main menu
- [ ] Leaderboard / high score persistence
- [ ] Sound effects
- [ ] Linux / macOS support

## 📄 License

MIT License — feel free to use, modify, and distribute.
