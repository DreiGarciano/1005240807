#include <iostream>
#include <string>
using namespace std;

// --- Menu Data ---------------------------------------------------
const int MENU_SIZE = 9;
const int MAX_ORDER = 50;

string menuNames[MENU_SIZE] = {
    "Burger",       "Pizza",        "Pasta",
    "Fried Chicken","Fish & Chips", "Caesar Salad",
    "Softdrink",    "Juice",        "Water"
};

double menuPrices[MENU_SIZE] = {
    120.00, 180.00, 150.00,
    130.00, 140.00,  90.00,
     40.00,  50.00,  25.00
};

string menuCategory[MENU_SIZE] = {
    "Main", "Main", "Main",
    "Main", "Main", "Main",
    "Drinks", "Drinks", "Drinks"
};

// --- Order Storage -----------------------------------------------
int    orderedItems[MAX_ORDER];
int    orderedQty[MAX_ORDER];
int    orderCount = 0;
string customerName = "";
string orderType    = "";

// --- Display Full Menu -------------------------------------------
void showMenu() {
    cout << "\n  ------------------------------------------\n";
    cout << "   MENU\n";
    cout << "  ------------------------------------------\n";

    // for loop: print all menu items
    for (int i = 0; i < MENU_SIZE; i++) {
        cout << "  [" << (i + 1) << "] "
             << menuNames[i]
             << " (" << menuCategory[i] << ")"
             << "  -  PHP " << menuPrices[i] << "\n";
    }
    cout << "  ------------------------------------------\n";
}

// --- Add Item to Order -------------------------------------------
void addToOrder() {
    showMenu();

    int itemChoice, qty;
    cout << "\n  Enter item number to order: ";
    cin >> itemChoice;

    // if-else: validate item selection
    if (itemChoice < 1 || itemChoice > MENU_SIZE) {
        cout << "\n  [!] Invalid item number.\n";
        return;
    } else {
        cout << "  Enter quantity: ";
        cin >> qty;

        if (qty <= 0) {
            cout << "\n  [!] Quantity must be at least 1.\n";
            return;
        } else {
            // Nested if-else: check if item already in order
            bool alreadyOrdered = false;
            int existingIndex = -1;

            for (int i = 0; i < orderCount; i++) {
                if (orderedItems[i] == itemChoice - 1) {
                    alreadyOrdered = true;
                    existingIndex = i;
                }
            }

            if (alreadyOrdered) {
                orderedQty[existingIndex] += qty;
                cout << "\n  [?] Added " << qty << " more " << menuNames[itemChoice - 1]
                     << ". Total qty: " << orderedQty[existingIndex] << "\n";
            } else {
                orderedItems[orderCount] = itemChoice - 1;
                orderedQty[orderCount]   = qty;
                orderCount++;
                cout << "\n  [?] " << qty << "x " << menuNames[itemChoice - 1] << " added to order.\n";
            }
        }
    }
}

// --- View Current Order ------------------------------------------
void viewOrder() {
    if (orderCount == 0) {
        cout << "\n  Your order is empty.\n";
        return;
    }

    cout << "\n  ------------------------------------------\n";
    cout << "   Order for: " << customerName << "  [" << orderType << "]\n";
    cout << "  ------------------------------------------\n";

    double subtotal = 0;

    for (int i = 0; i < orderCount; i++) {
        int    idx   = orderedItems[i];
        int    qty   = orderedQty[i];
        double price = menuPrices[idx] * qty;
        subtotal    += price;

        cout << "  " << menuNames[idx]
             << " x" << qty
             << "  =  PHP " << price << "\n";
    }

    // Nested if-else: compute discount based on order type
    double discount    = 0;
    double serviceCharge = 0;

    if (orderType == "Dine-In") {
        serviceCharge = subtotal * 0.10;
        cout << "\n  Subtotal      : PHP " << subtotal << "\n";
        cout << "  Service Charge: PHP " << serviceCharge << " (10%)\n";
    } else if (orderType == "Takeout") {
        if (subtotal >= 500) {
            discount = 20.00;
            cout << "\n  Subtotal      : PHP " << subtotal << "\n";
            cout << "  Discount      : -PHP " << discount << " (promo >= 500)\n";
        } else {
            cout << "\n  Subtotal      : PHP " << subtotal << "\n";
        }
    } else if (orderType == "Delivery") {
        double deliveryFee = 50.00;
        cout << "\n  Subtotal      : PHP " << subtotal << "\n";
        cout << "  Delivery Fee  : PHP " << deliveryFee << "\n";
        subtotal += deliveryFee;
    }

    double total = subtotal + serviceCharge - discount;
    cout << "  ------------------------------------------\n";
    cout << "  TOTAL         : PHP " << total << "\n";
    cout << "  ------------------------------------------\n";
}

// --- Remove Item from Order --------------------------------------
void removeItem() {
    if (orderCount == 0) {
        cout << "\n  No items to remove.\n";
        return;
    }

    viewOrder();
    cout << "\n  Enter order line # to remove (1-" << orderCount << "): ";
    int num;
    cin >> num;

    if (num < 1 || num > orderCount) {
        cout << "\n  [!] Invalid selection.\n";
    } else {
        cout << "  [?] Removed: " << menuNames[orderedItems[num - 1]] << "\n";
        // Shift remaining items using for loop
        for (int i = num - 1; i < orderCount - 1; i++) {
            orderedItems[i] = orderedItems[i + 1];
            orderedQty[i]   = orderedQty[i + 1];
        }
        orderCount--;
    }
}

// --- Checkout ----------------------------------------------------
void checkout() {
    if (orderCount == 0) {
        cout << "\n  [!] Cannot checkout — order is empty.\n";
        return;
    }

    viewOrder();

    double amountPaid;
    cout << "\n  Enter amount paid: PHP ";
    cin >> amountPaid;

    // Compute total again for change calculation
    double subtotal = 0;
    for (int i = 0; i < orderCount; i++) {
        subtotal += menuPrices[orderedItems[i]] * orderedQty[i];
    }

    double serviceCharge = 0;
    double discount      = 0;
    double deliveryFee   = 0;

    if (orderType == "Dine-In") {
        serviceCharge = subtotal * 0.10;
    } else if (orderType == "Takeout") {
        if (subtotal >= 500) {
            discount = 20.00;
        }
    } else if (orderType == "Delivery") {
        deliveryFee = 50.00;
    }

    double total  = subtotal + serviceCharge + deliveryFee - discount;
    double change = amountPaid - total;

    if (change < 0) {
        cout << "\n  [!] Insufficient payment. Need PHP " << (total - amountPaid) << " more.\n";
    } else {
        cout << "\n  [?] Payment accepted!\n";
        cout << "  Change: PHP " << change << "\n";
        cout << "\n  Thank you, " << customerName << "! Enjoy your meal!\n";

        // Reset order
        orderCount   = 0;
        customerName = "";
        orderType    = "";
    }
}

// --- Set Customer Info -------------------------------------------
void setCustomerInfo() {
    cout << "\n  Enter customer name: ";
    cin.ignore();
    getline(cin, customerName);

    cout << "\n  Order Type:\n";
    cout << "  [1] Dine-In\n";
    cout << "  [2] Takeout\n";
    cout << "  [3] Delivery\n";
    cout << "  Choice: ";
    int t;
    cin >> t;

    // switch-case: set order type
    switch (t) {
        case 1:
            orderType = "Dine-In";
            break;
        case 2:
            orderType = "Takeout";
            break;
        case 3:
            orderType = "Delivery";
            break;
        default:
            orderType = "Dine-In";
            cout << "  [i] Defaulting to Dine-In.\n";
    }

    cout << "\n  [?] Welcome, " << customerName << "! Order type: " << orderType << "\n";
}

// --- Main --------------------------------------------------------
int main() {
    int choice;
    bool running = true;

    cout << "\n  +--------------------------------------+\n";
    cout << "  ¦    Restaurant Ordering System        ¦\n";
    cout << "  +--------------------------------------+\n";

    // while loop: keep system running
    while (running) {
        cout << "\n  +--------------------------------------+\n";
        cout << "  ¦  MAIN MENU                           ¦\n";
        cout << "  ¦  [1] Set Customer & Order Type       ¦\n";
        cout << "  ¦  [2] View Menu & Add Item            ¦\n";
        cout << "  ¦  [3] View Current Order              ¦\n";
        cout << "  ¦  [4] Remove Item from Order          ¦\n";
        cout << "  ¦  [5] Checkout                        ¦\n";
        cout << "  ¦  [6] Exit                            ¦\n";
        cout << "  +--------------------------------------+\n";
        cout << "  Choice: ";
        cin >> choice;

        // switch-case: route to correct function
        switch (choice) {
            case 1:
                setCustomerInfo();
                break;
            case 2:
                if (customerName == "") {
                    cout << "\n  [!] Please set customer info first (option 1).\n";
                } else {
                    addToOrder();
                }
                break;
            case 3:
                viewOrder();
                break;
            case 4:
                removeItem();
                break;
            case 5:
                checkout();
                break;
            case 6:
                running = false;
                cout << "\n  System closed. Goodbye!\n\n";
                break;
            default:
                cout << "\n  [!] Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
