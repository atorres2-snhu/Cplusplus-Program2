#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>
#include <algorithm> // For transform function
#include <limits>    // For numeric_limits

using namespace std;

class ItemTracker {
private:
    std::map<std::string, int> itemFrequency;

public:
    // Method to load items from a file
    void loadItemsFromFile(const string& filename) {
        ifstream inputFile(filename);
        string item;
        
        if (inputFile.is_open()) {
            while (getline(inputFile, item)) {  // Use getline to capture whole line
                transform(item.begin(), item.end(), item.begin(), ::tolower); // Convert to lowercase
                itemFrequency[item]++;
            }
            inputFile.close();
        } else {
            cerr << "Error: Could not open file " << filename << ". Please check if the file exists." << endl;
        }
    }

    // Method to get the frequency of a specific item
    int getItemFrequency(const string& item) {
        string lowerItem = item;
        transform(lowerItem.begin(), lowerItem.end(), lowerItem.begin(), ::tolower); // Convert user input to lowercase
        if (itemFrequency.find(lowerItem) != itemFrequency.end()) {
            return itemFrequency[lowerItem];
        }
        return 0; // Return 0 if item is not found
    }

    // Method to print all items with their frequencies
    void printAllItems() {
        cout << "\nItem Frequencies:\n";
        cout << "=================\n";
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    // Method to print a histogram of all items
    void printHistogram() {
        cout << "\nItem Frequency Histogram:\n";
        cout << "=========================\n";
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }

    // Method to save the frequency data to a backup file
    void saveToBackupFile(const string& filename) {
        ofstream outputFile(filename);
        
        if (outputFile.is_open()) {
            for (const auto& pair: itemFrequency) {
                outputFile << pair.first << " " << pair.second << endl;
            }
            outputFile.close();
        } else {
            cerr << "Error: Could not open file " << filename << endl;
        }
    }
};

int main() {
    ItemTracker tracker;
    tracker.loadItemsFromFile("CS210_Project_Three_Input_File.txt"); // Load items from the input file
    tracker.saveToBackupFile("frequency.dat"); // Save frequency data to backup file

    int userChoice;
    string item;

    do {
        // Display menu options
        cout << "\nCorner Grocer Item Tracker Menu:\n";
        cout << "1. Search for an item\n";
        cout << "2. Display all items and their frequencies\n";
        cout << "3. Display histogram of item frequencies\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        
        // Input validation for menu choice
        while (!(cin >> userChoice)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
        }

        switch (userChoice) {
            case 1:
                cout << "Enter the item name: ";
                cin >> item;
                cout << item << " was purchased " << tracker.getItemFrequency(item) << " time(s).\n";
                break;
            case 2:
                tracker.printAllItems();
                break;
            case 3:
                tracker.printHistogram();
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (userChoice != 4);

    return 0;
}