# MIMIC-IV-Search-Engine
This program is a search engine for the MIMIC-IV database, which contains clinical data for thousands of anonymized patients admitted to the Beth Israel Deaconess Medical Center in Boston (Bennett et al. 2025). With this program, you can search for patient records using patient IDs, clinical diagnoses, and demographic data. We use graph data structures to store the data so it can be quickly searched. 

## Inputs

The necessary input files for data can be found in the /data directory.

### Example Test Cases:

Setup

    Load data/MimicPatient.ndjson: Read 100 lines
    Created 100 patients
    Load data/MimicLocation.ndjson: Read 31 lines
    Created 31 locations
    Load data/MimicEncounter.ndjson: Read 275 lines
    Created 275 encounters; skipped 0

Search for patient ID

    Select from the following options: 
    1. Search by patient
    2. Search by location
    3. Search by encounter
    4. Print all patients
    5. Print all locations
    0. Exit
    > 1
    Enter patient ID: 
    > 74a2fd87-885b-5eca-9f8b-9141915dba51
    Patient found
    ==== Patient ID: 74a2fd87-885b-5eca-9f8b-9141915dba51 ====
    Gender: female
    Birth Date: 2070-04-05
    Number of Encounters: 1
    ==== Encounter ID: 6ffa821c-2cf3-58c5-aa96-7436930d6bf2 ====
    Number of Locations: 3
        ==== Location ID: 501cd59a-cd8a-5f98-8298-2ca9c897d59f ====
        Location Name: Emergency Department
        ==== Location ID: 77b3f959-fa2c-5599-8713-a86815b29a4a ====
        Location Name: Medical Intensive Care Unit (MICU)
        ==== Location ID: 0483cba3-574b-58e3-a6a1-2eec0f3b707a ====
        Location Name: Med/Surg

Print all locations

    Select from the following options: 
    1. Search by patient
    2. Search by location
    3. Search by encounter
    4. Print all patients
    5. Print all locations
    0. Exit
    > 5
    ==== Location ID: dbba2bef-57a7-582f-8d86-a7a6d7fea258 ====
    Location Name: Surgical Intensive Care Unit (SICU)
    Number of Encounters: 33
    ==== Location ID: 9aaa291e-bf3f-5cab-bae0-799e43da5ad5 ====
    Location Name: Neuro Surgical Intensive Care Unit (Neuro SICU)
    Number of Encounters: 4
    ==== Location ID: 77b3f959-fa2c-5599-8713-a86815b29a4a ====
    Location Name: Medical Intensive Care Unit (MICU)
    Number of Encounters: 36
    ==== Location ID: 73a95bb4-bc53-5ad9-ba8b-0cc7d99bc51f ====
    Location Name: Unknown
    Number of Encounters: 1
    ==== Location ID: 0fc2d23b-0e5b-5f91-8369-6d37301fea51 ====
    Location Name: Medicine
    Number of Encounters: 77
    ==== Location ID: 3f108faf-a803-5c58-8c3b-9a79e2c02bc7 ====
    Location Name: Observation
    Number of Encounters: 2
    ==== Location ID: 00e4b7f2-1d93-5521-9dd9-cba8fa9461af ====
    Location Name: Trauma SICU (TSICU)
    Number of Encounters: 20
    ==== Location ID: 501cd59a-cd8a-5f98-8298-2ca9c897d59f ====
    Location Name: Emergency Department
    Number of Encounters: 182
    ==== Location ID: d82eeafd-5ac3-5765-8eb2-2b4153978abb ====
    Location Name: Med/Surg/Trauma
    Number of Encounters: 25
    ==== Location ID: df3de283-871d-5380-bbb6-817937650feb ====
    Location Name: Surgery/Trauma
    Number of Encounters: 3
    ==== Location ID: 26875036-4b73-57fc-944b-6ddfcd07d8e3 ====
    Location Name: Neuro Intermediate
    Number of Encounters: 1
    ==== Location ID: 9152585d-31b9-50ca-9476-a4db49030917 ====
    Location Name: Transplant
    Number of Encounters: 39
    ==== Location ID: 25fdf8f3-5c5e-517b-b732-8f4501f25c33 ====
    Location Name: Medicine/Cardiology
    Number of Encounters: 43
    ==== Location ID: dcde0b27-37b5-5ef1-8d7e-85d608901e2b ====
    Location Name: Medical/Surgical Intensive Care Unit (MICU/SICU)
    Number of Encounters: 32
    ==== Location ID: ecbf468a-22ec-5320-8e11-6ebcc918dad5 ====
    Location Name: Cardiology Surgery Intermediate
    Number of Encounters: 1
    ==== Location ID: d4b315bc-5e39-5162-9d5c-dada4294b1a9 ====
    Location Name: PACU
    Number of Encounters: 25
    ==== Location ID: f4ed77ed-3be3-5700-bc6a-3622ca10f90f ====
    Location Name: Discharge Lounge
    Number of Encounters: 36
    ==== Location ID: 30fa4243-10dc-5b14-8819-e4785f8dd4a7 ====
    Location Name: Coronary Care Unit (CCU)
    Number of Encounters: 16
    ==== Location ID: 7999fbb8-3413-5569-a2e8-b627c0b60b2d ====
    Location Name: Cardiology
    Number of Encounters: 1
    ==== Location ID: 0483cba3-574b-58e3-a6a1-2eec0f3b707a ====
    Location Name: Med/Surg
    Number of Encounters: 48
    ==== Location ID: 0c8de059-7250-5b94-b98d-0a079b28f06c ====
    Location Name: Cardiac Surgery
    Number of Encounters: 39
    ==== Location ID: 7fabe959-1cae-5f68-a720-27c2975f8ec8 ====
    Location Name: Cardiac Vascular Intensive Care Unit (CVICU)
    Number of Encounters: 31
    ==== Location ID: d80df646-f05d-5b0d-9838-6be5caed33db ====
    Location Name: Medicine/Cardiology Intermediate
    Number of Encounters: 1
    ==== Location ID: ce894871-5616-57b1-9cf0-687c06efb1f0 ====
    Location Name: Hematology/Oncology
    Number of Encounters: 31
    ==== Location ID: 7fc6d652-37b4-5812-9412-a1e397a11d7f ====
    Location Name: Med/Surg/GYN
    Number of Encounters: 13
    ==== Location ID: 35f60a03-d022-5ad4-9952-6494d475fc09 ====
    Location Name: Vascular
    Number of Encounters: 20
    ==== Location ID: 4dfa8a5c-f049-5266-b341-756d86fc0748 ====
    Location Name: Neuro Stepdown
    Number of Encounters: 3
    ==== Location ID: 0e7530e9-f728-5f0f-a959-bfd148882219 ====
    Location Name: Neurology
    Number of Encounters: 46
    ==== Location ID: 38348787-d473-591c-b2bc-3c02ddb8890e ====
    Location Name: Psychiatry
    Number of Encounters: 3
    ==== Location ID: c69e109f-5540-5e58-98a8-32154d4c539d ====
    Location Name: Emergency Department Observation
    Number of Encounters: 26
    ==== Location ID: 7f04d9ea-2eff-5944-97f1-cdc45ec531d4 ====
    Location Name: Hematology/Oncology Intermediate
    Number of Encounters: 23

Search for patient ID that doesn't exist

    Select from the following options: 
    1. Search by patient
    2. Search by location
    3. Search by encounter
    4. Print all patients
    5. Print all locations
    0. Exit
    > 1
    Enter patient ID: 
    > nonExistent
    Patient not found

Run a command that doesn't exist

    Select from the following options: 
    1. Search by patient
    2. Search by location
    3. Search by encounter
    4. Print all patients
    5. Print all locations
    0. Exit
    > 6
    Invalid command.

## Build and Run Commands

    g++ -std=c++17 *.cpp -o MIMICsearch

    ./MIMICsearch

## Current Status

LAST UPDATED: **24 November 2026**

### Work History

The team worked on the main branch for this iteration, because the features we were building were core functionality requirements rather than enhancements. Team members communicated with each other when they pulled the most recent code, when they were working, what they modified, and when they pushed their updates to main.

**Relevant Commits:**

 * **Piper:** Load patients, locations, and encounters from MIMIC-IV FHIR; build graph
   * 1b004241667c878db3b573ad3fb127d65edf8ae7
   * e624e957c0a914d6ebe3eaa4772353b936ea4c6c
   * c68d77ede3002d6d61eacdfe0e90dc38ea580355
 * **Caroline:** Classes and file I/O functions; main flow of control loop, print functions, and search by patient ID
   * 1e416ce29f616af499d38c48da95dae3af84fd3f
   * 25cc628a10035b8d47323c832e1c448647b72ade
 * **Kaycie:** Kaycie had issues accessing a computer for this iteration and was not able to commit to the GitHub repository.

### Progress Summary

The program can read and store data from the MIMIC-IV dataset in a graph. The *searchPatient* function can take in a patient ID fron the user and return all relevant information associated with that patient, including information regarding their medical encounters and the locations of the encounters.

### Known Limitations

The scope of the data is quite large, so for this iteration we have limited ourselves to three data sources: Patient, Location, and Encounter. Currently, some of the *print* features for the *Location* and *Encounter* classes do not work, because they rely on classes that are defined later in the code.  
