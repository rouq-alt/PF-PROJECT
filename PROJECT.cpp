#include <stdio.h>
#include <string.h>
#include <stdlib.h>

    int code;
    char name[20];
    char supplier[20];
    int quantity;
};

// Function to display the main menu
int menu() {
    int choice;
    printf("\n\n MAIN MENU \n");
    puts(" Enter 1 for Inventory management");
    puts(" Enter 2 for Events management");
    puts(" Enter 3 for Employee Management");
    puts(" Enter 4 for Delivery Management");
    puts(" Enter 0 to exit program");
    printf(" Enter choice: ");
    scanf("%d", &choice);
    return choice;
}


void saveInventoryToFile(struct items item[], int count) {
    FILE *file = fopen("inventory.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%s,%d\n", item[i].code, item[i].name, item[i].supplier, item[i].quantity);
    }

    fclose(file);
    printf("Inventory saved to file.\n");
}


void loadInventoryFromFile(struct items item[], int *count) {
    FILE *file = fopen("inventory.txt", "r");
    if (file == NULL) {
        printf("File not found. Starting with default inventory.\n");
        *count = 0; 
        return;
    }

    int i = 0;
    while (fscanf(file, "%d,%19[^,],%19[^,],%d\n", &item[i].code, item[i].name, item[i].supplier, &item[i].quantity) == 4) {
        i++;
    }

    *count = i;
    fclose(file);
    printf("Inventory loaded from file. Total items: %d\n", *count);
}

// Inventory management functionality
void inventory() {
    puts("\nINVENTORY MANAGEMENT\n");
    int choice = 1, qty = 0, currentItems = 0, searchCode;
    char searchSup[20];
    struct items item[100];


    loadInventoryFromFile(item, &currentItems);

    while (choice != 0) {
        puts("\n\tINVENTORY MENU\n");
        puts("\t1. Find number of items in the inventory");
        puts("\t2. Display current inventory");
        puts("\t3. List details of all items by a supplier");
        puts("\t4. Find item details by code");
        puts("\t5. Add item information");
        puts("\t6. Update stock");
        puts("\t0. Exit inventory");
        printf("\tEnter choice: ");
        scanf("%d", &choice);
        getchar();

        int i;
        switch (choice) {
            case 0:
                saveInventoryToFile(item, currentItems);
                printf("\tExiting Inventory...\n");
                break;

            case 1:
                printf("\tTotal items: %d\n", currentItems);
                break;

            case 2:
                if (currentItems == 0) {
                    printf("\tNo items in inventory.\n");
                } else {
                    for (i = 0; i < currentItems; i++) {
                        printf("\n\tItem Code: %d\n", item[i].code);
                        printf("\tItem Name: %s\n", item[i].name);
                        printf("\tSupplier: %s\n", item[i].supplier);
                        printf("\tQuantity: %d\n", item[i].quantity);
                        if (item[i].quantity <= 5) {
                            printf("\t**** LOW STOCK ****\n");
                        }
                    }
                }
                break;

            case 3:
                printf("\tEnter supplier name: ");
                fgets(searchSup, 20, stdin);
                searchSup[strcspn(searchSup, "\n")] = 0; 
                printf("\tItems supplied by %s:\n", searchSup);

                for (i = 0; i < currentItems; i++) {
                    if (strcmp(searchSup, item[i].supplier) == 0) {
                        printf("\tItem Code: %d\n", item[i].code);
                        printf("\tItem Name: %s\n", item[i].name);
                        printf("\tQuantity: %d\n\n", item[i].quantity);
                    }
                }
                break;

            case 4:
                printf("\tEnter item code: ");
                scanf("%d", &searchCode);
                for (i = 0; i < currentItems; i++) {
                    if (searchCode == item[i].code) {
                        printf("\tItem Code: %d\n", item[i].code);
                        printf("\tItem Name: %s\n", item[i].name);
                        printf("\tSupplier: %s\n", item[i].supplier);
                        printf("\tQuantity: %d\n", item[i].quantity);
                    }
                }
                break;

            case 5:
                printf("\tEnter item code: ");
                scanf("%d", &item[currentItems].code);
                getchar();

                printf("\tEnter item name: ");
                fgets(item[currentItems].name, 20, stdin);
                item[currentItems].name[strcspn(item[currentItems].name, "\n")] = 0;

                printf("\tEnter supplier: ");
                fgets(item[currentItems].supplier, 20, stdin);
                item[currentItems].supplier[strcspn(item[currentItems].supplier, "\n")] = 0;

                printf("\tEnter quantity: ");
                scanf("%d", &item[currentItems].quantity);

                currentItems++;
                printf("\tItem added successfully!\n");
                break;

            case 6:
                printf("\tEnter item code to update stock: ");
                scanf("%d", &searchCode);
                for (i = 0; i < currentItems; i++) {
                    if (searchCode == item[i].code) {
                        printf("\tEnter quantity to add: ");
                        scanf("%d", &qty);
                        item[i].quantity += qty;
                        printf("\tStock updated. New quantity: %d\n", item[i].quantity);
                    }
                }
                break;

            default:
                printf("\tInvalid entry. Please try again.\n");
        }
    }
}


void events() {
    int g = -1;
    puts("\nEVENT MANAGEMENT \n");
    while (g != 0) {
        puts("\n\tEVENT MANAGEMENT MENU\n");
        puts("\tEnter 1 for male team schedule");
        puts("\tEnter 2 for female team schedule");
        puts("\tEnter 0 to exit event management");
        printf("\tEnter choice: ");
        scanf("%d", &g);

        switch (g) {
            case 1:
                puts("[Male team schedule]");
                break;
            case 2:
                puts("[Female team schedule]");
                break;
            case 0:
                puts("Exiting event management...");
                break;
            default:
                puts("Invalid choice");
        }
    }
}

void employee() {
     char employee[25][100];
    char department[25][10];
    int salary[25];
    int employeeCount = 0, choice;

    while (1) {
        printf("\nEMPLOYEE MANAGEMENT\n");
        printf("1. Add Employee\n");
        printf("2. Display all Employees\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 3) break;

        switch (choice) {
            case 1:
                if (employeeCount < 25) {
                    printf("Enter employee name: ");
                    fgets(employee[employeeCount], 100, stdin);
                    employee[employeeCount][strcspn(employee[employeeCount], "\n")] = 0;

                    printf("Enter department: ");
                    fgets(department[employeeCount], 10, stdin);
                    department[employeeCount][strcspn(department[employeeCount], "\n")] = 0;

                    printf("Enter salary: ");
                    scanf("%d", &salary[employeeCount]);
                    getchar();

                    employeeCount++;
                    printf("Employee added.\n");
                } else {
                    printf("Maximum employees reached!\n");
                }
                break;

            case 2:
                printf("Current Employees:\n");
                for (int i = 0; i < employeeCount; i++) {
                    printf("Name: %s, Dept: %s, Salary: %d\n", employee[i], department[i], salary[i]);
                }
                break;

            default:
                printf("Invalid choice\n");
        }
    }
}
void deliverySystem() {
    int choice;

    do {
        printf("\nDELIVERY SYSTEM\n");
        printf("1. Request Delivery\n");
        printf("2. View Delivery Logs\n");
        printf("0. Exit Delivery System\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Request delivery
                FILE *file = fopen("delivery(1).txt", "a");
                if (file == NULL) {
                    printf("Error: Unable to open delivery log file!\n");
                    break;
                }

                char item[50], company[50], address[100];
                printf("\nEnter item name: ");
                getchar(); 
                fgets(item, sizeof(item), stdin);
                item[strcspn(item, "\n")] = 0; 

                printf("Enter company name: ");
                fgets(company, sizeof(company), stdin);
                company[strcspn(company, "\n")] = 0; 

                printf("Enter delivery address: ");
                fgets(address, sizeof(address), stdin);
                address[strcspn(address, "\n")] = 0; 

                fprintf(file, "Item: %s\nCompany: %s\nAddress: %s\n\n", item, company, address);
                fclose(file);

                printf("Delivery request saved successfully!\n");
                break;
            }
            case 2: {
                FILE *file = fopen("D:/Downloads/delivery.txt", "r");
                if (file == NULL) {
                    printf("No deliveries found yet!\n");
                    break;
                }

                char line[150];
                printf("\n--- Delivery Log ---\n");
                while (fgets(line, sizeof(line), file)) {
                    printf("%s", line);
                }
                fclose(file);
                printf("--- End of Log ---\n");
                break;
            }
            case 0:
                printf("Exiting delivery system...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);
}
int main() {
    int choice;
    do {
        choice = menu();
        switch (choice) {
            case 1:
                inventory();
                break;
            case 2:
                events();
                break;
            case 3:
                employee();
                break;
             case 4:
                deliverySystem(); 
                break;   
            case 0:
                printf("Closing program...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 0);
    return 0;
}
 
