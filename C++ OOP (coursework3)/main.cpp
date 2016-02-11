#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string text = "";

class Person{

private:
    string name;
    string egn;
    string address;

public:
    Person(string n, string e, string ad){
        setName(n);
        setEgn(e);
        setAddress(ad);
    }
    string getName(){
        return name;
    }
    string getEgn(){
        return egn;
    }
    string getAddress(){
        return address;
    }
    void setName(string n){
        if(n != ""){
        name = n;
        }
        else{
        name = "Gosho";
        }
    }
    void setAddress(string ad){
        if(ad != ""){
        address = ad;
        }
        else{
        address = "Pz";
        }
    }
    void setEgn(string e){
        if(e != "" && e.size() != 9){
        egn = e;
        }
        else{
        egn = "9411023422";
        }
    }
    ~Person(){
    }
};

class Owner:Person{

private:
    char *adr[5];

public:
    Owner(string n, string e, string ad, char *a[5]):Person(n,e, ad){
        for(int i=0; i<5; i++){
            adr[i] = a[i];
        }
    }

    void showAddresses(){
        for(int i=0; i<5; i++){
            cout<<adr[i]<<endl;
        }
    }

    static void showOwners(Owner owners[4]){

        for(int i=0; i<4; i++){
            for(int j=0; j<5; j++){
              if(owners[i].getAddress() == owners[i].adr[j]){
                    cout<<owners[i];
                    text += "Name: " + owners[i].getName() + ", EGN: " + owners[i].getEgn() + ", Address: " + owners[i].getAddress() + "\n";
                    break;
                }
            }
        }
        writeFile(text);
    }

    static void showProperties(string egn, Owner owner[]){
        for(int i=0; i<4; i++){
            if(owner[i].getEgn() == egn){
                cout<<"Properties of "<<owner[i].getName()<<": "<<endl;
                text += "Properties of " + owner[i].getName() + ": \n";
                for(int j=0; j<5; j++){
                    cout<<owner[i].adr[j]<<" ,";
                    text += (string)owner[i].adr[j] + ", ";
                }
            }
        }
        writeFile(text);
    }
    static int writeFile (string text){

      ofstream myfile;
      myfile.open ("example.txt");
      myfile << text << "\n";
      myfile.close();
      return 0;

}


    friend ostream& operator<<(std::ostream& os, Owner owner);
};

ostream& operator<<(ostream& os, Owner owner)
{
    os <<"Name: "<< owner.getName() << ", EGN: "<<owner.getEgn()<<", Address: "<<owner.getAddress()<<endl;
    return os;
}



int main()
{
    char *addresses[5] = {"Pz","Pld","Sf","Bs","Vn"};
    char *addresses2[5] = {"Pz","Vidin","Pleven", "Bs","Vn"};
    Owner sasho("Sasho", "9411023762", "Pz", addresses2);
    Owner misho("Misho", "9310023362", "Pld", addresses2);
    Owner genka("Genka", "9201023562", "Vraca", addresses);
    Owner michael("Michael", "9102023462", "Bs", addresses);

    Owner owners[] = {sasho, misho, genka, michael};
    Owner::showOwners(owners);
    Owner::showProperties("9411023762", owners);

    return 0;
}
