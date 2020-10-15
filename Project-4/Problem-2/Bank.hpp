#pragma once
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

const int waitingQCapacity = 50;
const int eventsQCapacity = 50;
const int numTellers = 1;

class BankCustomer {
   public:
    int ID;
    int ArrivalTime;
    int ServiceStartTime;
    int TransactionLength;
};

class Event {
   public:
    char EventType;  //'A' for arrival and 'D' for departure
    int CustID;      // ID of the customer who created the event
    int ADTime;      // Arrival or Departure time
};

class PQueue {
   private:
    int QCapacity;  // Max size of the queue
    Event* events;  // Pointer to the array that holds arrival & departure
                    // events
    int count;      // Number of events currently in the queue
    bool listInsert(Event ev);  // insert a new event to a sorted list
    bool listDelete();          // Delete the event at the end of the list
    Event listPeek();           // Get the event at the end of the list

   public:
    PQueue(int c);  // c for the Qcapacity
    bool isEmpty();
    void printall();
    bool enqueue(Event ev);  // calls listInsert to insert a new event
    bool dequeue();     // calls listDelete to remove the queue’s front event
    Event peekFront();  // calls listPeek to return the queue’s front event
    ~PQueue();
};

class ArrayQueue {
   private:
    int Qcapacity;
    int* IDs;   // array of queue items (the customers' IDs)
    int front;  // index of front of queue
    int back;   // index of back of queue
    int count;  // number of items currently in the queue

   public:
    ArrayQueue(int c);
    bool isEmpty();
    bool enqueue(const int newID);
    bool dequeue();
    int peekFront();
    int queueLength();  // return current number of items in the queue
    ~ArrayQueue();
};

class BankTellerService {
   private:
    int BusyTeller;   // indicates if the teller is currently busy or not
    int CustomersNum;  // total number of customers in the simulation
    ifstream inf;      // text file with arrival and transaction times
    ofstream otf;      // text tile with the trace messages and final statistics
    ArrayQueue WaitingQ = ArrayQueue(waitingQCapacity);
    PQueue eventsQ = PQueue(eventsQCapacity);
    BankCustomer* Customers;  // array of the customer objects in the simulation
    int waitingQMax = 0;      // max length of the waiting queue

   public:
    BankTellerService(string infS, string otfS);
    void readCustomersInfo();
    void serveCustomers();
    void getStatistics();
    ~BankTellerService();
};