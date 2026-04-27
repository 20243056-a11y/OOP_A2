#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
using namespace std;

class Product {
protected:
    int id;
    string name;
    double price;
    int quantity;
    static int totalProducts;

public:
    Product(int i, string n, double p, int q);
    virtual ~Product();

    virtual void display() const;

    // Getters
    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    // Operator overloading
    Product& operator+(int qty);
    bool operator==(const Product& other) const;
    friend ostream& operator<<(ostream& os, const Product& p);

    // Friend function
    friend void comparePrice(const Product& a, const Product& b);

    // Static function
    static int getTotalProducts() { return totalProducts; }
};

class Book : public Product {
    string author;
    int pages;

public:
    Book(int i, string n, double p, int q, string a, int pg);
    void display() const override;
};

class Electronic : public Product {
    string brand;
    int warranty;

public:
    Electronic(int i, string n, double p, int q, string b, int w);
    void display() const override;
};

class OfficeSupply : public Product {
    string category;
    string material;

public:
    OfficeSupply(int i, string n, double p, int q, string c, string m);
    void display() const override;
};

#endif#pragma once
