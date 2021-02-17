
/**
Sean Fitze
Homework 1
Main file 
*/
#include <iostream>
#include <string>
#include "Maze.h"

using namespace std;


int main (int argc, char* argv[]) {
    
    //initialize
    
    /*
    //cout << m.get_name() << " " << m.get_points() << " ";
    //cout << m.is_human() << endl;
    //cout and change points
    cout << m << endl;
    m.ChangePoints(69);
    cout << "Now " << m << endl;

    //set pos
    cout << m.get_position().row << " ";
    cout << m.get_position().col << endl;
    Position nw;
    nw.row = 3;
    nw.col = 2;

    m.SetPosition(nw);
    cout << m.get_position().row << " ";
    cout << m.get_position().col << endl;
    Position tmp;
    tmp.row = 4;
    cout << m.ToRelativePosition(tmp) << endl;
    tmp.row = 2;
    cout << m.ToRelativePosition(tmp) << endl;
    tmp.col = 3;
    tmp.row = 0;
    cout << m.ToRelativePosition(tmp) << endl;
    tmp.col = 1;
    cout << m.ToRelativePosition(tmp) << endl;
    */

    
    //testing getting and setting square value

    
    
    //testing get and set square value
    /*
    pos.row = 0;
    pos.col = 0;
    cout << SquareTypeStringify(b.get_square_value(pos)) << endl;
    Position on_b;
    on_b.row = 2;
    on_b.col = 3;
    b.SetSquareValue(on_b, SquareType::Enemy)
    cout << b << endl;
    */

    //testing GetMoves
    
    /*
    pos.row = 0;
    pos.col = 2;
    m.SetPosition(pos);
    vector<Position> vec = b.GetMoves(&m);
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i].row << " " << vec[i].col <<endl;
    }
    cout << "size" << vec.size();
    */

    //testing MovePlayer]
    /*pos.row = 0;
    pos.col = 1;
    cout << b << endl;
    cout << m << endl;
    b.MovePlayer(&m, pos);
    cout << b << endl;
    cout << m.get_position().row << m.get_position().col << endl;
    cout << endl;
    */

    //test gget exit occupant
    /*
    pos.row = 3;
    pos.col = 3;
    cout << SquareTypeStringify(b.GetExitOccupant());
    b.SetSquareValue(pos, SquareType::Enemy);
    cout << SquareTypeStringify(b.GetExitOccupant());
    */

    
    /*Board b;
    cout << b << endl;
    Position pos;
    pos.row = 0;
    pos.col = 3;
    Player e("enemy", false);
    e.SetPosition(pos);
    std::vector<Position> test = b.GetMoves(&e);
    cout << test.size() << test[0].row << test[0].col << endl;
    cout << b.MovePlayer(&e,test[0]) << endl;
    */
    string name = "";
    string enemies = "";
    cout << "What is your name?: " << endl;
    cin >> name;
    cout << "How Many enemies? 1 - 4: " << endl;
    cin >> enemies;
    Player m(name, true);
    Maze maze;
    maze.NewGame(&m,stoi(enemies));
    
    //srand(time(NULL));
    return 0;
}