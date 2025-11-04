#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include<fstream>
#include<sstream>

using namespace std;

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

public:
	Meal(string name, double price,string type) {

		setName(name);
		setPrice(price);
		setType(type);
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

	int SearchIng(string& name, string& type) {
	
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

	string getName()const noexcept {

		return name;

	}
	double getPrice()const noexcept {
		return price;
	}
	void Show() {
		cout << this->getName() << " - $" << this->getPrice() << endl;
	}
};

class ColdDrink{
	string name;
	double price;
	string type = "cold";
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

	string getName()const noexcept {

		return name;

	}
	double getPrice()const noexcept {
		return price;
	}

	void Show() {
		cout << this->getName() << " - $" << this->getPrice() << endl;
	}
};

class Cart {

	vector<Meal> meals;
	vector<HotDrink> hotdrinks;
	vector<ColdDrink> colddrinks;

};

class User {

	string username;
	string password;

	void setPassword(string& password) {
		if (password.length() < 8)
		{
			throw string("Password must be at least 8 characters!!");
		}
		this->password = password;
	
	}

public:
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

	int SearchMealInMenu(string& name) {
	
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
		cout << "O------------  HOT MEALS  ------------O" << endl;
		for (size_t i = 0; i < hotmeals.size(); i++)
		{
			hotmeals[i].Show();
		}
		cout << "O------------  COLD MEALS  ------------O" << endl;
		for (size_t i = 0; i < coldmeals.size(); i++)
		{
			coldmeals[i].Show();
		}
		
		cout << "O------------  COLD DRINKS  ------------O" << endl;
		for (size_t i = 0; i < colddrinks.size(); i++)
		{
			colddrinks[i].Show();
		}
		cout << "O------------  HOT DRINKS  ------------O" << endl;
		for (size_t i = 0; i < hotdrinks.size(); i++)
		{
			hotdrinks[i].Show();
		}
	
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
};

class Restaurant {

	vector<User> users;
	Menu menu;
	Cart cart;
	Stock stock;

public:

	Restaurant() {
		try {
			this->loadData();
		}
		catch (const string& msg) {
			cout << msg << endl;
			this->saveData();
		}

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
		stock.saveDatatoStock();
		menu.saveDatatoMenu();
		menu.saveDatatoMeals();
		saveUsers();

	}

	void loadData() {
		stock.loadDatafromStock();
		menu.loadDataFromMenu();
		menu.loadDataFromMeals();
		loadUsers();
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

	int SearchMeal(string& name) {

		return menu.SearchMealInMenu(name);

	}

	int SearchIngredient(string& name, string& type) {
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

	double getIngredientMassKG(int index) {
		return stock.getIngMassKG(index);

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

};


void main() {

	Restaurant restaurant;

	cout << " __        __   _                               " << endl;
	cout << " \\ \\      / /__| | ___ ___  _ __ ___   ___ " << endl;
	cout << "  \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\"<<endl;
	cout << "   \\ V  V /  __/ | (_| (_) | | | | | |  __/ " << endl;
	cout << "    \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|"<< endl;
	cout << endl;
	cout << "                             T O   V A L H A L L A" << endl << endl << endl;
	char choise;
	while (true)
	{
		cout << "Enter the restaurant system" << endl << endl;
		cout << "1. Admin Panel" << endl;
		cout << "2. User Panel" << endl;
		cout << "3. Exit" << endl;
		cout << "\n>";

		cin >> choise;
		cin.ignore();
		if (choise=='1'){

			system("cls");
			string username, password;
			
			cout << "Enter username: ";
			getline(cin, username);
			cout << "Enter password: ";
			getline(cin, password);

			if (username=="admin"&&password=="valhalla")
			{
				bool running = true;
				system("cls");
				cout << "Welcome to the system BOSS" << endl<<endl;
				while(running){
				cout << "Choose where do you want to make change: \n" << endl;
				cout << "1. Menu" << endl;
				cout << "2. Stock" << endl;
				cout << "3. Back" << endl;
				cout << "\n> ";
				cin >> choise;
				cin.ignore();
				system("cls");

				switch (choise)  {

				case '1':
					while(true){
						
						cout << "1. Show Menu Items" << endl;
						cout << "2. Add New Meal to Menu" << endl;
						cout << "3. Add New Drink to Menu" << endl;
						cout << "4. Change price of Menu item" << endl;
						cout << "5. Delete menu item" << endl;
						cout << "6. Search and show info menu item" << endl;
						cout << "7. Back" << endl<<endl;
						cout << "> ";

					cin >> choise;
					cin.ignore();

					if (choise=='1')
					{
						system("cls");
						restaurant.ShowMenu();

					}

					else if (choise == '2') {
					
						string type;
						string mealname;
						double price;
						cout << "Type of Meal: " << endl;
						cout << "1. Hot" << endl;
						cout << "2. Cold" << endl;
						cout << "> ";

						getline(cin, type);

						if (type=="1")
						{
							type = "hot";
						}
						else if (type == "2") {
							type = "cold";
						}
						else {
							cout << "Wrong choice!!!" << endl;

						}

						cout << "Enter name of meal: ";
						getline(cin, mealname);

						if (restaurant.SearchMeal(mealname) != -1) {
							cout << "There is this meal in Menu already" << endl;
							continue;
						
						}

						cout << "Enter the price of meal: ";
						cin >> price;
						cin.ignore();

						Meal meal(mealname, price,type);

						while(1){
							cout << "1. Add ingredient" << endl;
							cout << "2. Finish" << endl;
							cout << "> ";
							cin >> choise;
							cin.ignore();
							if (choise=='1')
							{
								string ingType;
								string ingName;
								double mass; int count;
								cout << "Ingredient will be by: " << endl;
								cout << "1. kg" << endl;
								cout << "2. pieces" << endl;
								cout << "> ";
								getline(cin, ingType);
								cout << "Enter the ing name: ";
								getline(cin, ingName);



								if (ingType=="1")
								{
									cout << "Enter the amount of ingredient(kg): ";
									cin>> mass;
									cin.ignore();
									IngredientWthKg neededIng(ingName, mass);
									meal.addIngKg(neededIng);
								}
								else if (ingType=="2")
								{
									cout << "Enter the amount of ingredient(pieces): ";
									cin >> count;
									cin.ignore();
									IngredientWthPcs neededIng(ingName, count);
									meal.addIngPcs(neededIng);
								}
								else {							
									cout << "Wrong choice!!!" << endl;
									continue;
								}
							}
							else if (choise == '2') {
								restaurant.addNewMeal(meal);	
								break;
							}
						}
					}

					else if (choise == '3') {
						string type;
						string drinkname;
						double price;
						cout << "Type of Drink: " << endl;
						cout << "1. Hot" << endl;
						cout << "2. Cold" << endl;
						cout << "> ";
						getline(cin, type);

						if (type!="1" && type!="2")
						{
							cout << "Wrong choice!!!" << endl;
							continue;
						}

						cout << "Enter name of drink: ";
						getline(cin, drinkname);
						cout << "Enter the price of drink: ";
						cin >> price;
						cin.ignore();

						if (type=="1")
						{
							HotDrink drink(drinkname, price);
							restaurant.addNewDrink(drink);
						}
						else if (type == "2") {
							ColdDrink drink(drinkname, price);
							restaurant.addNewDrink(drink);
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
							cout << "There is no this item in menu" << endl;
						}
						else {
						
							if (place=="meal")
							{
								
								cout << "Enter new price: $";
								cin >> price;
								cin.ignore();
								restaurant.changePriceMeal(index, price);
							}
							else if (place == "Hotd") {
								cout << "Enter new price: $";
								cin >> price;
								cin.ignore();
								restaurant.changePriceHotDrink(index, price);
							
							}
							else {
								cout << "Enter new price: $";
								cin >> price;
								cin.ignore();
								restaurant.changePriceColdDrink(index, price);

							}
						
						}
						

					}

					else if (choise == '5') {
						string name;
						while (1) {
							cout << "1. Delete Meal" << endl;
							cout << "2. Delete Hot Drink" << endl;
							cout << "3. Delete Cold Drink" << endl;
							cout << "4. Back" << endl;
							cout << "> ";
							cin >> choise;
							cin.ignore();

							if (choise == '1') {
								cout << "Enter the name of unwanted meal: ";
								getline(cin, name);
								int index = restaurant.SearchMeal(name);
								if (index == -1) {
									cout << "There is no such meal in menu\n";
									continue;
								}
								restaurant.DeleteMeal(index);
								cout << "Meal deleted successfully!\n";
							}
							else if (choise == '2') {
								cout << "Enter the name of unwanted Hot Drink: ";
								getline(cin, name);
								int index = restaurant.SearchHotDrink(name);
								if (index == -1) {
									cout << "There is no such Hot Drink in menu\n";
									continue;
								}
								restaurant.DeleteHotDrink(index);
								cout << "Hot drink deleted successfully!\n";
							}
							else if (choise == '3') {
								cout << "Enter the name of unwanted Cold Drink: ";
								getline(cin, name);
								int index = restaurant.SearchColdDrink(name);
								if (index == -1) {
									cout << "There is no such Cold Drink in menu\n";
									continue;
								}
								restaurant.DeleteColdDrink(index);
								cout << "Cold drink deleted successfully!\n";
							}
							else if (choise == '4') {
								break;
							}
							else {
								cout << "Wrong choice!!!" << endl;
								continue;
							}
						}
					
					}

					else if (choise == '6') {
					
						string name;
						int index;

						cout << "Enter the name of menu item: " << endl;
						cout << "> ";
						getline(cin, name);
						index = restaurant.SearchMeal(name);

						if (index != -1)
						{
							restaurant.ShowMealInfo(index);
						}
						else {
							index = restaurant.SearchHotDrink(name);
							if (index != -1)
							{
								restaurant.ShowHotDrinkInfo(index);
							}
							else {
								index = restaurant.SearchColdDrink(name);
								if (index != -1)
								{
									restaurant.ShowColdDrinkInfo(index);
								}
							}
						}

						if (index == -1)
						{
							cout << "There is no this item in menu" << endl;
						}

					}

					else if (choise == '7') {
						break;
					}
					
					else {
					
						cout << "Wrong Choice!!"<<endl;
					}

				}
				break;

				case '2':
					while(1){

					cout << "1. Show Stock Items" << endl;
					cout << "2. Add or Buy New Ingredient" << endl;
					cout << "3. Decrease stock item" << endl;
					cout << "4. Delete stock item" << endl;
					cout << "5. Search and show info stock item" << endl;
					cout << "6. Back" << endl;
					cout << "\n> ";
					cin >> choise;
					cin.ignore();

					if (choise=='1')
					{
						restaurant.ShowStock();
					}

					else if (choise == '2') {
						
						string name;
						double price;

						while (true) {
						
							cout << "Enter the type of ingredient: " << endl << endl;
							cout << "1. Kg" << endl;
							cout << "2. Pieces" << endl;
							cout << "3. Finish adding ingredient" << endl;
							cout << "\n> ";

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
									double newmass = mass + restaurant.getIngredientMassKG(index);
									restaurant.setIngredientMassKg(index, newmass);
									restaurant.saveData();

								}else{

								cout << "Enter the amount of ingredient(KG): ";
								cin >> mass;

								cout << "Enter price per kg: ";
								cin >> price;
								cin.ignore();

								IngredientWthKg ing(name, mass);
								ing.setPrice(price);

								restaurant.addNewIngredientKg(ing);
								restaurant.saveData();
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
									cout << "Enter the amount of ingredient that you want to buy: ";
									cin >> pieces;
									cin.ignore();
									double newpieces = pieces + restaurant.getInredientCountPcs(index);
									restaurant.setIngredientCountPcs(index, newpieces);
									restaurant.saveData();

								} else {

								cout << "Enter the amount of ingredient(Pieces): ";
								cin >> pieces;

								cout << "Enter price per piece: ";
								cin >> price;
								cin.ignore();

								IngredientWthPcs ing(name, pieces);
								ing.setPrice(price);

								restaurant.addNewIngredientPcs(ing);
								restaurant.saveData();
								}
							}
							
							else if (choise == '3') {							
								break;
							}

							else {
								cout << "Wrong Choice!!!" << endl;
								continue;
							}
						
						}
					}

					else if (choise == '3') {
					
						string name;
						double price;
						while (true) {

							cout << "Enter the type of ingredient: " << endl << endl;
							cout << "1. Kg" << endl;
							cout << "2. Pieces" << endl;
							cout << "3. Finish decreasing ingredient" << endl;
							cout << "\n> ";

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
									double newmass = restaurant.getIngredientMassKG(index)-mass;
									restaurant.setIngredientMassKg(index, newmass);
									restaurant.saveData();

								}
								else {

									cout << "There is not this ingredient in stock" << endl;
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
									double newpieces = restaurant.getInredientCountPcs(index)-pieces;
									restaurant.setIngredientCountPcs(index, newpieces);
									restaurant.saveData();

								}
								else {
									cout << "There is not this ingredient in stock" << endl;
									continue;
								}
							}

							else if (choise == '3') {
								break;
							}

							else {
								cout << "Wrong Choice!!!" << endl;
								continue;
							}

						}

					}

					else if (choise == '4') {
					
						string name;

						while (true) {

							cout << "Enter the type of ingredient: " << endl << endl;
							cout << "1. Kg" << endl;
							cout << "2. Pieces" << endl;
							cout << "3. Finish deleting ingredient" << endl;
							cout << "\n> ";

							cin >> choise;
							cin.ignore();
							string type;

							if (choise == '1')
							{
								type = "kg";
								cout << "Enter the name of ingredient: ";
								getline(cin, name);
								int index = restaurant.SearchIngredient(name, type);

								if (index != -1)
								{

									restaurant.DeleteIngredientKG(index);
									restaurant.saveData();

								}
								else {

									cout << "There is not this ingredient in stock" << endl;
									continue;
								}
							}

							else if (choise == '2')
							{
								type = "pcs";
								cout << "Enter the name of ingredient: ";
								getline(cin, name);
								int index = restaurant.SearchIngredient(name, type);

								if (index != -1)
								{

									restaurant.DeleteIngredientPCS(index);
									restaurant.saveData();

								}
								else {

									cout << "There is not this ingredient in stock" << endl;
									continue;
								}
							}

							else if (choise == '3') {
								break;
							}

							else {
								cout << "Wrong Choice!!!" << endl;
								continue;
							}

						}
					}

					else if (choise == '5') {
					
						string name;

						while (true) {

							cout << "Enter the type of ingredient: " << endl << endl;
							cout << "1. Kg" << endl;
							cout << "2. Pieces" << endl;
							cout << "3. Finish" << endl;
							cout << "\n> ";

							cin >> choise;
							cin.ignore();
							string type;

							if (choise == '1')
							{
								type = "kg";
								cout << "Enter the name of ingredient: ";
								getline(cin, name);
								int index = restaurant.SearchIngredient(name, type);

								if (index != -1)
								{

									restaurant.ShowIngredientKg(index);

								}
								else {

									cout << "There is not this ingredient in stock" << endl;
									continue;
								}
							}

							else if (choise == '2')
							{
								type = "pcs";
								cout << "Enter the name of ingredient: ";
								getline(cin, name);
								int index = restaurant.SearchIngredient(name, type);

								if (index != -1)
								{

									restaurant.ShowIngredientPcs(index);

								}
								else {

									cout << "There is not this ingredient in stock" << endl;
									continue;
								}
							}

							else if (choise == '3') {
								break;
							}

							else {
								cout << "Wrong Choice!!!" << endl;
								continue;
							}

						}
					
					}

					else if (choise == '6') {
					
						break;
					}

					else {
					
						cout << "Wrong Choice!!" << endl;
					
					}

					}
			
				break;

				case '3':
					running = false;
					break;
				}			
			}
		}

			else {
			
				cout << "Username or password is wrong!!!" << endl;
				
			}
			}

		else if (choise == '2') {
		
			while (1) {
			
				cout << "1. Sign in" << endl;
				cout << "2. Register" << endl;
				cout << "3. Back" << endl;

				cin >> choise;
				cin.ignore();

				if (choise=='1')
				{

					string username, password;

					cout << "Enter username: ";
					getline(cin, username);
					cout << "Enter password: ";
					getline(cin, password);

					int index = restaurant.SearchUser(username);

					if (index==-1)
					{
						cout << "Username or password is wrong" << endl; continue;

					}

					if (restaurant.getPassword(index)!=password)
					{
						cout << "Username or password is wrong" << endl; continue;
					}

					while (true)
					{
						cout << "Welcome to the VALHALLA restaurant " << username << endl<<endl<<endl;

						cout << "1. Show Menu" << endl;
						cout << "2. Add to Cart" << endl;
						cout << "3. See Your Cart" << endl;
						cout << "4. Exit" << endl;
						cout << "\n> ";

						cin >> choise;
						cin.ignore();
						if (choise=='1')
						{
							restaurant.ShowMenu();
						}
					}



				}
				else if (choise == '2') {
				
					string username, password, confirmpass;

					cout << "Enter username: ";
					getline(cin, username);

					if (restaurant.SearchUser(username)!=-1)
					{
						cout << "This user already exists" << endl;
						continue;
					}

					cout << "Enter password: ";
					getline(cin, password);

					cout << "Confirm password: ";
					getline(cin, confirmpass);
				
					if (password!=confirmpass)
					{
						continue;
					}
					
					User user(username, password);

					restaurant.addUser(user);
					restaurant.saveData();

				}
			
			}
		
		}

		else if (choise == '3') {
			break;
		}
		else {
			cout << "Wrong Choice!!!" << endl;
		}
		

	}

}