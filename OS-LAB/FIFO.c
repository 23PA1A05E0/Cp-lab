#include <stdio.h>
#include <stdlib.h>

// Function to simulate FIFO page replacement
int fifo(int pages[], int n, int capacity) {
    // Array to represent the frames in memory
    int *frames = (int *)malloc(capacity * sizeof(int));
    for (int i = 0; i < capacity; i++) {
        frames[i] = -1; // Initialize frames as empty (-1 represents empty)
    }

    int page_faults = 0; // Counter for page faults
    int index = 0;       // Index to keep track of the oldest page

    printf("Page Replacement Process:\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in memory
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        // If the page is not in memory, replace the oldest page
        if (!found) {
            frames[index] = page; // Replace the page at the current index
            page_faults++;        // Increment page fault count
            index = (index + 1) % capacity; // Move to the next frame (circular queue)

            // Print the current state of frames
            printf("Page %d -> Frames: ", page);
            for (int j = 0; j < capacity; j++) {
                if (frames[j] == -1)
                    printf("[ ] ");
                else
                    printf("[%d] ", frames[j]);
            }
            printf(" (Page Fault)\n");
        } else {
            // Print the current state of frames (no page fault)
            printf("Page %d -> Frames: ", page);
            for (int j = 0; j < capacity; j++) {
                if (frames[j] == -1)
                    printf("[ ] ");
                else
                    printf("[%d] ", frames[j]);
            }
            printf(" (No Page Fault)\n");
        }
    }

    free(frames); // Free dynamically allocated memory
    return page_faults;
}

int main() {
    int n, capacity;

    // Input: Number of pages and memory capacity
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int *pages = (int *)malloc(n * sizeof(int));
    printf("Enter the page reference sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames (capacity): ");
    scanf("%d", &capacity);

    // Simulate FIFO page replacement
    int page_faults = fifo(pages, n, capacity);
    printf("\nTotal Page Faults: %d\n", page_faults);

    free(pages); // Free dynamically allocated memory
    return 0;
}
