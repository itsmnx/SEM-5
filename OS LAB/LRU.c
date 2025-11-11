//LRU-practical 12(06-11-2025)

#include <stdio.h>
#define MAX_FRAMES 10
#define MAX_REFERENCES 50

int main() {
    printf("Manas joshi | Section-C | Roll no; 37\n");
    int num_references, num_frames;
    int refs[MAX_REFERENCES];
    int frames[MAX_FRAMES];
    int last_used[MAX_FRAMES];

    printf("Enter the number of frames (max %d): ", MAX_FRAMES);
    scanf("%d", &num_frames);
    if (num_frames <= 0 || num_frames > MAX_FRAMES) {
        printf("Invalid number of frames.\n");
        return 1;
    }

    printf("Enter the number of page references (max %d): ", MAX_REFERENCES);
    scanf("%d", &num_references);
    if (num_references <= 0 || num_references > MAX_REFERENCES) {
        printf("Invalid number of references.\n");
        return 1;
    }

    printf("Enter the page reference sequence:\n");
    for (int i = 0; i < num_references; i++) {
        scanf("%d", &refs[i]);
    }

    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
        last_used[i] = -1;
    }

    int page_faults = 0, page_hits = 0, time = 0;

    printf("\nSimulation Start (LRU)\n");
    printf("Ref\tStatus\tFrames\n");
    printf("---\t------\t");
    for (int i = 0; i < num_frames; i++) printf("F%d ", i);
    printf("\n");

    for (int i = 0; i < num_references; i++) {
        int page = refs[i];
        int hit = 0;

        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                hit = 1;
                last_used[j] = time++;
                break;
            }
        }

        if (hit) {
            page_hits++;
            printf("%d\tHit\t", page);
        } else {
            page_faults++;
            int placed = 0;

            for (int j = 0; j < num_frames; j++) {
                if (frames[j] == -1) {
                    frames[j] = page;
                    last_used[j] = time++;
                    placed = 1;
                    break;
                }
            }

            if (!placed) {
                int lru_index = 0;
                for (int j = 1; j < num_frames; j++) {
                    if (last_used[j] < last_used[lru_index]) {
                        lru_index = j;
                    }
                }
                frames[lru_index] = page;
                last_used[lru_index] = time++;
            }

            printf("%d\tFault\t", page);
        }

        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("\nTotal references: %d\n", num_references);
    printf("Page Faults: %d\n", page_faults);
    printf("Page Hits: %d\n", page_hits);
    printf("Fault ratio: %.3f\n", (double)page_faults / num_references);

    return 0;
}
