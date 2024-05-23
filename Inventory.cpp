/*
CSCI235 Fall 2023
Project 7 - Trinkets and Baubles: The Inventory 
zhilin li
*/

#include "Inventory.hpp"

Inventory::Inventory():BinarySearchTree<Item*>(){}
/**
 * @param : A Pointer to the Item object to be added to the inventory.
 * @post  : The Item is added to the inventory, preserving the BST structure. The BST property is based on (ascending) alphabetical order of the item's name.
 *          If the item is type UNKNOWN, WEAPON, or ARMOR and is already in the inventory, it is not added.
      However, if another instance of an Item of type CONSUMABLE is being added (an item with the same name), its quantity is updated to the sum of the quantities of the two objects, and the time_picked_up_ variable is updated to that of the latest instance of the item being added.
 * @return true if the item was added to the inventory or updated, false otherwise.
 */
bool Inventory::addItem(Item* item)
{
    std::string type = item->getType();
    if(type == "CONSUMABLE")
    {
        if(contains(item))
        {
            Item* old = findItem(item->getName());
            old->setQuantity(old->getQuantity() + item->getQuantity());
            old->updateTimePickedUp();
            return true;
        }
        else
        {
            add(item);
            return true;
        }
    }
    else if((type == "UNKNOWN"||type == "WEAPON"||type == "ARMOR")&&(!contains(item)))
    {
        add(item);
        return true; 
    }
    else
    {
        return false;
    }
}
/**
 * @param   : A reference to string name of the item to be found.
 * @return  : An Item pointer to the found item, or nullptr if the item is not in the inventory.
 */
Item* Inventory::findItem(const std::string& item) const
{
    Item* temp = new Item(item);
    if(getPointerTo(temp)!=nullptr)
    {
        return getPointerTo(temp)->getItem();
    }
    else
    {
        return nullptr;
    }
}

/**
 * @param   : A reference to string name of the item to be removed from the inventory.
 * @return  : True if the item was found and removed or updated successfully, false otherwise.
 * @post    : If the item is found in the inventory, it is removed while preserving the BST structure.
              If a CONSUMABLE is removed, its quantity is decremented by one, but its time_picked_up_ remains the same. However, if it is the last item (it's quantity is 1 and is being removed), the item should be removed. Non-CONSUMABLE items should always be removed when they are found.
 */
bool Inventory::removeItem(const std::string& item)
{
    Item* need = findItem(item);
    if(need==nullptr)
    {
        return false;
    }
    if(need->getType()=="CONSUMABLE"&&need->getQuantity()>1)
    {
        need->setQuantity(need->getQuantity()-1);
    }
    else
    {
        remove(need);
    }
    return true;
}
/**
 * @return    : The total sum of gold values of all items in the inventory.
 */
int Inventory::getTotalGoldValue()
{
    return getSubtreeTotal(getRoot());
}

/**
 * @post    : The names of all items in the Inventory are printed in ascending order.
 *            This function performs an in-order traversal of the binary search tree and prints the details of each item in the following format. 
        NOTE: QUANTITY ONLY NEEDS TO BE DISPLAYED FOR CONSUMABLE ITEMS.

 *            [NAME] ([TYPE])
              Level: [LEVEL]
              Value: [VALUE]
              Quantity: [QUANTITY]
   
              Example:
              TIRED GAUNTLETS (ARMOR)
              Level: 3
              Value: 25
        
              SMALL HEALTH POTION (CONSUMABLE)
              Level: 1
              Value: 10
              Quantity: 2
 * 
 */
void Inventory::printInventoryInOrder() const
{
    printNode(getRoot());

}
/**
 * @param   : a reference to bool if the items are to be printed in ascending order. 
 * @param   : a reference to string attribute which defines the order by which the items are to be printed. You may assume that the given parameter will be in one of the following forms: ["NAME"/"TYPE"/"LEVEL"/"VALUE"/"TIME"]
 * @post    : All items in the Inventory are printed in the order specified by the parameter.
 *          Example usage: inventory.printInventory(false, "LEVEL");
            NOTE: QUANTITY ONLY NEEDS TO BE DISPLAYED FOR CONSUMABLE ITEMS:

            FEATHER DUSTER (WEAPON)
            Level: 5
            Value: 100

            TIRED GAUNTLETS (ARMOR)
            Level: 3
            Value: 50

            SMALL HEALTH POTION (CONSUMABLE)
            Level: 1
            Value: 10
            Quantity: 2

            NOODLES (CONSUMABLE)
            Level: 0
            Value: 120
            Quantity: 5
 */
void Inventory::printInventory(const bool& order, const std::string& attribute)
{
    std::vector<Item*> sorted;
    sorted = createVector(getRoot(),sorted);
    sorted = sortVector(order,attribute,sorted);

    for(int i=0;i<sorted.size();i++)
    {
        printInfo(sorted[i]);
    }
}

int Inventory::getSubtreeTotal(std::shared_ptr<BinaryNode<Item*>> subTreePtr)
{
    int quanlity = 1;
    if(subTreePtr->getItem()->getType()=="CONSUMABLE")
    {
        quanlity = subTreePtr->getItem()->getQuantity();
    }
    int sum = subTreePtr->getItem()->getGoldValue() * quanlity;
    if(subTreePtr->getLeftChildPtr()!=nullptr)
    {
        sum+=getSubtreeTotal(subTreePtr->getLeftChildPtr());
    }
    if(subTreePtr->getRightChildPtr()!=nullptr)
    {
        sum+=getSubtreeTotal(subTreePtr->getRightChildPtr());
    }
    return sum;
}

void Inventory::printInfo(std::shared_ptr<BinaryNode<Item*>> subTreePtr) const
{
    Item* item = subTreePtr->getItem();
    std::cout<<item->getName()<<" ("<<item->getType()<<")\nLevel: "<<item->getLevel()<<"\nValue: "<<item->getGoldValue()<<"\n";
    if(item->getType()=="CONSUMABLE")
    {
        std::cout<<"Quantity: "<<item->getQuantity()<<"\n";
    }
}
void Inventory::printInfo(Item* item) const
{
    std::cout<<item->getName()<<" ("<<item->getType()<<")\nLevel: "<<item->getLevel()<<"\nValue: "<<item->getGoldValue()<<"\n";
    if(item->getType()=="CONSUMABLE")
    {
        std::cout<<"Quantity: "<<item->getQuantity()<<"\n";
    }
}
void Inventory::printNode(std::shared_ptr<BinaryNode<Item*>> subTreePtr) const
{
    if(subTreePtr!=nullptr)
    {
        printNode(subTreePtr->getLeftChildPtr());
        printInfo(subTreePtr);
        printNode(subTreePtr->getRightChildPtr());
    }
}

std::vector<Item*> Inventory::createVector(std::shared_ptr<BinaryNode<Item*>> subTreePtr,std::vector<Item*> sorted)
{
    if(subTreePtr!=nullptr)
    {
        sorted.push_back(subTreePtr->getItem());
    }
    if(subTreePtr->getLeftChildPtr()!=nullptr)
    {
        sorted = createVector(subTreePtr->getLeftChildPtr(),sorted);
    }
    if(subTreePtr->getRightChildPtr()!=nullptr)
    {
        sorted = createVector(subTreePtr->getRightChildPtr(),sorted);
    }
    return sorted;
}

std::vector<Item*> Inventory::sortVector(const bool& order, const std::string& attribute,std::vector<Item*> sorted)
{
    if(order&&attribute=="NAME")
    {
        std::sort(sorted.begin(),sorted.end(),[](Item* x, Item* y)
        {
            return x->getName()<y->getName();
        });
    }
    else if (!order&&attribute=="NAME")
    {
        std::sort(sorted.begin(),sorted.end(),[](Item* x, Item* y)
        {
            return x->getName()>y->getName();
        });
    }
    else if (order&&attribute=="TYPE")
    {
        std::sort(sorted.begin(),sorted.end(),[](Item* x, Item* y)
        {
            return x->getType()<y->getType();
        }); 
    }
    else if (!order&&attribute=="TYPE")
    {
        std::sort(sorted.begin(),sorted.end(),[](Item* x, Item* y)
        {
            return x->getType()>y->getType();
        });
    }
    else if (order&&attribute=="LEVEL")
    {
        std::sort(sorted.begin(),sorted.end(),[](Item* x, Item* y)
        {
            return x->getLevel()<y->getLevel();
        }); 
    }
    else if (!order&&attribute=="LEVEL")
    {
        std::sort(sorted.begin(),sorted.end(),[](Item* x, Item* y)
        {
            return x->getLevel()>y->getLevel();
        });
    }
    else if (order&&attribute=="VALUE")
    {
        std::sort(sorted.begin(),sorted.end(),[](Item* x, Item* y)
        {
            return x->getGoldValue()<y->getGoldValue();
        });
    }
    else if (!order&&attribute=="VALUE")
    {
        std::sort(sorted.begin(),sorted.end(),[](Item* x, Item* y)
        {
            return x->getGoldValue()>y->getGoldValue();
        });
    }
    else if (order&&attribute=="TIME")
    {
        std::sort(sorted.begin(),sorted.end(),[](Item* x, Item* y)
        {
            return x->getTimePickedUp()<y->getTimePickedUp();
        });
    }
    else if (!order&&attribute=="TIME")
    {
        std::sort(sorted.begin(),sorted.end(),[](Item* x, Item* y)
        {
            return x->getTimePickedUp()>y->getTimePickedUp();
        });
    }
    return sorted;
}