#include "quiz.h"
#include "timer.h"
#include "user.h"
#include "question.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern volatile sig_atomic_t time_up;

void shuffle(int *arr, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

void startQuiz(const char *selectedCategory, const char *username) {
    int filtered[100], count = 0, score = 0, answer;
    int incorrect[100], incorrectCount = 0;

    if (strcmp(selectedCategory, "ALL") == 0) {
        for (int i = 0; i < questionCount; i++) filtered[count++] = i;
    } else {
        for (int i = 0; i < questionCount; i++) {
            if (strcmp(questions[i].category, selectedCategory) == 0)
                filtered[count++] = i;
        }
    }

    if (count == 0) {
        printf("❌ No questions in this category.\n");
        return;
    }

    shuffle(filtered, count);

    for (int i = 0; i < count; i++) {
        struct Question q = questions[filtered[i]];
        printf("\n📍 Question %d of %d\n", i + 1, count);
        printf("%s\n", q.questionText);
        for (int j = 0; j < 4; j++) {
            printf("  %d. %s\n", j + 1, q.options[j]);
        }

        setup_timer();
        if (scanf("%d", &answer) != 1 || time_up || answer < 1 || answer > 4) {
            printf("❌ Wrong or Timed out.\n");
            incorrect[incorrectCount++] = filtered[i];
            disable_timer();
            continue;
        }
        disable_timer();

        if (answer - 1 == q.correctOption) {
            printf("✅ Correct!\n");
            score++;
        } else {
            printf("❌ Incorrect. Correct: %s\n", q.options[q.correctOption]);
            incorrect[incorrectCount++] = filtered[i];
        }
    }

    // Save score
    FILE *fp = fopen("scores.txt", "a");
    time_t now = time(NULL);
    fprintf(fp, "%s|%s|%d/%d|%s", username, selectedCategory, score, count, ctime(&now));
    fclose(fp);

    // Save incorrect questions
    FILE *mistakeFile = fopen("mistakes.txt", "w");
    for (int i = 0; i < incorrectCount; i++) {
        struct Question q = questions[incorrect[i]];
        fprintf(mistakeFile, "%s|%s\n", q.category, q.questionText);
    }
    fclose(mistakeFile);

    // Retry
    if (incorrectCount > 0) {
        printf("\n🔁 Retry Incorrect Questions:\n");
        for (int i = 0; i < incorrectCount; i++) {
            struct Question q = questions[incorrect[i]];
            printf("\n%s\n", q.questionText);
            for (int j = 0; j < 4; j++) {
                printf("  %d. %s\n", j + 1, q.options[j]);
            }
            scanf("%d", &answer);
            if (answer - 1 == q.correctOption)
                printf("✅ Correct this time!\n");
            else
                printf("❌ Still wrong.\n");
        }
    }

    printf("\n✅ Quiz Completed. Score: %d/%d\n", score, count);
}

