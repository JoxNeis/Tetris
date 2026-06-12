#include <Tetromino.h>

#pragma region STRUCT

typedef struct {
    int shape[4][4];
} Rotation;

typedef struct {
    Rotation rotations[4];
    int color;
} Tetromino;

#pragma endregion

#pragma region I
// I piece (Cyan)
const Tetromino tet_i = {
    .rotations = {
        { // Rotation 0
            .shape = {
                {0,0,0,0},
                {1,1,1,1},
                {0,0,0,0},
                {0,0,0,0}
            }
        },
        { // Rotation 90
            .shape = {
                {0,0,1,0},
                {0,0,1,0},
                {0,0,1,0},
                {0,0,1,0}
            }
        },
        { // Rotation 180
            .shape = {
                {0,0,0,0},
                {0,0,0,0},
                {1,1,1,1},
                {0,0,0,0}
            }
        },
        { // Rotation 270
            .shape = {
                {0,1,0,0},
                {0,1,0,0},
                {0,1,0,0},
                {0,1,0,0}
            }
        }
    },
    .color = 1  // Cyan
};
#pragma endregion
#pragma region O
// O piece (Yellow)
const Tetromino tet_o = {
    .rotations = {
        { // All rotations same for square
            .shape = {
                {0,0,0,0},
                {0,1,1,0},
                {0,1,1,0},
                {0,0,0,0}
            }
        },
        {
            .shape = {
                {0,0,0,0},
                {0,1,1,0},
                {0,1,1,0},
                {0,0,0,0}
            }
        },
        {
            .shape = {
                {0,0,0,0},
                {0,1,1,0},
                {0,1,1,0},
                {0,0,0,0}
            }
        },
        {
            .shape = {
                {0,0,0,0},
                {0,1,1,0},
                {0,1,1,0},
                {0,0,0,0}
            }
        }
    },
    .color = 2  // Yellow
};

#pragma endregion
#pragma region T
// T piece (Purple)
const Tetromino tet_t = {
    .rotations = {
        { // Rotation 0
            .shape = {
                {0,0,0,0},
                {0,1,0,0},
                {1,1,1,0},
                {0,0,0,0}
            }
        },
        { // Rotation 90
            .shape = {
                {0,0,0,0},
                {0,1,0,0},
                {0,1,1,0},
                {0,1,0,0}
            }
        },
        { // Rotation 180
            .shape = {
                {0,0,0,0},
                {0,0,0,0},
                {1,1,1,0},
                {0,1,0,0}
            }
        },
        { // Rotation 270
            .shape = {
                {0,0,0,0},
                {0,1,0,0},
                {1,1,0,0},
                {0,1,0,0}
            }
        }
    },
    .color = 3  // Purple
};

#pragma endregion
#pragma region S
// S piece (Green)
const Tetromino tet_s = {
    .rotations = {
        { // Rotation 0
            .shape = {
                {0,0,0,0},
                {0,1,1,0},
                {1,1,0,0},
                {0,0,0,0}
            }
        },
        { // Rotation 90
            .shape = {
                {0,0,0,0},
                {0,1,0,0},
                {0,1,1,0},
                {0,0,1,0}
            }
        },
        { // Rotation 180
            .shape = {
                {0,0,0,0},
                {0,0,0,0},
                {0,1,1,0},
                {1,1,0,0}
            }
        },
        { // Rotation 270
            .shape = {
                {1,0,0,0},
                {1,1,0,0},
                {0,1,0,0},
                {0,0,0,0}
            }
        }
    },
    .color = 4  // Green
};

#pragma endregion
#pragma region Z
// Z piece (Red)
const Tetromino tet_z = {
    .rotations = {
        { // Rotation 0
            .shape = {
                {0,0,0,0},
                {1,1,0,0},
                {0,1,1,0},
                {0,0,0,0}
            }
        },
        { // Rotation 90
            .shape = {
                {0,0,0,0},
                {0,0,1,0},
                {0,1,1,0},
                {0,1,0,0}
            }
        },
        { // Rotation 180
            .shape = {
                {0,0,0,0},
                {0,0,0,0},
                {1,1,0,0},
                {0,1,1,0}
            }
        },
        { // Rotation 270
            .shape = {
                {0,1,0,0},
                {1,1,0,0},
                {1,0,0,0},
                {0,0,0,0}
            }
        }
    },
    .color = 5  // Red
};

#pragma endregion
#pragma region J
// J piece (Blue)
const Tetromino tet_j = {
    .rotations = {
        { // Rotation 0
            .shape = {
                {0,0,0,0},
                {1,0,0,0},
                {1,1,1,0},
                {0,0,0,0}
            }
        },
        { // Rotation 90
            .shape = {
                {0,0,0,0},
                {0,1,1,0},
                {0,1,0,0},
                {0,1,0,0}
            }
        },
        { // Rotation 180
            .shape = {
                {0,0,0,0},
                {0,0,0,0},
                {1,1,1,0},
                {0,0,1,0}
            }
        },
        { // Rotation 270
            .shape = {
                {0,1,0,0},
                {0,1,0,0},
                {1,1,0,0},
                {0,0,0,0}
            }
        }
    },
    .color = 6  // Blue
};

#pragma endregion
#pragma region L
// L piece (Orange)
const Tetromino tet_l = {
    .rotations = {
        { // Rotation 0
            .shape = {
                {0,0,0,0},
                {0,0,1,0},
                {1,1,1,0},
                {0,0,0,0}
            }
        },
        { // Rotation 90
            .shape = {
                {0,0,0,0},
                {0,1,0,0},
                {0,1,0,0},
                {0,1,1,0}
            }
        },
        { // Rotation 180
            .shape = {
                {0,0,0,0},
                {0,0,0,0},
                {1,1,1,0},
                {1,0,0,0}
            }
        },
        { // Rotation 270
            .shape = {
                {1,1,0,0},
                {0,1,0,0},
                {0,1,0,0},
                {0,0,0,0}
            }
        }
    },
    .color = 7  // Orange
};

#pragma endregion

#pragma region  TETROMINO ARRAY
const Tetromino tetrominoes[7] = {
    tet_i,  // 0
    tet_o,  // 1
    tet_t,  // 2
    tet_s,  // 3
    tet_z,  // 4
    tet_j,  // 5
    tet_l   // 6
};
#pragma endregion

#pragma region HELPER
const Tetromino* get_tetromino(int type) {
    return &tetrominoes[type % 7];
}

void get_rotation_shape(const Tetromino* t, int rotation, int output[4][4]) {
    if (rotation >= 0 && rotation < 4) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                output[i][j] = t->rotations[rotation].shape[i][j];
            }
        }
    }
}

const Tetromino* get_tetromino_by_type(TetrominoType type) {
    return get_tetromino((int)type);
}
#pragma endregion