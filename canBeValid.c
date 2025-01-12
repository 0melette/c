#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

#define MAX_LEN 100000

bool canBeValid(const char *s, const char *locked) {
    int length = strlen(s);
    if (length % 2 == 1) {
        return false;
    }

    int openBrackets[MAX_LEN], unlocked[MAX_LEN];
    int openTop = -1, unlockTop = -1;

    for (int i = 0; i < length; i++) {
        if (locked[i] == '0') {
            unlocked[++unlockTop] = i;
        } else if (s[i] == '(') {
            openBrackets[++openTop] = i;
        } else if (s[i] == ')') {
            if (openTop >= 0) {
                openTop--;
            } else if (unlockTop >= 0) {
                unlockTop--;
            } else {
                return false;
            }
        }
    }

    while (openTop >= 0 && unlockTop >= 0 && openBrackets[openTop] < unlocked[unlockTop]) {
        openTop--;
        unlockTop--;
    }

    if (openTop >= 0) {
        return false;
    }

    return true;
}

int main() {
  struct TestCase {
    const char *description;
    const char *s;
    const char *locked;
    bool expected;
  };

struct TestCase testCases[] = {
    {"Odd length string, must return false", ")", "0", false},
    {"Valid parentheses with no locked characters", "()()", "0000", true},
    {"Unbalanced parentheses with locked characters", "))()))", "010100", true},
    {"Completely locked invalid string", "))(", "111", false},
    {"Empty string (edge case)", "", "", true},
    {"Only one unlocked character", "(", "0", false},
    {"Balanced locked string", "(())", "1111", true},
    {"Locked invalid string, cannot fix", ")(", "11", false},
};

  int numTestCases = sizeof(testCases) / sizeof(testCases[0]);
  int passed = 0;

  printf(CYAN "Running Test Cases:\n\n" RESET);
  for (int i = 0; i < numTestCases; i++) {
    struct TestCase test = testCases[i];
    bool actual = canBeValid(test.s, test.locked);

    printf(CYAN "Test Case %d: %s\n" RESET, i + 1, test.description);
    printf("  Input: " YELLOW "s = \"%s\", locked = \"%s\"\n" RESET, test.s, test.locked);
    printf("  Expected: %s, Actual: %s\n",
           test.expected ? GREEN "true" RESET : RED "false" RESET,
           actual ? GREEN "true" RESET : RED "false" RESET);

    if (actual == test.expected) {
      printf(GREEN "  Result: PASSED\n" RESET);
      passed++;
    } else {
      printf(RED "  Result: FAILED\n" RESET);
    }
    printf("\n");
  }

  printf(CYAN "Summary: " RESET "%d/%d Test Cases Passed\n", passed, numTestCases);

  return 0;
}
