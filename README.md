# Cricket Score Simulator

This is a simple **Cricket Score Simulation** program written in C. It allows users to input team details, play an innings-by-innings simulation of a cricket match, and track scores, wickets, extras, and overs dynamically.

## Features
- Two teams with customizable player names.
- Toss to decide which team bats first.
- Ball-by-ball input for events like runs, wickets, and extras.
- Automatic scoreboard updates after each event.
- Ensures that extra deliveries (wide/no-ball) do not count towards the ball count.
- Displays the final match result based on scores.

## How to Use
1. Compile the program using a C compiler:
   ```sh
   gcc cricket_score_simulator.c -o cricket_sim
   ```
2. Run the executable:
   ```sh
   ./cricket_sim
   ```
3. Enter details for both teams when prompted.
4. Input the number of overs for the match.
5. Play ball-by-ball by entering valid events (e.g., `one`, `four`, `wicket`, `wide`, etc.).
6. The match will progress automatically, updating the scoreboard after every ball.
7. The final result is displayed at the end of the game.

## Valid Ball Events
- `dot` - No run scored
- `one`, `two`, `three`, `four`, `six` - Runs scored
- `wicket` - Striker gets out
- `wide`, `no-ball` - Extra run awarded, ball is not counted
- `bye`, `leg-bye` - Extra run awarded, ball is counted

## Future Enhancements
- Track individual player scores and bowler statistics.
- Add more match formats (T20, ODI, Test mode).
- Implement a graphical user interface (GUI).
- Implement a database connectivity to keep track of player, team details and records.

