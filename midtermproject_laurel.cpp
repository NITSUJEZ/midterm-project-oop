//Justin O. Laurel
//IT2A - INTERPROG 

#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;

//Defining the class
class InventoryItem {
private:
    int productID;
    string name;
    int quantity;
    double price;
    string category;

public:
    //Constructor init item deets when creating an obj
    InventoryItem(int id, string name, int quantity, double price, string category) {
        this->productID=id;
        this->name=name;
        this->quantity=quantity;
        this->price=price;
        this->category=category;
    }

    //Getter func for priv data
    int getID()const { return productID; }
    string getName()const { return name; }
    int getQuantity()const { return quantity; }
    double getPrice()const { return price; }
    string getCategory()const { return category; }

    //Setter func to change price n quantity
    void setQuantity(int newQuantity) { quantity=newQuantity; }
    void setPrice(double newPrice) { price=newPrice; }

    //func prints item details in a row format
    void displayRow()const {
        cout<<left<<setw(10)<<productID
            <<setw(20)<<name
            <<setw(10)<<quantity
            <<setw(10)<<fixed<<setprecision(2)<<price
            <<setw(15)<<category<<endl;
    }
};

//Func to display all inv items
void displayAllItems(const vector<InventoryItem>& items) {
    if(items.empty()) {
        cout<<"No items in the inventory."<<endl;
        return;
    }

    //Displaying headers in column
    cout<<left<<setw(10)<<"ProductID"
        <<setw(20)<<"Name"
        <<setw(10)<<"Quantity"
        <<setw(10)<<"Price"
        <<setw(15)<<"Category"<<endl;
    cout<<string(65,'-')<<endl;

    //Accessing each item
    for(const auto& item: items) {
        item.displayRow();
    }
}

//Func for items <=5
void displayLowStockItems(const vector<InventoryItem>& items) {
    cout<<"\nDisplaying low stock items:\n";
    cout<<left<<setw(10)<<"ProductID"
        <<setw(20)<<"Name"
        <<setw(10)<<"Quantity"
        <<setw(10)<<"Price"
        <<setw(15)<<"Category"<<endl;
    cout<<string(65,'-')<<endl;

    bool found=false;
    for(const auto& item: items) {
        if(item.getQuantity()<=5) {
            item.displayRow();
            found=true;
        }
    }

    if(!found) {
        cout<<"No low stock items found."<<endl;
    }
}

//Bubble sort quantity and price
void bubbleSort(vector<InventoryItem>& items, int choice, bool ascending) {
    bool swapped;

    //Outer loop runs through the list multiple times
    for(size_t i=0; i<items.size()-1; i++) {
        swapped=false;

        //Inner loop compares adjacent items and swap if necessary
        for(size_t j=0; j<items.size()-i-1; j++) {
            bool condition=false;

            if(choice==1) {
                //Sorting by quantity
                condition=ascending
                            ? items[j].getQuantity()>items[j+1].getQuantity()
                            : items[j].getQuantity()<items[j+1].getQuantity();
            } else if(choice==2) {
                //Sorting by price
                condition=ascending
                            ? items[j].getPrice()>items[j+1].getPrice()
                            : items[j].getPrice()<items[j+1].getPrice();
            }

            //Swap items if the condition is true
            if(condition) {
                swap(items[j], items[j+1]);
                swapped=true;
            }
        }

        //no swap = already sorted
        if(!swapped) break;
    }

    cout<<"Items sorted successfully!"<<endl;
}

int main() {
    //Vector for dynamic resizing for push_back
    vector<InventoryItem> items;
    int nextID=1; //Tracking of next product ID
    int choice;

    while(true) {
        cout<<"\nMenu\n";
        cout<<"1 - Add Item\n";
        cout<<"2 - Update Item\n";
        cout<<"3 - Remove Item\n";
        cout<<"4 - Display All Items\n";
        cout<<"5 - Search Item\n";
        cout<<"6 - Sort Items\n";
        cout<<"7 - Display Low Stock Items\n";
        cout<<"8 - Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;

        if(choice==8) {
            cout<<"Exiting..."<<endl;
            break;
        }

        if(choice==1) {
            string name, category;
            int quantity;
            double price;

            cout<<"Enter item name: ";
            cin>>name;
            cout<<"Enter quantity: ";
            cin>>quantity;
            cout<<"Enter price: ";
            cin>>price;
            cout<<"Enter category: ";
            cin>>category;

            items.push_back(InventoryItem(nextID, name, quantity, price, category));
            cout<<"Item added successfully!"<<endl;
            nextID++;
        } else if(choice==2) {
            int id;
            cout<<"Enter product ID to update: ";
            cin>>id;
            bool found=false;

            for(auto& item: items) {
                if(item.getID()==id) {
                    found=true;
                    int updateChoice;

                    cout<<"Choose update option:\n";
                    cout<<"1 - Update Quantity\n";
                    cout<<"2 - Update Price\n";
                    cout<<"Enter choice: ";
                    cin>>updateChoice;

                    if(updateChoice==1) {
                        int newQuantity;
                        cout<<"Enter new quantity: ";
                        cin>>newQuantity;
                        item.setQuantity(newQuantity);
                        cout<<"Quantity updated successfully!"<<endl;
                    } else if(updateChoice==2) {
                        double newPrice;
                        cout<<"Enter new price: ";
                        cin>>newPrice;
                        item.setPrice(newPrice);
                        cout<<"Price updated successfully!"<<endl;
                    } else {
                        cout<<"Invalid update option."<<endl;
                    }
                    break;
                }
            }

            if(!found) {
                cout<<"Item not found!"<<endl;
            }
        } else if(choice==3) {
            int id;
            cout<<"Enter product ID to remove: ";
            cin>>id;
            bool removed=false;

            for(size_t i=0; i<items.size(); i++) {
                if(items[i].getID()==id) {
                    cout<<"Item "<<items[i].getName()<<" has been removed from the inventory."<<endl;
                    items.erase(items.begin()+i);
                    removed=true;
                    break;
                }
            }

            if(!removed) {
                cout<<"Item not found!"<<endl;
            }
        } else if(choice==4) {
            cout<<"\nDisplaying all items:\n";
            displayAllItems(items);
        } else if(choice==5) {
            int id;
            cout<<"Enter product ID to search: ";
            cin>>id;
            bool found=false;

            for(const auto& item: items) {
                if(item.getID()==id) {
                    cout<<"\nItem details:\n";
                    cout<<left<<setw(10)<<"ProductID"
                        <<setw(20)<<"Name"
                        <<setw(10)<<"Quantity"
                        <<setw(10)<<"Price"
                        <<setw(15)<<"Category"<<endl;
                    cout<<string(65,'-')<<endl;
                    item.displayRow();
                    found=true;
                    break;
                }
            }

            if(!found) {
                cout<<"Item not found!"<<endl;
            }
        } else if(choice==6) {
            int sortChoice, orderChoice;

            cout<<"Sort by: 1 - Quantity, 2 - Price: ";
            cin>>sortChoice;
            cout<<"Order: 1 - Ascending, 2 - Descending: ";
            cin>>orderChoice;

            bool ascending=(orderChoice==1);
            bubbleSort(items, sortChoice, ascending);

            cout<<"\nDisplaying sorted items:\n";
            displayAllItems(items);
        } else if(choice==7) {
            displayLowStockItems(items);
        } else {
            cout<<"Invalid choice. Please try again."<<endl;
        }
    }

    return 0;
}
