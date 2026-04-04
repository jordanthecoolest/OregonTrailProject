#include <stdio.h>

void shop(float *money) {
    int choice, qty;
    int inv[6] = {0};
    char *items[] = {"Food", "Clothing", "Oxen", "Ammunition", "Medicine", "Spare Parts"};
    float prices[] = {0.20, 10.00, 40.00, 2.00, 5.00, 50.00};
    char *units[] = {"lbs", "sets", "yokes", "boxes", "sets", "sets"};
    
    int running = 1;
    
    do {
        printf("\nMoney: $%.2f\n", *money);
        printf("1. Food (20¢/lb)\n");
        printf("2. Clothing ($10/set)\n");
        printf("3. Oxen ($40/yoke)\n");
        printf("4. Ammunition ($2/box)\n");
        printf("5. Medicine ($5/set)\n");
        printf("6. Spare Parts ($50/set)\n");
        printf("0. Exit shop\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        if (choice == 0) {
            running = 0;
        }
        else if (choice >= 1 && choice <= 6) {
            printf("How many %s? ", items[choice-1]);
            scanf("%d", &qty);
            
            if (qty > 0) {
                float cost = qty * prices[choice-1];
                if (cost <= *money) {
                    *money -= cost;
                    inv[choice-1] += qty;
                    printf("Bought %d %s of %s. Remaining: $%.2f\n", 
                           qty, units[choice-1], items[choice-1], *money);
                    if (choice == 3 && inv[2] < 3)
                        printf("Tip: It's recommended to have at least 3 yokes of oxen\n");
                } else {
                    printf("Not enough money! Need $%.2f\n", cost);
                }
            } else {
                printf("Quantity must be positive.\n");
            }
        } else {
            printf("Invalid choice. Please select 0-6.\n");
        }
        
    } while (running);

    printf("\n--- Final Inventory ---\n");
    for (int i = 0; i < 6; i++)
        printf("%s: %d %s\n", items[i], inv[i], units[i]);
}

int main() {
    float money = 400.00;
    
    printf("Starting money: $%.2f\n", money);
    shop(&money);
    printf("\nExited shop with $%.2f\n", money);
    
    return 0;
}