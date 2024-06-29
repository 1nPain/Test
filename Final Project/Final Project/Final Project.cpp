#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits> // for std::numeric_limits

using namespace std;

class Product {
protected:
    string product_code; // atau disebut ID
    string product_name;
public:
    Product(string code, string name) : product_code(code), product_name(name) {}

    string getCode() const { return product_code; }
    string getName() const { return product_name; }
    void setName(const string& name) { product_name = name; }

    virtual void display() const = 0; // pure virtual function for display

    virtual ~Product() {}
};

//Product
class Laptop : public Product {
protected:
    string processor;
    int ram; // in GB
public:
    Laptop(string code, string name, string proc, int ramSize)
        : Product(code, name), processor(proc), ram(ramSize) {}

    void display() const override {
        cout << "Laptop - ID: " << product_code << ", Name: " << product_name
            << ", Processor: " << processor << ", RAM: " << ram << " GB" << endl;
    }
};
class Phone : public Product {
protected:
    string os;
    int battery; // in mAh
public:
    Phone(string code, string name, string operatingSystem, int batterySize)
        : Product(code, name), os(operatingSystem), battery(batterySize) {}

    void display() const override {
        cout << "Phone - ID: " << product_code << ", Name: " << product_name
            << ", OS: " << os << endl;
    }
};
class Computer : public Product {
protected:
    string gpu;
    int ram; // in GB
    int storage; // in GB
public:
    Computer(string code, string name, string graphics, int ramSize, int storageSize)
        : Product(code, name), gpu(graphics), ram(ramSize), storage(storageSize) {}

    void display() const override {
        cout << "Computer - ID: " << product_code << ", Name: " << product_name
            << ", GPU: " << gpu << ", RAM: " << ram << " GB, Storage: " << storage << " GB" << endl;
    }
};
class Console : public Product {
protected:
    int storage; // in GB
public:
    Console(string code, string name, int storageSize)
        : Product(code, name), storage(storageSize) {}

    void display() const override {
        cout << "Console - ID: " << product_code << ", Name: " << product_name
            << ", Storage: " << storage << " GB" << endl;
    }
};

// Menu 
int getValidatedIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input. Please enter a number." << endl;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard any remaining input
            return value;
        }
    }
}

void addProduct(vector<Product*>& container) {
    int type;
    cout << "Select product type (1: Laptop, 2: Phone, 3: Computer, 4: Console): ";
    cin >> type;

    string code, name;
    cout << "Enter product code: ";
    cin >> code;
    cout << "Enter product name: ";
    cin >> name;

    for (const auto& product : container) {
        if (product->getCode() == code) {
            cout << "Error: Product code already exists." << endl;
            return;
        }
    }

    if (type == 1) {
        string processor;
        int ram;
        cout << "Enter processor: ";
        cin >> processor;
        ram = getValidatedIntInput("Enter RAM size (in GB): ");
        container.push_back(new Laptop(code, name, processor, ram));
    }
    else if (type == 2) {
        string os;
        int battery;
        cout << "Enter operating system: ";
        cin >> os;
        battery = getValidatedIntInput("Enter battery capacity (in mAh): ");
        container.push_back(new Phone(code, name, os, battery));
    }
    else if (type == 3) {
        string gpu;
        int ram, storage;
        cout << "Enter GPU: ";
        cin >> gpu;
        ram = getValidatedIntInput("Enter RAM size (in GB): ");
        storage = getValidatedIntInput("Enter storage size (in GB): ");
        container.push_back(new Computer(code, name, gpu, ram, storage));
    }
    else if (type == 4) {
        int storage;
        storage = getValidatedIntInput("Enter storage size (in GB): ");
        container.push_back(new Console(code, name, storage));
    }
    else {
        cout << "Invalid product type." << endl;
    }
}

void editProduct(vector<Product*>& container) {
    string code;
    cout << "Enter product code to edit: ";
    cin >> code;

    for (auto& product : container) {
        if (product->getCode() == code) {
            string name;
            cout << "Enter new product name: ";
            cin >> name;
            product->setName(name);
            cout << "Product updated successfully." << endl;
            return;
        }
    }

    cout << "Product not found." << endl;
}

void displayAllProducts(const vector<Product*>& container) {
    for (const auto& product : container) {
        product->display();
    }
}

void displayProductByID(const vector<Product*>& container, const string& code) {
    for (const auto& product : container) {
        if (product->getCode() == code) {
            product->display();
            return;
        }
    }

    cout << "Product not found." << endl;
}

void deleteAllProducts(vector<Product*>& container) {
    for (auto& product : container) {
        delete product;
    }
    container.clear();
    cout << "All products deleted successfully." << endl;
}

void deleteProductByID(vector<Product*>& container, const string& code) {
    auto it = remove_if(container.begin(), container.end(),
        [&code](Product* product) { return product->getCode() == code; });

    if (it != container.end()) {
        for (auto i = it; i != container.end(); ++i) {
            delete* i;
        }
        container.erase(it, container.end());
        cout << "Product deleted successfully." << endl;
    }
    else {
        cout << "Product not found." << endl;
    }
}

// Clear Screen untuk tidak clutter
void clearScreen() {
#if defined(_WIN32)
    system("cls");
#elif defined(__unix__) || defined(__APPLE__) && defined(__MACH__)
    system("clear");
#endif
}

// Main Scn
int main() {
    vector<Product*> container;

    bool isRunning = true;
    int choice;

    while (isRunning) {
        cout << "1. Add Product" << endl;
        cout << "2. Edit Product" << endl;
        cout << "3. Display All Products" << endl;
        cout << "4. Display Product By ID" << endl;
        cout << "5. Delete All Products" << endl;
        cout << "6. Delete Product By ID" << endl;
        cout << "0. Exit Program" << endl;

        cout << "Input Choice: ";
        cin >> choice;

        clearScreen();

        if (choice == 1) {
            addProduct(container);
        }
        else if (choice == 2) {
            editProduct(container);
        }
        else if (choice == 3) {
            displayAllProducts(container);
        }
        else if (choice == 4) {
            string code;
            cout << "Enter product code: ";
            cin >> code;
            displayProductByID(container, code);
        }
        else if (choice == 5) {
            deleteAllProducts(container);
        }
        else if (choice == 6) {
            string code;
            cout << "Enter product code: ";
            cin >> code;
            deleteProductByID(container, code);
        }
        else if (choice == 0) {
            isRunning = false;
        }
        else {
            cout << "Invalid choice." << endl;
        }

        if (isRunning) {
            cout << "\nPress Enter to return to the main menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer
            cin.get(); // wait for Enter key
            clearScreen();
        }
    }

    deleteAllProducts(container); // Clean up any remaining products before exiting

    return 0;
}
