#include<stdio.h>
#include<string.h>

struct Address {
    char street[50];
    char city[30];
};

struct Patient {
    int id;
    char name[50];
    int age;
    char gender[10];
    char contact[20];
    struct Address address;
    char diagnosis[100];
};

void open(struct Patient p[]) {
    
}

void close(struct Patient p[]) {
   
}

void addPatient(struct Patient p[]) {
    printf("\nEnter Name: ");
    fgets(p.name, sizeof p.name, stdin);

    printf("Enter Age: ");
    scanf("%d", &p.age);
    getchar();

    printf("Enter Gender: ");
    fgets(p.gender, sizeof p.gender, stdin);

    printf("Enter Contact: ");
    fgets(p.contact, sizeof p.contact, stdin);

    printf("Enter Street: ");
    fgets(p.address.street, sizeof p.address.street, stdin);

    printf("Enter City: ");
    fgets(p.address.city, sizeof p.address.city, stdin);

    printf("Enter Diagnosis: ");
    fgets(p.diagnosis, sizeof p.diagnosis, stdin);

    
}

void display(struct Patient p[]) {
    printf("---------------\nPATIENT RECORDS\n---------------\n");
}

void search(struct Patient p[]) {

}

void update(struct Patient p[]) {

}

void delete(struct Patient p[]) {

}

int main() {
    struct Patient p;
    FILE *file;
    file = fopen("patient.txt", "r");
    if (file = NULL) {
        file = fopen("");
    }
    int choice; 
    
    printf("----------------------------\nCLINIC PATIENT RECORD SYSTEM\n----------------------------\n");
    printf("1. Add New Patient Record\n");
    printf("2. Display All Patient Records\n");
    printf("3. Search Patient by ID\n");
    printf("4. Update Patient Information\n");
    printf("5. Delete Patient Record\n");
    printf("6. Exit\n");
    printf("----------------------------\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            addPatient;
            break;
        case 2:
            display;
            break;
        case 3:
            search;
            break;
        case 4:
            update;
            break;
        case 5:
            delete;
            break;
        case 6:
            printf("PROGRAM CLOSED\n");
            break;
    }

    fclose(file);
}