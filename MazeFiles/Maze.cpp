//Sean Fitze
//Maze.cpp
#include "Maze.h"
#include <iostream>
#include <string>
/***
 * Returns a string representation of a given SquareType
 * @param sq square type to stringify
 * @return a string representation of the SquareType
 */ 
std::string SquareTypeStringify(SquareType sq) {
	std::string str = "";
    if (sq == SquareType::Wall) {
        str = "🏯";
    }
    if (sq == SquareType::Empty) {
        str = "🌌";
    }
    if (sq == SquareType::Exit) {
        str = "🧿";
    }
    if (sq == SquareType::Human) {
        str = "🥺";
    }
    if (sq == SquareType::Enemy) {
        str = "🦠";
    }
    if (sq == SquareType::Treasure) {
        str = "🎁";
    }
    return str;
}

////////////////////////////////////////////////////////////////
// //Board
////////////////////////////////////////////////////////////////

// Board constructor
Board::Board() {
    int rand = std::rand() % 10 + 1;  //generate random number
    srand(time(NULL));
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            if (i == 0 && j == 0) {
                arr_[i][j] = SquareType::Human; //sets human position (0,0)
            }
            else if (i == rows_ -1 && j == cols_ -1) {
                arr_[i][j] = SquareType::Exit; //sets Exit position (row,col)
            }
            else {
                rand = std::rand() % 10 + 1;  //generate random number
                if (rand == 1) {
                    arr_[i][j] = SquareType::Treasure;
                }
                else if (rand ==  9 || rand == 10) {
                    arr_[i][j] = SquareType::Wall;
                }
                else {
                    arr_[i][j] = SquareType::Empty; //sets every other square
                }
            }
        }
    }
}

/***
 * Gets the Square type of a position on the Board
 * @param pos position to look on the Board
 * @return a SquareType on that position 
 */
SquareType Board::get_square_value(Position pos) const {
    return arr_[pos.row][pos.col];
}

/*** 
 * Sets the value of a square to the given SquareType
 * @param pos position to set value to
 * @param value value to set position to
 */
void Board::SetSquareValue(Position pos, SquareType value) {
    arr_[pos.row][pos.col] = value;
}


/***
 * Gets the possible Positions that a Player could move to
 * (not on the board or into a wall)
 * @param p pointer to a Player
 * @return a vector of the possible Positions
 */ 
std::vector<Position> Board::GetMoves(Player *p) {
    std::vector<Position> moves;
    Position temp = p->get_position();
    // Check which directions are off the board
    bool up = true;
    bool down = true;
    bool left = true;
    bool right = true;
    if (temp.row == 0) {
        up = false;
    }
    if (temp.row == rows_ -1) {
        down = false;
    }
    if (temp.col == 0) {
        left = false;
    }
    if (temp.col == cols_ -1) {
        right = false;
    }

    bool nomoves = true;
    //check remaining squares and if they are valid
    if (up == true) {
        if (arr_[temp.row-1][temp.col] != SquareType::Wall) {
            temp.row --;
            moves.push_back(temp);
            temp = p->get_position();
            nomoves = false;
        }
    }
    if (down == true) {
        if (arr_[temp.row+1][temp.col] != SquareType::Wall) {
            temp.row ++;
            moves.push_back(temp);
            temp = p->get_position();
            nomoves = false;
        }
    }
    if(right == true) {
        if (arr_[temp.row][temp.col+1] != SquareType::Wall) {
            temp.col ++;
            moves.push_back(temp);
            temp = p->get_position();
            nomoves = false;
        }
    }
    if (left == true) {
        if (arr_[temp.row][temp.col-1] != SquareType::Wall) {
            temp.col --;
            moves.push_back(temp);
            temp = p->get_position();
            nomoves = false;
        }
    }
    if (nomoves == true) {
        moves.push_back(p->get_position());
    }
    
    //check if player hits goes off the board or not
    return moves;
}

/***
 * Move a player to a new position on the board
 * @param p pointer to a Player
 * @param pos position to move to
 * @return true if they moved successfully, false otherwise
 */
bool Board::MovePlayer(Player *p, Position pos) {
    //edge case cant move
    if (p->get_position() == pos) {
        return true;
    }
    bool moved = false;
    
    if (this->get_square_value(pos) == SquareType::Empty || this->get_square_value(pos) == SquareType::Treasure || this->get_square_value(pos) == SquareType::Exit) {
        //update position
        if (this->get_square_value(pos) == SquareType::Treasure) {
            p->ChangePoints(100);
        }
        //if enemy 
        if (!p->is_human()) {
            //special case if enemy is on the exit keep the exit square the same
            if (p->get_position().row == rows_ -1 && p->get_position().col == cols_ -1) {
                this->SetSquareValue(p->get_position(), SquareType::Exit);
            }
            //else enemy is not on exit square
            else {
                this->SetSquareValue(p->get_position(), SquareType::Empty);
            }
            p->SetPosition(pos);
            this->SetSquareValue(pos, SquareType::Enemy);
            moved = true;
        }
        //if human
        else {
            this->SetSquareValue(p->get_position(), SquareType::Empty);
            p->SetPosition(pos);
            this->SetSquareValue(pos, SquareType::Human);
            moved = true;
        }
    }
    //if enemy hits player
    if (this->get_square_value(pos) == SquareType::Human && !p->is_human()) {
        this->SetSquareValue(p->get_position(), SquareType::Empty);
        p->SetPosition(pos);
        this->SetSquareValue(pos, SquareType::Enemy);
        moved = true;
    }
    //special case if enemy on enemy or human on enemy
    if (this->get_square_value(pos) == SquareType::Enemy) {
        //if it is a enemy do nothing
        if (!p->is_human()) {
            moved = true;
        }
        //else update normally
        else {
            this->SetSquareValue(p->get_position(), SquareType::Empty);
            p->SetPosition(pos);
            this->SetSquareValue(pos, SquareType::Human);
            moved = true;
        }
    }
    return moved;
}

/***
 * Get the square type of the exit square
 * @return returns the square type of the exit square 
 */
SquareType Board::GetExitOccupant() {
    return arr_[rows_-1][cols_-1];
}

//Overrides operator<< for board
std::ostream& operator<<(std::ostream& os, const Board &b) {
    Position tmp;
    tmp.row = 0;
    tmp.col = 0;
    for (int i = 0; i < b.get_rows(); i++) {
        for (int j = 0; j < b.get_cols(); j++) {
            tmp.row = i;
            tmp.col = j;
            os << SquareTypeStringify(b.get_square_value(tmp));
        }
        os << std::endl;
    }
    return os;
}


////////////////////////////////////////////////////////////////
// //Maze
////////////////////////////////////////////////////////////////

//Maze constructor
Maze::Maze() {
    board_ = new Board;
    //sets spawn points for the enemies
    Position spawn;
    for (int i = 1; i < board_->get_rows(); i++) {
        for (int j = 1; j < board_->get_cols(); j++) {
            spawn.row = i;
            spawn.col = j;
            if (board_->get_square_value(spawn) == SquareType::Empty) {
                spawnPoints_.push_back(spawn);
            }
        }
    }

    //turn count
    turn_count_ = 0;
    ai_ = true; //default
}

//Maze Destructor
Maze::~Maze() {
    delete board_;
}

/***
 * Generates a new board based off the user input
 */
void Maze::GenerateNewBoard() {
    delete board_;
    board_ = new Board;
    spawnPoints_.clear();
    Position spawn;
    for (int i = 1; i < board_->get_rows(); i++) {
        for (int j = 1; j < board_->get_cols(); j++) {
            spawn.row = i;
            spawn.col = j;
            if (board_->get_square_value(spawn) == SquareType::Empty) {
                spawnPoints_.push_back(spawn);
            }
        }
    }

}

/***
 * Initialize a new game, given one human player and a number of enemies to generate
 * @param human a human to generate
 * @param enemies number of enemies to generate
 */
void Maze::NewGame(Player *human, const int enemies) {
    turn_count_ = 0; 
    std::cout << *board_ << std::endl;
    std::string successfully ="";
    while (successfully != "y") {
        std::cout << "Has the board generated successfully? [y]es [n]o: ";
        std::cin >> successfully;
        //gnerate new board if the board is not successfully generated
        if (successfully == "n") {
            this->GenerateNewBoard();
            std::cout << "Generating new board... " << std::endl << *board_ << std::endl;
        }
        else if (successfully != "y") {
            std::cout << "Invalid command." << std::endl;
        }
    }
    
    //player generate
    players_.push_back(human);
    // //generate enemeies
     //initialize enemies and draw enemies
    for (int i = 0; i < enemies; i++) {
        Player* tmp = new Player("Enemy" + std::to_string(i), false);
        tmp->SetPosition(spawnPoints_[i]);
        board_->SetSquareValue(spawnPoints_[i], SquareType::Enemy);
        players_.push_back(tmp);
    }
    //ask if user wants ai on or not
    bool leave = false;

    while (!leave) {
        std::cout << "Would you like to play with computers? [y]es [n]o: ";
        std::cin >> successfully;
        if (successfully == "n") {
            std::cout << "No computers added this game." << std::endl;   
            ai_ = false;
            leave = true;
        }
        else if (successfully == "y") {
            std::cout << "Computers will be added." << std::endl;
            ai_ = true;
            leave = true;
        }
        else {
            std::cout << "Invalid Input." << std::endl;
        }
    }
    
    //start game
    while (!this->IsGameOver()) {
        if (turn_count_ == players_.size()) {
            turn_count_ = 0;
        }
        std::cout << *board_ << std::endl;
        if (!players_[turn_count_]->is_human() && ai_ == true)
        {
            this->TakeTurnAi(players_[turn_count_], players_[0]->get_position());
        }
        else {
            this->TakeTurn(players_[turn_count_]);
        }
        turn_count_ ++;

    }
    //std::cout << this << std::endl;
    std::cout << this->GenerateReport() << std::endl;

}

//Helper to lowercase vec
/***
 * Helper function to check if input is lowercase characters
 * @param vec a vector of uppercase strings to convert to lowercase
 * @return a vector of lowercase strings
 */
std::vector<std::string> toLowerHelper(const std::vector<std::string> vec) {
    std::vector<std::string> lowerVec;
    for (unsigned int i = 0; i < vec.size(); i++) {
        if (vec[i] == "UP"){
            lowerVec.push_back("up");
        }
        else if (vec[i] == "DOWN"){
            lowerVec.push_back("down");
        }
        else if (vec[i] == "RIGHT") {
            lowerVec.push_back("right");
        }
        else if (vec[i] == "LEFT") {
            lowerVec.push_back("left");
        }
        else if (vec[i] == "NOWHERE") {
            lowerVec.push_back("nowhere");
        }
    }
    return lowerVec;
}

/***
 * Have the player take their turn;
 * @param p player to take their turn
 */
void Maze::TakeTurn(Player *p) {
    std::cout << p->get_name() << " can go: ";
    std::string choice;
    std::vector<Position> vec = board_->GetMoves(p); //vector of moves player can get
    std::vector<std::string> str_vec; //vector of string moves
    //get moves
    for (unsigned int i = 0; i < vec.size(); i++) {
        std::cout << p->ToRelativePosition(vec[i]) << " "; 
        str_vec.push_back(p->ToRelativePosition(vec[i]));
    }
    std::cout << std::endl;

    std::vector<std::string>str_lowerVec = toLowerHelper(str_vec);
    bool moved = false;
    while(!moved) {
        //move player
        std::cout << "Please enter your choice: ";
        std::cin >> choice;
        bool correctChoice = false;
        int pos_index = 0;
        for (unsigned int i = 0; i < str_vec.size(); i++) {
            if (choice == str_vec[i] || choice == str_lowerVec[i]) {
                correctChoice = true;
                pos_index = i;
            }
        }
        if (correctChoice == true) {
            moved = board_->MovePlayer(p, vec[pos_index]);
        }
        else {
            std::cout << "Invalid move." << std::endl;
        }
    }
}

/***
 * Take turn for the ai
 * @param p enemy to take turn for
 * @return true if moved successfully
 */
void Maze::TakeTurnAi(Player *p, Position pos) {
    std::vector<Position> vec = board_->GetMoves(p); //vector of moves enemy can take
    std::vector<Position> modified_vec;
    //try to locate player 
    for (unsigned int i = 0; i < vec.size(); i++) {
        if (vec[i].row == pos.row || vec[i].col == pos.col) {
            modified_vec.push_back(vec[i]);
        }
    }
    //if found a modified move pick from it
    if (modified_vec.size() > 0) {
        srand(time(NULL));
        int rand = std::rand() % vec.size();  //generate random number
        board_->MovePlayer(p, vec[rand]); 
    }
    //if not pick from all moves
    srand(time(NULL));
    int rand = std::rand() % vec.size();  //generate random number
    board_->MovePlayer(p, vec[rand]);
}

/***
 * Tells if game is over
 * @return true if the human made it to the exit
 * or the enemies ate all the humans
 */
bool Maze::IsGameOver() {
    if (board_->GetExitOccupant() == SquareType::Human) {
        //if human is on exit position game over
        return true;
    }
    //if human or enemy are on the same position game over
    for (unsigned int i = 1; i < players_.size(); i++) {
        if (players_[0]->get_position() == players_[i]->get_position()) {
            return true;
        }
    }
    return false;
}

/***
 * Generates game end report
 */
std::string Maze::GenerateReport() {
    std::cout << *board_ << std::endl;
    for (unsigned int i = 0; i < players_.size(); i++) { //displays players scores
        std::cout << *players_[i];
    }
    std::cout << std::endl;
    return "Game End";
}