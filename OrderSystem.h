#ifndef ORDER_SYSTEM_H
#define ORDER_SYSTEM_H

#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

class Product {
public:
    int id;
    string name;
    double price;
    int quantity;

    Product(int i, string n, double p, int q);
    void reduceQuantity(int q);
};

class Customer {
public:
    string name;
    Customer(string n);
    virtual double getDiscount(double total) = 0;
};

class RegularCustomer : public Customer {
public:
    RegularCustomer(string n);
    double getDiscount(double total) override;
};

class PremiumCustomer : public Customer {
    double discountRate;
public:
    PremiumCustomer(string n, double rate);
    double getDiscount(double total) override;
};

class Payment {
public:
    virtual void pay(double amount) = 0;
};

class CashPayment : public Payment {
public:
    void pay(double amount) override;
};

class CardPayment : public Payment {
    string cardNumber;
public:
    CardPayment(string num);
    void pay(double amount) override;
};

class OrderItem {
public:
    Product* product;
    int quantity;

    OrderItem(Product* p, int q);
    double getTotal();
};

class Delivery {
public:
    double fee;
    bool isDelivery;

    Delivery(bool d, double f = 0);
};

class Order {
    vector<OrderItem> items;
    Customer* customer;
    Payment* payment;
    Delivery delivery;

public:
    Order(Customer* c, Payment* p, Delivery d);
    void addItem(Product* p, int q);
    double getSubtotal();
    void printInvoice();
};

#endif
