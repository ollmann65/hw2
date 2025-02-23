#include "clothing.h"
#include "util.h"  
#include <string>
#include <set>
#include <iostream>

Clothing::Clothing(const std::string& name, double price, int qty, const std::string& size, const std::string& brand)
    : Product("clothing", name, price, qty), size_(size), brand_(brand) {}
std::set<std::string> Clothing::keywords() const
{
    
    std::set<std::string> words = parseStringToWords(name_ + ", " + brand_);
    return words;
}
std::string Clothing::displayString() const 
{
    return name_ + "\nSize: " + size_ + " Brand: " + brand_ + "\n" +
           std::to_string(price_) + " " + std::to_string(qty_) + " left.";
}
void Clothing::dump(std::ostream& os) const 
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n"
       << size_ << "\n" << brand_ << std::endl;
}
