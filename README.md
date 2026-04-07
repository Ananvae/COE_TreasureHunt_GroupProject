# COE_TreasureHunt_GroupProject
Group member names: 
Natalie Opiela,
Ananvita Padmanabhn,
Diego Barberena,
Darianna Pando,
Ayush Kaulgud

# UT Campus Treasure Hunt — COE 301 Group Project

## How to Compile

g++ -o treasure main.cpp Clue.cpp TreasureHunt.cpp

Run from the same folder as map.txt and clues.txt:

./treasure


## How to Play

- Use W/A/S/D to move the player (@) around the map
- Walk into a landmark tile to trigger a UT trivia question
- Answer correctly to earn points
- Wrong answers on all attempts cost you half the clue's points
- Complete all 6 landmarks to win
- Drop below 0 points and it's game over

## File Structure

| File | Purpose |
|---|---|
| main.cpp | Entry point, loads files and starts the game |
| Clue.h / Clue.cpp | Clue class - question, answer, points, attempts |
| TreasureHunt.h / TreasureHunt.cpp | Main game class - map, player, score, game loop |
| map.txt | Campus map grid, loaded at runtime |
| clues.txt | Pipe-delimited trivia questions, loaded at runtime |

## Team Roles

Ayush — TreasureHunt class, game loop logic, movement and win/loss conditions
Ananvita — Clue class, file loading, answer checking and case-insensitive comparison
Natalie — Map design, clues.txt content, landmark placement and trivia research
Darianna — main.cpp, score system, pointer and reference implementation
Diego — README, testing, presentation slides

## AI Tool Usage

We used Claude (claude.ai) Sonnet 4.6 to help us debug syntax errors, talk through class design, and check our pointer/reference usage. All code was written and understood by our team.

