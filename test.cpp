#include "test.hpp"

// Constructor
Inventory::Inventory() {}

// Destructor
Inventory::~Inventory()
{
    // The BinarySearchTree destructor will automatically deallocate the Item pointers
}

// Additional Methods
bool Inventory::addItem(Item* item)
{
    if (item == nullptr)
        return false;

    Item* existingItem = findItem(item->getName());
    if (existingItem)
    {
        if (item->getType() == CONSUMABLE)
        {
            // Update quantity and time_picked_up for consumable items
            existingItem->setQuantity(existingItem->getQuantity() + item->getQuantity());
            existingItem->setTimePickedUp(item->getTimePickedUp());
            delete item; // Dealocate the added item since it's not needed anymore
            return true;
        }
        else
        {
            // Item of type other than CONSUMABLE, do not add
            delete item; // Dealocate the added item since it's not needed anymore
            return false;
        }
    }

    BinarySearchTree<Item*>::add(item);
    return true;
}

bool Inventory::removeItem(const std::string& itemName)
{
    Item* itemToRemove = findItem(itemName);
    if (itemToRemove)
    {
        if (itemToRemove->getType() == CONSUMABLE && itemToRemove->getQuantity() > 1)
        {
            // Decrement quantity for consumable items
            itemToRemove->setQuantity(itemToRemove->getQuantity() - 1);
        }
        else
        {
            BinarySearchTree<Item*>::remove(itemToRemove);
            delete itemToRemove; // Dealocate the removed item
        }
        return true;
    }

    return false;
}

Item* Inventory::findItem(const std::string& itemName)
{
    auto itemNode = BinarySearchTree<Item*>::getPointerTo(new Item(itemName));

    if (itemNode)
    {
        return itemNode->getItem();
    }

    return nullptr;
}


int Inventory::getTotalGoldValue() const
{
    int totalGold = 0;
    void visit(Item*& item)
    {
        totalGold += (item->getType() == CONSUMABLE) ? (item->getGoldValue() * item->getQuantity()) : item->getGoldValue();
    }
    BinarySearchTree<Item*>::inorderTraverse(visit);
    return totalGold;
}

void Inventory::printInventoryInOrder()
{
    void visit(Item*& item)
    {
        printItemDetails(item);
    }
    BinarySearchTree<Item*>::inorderTraverse(visit);
}

void Inventory::printInventory(bool ascendingOrder, const std::string& attribute)
{
    if (ascendingOrder)
    {
        if (attribute == "NAME")
            BinarySearchTree<Item*>::inorderTraverse([this](Item*& item) { printItemDetails(item); });
        else if (attribute == "TYPE")
            BinarySearchTree<Item*>::inorderTraverse([](Item*& item) { std::cout << item->getType() << std::endl; });
        else if (attribute == "LEVEL")
            BinarySearchTree<Item*>::inorderTraverse([](Item*& item) { std::cout << item->getLevel() << std::endl; });
        else if (attribute == "VALUE")
            BinarySearchTree<Item*>::inorderTraverse([](Item*& item) { std::cout << item->getGoldValue() << std::endl; });
        else if (attribute == "TIME")
            BinarySearchTree<Item*>::inorderTraverse([](Item*& item) { std::cout << item->getTimePickedUp() << std::endl; });
    }
    else
    {
        if (attribute == "NAME")
            BinarySearchTree<Item*>::postorderTraverse([this](Item*& item) { printItemDetails(item); });
        else if (attribute == "TYPE")
            BinarySearchTree<Item*>::postorderTraverse([](Item*& item) { std::cout << item->getType() << std::endl; });
        else if (attribute == "LEVEL")
            BinarySearchTree<Item*>::postorderTraverse([](Item*& item) { std::cout << item->getLevel() << std::endl; });
        else if (attribute == "VALUE")
            BinarySearchTree<Item*>::postorderTraverse([](Item*& item) { std::cout << item->getGoldValue() << std::endl; });
        else if (attribute == "TIME")
            BinarySearchTree<Item*>::postorderTraverse([](Item*& item) { std::cout << item->getTimePickedUp() << std::endl; });
    }
}

void Inventory::printItemDetails(Item* item) const
{
    std::cout << "[" << item->getName() << "] (" << item->getType() << ")\n"
              << "Level: " << item->getLevel() << "\n"
              << "Value: " << item->getGoldValue() << std::endl;
    if (item->getType() == CONSUMABLE)
        std::cout << "Quantity: " << item->getQuantity() << std::endl;
    std::cout << std::endl;
}
