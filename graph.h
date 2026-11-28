#pragma once
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

    // helper methods for encounters in Location class
    void addEncounter(Encounter *e) { encounters.push_back(e); }
    int getEncounterCount() { return encounters.size(); }

    // helper methods for Location class
    void printAbbreviatedLocationInfo(int indentLevel = 0);
    void printAllLocationInfo(int indentLevel = 0);
    void printLocationInfoSpecificEncounter(int indentLevel = 0);
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

    // get methods
    string getId() { return id; }

    // helper methods for locations in Encounter class
    void addLocation(Location *loc) { locations.push_back(loc); }

    // helper methods for Encounter class
    void printEncounterInfoSpecificPatient(int indentLevel = 0);
    void printAllEncounterInfo(int indentLevel = 0);
    void printEncounterInfoSpecificLocation(int indentLevel = 0);
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

    // helper methods for encounters in Patient class
    int getEncounterCount() { return encounters.size(); }
    void addEncounter(Encounter *e) { encounters.push_back(e); }
    vector<Encounter *> getEncounters() { return encounters; }

    // helper methods for Patient class
    void printAbbreviatedPatientInfo(int indentLevel = 0);
    void printAllPatientInfo(int indentLevel = 0);
    void printPatientInfoSpecificEncounter(int indentLevel = 0);
};

// helper methods for Location class
void Location::printAbbreviatedLocationInfo(int indentLevel)
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

void Location::printAllLocationInfo(int indentLevel)
{
    string indent = "";
    for (int i = 0; i < indentLevel; i++)
    {
        indent += "  ";
    }
    cout << indent << "==== Location ID: " << id << " ====" << endl;
    cout << indent << "Location Name: " << name << endl;
    cout << indent << "Number of Encounters: " << encounters.size() << endl;
    for (Encounter *e : encounters)
    {
        e->printEncounterInfoSpecificLocation(indentLevel + 1);
    }
    
}

void Location::printLocationInfoSpecificEncounter(int indentLevel)
{
    string indent = "";
    for (int i = 0; i < indentLevel; i++)
    {
        indent += "  ";
    }
    cout << indent << "==== Location ID: " << id << " ====" << endl;
    cout << indent << "Location Name: " << name << endl;
}

// helper methods for Encounter class
void Encounter::printAllEncounterInfo(int indentLevel)
{
    string indent = "";
    for (int i = 0; i < indentLevel; i++)
    {
        indent += "  ";
    }
    cout << indent << "==== Encounter ID: " << id << " ====" << endl;
    cout << indent << "Patient ID: " << subject->getId() << endl;
    subject->printPatientInfoSpecificEncounter(indentLevel + 1);
    cout << indent << "Number of Locations: " << locations.size() << endl;
    for (Location *l : locations)
    {
        l->printLocationInfoSpecificEncounter(indentLevel + 1);
    }
}

void Encounter::printEncounterInfoSpecificLocation(int indentLevel)
{
    string indent = "";
    for (int i = 0; i < indentLevel; i++)
    {
        indent += "  ";
    }
    cout << indent << "==== Encounter ID: " << id << " ====" << endl;
    cout << indent << "Patient ID: " << subject->getId() << endl;
}

void Encounter::printEncounterInfoSpecificPatient(int indentLevel)
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

// helper methods for Patient class
void Patient::printAbbreviatedPatientInfo(int indentLevel)
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

void Patient::printAllPatientInfo(int indentLevel)
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

void Patient::printPatientInfoSpecificEncounter(int indentLevel)
{
    string indent = "";
    for (int i = 0; i < indentLevel; i++)
    {
        indent += "  ";
    }
    // TO DO: uncomment when fields are added to constructor
    // cout << indent << "Name: " << name << endl;
    cout << indent << "Gender: " << gender << endl;
    cout << indent << "Birth Date: " << birthDate << endl;
    // cout << indent << "Ethnicity: " << ethnicity << endl;
    // cout << indent << "Hispanic/Latino: " << HispanicLatino << endl;
    // cout << indent << "Marital Status: " << maritalStatus << endl;
}

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