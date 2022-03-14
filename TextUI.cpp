#include "TextUI.h"

TextUI::TextUI() {
  std::vector<std::string> subcategories;
  subcategories.push_back("Camera");
  subcategories.push_back("Television");
  subcategories.push_back("Phone");
  _productCategories.insert(std::make_pair("Electronics", subcategories));
  subcategories.clear();
  subcategories.push_back("Monitors");
  subcategories.push_back("Mouse");
  subcategories.push_back("Keyboard");
  _productCategories.insert(std::make_pair("Computers", subcategories));
  subcategories.clear();
  subcategories.push_back("Basketball");
  subcategories.push_back("Football");
  subcategories.push_back("Baseball");
  _productCategories.insert(std::make_pair("Sports", subcategories));
  subcategories.clear();
  subcategories.push_back("MenClothing");
  subcategories.push_back("WomenClothing");
  subcategories.push_back("Necklaces");
  _productCategories.insert(std::make_pair("Clothing", subcategories));
  subcategories.clear();
  subcategories.push_back("Textbooks");
  subcategories.push_back("Novels");
  subcategories.push_back("Cookbooks");
  _productCategories.insert(std::make_pair("Books", subcategories));
  subcategories.clear();
}

std::string TextUI::DisplayRoleChoice() {
  std::string role;

  std::cout << "Welcome to BidToBuy. Choose a role to log in (buyer/seller): ";
  std::cin >> role;
  while (role != "buyer" && role != "seller") {
    std::cout << "Please enter a valid input. Choose a role to log in (buyer/seller): ";
    std::cin >> role;
  }
  return role;
}

void TextUI::LoadInUserData(std::string filename) {
  std::fstream file(filename, std::ios::in);
  std::string line;
  if (file.is_open()) {
    while (getline(file, line)) {
      std::stringstream str(line);
      std::string userType;
      getline(str, userType, ',');
      std::string username;
      getline(str, username, ',');
      std::string address;
      getline(str, address, ',');
      std::string phoneNum;
      getline(str, phoneNum, ',');
      std::string accountBalance;
      getline(str, accountBalance, ',');
      std::string rateTotal;
      getline(str, rateTotal, ',');
      std::string rateCount;
      getline(str, rateCount, ',');
      MakeNewUser(username, address, stol(phoneNum), stod(accountBalance), stol(rateTotal), stoi(rateCount), userType);
    }
  }
}

void TextUI::LoadInBidsData(std::string filename) {
  std::fstream file(filename, std::ios::in);
  std::string line;
  if (file.is_open()) {
    while (getline(file, line)) {
      std::stringstream str(line);
      std::string productName;
      getline(str, productName, ',');
      std::string subcategory;
      getline(str, subcategory, ',');
      std::string seller;
      getline(str, seller, ',');
      std::string buyer;
      getline(str, buyer, ',');
      std::string quality;
      getline(str, quality, ',');
      std::string basePrice;
      getline(str, basePrice, ',');
      std::string bid;
      getline(str, bid, ',');
      if (subcategory == "Camera") _historyOrders.push_back(ProductFactory::AddCamera(productName, stod(basePrice), quality, seller, std::make_pair(stod(bid), buyer)));
      if (subcategory == "Television") _historyOrders.push_back(ProductFactory::AddTelevision(productName, stod(basePrice), quality, seller, std::make_pair(stod(bid), buyer)));
      if (subcategory == "Phone") _historyOrders.push_back(ProductFactory::AddPhone(productName, stod(basePrice), quality, seller, std::make_pair(stod(bid), buyer)));
      if (subcategory == "Monitors") _historyOrders.push_back(ProductFactory::AddMonitors(productName, stod(basePrice), quality, seller, std::make_pair(stod(bid), buyer)));
      if (subcategory == "Mouse") _historyOrders.push_back(ProductFactory::AddMouse(productName, stod(basePrice), quality, seller, std::make_pair(stod(bid), buyer)));
      if (subcategory == "Keyboard") _historyOrders.push_back(ProductFactory::AddKeyboard(productName, stod(basePrice), quality, seller, std::make_pair(stod(bid), buyer)));
      if (subcategory == "Basketball") _historyOrders.push_back(ProductFactory::AddBasketball(productName, stod(basePrice), quality, seller, std::make_pair(stod(bid), buyer)));
      if (subcategory == "Football") _historyOrders.push_back(ProductFactory::AddFootball(productName, stod(basePrice), quality, seller, std::make_pair(stod(bid), buyer)));
      if (subcategory == "Baseball") _historyOrders.push_back(ProductFactory::AddBaseball(productName, stod(basePrice), quality, seller, std::make_pair(stod(bid), buyer)));
      if (subcategory == "MenClothing") _historyOrders.push_back(ProductFactory::AddMenClothing(productName, stod(basePrice), quality, seller, std::make_pair(stod(bid), buyer)));
      if (subcategory == "WomenClothing") _historyOrders.push_back(ProductFactory::AddWomenClothing(productName, stod(basePrice), quality, seller, std::make_pair(stod(bid), buyer)));
      if (subcategory == "Necklaces") _historyOrders.push_back(ProductFactory::AddNecklaces(productName, stod(basePrice), quality, seller, std::make_pair(stod(bid), buyer)));
      if (subcategory == "Textbooks") _historyOrders.push_back(ProductFactory::AddTextbooks(productName, stod(basePrice), quality, seller, std::make_pair(stod(bid), buyer)));
      if (subcategory == "Novels") _historyOrders.push_back(ProductFactory::AddNovels(productName, stod(basePrice), quality, seller, std::make_pair(stod(bid), buyer)));
      if (subcategory == "Cookbooks") _historyOrders.push_back(ProductFactory::AddCookbooks(productName, stod(basePrice), quality, seller, std::make_pair(stod(bid), buyer)));
    }
  }
}

std::string TextUI::LogInUsername(std::string role) {
  std::string username;

  std::cout << "Username: ";
  std::cin >> username;
  try {
    if (role == "seller") {
      if (GetSeller(username) == NULL) {
        CreateNewAccount(role, username);
      }
    } else {
      if (GetBuyer(username) == NULL) {
        CreateNewAccount(role, username);
      }
    }
  } catch (std::exception&) {
    throw std::exception();
  }
  return username;
}

void TextUI::CreateNewAccount(std::string role, std::string username) {
  std::string option;

  std::cout << "The username is not found in the " << role << " list." << std::endl
            << "Create a new account? (c)" << std::endl
            << "Exit the program? (e)" << std::endl
            << "Please enter an option (c/e): ";
  std::cin >> option;
  while (option != "c" && option != "e") {
    std::cout << "Please enter a valid option. Enter your option again (c/e): ";
    std::cin >> option;
  }
  if (option == "c") {
    std::string address;
    long phoneNum;
    double accountBalance;

    std::cout << "Address: ";
    std::cin >> address;
    std::cout << "Phone Number: ";
    std::cin >> phoneNum;
    std::cout << "Add money to account: ";
    std::cin >> accountBalance;

    MakeNewUser(username, address, phoneNum, accountBalance, 0.0, 0, role);
  }
  if (option == "e") {
    throw std::exception();
  }
}

void TextUI::DisplayForBuyer(std::string name) {
  Buyer* b = GetBuyer(name);

  std::string option;
  std::cout << "Please choose from the following list of buyer options: " << std::endl;
  std::cout << "1. View/Bid-On Products" << std::endl;
  std::cout << "2. View/Send Messages" << std::endl;
  std::cout << "3. Check Account Balance" << std::endl;
  std::cout << "4. Update User Info" << std::endl;
  std::cout << "5. View Bid History" << std::endl;
  std::cout << "6. View Purchased Products" << std::endl;
  std::cout << "7. Exit the program?" << std::endl;
  std::cin >> option;

  while (option != "1" && option != "2" && option != "3" && option != "4" && option != "5" && option != "6" && option != "7") {
    std::cout << "Please enter a valid option. Enter your option again (1-7): ";
    std::cin >> option;
  }

  if (option == "1") {
    std::cout << "Here's a list of all currently biddable products: " << std::endl;
  }
  if (option == "2") {
    std::cout << "Messages" << std::endl;
  }
  if (option == "3") {
    std::cout << "Your account balance is: $" << b->GetAccountBalance() << std::endl;
  }
  if (option == "4") {
  }
  if (option == "5") {
  }
  if (option == "6") {
  }
  if (option == "7") {
    throw std::exception();
  }
}

void TextUI::DisplayForSeller(std::string name) {
  Seller* b = GetSeller(name);

  if (!b->MessageboxIsEmpty()) {
    std::cout << "You have new message(s)!" << std::endl;
  }

  std::string option;
  std::cout << "Please choose from the following list of seller options: " << std::endl;
  std::cout << "1. Post a product for sale" << std::endl;
  std::cout << "2. View/Send messages" << std::endl;
  std::cout << "3. Check account balance" << std::endl;
  std::cout << "4. Rate a buyer" << std::endl;
  std::cout << "5. Update user info" << std::endl;
  std::cout << "6. View product list" << std::endl;
  std::cout << "7. Close bid on a product" << std::endl;
  std::cout << "8. Exit the program" << std::endl;
  std::cin >> option;

  while (option != "1" && option != "2" && option != "3" && option != "4" && option != "5" && option != "6" && option != "7" && option != "8") {
    std::cout << "Please enter a valid option. Enter your option again (1-8): ";
    std::cin >> option;
  }

  if (option == "1") {
  }
  if (option == "2") {
  }
  if (option == "3") {
  }
  if (option == "4") {
  }
  if (option == "5") {
  }
  if (option == "6") {
  }
  if (option == "7") {
  }
  if (option == "8") {
    throw std::exception();
  }
}

void TextUI::CheckMessagebox(std::string role, std::string name) {
  if (role == "buyer") {
    if (!GetBuyer(name)->MessageboxIsEmpty()) {
      std::cout << "You have new message(s)!";
    }
  } else {
    if (!GetSeller(name)->MessageboxIsEmpty()) {
      std::cout << "You have new message(s)!";
    }
  }
  std::cout << std::endl;
}

void TextUI::ViewProductsForSale() {
  for (std::map<int, Product*>::iterator i = _products.begin(); i != _products.end(); i++) {
    std::cout << "product id: " << i->first << ", product name: " << i->second->GetProductName() << std::endl;
  }
}

Seller* TextUI::GetSeller(std::string name) {
  if (_sellers.find(name) != _sellers.end()) {
    return _sellers[name];
  } else {
    return NULL;
  }
}

Buyer* TextUI::GetBuyer(std::string name) {
  if (_buyers.find(name) != _buyers.end()) {
    return _buyers[name];
  } else {
    return NULL;
  }
}

bool TextUI::MakeNewUser(std::string name, std::string address, long phoneNum, double accountBalance, double rateTotal, int rateCount, std::string userType) {
  if (userType == "seller") {
    _sellers.insert(std::make_pair(name, new Seller(name, address, phoneNum, accountBalance, rateTotal, rateCount)));
    return true;
  } else if (userType == "buyer") {
    _buyers.insert(std::make_pair(name, new Buyer(name, address, phoneNum, accountBalance, rateTotal, rateCount)));
    return true;
  } else {
    return false;
  }
}

bool TextUI::AddNewProduct(Product* p, Seller* seller) {
  int id = GetID();
  if (_products.find(id) == _products.end()) {
    _products.insert(std::make_pair(id, p));
    seller->AddProductForSale(id, p);
    return true;
  } else {
    return false;
  }
}

bool TextUI::AddBidToProduct(int id, double bid, Buyer* buyer) {
  if (_products.find(id) != _products.end()) {
    buyer->AddBidToProduct(_products[id], bid);
    _products[id]->SetCurrentBid(bid, buyer->GetUsername());
    return true;
  } else {
    std::cout << "The product id is not in the list." << std::endl;
    return false;
  }
}

int TextUI::id = 0;
