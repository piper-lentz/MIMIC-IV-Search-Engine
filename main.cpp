#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "json.hpp"

using namespace std;
using json = nlohmann::json; // external JSON library

// declare classes
class Patient;
class Encounter;
class Location;

// define classes
class Location
{
private:
    // data
    string id;
    string name;
    vector<Encounter *> encounters;

public:
    // parameterized constructor
    Location(string id, string name)
    {
        this->id = id;
        this->name = name;
    }

    // get methods
    string getId() { return id; }
    string getName() { return name; }

    // helper methods for encounters
    void addEncounter(Encounter *e) { encounters.push_back(e); }
    int getEncounterCount() { return encounters.size(); }

    // helper methods for location
    void printAbbreviatedLocationInfo(int indentLevel = 0)
    {
        string indent = "";
        for (int i = 0; i < indentLevel; i++)
        {
            indent += "  ";
        }
        cout << indent << "==== Location ID: " << id << " ====" << endl;
        cout << indent << "Location Name: " << name << endl;
        cout << indent << "Number of Encounters: " << encounters.size() << endl;
    }

    void printAllLocationInfo(int indentLevel = 0)
    {
        string indent = "";
        for (int i = 0; i < indentLevel; i++)
        {
            indent += "  ";
        }
        cout << indent << "==== Location ID: " << id << " ====" << endl;
        cout << indent << "Location Name: " << name << endl;
        cout << indent << "Number of Encounters: " << encounters.size() << endl;
        // this throws an error: the encounter class is not fully defined yet
        /*
        for (Encounter *e : encounters)
        {
            e->printEncounterInfoSpecificLocation(indentLevel + 1);
        }
        */
    }

    void printLocationInfoSpecificEncounter(int indentLevel = 0)
    {
        string indent = "";
        for (int i = 0; i < indentLevel; i++)
        {
            indent += "  ";
        }
        cout << indent << "==== Location ID: " << id << " ====" << endl;
        cout << indent << "Location Name: " << name << endl;
    }
};

class Encounter
{
private:
    // data
    string id;
    Patient *subject;
    vector<Location *> locations; // one encounter can have >1 location

public:
    // parameterized constructor
    Encounter(string id, Patient *subject)
    {
        this->id = id;
        this->subject = subject;
    }

    // helper methods for locations
    void addLocation(Location *loc) { locations.push_back(loc); }

    // helper methods for encounter

    // these throw an error: the patient class is not fully defined yet
    /*
    void printAllEncounterInfo(int indentLevel = 0)
    {
        string indent = "";
        for (int i = 0; i < indentLevel; i++)
        {
            indent += "  ";
        }
        cout << indent << "==== Encounter ID: " << id << " ====" << endl;
        cout << indent << "Patient ID: " << subject->getId() << endl;
        cout << indent << "Number of Locations: " << locations.size() << endl;
        for (Location *l : locations)
        {
            l->printLocationInfoSpecificEncounter(indentLevel + 1);
        }
    }

    void printEncounterInfoSpecificLocation(int indentLevel = 0)
    {
        string indent = "";
        for (int i = 0; i < indentLevel; i++)
        {
            indent += "  ";
        }
        cout << indent << "==== Encounter ID: " << id << " ====" << endl;
        cout << indent << "Patient ID: " << subject->getId() << endl;
    }
    */

    void printEncounterInfoSpecificPatient(int indentLevel = 0)
    {
        string indent = "";
        for (int i = 0; i < indentLevel; i++)
        {
            indent += "  ";
        }
        cout << indent << "==== Encounter ID: " << id << " ====" << endl;
        cout << indent << "Number of Locations: " << locations.size() << endl;
        for (Location *l : locations)
        {
            l->printLocationInfoSpecificEncounter(indentLevel + 1);
        }
    }

};

class Patient
{
private:
    // data
    string id;
    string name;
    string gender;
    string birthDate;
    string ethnicity;
    string HispanicLatino;
    string maritalStatus;
    vector<Encounter *> encounters;

public:
    // parameterized constructor
    Patient(string id, string gender, string birthDate)
    {
        this->id = id;
        this->gender = gender;
        this->birthDate = birthDate;
        // TO DO: add fields for name, ethnicity, HispanicLatino, maritalStatus
    }

    // get methods
    // TO DO: uncomment get methods when fields are added to constructor
    string getId() { return id; }
    // string getName() { return name; }
    string getGender() { return gender; }
    string getBirthDate() { return birthDate; }
    // string getEthnicity() { return ethnicity; }
    // string getHispanicLatino() { return HispanicLatino; }
    // string getMaritalStatus() { return maritalStatus; }

    // helper methods for encounters
    int getEncounterCount() { return encounters.size(); }
    void addEncounter(Encounter *e) { encounters.push_back(e); }
    vector<Encounter *> getEncounters() { return encounters; }

    // helper methods for patient
    void printAbbreviatedPatientInfo(int indentLevel = 0)
    {
        string indent = "";
        for (int i = 0; i < indentLevel; i++)
        {
            indent += "  ";
        }
        cout << indent << "==== Patient ID: " << id << " ====" << endl;
        // TO DO: uncomment when fields are added to constructor
        // cout << indent << "Name: " << name << endl;
        cout << indent << "Gender: " << gender << endl;
        cout << indent << "Birth Date: " << birthDate << endl;
        // cout << indent << "Ethnicity: " << ethnicity << endl;
        // cout << indent << "Hispanic/Latino: " << HispanicLatino << endl;
        // cout << indent << "Marital Status: " << maritalStatus << endl;
        cout << indent << "Number of Encounters: " << encounters.size() << endl;
    }

    void printAllPatientInfo(int indentLevel = 0)
    {
        string indent = "";
        for (int i = 0; i < indentLevel; i++)
        {
            indent += "  ";
        }
        cout << indent << "==== Patient ID: " << id << " ====" << endl;
        // TO DO: uncomment when fields are added to constructor
        // cout << indent << "Name: " << name << endl;
        cout << indent << "Gender: " << gender << endl;
        cout << indent << "Birth Date: " << birthDate << endl;
        // cout << indent << "Ethnicity: " << ethnicity << endl;
        // cout << indent << "Hispanic/Latino: " << HispanicLatino << endl;
        // cout << indent << "Marital Status: " << maritalStatus << endl;
        cout << indent << "Number of Encounters: " << encounters.size() << endl;
        for (Encounter *e : encounters)
        {
            e->printEncounterInfoSpecificPatient(indentLevel + 1);
        }
    }
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

// searchPatient helper function
// Inputs: patients (unordered_map<string, Patient *>)
// Takes user input for patient ID and searches for patient in patients map
// If patient is found, prints patient info
void searchPatient(unordered_map<string, Patient *> &patients)
{
    string id;
    cout << "Enter patient ID: ";
    cin >> id;
    if (patients.find(id) != patients.end())
    {
        cout << "Patient found" << endl;
        Patient *p = patients[id];
        p->printAllPatientInfo();
    }
    else
    {
        cout << "Patient not found" << endl;
    }
}

// main function
int main()
{
    // ---------------- PATIENT OBJECTS ---------------- 
    // turns each line in Patient data into a Patient object
    vector<string> patientLines = loadFile("data/MimicPatient.ndjson");
    unordered_map<string, Patient *> patients;
    for (string line : patientLines)
    {
        json j = json::parse(line);
        string id = j["id"];
        string gender = j.value("gender", "unknown");
        string birthDate = j.value("birthDate", "unknown");
        // TO DO: add fields for name, ethnicity, HispanicLatino, maritalStatus
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
    // for each line in Encounter data, build one Encounter object
    // then connect it to its patient and its locations
    vector<string> encounterLines = loadFile("data/MimicEncounter.ndjson");
    vector<Encounter *> encounters;
    int skipped = 0;
    for (string line : encounterLines)
    {
        json j = json::parse(line);
        string id = j["id"];

        // get patient ID (after the /)
        string ref = j["subject"]["reference"];
        string patientId = ref.substr(ref.find('/') + 1);

        // skip this encounter if its patient isn't in map
        if (patients.find(patientId) == patients.end())
        {
            skipped++;
            continue;
        }
        Patient *p = patients[patientId]; // gets patient out of map

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
    cout << "Created " << encounters.size() << " encounters; skipped " << skipped << endl;

    // main program loop
    bool running = true;
    while (running)
    {
        cout << "Select from the following options: " << endl;
        cout << "1. Search by patient" << endl;
        cout << "2. Search by location" << endl;
        cout << "3. Search by encounter" << endl;
        cout << "4. Print all patients" << endl;
        cout << "5. Print all locations" << endl;
        cout << "0. Exit" << endl;
        int command;
        cin >> command;
        switch (command)
        {
            case 1:
                searchPatient(patients);
                break;
            case 2:
                cout << "Search by location is not yet implemented." << endl;
                // TO DO: implement search by location
                break;
            case 3: 
                cout << "Search by encounter is not yet implemented." << endl;
                // TO DO: implement search by encounter
                break;
            case 4:
                for (auto pair : patients)
                {
                    Patient *p = pair.second;
                    p->printAbbreviatedPatientInfo();
                }
                break;
            case 5:
                for (auto pair : locations) 
                {
                    Location* l = pair.second;
                    l->printAbbreviatedLocationInfo();
                }
                break;
            case 0:
                cout << "Exiting program." << endl;
                running = false;
                break;
            default:
                cout << "Invalid command." << endl;
        }
    }

    return 0;
}