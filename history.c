#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "Utils.h"

#include "history.h"

typedef struct History
{
  int id;
  int user_id;
  int music_id;
  char *timestamp;
  char *duration;
  char *platform;
} *History;

History Create_History(char **fields)
{
  History history = malloc(sizeof(struct History));
  history->id = atoi(fields[0] + 1);
  history->user_id = atoi(fields[1] + 1);
  history->music_id = atoi(fields[2] + 1);
  history->timestamp = g_strndup(fields[3],10);
  history->duration = g_strdup(fields[4]);
  history->platform = g_strdup(fields[5]);

  return history;
}

int get_history_id(History history)
{
  return history->id;
}

int get_history_user_id(History history)
{
  return history->user_id;
}

int get_history_music_id(History history)
{
  return history->music_id;
}

char *get_history_timestamp(History history)
{
  return g_strdup(history->timestamp);
}

char *get_history_duration(History history)
{
  return g_strdup(history->duration);
}

char *get_history_platform(History history)
{
  return g_strdup(history->platform);
}

void destroy_history(gpointer data)
{
  History history = (History)data;

  g_free(history->timestamp);
  g_free(history->duration);
  g_free(history->platform);

  free(history);
}