#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>

#define MAX_TEXT 256

struct Question {
    char statement[MAX_TEXT];
    char options[4][MAX_TEXT];
    char correct;
};

void runQuiz(const char *filename, const char *level, const char *username);
void chat(int q, int right, int wrong, const char *username, const char *level);
void clearScreen() {
    system("cls");
}

void viewScores();
void viewRules();
void viewHelp();
void changeTheme();

int main() {
    clearScreen();
    system("color 5F");

    char username[50];
    int valid = 0;

    while (!valid) {
    printf("\n\t\t\t\t       Loading Quiz Zone");
for (int i = 0; i < 5; i++) {
    Sleep(500);
    printf(".");
    fflush(stdout);
}
printf("\n\n");

        printf("\t\t\t\t-------------------------------\n");
        printf("\t\t\t\t     WELCOME TO QUIZ ZONE      \n");
        printf("\t\t\t\t-------------------------------\n");
        printf("\t\t\t\t     Enter your name: ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = 0;

        valid = 1;
        for (int i = 0; i < strlen(username); i++) {
            if (!isalpha(username[i]) && username[i] != ' ') {
                valid = 0;
                break;
            }
        }

        if (strlen(username) == 0 || !valid) {
            printf("\nInvalid name. Use only alphabets. Try again.\n\n");
        }
    }

    int menuChoice;
    do {
        clearScreen();
        printf("\n\t\t\t\t=========== MAIN MENU ===========\n");
        printf("\t\t\t\t1. Start Quiz\n");
        printf("\t\t\t\t2. View Past Score\n");
        printf("\t\t\t\t3. View Rules\n");
        printf("\t\t\t\t4. Help/About\n");
        printf("\t\t\t\t5. Exit\n");
        printf("\t\t\t\t6. Change Theme\n");
        printf("\t\t\t\tEnter your choice: ");
        scanf("%d", &menuChoice);
        getchar();

        switch (menuChoice) {
            case 1: {
                int levelChoice;
                do {
                    clearScreen();
                    printf("\t\t\t\t===============================\n");
                    printf("\t\t\t\t         SELECT LEVEL          \n");
                    printf("\t\t\t\t===============================\n");
                    printf("\t\t\t\t1. Easy\n");
                    printf("\t\t\t\t2. Intermediate\n");
                    printf("\t\t\t\t3. Hard\n");
                    printf("\t\t\t\t4. Back to Main Menu\n");
                    printf("\t\t\t\tEnter your choice: ");
                    scanf("%d", &levelChoice);
                    getchar();

                    if (levelChoice == 1)
                        runQuiz("easy.txt", "Easy", username);
                    else if (levelChoice == 2)
                        runQuiz("inter.txt", "Intermediate", username);
                    else if (levelChoice == 3)
                        runQuiz("hard.txt", "Hard", username);
                } while (levelChoice != 4);
                break;
            }
            case 2: viewScores(); break;
            case 3: viewRules(); break;
            case 4: viewHelp(); break;
            case 5: printf("\n\t\t\t\tThanks for using Quiz Zone!\n"); break;
            case 6: changeTheme(); break;
            default:
                printf("Invalid choice. Press Enter to try again...");
                getchar();
        }

    } while (menuChoice != 5);

    return 0;
}

void runQuiz(const char *filename, const char *level, const char *username) {
    clearScreen();
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("File not found!\n");
        return;
    }

    struct Question qList[100];
    int total = 0;
    while (fgets(qList[total].statement, MAX_TEXT, fp)) {
        for (int i = 0; i < 4; i++) {
            fgets(qList[total].options[i], MAX_TEXT, fp);
        }
        fscanf(fp, " %c\n", &qList[total].correct);
        total++;
    }
    fclose(fp);

    srand(time(NULL));
    for (int i = 0; i < total - 1; i++) {
        int j = i + rand() % (total - i);
        struct Question temp = qList[i];
        qList[i] = qList[j];
        qList[j] = temp;
    }

    int num;
    do {
        printf("\nHow many Questions do You Want To answer (1-%d)? ", total);
        if (scanf("%d", &num) != 1 || num < 1 || num > total) {
            printf("Invalid number. Try again.\n");
            while (getchar() != '\n');
        } else {
            break;
        }
    } while (1);

    int right = 0, wrong = 0;
    for (int i = 0; i < num; i++) {
        clearScreen();
        printf("Q%d: %s\n", i + 1, qList[i].statement);
        for (int j = 0; j < 4; j++) printf(" %s\n", qList[i].options[j]);

        char choice;
        do {
            printf("Enter your choice (A/B/C/D): ");
            scanf(" %c", &choice);
            choice = toupper(choice);
            if (choice < 'A' || choice > 'D') printf("Invalid input. Try again.\n");
        } while (choice < 'A' || choice > 'D');

        if (choice == toupper(qList[i].correct)) {
            right++;
            Beep(1000, 300);
            printf("\nCorrect Answer!\n");
        } else {
            wrong++;
            printf("\nWrong Answer! Correct option was: %c\n", toupper(qList[i].correct));
        }
        Sleep(1500);
    }

    chat(num, right, wrong, username, level);
    printf("\nPress Enter to return to menu...");
    getchar(); getchar();
}

void chat(int q, int right, int wrong, const char *username, const char *level) {
    clearScreen();
    printf("\n===================== RESULT SUMMARY =====================\n");
    printf("User Name      : %s\n", username);
    printf("Level          : %s\n", level);
    printf("Total Attempted: %d\n", q);
    printf("Correct Answers: %d\n", right);
    printf("Wrong Answers  : %d\n", wrong);
    printf("Marks Obtained : %d / %d\n", right * 4, q * 4);
    int per = (right * 100) / q;
    char comment[50];
    if (per >= 90) strcpy(comment, "Excellent");
    else if (per >= 80) strcpy(comment, "Very Good");
    else if (per >= 70) strcpy(comment, "Good");
    else if (per >= 60) strcpy(comment, "Average");
    else if (per >= 50) strcpy(comment, "Below Average");
    else strcpy(comment, "Poor");
    printf("Comment        : %s\n", comment);
    printf("==========================================================\n");

    FILE *f = fopen("scores.txt", "w");
    if (f) {
        fprintf(f, "==========================================\n");
        fprintf(f, "--------------------------------------\n");
        fprintf(f, "User    : %s\n", username);
        fprintf(f, "Level   : %s\n", level);
        fprintf(f, "Score   : %d / %d\n", right * 4, q * 4);
        fprintf(f, "Comment : %s\n", comment);
        fprintf(f, "--------------------------------------\n\n");
        fprintf(f, "==========================================\n\n");
        fclose(f);
    }
}

void viewScores() {
    clearScreen();
    FILE *f = fopen("scores.txt", "r");
    if (!f) {
        printf("No past scores found!\n");
    } else {
        char line[256];
        while (fgets(line, sizeof(line), f)) {
            printf("%s", line);
        }
        fclose(f);
    }
    printf("\nPress Enter to return to menu...");
    getchar();
}

void viewRules() {
    clearScreen();
    printf("\n=============== QUIZ RULES ===============\n");
    printf("1. Choose a difficulty level to begin the quiz.\n");
    printf("2. Each question has four options (A/B/C/D).\n");
    printf("3. One correct answer per question.\n");
    printf("4. Each correct answer awards 4 marks.\n");
    printf("5. No negative marking for wrong answers.\n");
    printf("==========================================\n");
    printf("\nPress Enter to return to menu...");
    getchar();
}

void viewHelp() {
    clearScreen();
    printf("\n=============== HELP / ABOUT ===============\n");
    printf("This Quiz App is developed to test general knowledge.\n");
    printf("Developed by: Fozia\n");
    printf("Version: 1.0\n");
    printf("Use arrow keys and input prompts to navigate.\n");
    printf("============================================\n");
    printf("\nPress Enter to return to menu...");
    getchar();
}

void changeTheme() {
    clearScreen();
    int themeChoice;
    printf("\n\n\t\t\t\t============= THEME SELECTION =============\n");
    printf("\t\t\t\t1. Blue Theme\n");
    printf("\t\t\t\t2. Green Theme\n");
    printf("\t\t\t\t3. Purple Theme\n");
    printf("\t\t\t\t4. Yellow Theme\n");
    printf("\t\t\t\t5. Red Theme\n");
    printf("\t\t\t\t6. Cancel\n");
    printf("\t\t\t\tChoose a theme (1-6): ");
    scanf("%d", &themeChoice);
    getchar();

    switch (themeChoice) {
        case 1: system("color 1F"); break;
        case 2: system("color 2F"); break;
        case 3: system("color 5F"); break;
        case 4: system("color 6F"); break;
        case 5: system("color 4F"); break;
        case 6: break;
        default: printf("Invalid choice.\n"); break;
    }
}
