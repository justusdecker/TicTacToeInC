/*
This code is translated from Python to C
for more info look up: https://github.com/justusdecker/tic-tac-toe-java-and-python/blob/main/main.py
*/

#include <stdio.h>

typedef enum {false, true} bool;

bool player = false;
bool is_running = true;
char table[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
char swapper[] = {-1,1};

// Get the win status for given element. 
bool CheckSum(char points) {
    return (bool)points == 3 || points == -3;
}

void CheckWin(void) {
    

    // define the checks
    // a & b are row & columns
    // c & d are diagonals
    char w_a = 0;
    char w_b = 0;
    char w_c = 0;
    char w_d = 0;
    for (char x=0;x<3;x++) {
        // adding up diagonals
        w_c += table[x][x];
        w_d += table[2-x][2-x];
        if (!CheckSum(w_a) && !CheckSum(w_b)) {
            w_a = 0;
            w_b = 0;
            for (char y=0;y<3;y++) {
                // adding up rows & columns
                w_a += table[x][y];
                w_b += table[y][x];
            }
        }
    }
    if (CheckSum(w_a) || CheckSum(w_b) || CheckSum(w_c) || CheckSum(w_d)) {
            printf("Player %d Wins!\n", player);
            is_running = false;
            return;
        }
    
    char x;
    char y;
    char draw = 0;
    for (char w=0;w<9;w++) {
        x = w / 3;
        y = w % 3;
        if (table[x][y]) draw++;
    }
    if (draw == 9) {
        printf("Draw!\n");
        is_running = false;
    }
}

// clear input buffer
void ClearBuffer(void) {
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

bool SetPixel(void) {

    // User input validation
    char ch;

    int first = 0x30;
    int last = 0x38;

    printf("Set your position: ");
    
    do {
        if (scanf("%c",&ch) != 1) {
        printf("No input given\n");
        return false;
        }
        
        ClearBuffer();

        if (ch < first || ch > last) {

            printf("Number out of range\n");
            return false;
        }
    } while (ch == '\n');
    
    
    // Mapping

    // the input maps from 9 to 2-2 from 6 to 1-2 and so on
    char x;
    char y;
    char w = ch - first;
    x = w / 3;
    y = w % 3;
    if (table[x][y] != 0) {
        return false;
    }
    table[x][y] = swapper[player];
    printf("%d %d %d\n",w,x,y);

    return true;
}

/*
Goes trough every row & column
Checks for swapper value in it & set the drawn character to X or O
Otherwise the character will be a space
*/
void render_table(void) {
    char x;
    char y;
    for (x=0;x<3;x++) {
        for (y=0;y<3;y++) {
            char unit;
            if (table[x][y] == -1) unit = 0x58;
            else if (table[x][y] == 1) unit = 0x4F;
            else unit = 0x20;
            printf(" %c ",unit);
        }
        printf("\n");
    }
}

// Runs until one of the players wins
void update(void) {
    while (is_running) {
        bool res_ok = false;
        while (!res_ok) {
            printf("Turn of player %d\n", player);
            render_table();
            res_ok = SetPixel();
            CheckWin();
        }
        player = !player;
    }
}

int main() {
    update();
}