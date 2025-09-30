#include <limits.h>
#include <string.h>
#include <stdio.h> // Added for printf and scanf

int main() {
    int n;
    /* exact prompt */
    printf("Enter the number of process:");
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    char name[100][32];
    int at[100], bt[100];
    int ct[100], wt[100], tat[100];
    int order[100];

    for (int i = 0; i < n; ++i) {
        printf("Enter process name, arrival time & execution time:");
        if (scanf("%31s %d %d", name[i], &at[i], &bt[i]) != 3) return 0;
        order[i] = i; // Store original index
    }

    /* sort indices by arrival time, tie-breaker: input order */
    for (int i = 0; i < n - 1; ++i) { // Fix: Loop bounds for sorting
        for (int j = i + 1; j < n; ++j) {
            if (at[order[i]] > at[order[j]]) {
                int tmp = order[i];
                order[i] = order[j];
                order[j] = tmp;
            }
        }
    }

    /* simulate FCFS according to sorted order */
    int t = 0; // Initialize time, assuming processes can arrive at t=0
    for (int i = 0; i < n; ++i) {
        if (at[order[i]] < t) { // If a process arrives before current time
             t = t; // No change, current time is ahead of arrival
        } else { // Process arrives after or at current time
            t = at[order[i]]; // Set current time to arrival time
        }
    }


    for (int k = 0; k < n; ++k) {
        int i = order[k];
        if (t < at[i]) t = at[i]; // Advance time to arrival if process hasn't arrived
        int start = t;
        ct[i] = start + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = start - at[i];
        t = ct[i];
    }

    double total_wt = 0.0, total_tat = 0.0;
    for (int i = 0; i < n; ++i) {
        total_wt += wt[i];
        total_tat += tat[i];
    }

    /* print in the same order as input, with arrows as requested */
    printf("Pname\tarrivaltime\texecutiontime\twaitingtime\ttatime\n");
    for (int i = 0; i < n; ++i) { // Changed order[i] to just i for original input order
        printf("%s\t%5d\t\t%5d\t\t%5d\t\t%5d\n", name[i], at[i], bt[i], wt[i], tat[i]);
    }

    printf("Average waiting time is:%.6f\n", total_wt / n);
    printf("Average turnaround time is:%.6f\n", total_tat / n); // Added this line for average TAT

    return 0;
}
