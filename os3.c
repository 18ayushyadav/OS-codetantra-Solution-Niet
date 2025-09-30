#include <stdio.h>
#include <limits.h> // For INT_MAX
#include <string.h> // For string operations, though not explicitly used for actual strings in this snippet

int main() {
    int n;

    /* exact prompt as in your expected output */
    printf("Enter the number of process:");
    if (scanf("%d", &n) != 1 || n <= 0) return 1; // Added error handling for scanf and non-positive n

    char name[100][32]; // Process name (assuming max 31 chars + null terminator)
    int at[100], bt[100], pr[100]; // Arrival Time, Burst Time, Priority
    int ct[100], tat[100], wt[100], completed[100]; // Completion Time, Turnaround Time, Waiting Time, Completion Status

    for (int i = 0; i < n; ++i) {
        printf("Enter process name, arrival time, execution time & priority:");
        if (scanf("%31s %d %d %d", name[i], &at[i], &bt[i], &pr[i]) != 4) return 1; // Added error handling for scanf
        completed[i] = 0; // Initialize as not completed
        ct[i] = tat[i] = wt[i] = 0; // Initialize times
    }

    int t = INT_MAX;
    for (int i = 0; i < n; ++i) {
        if (at[i] < t) t = at[i]; // Start at earliest arrival time
    }

    int done = 0;
    double total_wt = 0.0, total_tat = 0.0;

    while (done < n) {
        int idx = -1;
        int best_pr = INT_MAX; // Lower value means higher priority

        for (int i = 0; i < n; ++i) {
            if (!completed[i] && at[i] <= t) { // If not completed and arrived by current time
                if (pr[i] < best_pr) {
                    best_pr = pr[i];
                    idx = i;
                } else if (pr[i] == best_pr) {
                    // Tie-breaker: FCFS (earliest arrival), then by process index (original order)
                    if (idx == -1 || at[i] < at[idx] || (at[i] == at[idx] && i < idx)) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) { // No process is ready at current time 't'
            int next_at = INT_MAX;
            for (int i = 0; i < n; ++i) {
                if (!completed[i] && at[i] < next_at) {
                    next_at = at[i]; // Find the next arrival time
                }
            }
            if (next_at != INT_MAX) { // Advance time to the next arrival
                t = next_at;
            } else { // No more processes to schedule
                break;
            }
            continue;
        }

        // Execute the selected process
        t += bt[idx]; // Update current time by burst time
        ct[idx] = t;
        tat[idx] = ct[idx] - at[idx];
        wt[idx] = tat[idx] - bt[idx];
        
        total_tat += tat[idx];
        total_wt += wt[idx];
        
        completed[idx] = 1; // Mark as completed
        done++;
    }

    // Aligned header using arrows as requested
    printf("\nPname\tarrivaltime\texecutiontime\tpriority\twaitingtime\ttatime\n");

    // Print rows aligned to columns
    for (int i = 0; i < n; ++i) {
        // widths chosen to align reasonably for typical small integers and short names
        printf("%-5s\t%5d\t\t%5d\t\t%5d\t\t%5d\t\t%5d\n", name[i], at[i], bt[i], pr[i], wt[i], tat[i]);
    }

    printf("Average waiting time is:%.6f\n", total_wt / n);
    printf("Average turnaround time is:%.6f\n", total_tat / n);

    return 0;
}
