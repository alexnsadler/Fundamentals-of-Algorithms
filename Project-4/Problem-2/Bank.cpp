#include "Bank.hpp"
using namespace std;

// -------------------------- PriorityQueue --------------------------
PQueue::PQueue(int c) : QCapacity(c), count(0) {
    events = new Event[QCapacity];
}

bool PQueue::isEmpty() { return count == 0; }

bool PQueue::listInsert(Event ev) {
    bool canAdd = count < QCapacity;

    if (canAdd) {
        // while loop component of insertion sort
        int loc = count % QCapacity;
        while ((loc > 0) && ((events[loc - 1]).ADTime <= ev.ADTime)) {
            // keep arrival events before departure for equal event times
            if (((events[loc - 1]).ADTime == ev.ADTime) &&
                (ev.EventType == 'A')) {
                break;
            }
            events[loc] = events[loc - 1];
            loc--;
        }

        events[loc] = ev;  // insert new event into its correct place
        count++;
    }

    return canAdd;
}

bool PQueue::listDelete() {
    bool canRemove = !isEmpty();

    // if can remove item, remove it
    if (canRemove) {
        count--;
    }

    return canRemove;
}

Event PQueue::listPeek() {
    assert(!isEmpty());  // terminate program if the list is empty
    return events[count - 1];
}

Event PQueue::peekFront() { return listPeek(); }

void PQueue::printall() {
    for (int j = 0; j < count; j++) {
        cout << (events[j]).ADTime << " " << (events[j]).EventType << endl;
    }
}

bool PQueue::enqueue(Event ev) { return listInsert(ev); }

bool PQueue::dequeue() { return listDelete(); }

PQueue::~PQueue() { delete[] events; }

// -------------------------- ArrayQueue --------------------------
ArrayQueue::ArrayQueue(int c)
    : Qcapacity(c), front(0), back(Qcapacity - 1), count(0) {
    IDs = new int[Qcapacity];
}

bool ArrayQueue::isEmpty() { return count == 0; }

bool ArrayQueue::enqueue(const int newID) {
    bool canAdd = count < Qcapacity;

    // if there is room to add, add newID
    if (canAdd) {
        back = (back + 1) % Qcapacity;
        IDs[back] = newID;
        count++;
    }

    return canAdd;
}

bool ArrayQueue::dequeue() {
    bool canRemove = !isEmpty();

    // if can remove item, remove it
    if (canRemove) {
        front = (front + 1) % Qcapacity;
        count--;
    }

    return canRemove;
}

int ArrayQueue::peekFront() {
    assert(!isEmpty());  // terminate program if the list is empty

    return IDs[front];  // return item at front
}

int ArrayQueue::queueLength() { return count; }

ArrayQueue::~ArrayQueue() { delete[] IDs; }

// -------------------------- BankTellerService --------------------------
BankTellerService::BankTellerService(string infS, string otfS)
    : BusyTeller(0), CustomersNum(0) {
    Customers = new BankCustomer[eventsQCapacity];  

    inf.open(infS);
    if (inf.fail()) {
        cerr << "Error: Could not open input file\n";
        exit(1);
    }

    otf.open(otfS);
    if (otf.fail()) {
        cerr << "Error: Could not open output file\n";
        exit(1);
    }

    otf << "Number of tellers: " << numTellers << endl << endl;
}

void BankTellerService::readCustomersInfo() {
    Event eventTemp;
    BankCustomer customerTemp;
    int ArrivTime;
    int TransLen;

    // activate the exception handling of inf stream
    inf.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    while (CustomersNum <
           waitingQCapacity) {  // keep reading until reading maxints or
        // until a reading failure is caught.
        try {
            inf >> ArrivTime;
            inf >> TransLen;

        }
        // Check for reading failure due to end of file or due to reading a
        // non‐integer value from the file.
        catch (std::ifstream::failure e) {
            break;
        }

        // adding to event queue
        eventTemp.EventType = 'A';
        eventTemp.CustID = CustomersNum;
        eventTemp.ADTime = ArrivTime;
        eventsQ.enqueue(eventTemp);

        // adding to customers array
        customerTemp.ID = CustomersNum;
        customerTemp.ArrivalTime = ArrivTime;
        customerTemp.TransactionLength = TransLen;
        Customers[CustomersNum] = customerTemp;
        CustomersNum++;

    }
}

void BankTellerService::serveCustomers() {
    BankCustomer customerTemp;
    Event newEv;
    Event nextEv;

    // process all events
    while (!eventsQ.isEmpty()) {
        nextEv = eventsQ.peekFront();
        if (nextEv.EventType == 'A') {
            otf << "Processing an arrival event at time  <-- " << nextEv.ADTime
                 << endl;
            if (BusyTeller < numTellers) {
                // get customer at front of line and decrement CustomersNum
                Customers[nextEv.CustID].ServiceStartTime = nextEv.ADTime;

                // defining and saving out departure event to priority queue
                newEv.EventType = 'D';
                newEv.CustID = nextEv.CustID;
                newEv.ADTime = Customers[nextEv.CustID].ArrivalTime +
                               Customers[nextEv.CustID].TransactionLength;

                // enqueue new event and dequeue the arrival event
                eventsQ.enqueue(newEv);
                eventsQ.dequeue();

                BusyTeller++;  // teller now busy with customer
            } else {
                // if teller busy, add customer to waiting queue
                WaitingQ.enqueue(nextEv.CustID);
                if(WaitingQ.queueLength() > waitingQMax){
                    waitingQMax = WaitingQ.queueLength();
                }

                eventsQ.dequeue();
            }

        } else {
            otf << "Processing a departure event at time --> " << nextEv.ADTime
                 << endl;
            eventsQ.dequeue();

            if (!WaitingQ.isEmpty()) {
                // serve customer at front of waiting queue
                Customers[WaitingQ.peekFront()].ServiceStartTime =
                    nextEv.ADTime;
                customerTemp = Customers[WaitingQ.peekFront()];

                // defining and queueing new departure (since teller is free)
                newEv.EventType = 'D';
                newEv.CustID = WaitingQ.peekFront();
                newEv.ADTime = nextEv.ADTime + customerTemp.TransactionLength;
                eventsQ.enqueue(newEv);

                // dequeue waiting queue
                WaitingQ.dequeue();
            }

            else {
                BusyTeller--;
            }
        }
    }
}

void BankTellerService::getStatistics() {
    otf << endl;
    otf << "Final Statistics:\n";
    otf << "Total number of customers processed: " << CustomersNum << endl;
    

    // calculate statistics for output
    float waitingTime = 0;
    int maxWaitTime = 0;
    int waitingTemp;
    for (int i = 0; i < CustomersNum; i++) {
        waitingTemp =
            (Customers[i].ServiceStartTime - Customers[i].ArrivalTime);
        if (waitingTemp > maxWaitTime) {
            maxWaitTime = waitingTemp;
        }

        waitingTime += waitingTemp;
    }

    otf << "Average waiting time = " << waitingTime / CustomersNum;
    otf << "\tMaximum waiting time = " << maxWaitTime << endl;
    otf << "Maximum waiting queue length = " << waitingQMax;
}

BankTellerService::~BankTellerService() {
    delete[] Customers;
    inf.close();  // Close input the file at the end of your program
    otf.close();  // Close output the file at the end of your program
}
