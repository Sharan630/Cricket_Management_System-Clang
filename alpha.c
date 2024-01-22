#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEAMS 5
#define MAX_PLAYERS_PER_TEAM 10
#define MAX_NAME_LENGTH 50

// Define structures for player and team
struct Player {
    char name[MAX_NAME_LENGTH];
    int teamIndex_w;
    int teamIndex_r;
    int runs;
    int wickets;
};

struct Team {
    char name[MAX_NAME_LENGTH];
    char coach_name[MAX_NAME_LENGTH];
    int points;
    int matches_played;
    int matches_won;
    struct Player players[MAX_PLAYERS_PER_TEAM];
    int numPlayers;
};

// Function prototypes
void saveData(struct Team teams[], int numTeams);
void loadData(struct Team teams[], int *numTeams);
void addTeam(struct Team teams[], int *numTeams);
void addPlayer(struct Team teams[], int numTeams);
void updatePlayerInfo(struct Team teams[], int numTeams);
void viewPointsTable(struct Team teams[], int numTeams);
void viewTopWicketTakers(struct Team teams[], int numTeams);
void viewTopRunScorers(struct Team teams[], int numTeams);
void displayTeamWithHighestRunScorer(struct Team teams[], int numTeams);
void tournament(struct Team teams[], int numTeams);
void sortTeamsByPoints(struct Team teams[], int numTeams);
void sortPlayersByWickets(struct Player players[], int totalPlayers);
void sortPlayersByRuns(struct Player players[], int totalPlayers);


int main() {
    struct Team teams[MAX_TEAMS];
    for (int i = 0; i < MAX_TEAMS; i++)
    {
        teams[i].matches_played=0;
        teams[i].matches_won=0;
    }
    int numTeams = 0;
    int choice;

    loadData(teams, &numTeams);

    do {
        printf("\n1. Add Team\n");
        printf("2. Add Player\n");
        printf("3. Update Player Information\n");
        printf("4. View Points Table\n");
        printf("5. View Top Wicket-Takers\n");
        printf("6. View Top Run-Scorers\n");
        printf("7. Display Team with Highest Run-Scorer\n");
        printf("8. Tournament\n");
        printf("9.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTeam(teams, &numTeams);
                saveData(teams, numTeams);
                break;
            case 2:
                addPlayer(teams, numTeams);
                break;
            case 3:
                updatePlayerInfo(teams, numTeams);
                break;
            case 4:
                sortTeamsByPoints(teams, numTeams);
                viewPointsTable(teams, numTeams);
                break;
            case 5:
                viewTopWicketTakers(teams, numTeams);
                break;
            case 6:
                viewTopRunScorers(teams, numTeams);
                break;
            case 7:
                displayTeamWithHighestRunScorer(teams, numTeams);
                break;
            case 8:
                tournament(teams, numTeams);
            case 9:
                saveData(teams, numTeams);
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 8);

    return 0;
}
void sortTeamsByPoints(struct Team teams[], int numTeams) {
    int i, j;
    struct Team temp;

    for (i = 0; i < numTeams - 1; i++) {
        for (j = 0; j < numTeams - i - 1; j++) {
            if (teams[j].points < teams[j + 1].points) {
                // Swapping the elements
                temp = teams[j];
                teams[j] = teams[j + 1];
                teams[j + 1] = temp;
            }
        }
    }
}
void sortPlayersByWickets(struct Player players[], int totalPlayers) {
    int i, j;
    struct Player temp;

    for (i = 0; i < totalPlayers - 1; i++) {
        for (j = 0; j < totalPlayers - i - 1; j++) {
            if (players[j].wickets < players[j + 1].wickets) {
                temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }
}
void sortPlayersByRuns(struct Player players[], int totalPlayers) {
    int i, j;
    struct Player temp;

    for (i = 0; i < totalPlayers - 1; i++) {
        for (j = 0; j < totalPlayers - i - 1; j++) {
            if (players[j].runs < players[j + 1].runs) {
                temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }
}
// Function to save data to a text file
void saveData(struct Team teams[], int numTeams) {
    FILE *file = fopen("cricket_data.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < numTeams; i++) {
        fprintf(file, "%s %s %d %d ", teams[i].name, teams[i].coach_name, teams[i].points, teams[i].numPlayers);
        fprintf(file, "%d %d", teams[i].matches_played, teams[i].matches_won);
        for (int j = 0; j < teams[i].numPlayers; j++) {
            fprintf(file, " %s %d %d", teams[i].players[j].name, teams[i].players[j].runs, teams[i].players[j].wickets);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// Function to load data from a text file
void loadData(struct Team teams[], int *numTeams) {
    FILE *file = fopen("cricket_data.txt", "r");
    if (file == NULL) {
        printf("No existing data found.\n");
        return;
    }

    while (fscanf(file, "%s %s %d %d %d %d", teams[*numTeams].name, teams[*numTeams].coach_name, &teams[*numTeams].points, &teams[*numTeams].numPlayers, &teams[*numTeams].matches_played, &teams[*numTeams].matches_won) == 6) {
        for (int i = 0; i < teams[*numTeams].numPlayers; i++) {
            fscanf(file, " %s %d %d", teams[*numTeams].players[i].name, &teams[*numTeams].players[i].runs, &teams[*numTeams].players[i].wickets);
        }
        (*numTeams)++;
    }

    fclose(file);
}

// Function to add a new team
void addTeam(struct Team teams[], int *numTeams) {
    if (*numTeams < MAX_TEAMS) {
        printf("Enter the name of the team: ");
        scanf("%s", teams[*numTeams].name);
        
        teams[*numTeams].points = 0;
        teams[*numTeams].numPlayers = 0;
        
        printf("Enter the name of the team coach: ");
        scanf("%s", teams[*numTeams].coach_name);
        
        (*numTeams)++;
        printf("Team added successfully!\n");
    } else {
        printf("Maximum number of teams reached!\n");
    }
}

// Function to add a new player to a team
void addPlayer(struct Team teams[], int numTeams) {
    char teamName[MAX_NAME_LENGTH];
    int i, j, choice;
    int runs=0, wickets=0;
    printf("Enter the name of the team: ");
    scanf("%s", teamName);

    for (i = 0; i < numTeams; i++) {
        if (strcmp(teams[i].name, teamName) == 0) {
            if (teams[i].numPlayers < MAX_PLAYERS_PER_TEAM) {
                printf("Enter the name of the player: ");
                scanf("%s", teams[i].players[teams[i].numPlayers].name);
                printf("1. Allrounder\n2. Batsman\n3. Bowler\n Select: ");
                scanf("%d", &choice);
                if(choice == 1){
                    printf("Runs: "); 
                    scanf("%d", &runs);
                    printf("Wickets: ");
                    scanf("%d", &wickets);
                }
                else if (choice == 2){
                    printf("Runs: "); 
                    scanf("%d", &runs);
                }
                else
                {
                    printf("Wickets: "); 
                    scanf("%d", &wickets);
                }
                teams[i].players[teams[i].numPlayers].runs = runs;
                teams[i].players[teams[i].numPlayers].wickets = wickets;

                teams[i].numPlayers++;
                saveData(teams, numTeams);
                printf("Player added successfully!\n");
            } else {
                printf("Maximum number of players reached for this team!\n");
            }
            return;
        }
    }
    printf("Team not found!\n");
}

// Function to update player information (runs and wickets)
void updatePlayerInfo(struct Team teams[], int numTeams) {
    char teamName[MAX_NAME_LENGTH];
    char playerName[MAX_NAME_LENGTH];
    int runs, wickets;
    int i, j, choice;

    printf("Enter the name of the team: ");
    scanf("%s", teamName);

    for (i = 0; i < numTeams; i++) {
        if (strcmp(teams[i].name, teamName) == 0) {
            printf("Enter the name of the player: ");
            scanf("%s", playerName);

            for (j = 0; j < teams[i].numPlayers; j++) {
                if (strcmp(teams[i].players[j].name, playerName) == 0) {
                    printf("1. Allrounder\n2. Batsman\n3. Bowler\n Select: ");
                    scanf("%d", &choice);
                    if(choice == 1){
                        printf("Runs: "); 
                        scanf("%d", &runs);
                        printf("Wickets: ");
                        scanf("%d", &wickets);
                    }
                    else if (choice == 2){
                        printf("Runs: "); 
                        scanf("%d", &runs);
                    }
                    else
                    {
                        printf("Wickets: "); 
                        scanf("%d", &wickets);
                    }
                    teams[i].players[j].runs += runs;
                    teams[i].players[j].wickets += wickets;

                    // Calculate the team's points differently
                    // int playerPoints = runs / 10 + wickets;
                    // teams[i].points += playerPoints;

                    printf("Player information updated successfully!\n");
                    return;
                }
            }

            printf("Player not found in %s!\n", teamName);
            return;
        }
    }

    printf("Team not found!\n");
}


// Function to view points table
void viewPointsTable(struct Team teams[], int numTeams) {
    int i;

    printf("\nPoints Table:\n");
    printf("+----------------------+------------------+\n"); 
    printf("| %-20s | %-16s |\n", "Team", "Points");
    printf("+----------------------+------------------+\n"); 

    for (i = 0; i < numTeams; i++) {
        printf("| %-20s | %-16d |\n", teams[i].name, teams[i].points);
    }
    printf("+----------------------+------------------+\n");

}

// Function to compare players based on runs (for sorting)
int compareRuns(const void *a, const void *b) {
    return ((struct Player *)b)->runs - ((struct Player *)a)->runs;
}

// Function to compare players based on wickets (for sorting)
int compareWickets(const void *a, const void *b) {
    return ((struct Player *)b)->wickets - ((struct Player *)a)->wickets;
}

// Function to view top wicket-takers
// void viewTopWicketTakers(struct Team teams[], int numTeams) {
//     int i, j;

//      printf("\nTop Wicket-Takers:\n");
//     printf("+----------------------+---------+----------------------+----------------------+\n");
//     printf("| %-20s | %-7s | %-20s | %-20s |\n", "Player", "Wickets", "Team", "Team Coach");
//     printf("+----------------------+---------+----------------------+----------------------+\n");

//     for (i = 0; i < numTeams; i++) {
//         for (j = 0; j < teams[i].numPlayers; j++) {
//             printf("| %-20s | %-7d | %-20s | %-20s |\n", teams[i].players[j].name, teams[i].players[j].wickets, teams[i].name, teams[i].coach_name);
//         }
//     }

//     printf("+----------------------+---------+----------------------+----------------------+\n");
// }

void viewTopWicketTakers(struct Team teams[], int numTeams) {
    int i, j, totalPlayers = 0;
    struct Player allPlayers[500]; // Adjust the size based on your needs

    // Flatten the list of players from all teams
    for (i = 0; i < numTeams; i++) {
        for (j = 0; j < teams[i].numPlayers; j++) {
            allPlayers[totalPlayers] = teams[i].players[j];
            allPlayers[totalPlayers].teamIndex_w = i;
            totalPlayers++;
        }
    }

    // Sort the players by wickets
    sortPlayersByWickets(allPlayers, totalPlayers);

    // Print the sorted list of players
    printf("\nTop Wicket-Takers:\n");
    printf("+----------------------+---------+----------------------+----------------------+\n");
    printf("| %-20s | %-7s | %-20s | %-20s |\n", "Player", "Wickets", "Team", "Team Coach");
    printf("+----------------------+---------+----------------------+----------------------+\n");

    for (i = 0; i < totalPlayers; i++) {
        struct Player p = allPlayers[i];
        printf("| %-20s | %-7d | %-20s | %-20s |\n", p.name, p.wickets, teams[p.teamIndex_w].name, teams[p.teamIndex_w].coach_name);
    }

    printf("+----------------------+---------+----------------------+----------------------+\n");
}
// Function to view top run-scorers
void viewTopRunScorers(struct Team teams[], int numTeams) {
    int i, j, totalPlayers = 0;
    struct Player allPlayers[500]; // Adjust the size based on your needs

    // Flatten the list of players from all teams
    for (i = 0; i < numTeams; i++) {
        for (j = 0; j < teams[i].numPlayers; j++) {
            allPlayers[totalPlayers] = teams[i].players[j];
            allPlayers[totalPlayers].teamIndex_r = i;
            totalPlayers++;
        }
    }

    // Sort the players by runs
    sortPlayersByRuns(allPlayers, totalPlayers);

    // Print the sorted list of players
    printf("\nTop Run-Scorers:\n");
    printf("+----------------------+---------+----------------------+----------------------+\n");
    printf("| %-20s | %-7s | %-20s | %-20s |\n", "Player", "Runs", "Team", "Team Coach");
    printf("+----------------------+---------+----------------------+----------------------+\n");

    for (i = 0; i < totalPlayers; i++) {
        struct Player p = allPlayers[i];
        printf("| %-20s | %-7d | %-20s | %-20s |\n", p.name, p.runs, teams[p.teamIndex_r].name, teams[p.teamIndex_r].coach_name);
    }

    printf("+----------------------+---------+----------------------+----------------------+\n");
}
// Function to display team-wise player statistics
void displayTeamWithHighestRunScorer(struct Team teams[], int numTeams) {
    int i, j, maxRuns = 0;
    char teamWithMaxRunScorer[MAX_NAME_LENGTH] = "";

    for (i = 0; i < numTeams; i++) {
        for (j = 0; j < teams[i].numPlayers; j++) {
            if (teams[i].players[j].runs > maxRuns) {
                maxRuns = teams[i].players[j].runs;
                strcpy(teamWithMaxRunScorer, teams[i].name);
            }
        }
    }

    if (maxRuns > 0) {
    printf("\nTeam with Highest Run-Scorer:\n");
    printf("+----------------------+------------+\n");  
    printf("| %-20s | %-10s |\n", "Team", "Runs");
    printf("+----------------------+------------+\n");  

    printf("| %-20s | %-10d |\n", teamWithMaxRunScorer, maxRuns);

    printf("+----------------------+------------+\n");  
} else {
    printf("No runs scored yet!\n");
}
}
void tournament(struct Team teams[], int numTeams) {
    // Check if there are enough teams to conduct a tournament
    if (numTeams < 2) {
        printf("You need at least 2 teams to conduct a tournament.\n");
        return;
    }

    printf("Tournament Teams:\n");
    for (int i = 0; i < numTeams; i++) {
        printf("%d. %s\n", i + 1, teams[i].name);
    }

    int team1, team2;
    printf("Enter the numbers of the two teams to play the match (e.g., 1 2): ");
    scanf("%d %d", &team1, &team2);

    // Check if the team numbers are valid
    if (team1 < 1 || team1 > numTeams || team2 < 1 || team2 > numTeams || team1 == team2) {
        printf("Invalid team numbers.\n");
        return;
    }

    // Decrement team numbers by 1 to match array indices
    team1--;
    team2--;

    printf("Match between %s and %s!\n", teams[team1].name, teams[team2].name);

    int winner = rand() % 2; // 0 or 1
    if (winner == 0) {
        printf("%s wins the match!\n", teams[team1].name);
        teams[team1].matches_played++;
        teams[team1].matches_won++;
        teams[team1].points += 2; // Award 2 points for a win
    } else {
        printf("%s wins the match!\n", teams[team2].name);
        teams[team2].matches_played++;
        teams[team2].matches_won++;
        teams[team2].points += 2; // Award 2 points for a win
    }
    // Update matches_played for both teams
    teams[team1].matches_played++;
    //teams[team2].matches_played;
    saveData(teams, numTeams);
}