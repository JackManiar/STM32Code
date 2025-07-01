#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 256
#define MAX_MUX 16
#define MAX_POTS 16

typedef struct {
    int wiper;
    int muxInd;
    int potInd;
} PotEntry;

int main() {
    FILE *file = fopen("PotentiometerIndices.csv", "r");
    if (!file) {
        perror("Error opening input file");
        return 1;
    }

    PotEntry entries[MAX_MUX][MAX_POTS] = {0};
    int potExists[MAX_MUX][MAX_POTS] = {0};
    char line[MAX_LINE_LEN];
    int totalWipers = 0;

    // skip header
    fgets(line, sizeof(line), file);

    // read entries
    while (fgets(line, sizeof(line), file)) {
        int wiper, muxInd, potInd;
        if (sscanf(line, "%d,%d,%d", &wiper, &muxInd, &potInd) != 3) {
            fprintf(stderr, "Invalid row: %s", line);
            continue;
        }

        if (muxInd < 0 || muxInd >= MAX_MUX || potInd < 0 || potInd >= MAX_POTS) {
            fprintf(stderr, "Out of bounds: mux=%d, pot=%d\n", muxInd, potInd);
            continue;
        }

        if (potExists[muxInd][potInd]) {
            fprintf(stderr, "Duplicate: mux=%d pot=%d (wiper=%d already exists)\n",
                    muxInd, potInd, entries[muxInd][potInd].wiper);
        } else {
            totalWipers++;
        }

        entries[muxInd][potInd] = (PotEntry){.wiper = wiper, .muxInd = muxInd, .potInd = potInd};
        potExists[muxInd][potInd] = 1;
    }

    fclose(file);

    // validate and report
    for (int mux = 0; mux < MAX_MUX; mux++) {
        int count = 0;
        for (int pot = 0; pot < MAX_POTS; pot++) {
            if (potExists[mux][pot]) count++;
        }

        if (count == 0) continue;

        if (count != 16) {
            printf("❌ muxInd %d has %d potInds (should be 16)\n", mux, count);
            for (int pot = 0; pot < MAX_POTS; pot++) {
                if (!potExists[mux][pot])
                    printf("   - Missing potInd %d\n", pot);
            }
        } else {
            printf("✅ muxInd %d is complete\n", mux);
        }
    }

    // write sorted CSV
    FILE *out = fopen("pots_sorted.csv", "w");
    if (!out) {
        perror("Error opening output file");
        return 1;
    }

    fprintf(out, "wiper,muxInd,potInd\n");

    for (int mux = 0; mux < MAX_MUX; mux++) {
        for (int pot = 0; pot < MAX_POTS; pot++) {
            if (potExists[mux][pot]) {
                PotEntry e = entries[mux][pot];
                fprintf(out, "%d,%d,%d\n", e.wiper, e.muxInd, e.potInd);
            }
        }
    }

    fclose(out);
    printf("✅ Sorted output written to 'pots_sorted.csv'\n");

    // generate C++ array
    printf("\n// Copy this into your MuxedPot.cpp file:\n");
    printf("const WiperMapEntry MuxedPot::wiperMap[] = {\n");

    for (int mux = 0; mux < MAX_MUX; mux++) {
        for (int pot = 0; pot < MAX_POTS; pot++) {
            if (potExists[mux][pot]) {
                PotEntry e = entries[mux][pot];
                printf("    {%d, %d, %d},  // wiper %d\n", e.wiper, e.muxInd, e.potInd, e.wiper);
            }
        }
    }

    printf("};\n\n#define NUM_WIPERS %d\n", totalWipers);

    return 0;
}
