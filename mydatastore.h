#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <map>
#include <list>

class MyDataStore : public DataStore {
public:
    ~MyDataStore();

    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    void addToCart(const std::string& username, int hit);
    void viewCart(const std::string& username);
    void buyCart(const std::string& username);

private:
    std::vector<Product*> recentHits;

    std::set<Product*> products;

    std::map<std::string, User*> users;

    std::map<std::string, std::set<Product*>> keywords;

    std::map<std::string, std::list<Product*>> carts;
};

#endif
