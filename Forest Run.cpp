#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

// Structure to represent a player
struct Player {
    string name;
    int position;
    char symbol;
};

// Function to generate a random number between min and max (inclusive)
int rollDice(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Function to check if a given position is occupied by any player
bool isPositionOccupied(const vector<Player>& players, int position) {
    for (const auto& player : players) {
        if (player.position == position) {
            return true;
        }
    }
    return false;
}

// Function to move a player on the board based on the dice roll
void movePlayer(Player& player, int diceRoll) {
    int newPosition = player.position + diceRoll;
    if (newPosition <= 100) {
        player.position = newPosition;
    }
}

// Function to apply the effect of a benign animal's house on a player
void applyBenignEffect(Player& player, char animal) {
    int boostPoints = 0;
    switch (animal) {
        case 'T': boostPoints = 1; break;
        case 'P': boostPoints = 3; break;
        case 'D': boostPoints = 5; break;
        case 'G': boostPoints = 15; break;
    }
    movePlayer(player, boostPoints);
}

// Function to apply the effect of a wild animal's house on a player
void applyWildEffect(Player& player, char animal) {
    int stingPoints = 0;
    switch (animal) {
        case 'B': stingPoints = 5; break;
        case 'C': stingPoints = 10; break;
        case 'S': stingPoints = 20; break;
        case 'L': stingPoints = 25; break;
    }
    movePlayer(player, -stingPoints);
}

// Function to print the current board state with players' positions
void printBoard(const vector<Player>& players) {
    cout << "-------------------------------------------------------------------------------\n";
    for (int row = 9; row >= 0; --row) {
        for (int col = 0; col < 10; ++col) {
            int position = row * 10 + col + 1;
            char symbol = ' ';
            for (const auto& player : players) {
                if (player.position == position) {
                    symbol = player.symbol;
                    break;
                }
            }
            cout << "| ";
            if (position < 10) {
                cout << " ";
            }
            cout << position << " ";
            if (symbol != ' ') {
                cout << "(" << symbol << ")";
            } else {
                cout << "   ";
            }
        }
        cout << "|\n";
        cout << "-------------------------------------------------------------------------------\n";
    }
}


int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    // Initialize players
    vector<Player> players;
    players.push_back({"Player 1", 1, 'R'});
    players.push_back({"Player 2", 1, 'G'});
    players.push_back({"Player 3", 1, 'B'});

    // Main game loop
    while (true) {
        // Print board state
        system("cls");
        printBoard(players);

        // Process each player's turn
        for (auto& player : players) {
            cout << player.name << ", it's your turn. Press Enter to roll the dice.";
            cin.ignore();

            // Roll the dice
            int diceRoll = rollDice(1, 6);
            cout << "You rolled a " << diceRoll << ". ";
            cin.ignore();

            // Move the player
            movePlayer(player, diceRoll);
            cout << "You are now at position " << player.position << ". ";
            cin.ignore();
            
                    system("cls");
            printBoard(players);

            // Check if the player landed on an animal's house
            char animal = ' ';
            switch (player.position) {
                case 5: case 54: animal = 'T'; break;
                case 19: case 29: case 82: animal = 'P'; break;
                case 13: case 39: case 74: case 95: animal = 'D'; break;
                case 43: case 85: animal = 'G'; break;
                case 8: case 46: case 78: animal = 'B'; break;
                case 15: case 32: case 57: case 96: animal = 'C'; break;
                case 25: case 61: case 99: animal = 'S'; break;
                case 70: case 91: animal = 'L'; break;
            }

            if (animal != ' ') {
                cout << "You landed on a house of animal " << animal << ". ";
                if (animal == 'T' || animal == 'P' || animal == 'D' || animal == 'G') {
                    applyBenignEffect(player, animal);
                    cout << "You received a boost!\n";
                } else {
                    applyWildEffect(player, animal);
                    cout << "You got stung and moved backward!\n";
                }
            }

            // Check if the player reached the destination
            if (player.position == 100) {
                cout << player.name << " reached the destination!\n";
                players.erase(players.begin()); // Remove the finished player
            }
        }

        // Check if all players finished
        if (players.size() == 1) {
            cout << "Congratulations, " << players[0].name << "! You are the winner!\n";
            break;
        }
    }

    return 0;
}