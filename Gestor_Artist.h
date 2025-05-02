#ifndef GESTOR_ARTIST_H
#define GESTOR_ARTIST_H

#include "artist.h"

typedef struct Gestor_Artist *Gestor_Artist;

Gestor_Artist create_gestor_artist();
void insert_artist_gestor(Gestor_Artist gestor, char **artist_fields);
char *get_artist_name_by_id(Gestor_Artist gestor, int artist_id);
char *get_artist_type_by_id(Gestor_Artist gestor, int artist_id);
char *get_artist_country_by_id(Gestor_Artist gestor, int artist_id);
int get_artist_discography_duration_by_id(Gestor_Artist gestor, int artist_id);
double get_artist_rate_per_stream_by_id(Gestor_Artist gestor, int artist_id);
GArray* get_artist_weeks_by_id(Gestor_Artist gestor, int artist_id);

void update_artist_albums(Gestor_Artist gestor, int artist_id);
void update_artist_discography_duration(Gestor_Artist gestor, int artist_id, int duration);
void add_revenue(Gestor_Artist gestor, int artist_id, double revenue);
void destroy_gestor_artist(Gestor_Artist gestor);

////////////////////////////////////////////Auxiliary//////////////////////////////////////////////

int get_num_members(Gestor_Artist gestor,int artist_id);
int get_members_id(Gestor_Artist gestor,int artist_id,int index);
bool is_artist_type(Gestor_Artist gestor,int artist_id,char *type);
bool is_artist_group(Gestor_Artist gestor, int artist_id);
void update_artist_revenue(Gestor_Artist gestor_artist, int artist_id,  double rate_per_stream);

/////////////////////////////////////////////Queries///////////////////////////////////////////////
void get_query1_Artist(const char *id, Gestor_Artist gestor, char *result, char separator, int interativo);
void get_query2(int N, char *country, Gestor_Artist gestor, char *result,char separator, int interativo);

/////////////////////////////////////////////Query 4///////////////////////////////////////////////
void add_to_top10(GArray *top10, Artist artist, int week);
int compare_artists_by_duration(gconstpointer a, gconstpointer b, gpointer user_data);
void query_4(Gestor_Artist gestor, char *begin_date, char *end_date,  char separator,char *result, int interativo);


////////////////////////////////////////////////////////////////////////////////////////////
bool artist_exists(const char *artist_ids, Gestor_Artist gestor);

#endif // GESTOR_ARTIST_H
