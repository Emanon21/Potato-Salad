#include "GroceryItem.h"
// Constructor with string param
// @param that is assign to private data type of class and default 0 quantity
GroceryItem::GroceryItem(std::string& name)
{
	this->name = name;
	quantity = 0;
}


// Constructor with 2 param string and int
// @param are assign to name and quantity of private members of class
GroceryItem::GroceryItem(std::string& name, int quantity)
{
	this->name = name;
	this->quantity = quantity;
}


// Getter function
// @no param
// @return string name 
std::string GroceryItem::getName() const
{
	return name;
}

// Getter function
// @no param
// @return int type quantity
int GroceryItem::getQuantity() const
{
	return quantity;
}


// void function that will add quantity when called
// @no param
void GroceryItem::addItem()
{
	quantity++;
}


// void function that will remove quantity when called
// @no param
void GroceryItem::removeItem()
{
	if (quantity > 0) {
		quantity--;
	}
}


// Overloadin operator
bool GroceryItem::operator<(const GroceryItem other) const
{
	return name.compare(other.getName()) < 0;
}
