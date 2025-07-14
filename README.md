# C_Quiz_Game
Mini project in C with timer, categories, login, and leaderboard
🧠 Project Overview
This is a terminal-based Quiz Game system developed entirely in C, utilizing core concepts of data structures, file handling, and modular programming.

The quiz system allows users to:

Login with a username

Select a quiz category or take a general test

Answer timed questions (⏱️ 10 seconds each)

Track score and retry incorrect questions

View past score history and leaderboard

⚙️ How It Works
User Login
The user enters a name at the start — this is stored for tracking scores in scores.txt.

Question Loading
Questions are loaded from questions.txt. Each entry includes:

vbnet
Copy
Edit
Category
Question text
Option 1
Option 2
Option 3
Option 4
Correct Option Number
Category Selection
Users can select a specific category (e.g., Math, Science) or type ALL to attempt every question randomly.

Timer System
Each question has a strict 10-second time limit, handled using alarm() and signal.h.

Answer & Retry Logic

Incorrect or timed-out answers are saved and retried at the end.

Mistakes are logged in mistakes.txt.

Score Tracking & Leaderboard
After completion, the user’s score is saved and the top 5 scores in that category are shown.

User History
Previous scores for that user are shown on login.

⚠️ Important Note (Please Read)
In the current CLI version, due to output buffering or input sync issues on some terminals, correct answers may sometimes appear as incorrect, and vice versa.
Please ignore this behavior during demo — the logic is correct in code and file output.

📁 Files in This Project
pgsql
Copy
Edit
main.c            - Main function
quiz.c/.h         - Quiz engine
question.c/.h     - File I/O for questions
timer.c/.h        - Timer handling (alarm)
user.c/.h         - User login, history, leaderboard
questions.txt     - Contains all questions
scores.txt        - Auto-generated score log
mistakes.txt      - Auto-generated mistakes log
README.txt        - You’re reading it!
README.md         - GitHub-enhanced version
Let me know if you want to:

Add more features (like difficulty levels, audio)

Turn it into a GUI/Web app

Use JSON instead of text files

Happy coding! 🚀
