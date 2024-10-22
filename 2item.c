#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100
#define MAX_TRANS 100
#define MIN_SUPPORT 2

typedef struct {
    char items[2][10]; // For 2-itemsets
    int count;
} Itemset;

typedef struct {
    char transactions[MAX_TRANS][MAX_ITEMS][10]; // Transactions with items
    int transaction_count;
} Dataset;

// Function to count support for 2-itemsets
void count_itemsets(Dataset dataset, Itemset *itemsets, int *itemset_count) {
    for (int i = 0; i < dataset.transaction_count; i++) {
        for (int j = 0; j < dataset.transaction_count; j++) {
            if (j <= i) continue; // Avoid duplicate pairs

            // Check if both items are in the transaction
            for (int k = 0; k < MAX_ITEMS && dataset.transactions[i][k][0]; k++) {
                for (int l = 0; l < MAX_ITEMS && dataset.transactions[j][l][0]; l++) {
                    if (strcmp(dataset.transactions[i][k], dataset.transactions[j][l]) == 0) {
                        continue; // Skip if same item
                    }

                    // Form the 2-itemset
                    Itemset new_itemset;
                    strcpy(new_itemset.items[0], dataset.transactions[i][k]);
                    strcpy(new_itemset.items[1], dataset.transactions[j][l]);
                    new_itemset.count = 0;

                    // Check if this itemset already exists
                    int found = 0;
                    for (int m = 0; m < *itemset_count; m++) {
                        if (strcmp(itemsets[m].items[0], new_itemset.items[0]) == 0 &&
                            strcmp(itemsets[m].items[1], new_itemset.items[1]) == 0) {
                            found = 1;
                            itemsets[m].count++;
                            break;
                        }
                    }

                    // If not found, add to the itemsets
                    if (!found) {
                        itemsets[*itemset_count] = new_itemset;
                        itemsets[*itemset_count].count = 1;
                        (*itemset_count)++;
                    }
                }
            }
        }
    }
}

// Function to print the frequent itemsets
void print_frequent_itemsets(Itemset *itemsets, int itemset_count) {
    printf("Frequent 2-itemsets (min support = %d):\n", MIN_SUPPORT);
    for (int i = 0; i < itemset_count; i++) {
        if (itemsets[i].count >= MIN_SUPPORT) {
            printf("{%s, %s}: %d\n", itemsets[i].items[0], itemsets[i].items[1], itemsets[i].count);
        }
    }
}

int main() {
    Dataset dataset = {
        .transactions = {
            {"A"}, {"B"}, {"C"},
            {"A"}, {"B"},
            {"A"}, {"C"},
            {"B"}, {"C"},
            {"A"}, {"B"}, {"C"},
            {"B"}
        },
        .transaction_count = 6
    };

    Itemset itemsets[MAX_ITEMS];
    int itemset_count = 0;

    count_itemsets(dataset, itemsets, &itemset_count);
    print_frequent_itemsets(itemsets, itemset_count);

    return 0;
}
//---------------------------------------------------------------------------------------------
//gcc -o frequent_itemsets frequent_itemsets.c
//./frequent_itemsets

