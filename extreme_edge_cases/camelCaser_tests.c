/**
 * extreme_edge_cases
 * CS 341 - Fall 2023
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "camelCaser.h"
#include "camelCaser_tests.h"

size_t get_size(char **split) {
  if (split == NULL)
    return 0;

  size_t size = 0;
  char **walk = split;
  while (*walk) {
    size++;
    walk++;
  }
  return size;
}

int test_split_str() {
  const char *input_str =
      "The Heisenbug is an incredible creature. Facenovel servers get their "
      "power from its indeterminism. Code smell can be ignored with INCREDIBLE "
      "use of air freshener. God objects are the new religion.";

  char *expected_split[] = {
      "The Heisenbug is an incredible creature",
      " Facenovel servers get their power from its indeterminism",
      " Code smell can be ignored with INCREDIBLE use of air freshener",
      " God objects are the new religion", NULL};

  char **obtained_split = split_str(input_str);

  size_t obtained_split_len = get_size(obtained_split);
  size_t expected_split_len = get_size(expected_split);

  if (obtained_split_len != expected_split_len)
    return 0;

  char **walk = expected_split;
  while (*walk) {
    if (!strcmp(*walk, *obtained_split)) { // equal
      walk++;
      obtained_split++;
    } else
      return 0;
  }

  return *obtained_split == NULL;
}

int exit_run_test(char **result, int exit_code) {
  destroy(result);
  return exit_code;
}

int run_test(char **(*camelCaser)(const char *), void (*destroy)(char **),
             char *input, char **expected_output) {
  char **obtained_output = camel_caser(input);

  size_t expected_output_len = get_size(expected_output);
  size_t obtained_output_len = get_size(obtained_output);

  if (expected_output_len != obtained_output_len) {
    return exit_run_test(obtained_output, 0);
  }

  char **walk_expected = expected_output;
  char **walk_obtained = expected_output;

  while (*walk_expected && *walk_obtained) {
    if (strcmp(*walk_expected, *walk_obtained) != 0)
      return exit_run_test(obtained_output, 0);
    walk_expected++;
    walk_obtained++;
  }

  return exit_run_test(obtained_output, 1);
}

int test_camelCaser(char **(*camelCaser)(const char *),
                    void (*destroy)(char **)) {
  // TODO: Implement me!
  //
  char *in =
      "The Heisenbug is an incredible creature. Facenovel servers get their "
      "power from its indeterminism. Code smell can be ignored with INCREDIBLE "
      "use of air freshener. God objects are the new religion.";
  char *out[] = {"theHeisenbugIsAnIncredibleCreature",
                 "facenovelServersGetTheirPowerFromItsIndeterminism",
                 "codeSmellCanBeIgnoredWithIncredibleUseOfAirFreshener",
                 "godObjectsAreTheNewReligion", NULL};
  if (run_test(camelCaser, destroy, in, out) == 0)
    return 0;

  if (run_test(camelCaser, destroy, "123Abc! 345Efg mOM, 7.,!", (char *[]){"123Abc! 345Efg mOM, 7.,!"}) == 0)
    return 0;

  // return test_split_str(); -> to test if I split correctly
  return 1;
}
