#include <iostream>
#include <optional>
#include <string>

using namespace std;

enum class selection {
    rock, paper, scissor, invalid
};

class Player {
    public: string name;
    public: selection playerSelection;

    Player(string playerName) : name(playerName) {}
};

int encodeSelections(selection firstSelection, selection secondSelection) {
    return static_cast<int>(firstSelection) * 10 + static_cast<int>(secondSelection);
}

void printUserSelection(selection userSelection) {
    switch(userSelection) {
	case selection::rock: 
	    cout << "You chose rock." << endl;
	    break;
	case selection::paper:
	    cout << "You chose paper." << endl;
	    break;
	case selection::scissor: 
	    cout << "You chose scissors." << endl;
	    break;
	default: 
	    cout << "Invalid input. Please enter 'r', 'p', or 's'." << endl;
	    break;
    }
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
    cout << "Want to play again? (Y/N)" << endl;
    char continueInput;
    cin >> continueInput;
    if (continueInput == 'y' || continueInput == 'Y') {
	*gameOngoing = true;
    } else {
	*gameOngoing = false;
    }
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
            return std::nullopt;

        default:
            return std::nullopt;
    }
}

void playerRound(Player *player) {
    char userInput;

    cout << player->name << ", choose your input:" << endl;
    cout << "r: Rock" << endl;
    cout << "p: Paper" << endl;
    cout << "s: Scissors" << endl;

    cin >> userInput;
    setSelection(userInput, &(player->playerSelection));
    printUserSelection(player->playerSelection);
    cout << "----" << endl;
}

void gameRound(int *currentRound, Player *firstPlayer, Player *secondPlayer) {
    cout << "Round: " << *currentRound << endl;
    playerRound(firstPlayer);
    playerRound(secondPlayer);

    std::optional<Player*> winnerOptional = returnRoundWinner(firstPlayer, secondPlayer);
    if (winnerOptional.has_value()) {
        Player* winner = winnerOptional.value();
        cout << winner->name << " wins the round!" << endl;
        (*currentRound)++;
    } else {
        cout << "No winner this round." << endl;
        cout << "----" << endl;
    }
}

int main() {
    Player firstPlayer("Kim");
    Player secondPlayer("Robot");
    bool gameOngoing = true;

    while(gameOngoing) {
        int rounds = 3;
        int currentRound = 0;

        while(currentRound < rounds) {
            gameRound(&currentRound, &firstPlayer, &secondPlayer);
        }
        continueGameSelection(&gameOngoing);
    }
    
    return 0;
}
