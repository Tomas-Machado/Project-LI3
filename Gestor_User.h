#ifndef GESTOR_USER_H
#define GESTOR_USER_H

#include "users.h"

typedef struct Gestor_User *Gestor_User;

void auxiliar_genre_count(Gestor_User gestor_user, int age, int genre_index);
Gestor_User create_gestor_user();
void insert_user_gestor(Gestor_User gestor, char **user_fields,GArray *music_ids);
void destroy_gestor_user(Gestor_User gestor);

///////////////////////////////////////////////GETTERS///////////////////////////////////////////
int get_user_age_by_id(Gestor_User gestor, int user_id);
char *get_user_email_by_id (Gestor_User gestor,int user_id);
char *get_user_first_name_by_id (Gestor_User gestor,int user_id);
char *get_user_last_name_by_id (Gestor_User gestor,int user_id);
char *get_user_country_by_id (Gestor_User gestor,int user_id);
GArray *get_user_like_musics_id_by_id(Gestor_User gestor, int user_id);


////////////////////////////////////////AUXILIARY///////////////////////////////////////////////
int *get_genre_count_by_index_and_age1(Gestor_User user, int age, int genre_index);
GArray *get_genre_counts_by_age1(Gestor_User user, int age);
void update_genre_count(Gestor_User gestor, int genre_index, char genre_name, int music_id, int age);


////////////////////////////////////QUERY1///////////////////////////////////////////
void get_query1_User(const char *user_id, Gestor_User gestor, char *result, char separator, int interativo);
/////////////////////////////////////query3/////////////////////////////////////
int compare_genre_count(const void *a, const void *b);
void get_query3(int age1, int age2, Gestor_User gestor_user, char *result,char separator, int interativo);



#endif //GESTOR_USER_H
