#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include<fstream>
#include<sstream>
#include<windows.h>
#include <cstdlib>

using namespace std;


void setColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


class IngredientWthKg {
	string name;
	double mass;
	double price;
public:
	IngredientWthKg(string& name, double mass) {
		setName(name);
		setMass(mass);
	}

	void setName(string& name) {
		if (name.length() < 4)
		{
			throw string("Name of Ingredient cannot be less than 4 character");
		}
		this->name = name;

	}

	void setPrice(double price) {
	
		if (price<0)
		{
			throw string("Price Cannot be negative!!!");
		}

		this->price = price;
	}
	double getPrice()const noexcept {

		return price;

	}

	void setMass(double mass) {
	
		if (mass<0)
		{
			throw string("Mass cannot be negative...");
		}
		this->mass = mass;
	}

	double getMass() const noexcept {
	
		return mass;
	
	}
	
	string getName()const noexcept {
	
		return name;
	
	}

	void Show() {

		cout << this->getName() << " - " << this->getMass() << " kg,  $" << this->getPrice() << endl;

	}

	~IngredientWthKg() {}
};

class IngredientWthPcs{
	string name;
	int count;
	double price;
public:
	IngredientWthPcs(string& name, int count){
		setName(name);
		setCount(count);

	}


	void setPrice(double price) {

		if (price < 0)
		{
			throw string("Price Cannot be negative!!!");
		}

		this->price = price;
	}

	double getPrice()const noexcept {

		return price;

	}

	void setName(string& name) {
		if (name.length() < 4)
		{
			throw string("Name of Ingredient cannot be less than 4 character");
		}
		this->name = name;

	}

	void setCount(int count) {

		if (count < 0)
		{
			throw string("The number cannot be negative...");
		}
		this->count = count;
	}

	int getCount()const noexcept {
	
		return count;
	}

	string getName()const noexcept {

		return name;

	}

	void Show() {

		cout << this->getName() << " - " << this->getCount() << " pieces,  $" << this->getPrice() << endl;

	}

	~IngredientWthPcs() {}
};

class Meal {

	string name;
	double price;
	string type;
	vector<IngredientWthKg> neededIngsKG;
	vector<IngredientWthPcs> neededIngsPCS;

	int howMany;

public:
	Meal(string name, double price,string type) {

		setName(name);
		setPrice(price);
		setType(type);
	}

	void setHowMany(int howMany) {
		if (howMany<0)
		{
			throw string("Amount cannot be negative");
		}
		this->howMany = howMany;
	}

	void setName(string& name) {
		if (name.length() < 3)
		{
			throw string("Name of meal cannot be less than 3 characters!");
		}
		this->name = name;
	}

	void setPrice(double price) {

		if (price < 0)
		{
			throw string("Price cannot be negative");
		}
		this->price = price;
	}

	void setType(string type) {
		if (type == "hot" || type == "cold")
		{
			this->type = type;
			return;
		}
		throw string("Type of meal can be only \"hot\" or \"cold\"");

	}

	string getName()const noexcept {

		return name;

	}

	double getPrice()const noexcept {
		return price;
	}

	string getType()const noexcept {

		return type;
	}

	int getHowMany()const noexcept{
	
		return howMany;

	}

	void addIngKg(IngredientWthKg ing) {
	
		this->neededIngsKG.push_back(ing);

	}

	void addIngPcs(IngredientWthPcs ing) {

		this->neededIngsPCS.push_back(ing);

	}

	void Show() {

		cout<< this->getName() << " - $" << this->getPrice()<<endl;
		

	}

	void ShowInfo() {

		for (size_t i = 0; i < neededIngsKG.size(); i++)
		{
			cout << endl << neededIngsKG[i].getMass() << " kg " << neededIngsKG[i].getName();
		}

		for (size_t i = 0; i < neededIngsPCS.size(); i++)
		{
			cout << endl << neededIngsPCS[i].getCount() << " kg " << neededIngsPCS[i].getName();
		}

	}

	size_t getSizeOfIngKg() { return neededIngsKG.size(); }

	size_t getSizeOfIngPcs() { return neededIngsPCS.size(); }

	string getNameofIngKG(int index) {
	
		return neededIngsKG[index].getName();
	
	}

	double getKgofIngKG(int index) {
	
		return neededIngsKG[index].getMass();
	
	}

	string getNameofIngPCS(int index) {

		return neededIngsPCS[index].getName();

	}

	int getCountofIngPCS(int index) {

		return neededIngsPCS[index].getCount();
		 
	}

};

class Stock {

	vector<IngredientWthKg> ingKG;
	vector<IngredientWthPcs> ingPCS;

public:
	
	void Show() {

		cout << "O------------------   STOCK   ------------------O"<<endl<<endl;

		cout << "O------------  IINGREDIENTS (KG)  ------------O" << endl<<endl;
		for (size_t i = 0; i < ingKG.size(); i++)
		{
			ingKG[i].Show();
		}
		cout << "O------------  INGREDIENTS (PCS)  ------------O" << endl<<endl;
		for (size_t i = 0; i < ingPCS.size(); i++)
		{
			ingPCS[i].Show();
		}

	
	}

	void ShowIngKg(int index) {
		ingKG[index].Show();
	}

	void ShowIngPcs(int index) {
		ingPCS[index].Show();
	}

	void addIngredientKG(IngredientWthKg ing) {
	
		ingKG.push_back(ing);

	}

	void addIngredientPCS(IngredientWthPcs ing) {

		ingPCS.push_back(ing);

	}

	void saveDatatoStock() {
		ofstream fs("Stock(Ingredients).txt");
		if (!fs.is_open()) throw string("File couldn't open...");

		for (auto& m : ingKG)
			fs << "Kg#" << m.getName() << "#" << m.getMass() << "#" << m.getPrice() << "\n";
		for (auto& m : ingPCS)
			fs << "Pcs#" << m.getName() << "#" << m.getCount() << "#" << m.getPrice() << "\n";

		fs.close();
	
	}

	void loadDatafromStock() {
		ifstream fs("Stock(Ingredients).txt");
		if (!fs.is_open()) throw string("File not found...");
		if (fs.peek() == ifstream::traits_type::eof()) throw string("File empty...");

		string row;
		while (getline(fs, row)) {
			vector<string> parts;
			string temp;
			for (char ch : row) {
				if (ch == '#') {
					parts.push_back(temp);
					temp.clear();
				}
				else temp += ch;
			}
			parts.push_back(temp);

			if (parts.size() != 4) continue;

			string korp = parts[0];
			string name = parts[1];
			string masscount = parts[2];
			double price = stod(parts[3]);

			if (korp == "Kg") {

				IngredientWthKg ing(name, stod(masscount));
				ing.setPrice(price);
				ingKG.push_back(ing);

			}
			else if (korp == "Pcs") {
				IngredientWthPcs ing(name, stoi(masscount));
				ing.setPrice(price);
				ingPCS.push_back(ing);
			}
			
		}

		fs.close();
	}

	int SearchIng(string name, string type) {
	
		if (type=="kg")
		{
			for (size_t i = 0; i < ingKG.size(); i++)
			{
				if (name==ingKG[i].getName())
				{
					return i;
				}
			}
		}else{
			for (size_t i = 0; i < ingPCS.size(); i++)
			{
				if (name == ingPCS[i].getName())
				{
					return i;
				}
			}
		}

		return -1;
	}

	double getIngMassKG(int index) {
	
		return ingKG[index].getMass();

	}

	double getIngPriceKG(int index) {
	
		return ingKG[index].getPrice();
	}

	double getIngPricePCS(int index) {
	
		return ingPCS[index].getPrice();
	}

	int getIngCountPCS(int index) {
	
		return ingPCS[index].getCount();
	}

	void setIngMassKg(int index, double mass) {
	
		ingKG[index].setMass(mass);
	}

	void setIngCountPcs(int index, int pieces) {
	
		ingPCS[index].setCount(pieces);
	}

	void DeleteIngKg(int index)
	{
	
		ingKG.erase(ingKG.begin() + index);

	}

	void DeleteIngPcs(int index)
	{
	
		ingPCS.erase(ingPCS.begin() + index);

	}

};

class HotDrink {
	string name;
	double price;
	string type = "hot";

	int howMany;
public:
	HotDrink(string name, double price){
		setName(name);
		setPrice(price);
	}
	string getType()const noexcept {

		return type;
	}
	void setName(string& name) {
		if (name.length() < 3)
		{
			throw string("Name of drink cannot be less than 3 characters!");
		}
		this->name = name;
	}

	void setPrice(double price) {

		if (price < 0)
		{
			throw string("Price cannot be negative");
		}
		this->price = price;
	}

	void setHowMany(int howMany) {
	
		if (howMany<0)
		{
			throw string("Amount cannot be negative");
		}
		this->howMany = howMany;

	}

	string getName()const noexcept {

		return name;

	}
	double getPrice()const noexcept {
		return price;
	}

	int getHowMany()const noexcept {
	
		return howMany;
	}

	void Show() {
		cout << this->getName() << " - $" << this->getPrice() << endl;
	}
};

class ColdDrink{
	string name;
	double price;
	string type = "cold";

	int howMany;
public:
	ColdDrink(string name, double price) {
		setName(name);
		setPrice(price);
	}

	string getType()const noexcept {
	
		return type;
	}

	void setName(string& name) {
		if (name.length() < 3)
		{
			throw string("Name of drink cannot be less than 3 characters!");
		}
		this->name = name;
	}

	void setPrice(double price) {

		if (price < 0)
		{
			throw string("Price cannot be negative");
		}
		this->price = price;
	}

	void setHowMany(int howMany) {

		if (howMany < 0)
		{
			throw string("Amount cannot be negative");
		}
		this->howMany = howMany;

	}


	string getName()const noexcept {

		return name;

	}
	double getPrice()const noexcept {
		return price;
	
	}

	int getHowMany()const noexcept {

		return howMany;
	}

	void Show() {
		cout << this->getName() << " - $" << this->getPrice() << endl;
	}
};

class Cart {

	vector<Meal> meals;
	vector<HotDrink> hotdrinks;
	vector<ColdDrink> colddrinks;

	double totalP=0;

public:


	void addMealToCart(Meal meal) {
	
		meals.push_back(meal);

		this->totalP += meal.getPrice() * meal.getHowMany();
	
	}

	void addHotDrinkToCart(HotDrink drink) {
	
		hotdrinks.push_back(drink);

		this->totalP += drink.getPrice() * drink.getHowMany();
	
	}

	void addColdDrinkToCart(ColdDrink drink) {
	
		colddrinks.push_back(drink);

		this->totalP += drink.getPrice() * drink.getHowMany();
	}

	int getSizeMeals() {
	
		return meals.size();

	}

	int getSizeHotDrinks() {
	
		return hotdrinks.size();

	}

	int getSizeColdDrinks() {
	
		return colddrinks.size();

	}

	string getNameofMeal(int index) {
	
		return meals[index].getName();

	}

	string getTypeofMeal(int index) {
	
		return meals[index].getType();
	}

	string getNameofHotDrink(int index) {
	
		return hotdrinks[index].getName();

	}

	string getNameofColdDrink(int index) {
	
		return colddrinks[index].getName();

	}

	int getHowManyofMeal(int index) {

		return meals[index].getHowMany();

	}

	int getHowManyofHotDrink(int index) {

		return hotdrinks[index].getHowMany();

	}

	int getHowManyofColdDrink(int index) {

		return colddrinks[index].getHowMany();

	}

	double getPriceofMeal(int index) {
	
		return meals[index].getPrice();

	}

	double getPriceofHotDrink(int index) {
	
		return hotdrinks[index].getPrice();

	}

	double getPriceofColdDrink(int index) {
	
		return colddrinks[index].getPrice();

	}

	double getTotalP() {
	
		return totalP;
	}

	void setTotalP(double totalP) {
	
		this->totalP = totalP;
	
	}

	void setHowManyofMeal(int index,int qty) {
	
		meals[index].setHowMany(qty);
	
	}

	void setHowManyofHotDrink(int index,int qty) {
	
		hotdrinks[index].setHowMany(qty);
	
	}

	void setHowManyofColdDrink(int index,int qty) {
	
		colddrinks[index].setHowMany(qty);
	
	}

	void removeMeal(int index) {
	
		meals.erase(meals.begin() + index);

		this->totalP -= meals[index].getPrice() * meals[index].getHowMany();
	
	}

	void removeHotDrink(int index) {
	
		hotdrinks.erase(hotdrinks.begin() + index);

		this->totalP -= hotdrinks[index].getPrice() * hotdrinks[index].getHowMany();
	
	}

	void removeColdDrink(int index) {
	
		colddrinks.erase(colddrinks.begin() + index);

		this->totalP -= colddrinks[index].getPrice() * colddrinks[index].getHowMany();

	
	}

	

	int getSizeofNeedPCS(int index) {
	
		return meals[index].getSizeOfIngPcs();

	}

	string getNeedNameKg(int indexMeal,int indexIng) {
	
		return meals[indexMeal].getNameofIngKG(indexIng);
	
	}

	string getNeedNamePcs(int indexMeal,int indexIng) {
	
		return meals[indexMeal].getNameofIngPCS(indexIng);
	
	}

	int getAmountNeedKg(int indexMeal,int indexIng) {
		return meals[indexMeal].getKgofIngKG(indexIng);
	}
	int getAmountNeedPcs(int indexMeal,int indexIng) {
		return meals[indexMeal].getCountofIngPCS(indexIng);
	}

	void Show() {
	
		cout << "------Meals------" << endl;
		for (size_t i = 0; i < meals.size(); i++)
		{
			cout << i+1 << ". " << meals[i].getName() << "  -  $" << meals[i].getPrice() << "   Amount: " << meals[i].getHowMany() << "   Price:   $" <<meals[i].getPrice()*meals[i].getHowMany()<< endl;
		}
		cout << "------Hot Drinks------" << endl;
		for (size_t i = 0; i < hotdrinks.size(); i++)
		{
			cout << i+1 << ". " << hotdrinks[i].getName() << "  -  $" << hotdrinks[i].getPrice() << "   Amount: " << hotdrinks[i].getHowMany() << "   Price:   $" << hotdrinks[i].getPrice()* colddrinks[i].getHowMany()<< endl;
		}
		cout << "------Cold Drinks------" << endl;
		for (size_t i = 0; i < colddrinks.size(); i++)
		{
			cout << i+1 << ". " << colddrinks[i].getName() << "  -  $" << colddrinks[i].getPrice() << "   Amount: " << colddrinks[i].getHowMany() << "   Price:   $" << colddrinks[i].getPrice()* colddrinks[i].getHowMany()<< endl;
		}

		cout << endl << "Total Payment:     $" << totalP << endl;
	
	}

	void ClearAll() {
	
		meals.clear();
		hotdrinks.clear();
		colddrinks.clear();
	
	}

};

class User {

	string username;
	string password;
	vector<Cart> cartHistory;

	void setPassword(string& password) {
		if (password.length() < 8)
		{
			throw string("Password must be at least 8 characters!!");
		}
		this->password = password;
	
	}

public:


	void loadDataFromHistory() {
		ifstream fs("carthistory.txt");
		if (!fs.is_open()) throw string("File couldn't open...");

		cartHistory.clear();
		string line;

		while (getline(fs, line)) {
			if (line.empty()) continue;

			stringstream ss(line);
			string token;
			vector<string> parts;

			while (getline(ss, token, '#')) {
				parts.push_back(token);
			}

			if (parts.size() < 2) continue;

			string fileUsername = parts[0];
			Cart cart;

			for (size_t i = 1; i + 2 < parts.size(); i += 3) {
				string type = parts[i];
				string name = parts[i + 1];
				int count = stoi(parts[i + 2]);

				if (type == "meal") {
					Meal m(name,0,"hot");
					m.setHowMany(count);
					cart.addMealToCart(m);
				}
				else if (type == "hotdrink") {
					HotDrink h(name,0);
					h.setHowMany(count);
					cart.addHotDrinkToCart(h);
				}
				else if (type == "colddrink") {
					ColdDrink c(name,0);
					c.setHowMany(count);
					cart.addColdDrinkToCart(c);
				}
			}

			cartHistory.push_back(cart);
		}

		fs.close();
	}

	User(string& username, string& password) {
	
		setUsername(username);
		setPassword(password);
	}

	string getUsername()const noexcept {
	
		return username;
	
	}

	string getPassword()const noexcept {
	
		return password;
	
	}

	void setUsername(string&username) {
	
		if (username.length()<4)
		{
			throw string("Username must be at least 4 characters!!");
		}
		this->username = username;
	}

	void addCart(const Cart& cart) {
	
		cartHistory.push_back(cart);
	
	}

	int getSizeCartHistory() {
	
		return cartHistory.size();
	}

	void showCartHistory() {
	
		for (size_t i = 0; i < cartHistory.size(); i++)
		{
			cartHistory[i].Show();
		}

	}
	
	int getSizeMeals(int index) {
	
		return cartHistory[index].getSizeMeals();

	}

	int getSizeHotDrinks(int index) {
	
		return cartHistory[index].getSizeHotDrinks();

	}

	int getSizeColdDrinks(int index) {
	
		return cartHistory[index].getSizeColdDrinks();

	}

	string getNameOfMealIndex(int indexUser,int indexMeal) {
	
		return cartHistory[indexUser].getNameofMeal(indexMeal);
	
	}

	string getNameOfHotDrinkIndex(int index,int hots) {
	
		return cartHistory[index].getNameofHotDrink(hots);
	
	}

	string getNameOfColdDrinkIndex(int index,int colds) {
	
		return cartHistory[index].getNameofColdDrink(colds);
	
	}
	
	int getHowManyOfMealIndex(int indexUser,int indexMeal) {
	
		return cartHistory[indexUser].getHowManyofMeal(indexMeal);
	
	}
	
	int getHowManyOfHotDrinkIndex(int index,int hots) {
	
		return cartHistory[index].getHowManyofHotDrink(hots);
	
	}
	
	int getHowManyOfColdDrinkIndex(int index,int colds) {
	
		return cartHistory[index].getHowManyofColdDrink(colds);
	
	}

	double getPriceOfMealIndex(int index,int indexM) {
	
		return cartHistory[index].getPriceofMeal(indexM);
	}

	double getPriceOfHotDrinkIndex(int index,int indexM) {
	
		return cartHistory[index].getPriceofHotDrink(indexM);
	}

	double getPriceOfColdDrinkIndex(int index,int indexM) {
	
		return cartHistory[index].getPriceofColdDrink(indexM);
	}

	double getTotalPayment(int index) {
	
		return cartHistory[index].getTotalP();
	
	}

};

class Menu {

	vector<Meal> meals;
	vector<HotDrink> hotdrinks;
	vector<ColdDrink> colddrinks;

public:

	void saveDatatoMenu() {
		ofstream fs("menu.txt");
		if (!fs.is_open()) throw string("File couldn't open...");

		for (auto& m : meals)
			fs << "meal#" << m.getName() << "#" << m.getPrice() << "#" << m.getType() << "\n";

		for (auto& h : hotdrinks)
			fs << "Hotdrink#" << h.getName() << "#" << h.getPrice() << "#" << h.getType() << "\n";

		for (auto& c : colddrinks)
			fs << "Colddrink#" << c.getName() << "#" << c.getPrice() << "#" << c.getType() << "\n";

		fs.close();
	}

	void saveDatatoMeals() {
		ofstream fs("meals.txt");
		if (!fs.is_open()) throw string("File couldn't open...");

		for (auto& m : meals) {
			fs << "meal#" << m.getName() << "#" << m.getPrice() << "#" << m.getType();

			for (size_t i = 0; i < m.getSizeOfIngKg(); i++)
			{
				fs << "#" << m.getNameofIngKG(i) << "#" << m.getKgofIngKG(i);
			}

			for (size_t i = 0; i < m.getSizeOfIngPcs(); i++)
			{
				fs << "#" << m.getNameofIngPCS(i) << "#" << m.getCountofIngPCS(i);
			}

			fs << "\n";
		}
		for (auto& h : hotdrinks)
			fs << "Hotdrink#" << h.getName() << "#" << h.getPrice() << "#" << h.getType() << "\n";

		for (auto& c : colddrinks)
			fs << "Colddrink#" << c.getName() << "#" << c.getPrice() << "#" << c.getType() << "\n";

		fs.close();
	}

	void loadDataFromMeals() {
		ifstream fs("meals.txt");
		if (!fs.is_open()) throw string("File couldn't open...");

		meals.clear();
		hotdrinks.clear();
		colddrinks.clear();

		string line;
		while (getline(fs, line)) {
			if (line.empty()) continue;

			vector<string> parts;
			string token;
			stringstream ss(line);
			while (getline(ss, token, '#')) {
				parts.push_back(token);
			}

			if (parts.empty()) continue;

			string type = parts[0];

			
			if (type == "meal" && parts.size() >= 4) {
				string name = parts[1];
				double price = stod(parts[2]);
				string category = parts[3];

				Meal m(name, price, category);

				for (size_t i = 4; i + 1 < parts.size(); i += 2) {
					string ingName = parts[i];
					string ingValue = parts[i + 1];

					if (ingValue.find('.') != string::npos) {
						double kg = stod(ingValue);
						m.addIngKg(IngredientWthKg(ingName, kg));
					}
					else {
						int pcs = stoi(ingValue);
						m.addIngPcs(IngredientWthPcs(ingName, pcs));
					}
				}

				meals.push_back(m);
			}

			else if (type == "Hotdrink" && parts.size() == 4) {
				string name = parts[1];
				double price = stod(parts[2]);
				string category = parts[3];
				hotdrinks.emplace_back(name, price);
			}

			
			else if (type == "Colddrink" && parts.size() == 4) {
				string name = parts[1];
				double price = stod(parts[2]);
				string category = parts[3];
				colddrinks.emplace_back(name, price);
			}
		}

		fs.close();
	}

	void loadDataFromMenu() {
		ifstream fs("menu.txt");
		if (!fs.is_open()) throw string("File not found...");
		if (fs.peek() == ifstream::traits_type::eof()) throw string("File empty...");

		string row;
		while (getline(fs, row)) {
			vector<string> parts;
			string temp;
			for (char ch : row) {
				if (ch == '#') {
					parts.push_back(temp);
					temp.clear();
				}
				else temp += ch;
			}
			parts.push_back(temp);

			if (parts.size() != 4) continue;

			string mord = parts[0];
			string name = parts[1];
			double price = stod(parts[2]);
			string type = parts[3];

			if (mord == "meal") {
				meals.emplace_back(name, price, type);
			}
			else if (mord == "Hotdrink") {
				hotdrinks.emplace_back(name, price);
			}
			else if (mord == "Colddrink") {
				colddrinks.emplace_back(name, price);
			}
		}

		fs.close();
	}

	int SearchMealInMenu(string name) {
	
		for (size_t i = 0; i < meals.size(); i++)
		{
			if (meals[i].getName()==name)
			{
				return i;
			}
		}
		return -1;
	
	}

	int SearchHotDrinkInMenu(string& name) {

		for (size_t i = 0; i < hotdrinks.size(); i++)
		{
			if (hotdrinks[i].getName() == name)
			{
				return i;
			}
		}
		return -1;

	}

	int SearchColdDrinkInMenu(string& name) {

		for (size_t i = 0; i < colddrinks.size(); i++)
		{
			if (colddrinks[i].getName() == name)
			{
				return i;
			}
		}
		return -1;

	}

	int getSizeMeals()const noexcept {
		return meals.size();
	}

	void Show() {
	
		vector<Meal> hotmeals;
		vector<Meal> coldmeals;
		
		for (size_t i = 0; i < meals.size(); i++)
		{
			if (meals[i].getType() == "hot") {
			
				hotmeals.push_back(meals[i]);
			}
			else if(meals[i].getType() == "cold"){
				coldmeals.push_back(meals[i]);
			}
		}
		cout << "O------------  HOT MEALS  ------------O\n" << endl;
		for (size_t i = 0; i < hotmeals.size(); i++)
		{
			hotmeals[i].Show();
		}
		cout << "\nO------------  COLD MEALS  ------------O\n" << endl;
		for (size_t i = 0; i < coldmeals.size(); i++)
		{
			coldmeals[i].Show();
		}
		
		cout << "\nO------------  COLD DRINKS  ------------O\n" << endl;
		for (size_t i = 0; i < colddrinks.size(); i++)
		{
			colddrinks[i].Show();
		}
		cout << "\nO------------  HOT DRINKS  ------------O\n" << endl;
		for (size_t i = 0; i < hotdrinks.size(); i++)
		{
			hotdrinks[i].Show();
		}
		cout << endl;
	}

	void addMeal(Meal meal) {	
		this->meals.push_back(meal);
	}

	void addHotDrink(HotDrink drink) {
	
		this->hotdrinks.push_back(drink);
	}

	void addColdDrink(ColdDrink drink) {
		this->colddrinks.push_back(drink);
	}

	void ChangePriceofMeal(int index, double price) {	
		meals[index].setPrice(price);
		
	}

	void ChangePriceofHotDrink(int index, double price) {
		hotdrinks[index].setPrice(price);

	}

	void ChangePriceofColdDrink(int index, double price) {
		colddrinks[index].setPrice(price);

	}

	void DeleteMealFromMenu(int index) {
	
		meals.erase(meals.begin() + index);
	
	}

	void DeleteHotDrinkFromMenu(int index) {

		hotdrinks.erase(hotdrinks.begin() + index);

	}

	void DeleteColdDrinkFromMenu(int index) {

		colddrinks.erase(colddrinks.begin() + index);

	}

	void ShowMeal(int index) {
	
		meals[index].Show();

		cout << "Needed Ingredients" << endl;
		meals[index].ShowInfo();
		cout << endl;

	
	}

	void ShowHotDrink(int index) {
	
		hotdrinks[index].Show();
		cout << endl;

	}

	void ShowColdDrink(int index) {
	
		colddrinks[index].Show();
		cout << endl;

	}

	double getPriceMeal(int index) {
	
		return meals[index].getPrice();
	
	}

	double getPriceHotDrink(int index) {
	
		return hotdrinks[index].getPrice();
	
	}

	double getPriceColdDrink(int index) {
	
		return colddrinks[index].getPrice();
	
	}

	int getSizeOfMealNeedIngKg(int index) {
	
		return meals[index].getSizeOfIngKg();
	}

	string getNameOfMealNeedIngKg(int indexMeal,int indexIng) {
	
		return meals[indexMeal].getNameofIngKG(indexIng);
	
	}

	double getMassOfMealNeedIngKg(int indexMeal, int indexIng) {
	
		return meals[indexMeal].getKgofIngKG(indexIng);
	
	}
	int getSizeOfMealNeedIngPcs(int index) {
	
		return meals[index].getSizeOfIngPcs();
	}

	string getNameOfMealNeedIngPcs(int indexMeal,int indexIng) {
	
		return meals[indexMeal].getNameofIngPCS(indexIng);
	
	}

	int getCountOfMealNeedIngPcs(int indexMeal, int indexIng) {
	
		return meals[indexMeal].getCountofIngPCS(indexIng);
	
	}
};

class Restaurant {

	vector<User> users;
	Menu menu;
	Stock stock;
	Cart cart;

	double balance = 0;
public:

	Restaurant() {
		try{
			loadBalance();
		}
		catch(const string& s){
			saveBalance();
		
		}
		try {
			stock.loadDatafromStock();
		}
		catch (const string& s) {
			stock.saveDatatoStock();

		}
		try {
			menu.loadDataFromMenu();
		}
		catch (const string& s) {
			menu.saveDatatoMenu();

		}
		try {
			menu.loadDataFromMeals();
		}
		catch (const string& s) {
			menu.saveDatatoMeals();

		}
		
		
		try{ loadUsers(); }
		catch (const string& s) {
			saveUsers();

		}
		try{ loadHistory(); }
		catch (const string& s) {
			saveHistory();

		}

	}

	void saveBalance() {
		ofstream fs("balance.txt");

		if (!fs.is_open()) throw string("File couldn't open...");
		fs << balance << "\n";

		fs.close();
	
	}

	void loadBalance() {
	
		ifstream fs("balance.txt");
		if (!fs.is_open()) throw string("File not found...");
		if (fs.peek() == ifstream::traits_type::eof()) throw string("File empty...");

		string row;

		getline(fs, row);

		this->setBalance(stod(row));

		fs.close();

	}

	void saveHistory(){
	
		ofstream fs("carthistory.txt");

		if (!fs.is_open()) throw string("File couldn't open...");

		for (size_t t = 0; t < users.size(); t++)
		{
			fs << users[t].getUsername();
			for (size_t i = 0; i < users[t].getSizeCartHistory(); i++)
			{
				for (size_t j = 0; j < users[t].getSizeMeals(i); j++)
				{
					fs << "#meal#" << users[t].getNameOfMealIndex(i,j) << "#" << users[t].getHowManyOfMealIndex(i,j)<<"#"<<users[t].getPriceOfMealIndex(i,j);
				}
				for (size_t j = 0; j < users[t].getSizeHotDrinks(i); j++)
				{
					fs << "#hotdrink#" << users[t].getNameOfHotDrinkIndex(i, j) << "#" << users[t].getHowManyOfHotDrinkIndex(i, j) << "#" << users[t].getPriceOfHotDrinkIndex(i, j);
				}
				for (size_t j = 0; j < users[t].getSizeColdDrinks(i); j++)
				{
					fs << "#colddrink#" << users[t].getNameOfColdDrinkIndex(i, j) << "#" << users[t].getHowManyOfColdDrinkIndex(i, j) << "#" << users[t].getPriceOfColdDrinkIndex(i, j);
				}

				
			}
			fs << "\n";
		}
				
		fs.close();
	
	}

	void loadHistory() {
	
		ifstream fs("carthistory.txt");
		if (!fs.is_open()) throw string("File not found...");
		if (fs.peek() == ifstream::traits_type::eof()) throw string("File empty...");

		string row;
		while (getline(fs, row)) {
			vector<string> parts;
			string temp;
			for (char ch : row) {
				if (ch == '#') {
					parts.push_back(temp);
					temp.clear();
				}
				else temp += ch;
			}
			parts.push_back(temp);
	
			Cart newCart;
			string name = parts[0];
			int index = this->SearchUser(name);

			if (index == -1)
			{
				continue;
			}

			for (size_t i = 1; i < parts.size(); i+=4)
			{

				if (parts[i]=="meal")
				{
					string nameMeal = parts[i + 1];
					int amount = stoi(parts[i + 2]);
					double price = stod(parts[i + 3]);

					Meal meal(nameMeal, price, "hot");
					meal.setHowMany(amount);
					newCart.addMealToCart(meal);
				}
				else if (parts[i]=="hotdrink")
				{
					string nameHotD = parts[i + 1];
					int amount = stoi(parts[i + 2]);
					double price = stod(parts[i + 3]);

					HotDrink drink(nameHotD, price);
					drink.setHowMany(amount);
					newCart.addHotDrinkToCart(drink);
				}
				else if (parts[i]=="colddrink")
				{
					string nameColdD = parts[i + 1];
					int amount = stoi(parts[i + 2]);
					double price = stod(parts[i + 3]);

					ColdDrink drink(nameColdD, price);
					drink.setHowMany(amount);
					newCart.addColdDrinkToCart(drink);
				}

			}

			users[index].addCart(newCart);
			

			

		}

		fs.close();
	
	}
	
	void saveUsers() {
		ofstream fs("users.txt");
		if (!fs.is_open()) throw string("File couldn't open...");

		for (auto& u : users) {
			fs << u.getUsername() << "#" << u.getPassword() << "\n";
		}

		fs.close();
	}

	void loadUsers() {
		ifstream fs("users.txt");
		if (!fs.is_open()) throw string("File not found...");
		if (fs.peek() == ifstream::traits_type::eof()) throw string("File empty...");

		string row;
		while (getline(fs, row)) {
			vector<string> parts;
			string temp;
			for (char ch : row) {
				if (ch == '#') {
					parts.push_back(temp);
					temp.clear();
				}
				else temp += ch;
			}
			parts.push_back(temp);

			if (parts.size() != 2) continue;

			string username = parts[0];
			string password = parts[1];

			User user(username, password);

			users.push_back(user);

		}

		fs.close();
	}

	void saveData() {

		saveBalance();
		stock.saveDatatoStock();
		menu.saveDatatoMenu();
		menu.saveDatatoMeals();
		saveUsers();
		saveHistory();
		
	}

	void loadData() {
		loadBalance();
		stock.loadDatafromStock();
		menu.loadDataFromMenu();
		menu.loadDataFromMeals();	
		loadUsers();
		loadHistory();
	}

	void ShowMenu() {
		this->menu.Show();
	}

	void ShowStock() {

		this->stock.Show();
	}

	void addNewMeal(Meal meal) {

		menu.addMeal(meal);
		this->saveData();
	}

	void addNewDrink(HotDrink drink) {

		menu.addHotDrink(drink);
		this->saveData();
	}

	void addNewDrink(ColdDrink drink) {

		menu.addColdDrink(drink);
		this->saveData();
	}

	void addNewIngredientKg(IngredientWthKg ing) {

		this->stock.addIngredientKG(ing);

	}

	void addNewIngredientPcs(IngredientWthPcs ing) {

		this->stock.addIngredientPCS(ing);

	}

	void addMealCart(Meal& meal) {
		
		cart.addMealToCart(meal);
	}

	void addHotDrinkCart(HotDrink drink) {
	
		cart.addHotDrinkToCart(drink);
	}

	void addColdDrinkCart(ColdDrink drink) {
	
		cart.addColdDrinkToCart(drink);
	}

	int SearchMeal(string& name) {

		return menu.SearchMealInMenu(name);

	}

	int SearchIngredient(string name, string type) {
		return stock.SearchIng(name, type);
	}

	int SearchHotDrink(string& name) {

		return menu.SearchHotDrinkInMenu(name);

	}

	int SearchColdDrink(string& name) {

		return menu.SearchColdDrinkInMenu(name);

	}

	void changePriceMeal(int index, double price) {

		menu.ChangePriceofMeal(index, price);
		this->saveData();

	}

	void changePriceHotDrink(int index, double price) {
		menu.ChangePriceofHotDrink(index, price);
		this->saveData();
	}

	void changePriceColdDrink(int index, double price) {
		menu.ChangePriceofColdDrink(index, price);
		this->saveData();
	}

	void DeleteMeal(int index) {

		menu.DeleteMealFromMenu(index);
		this->saveData();

	}

	void DeleteHotDrink(int index) {

		menu.DeleteHotDrinkFromMenu(index);
		this->saveData();
	}

	void DeleteColdDrink(int index) {

		menu.DeleteColdDrinkFromMenu(index);
		this->saveData();
	}

	void DeleteIngredientKG(int index) {
		stock.DeleteIngKg(index);

	}

	void DeleteIngredientPCS(int index) {
		stock.DeleteIngPcs(index);

	}

	void ShowMealInfo(int index) {

		menu.ShowMeal(index);
	}

	void ShowHotDrinkInfo(int index) {
		menu.ShowHotDrink(index);
	}

	void ShowColdDrinkInfo(int index) {
		menu.ShowColdDrink(index);
	}

	void ShowIngredientKg(int index) {

		stock.ShowIngKg(index);
	}

	void ShowIngredientPcs(int index) {

		stock.ShowIngPcs(index);
	}

	void ShowCart() {
	
		cart.Show();
	
	}

	void ShowCartHistory(int index) {

		users[index].showCartHistory();

	}

	double getIngredientMassKG(int index) {
		return stock.getIngMassKG(index);

	}

	double getIngredientPriceKG(int index) {
	
		return stock.getIngPriceKG(index);
	}

	double getIngredientPricePCS(int index) {
	
		return stock.getIngPricePCS(index);
	}

	int getInredientCountPcs(int index) {

		return stock.getIngCountPCS(index);
	}

	void setIngredientMassKg(int index, double mass) {

		stock.setIngMassKg(index, mass);
	}

	void setIngredientCountPcs(int index, int pieces) {

		stock.setIngCountPcs(index, pieces);
	}

	int SearchUser(string& username) {

		for (size_t i = 0; i < users.size(); i++)
		{
			if (users[i].getUsername() == username)
			{
				return i;
			}
		}
		return -1;

	}

	void addUser(User user) {

		users.push_back(user);

	}

	string getPassword(int index) {
		return users[index].getPassword();
	}

	double getPriceofMeal(int index) {
	
		return menu.getPriceMeal(index);
	}

	double getPriceofHotDrink(int index) {
	
		return menu.getPriceHotDrink(index);
	}

	double getPriceofColdDrink(int index) {
	
		return menu.getPriceColdDrink(index);
	}

	

	
	int getSizeofNeedPCS(int index) {
	
		return cart.getSizeofNeedPCS(index);
	
	}

	string getIngNameKG(int indexMeal,int indexIng) {
	
		
	
	}

	int getSizeOfCartHotDrinks() {
		return cart.getSizeHotDrinks();
	}

	int getSizeOfCartColdDrinks() {
		return cart.getSizeColdDrinks();
	}

	void addCartToUser(int index) {
	
		users[index].addCart(cart);

	}

	bool updateCartQuantity(const string& itemName, int newQty) {

		for (size_t i = 0; i < cart.getSizeMeals(); i++)
		{
			if (cart.getNameofMeal(i)==itemName)
			{
				cart.setHowManyofMeal(i,newQty);

				return this->checkIng(itemName,newQty);
			}
			
		}
		for (size_t i = 0; i < cart.getSizeHotDrinks(); i++)
		{
			if (cart.getNameofHotDrink(i)==itemName)
			{
				cart.setHowManyofHotDrink(i,newQty);
				return true;
			}
			
		}
		for (size_t i = 0; i < cart.getSizeColdDrinks(); i++)
		{
			if (cart.getNameofColdDrink(i)==itemName)
			{
				cart.setHowManyofColdDrink(i,newQty);
				return true;
			}
			
		}


		
		return false;
	}

	bool removeItemFromCart(const string& itemName) {

		for (size_t i = 0; i < cart.getSizeMeals(); i++)
		{
			if (cart.getNameofMeal(i) == itemName)
			{
				cart.removeMeal(i);
				return true;
			}

		}
		for (size_t i = 0; i < cart.getSizeHotDrinks(); i++)
		{
			if (cart.getNameofHotDrink(i) == itemName)
			{
				cart.removeHotDrink(i);
				return true;
			}

		}
		for (size_t i = 0; i < cart.getSizeColdDrinks(); i++)
		{
			if (cart.getNameofColdDrink(i) == itemName)
			{
				cart.removeColdDrink(i);
				return true;
			}

		}



		return false;
	}

	bool isCartEmpty(bool answer = true) {
	
		if (cart.getSizeMeals()>0)
		{
			answer = false;
			return answer;
		}
		if (cart.getSizeHotDrinks()>0)
		{
			answer = false;
			return answer;
		}
		if (cart.getSizeColdDrinks()>0)
		{
			answer = false;
			return answer;
		}
		return answer;
	
	}

	void clearCart() {
		cart.ClearAll();
	
	}

	double getBalance() {
		return balance;
	}

	void setBalance(double b) {
		if (b<0)
		{
			throw string("Balance cannot be negative");
		}
		this->balance = b;
	}

	void showBalance() {

		cout << "Balance:   $" << this->balance << endl;

	}

	void addBalance(double adding) {
	
		this->setBalance(this->getBalance() + adding);
	}

	void reduceBalance(double reduce) {
	
		this->setBalance(this->getBalance() - reduce);
	}

	double getCartTotalPayment() {
	
		return cart.getTotalP();

	}

	bool checkIng(string name, int amount) {


		int indexMenuIng = menu.SearchMealInMenu(name);

		for (size_t i = 0; i < menu.getSizeOfMealNeedIngKg(indexMenuIng); i++)
		{
			string name = menu.getNameOfMealNeedIngKg(indexMenuIng, i);

			int indexIng = stock.SearchIng(name, "kg");

			if (indexIng == -1)
			{
				return false;
			}

			double mass = menu.getMassOfMealNeedIngKg(indexMenuIng, i) * amount;

			if (stock.getIngMassKG(indexIng) < mass)
			{
				return false;
			}

		}


		for (size_t i = 0; i < menu.getSizeOfMealNeedIngPcs(indexMenuIng); i++)
		{
			string name = menu.getNameOfMealNeedIngPcs(indexMenuIng, i);

			int indexIng = stock.SearchIng(name, "pieces");

			if (indexIng == -1)
			{
				return false;
			}

			int pieces = menu.getCountOfMealNeedIngPcs(indexMenuIng, i) * amount;

			if (stock.getIngCountPCS(indexIng) < pieces)
			{
				return false;
			}

		}

		return true;

	}

	bool removeFromStock() {
		
		for (size_t i = 0; i < cart.getSizeMeals(); ++i) {
			int indexMenuMeal = menu.SearchMealInMenu(cart.getNameofMeal(i));
			int amount = cart.getHowManyofMeal(i);

			
			for (size_t j = 0; j < menu.getSizeOfMealNeedIngKg(indexMenuMeal); ++j) {
				string ingName = menu.getNameOfMealNeedIngKg(indexMenuMeal, j);
				int indexStockIng = stock.SearchIng(ingName, "kg");
				if (indexStockIng == -1) {
					cout << "Error: Ingredient '" << ingName << "' not found in stock (kg)." << endl;
					return false;
				}
				double needed = menu.getMassOfMealNeedIngKg(indexMenuMeal, j) * amount;
				double available = stock.getIngMassKG(indexStockIng);
				if (available < needed) {
					cout << "Error: Not enough '" << ingName << "' in stock (kg). Needed: " << needed << ", available: " << available << endl;
					return false;
				}
				stock.setIngMassKg(indexStockIng, available - needed);
			}

			
			for (size_t j = 0; j < menu.getSizeOfMealNeedIngPcs(indexMenuMeal); ++j) {
				string ingName = menu.getNameOfMealNeedIngPcs(indexMenuMeal, j);
				int indexStockIng = stock.SearchIng(ingName, "pieces");
				if (indexStockIng == -1) {
					cout << "Error: Ingredient '" << ingName << "' not found in stock (pieces)." << endl;
					return false;
				}
				int neededPieces = menu.getCountOfMealNeedIngPcs(indexMenuMeal, j) * amount;
				int availablePieces = stock.getIngCountPCS(indexStockIng);
				if (availablePieces < neededPieces) {
					cout << "Error: Not enough '" << ingName << "' in stock (pieces). Needed: " << neededPieces << ", available: " << availablePieces << endl;
					return false;
				}
				stock.setIngCountPcs(indexStockIng, availablePieces - neededPieces);
			}
		}

	

		return true;
	}

};


void main() {

	Restaurant restaurant;
	setColor(11);
	cout << " __        __   _                               " << endl;
	cout << " \\ \\      / /__| | ___ ___  _ __ ___   ___ " << endl;
	cout << "  \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\"<<endl;
	cout << "   \\ V  V /  __/ | (_| (_) | | | | | |  __/ " << endl;
	cout << "    \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|"<< endl;
	cout << endl;
	cout << "                             T O   V A L H A L L A" << endl << endl << endl;
	setColor(14);
	char choise;

	while (true)
	{
		setColor(14);
		cout << "Enter the restaurant system" << endl << endl;
		cout << "1. Admin Panel" << endl;
		cout << "2. User Panel" << endl;
		cout << "3. Exit" << endl;
		setColor(14);
		cout << "\n> ";

		cin >> choise;
		cin.ignore();
		system("cls");
		if (choise=='1'){

			system("cls"); 
			string username, password;
			
			cout << "Enter username: ";
			getline(cin, username);
			cout << "Enter password: ";
			getline(cin, password);

			system("cls");

			if (username=="admin"&&password=="valhalla")
			{
				setColor(14);
				bool running = true;
				cout << "Welcome to the system BOSS" << endl<<endl;

				while(running){
				setColor(14);
				cout << "Choose where do you want to make change: \n" << endl;
				
				cout << "1. Menu" << endl;
				cout << "2. Stock" << endl;
				cout << "3. See Balance" << endl;
				cout << "4. Add Balance" << endl;
				cout << "5. Back" << endl;
				setColor(14);
				cout << "\n> ";
				cin >> choise;
				cin.ignore();
				system("cls");

				switch (choise)  {

				case '1':

					while(true){
						setColor(14);
						cout << "1. Show Menu Items" << endl;
						cout << "2. Add New Meal to Menu" << endl;
						cout << "3. Add New Drink to Menu" << endl;
						cout << "4. Change price of Menu item" << endl;
						cout << "5. Delete menu item" << endl;
						cout << "6. Search and show info menu item" << endl;
						cout << "7. Back" << endl<<endl;
						setColor(14);
						cout << "> ";

					cin >> choise;
					cin.ignore();
					system("cls");

					if (choise=='1')
					{
						restaurant.ShowMenu();
						cout << endl << endl;
					}

					else if (choise == '2') {
					
						string type;
						string mealname;
						double price;
						setColor(14);
						cout << "Type of Meal: \n" << endl;
						cout << "1. Hot" << endl;
						cout << "2. Cold" << endl;
						cout << "\n> ";
						
						getline(cin, type);
						if (type=="1")
						{
							type = "hot";
						}
						else if (type == "2") {
							type = "cold";
						}
						else {
							setColor(12);
							cout << "Wrong choice!!!" << endl;
							setColor(14);
						}

						cout << "\nEnter name of meal: ";
						getline(cin, mealname);
						if (restaurant.SearchMeal(mealname) != -1) {

							system("cls");
							setColor(12);
							cout << "There is this meal in Menu already\n" << endl;
							setColor(14);
							continue;
						
						}

						cout << "Enter the price of meal: ";
						cin >> price;
						cin.ignore();
						system("cls");
						
							Meal meal(mealname, price, type);
						
						
						setColor(10);
						cout << "Meal Created Successfully\n" << endl;
						setColor(14);
						while(1){
							setColor(14);
							cout << "1. Add ingredient" << endl;
							cout << "2. Finish" << endl;
							cout << "\n> ";
							setColor(14);
							cin >> choise;
							cin.ignore();
							system("cls");

							if (choise=='1')
							{
								string ingType;
								string ingName;
								double mass; int count;
								setColor(14);
								cout << "Ingredient will be by: \n" << endl;
								cout << "1. kg" << endl;
								cout << "2. pieces" << endl;
								cout << "\n> ";
								setColor(14);
								getline(cin, ingType);


								cout << "Enter the ing name: ";
								getline(cin, ingName);

								

								if (ingType=="1")
								{
									cout << "Enter the amount of ingredient(kg): ";
									cin>> mass;
									cin.ignore();
									system("cls");
									try { 
										IngredientWthKg neededIng(ingName, mass); 
										meal.addIngKg(neededIng);
									}
									catch (const string& s) {
										setColor(12);cout << s << endl<<endl;setColor(14);
										continue;
									}
									

									setColor(10);
									cout << "Ingredient Added Successfully\n" << endl;
									setColor(14);
								}
								else if (ingType=="2")
								{
									cout << "Enter the amount of ingredient(pieces): ";
									cin >> count;
									cin.ignore();
									system("cls");

									try { IngredientWthPcs neededIng(ingName, count); 
									meal.addIngPcs(neededIng);
									}
									catch (const string& s) { setColor(12);cout << s << endl<<endl;setColor(14); }
									
									setColor(10);
									cout << "Ingredient Added Successfully\n" << endl;
									setColor(14);
								}
								else {				
									system("cls");
									setColor(12);
									cout << "Wrong choice!!!" << endl;
									setColor(14);
									continue;
								}
							}
							else if (choise == '2') {
								restaurant.addNewMeal(meal);
								system("cls");
								setColor(10);
								cout << "Meal was added Menu successfully\n" << endl;
								setColor(14);
								break;
							}
						}
					}

					else if (choise == '3') {
						string type;
						string drinkname;
						double price;
						setColor(14);
						cout << "Type of Drink: \n" << endl;
						cout << "1. Hot" << endl;
						cout << "2. Cold" << endl << endl;
						cout << "> ";
						setColor(14);
						getline(cin, type);
						if (type!="1" && type!="2")
						{
							system("cls");
							setColor(12);
							cout << "Wrong choice!!!\n" << endl;
							setColor(14);
							continue;
						}

						cout << "Enter name of drink: ";
						getline(cin, drinkname);
						

						if (type=="1")
						{
							if (restaurant.SearchHotDrink(drinkname)!=-1)
							{
								system("cls");
								setColor(12);
								cout << "There is this drink in menu already\n" << endl;
								setColor(14);
								continue;
							}
							cout << "Enter the price of drink: ";
							cin >> price;
							cin.ignore();

							system("cls");

							try { HotDrink drink(drinkname, price);
							restaurant.addNewDrink(drink);
							}
							catch (const string& s) { setColor(12);cout << s << endl<<endl;setColor(14); continue; }
							
							setColor(10);
							cout << "Hot Drink added Successfully\n" << endl;
							setColor(14);
						}

						else if (type == "2") {
							if (restaurant.SearchColdDrink(drinkname) != -1)
							{
								system("cls");
								setColor(12);
								cout << "There is this drink in menu already\n" << endl;
								setColor(14);
								continue;
							}
							cout << "Enter the price of drink: ";
							cin >> price;
							cin.ignore();

							system("cls");
							try { ColdDrink drink(drinkname, price); 
							restaurant.addNewDrink(drink);
							}
							catch (const string& s) { setColor(12);cout << s << endl<<endl;setColor(14); continue; }
							
							setColor(10);
							cout << "Cold Drink added Successfully\n" << endl;
							setColor(14);
						}
					}

					else if (choise == '4') {
					
						string name;
						string place;
						double price;
						int index;
						cout << "Enter the name of Menu item: ";
						getline(cin, name);

						
						index = restaurant.SearchMeal(name);

						if (index!=-1)
						{
							place = "meal";
						}
						else {
							index = restaurant.SearchHotDrink(name);
							if (index!=-1)
							{
								place = "Hotd";
							}
							else {
								index = restaurant.SearchColdDrink(name);
								if (index!=-1)
								{
									place = "Coldd";
								}
							}
						}

						if (index==-1)
						{
							system("cls");
							setColor(12);
							cout << "There is no this item in menu" << endl;
							setColor(14);
						}
						else {
						
							if (place=="meal")
							{
								
								cout << "Enter new price: $";
								cin >> price;
								cin.ignore();

								system("cls");
								try{
								restaurant.changePriceMeal(index, price);
								}
								catch (const string& s) {
									setColor(12);cout << s << endl<<endl;setColor(14);
									continue;
								}
								setColor(10);
								cout << "Price Changed Successfully" << endl;
								setColor(14);
							}
							else if (place == "Hotd") {
								cout << "Enter new price: $";
								cin >> price;
								cin.ignore();
								system("cls");
								try { restaurant.changePriceHotDrink(index, price); }
								catch (const string& s) { setColor(12);cout << s << endl<<endl;setColor(14); continue; }
								setColor(10);
								cout << "Price Changed Successfully" << endl;
								setColor(14);
							}
							else {
								cout << "Enter new price: $";
								cin >> price;
								cin.ignore();
								system("cls");
								try { restaurant.changePriceHotDrink(index, price); }
								catch (const string& s) { setColor(12);cout << s << endl<<endl;setColor(14); continue; }
								setColor(10);
								cout << "Price Changed Successfully" << endl;
								setColor(14);
							}
						
						}
						

					}

					else if (choise == '5') {
						string name;
						while (1) {
							setColor(14);
							cout << "1. Delete Meal" << endl;
							cout << "2. Delete Hot Drink" << endl;
							cout << "3. Delete Cold Drink" << endl;
							cout << "4. Back" << endl << endl;
							cout << "> ";
							setColor(14);
							cin >> choise;
							cin.ignore();
							system("cls");
							if (choise == '1') {
								cout << "Enter the name of unwanted meal: ";
								getline(cin, name);
								system("cls");
								int index = restaurant.SearchMeal(name);
								if (index == -1) {

									setColor(12);
									cout << "There is no such meal in menu\n";
									setColor(14);
									continue;
								}
								restaurant.DeleteMeal(index);
								setColor(10);
								cout << "Meal deleted successfully!\n";
								setColor(14);
							}
							else if (choise == '2') {
								cout << "Enter the name of unwanted Hot Drink: ";
								getline(cin, name);
								system("cls");
								int index = restaurant.SearchHotDrink(name);
								if (index == -1) {
									setColor(12);
									cout << "There is no such Hot Drink in menu\n";
									setColor(14);
									continue;
								}
								restaurant.DeleteHotDrink(index);
								setColor(10);
								cout << "Hot drink deleted successfully!\n";
								setColor(14);
							}
							else if (choise == '3') {
								cout << "Enter the name of unwanted Cold Drink: ";
								getline(cin, name);
								system("cls");
								int index = restaurant.SearchColdDrink(name);
								if (index == -1) {
									setColor(12);
									cout << "There is no such Cold Drink in menu\n";
									setColor(14);
									continue;
								}
								restaurant.DeleteColdDrink(index);
								setColor(10);
								cout << "Cold drink deleted successfully!\n";
								setColor(14);
							}
							else if (choise == '4') {
								break;
							}
							else {
								system("cls");
								setColor(12);
								cout << "Wrong choice!!!\n" << endl;
								setColor(14);
								continue;
							}
						}
					
					}

					else if (choise == '6') {
					
						string name;
						int index;

						cout << "Enter the name of menu item: ";
						getline(cin, name);

						system("cls");
						index = restaurant.SearchMeal(name);

						if (index != -1)
						{
							cout << endl;
							restaurant.ShowMealInfo(index);
							cout << endl;
						}
						else {

							index = restaurant.SearchHotDrink(name);
							if (index != -1)
							{
								cout << endl;
								restaurant.ShowHotDrinkInfo(index);
								cout << endl;
							}
							else {
								index = restaurant.SearchColdDrink(name);
								if (index != -1)
								{
									cout << endl;
									restaurant.ShowColdDrinkInfo(index);
									cout << endl;
								}
							}
						}

						if (index == -1)
						{
							system("cls");
							setColor(12);
							cout << "There is no this item in menu\n" << endl;
							setColor(14);
						}

					}

					else if (choise == '7') {
						break;
					}
					
					else {


						system("cls");
						setColor(12);
						cout << "Wrong Choice!!"<<endl;
						setColor(14);
					}

				}

				break;

				case '2':

					while(1){
					setColor(14);
					cout << "1. Show Stock Items" << endl;
					cout << "2. Add or Buy New Ingredient" << endl;
					cout << "3. Decrease stock item" << endl;
					cout << "4. Delete stock item" << endl;
					cout << "5. Search and show info stock item" << endl;
					cout << "6. Back" << endl;
					cout << "\n> ";
					setColor(14);
					cin >> choise;
					cin.ignore();

					system("cls");

					if (choise=='1')
					{
						cout << endl;
						restaurant.ShowStock();
						cout << endl;

					}

					else if (choise == '2') {
						
						string name;
						double price;

						while (true) {
							setColor(14);
							cout << "Enter the type of ingredient: " << endl << endl;
							cout << "1. Kg" << endl;
							cout << "2. Pieces" << endl;
							cout << "3. Finish" << endl;
							cout << "\n> ";
							setColor(14);

							cin >> choise;
							cin.ignore();
							string type;

							if (choise=='1')
							{
								type = "kg";
								double mass;
								cout << "Enter the name of ingredient: ";
								getline(cin,name);

								int index = restaurant.SearchIngredient(name, type);

								if (index != -1)
								{
									
									cout << "Enter the amount of ingredient that you want to buy: ";
									cin >> mass;
									cin.ignore();
									system("cls");
									double price = restaurant.getIngredientPriceKG(index)*mass;
									double newmass = mass + restaurant.getIngredientMassKG(index);
									restaurant.setIngredientMassKg(index, newmass);
									restaurant.reduceBalance(price);
									restaurant.saveData();
									setColor(10);
									cout << "Ingredient Bought Successfully" << endl;
									setColor(14);
								}
								else{

								cout << "Enter the amount of ingredient(KG): ";
								cin >> mass;

								cout << "Enter price per kg: ";
								cin >> price;
								cin.ignore();

								system("cls");
								try {
									IngredientWthKg ing(name, mass);
									ing.setPrice(price);
									double redprice = mass * price;
									restaurant.addNewIngredientKg(ing);
									restaurant.reduceBalance(redprice);
									restaurant.saveData();
								}
								catch (const string& s) {
									setColor(12);cout << s << endl<<endl;setColor(14);
									continue;

								}
								setColor(10);
								cout << "Ingredient Bought Successfully" << endl; 
								setColor(14);
								}
							}

							else if (choise == '2')
							{
								type = "pcs";
								int pieces;
								cout << "Enter the name of ingredient: ";
								getline(cin, name);
								double redprice;
								int index = restaurant.SearchIngredient(name, type);

								if (index != -1)
								{
									cout << "Enter the amount of ingredient that you want to buy: ";
									cin >> pieces;
									cin.ignore();

									system("cls");
									redprice = pieces * restaurant.getIngredientPricePCS(index);
									double newpieces = pieces + restaurant.getInredientCountPcs(index);
									try{
									restaurant.setIngredientCountPcs(index, newpieces);
									restaurant.saveData();
									}
									catch (const string& s) {
										setColor(12);cout << s << endl<<endl;setColor(14);
										continue;
									}
									setColor(10);
									cout << "Ingredient Bought Successfully\n" << endl;
									setColor(14);

								} 
								else {

								cout << "Enter the amount of ingredient(Pieces): ";
								cin >> pieces;

								cout << "Enter price per piece: ";
								cin >> price;
								cin.ignore();
								system("cls");
								try{
								IngredientWthPcs ing(name, pieces);
								ing.setPrice(price);
								redprice = pieces * price;
								restaurant.addNewIngredientPcs(ing);
								restaurant.reduceBalance(redprice);
								restaurant.saveData();
								}
								catch (const string& s) {
									setColor(12);cout << s << endl<<endl;setColor(14);
									continue;
								}
								setColor(10);
								cout << "Ingredient Bought Successfully" << endl;
								setColor(14);
								}
							}
							
							else if (choise == '3') {	
								system("cls");
								break;
							}

							else {
								system("cls");
								setColor(12);
								cout << "Wrong Choice!!!" << endl;
								setColor(14);
								continue;
							}
						
						}
					}

					else if (choise == '3') {
					
						string name;
						double price;
						while (true) {
							setColor(14);
							cout << "Enter the type of ingredient: " << endl << endl;
							cout << "1. Kg" << endl;
							cout << "2. Pieces" << endl;
							cout << "3. Finish" << endl;
							cout << "\n> ";
							setColor(14);
							cin >> choise;
							cin.ignore();
							string type;

							if (choise == '1')
							{
								type = "kg";
								double mass;
								cout << "Enter the name of ingredient: ";
								getline(cin, name);
								int index = restaurant.SearchIngredient(name, type);

								if (index != -1)
								{

									cout << "Enter the amount of ingredient that you want to remove: ";
									cin >> mass;
									cin.ignore();

									system("cls");
									double newmass = restaurant.getIngredientMassKG(index)-mass;
									try{
									restaurant.setIngredientMassKg(index, newmass);
									restaurant.saveData();
									}
									catch (const string& s) {
										setColor(12);cout << s << endl<<endl;setColor(14);
										continue;
									}

									
									setColor(10);
									cout << "Ingredient updated successfully" << endl;
									setColor(14);
								}

								else {

									system("cls");
									setColor(12);
									cout << "There is not this ingredient in stock" << endl;
									setColor(14);
									continue;
								}
							}

							else if (choise == '2')
							{
								type = "pcs";
								int pieces;
								cout << "Enter the name of ingredient: ";
								getline(cin, name);
								int index = restaurant.SearchIngredient(name, type);

								if (index != -1)
								{
									cout << "Enter the amount of ingredient that you want to remove: ";
									cin >> pieces;
									cin.ignore();
									system("cls");
									double newpieces = restaurant.getInredientCountPcs(index)-pieces;
									try{
									restaurant.setIngredientCountPcs(index, newpieces);
									restaurant.saveData();
									}
									catch (const string& s) {
										setColor(12);cout << s << endl<<endl;setColor(14);
										continue;
									}
									setColor(10);
									cout << "Ingredient updated successfully" << endl;
									setColor(14);
								}
								else {

									system("cls");
									setColor(12);
									cout << "There is not this ingredient in stock" << endl;
									setColor(14);
									continue;
								}
							}

							else if (choise == '3') {
								system("cls");
								break;
							}

							else {

								system("cls");
								setColor(12);
								cout << "Wrong Choice!!!" << endl;
								setColor(14);
								continue;
							}

						}

					}

					else if (choise == '4') {
					
						string name;

						while (true) {
							setColor(14);
							cout << "Enter the type of ingredient: " << endl << endl;
							cout << "1. Kg" << endl;
							cout << "2. Pieces" << endl;
							cout << "3. Finish" << endl;
							cout << "\n> ";
							setColor(14);

							cin >> choise;
							cin.ignore();

							string type;

							if (choise == '1')
							{
								type = "kg";
								cout << "Enter the name of ingredient: ";
								getline(cin, name);
								system("cls");
								int index = restaurant.SearchIngredient(name, type);

								if (index != -1)
								{
									try{
									restaurant.DeleteIngredientKG(index);
									restaurant.saveData();
									}
									catch (const string& s) {
										setColor(12);cout << s << endl<<endl;setColor(14);
										continue;
									}
									setColor(10);
									cout << "Ingredient Removed Successfully" << endl;
									setColor(14);
								}
								else {
									setColor(12);
									cout << "There is not this ingredient in stock" << endl;
									setColor(14);
									continue;
								}
							}

							else if (choise == '2')
							{
								type = "pcs";
								cout << "Enter the name of ingredient: ";
								getline(cin, name);
								system("cls");
								int index = restaurant.SearchIngredient(name, type);

								if (index != -1)
								{
									try{
									restaurant.DeleteIngredientPCS(index);
									restaurant.saveData();
									}
									catch (const string& s) {
										setColor(12);cout << s << endl<<endl;setColor(14);
										continue;
									}
									setColor(10);
									cout << "Ingredient Removed Successfully" << endl << endl;
									setColor(14);
								}
								else {
									setColor(12);
									cout << "There is not this ingredient in stock" << endl;
									setColor(14);
									continue;

								}
							}

							else if (choise == '3') {
								system("cls");
								break;
							}

							else {
								system("cls");
								setColor(12);
								cout << "Wrong Choice!!!" << endl;
								setColor(14);
								continue;
							}
						}
					}

					else if (choise == '5') {
					
						string name;

						while (true) {
							setColor(14);
							cout << "Enter the type of ingredient: " << endl << endl;
							cout << "1. Kg" << endl;
							cout << "2. Pieces" << endl;
							cout << "3. Finish" << endl;
							cout << "\n> ";
							setColor(14);

							cin >> choise;
							cin.ignore();

							string type;

							if (choise == '1')
							{
								type = "kg";
								cout << "Enter the name of ingredient: ";
								getline(cin, name);
								system("cls");
								int index = restaurant.SearchIngredient(name, type);

								if (index != -1)
								{
									cout << endl;
									restaurant.ShowIngredientKg(index);
									cout << endl;

								}
								else {
									setColor(12);
									cout << "There is not this ingredient in stock" << endl;
									setColor(14);
									continue;
								}
							}

							else if (choise == '2')
							{
								type = "pcs";
								cout << "Enter the name of ingredient: ";
								getline(cin, name);
								system("cls");
								int index = restaurant.SearchIngredient(name, type);

								if (index != -1)
								{
									cout << endl;
									restaurant.ShowIngredientPcs(index);
									cout << endl;
								}
								else {
									setColor(12);
									cout << "There is not this ingredient in stock" << endl;
									setColor(14);
									continue;
								}
							}

							else if (choise == '3') {
								system("cls");
								break;
							}

							else {
								system("cls");
								setColor(12);
								cout << "Wrong Choice!!!" << endl;
								setColor(14);
								continue;
							}

						}
					
					}

					else if (choise == '6') {
						system("cls");
						break;
					}

					else {

						setColor(12);
						cout << "Wrong Choice!!" << endl;
						setColor(14);
					}

					}
			
				break;

				case '3':
					system("cls");
					restaurant.showBalance();
					break;

				case '4':

					double adding;
					cout << "Enter the amount of money you want to add: " << endl;
					cout << "\n> ";
					cin >> adding;
					cin.ignore();
					system("cls");
					try{
					restaurant.addBalance(adding);
					restaurant.saveData();
					}
					catch (const string& s) {
						setColor(12);cout << s << endl<<endl;setColor(14);
						continue;
					}
					setColor(10);
					cout <<"$ " << adding << " added balance successfully" << endl;
					setColor(14);
					break;
				case '5':
					running = false;
					break;
				default:
					setColor(12);
					cout << "Wrong Choice!!" << endl;
					setColor(14);
					break;
				}			
			}
		}

			else {
				setColor(12);
				cout << "Username or password is wrong!!!" << endl;
				setColor(14);
			}
			}

		else if (choise == '2') {
		
			while (1) {
				setColor(14);
				cout << "1. Sign in" << endl;
				cout << "2. Register" << endl;
				cout << "3. Back" << endl << endl;
				cout << "> ";
				setColor(14);
				cin >> choise;
				cin.ignore();
				system("cls");
				if (choise=='1')
				{
					string username, password;

					cout << "Enter username: ";
					getline(cin, username);
					cout << "Enter password: ";
					getline(cin, password);
					system("cls");
					int indexUser = restaurant.SearchUser(username);

					if (indexUser==-1)
					{
						setColor(12);
						cout << "Username or password is wrong" << endl; continue;
						setColor(14);
					}

					if (restaurant.getPassword(indexUser)!=password)
					{
						setColor(12);
						cout << "Username or password is wrong" << endl; continue;
						setColor(14);
					}
					setColor(11);
					cout << "Welcome to the VALHALLA restaurant " << username << endl << endl;
					setColor(14);
					while (true)
					{
						setColor(14);
						cout << "1. Show Menu" << endl;
						cout << "2. Add to Cart" << endl;
						cout << "3. See Your Cart" << endl;
						cout << "4. See Your History" << endl;
						cout << "5. Exit" << endl;
						setColor(14);
						cout << "\n> ";
						cin >> choise;
						cin.ignore();
						system("cls");
						if (choise=='1')
						{
							cout << endl;
							restaurant.ShowMenu();
							cout << endl;
						}

						else if (choise == '2') {
						
							while(1){
								setColor(14);
								cout << "1. Add meal" << endl;
								cout << "2. Add Drink" << endl;
								cout << "3. Finish" << endl;
								setColor(14);
								cout << "\n> ";
								cin >> choise;
								cin.ignore();
								system("cls");

							if (choise=='1') {

								string nameMeal;
								int howManyMeal;
								string type;
								setColor(14);
								cout << "1. Hot meal\n2. Cold meal\n\n> ";
								setColor(14);
								getline(cin, type); 
								system("cls");
								if (type=="1")
								{
									type = "hot";
								}
								else if (type == "2") {
								
									type = "cold";
								}
								else {
									setColor(12);
									cout << "Wrong choice" << endl;
									setColor(14);
									continue;
								}

								cout << "Enter name of meal: ";
								getline(cin,nameMeal);
								
								int indexMeal = restaurant.SearchMeal(nameMeal);

								if (indexMeal==-1)
								{
									system("cls");
									setColor(12);
									cout << "There is no this meal in menu or it is out of stock." << endl;
									setColor(14);
									continue;
								}

								cout << "How many portions you want: ";
								cin >> howManyMeal;
								cin.ignore();
								system("cls");
								if (!restaurant.checkIng(nameMeal, howManyMeal))
								{
									setColor(12);
									cout << "Sorry There is not enough ingredients for this meal for today." << endl;
									setColor(14);
									continue;
								}						
								try{
								Meal cartMeal(nameMeal,restaurant.getPriceofMeal(indexMeal),type);

								cartMeal.setHowMany(howManyMeal);
								setColor(10);
								cout << "\nAdded to cart successfully\n" << endl;
								setColor(14);
								restaurant.addMealCart(cartMeal);	
								}
								catch (const string& s) {
									setColor(12);cout << s << endl<<endl;setColor(14);
									continue;
								}
							}

							else if (choise == '2') {
							
								string type;
								string nameDrink;
								int howManyDrink;
								setColor(14);
								cout << "1. Hot Drink\n2. Cold Drink\n\n> ";
								setColor(14);
								getline(cin, type);
								system("cls");

								if (type == "1")
								{
									cout << "Enter name of drink: ";
									getline(cin, nameDrink);

									int indexDrink = restaurant.SearchHotDrink(nameDrink);

									if (indexDrink == -1)
									{
										system("cls");
										setColor(12);
										cout << "There is no this Drink in menu or it is out of stock." << endl;
										setColor(14);
										continue;
									}
									cout << "How many portions you want: ";
									cin >> howManyDrink;
									cin.ignore();
									system("cls");
									try{
									HotDrink cartHotDrink(nameDrink, restaurant.getPriceofHotDrink(indexDrink));
									cartHotDrink.setHowMany(howManyDrink);
									setColor(10);
									cout << "\nAdded to cart successfully\n" << endl;
									setColor(14);
									restaurant.addHotDrinkCart(cartHotDrink);
									}
									catch (const string& s) {
										setColor(12);cout << s << endl<<endl;setColor(14);
										continue;
									}
								}

								else if (type == "2") {

									cout << "Enter name of drink: ";
									getline(cin, nameDrink);

									int indexDrink = restaurant.SearchColdDrink(nameDrink);

									if (indexDrink == -1)
									{
										system("cls");
										setColor(12);
										cout << "There is no this Drink in menu or it is out of stock." << endl;
										setColor(14);
										continue;
									}
									cout << "How many portions you want: ";
									cin >> howManyDrink;
									cin.ignore();
									system("cls");
									try{
									ColdDrink cartColdDrink(nameDrink, restaurant.getPriceofColdDrink(indexDrink));
									cartColdDrink.setHowMany(howManyDrink);
									setColor(10);
									cout << "\nAdded to cart successfully\n" << endl;
									setColor(14);
									restaurant.addColdDrinkCart(cartColdDrink);
									}
									catch (const string& s) {
										setColor(12);cout << s << endl<<endl;setColor(14);
										continue;
									}
								}

								else {
									setColor(12);
									cout << "Wrong choice" << endl;
									setColor(14);
									continue;
								}																								
							}
							
							else if (choise == '3') { 
								break; 
							}

							else { 
								setColor(12);
								cout << "Wrong Choice" << endl;
								setColor(14);
								continue; 
								
							}
							} 							

						}

						else if (choise == '3') {
							cout << endl;
							restaurant.ShowCart();
							cout << endl;

							while (true) {
								setColor(14);
								cout << "\n1. Finish and Pay" << endl;
								cout << "2. Edit Cart" << endl;
								cout << "3. Back" << endl;
								setColor(14);
								cout << "\n> ";
								cin >> choise;
								cin.ignore();

								system("cls");

								if (choise == '1') {
									if (restaurant.isCartEmpty()) {
										setColor(12);
										cout << "Your cart is empty!" << endl;
										setColor(14);
										continue;
									}

									if (!restaurant.removeFromStock()) {
										setColor(12);
										cout << "Payment aborted: could not remove items from stock. Please review your cart or contact admin." << endl;
										setColor(14);
										continue; 
									}
									try{
									restaurant.addBalance(restaurant.getCartTotalPayment());
									restaurant.addCartToUser(indexUser);
									restaurant.saveData();
									restaurant.clearCart();
									}
									catch (const string& s) {
										setColor(12);cout << s << endl<<endl;setColor(14);
										continue;
									}
									setColor(10);
									cout << "\nPayment successful. Thank you for your purchase!\n" << endl;
									setColor(14);
									break;
								}

								else if (choise == '2') {
									while (true) {
										system("cls"); setColor(14);
										cout << "Editing Your Cart" << endl;
										setColor(14);
										restaurant.ShowCart();
										setColor(14);
										cout << "\n1. Change quantity" << endl;
										cout << "2. Remove item" << endl;
										cout << "3. Clear entire cart" << endl;
										cout << "4. Back" << endl;
										setColor(14);
										cout << "\n> ";
										cin >> choise;
										cin.ignore();
										system("cls");
										if (choise == '1') {
											string itemName;
											int newQty;
											cout << "Enter item name to edit: ";
											getline(cin, itemName);
											cout << "Enter new quantity: ";
											cin >> newQty;
											cin.ignore();
											system("cls");
											try{
											if (!restaurant.updateCartQuantity(itemName, newQty)) {
												setColor(12);
												cout << "Item not found in cart! or Not Enough ingredient!" << endl;
												setColor(14);
											}
											else {
												setColor(10);
												cout << "Quantity updated successfully!" << endl;
												setColor(14);
											}
											}
											catch (const string& s) {
												setColor(12);cout << s << endl<<endl;setColor(14);
												continue;
											}
										}

										else if (choise == '2') {
											string itemName;
											cout << "Enter item name to remove: ";
											getline(cin, itemName);
											system("cls");
											if (!restaurant.removeItemFromCart(itemName)) {
												setColor(12);
												cout << "Item not found in cart!" << endl;
												setColor(14);
											}
											else {
												setColor(10);
												cout << "Item removed successfully!" << endl;
												setColor(14);
											}
										}
										else if (choise == '3') {
											restaurant.clearCart(); setColor(10);
											cout << "Cart cleared successfully!" << endl;
											setColor(14);
										}
										else if (choise == '4') {
											break;
										}
										else {
											setColor(12);
											cout << "Wrong choice!" << endl;
											setColor(14);
										}
									}
								}

								else if (choise == '3') {
									break;
								}
								else {
									setColor(12);
									cout << "Wrong choice!" << endl;
									setColor(14);
}
							}
}

						else if (choise == '4') {
						
							cout << endl;
							restaurant.ShowCartHistory(indexUser);
							cout << endl;
						}

						else if (choise == '5') {
							break;
						}
						else {
							setColor(12);
							cout << "Wrong Choice!!"<<endl;
							setColor(14);
							continue;
						}
					}
				}

				else if (choise == '2') {
				
					string username, password, confirmpass;

					cout << "Enter username: ";
					getline(cin, username);
					

					if (restaurant.SearchUser(username)!=-1)
					{
						system("cls");
						setColor(12);
						cout << "This user already exists" << endl;
						setColor(14);
						continue;
					}

					cout << "Enter password: ";
					getline(cin, password);

					cout << "Confirm password: ";
					getline(cin, confirmpass);
					system("cls");
					if (password!=confirmpass)
					{
						setColor(12);
						cout << "Passwords do not match!!" << endl;
						setColor(14);
						continue;
					}
					try{
					User user(username, password);

					restaurant.addUser(user);
					restaurant.saveData();
					}
					catch (const string& s) {
						setColor(12);cout << s << endl<<endl;setColor(14);
						continue;
					}
					setColor(10);
					cout << "\nRegistered Succesfully" << endl;
					setColor(14);
}

				else if (choise == '3') {
					break;
				}
			
			}
		
		}

		else if (choise == '3') {
			break;
		}
		else {
			setColor(12);
			cout << "Wrong Choice!!!" << endl;
			setColor(14);
}
		

	}

}