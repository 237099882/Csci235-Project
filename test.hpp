#ifndef TEST_HPP
#define TEST_HPP

#include "BinarySearchTree.hpp"
#include "Item.hpp"
#include <iostream>

class Inventory : public BinarySearchTree<Item*>
{
public:
    // Constructor and Destructor
    Inventory();
    ~Inventory();

    // Additional Methods
    bool addItem(Item* item);
    bool removeItem(const std::string& itemName);
    Item* findItem(const std::string& itemName);
    int getTotalGoldValue() const;
    void printInventoryInOrder();
    void printInventory(bool ascendingOrder, const std::string& attribute);

private:
    // Helper method for printing items
    void printItemDetails(Item* item) const;
};

#endif // INVENTORY_HPP
