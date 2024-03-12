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

  int games = 0;
  double sum_min = 0, sum_pts = 0, sum_reb = 0, sum_ast = 0, sum_stls = 0, sum_blks = 0, sum_to = 0, sum_fg = 0, sum_tp = 0, sum_ft = 0;


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
    printf("\n\nGame Number: %d\nOpponent: %s\nMinutes Played: %d\nPoints: %d\nRebounds: %d\nAssists: %d\nSteals: %d\nBlocks: %d\nTurnovers: %d\nFG%%: %.2lf%%\nThree Point%%: %.2lf%%\nFT%%: %.2lf%%\n\n", data, player.opponent, player.min, player.pts, player.reb, player.ast, player.stls, player.blks, player.to, player.fg, player.tp, player.ft);
    found = 1;

    sum_min += player.min;
    sum_pts += player.pts;
    sum_reb += player.reb;
    sum_ast += player.ast;
    sum_stls += player.stls;
    sum_blks += player.blks;
    sum_to += player.to;
    sum_fg += player.fg;
    sum_tp += player.tp;
    sum_ft += player.ft;

    games++;
  }

  //printf("record: %d\n", record);
  //printf("data: %d\n", data);

  /*if (record != 11) {
    fclose(file_rdr);
    file_rdr = NULL;
    printf("Not enough data!\n");
    return -1;
  }*/

  if ((data == 0) && (record == EOF)) {
    fclose(file_rdr);
    file_rdr = NULL;
    printf("No data!\n");
    return -1;
  }
  data++;
}

if (!found) {
  printf("Stats for the game against %s were not found!\nEither they haven't matched up this season, or there was an error in your spelling\n",  opponent_input);
  return -1;
} else {
  printf("Average Stats Against %s In %d Games This Season:\nMinutes: %.2lf\nPoints: %.2lf\nRebounds: %.2lf\nAssists: %.2lf\nSteals: %.2lf\nBlocks: %.2lf\nTurnovers: %.2lf\nFG%%: %.2lf\nThree Point%%: %.2lf\nFT%%: %.2lf\n\n",
           opponent_input, games, sum_min / games, sum_pts / games, sum_reb / games, sum_ast / games, sum_stls / games, sum_blks / games, sum_to / games, sum_fg / games, sum_tp / games, sum_ft / games);
}
  fclose(file_rdr);
  file_rdr = NULL;
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

  /*if (result != 0) {
    printf("Stats for the game against %s were not found!\n",  opponent_input);
  }*/
}

int main() {
  prompt_user_and_read_stats();
  return 0;
}
