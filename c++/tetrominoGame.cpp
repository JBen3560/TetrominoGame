#include "Board.h"

/* -------------- TODO ---------------- */
// - Input validate to prevent placing on an existing piece
// - Add the id system to blocks within the same tetromino
// - Use the id system to remove tetrominos when one square is selected

int main(int argc, char* argv[]){
    vInt x = atoi(argv[1]);
    vInt y = atoi(argv[2]);
    
    if(argc != 3 || x <= 0 || y <= 0 || x * y % 4 != 0){
        cout << "Usage: " << argv[0] << " boardSizeX boardSizeY" << endl;
        cout << "boardSizeX and boardSizeY must be positive integers and their product must be divisible by 4." << endl;
        return 1;
    }
    Board board(atoi(argv[1]), atoi(argv[2]));
    board.runGame();
    return 0;
}