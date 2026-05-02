#ifndef ORDER_SYSTEM_H
#define ORDER_SYSTEM_H

#include "Product.h"
#include <vector>
#include <stdexcept>


class Customer {
protected:
    string name;

public:
    Customer(string n) : name(n) {}
    virtual double getDiscount(double amount) const { return 0; }
    string getName() const { return name; }
};

class PremiumCustomer : public Customer {
    double discountRate;

public:
    PremiumCustomer(string n, double rate) : Customer(n), discountRate(rate) {}

    double getDiscount(double amount) const override {
        return amount * discountRate;
    }
};


class Payment {
public:
    virtual string getMethod() const = 0;
};

class CashPayment : public Payment {
public:
    string getMethod() const override {
        return "Cash";
    }
};

class CardPayment : public Payment {
    string cardNumber;

public:
    CardPayment(string num) : cardNumber(num) {
        if (cardNumber.length() != 16)
            throw invalid_argument("Invalid card number!");
    }

    string getMethod() const override {
        return "Card";
    }
};


class OrderItem {
    Product* product;
    int quantity;

public:
    OrderItem(Product* p, int q) : product(p), quantity(q) {
        if (q <= 0 || q > p->getQuantity())
            throw invalid_argument("Invalid quantity!");
    }

    double getTotal() const {
        return product->getPrice() * quantity;
    }

    void display() const {
        cout << product->getName() << " x" << quantity
            << " = $" << getTotal() << endl;
    }
};


class Order {
    Customer* customer;
    vector<OrderItem> items;
    Payment* payment;
    double deliveryFee;

public:
    Order(Customer* c, Payment* p, double fee = 0)
        : customer(c), payment(p), deliveryFee(fee) {
        if (fee < 0)
            throw invalid_argument("Negative delivery fee!");
    }

    void addItem(Product* p, int q) {
        items.emplace_back(p, q);
    }

    double getSubtotal() const {
        double total = 0;
        for (auto& item : items)
            total += item.getTotal();
        return total;
    }

    void printInvoice() {
        cout << "----- INVOICE -----\n";
        cout << "Customer: " << customer->getName();

        double subtotal = getSubtotal();
        double discount = customer->getDiscount(subtotal);
        double finalTotal = subtotal - discount + deliveryFee;

        cout << "\nItems:\n";
        for (auto& item : items)
            item.display();

        cout << "\nSubtotal: $" << subtotal << endl;
        cout << "Discount: $" << discount << endl;
        cout << "Delivery: $" << deliveryFee << endl;
        cout << "Final Total: $" << finalTotal << endl;
        cout << "Payment: " << payment->getMethod() << endl;
        cout << "---------------------\n";
        cout << endl;
    }
};

#endif