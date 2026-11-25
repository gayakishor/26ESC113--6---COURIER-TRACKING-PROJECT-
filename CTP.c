#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 50

struct Parcel
{
    int sno;
    char senderName[50];
    char receiverName[50];
    float weight;
};

void bookParcel(struct Parcel p[], int *count);
void viewParcels(struct Parcel p[], int count);
void searchParcel(struct Parcel p[], int count);

int main()
{
    struct Parcel p[MAX];
    int count = 0;
    int choice;

    do
    {
        printf("\n====================================\n");
        printf("       COURIER TRACKING SYSTEM\n");
        printf("====================================\n");
        printf("1. Book Parcel\n");
        printf("2. View All Parcels\n");
        printf("3. Search Parcel by S.No.\n");
        printf("4. Exit\n");
        printf("------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            continue;
        }

        while (getchar() != '\n');

        switch (choice)
        {
            case 1:
                bookParcel(p, &count);
                break;

            case 2:
                viewParcels(p, count);
                break;

            case 3:
                searchParcel(p, count);
                break;

            case 4:
                printf("\nThank you for using the system!\n");
                break;

            default:
                printf("\nInvalid choice! Try again.\n");
        }

    } while (choice != 4);

    return 0;
}

// Function to book a parcel
void bookParcel(struct Parcel p[], int *count)
{
    if (*count >= MAX)
    {
        printf("\nParcel register is full!\n");
        return;
    }

    printf("\nEnter sender name: ");
    fgets(p[*count].senderName, 50, stdin);
    p[*count].senderName[strcspn(p[*count].senderName, "\n")] = '\0';

    printf("Enter receiver name: ");
    fgets(p[*count].receiverName, 50, stdin);
    p[*count].receiverName[strcspn(p[*count].receiverName, "\n")] = '\0';

    printf("Enter parcel weight (kg): ");

    char input[50];
    char *end;
    float weight;

    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        printf("Invalid input!\n");
        return;
    }

    weight = strtof(input, &end);

    while (isspace((unsigned char)*end))
        end++;

    if (end == input || *end != '\0' || weight <= 0)
    {
        printf("Invalid weight! Weight must be positive.\n");
        return;
    }

    p[*count].weight = weight;
    p[*count].sno = *count + 1;

    (*count)++;

    printf("\nParcel booked successfully!\n");
    printf("S.No. = %d\n", p[*count - 1].sno);
}

// Function to view all parcels
void viewParcels(struct Parcel p[], int count)
{
    int i;

    if (count == 0)
    {
        printf("\nNo parcels booked yet!\n");
        return;
    }

    printf("\n================ ALL PARCELS ================\n");
    printf("%-8s %-20s %-20s %-10s\n",
           "S.No.", "Sender", "Receiver", "Weight");

    for (i = 0; i < count; i++)
    {
        printf("%-8d %-20s %-20s %-10.2f\n",
               p[i].sno,
               p[i].senderName,
               p[i].receiverName,
               p[i].weight);
    }
}

// Function to search parcel
void searchParcel(struct Parcel p[], int count)
{
    int sno, i, found = 0;

    printf("\nEnter S.No. to search: ");

    if (scanf("%d", &sno) != 1)
    {
        printf("Invalid serial number!\n");
        while (getchar() != '\n');
        return;
    }

    while (getchar() != '\n');

    for (i = 0; i < count; i++)
    {
        if (p[i].sno == sno)
        {
            printf("\nParcel found!\n");
            printf("S.No.       : %d\n", p[i].sno);
            printf("Sender      : %s\n", p[i].senderName);
            printf("Receiver    : %s\n", p[i].receiverName);
            printf("Weight      : %.2f kg\n", p[i].weight);

            found = 1;
            break;
        }
    }

    if (found == 0)
    {
        printf("\nNo parcel found with S.No. %d\n", sno);
    }
}
