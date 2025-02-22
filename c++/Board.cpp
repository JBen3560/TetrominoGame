#include "Board.h"

Board::Board(int x, int y){
    // Create the board
    for(int i = 0; i < y; i++){
        vector<GridSquare> row;
        for(int j = 0; j < x; j++){
            GridSquare square;
            row.push_back(square);
        }
        board.push_back(row);
    }
}

void Board::print(){
    cout << "\n\tI: " << Icount << " \tL: " << Lcount << "\tT: " << Tcount << "\tS: " << Scount << "\tO: " << Ocount << endl;
    cout << "\n   ";
    for(vInt i = 0; i < board[0].size(); i++){
        cout << i;
        if(i < 10) cout << " ";
        cout << " ";
    }
    cout << endl;
    for(vInt i = 0; i < board.size(); i++){
        cout << i;
        if(i < 10) cout << " ";
        cout << " ";
        for(vInt j = 0; j < board[i].size(); j++){
            board[i][j].print();
            cout << "  ";
        }
        cout << endl;
    }
}

bool Board::isValidInput(const string& input, int& r, int& c) {
    istringstream iss(input);
    if (iss >> r >> c) {
        string leftover;
        if (!(iss >> leftover)) {  // Ensure no extra characters remain
            return true;
        }
    }
    return false;
}

bool Board::checkWin(){
    for(vInt i = 0; i < board.size(); i++){
        for(vInt j = 0; j < board[i].size(); j++){
            if(board[i][j].getDisplay() == '.' || board[i][j].getDisplay() == 'X') return false;
        }
    }
    cout << "\nCongratulations! You have filled the board!" << endl;
    return true;
}

char Board::placeTetromino(int r, int c, vector<pair<int, int>> &visited){
    // Check if the square is already visited
    bool found = false;
    for(vInt i = 0; i < visited.size(); i++){
        if(visited[i].first == r && visited[i].second == c) found = true;
    }

    // Fill the square
    

    if(!found){
        cout << "not found r: " << r << " c: " << c << endl;

        // Check neighbors
        bool nor = (r > 0 && board[r-1][c].getDisplay() == 'X');
        bool sou = (r < board.size()-1 && board[r+1][c].getDisplay() == 'X');
        bool eas = (c < board[0].size()-1 && board[r][c+1].getDisplay() == 'X');
        bool wes = (c > 0 && board[r][c-1].getDisplay() == 'X');

        // Add selected square to visited
        board[r][c].setDisplay('X');
        visited.push_back(make_pair(r, c));

        // Determine the tetromino
        if(visited.size() == 4){
            string tetromino = "";
            for(vInt i = 0; i < visited.size(); i++){
                // Check neighbors
                int count = 0;
                int vR = visited[i].first;
                int vC = visited[i].second;
                bool vNor = (vR > 0 && board[vR-1][vC].getDisplay() == 'X');
                bool vSou = (vR < board.size()-1 && board[vR+1][vC].getDisplay() == 'X');
                bool vEas = (vC < board[0].size()-1 && board[vR][vC+1].getDisplay() == 'X');
                bool vWes = (vC > 0 && board[vR][vC-1].getDisplay() == 'X');
                if(vNor) count++;
                if(vSou) count++;
                if(vEas) count++;
                if(vWes) count++;

                // Set the grid space type
                if(count >= 3){
                    board[vR][vC].setType('A');
                }
                else if(count == 2){
                    if((vNor && vSou) || (vEas && vWes)){
                        board[vR][vC].setType('B');
                    } else {
                        board[vR][vC].setType('C');
                    }
                }
                else if(count == 1){
                    board[vR][vC].setType('E');
                }
                else {
                    board[vR][vC].setType('X');
                }
                
                // Add to tetromino string
                tetromino += board[vR][vC].getType();
            }
            sort(tetromino.begin(), tetromino.end());

            cout << "tetromino: " << tetromino << endl;

            char display = 'X';
            if(tetromino == "AEEE") display = 'T';
            else if(tetromino == "BBEE") display = 'I';
            else if(tetromino == "BCEE") display = 'L';
            else if(tetromino == "CCEE") display = 'S';
            else if(tetromino == "CCCC") display = 'O';
            for(vInt i = 0; i < visited.size(); i++){
                board[visited[i].first][visited[i].second].setDisplay(display);
            }
            return display;
        }

        // Call neighbors
        if(nor){
            char display = placeTetromino(r-1, c, visited);
            if(display == 'L' || display == 'I' || display == 'T' || display == 'S' || display == 'O') return display;
        }
        if(sou){
            char display = placeTetromino(r+1, c, visited);
            if(display == 'L' || display == 'I' || display == 'T' || display == 'S' || display == 'O') return display;
        }
        if(eas){
            char display = placeTetromino(r, c+1, visited);
            if(display == 'L' || display == 'I' || display == 'T' || display == 'S' || display == 'O') return display;
        }
        if(wes){
            char display = placeTetromino(r, c-1, visited);
            if(display == 'L' || display == 'I' || display == 'T' || display == 'S' || display == 'O') return display;
        }
    }

    // If not enough squares to form a tetromino, return 'X'
    return 'X';
}

void Board::runGame(){
    cout << "\nYour goal is to fill the board with tetrominos. Fill grid squares in the shape" << endl;
    cout << "of a tetromino to place it. You may only reuse a tetromino once you have used all" << endl;
    cout << "other tetrominos. The game ends when the board is full." << endl;
    cout << "Good luck!" << endl;

    do{
        // Print the board
        print();
        
        // Get and validate user input
        string input;
        int r = 0, c = 0;
        cout << "\nEnter two numbers separated by a space: ";
        getline(cin, input);
        while(!isValidInput(input, r, c) || r >= board[0].size() || c >= board.size()){
            cout << "Invalid input. Please enter two numbers separated by a space within range: ";
            getline(cin, input);
        }

        // Place the tetromino
        vector<pair<int, int>> visited;
        char type = placeTetromino(r, c, visited);
        if(type == 'I') Icount++;
        else if(type == 'L') Lcount++;
        else if(type == 'T') Tcount++;
        else if(type == 'S') Scount++;
        else if(type == 'O') Ocount;

    }while(!checkWin());

    // Print the final board
    print();
    cout << "\nThanks for playing!" << endl;
}