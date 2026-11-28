#include "graph.h"
#include <algorithm>

// comparePatients helper function
// Inputs: patient a and patient b
// Returns true if patient a's ID comes before patient b's ID alphabetically
// Used to sort the patients vector by ID
bool comparePatients(Patient *a, Patient *b)
{
    return a->getId() < b->getId();
}

// findPatient helper function
// Inputs: patients (vector of Patient pointers, sorted by ID), id (string)
// Uses binary search to find the patient with the given ID
// Returns a pointer to the patient, or nullptr if not found
Patient *findPatient(vector<Patient *> &patients, string id)
{
    int low = 0;
    int high = patients.size() - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;
        string midId = patients[mid]->getId();

        if (midId == id)
        {
            return patients[mid];   // found it
        }
        else if (midId < id)
        {
            low = mid + 1;          // the ID must be in the right half
        }
        else
        {
            high = mid - 1;         // the ID must be in the left half
        }
    }
    return nullptr;                 // not in the vector
}

// searchPatient helper function
// Inputs: patients (vector of Patient pointers, sorted by ID)
// Takes user input for patient ID and uses binary search to find the patient
// If patient is found, prints patient info
void searchPatient(vector<Patient *> &patients)
{
    string id;
    cout << "Enter patient ID: ";
    cin >> id;
    Patient *p = findPatient(patients, id);
    if (p != nullptr)
    {
        cout << "Patient found" << endl;
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
    vector<Patient *> patients;
    for (string line : patientLines)
    {
        json j = json::parse(line);
        string id = j["id"];
        string gender = j.value("gender", "unknown");
        string birthDate = j.value("birthDate", "unknown");
        // TO DO: add fields for name, ethnicity, HispanicLatino, maritalStatus
        patients.push_back(new Patient(id, gender, birthDate));
    }
    sort(patients.begin(), patients.end(), comparePatients); // sort by ID
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

        // skip this encounter if its patient isn't in vector
        Patient *p = findPatient(patients, patientId); // binary search instead of hash map lookup
        if (p == nullptr)   // patient not found
        {
            skipped++;
            continue;
        }

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
            for (Patient *p : patients)
            {
                p->printAbbreviatedPatientInfo();
            }
            break;
        case 5:
            for (auto pair : locations)
            {
                Location *l = pair.second;
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