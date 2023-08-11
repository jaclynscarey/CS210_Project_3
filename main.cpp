/*
 * File:  main.cpp
 * Author: Jaclyn Carey
 * Date: August 11, 2023
 * Class: CS-210-X6054
 * Description: This program reads a list of items from an input file and stores them in a vector. It then displays a menu of options to the user, allowing them to look up an item, print a frequency list, print a histogram, or exit the program. The program also writes the data to a backup file.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

void PrintMenu() {
    // Print the main menu options
    cout << "\nMenu:" << endl;
    cout << "1. Look Up Item" << endl;
    cout << "2. Print Frequency List" << endl;
    cout << "3. Print Histogram" << endl;
    cout << "4. Exit" << endl << endl;
}

void LookUpItem(const vector<string>& items, const vector<int>& frequencies) {
    // Get user input for the item to look up
    string itemName;
    cout << "\nEnter the item you wish to look for: ";
    cin.ignore();
    getline(cin, itemName);

    // Convert the input to title case
    for (size_t i = 0; i < itemName.length(); ++i) {
        itemName[i] = tolower(itemName[i]);
    }
    itemName[0] = toupper(itemName[0]);

    bool found = false;
    for (size_t i = 0; i < items.size(); ++i) {
        // Check if the item exists in the list
        if (items[i] == itemName) {
            cout << "Frequency of " << itemName << ": " << frequencies[i] << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Item not found." << endl;
    }
}

void PrintFrequencyList(const vector<string>& items, const vector<int>& frequencies) {
    // Print the list of items and their frequencies
    cout << "\nFrequency List:" << endl << endl;
    for (size_t i = 0; i < items.size(); ++i) {
        cout << setw(2) << items[i] << " " << frequencies[i] << endl;
    }
}

void PrintHistogram(const vector<string>& items, const vector<int>& frequencies) {
    // Print a histogram using asterisks to represent frequencies
    cout << "\nHistogram:" << endl << endl;
    for (size_t i = 0; i < items.size(); ++i) {
        cout << setw(2) << items[i] << " ";
        for (int j = 0; j < frequencies[i]; ++j) {
            cout << "*";
        }
        cout << endl;
    }
}

int main() {
    vector<string> items;
    vector<int> frequencies;
    
    // Read input file to populate items and frequencies vectors
    ifstream inputFile("CS210_Project_Three_Input_File.txt");
    string currentItem;
    while (inputFile >> currentItem) {
        bool found = false;
        for (size_t i = 0; i < items.size(); ++i) {
            // Check if the item already exists in the vectors
            if (items[i] == currentItem) {
                frequencies[i]++;
                found = true;
                break;
            }
        }

        if (!found) {
            // Add the new item to the vectors
            items.push_back(currentItem);
            frequencies.push_back(1);
        }
    }

    // Create or open the backup file for writing
    ofstream backupFile("frequency.dat");
    if (!backupFile) {
        cerr << "Error opening backup file." << endl;
        return 1; // Exit with an error status
    }

    // Write data to the backup file
    for (size_t i = 0; i < items.size(); ++i) {
        backupFile << items[i] << " " << frequencies[i] << endl;
    }

    int choice;
    do {
        PrintMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                LookUpItem(items, frequencies);
                break;
            case 2:
                PrintFrequencyList(items, frequencies);
                break;
            case 3:
                PrintHistogram(items, frequencies);
                break;
            case 4:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a valid menu option." << endl;
                break;
        }
    } while (choice != 4);

    return 0;
}
