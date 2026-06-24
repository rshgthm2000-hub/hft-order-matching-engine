// You Do NOT Suppose to Change the Starter Template except the Mentioned Parts.
// But if you do then I'm not responsible for your failed testcases.
// It is a Very Easy to do Lab Assignment. Best of Luck...

#include<bits/stdc++.h>

using namespace std;

struct Order {
    string user;
    int qty;
    double price;
      int time; 
};

class Book {
public:
    string ticker;
    vector<Order> buy, sell;
    Book(string t) : ticker(t) {}
};

int find_idx(const vector<Book>& comp , const string &s){
    for(int i =0 ;i < comp.size() ; i++){
        if(comp[i].ticker == s){
            return i ;
        }
    }
    return -1;
}
auto comparator (Book &a , Book &b){
        return a.ticker < b.ticker;
    };
void part1() {
    string file;
    cin >> file;
    cin.ignore(1000, '\n');
    // Write your Solution Below
    ifstream fil(file);
    string line;
    if(!fil.is_open()){
        cout<<"FIle is not opened\n";
        return ;
    }
    
    vector<Book>comp;
    while(getline(fil , line)){
       stringstream ss(line);
        string Type,UserName,CompanyTicker,Quantities,Price ;
        getline(ss ,Type , ',');
        getline(ss ,UserName , ',');
        getline(ss ,CompanyTicker , ',');
        getline(ss ,Quantities , ',');
        getline(ss ,Price , ',');

        int idx = find_idx(comp , CompanyTicker);
        if(idx == -1){
            Book temp(CompanyTicker);
            if(Type == "BUY"){
                Order x ;
                x.user = UserName ;
                x.qty = stoi(Quantities);
                x.price = stoi(Price);
                temp.buy.push_back(x);
            }
            else{
                Order x ;
                x.user = UserName ;
                x.qty = stoi(Quantities);
                x.price = stoi(Price);
                temp.sell.push_back(x);
            }
            comp.push_back(temp);
        }else{
            if(Type == "BUY"){
                Order x;
                x.user = UserName ;
                x.qty = stoi(Quantities);
                x.price = stoi(Price);
                comp[idx].buy.push_back(x);
            }else{
                Order x;
                 x.user = UserName ;
                x.qty = stoi(Quantities);
                x.price = stoi(Price);
                comp[idx].sell.push_back(x);
            }
        }
    }
    fil.close();
    
    sort(comp.begin() , comp.end() , comparator);
    for(int i =0 ;i< comp.size() ;i++){
        cout<<comp[i].ticker<<" "<<comp[i].buy.size() + comp[i].sell.size()<<endl;
    }
}

void part2() {
    string file;
    cin >> file;
    // Write your Solution Below
    vector<string> names;
    string s;
    while(cin>>s){
        names.push_back(s);
    }
    cin.ignore(1000, '\n');
    
    ifstream fil(file);
    string line;
    if(!fil.is_open()){
        cout<<"FIle is not opened\n";
        return ;
    }
    vector<Book>comp;
     while(getline(fil , line)){
        stringstream ss(line);
        string Type,UserName,CompanyTicker,Quantities,Price ;
        getline(ss ,Type , ',');
        getline(ss ,UserName , ',');
        getline(ss ,CompanyTicker , ',');
        getline(ss ,Quantities , ',');
        getline(ss ,Price , ',');

         int idx = find_idx(comp , UserName);

         if(idx == -1){
            Book temp(UserName);
            if(Type == "BUY"){
                Order x ;
                x.user = CompanyTicker ;
                x.qty = stoi(Quantities);
                x.price = stoi(Price);
                temp.buy.push_back(x);
            }
            else{
                Order x ;
                x.user = CompanyTicker ;
                x.qty = stoi(Quantities);
                x.price = stoi(Price);
                temp.sell.push_back(x);
            }
            comp.push_back(temp);
        }
        else{
            if(Type == "BUY"){
                Order x;
                 x.user = CompanyTicker ;
                x.qty = stoi(Quantities);
                x.price = stoi(Price);
                comp[idx].buy.push_back(x);
            }else{
                Order x;
                 x.user = CompanyTicker ;
                x.qty = stoi(Quantities);
                x.price = stoi(Price);
                comp[idx].sell.push_back(x);
            }
        }
     }
     fil.close();
     for(int i =0 ;i < names.size() ;i++){
        int idx =  find_idx(comp , names[i]);
        if(idx == -1){
            cout<<names[i]<<" 0\n";
            continue;
        }
        int qnt =0 ;
        for(int j =0 ;j < comp[idx].buy.size() ;j++){
            qnt += comp[idx].buy[j].qty;
        }
        for(int j =0 ;j < comp[idx].sell.size() ;j++){
            qnt += comp[idx].sell[j].qty;
        }
        cout<<names[i]<<" "<<qnt<<endl;
     }
}

void part3() {
    string filePath = "./actual_output/Q1/CSV/";
    string YOUR_ROLL_NUMBER = "CS24B010"; // Change with Your Actual Roll Number
    string fileName;
    cin >> fileName;
    string file = filePath + YOUR_ROLL_NUMBER + "/" + fileName;
    cin.ignore(1000, '\n');
    // Write your Solution Below
    ofstream out(file);

    // CSV header
    out << "Ticker,Seller,Buyer,Qty,Price,Time\n";

    // formatting
    out << fixed << setprecision(2);

    vector<Book> comp;

    int currentTime = 0;       // transaction time
    int globalOrderTime = 0;   // order arrival time

    string type;

    while (cin >> type) {

        string username, ticker;
        int qty;
        double price;

        cin >> username >> ticker >> qty >> price;

        int idx = find_idx(comp, ticker);

        if (idx == -1) {
            comp.push_back(Book(ticker));
            idx = comp.size() - 1;
        }

        if (type == "BUY") {

            // sort SELL: lowest price first, then earliest time
            sort(comp[idx].sell.begin(), comp[idx].sell.end(),
                 [](Order &a, Order &b) {
                     if (a.price == b.price) return a.time < b.time;
                     return a.price < b.price;
                 });
         int i = 0;
            while (i < comp[idx].sell.size() && qty > 0) {
                if (comp[idx].sell[i].price <= price) {

                    int tradedQty = min(qty, comp[idx].sell[i].qty);

                    // log transaction
                    out << ticker << ","
                        << comp[idx].sell[i].user << ","
                        << username << ","
                        << tradedQty << ","
                        << comp[idx].sell[i].price << ","
                        << currentTime++ << "\n";

                    qty -= tradedQty;
                    comp[idx].sell[i].qty -= tradedQty;

                    if (comp[idx].sell[i].qty == 0)
                        comp[idx].sell.erase(comp[idx].sell.begin() + i);
                    else
                        i++;

                } else break;
            }

            // remaining BUY order
            if (qty > 0) {
                Order x{username, qty, price, globalOrderTime++};
                comp[idx].buy.push_back(x);
            }
        }
       else { // SELL

            // sort BUY: highest price first, then earliest time
            sort(comp[idx].buy.begin(), comp[idx].buy.end(),
                 [](Order &a, Order &b) {
                     if (a.price == b.price) return a.time < b.time;
                     return a.price > b.price;
                 });

            int i = 0;
            while (i < comp[idx].buy.size() && qty > 0) {
                if (comp[idx].buy[i].price >= price) {

                    int tradedQty = min(qty, comp[idx].buy[i].qty);

                    // log transaction
                    out << ticker << ","
                        << username << ","
                        << comp[idx].buy[i].user << ","
                        << tradedQty << ","
                        << price << ","
                        << currentTime++ << "\n";

                    qty -= tradedQty;
                    comp[idx].buy[i].qty -= tradedQty;

                    if (comp[idx].buy[i].qty == 0)
                        comp[idx].buy.erase(comp[idx].buy.begin() + i);
                    else
                        i++;

                } else break;
            }
             if (qty > 0) {
                Order x{username, qty, price, globalOrderTime++};
                comp[idx].sell.push_back(x);
            }
        }
    }

    out.close();
     
}

int main() {
    string part;
    cin >> part;
    
    if (part == "P1") {
        part1();
    } else if (part == "P2") {
        part2();
    } else {
        part3();
    }
    return 0;
}
