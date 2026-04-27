#include "Product.h"
#include <iostream>
#include <string>
using namespace std;


int Product::totalProducts = 0;

Product::Product(int i, string n, double p, int q)
    : id(i), name(n), price(p), quantity(q) {
    totalProducts++;
}

Product::~Product() {
    totalProducts--;
}

void Product::display() const {
    cout << "Product: " << name << " | Price: $" << price << " | Stock: " << quantity;
}

Product& Product::operator+(int qty) {
    quantity += qty;
    return *this;
}

bool Product::operator==(const Product& other) const {
    return (price == other.price);
}

ostream& operator<<(ostream& os, const Product& p) {
    os << "[ID:" << p.id << "] " << p.name << " - $" << p.price << " (x" << p.quantity << ")";
    return os;
}

void comparePrice(const Product& a, const Product& b) {
    cout << "\n--- Price Comparison ---" << endl;
    cout << a.name << " ($" << a.price << ") vs " << b.name << " ($" << b.price << ")" << endl;

    if (a.price > b.price)
        cout << a.name << " is more expensive!" << endl;
    else if (b.price > a.price)
        cout << b.name << " is more expensive!" << endl;
    else
        cout << "Both products have the same price!" << endl;
}


Book::Book(int i, string n, double p, int q, string a, int pg)
    : Product(i, n, p, q), author(a), pages(pg) {
}

void Book::display() const {
    Product::display();
    cout << " | Book by: " << author << " (" << pages << " pages)" << endl;
}


Electronic::Electronic(int i, string n, double p, int q, string b, int w)
    : Product(i, n, p, q), brand(b), warranty(w) {
}

void Electronic::display() const {
    Product::display();
    cout << " | Electronic - Brand: " << brand << " | Warranty: " << warranty << " months" << endl;
}


OfficeSupply::OfficeSupply(int i, string n, double p, int q, string c, string m)
    : Product(i, n, p, q), category(c), material(m) {
}

void OfficeSupply::display() const {
    Product::display();
    cout << " | Office Supply - Category: " << category << " | Material: " << material << endl;
}


int main() {
    cout << "\n========== SMART STORE - PRODUCT MANAGEMENT DEMO ==========\n" << endl;
    cout << "Team Member A: Product Module\n" << endl;

    // Create products using base class pointers (polymorphism)
    Product* products[4];

    products[0] = new Book(101, "Clean Code", 45.99, 10, "Robert Martin", 464);
    products[1] = new Electronic(102, "iPhone 15", 999.99, 5, "Apple", 12);
    products[2] = new OfficeSupply(103, "Stapler", 12.50, 50, "Office", "Metal");
    products[3] = new Book(104, "Design Patterns", 55.99, 7, "Erich Gamma", 395);

    // 1. Display all products (demonstrates overridden display() and operator<<)
    cout << "--- All Products ---" << endl;
    for (int i = 0; i < 4; i++) {
        cout << *products[i] << endl;      // Using overloaded <<
        products[i]->display();             // Using overridden display()
        cout << "------------------------" << endl;
    }

    // 2. Demonstrate operator+ (increase quantity)
    cout << "\n--- Adding 5 copies to 'Clean Code' ---" << endl;
    *products[0] + 5;
    cout << "After adding: " << *products[0] << endl;

    // 3. Demonstrate operator== (compare prices)
    cout << "\n--- Comparing Prices with operator== ---" << endl;
    if (*products[0] == *products[2])
        cout << "Clean Code and Stapler have the same price" << endl;
    else
        cout << "Clean Code and Stapler have different prices" << endl;

    // 4. Demonstrate friend function
    comparePrice(*products[1], *products[3]);

    // 5. Demonstrate static function
    cout << "\n--- Total Products Created (Static Function) ---" << endl;
    cout << "Total products in system: " << Product::getTotalProducts() << endl;

    // Cleanup
    cout << "\n--- Cleaning up ---" << endl;
    for (int i = 0; i < 4; i++) {
        delete products[i];
    }

    cout << "\nTotal products after cleanup: " << Product::getTotalProducts() << endl;
    cout << "\n========== DEMO COMPLETE ==========\n" << endl;

    return 0;
}