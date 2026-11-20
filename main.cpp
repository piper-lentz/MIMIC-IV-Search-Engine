#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Patient{
    private:
        string id;
        string name;
        string gender;
        string birthDate;
        string ethnicity;
        string HispanicLatino;
        string maritalStatus;
        vector<Encounter *> encounters;
};

class Encounter{
    private:
        string id;
        Patient* subject;
        Location* location;

};

class Location{
    private:
        string id;
        string name;
        vector<Encounter *> encounters;
};

// readFile helper function
// Inputs: fileName (string), lines (reference to vector<string>)
// Outputs: boolean
// Reads file at filename line-by-line
// Stores each line in lines vector
// Returns true if file opened successfully, false otherwise
bool readFile(string fileName, vector<string> &lines)
{
    ifstream file(fileName);
    if (!file) {
        return false;
    }

    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    return true;
}

// loadFile helper function
// Inputs: fileName (string)
// Outputs: vector<string>
// Calls readFile on fileName and vector<string> lines
// Returns vector of line strings read from file
vector<string> loadFile(string fileName)
{
    vector<string> lines;
    if (!readFile(fileName, lines)) {
        cout << "Error: cannot open " << fileName << endl;
        return {};
    }
    int fileSize = lines.size();
    cout << "Load " << fileName << ": Read " << fileSize << " lines" << endl;
    return lines;
}

// main function
int main()
{
    string fileName = "../"; // path to data goes here
    vector<string> lines = loadFile(fileName);
    // lines now contains each line of the file: load into graph

    return 0;
}