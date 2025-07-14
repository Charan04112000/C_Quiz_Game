#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "question.h"

struct Question questions[100];
int questionCount = 0;

void loadQuestions() {
    FILE *fp = fopen("questions.txt", "r");
    if (!fp) {
        printf("❌ Error: questions.txt not found.\n");
        exit(1);
    }

    while (!feof(fp)) {
        struct Question q;
        fscanf(fp, " %[^\n]", q.category);
        fscanf(fp, " %[^\n]", q.questionText);
        for (int i = 0; i < 4; i++)
            fscanf(fp, " %[^\n]", q.options[i]);
        fscanf(fp, "%d", &q.correctOption);
        fgetc(fp); // consume newline
        questions[questionCount++] = q;
    }

    fclose(fp);
}

void listCategories() {
    char printed[100][50];
    int printedCount = 0;

    printf("\n📂 Available Categories:\n");
    for (int i = 0; i < questionCount; i++) {
        int alreadyPrinted = 0;
        for (int j = 0; j < printedCount; j++) {
            if (strcmp(questions[i].category, printed[j]) == 0) {
                alreadyPrinted = 1;
                break;
            }
        }
        if (!alreadyPrinted) {
            strcpy(printed[printedCount++], questions[i].category);
            printf(" - %s\n", questions[i].category);
        }
    }
}

