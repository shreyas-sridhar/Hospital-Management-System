#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    char bloodGroup[4];
    char severity[10];
} Patient;

void swap(Patient* a, Patient* b) {
    Patient temp = *a;
    *a = *b;
    *b = temp;
}


int partition(Patient arr[], int low, int high) {
    Patient pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (strcmp(arr[j].bloodGroup, pivot.bloodGroup) < 0) {
            i++;
            swap(&arr[i], &arr[j]);
        } else if (strcmp(arr[j].bloodGroup, pivot.bloodGroup) == 0) {
            if (strcmp(arr[j].severity, pivot.severity) < 0) {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

int part(Patient arr[], int low, int high) {
    Patient pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (strcmp(arr[j].severity, pivot.severity) < 0) {
            i++;
            swap(&arr[i], &arr[j]);
        } else if (strcmp(arr[j].severity, pivot.severity) == 0) {
            if (strcmp(arr[j].bloodGroup, pivot.bloodGroup) < 0) {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}


void quicksort(Patient arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}
void qc(Patient arr[], int low, int high) {
    if (low < high) {
        int pi = part(arr, low, high);
        qc(arr, low, pi - 1);
        qc(arr, pi + 1, high);
    }
}

int binarySearch(Patient arr[], int left, int right, char* bloodGroup) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (strcmp(arr[mid].bloodGroup, bloodGroup) == 0)
            return mid;

        if (strcmp(arr[mid].bloodGroup, bloodGroup) < 0)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int bs(Patient arr[], int left, int right, char* severity) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (strcmp(arr[mid].severity, severity) == 0)
            return mid;

        if (strcmp(arr[mid].severity, severity) < 0)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int main() {
    int numPatients;
    printf("Enter the number of patients: ");
    scanf("%d", &numPatients);
    if (numPatients<=0)
    {
        printf("Invalid number of patients");
        return 0;
    }
    

    Patient* patients = (Patient*)malloc(numPatients * sizeof(Patient));

    printf("\nEnter patient details:\n");
    for (int i = 0; i < numPatients; i++) {
        printf("Patient %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", patients[i].name);
        printf("Blood Group: ");
        scanf("%s", patients[i].bloodGroup);
        printf("Severity: ");
        scanf("%s", patients[i].severity);
    }

    // Sort the patients using quicksort

    printf("\n--- Menu ---\n");
    printf("1. Search for a patient by blood group or severity\n");
    printf("2. Exit\n");

    int choice;
    char searchBloodGroup[4];
    char searchSeverity[10];

    printf("\nEnter your choice 1 for blood group and 2 for severity: ");
    scanf("%d", &choice);

    if (choice==1)
    {
    quicksort(patients, 0, numPatients - 1);
        while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter the blood group to search: ");
                scanf("%s", searchBloodGroup);

                int result = binarySearch(patients, 0, numPatients - 1, searchBloodGroup);

                if (result == -1) {
                    printf("No patients found with the given blood group.\n");
                } else {
                    printf("Found patient:\n");
                    printf("Name: %s\n", patients[result].name);
                    printf("Blood Group: %s\n", patients[result].bloodGroup);
                }
                break;

            case 2:
                free(patients);
                printf("\nProgram exited.\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
    }

    else if (choice==2)
    {
    qc(patients, 0, numPatients - 1);
        while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter the severity to search: ");
                scanf("%s", searchSeverity);

                int result = bs(patients, 0, numPatients - 1, searchSeverity);

                if (result == -1) {
                    printf("No patients found with the given severity.\n");
                } else {
                    printf("Found patient:\n");
                    printf("Name: %s\n", patients[result].name);
                    printf("Severity: %s\n", patients[result].severity);
                }
                break;

            case 2:
                free(patients);
                printf("\nProgram exited.\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
    }
    else
    {
        printf("Invalid choice. Please try again.\n");
    }
    return 0;
}

