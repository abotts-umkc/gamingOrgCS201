#include "functions.h"

// turn a string into lowercase
string toLowercase(const string& str) {
    string lowerCaseStr;
    for (char c : str) {
        lowerCaseStr += tolower(c);
    }
    return lowerCaseStr;
}

// load games from file
vector<Game> loadGames(const string& filePath, LinkedList& gameQueue) {
    vector<Game> games;
    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return games; 
    }
    string line, name, genre, platform, type, yearStr, ratingStr;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, name, ',');
        getline(ss, genre, ',');
        getline(ss, platform, ',');
        getline(ss, type, ',');
        getline(ss, yearStr, ',');
        getline(ss, ratingStr);
        int year = stoi(yearStr);
        int rating = stoi(ratingStr);
        Game game(name, genre, platform, type, year);
        game.setRating(rating); 
        games.push_back(game);
        gameQueue.addElement(game); 
    }

    file.close(); 
    return games;
}

// rate a game
void rateGame(vector<Game>& games, const string& gameName, int rating) {
    string lowerCaseGameName = toLowercase(gameName);
    for (auto& game : games) {
        if (toLowercase(game.getName()) == lowerCaseGameName) {
            game.setRating(rating);
            cout << "Rating updated for " << gameName << endl;
            return;
        }
    }
    cout << "Game not found: " << gameName << endl;
}

//used for the search by rate
void printGamesWithRating(const vector<Game>& games, int rating) {
    const int nameWidth = 50; 
    const int genreWidth = 20; 
    cout << left << setw(nameWidth) << "Name" << setw(genreWidth) << "Genre" << endl;
    for (const auto& game : games) {
        if (game.getRating() == rating) {
            cout << left << setw(nameWidth) << game.getName() << setw(genreWidth) << game.getGenre() << endl;
        }
    }
}
//all these linkedlist functions are what make the random game option in the menu work 
// it uses a queue type of linked list to spit back out a random game
//pretend you dont know what to play this will continously spit out one random game to give you ideas from your list
void LinkedList::addElement(Game game) {
    auto newNode = make_unique<Node>(game);
    if (!head) {
        head = move(newNode);
        tail = head.get();
    }
    else {
        tail->next = move(newNode);
        tail = tail->next.get();
    }
}

Game LinkedList::peek() {
    if (listIsEmpty()) {
        throw runtime_error("List is empty");
    }
    return head->data;
}

void LinkedList::delElement() {
    if (listIsEmpty()) {
        throw runtime_error("List is empty");
    }
    head = move(head->next);
    if (!head) {
        tail = nullptr;
    }
}

void LinkedList::printList() {
    for (Node* curr = head.get(); curr != nullptr; curr = curr->next.get()) {
        cout << "Game Name: " << curr->data.getName() << ", Genre: " << curr->data.getGenre() << endl;
    }
}

bool LinkedList::listIsEmpty() {
    return head == nullptr;
}

void printGamesByType(const vector<Game>& games, int typeChoice) {
    if (typeChoice != 1 && typeChoice != 2) {
        cout << "Invalid type choice. Please enter 1 for Digital or 2 for Physical.\n";
        return;
    }
    int numOfGamesToPrint = getNumberOfGamesToPrint(); 
    const int nameWidth = 50;
    const int genreWidth = 20;
    string type = (typeChoice == 1) ? "Digital" : "Physical";
    cout << "Games of type " << type << ":\n";
    cout << left << setw(nameWidth) << "Name:" << setw(genreWidth) << "Genre:" << endl;
    int printedCount = 0;
    //i learned how to use the transform command in stack overflow researching how to handle the errors i was getting with 
    //the file not reading the information in
    //they help to get rid of blank spaces and to make character capitalization irrelevant
    for (const auto& game : games) {
        string gameType = game.getType();
        gameType.erase(0, gameType.find_first_not_of(' '));
        gameType.erase(gameType.find_last_not_of(' ') + 1);
        transform(gameType.begin(), gameType.end(), gameType.begin(),
            [](unsigned char c) { return tolower(c); });
        if (printedCount >= numOfGamesToPrint) {
            break; 
        }
        if (gameType == (typeChoice == 1 ? "digital" : "physical")) {
            cout << left << setw(nameWidth) << game.getName() << setw(genreWidth) << game.getGenre() << endl;
            printedCount++;
        }
    }
}

//this is an inner function for the digital/physical option because otherwise it will return a giant long list for all
//helps to give the user some control over how much is printing on the screen
int getNumberOfGamesToPrint() {
    while (true) { 
        cout << "Select how many games you want to print:\n";
        cout << "1 - 10 games\n";
        cout << "2 - 25 games\n";
        cout << "3 - 50 games\n";
        cout << "4 - All games\n";
        cout << "Enter your choice: ";

        int choice;
        if (cin >> choice) {
            switch (choice) {
            case 1: return 10;
            case 2: return 25;
            case 3: return 50;
            case 4: return numeric_limits<int>::max(); 
            default:
                cout << "Invalid choice, please enter a valid option.\n";
                break;
            }
        }
        else {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    }
}


void printGamesByGenre(const vector<Game>& games) {
    cout << "Select a genre:\n";
    cout << "1. RPG\n";
    cout << "2. Shooter\n";
    cout << "3. Platformer\n";
    cout << "4. Simulation\n";
    cout << "5. Racing\n";
    cout << "6. Survival\n";
    cout << "7. Adventure\n";
    cout << "8. Card\n";
    cout << "9. Board\n";
    cout << "Enter your choice: ";

    int genreChoice;
    cin >> genreChoice;
    string genre;

    switch (genreChoice) {
    case 1: genre = "rpg"; break;
    case 2: genre = "shooter"; break;
    case 3: genre = "platformer"; break;
    case 4: genre = "simulation"; break;
    case 5: genre = "racing"; break;
    case 6: genre = "survival"; break;
    case 7: genre = "adventure"; break;
    case 8: genre = "card"; break;
    case 9: genre = "board"; break;
    default:
        cout << "Invalid choice. Returning to menu.\n";
        return;
    }

    const int nameWidth = 50; 
    const int genreWidth = 30; 

    cout << "\n";
    cout << left << setw(nameWidth) << "Game:" << setw(genreWidth) << "Genre:" << endl;

    for (const auto& game : games) {
        string gameGenre = game.getGenre();
        gameGenre.erase(0, gameGenre.find_first_not_of(' '));
        gameGenre.erase(gameGenre.find_last_not_of(' ') + 1);
        transform(gameGenre.begin(), gameGenre.end(), gameGenre.begin(),
            [](unsigned char c) { return tolower(c); });

        if (gameGenre == genre) {
            cout << left << setw(nameWidth) << game.getName() << setw(genreWidth) << game.getGenre() << endl;
        }
    }
}

//this giant function is how i add games to the games.txt game library for the user to interact with in the program
void addGameToLibrary(vector<Game>& games, const string& filePath) {
    string name, genre, platform, type;
    int year, rating;

    // Game Name
    cout << "Enter the name of the game: ";
    getline(cin, name);
    cout << endl;

    // Game Genre
    cout << "Select the genre:\n";
    cout << "1. RPG\n2. Shooter\n3. Platformer\n4. Simulation\n5. Racing\n6. Survival\n7. Adventure\n8. Card\n9. Board\n";
    int genreChoice;
    cin >> genreChoice;
    cout << endl;
    if (cin.fail() || genreChoice < 1 || genreChoice > 9) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "Invalid input. Please select a number between 1 and 9.\n";
    }
    else {
        string genre;
        switch (genreChoice) {
        case 1: genre = "RPG"; break;
        case 2: genre = "Shooter"; break;
        case 3: genre = "Platformer"; break;
        case 4: genre = "Simulation"; break;
        case 5: genre = "Racing"; break;
        case 6: genre = "Survival"; break;
        case 7: genre = "Adventure"; break;
        case 8: genre = "Card"; break;
        case 9: genre = "Board"; break;
        default:
            cout << "Invalid genre choice. Please select a number between 1 and 9.\n";
            break;
        }

        // Game Platform
        cout << "Select the platform:\n";
        cout << "1. PC\n2. PlayStation\n3. Nintendo\n4. Xbox\n5. Non-Platform\n";
        int platformChoice;
        cin >> platformChoice;
        cout << endl;
        if (cin.fail() || platformChoice < 1 || platformChoice > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid input. Please select a number between 1 and 5.\n";
        }
        else {
            string platform;
            switch (platformChoice) {
            case 1: platform = "PC"; break;
            case 2: platform = "PlayStation"; break;
            case 3: platform = "Nintendo"; break;
            case 4: platform = "Xbox"; break;
            case 5: platform = "Non-Platform"; break;
            default:
                cout << "Invalid platform choice. Please select a number between 1 and 5.\n";
                break;
            }

            // Game Type
            cout << "Enter 1 for Digital, 2 for Physical: ";
            int typeChoice;
            cin >> typeChoice;
            cout << endl;
            if (cin.fail() || (typeChoice != 1 && typeChoice != 2)) {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "Invalid input. Please enter 1 for Digital or 2 for Physical.\n";
            }
            else {
                type = (typeChoice == 1) ? "Digital" : "Physical";
            }
            cout << "Enter the year of release (4 digits): ";
            cin >> year;
            if (cin.fail() || year < 1000 || year > 9999) {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "Invalid input. Please enter a 4-digit year.\n";
            }
            else {
            }

            //Game Rating
            cout << "Enter rating (0-5): ";
            cin >> rating;
            cout << endl;
            if (cin.fail() || rating < 0 || rating > 5) {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "Invalid input. Please enter a rating between 0 and 5.\n";               
            }
            else {
            }

            Game newGame(name, genre, platform, type, year);
            newGame.setRating(rating);
            games.push_back(newGame);

            // learned how to use these different ios identifiers for the .txt file in stack overflow researching 
            fstream fileStream(filePath, ios::in | ios::out | ios::app); 
            if (fileStream.is_open()) {
                fileStream.seekg(0, ios::end);              
                if (fileStream.tellg() != 0) {
                    fileStream.seekg(-1, ios::end); 
                    char lastChar;
                    fileStream.get(lastChar); 
                    if (lastChar != '\n') {
                        fileStream << "\n"; 
                    }
                }               
                fileStream.clear(); 
                fileStream << name << ", " << genre << ", " << platform << ", " << type << ", " << year << ", " << rating;
                fileStream.close();
                cout << name << " has been added to your library." << endl;
            }
            else {
                cout << "Unable to open file to write.\n";
            }
        }
    }
}

//this controls searching by a letter for the name of a game 
void searchGamesByFirstLetter(const vector<Game>& games) {
    cout << "Enter the first letter of the game's name: ";
    char firstLetter;
    cin >> firstLetter;
    if (!isalpha(firstLetter)) {
        cout << "Invalid input. Please enter a letter.\n";
        return;
    }
    firstLetter = tolower(firstLetter); 
    const int nameWidth = 60; 
    const int genreWidth = 30; 

    bool found = false;
    for (const auto& game : games) {
        if (!game.getName().empty() && tolower(game.getName()[0]) == firstLetter) {
            cout << left << setw(nameWidth) << "Name: " + game.getName()
                << setw(genreWidth) << "Genre: " + game.getGenre() << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No games found starting with the letter '" << firstLetter << "'.\n";
    }
}








