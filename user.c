#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

void user_login(char *username) {
    printf("Enter your username: ");
    scanf("%s", username);
}

void show_user_history(const char *username) {
    FILE *fp = fopen("scores.txt", "r");
    char line[256];
    if (!fp) return;

    printf("\n📜 Your Quiz History:\n");
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, username)) {
            printf("%s", line);
        }
    }
    fclose(fp);
}

void show_leaderboard(const char *category) {
    struct Entry {
        char user[50];
        char cat[50];
        int score;
    } entries[100];

    FILE *fp = fopen("scores.txt", "r");
    char line[256];
    int count = 0;
    if (!fp) return;

    while (fgets(line, sizeof(line), fp)) {
        char user[50], cat[50], time[50];
        int score, total;
        sscanf(line, "%[^|]|%[^|]|%d/%d|%s", user, cat, &score, &total, time);
        if (strcmp(cat, category) == 0) {
            strcpy(entries[count].user, user);
            strcpy(entries[count].cat, cat);
            entries[count].score = score;
            count++;
        }
    }
    fclose(fp);

    // Sort top 5
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (entries[j].score > entries[i].score) {
                struct Entry tmp = entries[i];
                entries[i] = entries[j];
                entries[j] = tmp;
            }
        }
    }

    printf("\n🏆 Top 5 Scores in %s:\n", category);
    for (int i = 0; i < count && i < 5; i++) {
        printf("%d. %s - %d\n", i + 1, entries[i].user, entries[i].score);
    }
}

