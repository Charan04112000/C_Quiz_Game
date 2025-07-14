#ifndef QUESTION_H
#define QUESTION_H

struct Question {
    char category[50];
    char questionText[256];
    char options[4][100];
    int correctOption;
};

extern struct Question questions[100];
extern int questionCount;

void loadQuestions();
void listCategories();

#endif

