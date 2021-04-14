//
// Created by asiia on 01.04.2021.
//

#ifndef WENDEX_TAXI_PAYMENTMETHODS_H
#define WENDEX_TAXI_PAYMENTMETHODS_H

#include <iostream>
using namespace std;

enum PaymentMethod{
    Cash,
    WebMoney,
    Card
};
void PrintPaymentMethod(PaymentMethod method){
    switch (method) {
        case 0: cout<<"Cash";
        case 1: cout<<"WebMoney";
        case 2: cout<<"Card";
    }
}
#endif //WENDEX_TAXI_PAYMENTMETHODS_H
