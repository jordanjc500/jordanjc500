#include <iostream>
#include <string>
#include <conio.h>
#include <chrono>
#include <windows.h>
#include <vector>
#include <iomanip>

using namespace std;

class Generator { //contains each buildings info
	private: 
		string name;
		double cost;
		double baseProduction;
		int owned;

	public:
		Generator(string n, double c, double b, int o) {
			name = n;
			cost = c;
			baseProduction = b;
			owned = o;
		}

		string get_name() {
			return name;
		}

		double get_price() {
			return cost;
		}

		double get_prod() {
			return baseProduction;
		}

		int get_owned() {
			return owned;
		}

		void try_buy(long double &money) { //most buildings' cost will scale by 1.1^n, where n is the number owned
			if (money >= this->cost) {
				this->owned++;
				money -= this->cost;
				this->cost *= 1.1;
				cout << this->name << " successfully bought. You now have " << this->owned << endl;
			} else {
				cout << "Insufficient funds." << endl;
			}
		}
};

class Upgrade {
	private:
		double cost;
		int AffectedGenerator;
		double multiplier;
		bool owned;
	public:
		Upgrade(double c, int g, double m, bool o) {
			cost = c;
			AffectedGenerator = g;
			multiplier = m;
			owned = o;
		}

		double get_price() {
			return cost;
		}
};

int main() {
	long double money = 0;
	double prodRate = 0;
	cout << fixed << setprecision(2);

	vector<Generator> buildings;
	buildings.push_back(Generator("Lemon Stand", 10, 1, 0));
	buildings.push_back(Generator("Coffee Shop", 100, 7.5, 0));
	buildings.push_back(Generator("Factory", 600, 35, 0));

	cout << "Welcome to IdleGame." << endl;
	cout << "You have: $" << long(money) << endl;
	while (true) {
		system("cls");
		prodRate = 0;
		for (auto& b : buildings) {
			prodRate += (b.get_prod() * b.get_owned());
		}
		money += (prodRate / 10);
		if (_kbhit()) {
			char input = _getch();
			if (input == 'a') money += 1;
			if (input == 'q') {
				cout << "Thank you for playing." << endl;
				break;
			}
			if (input == '1') buildings[0].try_buy(money);
			if (input == '2') buildings[1].try_buy(money);
			if (input == '3') buildings[2].try_buy(money);
		}
		/*char input = _kbhit();
		if (input == 'a') {
			money += 1;
		}
		if (input == 'q') {
			cout << "Thank you for playing." << endl;
			break;
		}
		if (input == '1') {
			buildings[0].try_buy(money);
		}
		if (input == '2') {
			buildings[1].try_buy(money);
		}*/
		Sleep(100);
		cout << "You now have $" << money << endl;
	}
	return 0; 
}