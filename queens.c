#include <stdio.h>
#include <stdlib.h>

static size_t sol_count = 0;

/* given specific position, detect if collided with previous positions
   input row should be encoded with (1 << row)
   return 1 if collided, 0 if not */
size_t collide(size_t column, size_t row, size_t *map)
{
    size_t collide_detect_mask = 0;

    size_t horizonal_collide = 0;
    size_t slash_collide = 0;
    size_t backslash_collide = 0;

    for (int i = 0; i < column; i++) {
        horizonal_collide = map[i];
        slash_collide = map[i] >> (column - i);
        backslash_collide = map[i] << (column - i);
        collide_detect_mask |= (horizonal_collide | slash_collide | backslash_collide);
    }
    
    return collide_detect_mask & row;
}

void nonrecursive_solver(size_t number)
{
    /* map is the row array, each with (1 << row) */
    size_t *map;
    map = malloc(sizeof(size_t) * number);
    
    for (int i = 0; i < number; i++) {
        map[i] = 0;
    }

    /* only row is in 2's power form */
    unsigned int row = 1;
    unsigned int column = 0;

    while (column < number) {
        while (row < (1 << number)) {
            /* if not collided */
            if (!collide(column, row, map)) {
                /* reset map */
                map[column] |= row;
                row = 1;
                break;
            } else {
                /* if collided, find another */
                row = row << 1;
            }
        }

        /* if no available position left */
        if (!map[column]) {
            /* exit if in the first column */
            if (column == 0) {
                break;
            } else {
            /* return to previous column and find another */
                column--;
                row = map[column] << 1;
                map[column] = 0;
                continue;
            }
        }

        /* if we found an available position */
        /* if it is the last column */
        if (column == number - 1) {
            /* solution count increase */
            sol_count++;
            /* set row to the next row */
            row = map[column] << 1;
            /* reset map */
            map[column] = 0;
            continue;
        } else {
            /* if not the last column, then keep move on */
            column++;
        }
    }
    free(map);
}

void solve_queens(size_t number)
{
    nonrecursive_solver(number);
    printf("solutions = %lu\n", sol_count);
}

int main()
{
    solve_queens(8);
    return 0;
}