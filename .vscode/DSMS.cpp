#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // for system()
using namespace std;

class DepartmentStore {
public:
    void showMenu();
    void addItem();
    void displayItems();
    void checkItem();
    void updateItem();
    void deleteItem();
};

// Display Control Panel
void DepartmentStore::showMenu() {
    system("Color 0A");
    system("cls");
    cout << "*******************************************************\n";
    cout << "\t\tDepartment Store Management System\n";
    cout << "*******************************************************\n";
    cout << "1. Add New Item\n";
    cout << "2. Display All Items\n";
    cout << "3. Check Specific Item\n";
    cout << "4. Update Item Details\n";
    cout << "5. Delete Item\n";
    cout << "6. Exit\n";
    cout << "*******************************************************\n";
}

// Add New Item
void DepartmentStore::addItem() {
    system("cls");
    system("Color 0A");
    fstream file;
    int itemCount, itemId;
    string itemName, companyName;

    cout << "Add New Item:\n";
    cout << "-----------------------------------------------\n";
    cout << "Item ID: ";
    cin >> itemId;
    cout << "Item Name: ";
    cin >> itemName;
    cout << "Company Name: ";
    cin >> companyName;
    cout << "Quantity: ";
    cin >> itemCount;

    file.open("items.txt", ios::out | ios::app);
    file << itemId << " " << itemName << " " << companyName << " " << itemCount << "\n";
    file.close();

    cout << "Item added successfully!\n";
}

// Display All Items
void DepartmentStore::displayItems() {
    system("cls");
    system("Color 0A");
    fstream file;
    int itemCount, itemId;
    string itemName, companyName;

    file.open("items.txt", ios::in);
    if (!file) {
        cout << "Error: Unable to open file.\n";
        return;
    }

    cout << "Item Details:\n";
    cout << "--------------------------------------------------\n";
    cout << "ID\tName\t\tCompany\t\tQuantity\n";
    cout << "--------------------------------------------------\n";

    while (file >> itemId >> itemName >> companyName >> itemCount) {
        cout << itemId << "\t" << itemName << "\t\t" << companyName << "\t\t" << itemCount << "\n";
    }

    file.close();
}

// Check Specific Item
void DepartmentStore::checkItem() {
    system("cls");
    system("Color 0A");
    fstream file;
    int itemId, searchId, itemCount;
    string itemName, companyName;
    bool found = false;

    cout << "Check Specific Item:\n";
    cout << "-----------------------------------------------\n";
    cout << "Enter Item ID: ";
    cin >> searchId;

    file.open("items.txt", ios::in);
    if (!file) {
        cout << "Error: Unable to open file.\n";
        return;
    }

    while (file >> itemId >> itemName >> companyName >> itemCount) {
        if (itemId == searchId) {
            cout << "Item Found:\n";
            cout << "ID: " << itemId << "\n";
            cout << "Name: " << itemName << "\n";
            cout << "Company: " << companyName << "\n";
            cout << "Quantity: " << itemCount << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Item with ID " << searchId << " not found.\n";
    }

    file.close();
}

// Update Item Details
void DepartmentStore::updateItem() {
    system("cls");
    system("Color 0A");
    fstream file, tempFile;
    int itemId, searchId, itemCount, newCount;
    string itemName, companyName, newName, newCompany;
    bool found = false;

    cout << "Update Item Details:\n";
    cout << "-----------------------------------------------\n";
    cout << "Enter Item ID: ";
    cin >> searchId;

    file.open("items.txt", ios::in);
    tempFile.open("temp.txt", ios::out);
    if (!file || !tempFile) {
        cout << "Error: Unable to open file.\n";
        return;
    }

    while (file >> itemId >> itemName >> companyName >> itemCount) {
        if (itemId == searchId) {
            cout << "Enter New Item Name: ";
            cin >> newName;
            cout << "Enter New Company Name: ";
            cin >> newCompany;
            cout << "Enter New Quantity: ";
            cin >> newCount;

            tempFile << itemId << " " << newName << " " << newCompany << " " << newCount << "\n";
            found = true;
        } else {
            tempFile << itemId << " " << itemName << " " << companyName << " " << itemCount << "\n";
        }
    }

    if (!found) {
        cout << "Item with ID " << searchId << " not found.\n";
    } else {
        cout << "Item updated successfully.\n";
    }

    file.close();
    tempFile.close();

    remove("items.txt");
    rename("temp.txt", "items.txt");
}

// Delete Item
void DepartmentStore::deleteItem() {
    system("cls");
    system("Color 0A");
    fstream file, tempFile;
    int itemId, searchId, itemCount;
    string itemName, companyName;
    bool found = false;

    cout << "Delete Item:\n";
    cout << "-----------------------------------------------\n";
    cout << "Enter Item ID: ";
    cin >> searchId;

    file.open("items.txt", ios::in);
    tempFile.open("temp.txt", ios::out);
    if (!file || !tempFile) {
        cout << "Error: Unable to open file.\n";
        return;
    }

    while (file >> itemId >> itemName >> companyName >> itemCount) {
        if (itemId == searchId) {
            found = true;
        } else {
            tempFile << itemId << " " << itemName << " " << companyName << " " << itemCount << "\n";
        }
    }

    if (!found) {
        cout << "Item with ID " << searchId << " not found.\n";
    } else {
        cout << "Item deleted successfully.\n";
    }

    file.close();
    tempFile.close();

    remove("items.txt");
    rename("temp.txt", "items.txt");
}

// Main Function
int main() {
    DepartmentStore store;
    int choice;

    while (true) {
        store.showMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                store.addItem();
                break;
            case 2:
                store.displayItems();
                break;
            case 3:
                store.checkItem();
                break;
            case 4:
                store.updateItem();
                break;
            case 5:
                store.deleteItem();
                break;
            case 6:
                cout << "Exiting program. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
        system("pause");
    }
}