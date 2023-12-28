#include <stdio.h>
#include <stdbool.h>
#include <ctype.h> // Include for toupper()

#define MAX_MOVIES 5
#define MAX_TIME_SLOTS 3
#define MAX_THEATERS 2

#define ROWS 10
#define SEATS 10

bool seats[MAX_MOVIES][MAX_TIME_SLOTS][MAX_THEATERS][ROWS][SEATS];

void displayLayout(int movie, int timeSlot, int theater) {
    printf("Seating Layout for %d: %d - %d:\n", movie + 1, timeSlot + 1, theater + 1);
    printf("-------------SCREEN------------\n");
    printf("   1  2  3  4  5  6  7  8  9 10\n");

    for (int i = 0; i < ROWS; i++) {
        printf("%c ", 'A' + i);
        for (int j = 0; j < SEATS; j++) {
            if (seats[movie][timeSlot][theater][i][j])
                printf("[X]"); // Booked seat
            else
                printf("[ ]"); // Available seat
        }
        printf("\n");
    }
    printf("--------------------------------\n");
}

void bookSeat(int movie, int timeSlot, int theater, int row, int seat,
              char movies[MAX_MOVIES][50], char timeSlots[MAX_TIME_SLOTS][10],
              char theaters[MAX_THEATERS][20]) {
    if (row >= 0 && row < ROWS && seat >= 0 && seat < SEATS) {
        if (!seats[movie][timeSlot][theater][row][seat]) {
            seats[movie][timeSlot][theater][row][seat] = true;
            printf("Seat %c%d booked successfully for %s at %s in %s.\n", 'A' + row, seat + 1,
                   movies[movie], timeSlots[timeSlot], theaters[theater]);
        } else {
            printf("Seat %c%d is already booked.\n", 'A' + row, seat + 1);
        }
    } else {
        printf("Invalid seat selection.\n");
    }
}

int main() {
    char movies[MAX_MOVIES][50] = {
        "Avengers: Endgame",
        "The Dark Knight",
        "Inception",
        "Pulp Fiction",
        "Fight Club"
    };

    char timeSlots[MAX_TIME_SLOTS][10] = {
        "10:00 AM",
        "02:00 PM",
        "06:00 PM"
    };

    char theaters[MAX_THEATERS][20] = {
        "Theater 1",
        "Theater 2"
    };

    int movieChoice, timeSlotChoice, theaterChoice;

    printf("Available Movies:\n");
    for (int i = 0; i < MAX_MOVIES; i++) {
        printf("%d. %s\n", i + 1, movies[i]);
    }

    printf("Enter the movie number: ");
    scanf("%d", &movieChoice);
    movieChoice--;

    printf("Available Time Slots:\n");
    for (int i = 0; i < MAX_TIME_SLOTS; i++) {
        printf("%d. %s\n", i + 1, timeSlots[i]);
    }

    printf("Enter the time slot number: ");
    scanf("%d", &timeSlotChoice);
    timeSlotChoice--;

    printf("Available Theaters:\n");
    for (int i = 0; i < MAX_THEATERS; i++) {
        printf("%d. %s\n", i + 1, theaters[i]);
    }

    printf("Enter the theater number: ");
    scanf("%d", &theaterChoice);
    theaterChoice--;

    // Initialize all seats as available
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < SEATS; j++) {
            seats[movieChoice][timeSlotChoice][theaterChoice][i][j] = false;
        }
    }

    char choice;
    int row, seat;

    while (true) {
        displayLayout(movieChoice, timeSlotChoice, theaterChoice);

        printf("\nMenu:\n");
        printf("1. Book a seat\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                printf("Enter the row (A-J): ");
                scanf(" %c", &choice);
                choice = toupper(choice);
                row = choice - 'A';

                printf("Enter the seat number (1-10): ");
                scanf("%d", &seat);
                seat--;

                bookSeat(movieChoice, timeSlotChoice, theaterChoice, row, seat,
                         movies, timeSlots, theaters);
                break;
            case '2':
                printf("Thank you for using the ticket booking system.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
