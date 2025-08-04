#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100
#define MAX_USERS 50
#define MAX_EXPERIMENTS 100

typedef struct {
    char name[50];
    int quantity;
} Chemical;

typedef struct {
    char name[50];
    char type[50];
    int status; // 0 for available, 1 for in use
} Equipment;

typedef struct {
    char title[50];
    char date[20];
    char user[50];
} Experiment;

typedef struct {
    char username[50];
    char password[50];
    char role[20]; // e.g., "admin", "user"
} User;

Chemical chemicals[MAX_ITEMS];
Equipment equipment[MAX_ITEMS];
Experiment experiments[MAX_EXPERIMENTS];
User users[MAX_USERS];
int chemicalCount = 0, equipmentCount = 0, experimentCount = 0, userCount = 0;

// Function prototypes
void generateExperimentReport() {
    printf("Experiment Report:\n");
    printf("-------------------------------\n");
    printf("Title\t\tDate\t\tUser\n");
    printf("-------------------------------\n");
    for (int i = 0; i < experimentCount; i++) {
        printf("%s\t\t%s\t\t%s\n", experiments[i].title, experiments[i].date, experiments[i].user);
    }
    printf("-------------------------------\n");

}
void generateInventoryReport() {
    printf("Inventory Report:\n");
    printf("-------------------------------\n");
    printf("Name\t\tQuantity\n");
    printf("-------------------------------\n");
    for (int i = 0; i < chemicalCount; i++) {
        printf("%s\t\t\t%dml\n", chemicals[i].name, chemicals[i].quantity);
    }
    printf("-------------------------------\n");

    
}
void usageStatistics() {
    printf("Usage Statistics:\n");
    printf("-------------------------------\n");
    printf("Total Chemicals: %d\n", chemicalCount);
    printf("Total Equipment: %d\n", equipmentCount);
    printf("Total Users: %d\n", userCount);
    printf("Total Experiments: %d\n", experimentCount);
    printf("-------------------------------\n");

    
}
void addUser();
void login();
void loadUsers();
void saveUsers();
void loadChemicals();
void saveChemicals();
void loadEquipment();
void saveEquipment();
void loadExperiments();
void saveExperiments();
void displayDashboard();
void inventoryManagement();
void equipmentManagement();
void experimentTracking();
void userManagement();
void generateReport();
void exitSystem();

void generateReport() {
    int choice;
    do {
        printf("\nGenerate Report\n");
        printf("1. Generate Inventory Report\n");
        printf("2. Generate Experiment Report\n");
        printf("3. Usage Statistics\n");
        printf("0. Back to Dashboard\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: generateInventoryReport(); break;
            case 2: generateExperimentReport(); break;
            case 3: usageStatistics(); break;
            case 0: break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 0);
}

void addUser() {
    if (userCount < MAX_USERS) {
        printf("Enter username: ");
        scanf("%s", users[userCount].username);
        printf("Enter password: ");
        scanf("%s", users[userCount].password);
        strcpy(users[userCount].role, "user");
        userCount++;
    } else {
        printf("User limit reached!\n");
    }
}

void login() {
    char username[50], password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Login successful!\n");
            return;
        }
    }
    printf("Invalid username or password!\n");
    exit(1);
}

void loadUsers() {
    FILE *file = fopen("users.txt", "r");
    if (file) {
        while (fscanf(file, "%s %s %s", users[userCount].username, users[userCount].password, users[userCount].role) != EOF) {
            userCount++;
        }
        fclose(file);
    }
}

void saveUsers() {
    FILE *file = fopen("users.txt", "w");
    if (file) {
        for (int i = 0; i < userCount; i++) {
            fprintf(file, "%s %s %s\n", users[i].username, users[i].password, users[i].role);
        }
        fclose(file);
    }
}

// Inventory management functions
void addChemical() {
    if (chemicalCount < MAX_ITEMS) {
        printf("Enter chemical name: ");
        scanf("%s", chemicals[chemicalCount].name);
        printf("Enter quantity(in ml): ");
        scanf("%d", &chemicals[chemicalCount].quantity);
        chemicalCount++;
    } else {
        printf("Chemical limit reached!\n");
    }
}

void removeChemical() {
    char name[50];
    printf("Enter chemical name to remove: ");
    scanf("%s", name);
    for (int i = 0; i < chemicalCount; i++) {
        if (strcmp(chemicals[i].name, name) == 0) {
            chemicals[i] = chemicals[chemicalCount - 1]; // Remove last item
            chemicalCount--;
            printf("Chemical removed.\n");
            return;
        }
    }
    printf("Chemical not found.\n");
}

void updateChemical() {
    char name[50];
    printf("Enter chemical name to update: ");
    scanf("%s", name);
    for (int i = 0; i < chemicalCount; i++) {
        if (strcmp(chemicals[i].name, name) == 0) {
            printf("Enter new quantity: ");
            scanf("%d", &chemicals[i].quantity);
            printf("Chemical updated.\n");
            return;
        }
    }
    printf("Chemical not found.\n");
}

void listChemicals() {
    printf("List of Chemicals:\n");
    for (int i = 0; i < chemicalCount; i++) {
        printf("Name: %s, Quantity: %dml\n", chemicals[i].name, chemicals[i].quantity);
    }
}

void inventoryManagement() {
    int choice;
    do {
        printf("\nInventory Management\n");
        printf("1. Add Chemical\n");
        printf("2. Remove Chemical\n");
        printf("3. Update Chemical\n");
        printf("4. List Chemicals\n");
        printf("0. Back to Dashboard\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addChemical(); break;
            case 2: removeChemical(); break;
            case 3: updateChemical(); break;
            case 4: listChemicals(); break;
            case 0: break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 0);
}

// Equipment management functions
void addEquipment() {
    if (equipmentCount < MAX_ITEMS) {
        printf("Enter equipment name: ");
        scanf("%s", equipment[equipmentCount].name);
        printf("Enter equipment type: ");
        scanf("%s", equipment[equipmentCount].type);
        equipment[equipmentCount].status = 0; // Set to available
        equipmentCount++;
    } else {
        printf("Equipment limit reached!\n");
    }
}

void removeEquipment() {
    char name[50];
    printf("Enter equipment name to remove: ");
    scanf("%s", name);
    for (int i = 0; i < equipmentCount; i++) {
        if (strcmp(equipment[i].name, name) == 0) {
            equipment[i] = equipment[equipmentCount - 1]; // Remove last item
            equipmentCount--;
            printf("Equipment removed.\n");
            return;
        }
    }
    printf("Equipment not found.\n");
}

void updateEquipment() {
    char name[50];
    printf("Enter equipment name to update: ");
    scanf("%s", name);
    for (int i = 0; i < equipmentCount; i++) {
        if (strcmp(equipment[i].name, name) == 0) {
            printf("Enter new type: ");
            scanf("%s", equipment[i].type);
            printf("Equipment updated.\n");
            return;
        }
    }
    printf("Equipment not found.\n");
}

void listEquipment() {
    printf("List of Equipment:\n");
    for (int i = 0; i < equipmentCount; i++) {
        printf("Name: %s, Type: %s, Status: %s\n",
               equipment[i].name, equipment[i].type,
               equipment[i].status == 0 ? "Available" : "In Use");
    }
}

void equipmentManagement() {
    int choice;
    do {
        printf("\nEquipment Management\n");
        printf("1. Add Equipment\n");
        printf("2. Remove Equipment\n");
        printf("3. Update Equipment\n");
        printf("4. List Equipment\n");
        printf("0. Back to Dashboard\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEquipment(); break;
            case 2: removeEquipment(); break;
            case 3: updateEquipment(); break;
            case 4: listEquipment(); break;
            case 0: break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 0);
}

// Experiment tracking functions
void logExperiment() {
    if (experimentCount < MAX_EXPERIMENTS) {
        printf("Enter experiment title: ");
        scanf("%s", experiments[experimentCount].title);
        printf("Enter date: ");
        scanf("%s", experiments[experimentCount].date);
        printf("Enter username: ");
        scanf("%s", experiments[experimentCount].user);
        experimentCount++;
    } else {
        printf("Experiment limit reached!\n");
    }
}

void viewExperiments() {
    printf("List of Experiments:\n");
    for (int i = 0; i < experimentCount; i++) {
        printf("Title: %s, Date: %s, User: %s\n",
               experiments[i].title, experiments[i].date, experiments[i].user);
    }
}

void updateExperiment() {
    char title[50];
    printf("Enter experiment title to update: ");
    scanf("%s", title);
    for (int i = 0; i < experimentCount; i++) {
        if (strcmp(experiments[i].title, title) == 0) {
            printf("Enter new date: ");
            scanf("%s", experiments[i].date);
            printf("Experiment updated.\n");
            return;
        }
    }
    printf("Experiment not found.\n");
}

void experimentTracking() {
    int choice;
    do {
        printf("\nExperiment Tracking\n");
        printf("1. Log New Experiment\n");
        printf("2. View Experiments\n");
        printf("3. Update Experiment\n");
        printf("0. Back to Dashboard\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: logExperiment(); break;
            case 2: viewExperiments(); break;
            case 3: updateExperiment(); break;
            case 0: break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 0);
}

// User management functions
void removeUser() {
    char username[50];
    printf("Enter username to remove: ");
    scanf("%s", username);
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            users[i] = users[userCount - 1]; // Remove last item
            userCount--;
            printf("User removed.\n");
            return;
        }
    }
    printf("User not found.\n");
}

void updateUser() {
    char username[50];
    printf("Enter username to update: ");
    scanf("%s", username);
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Enter new password: ");
            scanf("%s", users[i].password);
            printf("User updated.\n");
            return;
        }
    }
    printf("User not found.\n");
}

void userManagement() {
    int choice;
    do {
        printf("\nUser Management\n");
        printf("1. Add User\n");
        printf("2. Remove User\n");
        printf("3. Update User\n");
        printf("0. Back to Dashboard\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addUser(); break;
            case 2: removeUser(); break;
            case 3: updateUser(); break;
            case 0: break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 0);
}




// File handling
void loadChemicals() {
    FILE *file = fopen("chemicals.txt", "r");
    if (file) {
        while (fscanf(file, "%s %d", chemicals[chemicalCount].name, &chemicals[chemicalCount].quantity) != EOF) {
            chemicalCount++;
        }
        fclose(file);
    }
}

void saveChemicals() {
    FILE *file = fopen("chemicals.txt", "w");
    if (file) {
        for (int i = 0; i < chemicalCount; i++) {
            fprintf(file, "%s %d\n", chemicals[i].name, chemicals[i].quantity);
        }
        fclose(file);
    }
}

void loadEquipment() {
    FILE *file = fopen("equipment.txt", "r");
    if (file) {
        while (fscanf(file, "%s %s %d", equipment[equipmentCount].name, equipment[equipmentCount].type, &equipment[equipmentCount].status) != EOF) {
            equipmentCount++;
        }
        fclose(file);
    }
}

void saveEquipment() {
    FILE *file = fopen("equipment.txt", "w");
    if (file) {
        for (int i = 0; i < equipmentCount; i++) {
            fprintf(file, "%s %s %d\n", equipment[i].name, equipment[i].type, equipment[i].status);
        }
        fclose(file);
    }
}

void loadExperiments() {
    FILE *file = fopen("experiments.txt", "r");
    if (file) {
        while (fscanf(file, "%s %s %s", experiments[experimentCount].title, experiments[experimentCount].date, experiments[experimentCount].user) != EOF) {
            experimentCount++;
        }
        fclose(file);
    }
}

void saveExperiments() {
    FILE *file = fopen("experiments.txt", "w");
    if (file) {
        for (int i = 0; i < experimentCount; i++) {
            fprintf(file, "%s %s %s\n", experiments[i].title, experiments[i].date, experiments[i].user);
        }
        fclose(file);
    }
}

void exitSystem() {
    saveUsers();
    saveChemicals();
    saveEquipment();
    saveExperiments();
    printf("Data saved. Exiting...\n");
    exit(0);
}

void displayDashboard() {
    int choice;
    do {
        printf("\nDashboard\n");
        printf("1. Inventory Management\n");
        printf("2. Equipment Management\n");
        printf("3. Experiment Tracking\n");
        printf("4. User Management\n");
        printf("5. Generate Report\n");
        printf("0. Save and Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: inventoryManagement(); break;
            case 2: equipmentManagement(); break;
            case 3: experimentTracking(); break;
            case 4: userManagement(); break;
            case 5: generateReport(); break;
            case 0: exitSystem(); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 0);
}

int main() {
    loadUsers();
    loadChemicals();
    loadEquipment();
    loadExperiments();

    int option;
    printf("Welcome to the Chemistry Laboratory Management System\n");
    printf("1. Add New User\n");
    printf("2. Login as Existing User\n");
    printf("Choose an option: ");
    scanf("%d", &option);

    switch (option) {
        case 1: addUser(); break;
        case 2: login(); break;
        default: printf("Invalid option!\n"); exit(1);
    }

    displayDashboard();
    return 0;
}
