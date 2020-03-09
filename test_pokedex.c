// Assignment 2 19T1 COMP1511: Pokedex
// test_pokedex.c
//
// This file allows you to automatically test the functions you
// implement in pokedex.c.
//
// This program was written by YOUR-NAME-HERE (z5555555)
// on INSERT-DATE-HERE
//
// Version 1.0.0: Assignment released.
// Version 1.0.1: Added pointer check for the provided tests.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "pokedex.h"

// Add your own #defines here.


// Sample data on Bulbasaur, the Pokemon with pokemon_id 1.
#define BULBASAUR_ID 1
#define BULBASAUR_NAME "Bulbasaur"
#define BULBASAUR_HEIGHT 0.7
#define BULBASAUR_WEIGHT 6.9
#define BULBASAUR_FIRST_TYPE GRASS_TYPE
#define BULBASAUR_SECOND_TYPE POISON_TYPE

// Sample data on Ivysaur, the Pokemon with pokemon_id 2.
#define IVYSAUR_ID 2
#define IVYSAUR_NAME "Ivysaur"
#define IVYSAUR_HEIGHT 1.0
#define IVYSAUR_WEIGHT 13.0
#define IVYSAUR_FIRST_TYPE GRASS_TYPE
#define IVYSAUR_SECOND_TYPE POISON_TYPE


// Add your own prototypes here.
// Sample data on Mew, the pokemon with pokemon_id 151.
#define MEW_ID 151
#define MEW_NAME "Mew"
#define MEW_HEIGHT 0.4
#define MEW_WEIGHT 4.0
#define MEW_FIRST_TYPE PSYCHIC_TYPE
#define MEW_SECOND_TYPE NONE_TYPE

// Sample data on Arcanine, the pokemon with pokemon_id 59.
#define ARCANINE_ID 59
#define ARCANINE_NAME "Arcanine"
#define ARCANINE_HEIGHT 1.9
#define ARCANINE_WEIGHT 155.0
#define ARCANINE_FIRST_TYPE FIRE_TYPE
#define ARCANINE_SECOND_TYPE NONE_TYPE

//Sample data on Onix, the pokemon with pokemon_id 95
#define ONIX_ID 95
#define ONIX_NAME "Onix"
#define ONIX_HEIGHT 8.8
#define ONIX_WEIGHT 210
#define ONIX_FIRST_TYPE GROUND_TYPE
#define ONIX_SECOND_TYPE ROCK_TYPE

//Sample data on Charmander, the pokemon with pokemon_id 3
#define CHARMANDER_ID 4
#define CHARMANDER_NAME "Charmander"
#define CHARMANDER_HEIGHT 0.6
#define CHARMANDER_WEIGHT 8.5
#define CHARMANDER_FIRST_TYPE FIRE_TYPE
#define CHARMANDER_SECOND_TYPE NONE_TYPE
// Tests for Pokedex functions from pokedex.c.
static void test_new_pokedex(void);
static void test_add_pokemon(void);
static void test_get_found_pokemon(void);
static void test_next_pokemon(void);
static void test_get_type_pokemon(void);
static void test_remove_pokemon(void);
static void test_prev_pokemon(void);
static void test_change_current_pokemon(void);
static void test_go_exploring(void);

// Helper functions for creating/comparing Pokemon.
static Pokemon create_bulbasaur(void);
static Pokemon create_ivysaur(void);
static Pokemon create_mew(void);
static Pokemon create_arcanine(void);
static Pokemon create_onix(void);
static Pokemon create_charmander(void);
static int is_same_pokemon(Pokemon first, Pokemon second);
static int is_copied_pokemon(Pokemon first, Pokemon second);



int main(int argc, char *argv[]) {
    printf("Welcome to the COMP1511 Pokedex Tests!\n");

    printf("\n==================== Pokedex Tests ====================\n");

    test_new_pokedex();
    test_add_pokemon();
    test_next_pokemon();
    test_get_found_pokemon();
    test_get_type_pokemon();
    test_remove_pokemon();
    test_prev_pokemon();
    test_change_current_pokemon();
    test_go_exploring();
    printf("\nAll Pokedex tests passed, you are Awesome!\n");
}


////////////////////////////////////////////////////////////////////////
//                     Pokedex Test Functions                         //
////////////////////////////////////////////////////////////////////////

// `test_new_pokedex` checks whether the new_pokedex and destroy_pokedex
// functions work correctly, to the extent that it can.
//
// It does this by creating a new Pokedex, checking that it's not NULL,
// then calling destroy_pokedex.
//
// Note that it isn't possible to check whether destroy_pokedex has
// successfully destroyed/freed the Pokedex, so the best we can do is to
// call the function and make sure that it doesn't crash..
static void test_new_pokedex(void) {
    printf("\n>> Testing new_pokedex\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("       --> Checking that the returned Pokedex is not NULL\n");
    assert(pokedex != NULL);

    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed new_pokedex tests!\n");
}

// `test_add_pokemon` checks whether the add_pokemon function works
// correctly.
//
// It does this by creating the Pokemon Bulbasaur (using the helper
// functions in this file and the provided code in pokemon.c), and
// calling add_pokemon to add it to the Pokedex.
//
// Some of the ways that you could extend these test would include:
//   - adding additional Pokemon other than just Bulbasaur,
//   - checking whether the currently selected Pokemon is correctly set,
//   - checking that functions such as `count_total_pokemon` return the
//     correct result after more Pokemon are added,
//   - ... and more!
static void test_add_pokemon(void) {
    printf("\n>> Testing add_pokemon\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Creating Bulbasaur\n");
    Pokemon bulbasaur = create_bulbasaur();

    printf("    ... Adding Bulbasaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);

    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed add_pokemon tests!\n");
}

// `test_next_pokemon` checks whether the next_pokemon function works
// correctly.
//
// It does this by creating two Pokemon: Bulbasaur and Ivysaur (using
// the helper functions in this file and the provided code in pokemon.c).
//
// It then adds these to the Pokedex, then checks that calling the
// next_pokemon function changes the currently selected Pokemon from
// Bulbasaur to Ivysaur.
//
// Some of the ways that you could extend these tests would include:
//   - adding even more Pokemon to the Pokedex,
//   - calling the next_pokemon function when there is no "next" Pokemon,
//   - calling the next_pokemon function when there are no Pokemon in
//     the Pokedex,
//   - ... and more!
static void test_next_pokemon(void) {
    printf("\n>> Testing next_pokemon\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Creating Bulbasaur and Ivysaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();

    printf("    ... Adding Bulbasaur and Ivysaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);

    printf("       --> Checking that the current Pokemon is Bulbasaur\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), bulbasaur));

    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);

    printf("       --> Checking that the current Pokemon is Ivysaur\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), ivysaur));

    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed next_pokemon tests!\n");
}

// `test_get_found_pokemon` checks whether the get_found_pokemon
// function works correctly.
//
// It does this by creating two Pokemon: Bulbasaur and Ivysaur (using
// the helper functions in this file and the provided code in pokemon.c).
//
// It then adds these to the Pokedex, sets Bulbasaur to be found, and
// then calls the get_found_pokemon function to get all of the Pokemon
// which have been found (which should be just the one, Bulbasaur).
//
// Some of the ways that you could extend these tests would include:
//   - calling the get_found_pokemon function on an empty Pokedex,
//   - calling the get_found_pokemon function on a Pokedex where none of
//     the Pokemon have been found,
//   - checking that the Pokemon in the new Pokedex are in ascending
//     order of pokemon_id (regardless of the order that they appeared
//     in the original Pokedex),
//   - checking that the currently selected Pokemon in the returned
//     Pokedex has been set correctly,
//   - checking that the original Pokedex has not been modified,
//   - ... and more!
static void test_get_found_pokemon(void) {
    printf("\n>> Testing get_found_pokemon\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Creating Bulbasaur and Ivysaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();

    printf("    ... Adding Bulbasaur and Ivysaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);

    printf("       --> Checking that the current Pokemon is Bulbasaur\n");
    assert(get_current_pokemon(pokedex) == bulbasaur);

    printf("    ... Setting Bulbasaur to be found\n");
    find_current_pokemon(pokedex);

    printf("    ... Getting all found Pokemon\n");
    Pokedex found_pokedex = get_found_pokemon(pokedex);

    printf("       --> Checking the correct Pokemon were copied and returned\n");
    assert(count_total_pokemon(found_pokedex) == 1);
    assert(count_found_pokemon(found_pokedex) == 1);
    assert(is_copied_pokemon(get_current_pokemon(found_pokedex), bulbasaur));

    printf("    ... Destroying both Pokedexes\n");
    destroy_pokedex(pokedex);
    destroy_pokedex(found_pokedex);

    printf(">> Passed get_found_pokemon tests!\n");
}


// Write your own Pokedex tests here!

static void test_get_type_pokemon(void) {
    printf("\n              ^_^ Testing get_type_pokemon ^_^\n");

    printf("    --- Creating a new Pokedex ---\n");
    Pokedex pokedex = new_pokedex();

    printf("    --- Creating Mew, Charmander, Onix and Arcanine ---\n");
    Pokemon mew = create_mew();
    Pokemon charmander = create_charmander();
    Pokemon onix = create_onix();
    Pokemon arcanine = create_arcanine();
    printf("    --- Adding Mew, Charmander, Onix and Arcanine to the Pokedex ---\n");
    add_pokemon(pokedex, mew);
    add_pokemon(pokedex, charmander);
    add_pokemon(pokedex, onix);
    add_pokemon(pokedex, arcanine);

    printf("       !!!Checking that the current Pokemon is Mew!!!\n");
    assert(get_current_pokemon(pokedex) == mew);

    printf("    --- go exploring to find 20 pokemon ---\n");
    go_exploring(pokedex, 1, 151, 20);

    printf("    --- Getting all pokemon of 'FIRE_TYPE' Pokemon ---\n");
    Pokedex type_pokedex = get_pokemon_of_type(pokedex ,FIRE_TYPE);

    printf("       !!!Checking the correct Pokemon were copied and returned!!!\n");
    assert(count_total_pokemon(type_pokedex) == 2);
    assert(count_found_pokemon(type_pokedex) == 2);
    assert(is_copied_pokemon(get_current_pokemon(type_pokedex), charmander));

    printf("    --- Destroying both Pokedexes ---\n");
    destroy_pokedex(pokedex);
    destroy_pokedex(type_pokedex);

    printf("        -------PASS-------\n");
}

static void test_remove_pokemon(void) {
    printf("\n!             ^_^ Testing remove_pokemon ^_^\n");

    printf("    --- Creating a new Pokedex ---\n");
    Pokedex pokedex = new_pokedex();

    printf("    --- Creating Mew, Charmander, Onix and Arcanine ---\n");
    Pokemon mew = create_mew();
    Pokemon charmander = create_charmander();
    Pokemon onix = create_onix();
    Pokemon arcanine = create_arcanine();
    printf("    --- Adding Mew, Charmander, Onix and Arcanine to the Pokedex ---\n");
    add_pokemon(pokedex, mew);
    add_pokemon(pokedex, charmander);
    add_pokemon(pokedex, onix);
    add_pokemon(pokedex, arcanine);

    printf("       !!!Checking that the current Pokemon is Mew!!!\n");
    assert(get_current_pokemon(pokedex) == mew);

    printf("    --- Go exploring to find 20 pokemon ---\n");
    go_exploring(pokedex, 1, 152, 20);

    printf("    --- Removing current pokemon ---\n");
    remove_pokemon(pokedex);

    printf("       !!!Checking that current pokemon is Charmander!!!\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), charmander));

    printf("    --- Destroying both Pokedexes ---\n");
    destroy_pokedex(pokedex);

    printf("        -------PASS-------\n");
}

static void test_prev_pokemon(void) {
    printf("\n              ^_^ Testing prev_pokemon ^_^\n");

    printf("    --- Creating a new Pokedex ---\n");
    Pokedex pokedex = new_pokedex();

    printf("    --- Creating Mew, Charmander, Onix and Arcanine ---\n");
    Pokemon mew = create_mew();
    Pokemon charmander = create_charmander();
    Pokemon onix = create_onix();
    Pokemon arcanine = create_arcanine();
    printf("    --- Adding Mew, Charmander, Onix and Arcanine to the Pokedex ---\n");
    add_pokemon(pokedex, mew);
    add_pokemon(pokedex, charmander);
    add_pokemon(pokedex, onix);
    add_pokemon(pokedex, arcanine);

    printf("       !!!Checking that the current Pokemon is Mew!!!\n");
    assert(get_current_pokemon(pokedex) == mew);

    printf("    --- Moving to the next pokemon ---\n");
    next_pokemon(pokedex);

    printf("       !!!Checking that current pokemon is Charmander!!!\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), charmander));

    printf("    --- Moving to the next pokemon ---\n");
    next_pokemon(pokedex);

    printf("       !!!Checking that current pokemon is Onix!!!\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), onix));

    printf("    --- Moving to the previous pokemon ---\n");
    prev_pokemon(pokedex);

    printf("       !!!Checking that current pokemon is Charmander!!!\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), charmander));

    printf("    --- Destroying the Pokedex ---\n");
    destroy_pokedex(pokedex);

    printf("        -------PASS-------\n");
}

static void test_change_current_pokemon(void) {
    printf("\n          ^_^ Testing change_current_pokemon_pokemon ^_^\n");

    printf("    --- Creating a new Pokedex ---\n");
    Pokedex pokedex = new_pokedex();

    printf("    --- Creating Mew, Charmander, Onix and Arcanine ---\n");
    Pokemon mew = create_mew();
    Pokemon charmander = create_charmander();
    Pokemon onix = create_onix();
    Pokemon arcanine = create_arcanine();
    printf("    --- Adding Mew, Charmander, Onix and Arcanine to the Pokedex ---\n");
    add_pokemon(pokedex, mew);
    add_pokemon(pokedex, charmander);
    add_pokemon(pokedex, onix);
    add_pokemon(pokedex, arcanine);

    printf("       !!!Checking that the current Pokemon is Mew!!!\n");
    assert(get_current_pokemon(pokedex) == mew);

    printf("    --- Moving to the pokemon with pokemon Id 4 ---\n");
    change_current_pokemon(pokedex, 4);

    printf("       !!!Checking that current pokemon is Charmander!!!\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), charmander));

    printf("    --- Moving to the pokemon with pokemon Id 59 ---\n");
    change_current_pokemon(pokedex, 59);

    printf("       !!!Checking that current pokemon is Arcanine!!!\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), arcanine));

    printf("    --- Moving to the first pokemon using prev_pokemon ---\n");
    prev_pokemon(pokedex);
    prev_pokemon(pokedex);
    prev_pokemon(pokedex);

    printf("       !!!Checking that current pokemon is Mew!!!\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), mew));

    printf("    --- Destroying the Pokedex ---\n");
    destroy_pokedex(pokedex);

    printf("        -------PASS-------\n");
}

static void test_go_exploring(void) {
    printf("\n!             ^_^ Testing go_exploring ^_^\n");

    printf("    --- Creating a new Pokedex ---\n");
    Pokedex pokedex = new_pokedex();

    printf("    --- Creating Mew, Charmander, Onix and Arcanine ---\n");
    Pokemon mew = create_mew();
    Pokemon charmander = create_charmander();
    Pokemon onix = create_onix();
    Pokemon arcanine = create_arcanine();
    printf("    --- Adding Mew, Charmander, Onix and Arcanine to the Pokedex ---\n");
    add_pokemon(pokedex, mew);
    add_pokemon(pokedex, charmander);
    add_pokemon(pokedex, onix);
    add_pokemon(pokedex, arcanine);

    printf("       !!!Checking that the current Pokemon is Mew!!!\n");
    assert(get_current_pokemon(pokedex) == mew);

    printf("    --- Go exploring to find 1 pokemon ---\n");
    go_exploring(pokedex, 1, 152, 1);

    printf("    --- Checking that total pokemon found is 1 ---\n");
    assert(count_found_pokemon(pokedex) == 1);

    printf("    --- Destroying both Pokedexes ---\n");
    destroy_pokedex(pokedex);

    printf("        -------PASS-------\n");
}

////////////////////////////////////////////////////////////////////////
//                     Helper Functions                               //
////////////////////////////////////////////////////////////////////////

// Helper function to create Bulbasaur for testing purposes.
static Pokemon create_bulbasaur(void) {
    Pokemon pokemon = new_pokemon(
            BULBASAUR_ID, BULBASAUR_NAME,
            BULBASAUR_HEIGHT, BULBASAUR_WEIGHT,
            BULBASAUR_FIRST_TYPE,
            BULBASAUR_SECOND_TYPE
    );
    return pokemon;
}

// Helper function to create Ivysaur for testing purposes.
static Pokemon create_ivysaur(void) {
    Pokemon pokemon = new_pokemon(
            IVYSAUR_ID, IVYSAUR_NAME,
            IVYSAUR_HEIGHT, IVYSAUR_WEIGHT,
            IVYSAUR_FIRST_TYPE,
            IVYSAUR_SECOND_TYPE
    );
    return pokemon;
}
// Helper function to create Mew for testing purposes.
static Pokemon create_mew(void) {
    Pokemon pokemon = new_pokemon(
            MEW_ID, MEW_NAME,
            MEW_HEIGHT, MEW_WEIGHT,
            MEW_FIRST_TYPE,
            MEW_SECOND_TYPE
    );
    return pokemon;
}
// A helper function to create Arcanine for testing purposes.
static Pokemon create_arcanine(void) {
    Pokemon pokemon = new_pokemon(
            ARCANINE_ID, ARCANINE_NAME,
            ARCANINE_HEIGHT, ARCANINE_WEIGHT,
            ARCANINE_FIRST_TYPE,
            ARCANINE_SECOND_TYPE
    );
    return pokemon;
}
// A helper function to create Onix for testing purposes.
static Pokemon create_onix(void) {
    Pokemon pokemon = new_pokemon(
            ONIX_ID, ONIX_NAME,
            ONIX_HEIGHT, ONIX_WEIGHT,
            ONIX_FIRST_TYPE,
            ONIX_SECOND_TYPE
    );
    return pokemon;
}
// A helper function to create Charmander or testing purposes.
static Pokemon create_charmander(void) {
    Pokemon pokemon = new_pokemon(
            CHARMANDER_ID, CHARMANDER_NAME,
            CHARMANDER_HEIGHT, CHARMANDER_WEIGHT,
            CHARMANDER_FIRST_TYPE,
            CHARMANDER_SECOND_TYPE
    );
    return pokemon;
}
// Helper function to compare whether two Pokemon are the same.
// This checks that the two pointers contain the same address, i.e.
// they are both pointing to the same pokemon struct in memory.
//
// Pokemon ivysaur = new_pokemon(0, 'ivysaur', 1.0, 13.0, GRASS_TYPE, POISON_TYPE)
// Pokemon also_ivysaur = ivysaur
// is_same_pokemon(ivysaur, also_ivysaur) == TRUE
static int is_same_pokemon(Pokemon first, Pokemon second) {
    return first == second;
}

// Helper function to compare whether one Pokemon is a *copy* of
// another, based on whether their attributes match (e.g. pokemon_id,
// height, weight, etc).
//
// It also checks that the pointers do *not* match -- i.e. that the
// pointers aren't both pointing to the same pokemon struct in memory.
// If the pointers both contain the same address, then the second
// Pokemon is not a *copy* of the first Pokemon.
//
// This function doesn't (yet) check that the Pokemon's names match
// (but perhaps you could add that check yourself...).
static int is_copied_pokemon(Pokemon first, Pokemon second) {
    return (pokemon_id(first) == pokemon_id(second))
    &&  (first != second)
    &&  (pokemon_height(first) == pokemon_height(second))
    &&  (pokemon_weight(first) == pokemon_weight(second))
    &&  (pokemon_first_type(first) == pokemon_first_type(second))
    &&  (pokemon_second_type(first) == pokemon_second_type(second));
}

// Write your own helper functions here!
