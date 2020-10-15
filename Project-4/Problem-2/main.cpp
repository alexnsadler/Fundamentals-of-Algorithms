// Alex Sadler - 001792279
#include "Bank.hpp"
using namespace std;

int main() {

    BankTellerService bts("ints.txt", "output.txt");
    bts.readCustomersInfo();
    bts.serveCustomers();
    bts.getStatistics();

    return 0;
}