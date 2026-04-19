#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>

using namespace std;

int main()
{
    map<string, double> rates;
    rates["USD"] = 89.50;
    rates["EUR"] = 97.30;
    rates["GBP"] = 113.20;
    int choice;

    vector<string> history;

    while (true) {
        cout << "1. Convert to RUB" << endl;
        cout << "2. Show rates" << endl;
        cout << "3. Save history" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose:";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        if (choice == 1) {
            try {
                string currency;
                cout << "Currency (USD/EUR/GBP): ";
                cin >> currency;
                if (rates.find(currency) == rates.end()) {
                    throw runtime_error("Unknown currency: " + currency);
                }
                cout << "Amount: ";
                double amount;
                cin >> amount;
                if (amount <= 0) {
                    throw runtime_error("Amount must be positive!");
                }
                double result = amount * rates[currency];
                cout << amount << " " << currency << " = "
                    << result << " RUB" << endl;
                history.push_back(to_string(amount) + " " + currency
                    + " = " + to_string(result) + " RUB");
            }
            catch (exception& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
        else if (choice == 2) {
            for (auto& pair : rates) {
                cout << pair.first << " = "
                    << pair.second << " RUB" << endl;
            }
        }
        else if (choice == 3) {
            if (history.empty()) {
                cout << "No conversions yet" << endl;
            }
            else {
                ofstream fout("history.txt");
                for (int i = 0; i < history.size(); i++) {
                    fout << history[i] << endl;
                }
                fout.close();
                cout << "History saved!" << endl;
            }
        }
        else if (choice == 0) {
            cout << "Bye!" << endl;
            break;
        }
    }
    return 0;
}

