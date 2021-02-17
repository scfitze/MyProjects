//Sean Fitze
//Player.cpp
#include <iostream>
#include <string>
#include "Player.h"


/***
 * Constructor for Player Class
 * sets name, points, position, and human status of player
 * @param name string name of the player
 * @param is_human bool true if player is human false otherwise
 */
Player::Player (const std::string name, const bool is_human) {
    name_ = name;
    points_ = 0;
    is_human_ = is_human;
    pos_.row = 0;
    pos_.col = 0;
}

/***
 * Update the points_ value according to the int passed in
 * @param x const int to add the value of points to 
*/
void Player::ChangePoints(const int x) {
    points_ += x;
}

/***
 * Updates the Player's pos_ to the new Position
 * @param a position to change to
 */
void Player::SetPosition(Position pos) {
    pos_.row = pos.row;
    pos_.col = pos.col;
}

/***
 * Translate the other position into a direction relative to the Player by comparing other with pos_
 * @param other Position struct relative to players position
 * @return string of position relative to the player
 */ 
std::string Player::ToRelativePosition(Position other) {
    if (other.row -1 == pos_.row) {
        return "DOWN";
    }
    else if (other.row +1 == pos_.row) {
        return "UP";
    }
    else if (other.col -1 == pos_.col) {
        return "RIGHT";
    }
    else if (other.col +1 == pos_.col) {
        return "LEFT";
    }
    else {
        return "NOWHERE";
    }
}


/***
 * Convert this player to a string representation of their name and points
 * @param os output stream to output the player stats
 * @param b const Player address of the player that will be displayed
 * @return the output stream containing the string to output
 */
std::ostream& operator<<(std::ostream& os, const Player &b) {
    os << b.name_ << " has " << b.points_ << " points" << "." << std::endl;;
    return os;
}