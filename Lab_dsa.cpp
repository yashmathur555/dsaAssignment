#include <bits/stdc++.h>
using namespace std;

struct Item {
    int itemID;
    string itemName;
    int quantity;
    float price;
};

class Inventory {
private:
    vector<Item> items;

public:
    void insertItem(int id, string name, int qty, float price) {
        Item newItem = {id, name, qty, price};
        items.push_back(newItem);
        cout << "Item inserted successfully\n";
    }

    void deleteItem(int id) {
        for (auto it = items.begin(); it != items.end(); it++) {
            if (it->itemID == id) {
                items.erase(it);
                cout << "Item deleted successfully\n";
                return;
            }
        }
        cout << "Item not found\n";
    }

    void searchItem(string key) {
        for (auto &it : items) {
            if (to_string(it.itemID) == key || it.itemName == key) {
                cout << "Found: " << it.itemID << " | " << it.itemName 
                     << " | Qty: " << it.quantity << " | Price: " << it.price << endl;
                return;
            }
        }
        cout << "Item not found\n";
    }

    void displayAll() {
        if (items.empty()) {
            cout << "Inventory is empty\n";
            return;
        }
        cout << "\n--- Inventory Items ---\n";
        for (auto &it : items) {
            cout << it.itemID << " | " << it.itemName 
                 << " | Qty: " << it.quantity << " | Price: " << it.price << endl;
        }
    }

    void managePriceQuantity() {
        if (items.empty()) {
            cout << "No items available\n";
            return;
        }
        vector<vector<float>> priceQty(2, vector<float>(items.size()));
        for (int i=0; i<items.size(); i++) {
            priceQty[0][i] = items[i].price;
            priceQty[1][i] = items[i].quantity;
        }

        cout << "\nRow-Major Order:\n";
        for (int i=0; i<2; i++) {
            for (int j=0; j<items.size(); j++) {
                cout << priceQty[i][j] << " ";
            }
            cout << endl;
        }

        cout << "\nColumn-Major Order:\n";
        for (int j=0; j<items.size(); j++) {
            for (int i=0; i<2; i++) {
                cout << priceQty[i][j] << " ";
            }
            cout << endl;
        }
    }

    void optimizeSparseStorage(int threshold) {
        if (items.empty()) {
            cout << "Inventory empty\n";
            return;
        }
        cout << "\n--- Sparse Representation (ID, Name, Qty, Price) ---\n";
        bool found = false;
        for (auto &it : items) {
            if (it.quantity <= threshold) {
                cout << it.itemID << " | " << it.itemName 
                     << " | " << it.quantity << " | " << it.price << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No items found with quantity <= " << threshold << endl;
        }
    }
};

int main() {
    Inventory inv;
    int choice;

    while (true) {
        cout << "\n====== Grocery Store Inventory System ======\n";
        cout << "1. Insert Item\n";
        cout << "2. Delete Item\n";
        cout << "3. Search Item (by ID or Name)\n";
        cout << "4. Display All Items\n";
        cout << "5. Manage Price & Quantity (Row/Column Order)\n";
        cout << "6. Optimize Sparse Storage (Low Stock)\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id, qty;
            string name;
            float price;
            cout << "Enter Item ID: "; cin >> id;
            cout << "Enter Item Name: "; cin >> name;
            cout << "Enter Quantity: "; cin >> qty;
            cout << "Enter Price: "; cin >> price;
            inv.insertItem(id, name, qty, price);
        }
        else if (choice == 2) {
            int id;
            cout << "Enter Item ID to delete: "; cin >> id;
            inv.deleteItem(id);
        }
        else if (choice == 3) {
            string key;
            cout << "Enter Item ID or Name to search: "; cin >> key;
            inv.searchItem(key);
        }
        else if (choice == 4) {
            inv.displayAll();
        }
        else if (choice == 5) {
            inv.managePriceQuantity();
        }
        else if (choice == 6) {
            int threshold;
            cout << "Enter threshold quantity for rarely restocked items: ";
            cin >> threshold;
            inv.optimizeSparseStorage(threshold);
        }
        else if (choice == 7) {
            cout << "Exiting...\n";
            break;
        }
        else {
            cout << "Invalid choice\n";
        }
    }
    return 0;
}
