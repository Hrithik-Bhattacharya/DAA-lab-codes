#include <stdio.h>
#include <string.h>
#define NO_OF_CHARS 256

// Preprocess: build bad character table
void badCharHeuristic(char *pat, int m, int badChar[NO_OF_CHARS]) {
    for (int i = 0; i < NO_OF_CHARS; i++)
        badChar[i] = -1;

    for (int i = 0; i < m; i++)
        badChar[(unsigned char)pat[i]] = i;
}

// Boyer-Moore search using bad character rule
int boyerMooreSearch(char *txt, char *pat) {
    int n = strlen(txt);
    int m = strlen(pat);
    int badChar[NO_OF_CHARS];

    badCharHeuristic(pat, m, badChar);

    int s = 0; // shift of the pattern
    while (s <= (n - m)) {
        int j = m - 1;

        // Compare from right to left
        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        if (j < 0) {
            return 1; // Match found
            // Shift pattern to align next possible match
            s += (s + m < n) ? m - badChar[(unsigned char)txt[s + m]] : 1;
        } else {
            // Shift pattern so that bad character aligns
            s += (j - badChar[(unsigned char)txt[s + j]] > 1) ? 
                 (j - badChar[(unsigned char)txt[s + j]]) : 1;
        }
    }
    return 0; // No match
}

int main() {
    char text[1000], pattern[1000];

    printf("Enter text: ");
    scanf("%s", text); // read full line

    printf("Enter pattern: ");
    scanf("%s", pattern);

    if (boyerMooreSearch(text, pattern))
        printf("Pattern found in text.\n");
    else
        printf("Pattern not found.\n");

    return 0;
}
