#include "OrderSystem.h"

Product::Product(int i, string n, double p, int q) {
    if (p < 0 || q < 0) throw invalid_argument("Invalid product data");
    id = i; name = n; price = p; quantity = q;
}

void Product::reduceQuantity(int q) {
    if (q > quantity) throw runtime_error("Not enough stock");
    quantity -= q;
}


Customer::Customer(string n) { name = n; }

RegularCustomer::RegularCustomer(string n) : Customer(n) {}

double RegularCustomer::getDiscount(double total) {
    return 0;
}

PremiumCustomer::PremiumCustomer(string n, double rate)
    : Customer(n), discountRate(rate) {}

double PremiumCustomer::getDiscount(double total) {
    return total * discountRate;
}


void CashPayment::pay(double amount) {
    cout << "Paid " << amount << " using Cash\n";
}

CardPayment::CardPayment(string num) {
    if (num.length() != 16) throw invalid_argument("Invalid card number");
    cardNumber = num;
}

void CardPayment::pay(double amount) {
    cout << "Paid " << amount << " using Card\n";
}


OrderItem::OrderItem(Product* p, int q) {
    if (q <= 0) throw invalid_argument("Invalid quantity");
    product = p;
    quantity = q;
}

double OrderItem::getTotal() {
    return product->price * quantity;
}


Delivery::Delivery(bool d, double f) {
    if (f < 0) throw invalid_argument("Invalid delivery fee");
    isDelivery = d;
    fee = d ? f : 0;
}


Order::Order(Customer* c, Payment* p, Delivery d)
    : customer(c), payment(p), delivery(d) {}

void Order::addItem(Product* p, int q) {
    p->reduceQuantity(q);
    items.push_back(OrderItem(p, q));
}

double Order::getSubtotal() {
    double sum = 0;
    for (auto& item : items)
        sum += item.getTotal();
    return sum;
}

void Order::printInvoice() {
    double subtotal = getSubtotal();
    double discount = customer->getDiscount(subtotal);
    double total = subtotal - discount + delivery.fee;

    cout << "----- Invoice -----\n";
    cout << "Customer: " << customer->name << endl;

    for (auto& item : items) {
        cout << item.product->name << " x" << item.quantity
            << " = " << item.getTotal() << endl;
    }

    cout << "Subtotal: " << subtotal << endl;
    cout << "Discount: " << discount << endl;
    cout << "Delivery Fee: " << delivery.fee << endl;
    cout << "Final Total: " << total << endl;

    payment->pay(total);
    cout << "-------------------\n";
    cout << endl;
}