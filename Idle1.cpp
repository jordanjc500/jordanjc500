#include <iostream>
#include <string>
#include <conio.h>
#include <chrono>
#include <windows.h>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <functional>
#include <algorithm>

using namespace std;

class Generator { //contains each building's info
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

		bool try_buy(long double& money, string& msg) {
			if (money >= cost) {
				owned++;
				money -= cost;
				cost *= 1.1;
				msg = name + " bought. You now have " + to_string(owned);
				return true;
			}
			msg = "Insufficient funds.";
			return false;
		}
};
 
class Upgrade {
	private:
		double cost;
		int affectedGenerator;
		double multiplier;
		bool owned;
	public:
		Upgrade(double c, int g, double m, bool o) {
			cost = c;
			affectedGenerator = g;
			multiplier = m;
			owned = o;
		}

		double get_price() {
			return cost;
		}
};

class Achievement {
	private:
		string name;
		int buildingIndex;
		int required;
		bool unlocked = false;
		//string description;
	public:	
		Achievement(string n, int index, int r) {
			name = n;
			buildingIndex = index;
			required = r;
		}

		bool check_unlock(int owned) {
			if (!unlocked && owned >= required) {
				unlocked = true;
				return true;
			}
			return false;
		}

		string get_name() {
			return name;
		}

		int get_index() {
			return buildingIndex;
		}

		bool get_unlocked() {
			return unlocked;
		}
};

/*class Statistic {

};*/ //TODO: add statistics including time played, total cash generated, cash spent, total # of generators, achievements unlocked, playtime

int main() {
	long double money = 0;
	cout << fixed << setprecision(2);

	vector<Generator> buildings;
	buildings.push_back(Generator("Lemon Stand", 10, 1, 0));
	buildings.push_back(Generator("Coffee Shop", 100, 7.5, 0));
	buildings.push_back(Generator("Factory", 600, 35, 0));
	vector<Achievement> A;
	A.push_back(Achievement("Humble Beginnings", 0, 1));
	A.push_back(Achievement("Gaining Traction", 0, 25));
	A.push_back(Achievement("Building Up Speed", 0, 50));
	vector<Upgrade> U;
	U.push_back(Upgrade(100, 0, 1.5, false));

	cout << "Welcome to IdleGame." << endl;
	cout << "You have: $" << long(money) << endl;

	//Statistic stats; 
	string message;

	auto setMessage = [&](const string& m) {
		message = m;
		//double messageTimer = 3.0; TODO: add timed notifications
		};

	auto buy = [&](int i) {
		string msg;
		buildings[i].try_buy(money, msg);
		setMessage(msg);
		};

	bool running = true;
	auto last = chrono::steady_clock::now();
	double sinceRender = 0;

	//controls
	unordered_map<char, function<void()>> commands;
	commands['a'] = [&] { money += 1; };
	commands['1'] = [&] { buy(0); };
	commands['2'] = [&] { buy(1); };
	commands['3'] = [&] { buy(2); };
	commands['q'] = [&] { running = false; };




	while (running) {

		auto now = chrono::steady_clock::now();
		double dt = chrono::duration<double>(now - last).count();
		last = now;
		//dt = min(dt, 0.25); 

		while (_kbhit()) {
			char c = _getch();
			auto it = commands.find(c);
			if (it != commands.end()) it->second();
		}

		double prodRate = 0;
		for (auto& b : buildings) {
			prodRate += (b.get_prod() * b.get_owned());
		}
		long double gained = prodRate * dt;
		money += gained;

		for (auto& a : A) {
			if (a.check_unlock(buildings[a.get_index()].get_owned()))
				message = "Achievement unlocked: " + a.get_name();
		}

		sinceRender += dt;
		if (sinceRender >= 0.1) {
			sinceRender = 0;
			system("cls");
			cout << "$" << money << "  (+" << prodRate << "/s)\n" << message << "\n";
		}

		Sleep(10);
	}
	
	if (running == false) {
		cout << "Thank you for playing!" << endl;
	}

	return 0; 
}