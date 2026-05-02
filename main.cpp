#include "Product.h"
#include "OrderSystem.h"
#include <iostream>

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
    cout << "\n========== SMART STORE FULL SYSTEM ==========\n" << endl;
    Product* products[4];

    products[0] = new Book(101, "Clean Code", 45.99, 10, "Robert Martin", 464);
    products[1] = new Electronic(102, "iPhone 15", 999.99, 5, "Apple", 12);
    products[2] = new OfficeSupply(103, "Stapler", 12.50, 50, "Office", "Metal");
    products[3] = new Book(104, "Design Patterns", 55.99, 7, "Erich Gamma", 395);

    cout << "\n--- All Products ---" << endl;
    for (int i = 0; i < 4; i++) {
        cout << *products[i] << endl;
        products[i]->display();
        cout << "------------------------" << endl;
    }

    // Operator overloading
    cout << "\n--- Adding 5 copies to 'Clean Code' ---" << endl;
    *products[0] + 5;
    cout << "After adding: " << *products[0] << endl;

    // Comparison
    cout << "\n--- Comparing Prices ---" << endl;
    comparePrice(*products[1], *products[3]);

    cout << "\nTotal products: " << Product::getTotalProducts() << endl;

    cout << "\n========== PART 2: ORDER SYSTEM ==========\n";

    // Customers
    Customer* c1 = new Customer("Ali");
    Customer* c2 = new PremiumCustomer("Ahmed", 0.1);

    // Payments
    Payment* pay1 = new CashPayment();
    Payment* pay2 = new CardPayment("1234567891234567");

    // Orders
    Order order1(c1, pay1);           // Pickup
    Order order2(c2, pay2, 20);       // Delivery

    try {
        // Add items
        order1.addItem(products[0], 2);
        order1.addItem(products[2], 5);

        order2.addItem(products[1], 1);
        order2.addItem(products[3], 2);

        // Print invoices
        order1.printInvoice();
        order2.printInvoice();

    }
    catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}