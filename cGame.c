#include <stdio.h>

int main() {
    int score = 0;
    int answer;

    printf("Welcome to the Quiz Game!\n\n");

    // Question 1
    printf("1. Who is the father of C language?\n");
    printf("1) Dennis Ritchie\n2) James Gosling\n3) Bjarne Stroustrup\n4) Guido van Rossum\n");
    printf("Enter your answer: ");
    scanf("%d", &answer);

    if(answer == 1) {
        printf("Correct!\n\n");
        score++;
    } else {
        printf("Wrong! Correct answer: Dennis Ritchie\n\n");
    }

    // Question 2
    printf("2. Which symbol is used for comments in C?\n");
    printf("1) // 2) ## 3) ** 4) @@\n");
    printf("Enter your answer: ");
    scanf("%d", &answer);

    if(answer == 1) {
        printf("Correct!\n\n");
        score++;
    } else {
        printf("Wrong! Correct answer: //\n\n");
    }

    // Question 3
    printf("3. Which function is used for input in C?\n");
    printf("1) printf() 2) scanf() 3) input() 4) cin\n");
    printf("Enter your answer: ");
    scanf("%d", &answer);

    if(answer == 2) {
        printf("Correct!\n\n");
        score++;
    } else {
        printf("Wrong! Correct answer: scanf()\n\n");
    }

    printf("Quiz Finished!\n");
    printf("Your Final Score: %d/3\n", score);

    return 0;
}