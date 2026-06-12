#ifndef TETROMINO_H
#define TETROMINO_H

#pragma region ENUMS
typedef enum {
    TET_I = 0,
    TET_O = 1,
    TET_T = 2,
    TET_S = 3,
    TET_Z = 4,
    TET_J = 5,
    TET_L = 6
} TetrominoType;
#pragma endregion

#pragma region STRUCT
typedef struct {
    int shape[4][4];
} Rotation;

typedef struct {
    Rotation rotations[4];
    int color;
} Tetromino;
#pragma endregion

#pragma region TETROMINO SHAPES
extern const Tetromino tet_i;
extern const Tetromino tet_o;
extern const Tetromino tet_t;
extern const Tetromino tet_s;
extern const Tetromino tet_z;
extern const Tetromino tet_j;
extern const Tetromino tet_l;
extern const Tetromino tetrominoes[7];
#pragma endregion

#pragma region HELPER
const Tetromino* get_tetromino(int type);
const Tetromino* get_tetromino_by_type(TetrominoType type);
void get_rotation_shape(const Tetromino* t, int rotation, int output[4][4]);
#pragma endregion

#endif