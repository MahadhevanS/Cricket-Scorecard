#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PLAYERS 11
#define MAX_NAME_LEN 30

struct Team {
    char name[50];
    char players[MAX_PLAYERS][MAX_NAME_LEN];
};

int total_overs = 0;

void swap_strikers(int *striker, int *non_striker) {
    int temp = *striker;
    *striker = *non_striker;
    *non_striker = temp;
}

void display_scoreboard(struct Team batting_team, struct Team bowling_team, int striker, int non_striker, int bowler, int score, int wickets, int extras, int over, int balls) {
    printf("\n---------------------------------------------------\n");
    printf("Batting: %s\n", batting_team.name);
    printf("Striker: %s\tNon-Striker: %s\n",
           batting_team.players[striker],
           batting_team.players[non_striker]);
    printf("Bowling: %s\n", bowling_team.name);
    printf("Bowler: %s\n", bowling_team.players[bowler]);
    printf("Over: %d.%d\tScore: %d/%d\tExtras: %d\n",
           over, balls, score, wickets, extras);
    printf("---------------------------------------------------\n");
}

void process_event(char event[], int *score, int *wickets, int *extras, int *next_batsman, int *striker, struct Team *batting_team) {
    if (strcmp(event, "one") == 0) {
        (*score) += 1;
    } else if (strcmp(event, "two") == 0) {
        (*score) += 2;
    } else if (strcmp(event, "three") == 0) {
        (*score) += 3;
    } else if (strcmp(event, "four") == 0) {
        (*score) += 4;
    } else if (strcmp(event, "six") == 0) {
        (*score) += 6;
    } else if (strcmp(event, "wicket") == 0) {
        (*wickets)++;
        if (*wickets < MAX_PLAYERS - 1) {
            printf("Wicket! %s is out.\n", batting_team->players[*striker]);
            *striker = *next_batsman;
            (*next_batsman)++;
            printf("New batsman: %s\n", batting_team->players[*striker]);
        } else {
            printf("All out!\n");
        }
    } else if (strcmp(event, "wide") == 0 || strcmp(event, "no-ball") == 0) {
        (*extras)++;
        (*score)++;
    } else if (strcmp(event, "bye") == 0 || strcmp(event, "leg-bye") == 0) {
        (*extras)++;
        (*score)++;
    } else if (strcmp(event, "dot") == 0) {
        // No run
    } else {
        printf("Invalid input. Try again.\n");
    }
}

int innings(struct Team batting_team, struct Team bowling_team, int target) {
    int score = 0, wickets = 0, extras = 0, over = 0, balls = 0;
    int striker = 0, non_striker = 1, next_batsman = 2, bowler = MAX_PLAYERS - 1;

    while (over < total_overs && wickets < MAX_PLAYERS - 1) {
        display_scoreboard(batting_team, bowling_team, striker, non_striker, bowler, score, wickets, extras, over, balls);

        char event[20];
        printf("Enter event: ");
        fgets(event, sizeof(event), stdin);
        event[strcspn(event, "\n")] = '\0';

        process_event(event, &score, &wickets, &extras, &next_batsman, &striker, &batting_team);

        if(!strcmp(event,"wide") && !strcmp(event,"no-ball")){
            balls++;
        }
        if (strcmp(event, "one") == 0 || strcmp(event, "three") == 0) {
            swap_strikers(&striker, &non_striker);
        }

        if (target > 0 && score > target) {
            printf("\nTarget achieved! Innings over.\n");
            break;
        }

        if (balls == 7) {
            over++;
            balls = 1;
            swap_strikers(&striker, &non_striker);
            bowler--;
            if (bowler < MAX_PLAYERS / 2)
                bowler = MAX_PLAYERS - 1;
            printf("\n--- New Over ---\n");
        }
    }

    printf("\nInnings Complete: %s scored %d/%d (Extras: %d)\n", batting_team.name, score, wickets, extras);
    return score;
}

void get_team_details(struct Team *team) {
    printf("Enter team name: ");
    fgets(team->name, sizeof(team->name), stdin);
    team->name[strcspn(team->name, "\n")] = '\0';

    printf("Enter player names for %s:\n", team->name);
    for (int i = 0; i < MAX_PLAYERS; i++) {
        printf("Player %d: ", i + 1);
        fgets(team->players[i], MAX_NAME_LEN, stdin);
        team->players[i][strcspn(team->players[i], "\n")] = '\0';
    }
}

int main() {
    srand(time(NULL));
    struct Team t1, t2;

    printf("Enter details for Home Team:\n");
    get_team_details(&t1);

    printf("\nEnter details for Opponent Team:\n");
    get_team_details(&t2);

    printf("\nEnter number of overs: ");
    scanf("%d", &total_overs);
    getchar(); // Clear newline after scanf

    int first_innings_score, second_innings_score;
    int toss = rand() % 2;

    if (toss == 0) {
        printf("\nToss: %s won and chose to bat first.\n", t1.name);
        printf("\n--- First Innings ---\n");
        first_innings_score = innings(t1, t2, 0);

        printf("\n--- Second Innings ---\n");
        second_innings_score = innings(t2, t1, first_innings_score);

        if (second_innings_score > first_innings_score) {
            printf("\nResult: %s won by %d wickets!\n", t2.name, MAX_PLAYERS - 1 - (second_innings_score - first_innings_score));
        } else if (second_innings_score < first_innings_score) {
            printf("\nResult: %s won by %d runs!\n", t1.name, first_innings_score - second_innings_score);
        } else {
            printf("\nResult: Match Tied!\n");
        }

    } else {
        printf("\nToss: %s won and chose to bat first.\n", t2.name);
        printf("\n--- First Innings ---\n");
        first_innings_score = innings(t2, t1, 0);

        printf("\n--- Second Innings ---\n");
        second_innings_score = innings(t1, t2, first_innings_score);

        if (second_innings_score > first_innings_score) {
            printf("\nResult: %s won by %d wickets!\n", t1.name, MAX_PLAYERS - 1 - (second_innings_score - first_innings_score));
        } else if (second_innings_score < first_innings_score) {
            printf("\nResult: %s won by %d runs!\n", t2.name, first_innings_score - second_innings_score);
        } else {
            printf("\nResult: Match Tied!\n");
        }
    }

    return 0;
}
