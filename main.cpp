#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "json.hpp"

class Encounter;
class Location;
using namespace std;
using json = nlohmann::json;

class Patient
{
private:
    string id;
    string name;
    string gender;
    string birthDate;
    string ethnicity;
    string HispanicLatino;
    string maritalStatus;
    vector<Encounter *> encounters;

    // start Piper
public:
    Patient(string id, string gender, string birthDate)
    {
        this->id = id;
        this->gender = gender;
        this->birthDate = birthDate;
    }
    string getId() { return id; }
    string getGender() { return gender; }

    void addEncounter(Encounter *e) { encounters.push_back(e); }
    int getEncounterCount() { return encounters.size(); }
    // end Piper
};

class Encounter
{
private:
    string id;
    Patient *subject;
    vector<Location *> locations; // changed to locations vector cause one encounter can have >1 location

public:
    Encounter(string id, Patient *subject)
    {
        this->id = id;
        this->subject = subject;
    }
    void addLocation(Location *loc) { locations.push_back(loc); }
};

class Location
{
private:
    string id;
    string name;
    vector<Encounter *> encounters;

    // start Piper
public:
    Location(string id, string name)
    {
        this->id = id;
        this->name = name;
    }
    string getId() { return id; }
    string getName() { return name; }

    void addEncounter(Encounter *e) { encounters.push_back(e); }
    int getEncounterCount() { return encounters.size(); }
    // end Piper
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
    if (!file)
    {
        return false;
    }

    string line;
    while (getline(file, line))
    {
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
    if (!readFile(fileName, lines))
    {
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
    string fileName = "data/MimicPatient.ndjson"; // path to data goes here
    vector<string> lines = loadFile(fileName);
    // lines now contains each line of the file: load into graph

    // start Piper
    // ---------------- PATIENT OBJECTS ---------------- 
    // turns each line in Patient data into a Patient object
    unordered_map<string, Patient *> patients;
    for (string line : lines)
    {
        json j = json::parse(line);
        string id = j["id"];
        string gender = j.value("gender", "unknown");
        string birthDate = j.value("birthDate", "unknown");
        patients[id] = new Patient(id, gender, birthDate);
    }
    cout << "Created " << patients.size() << " patients" << endl;

    // ---------------- LOCATION OBJECTS ---------------- 
    // turns each line in Location data into a Location object
    vector<string> locationLines = loadFile("data/MimicLocation.ndjson");
    unordered_map<string, Location *> locations;
    for (string line : locationLines)
    {
        json j = json::parse(line);
        string id = j["id"];
        string name = j.value("name", "unknown");
        locations[id] = new Location(id, name);
    }
    cout << "Created " << locations.size() << " locations" << endl;

    // ---------------- ENCOUNTER OBEJECTS  ---------------- 
    //For each line in the encounter data, build one Encounter and connect it to its patient and its locations
    vector<string> encounterLines = loadFile("data/MimicEncounter.ndjson");
    vector<Encounter *> encounters;
    int skipped = 0;
    for (string line : encounterLines)
    {
        json j = json::parse(line);
        string id = j["id"];

        // get patient ID 
        string ref = j["subject"]["reference"];
        string patientId = ref.substr(ref.find('/') + 1);

        // skip this encounter if its patient isn't in map
        if (patients.find(patientId) == patients.end())
        {
            skipped++;
            continue;
        }
        Patient *p = patients[patientId];

        // create encounter and connect it to its patient
        Encounter *e = new Encounter(id, p);
        p->addEncounter(e);

        // connect encounter to each of its locations
        if (j.contains("location"))
        {
            for (auto loc : j["location"])
            {
                string locRef = loc["location"]["reference"];
                string locId = locRef.substr(locRef.find('/') + 1);
                if (locations.find(locId) != locations.end())
                {
                    e->addLocation(locations[locId]);
                    locations[locId]->addEncounter(e);
                }
            }
        }
        encounters.push_back(e);
    }

    cout << "Created " << encounters.size() << " encounters, skipped " << skipped << endl;

    // to make sure it works we shall print how many encounters each location has
    // also gives us insight into the data lol
    for (auto pair : locations) {
        Location* loc = pair.second;
        cout << loc->getName() << ": " << loc->getEncounterCount() << " encounters" << endl;
}
    // end Piper

    return 0;
}