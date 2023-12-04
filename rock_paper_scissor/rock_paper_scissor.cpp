#include <iostream>
#include <optional>
#include <string>

using namespace std;

enum class selection {
    rock, paper, scissor, invalid
};

class Player {
    public:
        string name;
        int score;
        selection playerSelection;
        
        Player(string playerName) : name(playerName), score(0), playerSelection(selection::invalid) {}
};

int encodeSelections(selection firstSelection, selection secondSelection) {
    return static_cast<int>(firstSelection) * 10 + static_cast<int>(secondSelection);
}

string selectionToString(selection userSelection) {
    switch(userSelection) {
        case selection::rock:
            return "rock";
        case selection::paper:
            return "paper";
        case selection::scissor:
            return "scissors";
        default:
            return "invalid";
    }
}

void printUserSelection(selection userSelection) {
    switch(userSelection) {
        case selection::rock:
        case selection::paper:
        case selection::scissor:
            cout << "You chose " << selectionToString(userSelection) << "." << endl;
            break;
        default:
            cout << "Invalid input. Please enter 'r', 'p', or 's'." << endl;
            break;
    }
    cout << endl;
}

void printUserScore(Player firstPlayer, Player secondPlayer) {
    cout << "Score (" << firstPlayer.name << ":" << firstPlayer.score << " - " << secondPlayer.score << ":" << secondPlayer.name << ")" << endl;
}

void setSelection(char input, selection *selection) {
    switch(input) {
        case 'r':
            *selection = selection::rock;
            break;
        case 'p':
            *selection = selection::paper;
            break;
        case 's':
            *selection = selection::scissor;
            break;
        default:
            *selection = selection::invalid;
            break;
    }
}

void continueGameSelection(bool *gameOngoing) {
    char continueInput;
    cout << "Want to play again? (Y/N)" << endl;
    cin >> continueInput;
    
    *gameOngoing = (continueInput == 'y' || continueInput == 'Y');
}

optional<Player*> returnRoundWinner(Player* firstPlayer, Player* secondPlayer) {
    int encodedSelections = encodeSelections(firstPlayer->playerSelection, secondPlayer->playerSelection);

    switch(encodedSelections) {
        // First Player win
        case 10:
        case 02:
        case 21:
            return firstPlayer;

        // Second Player win
        case 01:
        case 20:
        case 12:
            return secondPlayer;

        // It's a tie
        case 00:
        case 11:
        case 22:
            return nullopt;

        default:
            return nullopt;
    }
}

optional<Player*> returnGameWinner(Player* firstPlayer, Player* secondPlayer) {
    if (firstPlayer->score > secondPlayer->score) {
        return firstPlayer;
    } else if (firstPlayer->score < secondPlayer->score) {
        return secondPlayer;
    }
    return nullopt;
}

void increasePlayerScore(Player *roundWinner, Player *firstPlayer, Player *secondPlayer) {
   if (roundWinner->name == firstPlayer->name) {
	    firstPlayer->score++;
	} else if (roundWinner->name == secondPlayer->name) {
	    secondPlayer->score++;
	}
}

void playerRound(Player *player) {
    char userInput;

    cout << player->name << "'s turn. Choose your input:" << endl;
    cout << "r: Rock" << endl;
    cout << "p: Paper" << endl;
    cout << "s: Scissors" << endl;

    cin >> userInput;
    setSelection(userInput, &(player->playerSelection));
    printUserSelection(player->playerSelection);
}

void gameRound(int *currentRound, Player *firstPlayer, Player *secondPlayer) {
    cout << "--- Round " << *currentRound << " ----" << endl;
    playerRound(firstPlayer);
    playerRound(secondPlayer);

    optional<Player*> roundWinnerOptional = returnRoundWinner(firstPlayer, secondPlayer);
    if (roundWinnerOptional.has_value()) {
        Player* roundWinner = roundWinnerOptional.value();

        cout << "Round " << *currentRound << " Outcome:" << endl;
        cout << firstPlayer->name << " chose " << selectionToString(firstPlayer->playerSelection) << "." << endl;
        cout << secondPlayer->name << " chose " << selectionToString(secondPlayer->playerSelection) << "." << endl;
        
        cout << endl;
        cout << roundWinner->name << " wins the Round!" << endl;
        
        increasePlayerScore(roundWinner, firstPlayer, secondPlayer);
        (*currentRound)++;
    } else {
        cout << "No winner this Round." << endl;
    }
    printUserScore(*firstPlayer, *secondPlayer);
    cout << endl;
}

void gameSession(bool *gameOngoing, Player *firstPlayer, Player *secondPlayer) {
    int rounds = 3;
    int currentRound = 0;

    while(currentRound < rounds) {
        gameRound(&currentRound, firstPlayer, secondPlayer);
    }
    
    optional<Player*> gameWinnerOptional = returnGameWinner(firstPlayer, secondPlayer);
    if (gameWinnerOptional.has_value()) {
        Player* gameWinner = gameWinnerOptional.value();
        cout << gameWinner->name << " wins the Game!!!" << endl;
    } else {
        cout << "No winner this Game." << endl;
        cout << "----" << endl;
    }
    
    continueGameSelection(gameOngoing);
}

int main() {
    Player firstPlayer("Kim");
    Player secondPlayer("Robot");
    bool gameOngoing = true;

    while(gameOngoing) {
        gameSession(&gameOngoing, &firstPlayer, &secondPlayer);
    }
    
    return 0;
}
