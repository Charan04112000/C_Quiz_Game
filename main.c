#include <stdio.h>
#include <string.h>
#include "quiz.h"
#include "user.h"
#include "question.h"

int main() {
    char username[50], category[50];

    user_login(username);
    show_user_history(username);

    loadQuestions();
    listCategories();

    printf("\nEnter category (or 'ALL' for all questions): ");
    scanf("%s", category);

    startQuiz(category, username);

    show_leaderboard(category);
    return 0;
}

