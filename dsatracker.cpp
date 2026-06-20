Extended description: Cleaned up Markdown formatting and corrected minor spelling mistakes.#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

// -----------------------------
// Data Structure
// -----------------------------
struct Problem {
    string name;
    string topic;
    string difficulty;
    bool isSolved;
};

const string FILE_NAME = "progress.txt";

// -----------------------------
// Utility Functions
// -----------------------------

// Save a problem to file
void saveProblemToFile(const Problem& problem) {
    ofstream file(FILE_NAME, ios::app);
    file << problem.name << ","
         << problem.topic << ","
         << problem.difficulty << ","
         << problem.isSolved << "\n";
    file.close();
}

// Load problems from file
vector<Problem> loadProblemsFromFile() {
    vector<Problem> problems;
    ifstream file(FILE_NAME);

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, topic, difficulty, solvedStr;

        getline(ss, name, ',');
        getline(ss, topic, ',');
        getline(ss, difficulty, ',');
        getline(ss, solvedStr, ',');

        Problem problem;
        problem.name = name;
        problem.topic = topic;
        problem.difficulty = difficulty;
        problem.isSolved = (solvedStr == "1");

        problems.push_back(problem);
    }

    file.close();
    return problems;
}

// -----------------------------
// Core Features
// -----------------------------

// Add a new problem
void addProblem() {
    Problem problem;

    cout << "\nEnter Problem Name: ";
    cin.ignore();
    getline(cin, problem.name);

    cout << "Enter Topic: ";
    getline(cin, problem.topic);

    cout << "Enter Difficulty (Easy/Medium/Hard): ";
    getline(cin, problem.difficulty);

    cout << "Solved? (1 = Yes, 0 = No): ";
    cin >> problem.isSolved;

    saveProblemToFile(problem);
    cout << "✅ Problem added successfully.\n";
}

// Display all problems
void displayProblems() {
    vector<Problem> problems = loadProblemsFromFile();

    if (problems.empty()) {
        cout << "\nNo problems found.\n";
        return;
    }

    cout << "\n----- Problem List -----\n";
    for (const auto& problem : problems) {
        cout << "Name: " << problem.name
             << " | Topic: " << problem.topic
             << " | Difficulty: " << problem.difficulty
             << " | Solved: " << (problem.isSolved ? "Yes" : "No")
             << "\n";
    }
}

// Show analytics
void showAnalytics() {
    vector<Problem> problems = loadProblemsFromFile();

    int totalProblems = problems.size();
    int solvedCount = 0;

    map<string, int> topicFrequency;
    map<string, int> difficultyFrequency;

    for (const auto& problem : problems) {
        if (problem.isSolved) {
            solvedCount++;
        }
        topicFrequency[problem.topic]++;
        difficultyFrequency[problem.difficulty]++;
    }

    cout << "\n----- Analytics -----\n";
    cout << "Total Problems: " << totalProblems << "\n";
    cout << "Solved Problems: " << solvedCount << "\n";

    if (totalProblems > 0) {
        cout << "Accuracy: " << (solvedCount * 100 / totalProblems) << "%\n";
    }

    cout << "\nTopic-wise Distribution:\n";
    for (const auto& entry : topicFrequency) {
        cout << entry.first << ": " << entry.second << "\n";
    }

    cout << "\nDifficulty-wise Distribution:\n";
    for (const auto& entry : difficultyFrequency) {
        cout << entry.first << ": " << entry.second << "\n";
    }
}

// -----------------------------
// Main Menu
// -----------------------------
void showMenu() {
    cout << "\n===== DSA Progress Tracker =====\n";
    cout << "1. Add Problem\n";
    cout << "2. View Problems\n";
    cout << "3. View Analytics\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;

    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addProblem();
                break;
            case 2:
                displayProblems();
                break;
            case 3:
                showAnalytics();
                break;
            case 4:
                cout << "Exiting program...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}