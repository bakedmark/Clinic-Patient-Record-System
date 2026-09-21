#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100 // it can add up to 100 patients 

// function prototype
void addPatient();
void viewAllPatients();
void editPatient();
void searchPatient();
void deletePatient();


typedef struct // data entry for each patient 
{
    int id;            // up to 10 digits
    char name[50];     // Lastname, First Name MI.
    int age;           //
    char gender[10];   // Male or Female
    int contact;       // 11 digits starting with 09
    char disease[100]; // illness
    char address[100];
    int birtday; // MM,DD,YYYY
} Patient;

Patient patients[MAX_PATIENTS];
int patientCount = 0; // global variable that stores each patient array ex. patients[0] ...

int main()
{
    int choice;

    printf("\n\t\t\t\t\t\t==========================================================\n\n");
    printf("\t\t\t\t\t\t\t\t      Patient Record");
    printf("\n\n\t\t\t\t\t\t==========================================================\n\n");

    printf("\n\t\t\t\t[1] Add Patient");
    printf("\t\t[2] View Records");
    printf("\t\t[3] Search Patient");
    printf("\t\t[4] Update Record\n");
    printf("\n\t\t\t\t\t[5] Delete Record");
    printf("\t\t[6] Exit\n");

    do 
    {

        printf("\n\n\t\t\t\tEnter your choice from the menu: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addPatient();
            break;
        case 2:
            viewAllPatients();
            break;
        case 3:
            searchPatient();
            break;
        case 4:
            editPatient();
            break;
        case 5:
            deletePatient();
            break;
        case 6:
            printf("Exiting...");
            break;
        default:
            printf("Invalid");
        }

    } while (choice < 6);

    return 0;
}

void addPatient()
{

    printf("\n\t\t\t\tID Number                       : ");
    scanf("%d", &patients[patientCount].id);
    while (getchar() != '\n');

    printf("\t\t\t\tName [Lastname, First Name MI.] : ");
    fgets(patients[patientCount].name, sizeof(patients[patientCount].name), stdin);
    patients[patientCount].name[strcspn(patients[patientCount].name, "\n")] = '\0';

    printf("\t\t\t\tBirtday [MM/DD/YYYY]            : ");
    scanf("%d", &patients[patientCount].birtday);
    while (getchar() != '\n');

    printf("\t\t\t\tAge                             : ");
    scanf("%d", &patients[patientCount].age);
    while (getchar() != '\n');

    printf("\t\t\t\tGender                          : ");
    fgets(patients[patientCount].gender, sizeof(patients[patientCount].gender), stdin);
    patients[patientCount].gender[strcspn(patients[patientCount].gender, "\n")] = '\0';

    printf("\t\t\t\tAddress                         : ");
    fgets(patients[patientCount].address, sizeof(patients[patientCount].address), stdin);
    patients[patientCount].address[strcspn(patients[patientCount].address, "\n")] = '\0';

    printf("\t\t\t\tContact Number                  : ");
    scanf("%d", &patients[patientCount].contact);
    while (getchar() != '\n');

    printf("\t\t\t\tIllness                         : ");
    fgets(patients[patientCount].disease, sizeof(patients[patientCount].disease), stdin);
    patients[patientCount].disease[strcspn(patients[patientCount].disease, "\n")] = '\0';

    printf("\n\t\t\t\tPatient %s has been added successfully!", patients[patientCount].name);
    patientCount++;
}

void editPatient()
{
    int searchID;
    int found = 0;

    printf("\n\t\t\t\tPatient ID: ");
    scanf("%d", &searchID);

    for (int i = 0; i < patientCount; i++)
    {

        if (patients[i].id == searchID)
        {

            printf("\n\t\t\t\tID Number                       : %d", patients[i].id);
            printf("\n\t\t\t\tName [Lastname, First Name MI.] : %s", patients[i].name);
            printf("\n\t\t\t\tBirtday [MM/DD/YYYY]            : %d", patients[i].birtday);
            printf("\n\t\t\t\tAge                             : %d", patients[i].age);
            printf("\n\t\t\t\tGender                          : %s", patients[i].gender);
            printf("\n\t\t\t\tAddress                         : %s", patients[i].address);
            printf("\n\t\t\t\tContact Number                  : %d", patients[i].contact);
            printf("\n\t\t\t\tIllness                         : %s\n", patients[i].disease);
            printf("\n\t\t\t\t================================================\n");

            printf("\n\t\t\t\tID Number                       : ");
            scanf("%d", &patients[i].id);
            while (getchar() != '\n')
                ;

            printf("\t\t\t\tName [Lastname, First Name MI.] : ");
            fgets(patients[i].name, sizeof(patients[i].name), stdin);
            patients[i].name[strcspn(patients[i].name, "\n")] = '\0';

            printf("\t\t\t\tBirtday [MM/DD/YYYY]            : ");
            scanf("%d", &patients[i].birtday);
            while (getchar() != '\n')
                ;

            printf("\t\t\t\tAge                             : ");
            scanf("%d", &patients[i].age);
            while (getchar() != '\n')
                ;

            printf("\t\t\t\tGender                          : ");
            fgets(patients[i].gender, sizeof(patients[i].gender), stdin);
            patients[i].gender[strcspn(patients[i].gender, "\n")] = '\0';

            printf("\t\t\t\tAddress                         : ");
            fgets(patients[i].address, sizeof(patients[i].address), stdin);
            patients[i].address[strcspn(patients[i].address, "\n")] = '\0';

            printf("\t\t\t\tContact Number                  : ");
            scanf("%d", &patients[i].contact);
            while (getchar() != '\n')
                ;

            printf("\t\t\t\tIllness                         : ");
            fgets(patients[i].disease, sizeof(patients[i].disease), stdin);
            patients[i].disease[strcspn(patients[i].disease, "\n")] = '\0';

            found = 1;

            printf("\n\t\t\t\tPatient %s has been edited successfully!", patients[i].name);
            break;
        }
    }
    if (found == 0)
    {
        printf("\n\t\t\t\t\t\t\t\tNo Patient Found");
        printf("\n\t\t\t\t================================================\n");
    }
}

void searchPatient()
{
    int searchID;
    int found = 0;

    printf("\n\t\t\t\tPatient ID: ");
    scanf("%d", &searchID);

    for (int i = 0; i < patientCount; i++)
    {
        if (patients[i].id == searchID)
        {
            printf("\n\t\t\t\tID Number                       : %d", patients[i].id);
            printf("\n\t\t\t\tName [Lastname, First Name MI.] : %s", patients[i].name);
            printf("\n\t\t\t\tBirtday [MM/DD/YYYY]            : %d", patients[i].birtday);
            printf("\n\t\t\t\tAge                             : %d", patients[i].age);
            printf("\n\t\t\t\tGender                          : %s", patients[i].gender);
            printf("\n\t\t\t\tAddress                         : %s", patients[i].address);
            printf("\n\t\t\t\tContact Number                  : %d", patients[i].contact);
            printf("\n\t\t\t\tIllness                         : %s\n", patients[i].disease);
            printf("\n\t\t\t\t================================================\n");

            found = 1;
            break;
        }
    }

    if (found == 0)
    {
        printf("\n\t\t\t\t\t\t\t\tNo Patient Found");
        printf("\n\t\t\t\t================================================\n");
    }
}

void viewAllPatients()
{

    if (patientCount <= 0)
    {
        printf("\n\t\t\t\t\t\t No Record of Patient");
        printf("\n\t\t\t\t================================================\n");

    }

    for (int i = 0; i < patientCount; i++)
    {
        printf("\n\t\t\t\tID Number                       : %d", patients[i].id);
        printf("\n\t\t\t\tName [Lastname, First Name MI.] : %s", patients[i].name);
        printf("\n\t\t\t\tBirtday [MM/DD/YYYY]            : %d", patients[i].birtday);
        printf("\n\t\t\t\tAge                             : %d", patients[i].age);
        printf("\n\t\t\t\tGender                          : %s", patients[i].gender);
        printf("\n\t\t\t\tAddress                         : %s", patients[i].address);
        printf("\n\t\t\t\tContact Number                  : %d", patients[i].contact);
        printf("\n\t\t\t\tIllness                         : %s\n", patients[i].disease);
        printf("\n\t\t\t\t================================================\n");
    }
}

void deletePatient()
{
    int delete;
    int found = 0;
    char choice;

    printf("\n\t\t\t\tPatient ID: ");
    scanf("%d", &delete);

    for (int i = 0; i < patientCount; i++)
    {
        if (patients[i].id == delete)
        {
            printf("\n\t\t\t\tare you sure [Y]: ");
            scanf(" %c", &choice);

            if (choice == 'Y' || choice == 'y')
            {

                found = 1;

                for (int j = i; j < patientCount - 1; j++)
                {
                    patients[j] = patients[j + 1];
                }

                printf("\n\t\t\t\tPatient %s has been deleted with the id number of %d!", patients[i].name, patients[i].id);

                patientCount--;
                break;
            }
            else
            {
                printf("\n\t\t\t\tDeletion cancelled.");
                printf("\n\t\t\t\t================================================\n");

            }
        
        } 
    }

    if (found == 0)
    {
        printf("\n\t\t\t\tThere is no patient with the ID number of %d.", delete);
        printf("\n\t\t\t\t================================================\n");

    }
}
