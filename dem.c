#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// -----------------------------
// STRUCT DEFINITIONS
// -----------------------------

// Address structure to store street and city
struct Address {
    char street[50];
    char city[30];
};

// Patient structure to store patient details
struct Patient {
    int id;                 // Unique patient ID
    char name[50];          // Patient name
    int age;                // Patient age
    char gender[10];        // Gender
    char contact[20];       // Contact number
    struct Address address; // Nested struct for address
    char diagnosis[100];    // Diagnosis details
};

// -----------------------------
// FUNCTION DEFINITIONS
// -----------------------------

// Generate unique ID by finding the max ID in the array and incrementing it
int generateUniqueID(struct Patient patients[], int count) {
    int maxID = 0;
    for (int i = 0; i < count; i++) {
        if (patients[i].id > maxID) {
            maxID = patients[i].id;
        }
    }
    return maxID + 1; // Next available ID
}

// Add a new patient record
void addPatient(struct Patient patients[], int *count) {
    struct Patient p;
    p.id = generateUniqueID(patients, *count); // Assign unique ID
    printf("\nAssigned Patient ID: %d\n", p.id);

    // Input patient details
    printf("Enter Name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = '\0'; // Remove newline

    printf("Enter Age: ");
    scanf("%d", &p.age);
    getchar(); // Clear buffer

    printf("Enter Gender: ");
    fgets(p.gender, sizeof(p.gender), stdin);
    p.gender[strcspn(p.gender, "\n")] = '\0';

    printf("Enter Contact: ");
    fgets(p.contact, sizeof(p.contact), stdin);
    p.contact[strcspn(p.contact, "\n")] = '\0';

    printf("Enter Street: ");
    fgets(p.address.street, sizeof(p.address.street), stdin);
    p.address.street[strcspn(p.address.street, "\n")] = '\0';

    printf("Enter City: ");
    fgets(p.address.city, sizeof(p.address.city), stdin);
    p.address.city[strcspn(p.address.city, "\n")] = '\0';

    printf("Enter Diagnosis: ");
    fgets(p.diagnosis, sizeof(p.diagnosis), stdin);
    p.diagnosis[strcspn(p.diagnosis, "\n")] = '\0';

    // Save patient to array
    patients[*count] = p;
    (*count)++;
    printf("\nPatient Recorded Successfully!\n");
}

// Display all patient records in tabular format
void displayAllPatients(struct Patient patients[], int count) {
    if (count == 0) {
        printf("\nNo patient records found.\n");
        return;
    }

    printf("\n-------------------------------------------------------------\n");
    printf("ID | Name                     | Age | Gender | Diagnosis\n");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-2d | %-24s | %-3d | %-6s | %s\n",
               patients[i].id,
               patients[i].name,
               patients[i].age,
               patients[i].gender,
               patients[i].diagnosis);
    }
    printf("-------------------------------------------------------------\n");
}

// Search patient by ID
void searchPatientByID(struct Patient patients[], int count) {
    int id, found = 0;
    printf("Enter Patient ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (patients[i].id == id) {
            // Display full patient details
            printf("\nPatient Found:\n");
            printf("ID: %d\nName: %s\nAge: %d\nGender: %s\nContact: %s\nStreet: %s\nCity: %s\nDiagnosis: %s\n",
                   patients[i].id,
                   patients[i].name,
                   patients[i].age,
                   patients[i].gender,
                   patients[i].contact,
                   patients[i].address.street,
                   patients[i].address.city,
                   patients[i].diagnosis);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Patient not found.\n");
    }
}

// Update patient information by ID
void updatePatient(struct Patient patients[], int count) {
    int id, found = 0;
    printf("Enter Patient ID to update: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < count; i++) {
        if (patients[i].id == id) {
            // Input new details
            printf("Enter New Name: ");
            fgets(patients[i].name, sizeof(patients[i].name), stdin);
            patients[i].name[strcspn(patients[i].name, "\n")] = '\0';

            printf("Enter New Age: ");
            scanf("%d", &patients[i].age);
            getchar();

            printf("Enter New Gender: ");
            fgets(patients[i].gender, sizeof(patients[i].gender), stdin);
            patients[i].gender[strcspn(patients[i].gender, "\n")] = '\0';

            printf("Enter New Contact: ");
            fgets(patients[i].contact, sizeof(patients[i].contact), stdin);
            patients[i].contact[strcspn(patients[i].contact, "\n")] = '\0';

            printf("Enter New Street: ");
            fgets(patients[i].address.street, sizeof(patients[i].address.street), stdin);
            patients[i].address.street[strcspn(patients[i].address.street, "\n")] = '\0';

            printf("Enter New City: ");
            fgets(patients[i].address.city, sizeof(patients[i].address.city), stdin);
            patients[i].address.city[strcspn(patients[i].address.city, "\n")] = '\0';

            printf("Enter New Diagnosis: ");
            fgets(patients[i].diagnosis, sizeof(patients[i].diagnosis), stdin);
            patients[i].diagnosis[strcspn(patients[i].diagnosis, "\n")] = '\0';

            printf("Patient Updated Successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Patient not found.\n");
    }
}

// Delete patient record by ID
void deletePatient(struct Patient patients[], int *count) {
    int id, found = 0;
    printf("Enter Patient ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < *count; i++) {
        if (patients[i].id == id) {
            // Shift records to overwrite deleted patient
            for (int j = i; j < *count - 1; j++) {
                patients[j] = patients[j + 1];
            }
            (*count)--;
            printf("Patient Deleted Successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Patient not found.\n");
    }
}

// Load patient records from file
void loadFromFile(struct Patient patients[], int *count) {
    FILE *fp = fopen("patients.txt", "r");
    if (fp == NULL) {
        *count = 0; // No file found, start fresh
        return;
    }

    // Read patient records line by line
    while (fscanf(fp, "%d|%49[^|]|%d|%9[^|]|%19[^|]|%49[^|]|%29[^|]|%99[^\n]\n",
                  &patients[*count].id,
                  patients[*count].name,
                  &patients[*count].age,
                  patients[*count].gender,
                  patients[*count].contact,
                  patients[*count].address.street,
                  patients[*count].address.city,
                  patients[*count].diagnosis) == 8) {
        (*count)++;
    }

    fclose(fp);
}

// Save patient records to file
void saveToFile(struct Patient patients[], int count) {
    FILE *fp = fopen("patients.txt", "w");
    if (fp == NULL) {
        printf("Error saving file.\n");
        return;
    }

    // Write each patient record in pipe-separated format
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d|%s|%d|%s|%s|%s|%s|%s\n",
                patients[i].id,
                patients[i].name,
                patients[i].age,
                patients[i].gender,
                patients[i].contact,
                patients[i].address.street,
                patients[i].address.city,
                patients[i].diagnosis);
    }

    fclose(fp);
}

// -----------------------------
// MAIN FUNCTION
// -----------------------------
int main() {
    struct Patient patients[100]; // Array to store up to 100 patients
    int count = 0;                // Current patient count
    int choice;                   // Menu choice

    // Load existing patient records from file (if any)
    loadFromFile(patients, &count);

    // Menu-driven loop
    do {
        printf("\n---------------------------------\n");
        printf("CLINIC PATIENT RECORD SYSTEM\n");
        printf("---------------------------------\n");
        printf("1. Add New Patient Record\n");
        printf("2. Display All Patient Records\n");
        printf("3. Search Patient by ID\n");
        printf("4. Update Patient Information\n");
        printf("5. Delete Patient Record\n");
        printf("6. Save & Exit\n");
        printf("---------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear input buffer

        // Handle user choice
        switch (choice) {
            case 1:
                addPatient(patients, &count); // Add new patient
                break;
            case 2:
                displayAllPatients(patients, count); // Show all patients
                break;
            case 3:
                searchPatientByID(patients, count); // Search by ID
                break;
            case 4:
                updatePatient(patients, count); // Update patient info
                break;
            case 5:
                deletePatient(patients, &count); // Delete patient
                break;
            case 6:
                saveToFile(patients, count); // Save before exit
                printf("PROGRAM CLOSED\n");
                break;
            default:
                printf("Invalid choice.\n"); // Handle wrong input
                break;
        }
    } while (choice != 6); // Loop until user chooses to exit

    return 0;
}
