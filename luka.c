#include <stdio.h>
#include <assert.h>
#include <string.h>



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

int read_stats(const char *in_file) {

  assert(in_file != NULL);

  FILE *file_rdr = 0;
  file_rdr = fopen(in_file, "r");

  if (file_rdr == NULL) {
    printf("Error opening file\n");
    return -1;
  }
  //printf("test\n");

  player_stat player;

  int data = 0;
  int record = 1;

  while (record != EOF) {
    record = fscanf(file_rdr, "%3[^;];%d:%*d;%lf;%lf;%lf;%d;%d;%d;%d;%d;%d\n", player.opponent, &player.min, &player.fg, &player.tp, &player.ft, &player.reb, &player.ast, &player.stls, &player.blks, &player.to, &player.pts);

    /*player.fg *= .01;
    player.tp *= .01;
    player.ft *= .01;*/

  printf("Opponent: %s\nMinutes: %d\nFG%%: %.2lf\nThree Point%%: %.2lf\nFT%%: %.2lf\nRebounds: %d\nAssists: %d\nSteals: %d\nBlocks: %d\nTurnovers: %d\nPoints: %d\n\n\n", player.opponent, player.min, player.fg, player.tp, player.ft, player.reb, player.ast, player.stls, player.blks, player.to, player.pts);

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
  return 0;
}

void prompt_user_and_read_stats() {
  char in_file[256];
  printf("Enter the name of the file to read: ");
  fgets(in_file, sizeof(in_file), stdin);

  in_file[strcspn(in_file, "\n")] = '\0';

  int result = read_stats(in_file);

  if (result = 0) {
    printf("Error occurred while processing file.\n");
  }
}

int main() {
  prompt_user_and_read_stats();
  return 0;
}
