#include "mydatastore.h"
#include "util.h"
#include <iostream>

using namespace std;

MyDataStore::~MyDataStore() 
{
    for (auto p : products) 
    {
        delete p;
    }
    for (auto& entry : users) 
    {
        delete entry.second;
    }
}
void MyDataStore::addProduct(Product* p) 
{
    products.insert(p);

    set<string> words = p->keywords();
    for (const string& word : words) 
    {
        keywords[word].insert(p);
    }
}
void MyDataStore::addUser(User* u) 
{
    users[u->getName()] = u;
}
vector<Product*> MyDataStore::search(vector<string>& terms, int type) 
{
    if (terms.empty()) 
    {
        recentHits.clear();
        return recentHits;
    }
    set<Product*> results;
    for (const string& word : terms) 
    {
        set<Product*> matches = keywords[word];
        if (results.empty()) 
        {
            results = matches;
        } else 
        {
            results = (type == 0) ? setIntersection(results, matches) : setUnion(results, matches);
        }
    }

    recentHits.assign(results.begin(), results.end());
    return recentHits;
}
void MyDataStore::dump(ostream& ofile) 
{
    ofile << "<products>" << endl;
    for (auto p : products) 
    {
        p->dump(ofile);
    }
    ofile << "</products>\n<users>" << endl;
    for (auto& entry : users) 
    {
        entry.second->dump(ofile);
    }
    ofile << "</users>" << endl;
}
void MyDataStore::addToCart(const string& username, int hit) 
{
    if (!users.count(username) || hit < 1 || hit > static_cast<int>(recentHits.size())) 
    {
        cout << "Invalid request" << endl;
        return;
    }
    Product* productToAdd = recentHits[hit - 1];
    carts[username].push_back(productToAdd);
}
void MyDataStore::viewCart(const string& username) 
{
    if (!users.count(username)) 
    {
        cout << "Invalid username" << endl;
        return;
    }
    auto& cart = carts[username];
    int i = 1;
    for (auto* p : cart) 
    {
        cout << "Item " << i++ << endl;
        cout << p->displayString() << endl << endl;
    }
}
void MyDataStore::buyCart(const string& username) 
{
    if (!users.count(username)) 
    {
        cout << "Invalid username" << endl;
        return;
    }
    User* user = users[username];
    auto& cart = carts[username];

    for (auto it = cart.begin(); it != cart.end(); ) 
    {
        Product* p = *it;
        double price = p->getPrice();
        int qty = p->getQty();

        if (qty > 0 && price <= user->getBalance()) 
        {
            p->subtractQty(1);
            user->deductAmount(price);
            it = cart.erase(it);
        } else 
        {
            ++it;
        }
    }
}
