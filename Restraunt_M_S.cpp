#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cstdlib> 
#pragma pack(1)

using namespace std;
class stock {
public:
    char padding[2];//padding and alignmnet
    char ItemName[100000];
    int price;     
    int Quantity;  
    static int revenue;
    static int Totaltable;
    static int TableRemaining;
    static int CurrentTable;


    void display() {
        if(Quantity>=0){
        cout << ItemName << "\t\t\t" << price << "\t\t" << Quantity << endl;}
    }






 void insert(){
     ofstream fout;
     fout.open("ItemStock.txt",ios::binary | ios::app | ios::out);
     fout.write((char*)this,sizeof(*this));
     fout.close();
  }

  void display() const
  {
    cout<<right;
    cout<<this->ItemName<<"\t\t\t"<<this->Quantity<<"\t\t"<<this->price<<endl;
  }

bool  show() {

    bool opened=false;
    ifstream fin("ItemStock.txt", ios::binary);

    if (fin) {

        opened=true;

        stock s1;  // Create a new instance of stock for each record

       cout<<"Item Name\t\tPrice\t\tQuantity"<<endl;

          fin.read(reinterpret_cast<char*>(&s1),sizeof(s1));


          
        while (!fin.eof()) {

            s1.display();
fin.read(reinterpret_cast<char*>(&s1),sizeof(s1));
             

            
        }

        fin.close();
    }

    return opened;

}



void getdata() {
    int price, quantity;
    const int maxLength = 100;  // Maximum length of the char array
    char name[maxLength];
    cout<<"----Press Enter to continue----"<<endl;
    cin.ignore();  // Clear any leftover newline characters

    cout << "Enter name: ";
    cin.getline(name, maxLength);
// Modify the getdata() function

    cout << "Enter price: ";
    cin >> price;

    cout << "Enter quantity: ";
    cin >> quantity;

    strcpy(this->ItemName, name);
    this->price = price;
    this->Quantity = quantity;
}

  void setdata(char ch[],int pr,int quant) {

   
   strcpy(this->ItemName,ch);
    this->price = pr;
    this->Quantity = quant; // Assign quantity



  }

  static void saveToFile() {
        ofstream fout;
        fout.open("ItemStock_Backup.txt", ios::binary | ios::out ); // Open with truncation to clear the file
        if (fout.is_open()) {
            cout<<"Backup file opened"<<endl;
            // Write all objects to the file
            stock obj;

            ifstream fin("ItemStock.txt", ios::binary | ios::in);
            while (fin.read((char*)&obj, sizeof(obj))) {
                fout.write((char*)&obj, sizeof(obj));
            }
            fout.close();
            fin.close();
        }
     else{
        cout<<"Backup not found"<<endl;
     }


    }


 bool  update_stock(char key[]){
    ifstream fin;

    fin.open("ItemStock.txt",ios::binary);


    stock s1;
    bool found=false;

    ofstream fout;
    fout.open("NewFile.txt",ios::binary);

    while(!fin.eof()){
            fin.read(reinterpret_cast<char*> (&s1),sizeof(s1));
            if(strcmp(s1.ItemName,key)){
                fout.write(reinterpret_cast<char*> (&s1),sizeof(s1));

            }

            /* if two strings are same strcmp returns 0 (opposite to regular functions, it means that difference is 0)
               if two strings are not same, it returns 1*/

            else if(!strcmp(s1.ItemName,key)){
                    found=true;
                    s1.getdata();
                    fout.write(reinterpret_cast<char*> (&s1),sizeof(s1));
                    

            }

                 fin.read(reinterpret_cast<char*> (&s1),sizeof(s1));

            


    }    


   


    remove("ItemStock.txt");
    rename("NewFile.txt","ItemStock.txt");

    return found;
     }



bool CustomerMenuShow(){
    ifstream fin;
    int i=0;
     
    fin.open("ItemStock.txt",ios::binary);
    bool opened=false;
    if(fin){
        opened=true;
    fin.read(reinterpret_cast<char*>(this),sizeof(*this));
    cout<<"Item#\t\tItemName\tPrice"<<endl;

                cout<<i<<"\t\t"<<"Exit\t\t----"<<endl;

    while(!fin.eof()){
           i++;

        if(this->Quantity==0){
           
        cout<<i<<"\t\t"<<this->ItemName<<"\t\t"<<this->price<<"\t (*Not Available)"<<endl;;
            
            }
            else{
                 cout<<i<<"\t\t"<<this->ItemName<<"\t\t"<<this->price<<endl;
            }

         

                        fin.read(reinterpret_cast<char*>(this),sizeof(*this));


    }
    }

    fin.close();
    return opened;
    

}
stock getDetails(int choice){

    ifstream fin;
    int i=1;
    stock s1;
    char ch[10000]={'0'};
    s1.setdata(ch,-1,-1);
    fin.open("ItemStock.txt",ios::binary);
   


        fin.read(reinterpret_cast<char*>(&s1),sizeof(s1));

        while(!fin.eof()){
        if(i==choice){
          return s1;
        }

        else{
            i++;
            fin.read(reinterpret_cast<char*>(&s1),sizeof(s1));

        }}

        return s1;
    
    
}

void generateReceipt(stock s1,int quant[],int i){
    
            cout<<right;
            cout<<++i<<"\t\t"<<s1.ItemName<<"\t\t\t"<<s1.price<<"\t\t"<<quant[--i]<<endl;
           
   
}

void ByeByegreetingMessage(){
    cout<<"\n----Thanks for order-------"<<endl;
    cout<<"\n-----Your Order would be ready in 15 minutes----\n\n\n\n\n"<<endl;
}
void manageTables(){
    cout<<"Table: "<<++CurrentTable<<endl;
    stock::TableRemaining=stock::Totaltable-CurrentTable;
}

void updateQuantity(stock s1,int quan){ 
     stock temp;
    ifstream fin;

    ofstream fout;
    fin.open("ItemStock.txt",ios::binary);
    if(fin){
        
        fout.open("NewFile.txt",ios::binary);
        fin.read(reinterpret_cast<char*> (&temp),sizeof(temp));
        while(!fin.eof()){
            if(strcmp(s1.ItemName,temp.ItemName)){  //not same

                fout.write(reinterpret_cast<char*>(&temp),sizeof(temp));
                  fin.read(reinterpret_cast<char*> (&temp),sizeof(temp));


            }

            else if(!strcmp(s1.ItemName,temp.ItemName)){
                 temp.Quantity=quan;

                 fout.write(reinterpret_cast<char*>(&temp),sizeof(temp));

            

                fin.read(reinterpret_cast<char*> (&temp),sizeof(temp));
        }

       
    }

 fin.close();
        fout.close();
    remove("ItemStock.txt");
    rename("NewFile.txt","ItemStock.txt");
}}

void manageQuantity(int quant, int choice){
    stock s1;
    s1=getDetails(choice);
    int newQuan=(s1.Quantity-quant);

    updateQuantity( s1,newQuan);
}
void TakeOrder(int choice[],int quant[],int index){
 cout<<"\t\t\tJame's Restraunt"<<endl;
 manageTables();
 cout<<right;
    cout<<"\nItem#"<<setw(18)<<"Item Name"<<setw(20)<<"Price"<<setw(20)<<"Quantity\n"<<endl;
    int totalBill=0;
    for(int i=0;i<index;i++){
        stock s1;
        s1=getDetails(choice[i]);
        totalBill=totalBill+(s1.price * quant[i]);

        if(s1.price!=-1){
            generateReceipt(s1,quant,i);
            manageQuantity(quant[i],choice[i]);
        }
    }
   
    
   printBill(totalBill);
    ByeByegreetingMessage();
    
 }
void addRevenueToFile(int currRevenue){
     ofstream fout;
     fout.open("Revenues.txt",ios::binary | ios::app);

     if(fout){
        fout.write(reinterpret_cast<char*>(&currRevenue),sizeof(int));

     }


}

void printBill(int total){
    cout<<"----------------------------------------------"<<endl;
    cout<<"Total: \t\t\t"<<total<<endl;
    addRevenueToFile(total);

}

int MaxItems(){
    ifstream fin;
    int i=0;
    fin.open("ItemStock.txt",ios::binary);

    if(fin){
        fin.read(reinterpret_cast<char*>(this),sizeof(*this));

        while(!fin.eof()){
          ++i;  
        fin.read(reinterpret_cast<char*>(this),sizeof(*this));
         

        }
    }

    return i;
}

int addUpRevenue(){
   
  ifstream fin;
  fin.open("Revenues.txt",ios::binary  | ios::app);

  int r=0;
  int total=0;
  
  fin.read(reinterpret_cast<char*> (&r),sizeof(int));

  while(!fin.eof()){
    total+=r;
      fin.read(reinterpret_cast<char*> (&r),sizeof(int));
      
  }
  return total;


   

}

};

int stock:: revenue=0;
int stock:: Totaltable=50;
int stock:: TableRemaining=0;
int stock:: CurrentTable=0;
  


void mainMenu() {
    cout << "\t\t\t1)  owner" << endl;
    cout << "\t\t\t2)  customer" << endl;
    cout << "\t\t\t3)  Exit" << endl;
}

bool validateOwner() {
    string name, pass;
    cout<<"---------------------------------------------------------------------------------------------\n\n"<<endl;
    cout << "\t\t\tEnter Username: ";
    cin >> name;
    cout << "\t\t\tEnter Password: ";
    cin >> pass;
    cout<<"\n---------------------------------------------------------------------------------------------\n\n"<<endl;
    if (name == "owner" && pass == "owner") {
        return true;
    }
    return false;
}

int ownermenu() {
    int key;
    cout<<"----------------------------------------------------------------------"<<endl;
    cout << "\t\t\t-----Owner------" << endl;
    cout << "\t\t1. Add Item in Stock" << endl;
    cout << "\t\t2. View Item Stock" << endl;
     cout << "\t\t3. View Revenue" << endl;
     cout << "\t\t4. View Tables Available" << endl;
     cout<<"\t\t5. Search an item on name"<<endl;
     cout<<"\t\t6. Update an Item"<<endl;
     cout<<"\t\t7. Delete an item"<<endl;
    cout << "\t\t8. Exit Owner Module" << endl;
        cout<<"----------------------------------------------------------------------"<<endl;

    cin >> key;

    return key;
}

void writeToFile(const stock& s1) {
    ofstream fout("ItemStock.txt", ios::binary | ios::app);
    if (fout.is_open()) {
        fout.write(reinterpret_cast<const char*>(&s1), sizeof(s1));
        fout.close();
    }
}


bool search(char key[]){
   
   ifstream fin;
   fin.open("ItemStock.txt",ios::binary);
  

    stock s1;

    bool found=false;
    
   while(fin.read(reinterpret_cast<char*>(&s1), sizeof(s1))){
        if(!strcmp(s1.ItemName,key)){
            
             cout<<"Item Name\t\tPrice\t\tQuantity\n"<<endl;
             s1.display();
             found=true;
          
          }
 
   }

    fin.close();

    return found;   
  
}


bool remove(char key[]){
    ifstream fin;
    bool found=false;
    fin.open("ItemStock.txt",ios::binary);
    stock s1;

    ofstream fout;
    fout.open("NewFile.txt",ios::binary | ios::app);
    if(fin){

        fin.read(reinterpret_cast<char*>(&s1),sizeof(s1));

        while(!fin.eof()){
            if(strcmp(s1.ItemName,key)){
                 fout.write(reinterpret_cast<char*>(&s1),sizeof(s1));
                 fin.read(reinterpret_cast<char*>(&s1),sizeof(s1));


            }
           else{
            found=true;
            
                 fin.read(reinterpret_cast<char*>(&s1),sizeof(s1));}
           
            

        }
    }


    fin.close();
    remove("ItemStock.txt");
    rename("NewFile.txt","ItemStock.txt");
    return found;
}




int main() {
    
    int key;
    do {

         cout<<"\t\t-------Select from 1 to 3:---------- "<<endl;
        mainMenu();
        cin >> key;
        system("clear");
         switch (key) {
            case 1: {
                if (validateOwner()) {
                    cout << "Valid Owner" << endl;
                    system("clear");
                    do {
                        key = ownermenu();
                        switch (key) {
                            case 1: {
                               
                               stock s1;
                               s1.getdata();
                               s1.insert();
                                break;
                            }
                            case 2: {
                                

                                stock s1;

                                cout<<"----------------------------------------------------------------------------"<<endl;
                                if(!s1.show()){
                                    cout<<"----Not opened/ Is empty----"<<endl;
                                };
                                cout<<"----------------------------------------------------------------------------"<<endl;

                                break;
                            }


                            case 3:{
                                stock s1;
                                
                                cout<<"------------------------------------------"<<endl;
                                cout<<"Total Revenue: "<<s1.addUpRevenue()<<endl;

                                cout<<"-------------------------------------------"<<endl;
                                break;
                            }


                            case 4:{
                               
                                                                cout<<"-------------------------------------------"<<endl;

                                cout<<"Total Tables: "<<stock::Totaltable<<endl;
                                cout<<"Free Tables: "<<stock::TableRemaining<<endl;
                                                                cout<<"-------------------------------------------"<<endl;

                                break;
                            }

                            case 5:{
                                
                                int n=1000;
                                 char key[n];
                                 cout<<"--------------------------------------------------"<<endl;
                                cout<<"\t\tEnter a name: ";
                                
                                cin.ignore();
                                 cin.getline(key,n);
                                                                

                                 cout<<"--------------------------------------------------"<<endl;
                                
                                       cout<<"--------------------------------------------------"<<endl;

                                if(!search(key)){
                                    cout<<"------"<<key<<" not found------"<<endl;
                                } 
                                 cout<<"--------------------------------------------------"<<endl;


                                break;
                                   }

                                   case 6:{
                                    int n=1000;
                                    char key[n];
                                    cout<<"--------------------------------------------------"<<endl;
                                    cout<<"Enter Name of Item to Update: ";
                                    
                                     cin.ignore();

                                    
                                    cin.getline(key,n);

                                    cout<<"-----------Update Item In Stock-------------"<<endl;

                                      stock s1;
                                    cout<<"--------------------------------------------------"<<endl;
                                    if(!s1.update_stock(key)){
                                        cout<<"------Not Found---------"<<endl;
                                    }


                                    cout<<"--------------------------------------------------"<<endl;
                                    
                                    break;
                                   }


                                   case 7:{
                                   
                                    char name[1000];
                                   cout << "Enter name: ";
                                   cin.ignore();
                               cin.getline(name,sizeof(name));
                                    if(!remove(name)){
                                        cout<<"----Not found----"<<endl;
                                    }
                                    break;
                                   }
                           
                        }
                    }
                    
                     while (key != 8);
                }

                else{
                    cout<<"\n\n\t\t-------------Invalid owner-------------\n\n"<<endl;
                }
                
                break;
            }

            mainMenu();




            case 2:{

            
           system("clear");
                stock s1;
                cout<<"-----WELCOME TO RESTRAUNT----------"<<endl;
                if(!s1.CustomerMenuShow()){
                    cout<<"---File not opened----"<<endl;
                }
                else{

                int choice [10];
                int quant[10];
               int i;


                 for(i=0;i<10;i++){
                    cout<<"Enter item#: ";
                    cin>>choice[i];
                    cout<<endl;

                    int maxItems=s1.MaxItems();

                    if(choice[i]==0 ){
                        break;
                    }

                    while(choice[i]>maxItems    || choice[i]<0){
                        cout<<"\n\n*****Enter a valid number between 0 and "<<maxItems<<": ";
                        cin>>choice[i];

                           if(choice[i]==0 ){
                        break;
                    }                    
                    }
              if(choice[i]!=0){
                       cout<<endl<<"Enter quantity: ";
                    cin>>quant[i];}

                    else{
                        break;
                        }

                 }


                 s1.TakeOrder(choice,quant,i);
               
                  
                }
               
                

               break;


        }
        
        
        
        }
        
        }
    while (key != 3);


    stock::saveToFile();
    
    return 0;
}

