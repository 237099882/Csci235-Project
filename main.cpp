#include "Item.hpp"
#include "BinaryNode.hpp"
#include "Inventory.hpp"
#include "BinarySearchTree.hpp"
#include <iostream>
using namespace std;
int main()
{
    Item* a = new Item("aa",CONSUMABLE,0,3,4);//12
    Item* b = new Item("ab",CONSUMABLE,5,2,2);//4
    Item* c = new Item("ac",CONSUMABLE,4,1,1);//1
    Item* d = new Item("ba",CONSUMABLE,2,1,5);//5
    Item* e = new Item("bb",UNKNOWN,1,1,1);//1
    Item* f = new Item("bc",ARMOR,1,1,1);//1
    Item* g = new Item("ca",ARMOR,1,1,1);//1
    Item* h = new Item("cb",UNKNOWN,1,1,1);//1
    Item* i = new Item("cc",CONSUMABLE,1,1,10);//10
    Inventory test;
    test.addItem(f);
    test.addItem(b);
    test.addItem(c);
    test.addItem(d);
    test.addItem(e);
    test.addItem(a);
    test.addItem(g);
    test.addItem(h);
    test.addItem(i);
    cout<<a->getTimePickedUp()<<"\n";
    cout<<b->getTimePickedUp()<<"\n";
    test.addItem(a);
    test.addItem(b);
    //test.addItem(i);
    //cout<<test.getRoot()->getItem()->getName()<<" "<<test.getRoot()->getLeftChildPtr()->getItem()->getName()<<test.getRoot()->getRightChildPtr()->getItem()->getName();
    // cout<<i->getQuantity()<<" "<<endl;;
    // cout<<test.getTotalGoldValue()<<endl;
    // Item* found = test.findItem("ee");
    // std::cout<<test.removeItem("ab")<<" "<<test.removeItem("ab")<<" "<<test.removeItem("ab")<<" "<<std::endl;
    cout<<a->getTimePickedUp()<<"\n";
    cout<<b->getTimePickedUp()<<"\n";
    test.printInventory(false,"TIME");
}

