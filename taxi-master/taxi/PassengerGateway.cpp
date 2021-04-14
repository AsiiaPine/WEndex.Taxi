//
// Created by asiia on 01.04.2021.
//

#include <iostream>
#include "PassengerGateway.h"
#include "Repository.h"
//
//std::vector<Passenger*> PassengerGateway::AllPassengers;
//PassengerGateway::PassengerGateway(Passenger *passenger) : passenger(passenger), currentOrder(NULL){}
//
//PassengerGateway* PassengerGateway::SignUp(string UserName, string password, string email) {
//    if(password.size()<8){
//        cout<<"Length of password is less than 8 symbols"<<endl;
//        return nullptr;
//    }
//    auto passenger=new Passenger(UserName,password,email);
//    auto gate=new PassengerGateway(passenger);
//    AllPassengers.push_back(passenger);
//}
//void LogIn(string UserName, string password){
//    for(Passenger* passenger: PassengerGateway::AllPassengers){
//        if((passenger->name==UserName)&(passenger->password==password)){
//            std::cout<<"Welcome!"<<passenger->name<<endl;
//            PassengerGateway* gateway= new PassengerGateway(passenger);
//            return;
//        }
//    }
//    cout<<"Wrong user name or password"<<endl;
//}
//
//void PassengerGateway::LogOut() {
//    cout<<"Good bye"<<endl;
//    delete this;
//}
//
//void PassengerGateway::SeeOrderHistory() {
//    for(int i;i<PassengerGateway::orderRepository->amountOfOrders;i++){
//        Order order=PassengerGateway::orderRepository->GetOrder(i);
//        if(order.Passenger==this->passenger) PrintTheOrder(order);
//    }
//}
//
//
//
//
//
////template<typename coordinates>>
//
//void PassengerGateway::OrderTheRide(CarType type, Address address,Address startAddress, PaymentMethod paymentMethod) {
//    auto order=new Order(this->passenger, address,startAddress, )
//    PassengerGateway::orderRepository->Create()
//}
//
//void PassengerGateway::UpdateAddr(Address adr) {
//    this->currentOrder->address=adr;
//}
//
//void PassengerGateway::SeePayMethod() {
//    cout<<PrintPaymentMethod(this->passenger->methods);
//}
//
//void PassengerGateway::SeePayMethod(PaymentMethod newMethod) {
//    this->passenger->methods=newMethod;
//}
