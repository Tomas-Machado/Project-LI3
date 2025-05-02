#ifndef USERS_H_
#define USERS_H_
#include <glib.h>


void read_music(char *line, GHashTable *musics);
void read_artists(char *line, GHashTable *artists);
void read_users(char *line, GHashTable *users);

#endif