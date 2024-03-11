#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>



typedef struct stats {
  char opponent[3];
  int min;
  int pts;
  int reb;
  int ast;
  int stls;
  int blks;
  int to;
  double fg; //field goal percentage
  double tp; //three point percentage
  double ft; //free throw percentage
} player_stat;

int read_stats(const char *in_file, const char *opponent_input) {

  assert(in_file != NULL);

  FILE *file_rdr = 0;
  file_rdr = fopen(in_file, "r");

  if (file_rdr == NULL) {
    printf("Error opening file\n");
    return -1;
  }
  //printf("test\n");

  player_stat player;

  int data = 1;
  int record = 1;
  int found = 0;

  while (record != EOF) {
    record = fscanf(file_rdr, "%3[^;];%d:%*d;%lf;%lf;%lf;%d;%d;%d;%d;%d;%d\n", player.opponent, &player.min, &player.fg, &player.tp, &player.ft, &player.reb, &player.ast, &player.stls, &player.blks, &player.to, &player.pts);

    player.fg /= 10;
    if (player.ft == 1.000) {
      player.ft *= 100.0;
    } else {
      player.ft /= 10;
    }
    player.tp /= 10;

  if (strcmp(player.opponent, opponent_input) == 0) { 
    printf("\nGame Number: %d\nOpponent: %s\nMinutes: %d\nFG%%: %.2lf%%\nThree Point%%: %.2lf%%\nFT%%: %.2lf%%\nRebounds: %d\nAssists: %d\nSteals: %d\nBlocks: %d\nTurnovers: %d\nPoints: %d\n\n", data, player.opponent, player.min, player.fg, player.tp, player.ft, player.reb, player.ast, player.stls, player.blks, player.to, player.pts);
    found = 1;
  }

  //printf("record: %d\n", record);
  //printf("data: %d\n", data);

  if (record != 11) {
    fclose(file_rdr);
    file_rdr = NULL;
    printf("Not enough data!\n");
    return -1;
  }

  if ((data == 0) && (record == EOF)) {
    fclose(file_rdr);
    file_rdr = NULL;
    printf("No data!\n");
    return -1;
  }
  data++;
}

  fclose(file_rdr);
  file_rdr = NULL;

  if (!found) {
    printf("No stats found for this game!\n");
    return -1;
  }
  return 0;
}

void prompt_user_and_read_stats() {

  char in_file[256];
  char opponent_input[4];
  printf("Enter the name of the file to read: ");
  fgets(in_file, sizeof(in_file), stdin);

  in_file[strcspn(in_file, "\n")] = '\0';

  printf("Enter the opponent of the game that you would like to see stats for: ");
  fgets(opponent_input, sizeof(opponent_input), stdin);

  opponent_input[strcspn(opponent_input, "\n")] = '\0';

  for (int i = 0; i < strlen(opponent_input); i++) {
    opponent_input[i] = toupper(opponent_input[i]);
  }

  int result = read_stats(in_file, opponent_input);

  if (result = 0) {
    printf("Stats for the game againstt %s were not found!\n",  opponent_input);
  }
}

int main() {
  prompt_user_and_read_stats();
  return 0;
}
