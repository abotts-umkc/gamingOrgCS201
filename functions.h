#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <cctype> 
#include <memory>
#include <algorithm>
using namespace std;

class Game {
private:
    string name;
    string genre;
    string platform;
    string type;
    int year;
    int rating; 

public:
    Game() : year(0), rating(0) {} 

    Game(const string& name, const string& genre, const string& platform, const string& type, int year)
        : name(name), genre(genre), platform(platform), type(type), year(year), rating(0) {}
    // Getters
    string getName() const { return name; }
    string getGenre() const { return genre; }
    string getPlatform() const { return platform; }
    string getType() const { return type; }
    int getYear() const { return year; }
    int getRating() const { return rating; } 
    // Setters
    void setName(const string& newName) { name = newName; }
    void setGenre(const string& newGenre) { genre = newGenre; }
    void setPlatform(const string& newPlatform) { platform = newPlatform; }
    void setType(const string& newType) { type = newType; }
    void setYear(int newYear) { year = newYear; }
    void setRating(int newRating) {
        if (newRating >= 0 && newRating <= 5) {
            rating = newRating;
        }
        else {
            cout << "Invalid rating. Please enter a value between 0 and 5." << endl;
        }
    }
};

class LinkedList {
private:
    struct Node {
        Game data;
        unique_ptr<Node> next;
        Node(Game data) : data(data), next(nullptr) {}
    };
    unique_ptr<Node> head; 
    Node* tail; 

public:
    LinkedList() : head(nullptr), tail(nullptr) {}
    void addElement(Game game);
    Game peek();
    void delElement();
    void printList();
    bool listIsEmpty();
};

// these sub classes currently dont have any use inside of the program
//if i had a bunch more time to develop the program this is one of the things that i would flesh out 
//this is where i would place the download link for the game as one example
//or for physical games this is where i would place links to buy the game and order it 
//this extra information on a website would ideally be able to pull from outside sites to update itself 
//for example if one seller stopped selling the game it would pull from the next available on the same website etc.. 
class DigitalGame : public Game {
private:
    string downloadLink; 

public:
    //constructor
    DigitalGame() : Game(), downloadLink("") {}
    DigitalGame(const string& name, const string& genre, const string& platform, const string& type, int year, const string& downloadLink)
        : Game(name, genre, platform, type, year), downloadLink(downloadLink) {}
    //accessor
    string getDownloadLink() const { return downloadLink; }
    //mutator
    void setDownloadLink(const string& newLink) { downloadLink = newLink; }
};

class PhysicalGame : public Game {
private:
    string buyLocation; 
public:
    //constructors
    PhysicalGame() : Game(), buyLocation("") {}
    PhysicalGame(const string& name, const string& genre, const string& platform, const string& type, int year, const string& buyLocation)
        : Game(name, genre, platform, type, year), buyLocation(buyLocation) {}
    //accessor
    string getBuyLocation() const { return buyLocation; }
    //mutator
    void setBuyLocation(const string& newLocation) { buyLocation = newLocation; }
};

//extra functions that operate with the info from the classes in the menu
vector<Game> loadGames(const string& filePath, LinkedList& gameQueue);
void rateGame(vector<Game>& games, const string& gameName, int rating);
void printGamesWithRating(const vector<Game>& games, int rating);
void printGamesByType(const vector<Game>& games, int typeChoice);
int getNumberOfGamesToPrint();
void printGamesByGenre(const vector<Game>& games);
void addGameToLibrary(vector<Game>& games, const string& filePath);
void searchGamesByFirstLetter(const vector<Game>& games);



