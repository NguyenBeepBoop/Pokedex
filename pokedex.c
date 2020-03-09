// Assignment 2 19T1 COMP1511: Pokedex
// pokedex.c
//
// This program was written by NGUYEN HOANG (z5257125)
// on 24/04/19
//
// Version 1.0.0: Assignment released.
// Version 1.0.1: Minor clarifications about `struct pokenode`.
// Version 1.1.0: Moved destroy_pokedex function to correct location.
// Version 1.1.1: Renamed "pokemon_id" to "id" in change_current_pokemon.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Add any extra #includes your code needs here.
//
// But note you are not permitted to use functions from string.h
// so do not #include <string.h>

#include "pokedex.h"

// Add your own #defines here.


// Note you are not permitted to use arrays in struct pokedex,
// you must use a linked list.
//
// You are also not permitted to use arrays in any of the functions
// below.
//
// The only exception is that char arrays are permitted for
// search_pokemon and functions it may call, as well as the string
// returned by pokemon_name (from pokemon.h).
//
// You will need to add fields to struct pokedex.
// You may change or delete the head field.

struct pokedex {
    struct pokenode *head;
    struct pokenode *tail;
    int total_pokemon;
    int n_found;
};


// You don't have to use the provided struct pokenode, you are free to
// make your own struct instead.
// If you use the provided struct pokenode, you will need to add fields
// to it to store other information.

struct pokenode {
    struct pokenode *next;
    struct pokenode *prev;
    struct pokenode *evolution;
    Pokemon         pokemon;
    int found;
    int current;
    int evolve;
};

// Add any other structs you define here.


// Add prototypes for any extra functions you create here.
static struct pokenode *new_pokenode(Pokemon pokemon);
static void add_to_end(Pokedex pokedex, struct pokenode *node);
static void detail(Pokemon pokemon);
static void detail_not_found(Pokemon pokemon);
static void print(int found, Pokemon pokemon);
static int find_highest_id(Pokedex pokedex);
static int find_lowest_id(Pokedex pokedex);
static void print_evolution(Pokemon pokemon, int found);
static int strngln(char *string);
static void strngcpy(char *string_a, char *string_b);
static int to_lower(char ch);
static int substring_check(char *string, char *sub_str, int sub_ln, int str_ln);
// You need to implement the following 20 functions.
// In other words, replace the lines calling fprintf & exit with your code.
// You can find descriptions of what each function should do in pokedex.h


Pokedex new_pokedex(void) {
    Pokedex new_pokedex = malloc(sizeof (struct pokedex));
    assert(new_pokedex != NULL);
    // add your own code here
    new_pokedex->head = NULL;
    new_pokedex->tail = NULL;
    new_pokedex->total_pokemon = 0;
    new_pokedex->n_found = 0;
    return new_pokedex;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 1 Functions                          //
////////////////////////////////////////////////////////////////////////

void add_pokemon(Pokedex pokedex, Pokemon pokemon) {
    struct pokenode *n;
    n = new_pokenode(pokemon);
    add_to_end(pokedex, n);
    pokedex->total_pokemon++;
}
// Function prints out the details (Id, Name, Height, Weight, and types)
// of the current pokemon
void detail_pokemon(Pokedex pokedex) {
    struct pokenode *n = pokedex->head;
    if (n == NULL) {
        return;
    }
    while (n != NULL) {
        if (n->current == 1) {
            break;
        } else {
            n = n->next;
        }
    }
    if (n->found == 1) {
        detail(n->pokemon);
    } else {
        detail_not_found(n->pokemon);
    }
}

Pokemon get_current_pokemon(Pokedex pokedex) {
    struct pokenode *n = pokedex->head;
    if (n == NULL) {
        fprintf(stderr, "There's no current Pokemon\n");
        return 0;
    }
    while (n->next != NULL) {
        if (n->current == 1) {
            return n->pokemon;
        }
        n = n->next;
    }
    return n->pokemon;
}

void find_current_pokemon(Pokedex pokedex) {
    struct pokenode *n = pokedex->head;
    if (n == NULL) {
        return;
    }
    while (n != NULL) {
        if (n->current == 1 && n->found == 0) {
            n->found = 1;
            pokedex->n_found++;
        }
        n = n->next;
    }
}

void print_pokemon(Pokedex pokedex) {
    struct pokenode *n = pokedex->head;
    if (pokedex->head == NULL) {
        return;
    }
    while(n != NULL) {
        if (n->current == 1) {
            printf("--> ");
        } else {
            printf("    ");
        }
        print(n->found, n->pokemon);
        n = n->next;
    }
}

////////////////////////////////////////////////////////////////////////
//                         Stage 2 Functions                          //
////////////////////////////////////////////////////////////////////////

void next_pokemon(Pokedex pokedex) {
    struct pokenode *n = pokedex->head;
    if (pokedex->head == NULL) {
        return;
    }
    while (n->next != NULL) {
        if (n->current == 1) {
            n->current = 0;
            n->next->current = 1;
            return;
        }
        n = n->next;
    }
}

void prev_pokemon(Pokedex pokedex) {
    struct pokenode *n = pokedex->tail;
    if (pokedex->head == NULL) {
        return;
    }
    while (n->prev != NULL) {
        if (n->current == 1) {
            n->current = 0;
            n->prev->current = 1;
            return;
        }
        n = n->prev;
    }
}
// Function to change the current pokemon to pokemon with desired Id
void change_current_pokemon(Pokedex pokedex, int id) {
    struct pokenode *n = pokedex->head;
    int highest = find_highest_id(pokedex);
    int lowest = find_lowest_id(pokedex);
    if (n == NULL || id > highest || id < lowest) {
        return;
    }
// The following loop checks if the desired id is existing inside the pokedex
// if the next node of the current node is NULL, and the pokemon inside the
// current node is not the same as the desired id, the given id is Invalid
    while (n != NULL) {
        if (pokemon_id(n->pokemon) == id) {
            break;
        } else if (n->next == NULL) {
            return;
        }
        n = n->next;
    }
    n = pokedex->head;
// The following loop iterates through the linked list and changes the current
// pokemon to be not current
    while (n != NULL) {
        if (n->current == 1) {
            n->current = 0;
            break;
        }
        n = n->next;
    }
    n = pokedex->head;
// The following loop iterates through the linked list and finds the pokemon
// with the desired id and set the pokemon to be current
    while (n != NULL) {
        if (pokemon_id(n->pokemon) == id) {
            n->current = 1;
            return;
        }
        n = n->next;
    }
}
// The following function removes the current pokemon from the linked list
void remove_pokemon(Pokedex pokedex) {
    struct pokenode *n = pokedex->head;
    if (n == NULL) {
        return;
    }
// If there is only one pokemon in the linked list, destroy the current pokemon,
// free the node and set the node to NULL
    if (pokedex->head == pokedex->tail) {
        destroy_pokemon(pokedex->head->pokemon);
        pokedex->head = NULL;
        free(pokedex->head);
        pokedex->total_pokemon = 0;
        pokedex->n_found = 0;
        return;
    }
// If the current pokemon is the first pokemon, destroy the current pokemon
// and free the node that it is in
    if (n == pokedex->head && n->current == 1) {
        struct pokenode *temp = n->next;
        if (n->found == 1) {
            pokedex->n_found--;
        }
        destroy_pokemon(pokedex->head->pokemon);
        free(pokedex->head);
        n = temp;
        n->current = 1;
        pokedex->head = n;
        pokedex->total_pokemon--;
        return;
    }
    while (n->next != NULL) {
// If the current pokemon is the last pokemon in the linked list, destroy the
// Pokemon, free the node that it is in, and set the new tail pokemon to be the
// Pokemon one before it.
        if (n->next == pokedex->tail && n->next->current == 1) {
            if (n->next->found == 1) {
                pokedex->n_found--;
            }
            destroy_pokemon(n->next->pokemon);
            free(n->next);
            n->next = NULL;
            n->current = 1;
            pokedex->tail = n;
            pokedex->total_pokemon--;
            return;
// If the current pokemon is between the first and the last pokemon, destroy the
// pokemon, free the node and set the current pokemon to be the next pokemon.
        } else if (n->next->current == 1) {
            struct pokenode *temp = n->next;
            struct pokenode *temp2 = n;
            if (n->next->found == 1) {
                pokedex->n_found--;
            }
            destroy_pokemon(n->next->pokemon);
            temp = temp->next;
            temp->prev = temp2;
            temp->current = 1;
            *n->next = *temp;
            free(temp);
            pokedex->total_pokemon--;
            return;
        }
        n = n->next;
    }
}

void destroy_pokedex(Pokedex pokedex) {
    struct pokenode *n = pokedex->head;
    struct pokenode *next;
    while (n != NULL) {
        next = n->next;
        destroy_pokemon(n->pokemon);
        free(n);
        n = next;
    }
    free(pokedex);
}

////////////////////////////////////////////////////////////////////////
//                         Stage 3 Functions                          //
////////////////////////////////////////////////////////////////////////

void go_exploring(Pokedex pokedex, int seed, int factor, int how_many) {
    struct pokenode *n = pokedex->head;
    srand(seed);
    int n_found = 0; //integer to track number of found pokemon
    int rand_id;
// While the number of found pokemon is less than how_many find pokemon if they
// are in the pokedex.
    while (n_found < how_many) {
// The following loop iterates through the pokedex for each random Id generated.
// If the pokemon has not been found, set the pokemon to be found and increment
// the number of found pokemon so far.
        while (n != NULL) {
            rand_id = rand() % factor;
            if (pokemon_id(n->pokemon) == rand_id) {
                if (n->found == 0) {
                    pokedex->n_found++;
                }
                n_found++;
                n->found = 1;
            }
            n = n->next;
        }
        n = pokedex->head;
    }
}

int count_found_pokemon(Pokedex pokedex) {
    return pokedex->n_found;
}

int count_total_pokemon(Pokedex pokedex) {
    return pokedex->total_pokemon;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                          //
////////////////////////////////////////////////////////////////////////

void add_pokemon_evolution(Pokedex pokedex, int from_id, int to_id) {
    struct pokenode *n = pokedex->head;
    struct pokenode *evolution;
    int highest = find_highest_id(pokedex);
    int lowest = find_lowest_id(pokedex);
    int check_counter = 0;
// Checks if the evolution is invalid e.g. same pokemon or pokemon id outside
// the range of the pokedex.
    if (from_id == to_id || from_id < lowest || to_id > highest) {
        fprintf(stderr, "Invalid Pokemon Evolution!\n");
        exit(1);
    }
// Iterates through the pokedex to check for invalid evolution e.g. id of
// exsting pokemon to a removed pokemon or non-existing pokemon.
    while (n != NULL) {
        if (pokemon_id(n->pokemon) == from_id || pokemon_id(n->pokemon) == to_id) {
            check_counter++;
        } if (check_counter == 2) {
            break;
        } else if (n->next == NULL) {
            fprintf(stderr, "Invalid Pokemon Evolution!\n");
            exit(1);
        }
        n = n->next;
    }
    n = pokedex->head;
// Iterates through the pokedex to find the pokemon which the given pokemon will
// evolve to.
    while (n != NULL) {
        if (pokemon_id(n->pokemon) == to_id) {
            evolution = n;
            break;
        }
        n = n->next;
    }
    n = pokedex->head;
// Iterates through the pokedex to find the given from pokemon and sets it
// evolve to 1, and adds the to pokemon to the evolution.
    while (n != NULL) {
        if (pokemon_id(n->pokemon) == from_id) {
            n->evolution = evolution;
            n->evolve = 1;
            return;
        }
        n = n->next;
    }
}
// A function which prints out the chain of the evolutions of a pokemon. If the
// pokemon that will be evolved to is not found '????' will be printed instead
// of the pokemon's data.
void show_evolutions(Pokedex pokedex) {
    struct pokenode *n = pokedex->head;
    if (n == NULL) {
        return;
    }
    int id = 0;
    char *name;
    int type1;
    int type2;
// Iterate through the loop to find current pokemon
    while (n != NULL) {
        if (n->current == 1) {
            break;
        }
        n = n->next;
    }
    type1 = pokemon_first_type(n->pokemon);
    type2 = pokemon_second_type(n->pokemon);
    id = pokemon_id(n->pokemon);
    name = pokemon_name(n->pokemon);
// Print out the current pokemon and it's data if found.
    if (n->found == 1) {
        printf("#%03d %s [%s", id, name, pokemon_type_to_string(type1));
        if (pokemon_second_type(n->pokemon) != NONE_TYPE) {
            printf(" %s]", pokemon_type_to_string(type2));
        } else {
            printf("]");
        }
    } else {
        printf("#%03d ???? [????]", id);
    }
// Iterate through the pokemon's evolution and print out each of the pokemon's
// data.
    while (n->evolve == 1) {
        n = n->evolution;
        print_evolution(n->pokemon, n->found);
    }
    printf("\n");
}

int get_next_evolution(Pokedex pokedex) {
    struct pokenode *n = pokedex->head;
    int id = 0;
    if (n == NULL) {
        fprintf(stderr, "Pokedex: The pokedex is empty!");
        exit(1);
    }
    while (n != NULL) {
        if (n->current == 1) {
            break;
        }
        n = n->next;
    }
    if (n->evolve == 0) {
        return DOES_NOT_EVOLVE;
    }
    id = pokemon_id(n->evolution->pokemon);
    return id;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 5 Functions                          //
////////////////////////////////////////////////////////////////////////

Pokedex get_pokemon_of_type(Pokedex pokedex, pokemon_type type) {
    Pokedex type_pokedex = new_pokedex();
    struct pokenode *n = pokedex->head;
    int type1;
    int type2;
    while (n != NULL) {
        type1 = pokemon_first_type(n->pokemon);
        type2 = pokemon_second_type(n->pokemon);
        if ((type1 == type || type2 == type) && (n->found == 1)) {
            Pokemon new_pokemon = clone_pokemon(n->pokemon);
            struct pokenode *new_node = new_pokenode(new_pokemon);
            new_node->found = 1;
            type_pokedex->total_pokemon++;
            type_pokedex->n_found++;
            add_to_end(type_pokedex, new_node);
        }
        n = n->next;
    }
    return type_pokedex;
}

Pokedex get_found_pokemon(Pokedex pokedex) {
    Pokedex found_pokedex = new_pokedex();
    struct pokenode *n = pokedex->head;
    int highest_id = find_highest_id(pokedex);
    int id;
    int id_counter = 1;
    int lowest_id = find_lowest_id(pokedex);
    while (id_counter <= highest_id) {
        while (n != NULL) {
            id = pokemon_id(n->pokemon);
            if (id == lowest_id && n->found == 1) {
                Pokemon new_pokemon = clone_pokemon(n->pokemon);
                struct pokenode *new_node = new_pokenode(new_pokemon);
                new_node->found = 1;
                found_pokedex->total_pokemon++;
                found_pokedex->n_found++;
                add_to_end(found_pokedex, new_node);
                break;
            }
            n = n->next;
        }
        n = pokedex->head;
        lowest_id++;
        id_counter++;
    }
    return found_pokedex;
}

Pokedex search_pokemon(Pokedex pokedex, char *text) {
    Pokedex search_pokedex = new_pokedex();
    struct pokenode *n = pokedex->head;
    int strln_a, strln_b;
    int i = 0;
    while (n != NULL) {
        strln_a = strngln(pokemon_name(n->pokemon)) + 1;
        strln_b = strngln(text) + 1;
        char str_a[strln_a];
        char str_b[strln_b];
        strngcpy(pokemon_name(n->pokemon), str_a);
        strngcpy(text, str_b);

        while (str_a[i]) {
            str_a[i] = to_lower(str_a[i]);
            i++;
        }
        i = 0;
        while (str_b[i]) {
            str_b[i] = to_lower(str_b[i]);
            i++;
        }
        if ((substring_check(str_a, str_b, strln_b, strln_a) == 1) && (n->found == 1)) {
            Pokemon new_pokemon = clone_pokemon(n->pokemon);
            struct pokenode *new_node = new_pokenode(new_pokemon);
            new_node->found = 1;
            search_pokedex->total_pokemon++;
            search_pokedex->n_found++;
            add_to_end(search_pokedex, new_node);
        }
        i = 0;
        n = n->next;
    }
    return search_pokedex;
}

// Add definitions for your own functions below.
// Make them static to limit their scope to this file.

////////////////////////////////////////////////////////////////////////
//                 Helper functions (for pokedex.c)                   //
////////////////////////////////////////////////////////////////////////

// A helper function to allocate memory for a new pokenode and assign new
// pokemon data to the pokenode.
static struct pokenode *new_pokenode(Pokemon pokemon) {
    struct pokenode *node = malloc(sizeof(struct pokenode));
    if (node == NULL) {
        printf("Malloc failed out of memory.\n");
        exit(1);
    } else {
        node->pokemon = pokemon;
        node->next = NULL;
        node->found = 0;
        node->prev = NULL;
        node->current = 0;
        node->evolution = NULL;
        node->evolve = 0;
    }
    return node;
}
// A helper function to add the new pokenode to the pokedex. This function also
// sets the first pokemon to be the current pokemon and the head pokemon in the
// pokedex.
static void add_to_end(Pokedex pokedex, struct pokenode *node) {
    int id = pokemon_id(node->pokemon);
    if (node == NULL) {
        printf("Malloc failed out of memory.\n");
        exit(1);
    }
    if (pokedex->head == NULL) {
        pokedex->head = node;
        pokedex->tail = node;
        node->current = 1;
    } else {
        struct pokenode *n = pokedex->head;
// Iterate through the pokedex and check if pokemon has already been added.
        while (n != NULL) {
            if (pokemon_id(n->pokemon) == id) {
                printf("Pokedex: There's already a pokemon with pokemon_id %d!\n", id);
                exit(1);
            }
            n = n->next;
        }
        pokedex->tail->next = node;
        node->prev = pokedex->tail;
        pokedex->tail = node;
    }
}
// A helper function to print out the details of the pokemon if it has been
// found. This includes the Id, Name, Height, Weight, and Types of the pokemon.
// If the second type of the pokemon is a 'NONE_TYPE', the second type will not
// be printed.
static void detail(Pokemon pokemon) {
    int first = pokemon_first_type(pokemon);
    int second = pokemon_second_type(pokemon);
    printf("Id: %03d\n", pokemon_id(pokemon));
    printf("Name: %s\n", pokemon_name(pokemon));
    printf("Height: %.1lfm\n", pokemon_height(pokemon));
    printf("Weight: %.1lfkg\n", pokemon_weight(pokemon));
    if (second == NONE_TYPE) {
        printf("Type: %s\n", pokemon_type_to_string(first));
        return;
    }
    printf("Type: %s %s\n",
            pokemon_type_to_string(first), pokemon_type_to_string(second));
}
// A helper function to print out the details of the pokemon if it has not yet
// been found. The id of the pokemon will still be printed however, the name
// of the pokemon will be replaced by a number of asterisks(*), dependent on
// how long the name of the pokemon is. E.g. the pokemon Onix will have it's
// name printed as '****'. The rest of the pokemon data will be replaced by two
// dashes '--'.
static void detail_not_found(Pokemon pokemon) {
    int i = 0;
    printf("Id: %03d\n", pokemon_id(pokemon));
    printf("Name: ");
    while (pokemon_name(pokemon)[i] != '\0') {
        printf("*");
        i++;
    }
    printf("\n");
    printf("Height: --\nWeight: --\nType: --\n");
}

static void print(int found, Pokemon pokemon) {
    int i = 0;
    int id = pokemon_id(pokemon);
    char *name = pokemon_name(pokemon);
    printf("#%03d: ", id);
    if (found == 1) {
        printf("%s\n", name);
    } else {
        while (pokemon_name(pokemon)[i] != '\0') {
            printf("*");
            i++;
        }
        printf("\n");
    }
}
// A helper function to find the highest value of the current pokemon ids.
// The function iterates through the pokedex and finds the id of the pokemon.
// If the id of the pokemon is higher than the current highest id, the highest
// id is now the id of the pokemon, and the functions returns that value (id)
static int find_highest_id(Pokedex pokedex) {
    int id = 0;
    struct pokenode *n = pokedex->head;
    while (n != NULL) {
        if (pokemon_id(n->pokemon) > id) {
            id = pokemon_id(n->pokemon);
        }
        n = n->next;
    }
    return id;
}
// A helper function to find the lowest value of the current pokemon ids.
// The function iterates through the pokedex and finds the id of the pokemon.
// If the id of the pokemon is lower than the current lowest id, the lowest id
// is now the id of the pokemon, and the function returns that value (id)
static int find_lowest_id(Pokedex pokedex) {
    int id = find_highest_id(pokedex);
    struct pokenode *n = pokedex->head;
    while (n != NULL) {
        if (pokemon_id(n->pokemon) < id) {
            id = pokemon_id(n->pokemon);
        }
        n = n->next;
    }
    return id;
}
// A helper function to print out the evolution chain of a given pokemon.
// This helper function will print out only the evolutions of the pokemon, not
// the pokemon itself. The information of the evolution chain will be made of
// it's pokemon Id, Name and both types. If the pokemon's second type is
// considered to be a 'NONE_TYPE', the second type will not be printed.
// If any pokemon on the evolution chain has not yet been found it will have
// question marks printed instead of its name and type.
static void print_evolution(Pokemon pokemon, int found) {
    int id = pokemon_id(pokemon);
    char *name = pokemon_name(pokemon);
    int type1 = pokemon_first_type(pokemon);
    int type2 = pokemon_second_type(pokemon);
    printf(" --> ");
    if (found == 1) {
        printf("#%03d %s [%s", id, name, pokemon_type_to_string(type1));
        if (pokemon_second_type(pokemon) != NONE_TYPE) {
            printf(" %s]", pokemon_type_to_string(type2));
        } else {
            printf("]");
        }
    } else {
        printf("#%03d ???? [????]", id);
    }
}
// A helper function to find the string length of the given string.
static int strngln(char *string) {
    int i = 0;
    while (string[i] != '\0') {
        i++;
    }
    return i;
}
// A helper function to copy one string to another string.
static void strngcpy(char *string_a, char *string_b) {
    int i = 0;
    for(i = 0; string_a[i] != '\0'; ++i) {
        string_b[i] = string_a[i];
    }
}
// A helper function which changes the case of the given character to lower case.
static int to_lower(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        ch = ch + 32;
    }
    return ch;
}
// A helper function which returns 1 if the given substring is present in
// another string. It does this by iterating through the string and having a
// string length counter. The function first tests if the characters within
// both strings are the same. It then goes to check if the string length of the
// sub string in the string is equal to the given substring. As we have already
// test if the characters are different, both substrings must be equal and the
// helper function returns 1.
static int substring_check(char *string, char *sub_str, int sub_ln, int strln) {
    int i = 0;
    int z = 0; //z is second counter if first character matches
    int x = 0;
    int string_ln = 0;
    while (string[i]) {
        if (string[i] == sub_str[z]) {
            z = i;
            x = 0;
            while (string[z] && sub_str[x]) {
                string_ln++;
                if (string[z] != sub_str[x]) {
                    break;
                }
                if (string_ln == sub_ln) {
                    return 1;
                }
                z++;
                x++;
            }
        }
        z = 0;
        i++;
    }
    return 0;
}
