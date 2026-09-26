#include <stdio.h>   // for printf() and scanf()
#include <string.h>  // for strcspn() and strcpy()
#include <stdlib.h>  // for system("cls")
#include <windows.h> // for Sleep()

#define MAX_PATIENTS 100  // maximum number of patients that can be stored in the system

// function prototypes
void addPatient();
void viewRecord();
void updateRecord();
void searchPatient();
void deletePatient();
void loadingAnimation(const char *text); 
void showMenu();

typedef struct // Patient structure and typedef is used to avoid writing "struct" every time we declare a variable of this type
{
    int id;            // up to 10 digits
    char name[50];     // Lastname, First Name MI.
    int age;           //
    char gender[10];   // Male or Female
    char contact[16];  // 11 digits starting with 09 (a little extra room so fgets can also consume the newline)
    char disease[100]; // illness
    char address[100];
    char birthday[16]; // MM/DD/YYYY
} Patient;

Patient patients[MAX_PATIENTS];
int patientCount = 0; //

int main()
{

    int choice = 0;

    system("cls"); // clears the console screen
    loadingAnimation("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\tLOADING");

    do
    {
        showMenu();

        printf("\n\n\t\t\t\tEnter your choice from the menu: ");
        scanf("%d", &choice);
        while (getchar() != '\n')
            ; // flush the rest of the line so leftover input never bleeds into the next screen

        switch (choice)
        {
        case 1:
            addPatient();
            break;
        case 2:
            viewRecord();
            break;
        case 3:
            searchPatient();
            break;
        case 4:
            updateRecord();
            break;
        case 5:
            deletePatient();
            break;
        case 6:
            loadingAnimation("\n\n\n\n\t\t\t\t\t\t\t\t\t  EXITING");
            break;
        default:
            printf("\n\t\t\t\tInvalid choice. Please enter 1 to 6.\n");
            break;
        }

        if (choice != 6)
        {
            printf("\n\n\t\t\t\tPress Enter to continue...");
            getchar(); // wait for the user to press Enter before showing the menu again
        }

    } while (choice != 6);

    return 0;
}

// prints then adds a "." every second, like it's counting
void loadingAnimation(const char *text)
{
    printf("\n\n\n\t\t\t\t\t\t\t%s", text);
    // fflush(stdout);

    for (int i = 0; i < 3; i++)
    {
        Sleep(1000);
        printf(".");
        fflush(stdout); // "standard output" that prints the text right away instead of waiting the buffer \n or new line
    }

    Sleep(500);
}

// clears the screen and show menu options
void showMenu()
{
    system("cls");

    printf("\n\t\t\t\t\t\t      ==========================================================\n\n");
    printf("\t\t\t\t\t             |       P A T I E N T    R E C O R D    S Y S T E M        |");
    printf("\n\n\t\t\t\t\t\t      ==========================================================\n\n");

    printf("\n\t\t\t        [1] Add Patient");
    printf("\t\t   [2] View Records");
    printf("\t\t [3] Search Patient");
    printf("\t\t[4] Update Record\n");
    printf("\n\t\t\t                  [5] Delete Patient");
    printf("\t\t     [6] Exit\n");
}

// returns 1 if the ID already belongs to another patient, 0 if it's free.
// pass excludeIndex = -1 when adding a new patient (nothing to skip);
// pass the patient's own index when editing, so keeping their current ID is still allowed.
int isDuplicateID(int id, int excludeIndex)
{
    for (int i = 0; i < patientCount; i++)
    {
        if (i != excludeIndex && patients[i].id == id) // skip the patient being edited, but check all others
            return 1;                                  // duplicate found
    }
    return 0;
}

void addPatient()
{
    int newID;

    do
    {
        printf("\n\t\t\t\tID Number                       : ");
        scanf("%d", &newID);
        while (getchar() != '\n') // flush the rest of the line so leftover input never bleeds into the next screen
            ;

        if (isDuplicateID(newID, -1))
            printf("\t\t\t\tThat ID is already used. Please enter a different one.\n");

    } while (isDuplicateID(newID, -1));

    patients[patientCount].id = newID;

    printf("\t\t\t\tName [Lastname, First Name MI.] : ");
    fgets(patients[patientCount].name, sizeof(patients[patientCount].name), stdin);
    patients[patientCount].name[strcspn(patients[patientCount].name, "\n")] = '\0';

    printf("\t\t\t\tBirthday [MM/DD/YYYY]           : ");
    fgets(patients[patientCount].birthday, sizeof(patients[patientCount].birthday), stdin); 
    patients[patientCount].birthday[strcspn(patients[patientCount].birthday, "\n")] = '\0';

    printf("\t\t\t\tAge                             : ");
    scanf("%d", &patients[patientCount].age);
    while (getchar() != '\n')
        ;

    printf("\t\t\t\tGender                          : ");
    fgets(patients[patientCount].gender, sizeof(patients[patientCount].gender), stdin);
    patients[patientCount].gender[strcspn(patients[patientCount].gender, "\n")] = '\0';

    printf("\t\t\t\tAddress                         : ");
    fgets(patients[patientCount].address, sizeof(patients[patientCount].address), stdin);
    patients[patientCount].address[strcspn(patients[patientCount].address, "\n")] = '\0';

    printf("\t\t\t\tContact Number                  : ");
    fgets(patients[patientCount].contact, sizeof(patients[patientCount].contact), stdin);
    patients[patientCount].contact[strcspn(patients[patientCount].contact, "\n")] = '\0';

    printf("\t\t\t\tIllness                         : ");
    fgets(patients[patientCount].disease, sizeof(patients[patientCount].disease), stdin);
    patients[patientCount].disease[strcspn(patients[patientCount].disease, "\n")] = '\0';

    printf("\n\t\t\t\tPatient %s has been added successfully!", patients[patientCount].name);
    patientCount++;
}

void updateRecord()
{
    int searchID;
    int found = 0;

    printf("\n\t\t\t\tPatient ID: ");
    scanf("%d", &searchID);
    while (getchar() != '\n')
        ;

    for (int i = 0; i < patientCount; i++)
    {

        if (patients[i].id == searchID)
        {

            printf("\n\t\t\t\tID Number                       : %d", patients[i].id);
            printf("\n\t\t\t\tName [Lastname, First Name MI.] : %s", patients[i].name);
            printf("\n\t\t\t\tBirthday [MM/DD/YYYY]           : %s", patients[i].birthday);
            printf("\n\t\t\t\tAge                             : %d", patients[i].age);
            printf("\n\t\t\t\tGender                          : %s", patients[i].gender);
            printf("\n\t\t\t\tAddress                         : %s", patients[i].address);
            printf("\n\t\t\t\tContact Number                  : %s", patients[i].contact);
            printf("\n\t\t\t\tIllness                         : %s\n", patients[i].disease);
            printf("\n\t\t\t\t============================================================================================\n");

            int newID;
            do
            {
                printf("\n\t\t\t\tID Number                       : ");
                scanf("%d", &newID);
                while (getchar() != '\n')
                    ;

                if (isDuplicateID(newID, i))
                    printf("\t\t\t\tThat ID is already used by another patient. Please enter a different one.\n");

            } while (isDuplicateID(newID, i));
            patients[i].id = newID;

            printf("\t\t\t   Name [Lastname, First Name MI.] : ");
            fgets(patients[i].name, sizeof(patients[i].name), stdin);
            patients[i].name[strcspn(patients[i].name, "\n")] = '\0';

            printf("\t\t\t\tBirthday [MM/DD/YYYY]          : ");
            fgets(patients[i].birthday, sizeof(patients[i].birthday), stdin);
            patients[i].birthday[strcspn(patients[i].birthday, "\n")] = '\0';

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
            fgets(patients[i].contact, sizeof(patients[i].contact), stdin);
            patients[i].contact[strcspn(patients[i].contact, "\n")] = '\0';

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
        printf("\n\t\t\t\tNo Patient Found");
        printf("\n\t\t\t\t============================================================================================\n");
    }
}

void searchPatient()
{
    int searchID;
    int found = 0;

    printf("\n\t\t\t\tPatient ID: ");
    scanf("%d", &searchID);
    while (getchar() != '\n')
        ;

    for (int i = 0; i < patientCount; i++)
    {
        if (patients[i].id == searchID)
        {
            found = 1;

            printf("\n\t\t\t\tID Number                       : %d", patients[i].id);
            printf("\n\t\t\t\tName [Lastname, First Name MI.] : %s", patients[i].name);
            printf("\n\t\t\t\tBirthday [MM/DD/YYYY]           : %s", patients[i].birthday);
            printf("\n\t\t\t\tAge                             : %d", patients[i].age);
            printf("\n\t\t\t\tGender                          : %s", patients[i].gender);
            printf("\n\t\t\t\tAddress                         : %s", patients[i].address);
            printf("\n\t\t\t\tContact Number                  : %s", patients[i].contact);
            printf("\n\t\t\t\tIllness                         : %s\n", patients[i].disease);
            printf("\n\t\t\t\t============================================================================================\n");

            break; // exit the loop after finding the patient
        }
    }

    if (found == 0)
    {
        printf("\n\t\t\t\tNo Patient Found\n");
        printf("\n\t\t\t\t============================================================================================\n");
    }
}

void viewRecord()
{

    if (patientCount <= 0)
    {
        printf("\n\t\t\t\tNo Record of Patient\n");
        printf("\n\t\t\t\t============================================================================================\n");
    }

    for (int i = 0; i < patientCount; i++)
    {
        printf("\n\t\t\t\tID Number                       : %d", patients[i].id);
        printf("\n\t\t\t\tName [Lastname, First Name MI.] : %s", patients[i].name);
        printf("\n\t\t\t\tBirthday [MM/DD/YYYY]           : %s", patients[i].birthday);
        printf("\n\t\t\t\tAge                             : %d", patients[i].age);
        printf("\n\t\t\t\tGender                          : %s", patients[i].gender);
        printf("\n\t\t\t\tAddress                         : %s", patients[i].address);
        printf("\n\t\t\t\tContact Number                  : %s", patients[i].contact);
        printf("\n\t\t\t\tIllness                         : %s\n", patients[i].disease);
        printf("\n\t\t\t\t============================================================================================\n");
    }
}

void deletePatient()
{
    int delete;
    int found = 0;
    char choice;

    printf("\n\t\t\t\tPatient ID: ");
    scanf("%d", &delete);
    while (getchar() != '\n')
        ;

    for (int i = 0; i < patientCount; i++)
    {
        if (patients[i].id == delete)
        {
            found = 1;

            printf("\n\t\t\t\tare you sure [Y] if not [N]: ");
            scanf(" %c", &choice);
            while (getchar() != '\n')
                ;

            if (choice == 'Y' || choice == 'y')
            {
                char deletedName[50]; // temporary variable to hold the name of the deleted patient
                strcpy(deletedName, patients[i].name); // copy the name of the patient to be deleted before shifting the array

                for (int j = i; j < patientCount - 1; j++)
                {
                    patients[j] = patients[j + 1]; 
                }

                printf("\n\t\t\t\tPatient %s has been deleted with the id number of %d!", deletedName, delete);

                patientCount--;
            }
            else
            {
                printf("\n\t\t\t\tDeletion cancelled.");
                printf("\n\t\t\t\t============================================================================================\n");
            }
            break;
        }
    }

    if (found == 0)
    {
        printf("\n\t\t\t\tThere is no patient with the ID number of %d.", delete);
        printf("\n\t\t\t\t============================================================================================\n");
    }
}