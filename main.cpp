#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "functions.h"
#include <limits>

using namespace std;

int main() {
    LinkedList gameQueue;
    vector<Game> games = loadGames("games.txt", gameQueue);
    int choice;
    bool exit = false;
    while (!exit) {
        cout << "\nGame Organizer Menu:\n";
        cout << "1. Print all games\n";
        cout << "2. Rate a game\n";
        cout << "3. Sort by rate\n";
        cout << "4. Generate random game\n";
        cout << "5. Digital or Physical\n";
        cout << "6. Sort by genre\n";
        cout << "7. Add new game to the library\n";
        cout << "8. Search by first letter\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;
        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid choice selected, please pick one of the numbers listed." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                for (const auto& game : games) {
                    cout << "Name: " << game.getName() << endl;
                }
                break;
            case 2:
                {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    string gameName;
                    int rating;
                    cout << "Enter game name: ";
                    getline(cin, gameName);
                    cout << "Enter rating (0-5): ";
                    cin >> rating;
                    rateGame(games, gameName, rating);
                    break;
                }
            case 3:
                int rating;
                cout << "Please enter the rating of games you are looking for from 0-5: ";
                cin >> rating;
                printGamesWithRating(games, rating);
                break;
            case 4:
                //this is the one that utilizes the linked list queue
                if (!gameQueue.listIsEmpty()) {
                    Game randomGame = gameQueue.peek(); 
                    cout << "Random Game: " << randomGame.getName() << ", " << randomGame.getGenre() << endl;
                    gameQueue.delElement(); 
                    gameQueue.addElement(randomGame); 
                }
                else {
                    cout << "No more games in the queue." << endl;
                }
                break;
            case 5:
                int typeChoice;
                cout << "Enter 1 for Digital games, 2 for Physical games: ";
                cin >> typeChoice;
                printGamesByType(games, typeChoice);
                break;
            case 6:
                printGamesByGenre(games);
                break;
            case 7:
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                addGameToLibrary(games, "games.txt");
                break;
            case 8:
                searchGamesByFirstLetter(games);
                break;
            case 9:
                exit = true;
                break;
            default:
                cout << "Invalid choice selected, please pick one of the numbers listed." << endl;
        }
    }

    return 0;
}
   


