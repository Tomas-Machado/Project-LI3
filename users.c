#include <glib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/users.h"
#include "stdbool.h"
#include "Utils.h"

typedef struct User {

    int username;
    char *email;
    char *first_name;
    char *last_name;
    char *birth_date;
    char *country ;
    //char *subscription_type;
    GArray *liked_musics_id;

}   *Users;


Users create_User(char **fields,GArray *liked_musics_id) {
    Users user = malloc(sizeof(struct User));


    user->username = atoi(fields[0] +1 );
    user->email = g_strdup(fields[1]);
    user->first_name = g_strdup(fields[2]);
    user->last_name = g_strdup(fields[3]);
    user->birth_date = g_strdup(fields[4]);
    user->country = g_strdup(fields[5]);
    //user->subscription_type = g_strdup(fields[6]);
    user->liked_musics_id = liked_musics_id;

    return user;
}

int get_user_username(Users user) {
    return user->username;
}

char *get_user_first_name(Users user) {
    return g_strdup(user->first_name);
}

char *get_user_last_name(Users user) {
    return g_strdup(user->last_name);
}

char *get_user_email(Users user) {
    return g_strdup(user->email);
}

char *get_user_birth_date(Users user) {
    return g_strdup(user->birth_date);
}
GArray *get_user_like_musics_id(Users user) {
    return g_array_ref(user->liked_musics_id);
}
int get_user_age(Users user) {
    return calculate_age(user->birth_date);
}

char *get_user_country(Users user) {
    return g_strdup(user->country);
}
/*
char *get_user_subscription_type(Users user) {
    return g_strdup(user->subscription_type);
}
*/


void destroy_user(gpointer data) {
    Users user = (Users)data;

    // Liberando cada campo alocado dinamicamente
    g_free(user->email);
    g_free(user->first_name);
    g_free(user->last_name);
    g_free(user->birth_date);
    g_free(user->country);
    //g_free(user->subscription_type);
    g_array_free(user->liked_musics_id, TRUE);

    // Liberando a própria struct
    g_free(user);
}


