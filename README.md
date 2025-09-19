**Stock Market Simulation in C**

## 📌 Overview  
This project implements a simplified stock market system in C.  

The program models:  
- **People** who can submit buy/sell requests.  
- **Companies** listed in the stock market.  
- **Order books** for each company, storing buy and sell requests in sorted linked lists.  
- **Matching engine** that executes trades when compatible buy/sell orders meet.  

The main goals are to practice **structs**, **dynamic memory allocation**, **arrays**, and **linked lists** in C.

---

## 📂 Data Structures  
The system uses the following key structures:  
- `Person` → Represents an individual (name, unique ID).  
- `Company` → Represents a listed company (name, ticker, display order).  
- `Request` → Represents a buy/sell request (person, amount, price).  
- `RequestNode` → Linked list node storing a request.  
- `StockMarketEntry` → Holds all buy/sell requests for one company.  
- `StockMarket` → Collection of all companies and their order books.  

---

## 🛠️ Implemented Functions  

- `Person* create_person(char *name, int id);`  
- `Company* create_company(char *name, char *abbr, int order);`  
- `void add_company_to_market(StockMarket *market, Company *company);`  
- `void insert_buy_request(StockMarket *market, Person **people, int people_count, char *buyer_name, char *company_abbr, int amount, float price);`  
- `void insert_sell_request(StockMarket *market, Person **people, int people_count, char *seller_name, char *company_abbr, int amount, float price);`  
- `void print_market(StockMarket *market);`  


