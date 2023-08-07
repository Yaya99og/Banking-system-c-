#include<iostream>
#include<string>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<string.h>
#include<time.h>

using namespace std;

class Bank
{
	int accNo;
	int n=0;
	char name[50];
	double Tamt;                      //data types
	char type;
	float I;
	float Interest;
	float Interestr;
public:                                //access specifiers
	void createAccount();
	void MonthlyproI(float);
	void MonthlyproC(float);
	void displayAccount() const;        //defining a function
	void modify();
	void dep(float);
	void draw(float);
	void report() const;
	int retaccNo() const;
	int retdeposit() const;
	char rettype() const;
};

/*:: is scope resolution operator. Used to define a function outside a class. + to access global variable when there is a local variable with same name. + to access a class’s
static variables.*/

//This Function is used to create an Account of User.

void Bank::createAccount()
{
	cout<<endl;
	cout<<"\t\t\tPlease enter Unique Account No. : ";
	cin>>accNo;
	cout<<endl<<endl;
	cout<<"\t\t\tEnter the Name of the Account holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<endl;
	cout<<"\t\t\tEnter Type of the Account (C(Current)/S(Savings)) : ";
	cin>>type;
	type=toupper(type);
	cout<<endl;
	cout<<"\t\t\tEnter The Initial amount (<$25) : $";
	cin>>Tamt;
	cout<<endl;
	cout<<"\t\t\tEnter annual interest rate : ";
	cin>>I;
	cout<<endl;
	MonthlyproI(I);                //calling function of same class
	cout<<"\t\t\tAcquired Monthly Interest Amount was : $"<<Interest;
	cout<<endl<<endl;
	cout<<"\t\t\tAccount Created..";
}

//This function calculates service charge

void Bank::MonthlyproI(float x)
{
    Interestr = I / 12;
	Interest = Tamt * Interestr;
	Tamt = Tamt + Interest;
}

void Bank::MonthlyproC(float x)
{
    draw(x);
    if(Tamt<=0)
        {
        // Fine of $15 is charged if balance becomes $0 or less after withdraw.
        Tamt = Tamt - 15;
        }
    cout<<"\n\t\t\tNew Balance is : $"<<Tamt;
}

//This FUnction is used to Modify an Account of User.

void Bank::modify()
{
    string choice;
	cout<<"\n\t\t\tAccount No. : "<<accNo;
	cout<<"\n\t\t\tDo you want to change name yes=y/no=n? : ";
	cin>>choice;
	if(choice=="y")
    {
        cout<<"\n\t\t\tEnter new name : ";
        cin>>name;
    }
    cout<<"\n\t\t\tDo you want to change type yes=y/no=n? : ";
    cin>>choice;
    if(choice == "y")
    {
        cout<<"\n\t\t\tModify Type of Account (C(Current)/S(Savings)) : ";
        cin>>type;
        type=toupper(type);
    }
    cout<<"\n\t\t\tDo you want to change Annual Interest rate yes=y/no=n? : ";
    cin>>choice;
    if(choice == "y")
        {
            cout<<"\n\t\t\tEnter new Annual Interest rate : ";
            cin>>I;
            MonthlyproI(Tamt);
            cout<<"\n\t\t\tBalance after interest is : $"<<Tamt<<endl;
            cout<<"\n\t\t\tInterest acquired this month is : $"<<Interest<<endl;
        }
}

//This FUnction is used to display an Account of User.

void Bank::displayAccount() const
{
	cout<<"\n\t\t\tAccount No. : "<<accNo;
	cout<<"\n\t\t\tAccount Holder Name : ";
	cout<<name;
	cout<<"\n\t\t\tAnnual interest rate is : ";
	cout<<I;
	cout<<"\n\t\t\tType of Account : "<<type;
    cout<<"\n\t\t\tYour Balance is : $"<<Tamt;
	if(Tamt>25)
        cout<<"\n\t\t\tAccount Status : "<<"Active";
    else
        cout<<"\n\t\t\tAccount Status : "<<"Inactive";
}


void Bank::dep(float x)
{
	Tamt+=x;
}

void Bank::draw(float x)
{
	Tamt-=x;
	n++;
    cout<<"\n\t\t\tNumber of withdraws made : "<<n;
    if(n>4)
        {
        //Service charge is charged for every withdraw made if it exceeds monthly withdraw limit i.e. 4 free withdraw per month.
            n = n - 4;
            Tamt = Tamt - n * 1;
        //Service charge is n-4*1
        }
    else
    {
        Tamt = Tamt - 0;
    }

}

void Bank::report() const
{
	cout<<accNo<<setw(13)<<" "<<name<<setw(11)<<" "<<type<<setw(11)<<" "<<Interest<<"$"<<setw(11)<<" "<<"$"<<Tamt<<endl;
}

int Bank::retaccNo() const
{
	return accNo;
}

int Bank::retdeposit() const
{
	return Tamt;
}

char Bank::rettype() const
{
	return type;
}

void accountDetails()
{
	Bank B;
	ofstream outFile;//ofstream (write) derived from fstream and object of ofstream is created
	outFile.open("Bank.dat",ios::binary|ios::app);
	//.dat files stores data in binary format ios::binary is used to send data to file in binary format ios::app>>append mode
	B.createAccount();
	outFile.write(reinterpret_cast<char *> (&B), sizeof(Bank));//size of class as account is seperated at the &B
	outFile.close();//file is closed using close() function
}


void display_sp(int n)
{
	Bank B;
	bool flag=false;//datatype which return valaue ture and false only
	ifstream inFile;//ifstream (read) derived from fstream and object of ifstream is created
	inFile.open("Bank.dat",ios::binary);//file is opened using open() function
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\t\t\tBALANCE DETAILS\n";
    while(inFile.read(reinterpret_cast<char *> (&B), sizeof(Bank)))
//reinterpret_cast is casting operator used to convert pointer of one type to another it does not check data or pointer type.
	{
		if(B.retaccNo()==n)
		{
			B.displayAccount();
			flag=true;
		}
	}
    inFile.close();
	if(flag==false){
        cout<<"\n\n\t\t\tAccount number does not exist";
    }

}



void modifyAccount(int n)
{
	bool found=false;
	Bank B;
	fstream File;
    File.open("Bank.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&B), sizeof(Bank));
		if(B.retaccNo()==n)
		{
			B.displayAccount();
			cout<<"\n\n\t\t\tEnter The New Details of account"<<endl;
			B.modify();
			int pos=(-1)*static_cast<int>(sizeof(Bank));//static_cast converts data type from one to another itself
			File.seekp(pos,ios::cur); //seekp moves the put pointer(output) to a specified location. cur is current position in file.
		    File.write(reinterpret_cast<char *> (&B), sizeof(Bank));
		    cout<<"\n\n\t\t\tRecord Updated";
		    found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n\n\t\t\tRecord Not Found ";
}


void deleteAccount(int n)
{
	Bank B;
	ifstream inFile;
	ofstream outFile;
	inFile.open("Bank.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);   //beg means beginning of file and seekg moves get pointer(input) to a specified location.
	while(inFile.read(reinterpret_cast<char *> (&B), sizeof(Bank)))
	{
		if(B.retaccNo()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&B), sizeof(Bank));
		}
	}
    inFile.close();
	outFile.close();
	remove("Bank.dat");
	rename("Temp.dat","Bank.dat");
	cout<<"\n\n\t\tRecord Deleted ..";
}


void displayRecords()
{
	Bank B;
	ifstream inFile;
	inFile.open("Bank.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"===================================================================\n";
	cout<<"A/c no.      NAME          Type        Interest       Balance\n ";
	cout<<"===================================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&B), sizeof(Bank)))
	{
		B.report();
	}
	inFile.close();
}


void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	Bank B;
	fstream File;
    File.open("Bank.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&B), sizeof(Bank));
		if(B.retaccNo()==n)// n is a option give by the user
		{
			B.displayAccount();
			if(option==1)
			{
				//cout<<"\n\n\t\t\tTO DEPOSITSS AMOUNT";
				cout<<"\n\n\t\t\tEnter The amount to be deposited : $";
				cin>>amt;
				B.dep(amt);
			}
		    if(option==2)
			{
				//cout<<"\n\n\t\t\tTO WITHDRAW AMOUNT";
				cout<<"\n\n\t\t\tEnter The amount to be withdraw : $";
				cin>>amt;
				int bal=B.retdeposit()-amt;
				if(bal<0)
                {
                    cout<<"\n\t\t\tSorry !! Insufficient balance..";
                    cout<<"\n\t\t\tFine of $15 is charged."<<endl;
					B.MonthlyproC(amt);
                }
				else
					B.draw(amt);
		      }
			int pos=(-1)*static_cast<int>(sizeof(B));
			File.seekp(pos,ios::cur);//moves the cursor to the specified location i.e pos=-1 is specified
			File.write(reinterpret_cast<char *> (&B), sizeof(Bank));//
			cout<<"\n\n\t\t\tSuccess... Record Updated Successfully";
			found=true;
	       }
         }
    File.close();
	if(found==false)
		cout<<"\n\n\t\t\tOops! We Couldn't find your record";
}

//To Display Date on Screen

void date()
{
   time_t now = time(0);
    char* dt = ctime(&now);
    cout<<"Local date and time : "<< dt << endl;
    tm* gmtm = gmtime(&now);
    dt = asctime(gmtm);
    cout<<"UTC date and time : "<< dt << endl;
}

//To give delay to load Login System

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

//If Invalid Attempts will exceed the 3 then

void callExit()
{
    cout<<("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    cout<<("\t\t\t\t\t");
    fflush(stdin);                      //to clear or flush output buffer
    cout<<("You are out of the System.");
    cout<<("\n\n");
    cout<<("\t\t\t\t");
    cout<<("   Press Enter to Continue Exit Program...");
    getchar();            //lib function that gets a unsigned character from stdin.
}

// Mainpage of the Project

void mainpage()
{
  int process=0;
  date();
  cout<<endl;
  cout<<("\t\t\t\t    ---------------------------\n");
  cout<<("\t\t\t\t     |BANK MANAGEMENT SYSTEM|\n");
  cout<<("\t\t\t\t    ---------------------------\n");
  cout<<endl<<endl<<endl;
  cout<<("\t\t\t\t");
  cout<<("Prepared By    :");
  cout<<("  Pramish Gurung");
  cout<<("\n\n");
  cout<<("\t\t\t\t");
  cout<<("Final Project    :");
  cout<<("   Bank Management System");
  cout<<("\n\n");
  cout<<("\t\t\t\t");
  cout<<("\n\n");
  cout<<("\t\t\t\t    Press Enter to continue......");
  cout<<("\n\n");
  getchar();
  cout<<("\t\t\t\tLoading");

  for(process=0;process<25;process++)
  {
    delay(150);
    cout<<(".");
  }
}

// MenuList of Project


void menulist(){
    char ch;
	int num;
	do
	{
	cout<<"\n\n\t\t\t\t==============================\n";
	cout<<"\t\t\t\t|    BANK MANAGEMENT SYSTEM  |";
	cout<<"\n\t\t\t\t==============================\n";

        cout<<endl<<endl;
		cout<<"\t\t\t\t   :: :: MAIN MENU :: ::\n";
        cout<<endl<<endl;
		cout<<"\n\n\t\t\t\t1. Create New Account";
		cout<<"\n\t\t\t\t2. Deposit Amount to Account";
		cout<<"\n\t\t\t\t3. Withdraw Amount from Account";
		cout<<"\n\t\t\t\t4. Balance Inquiry";
		cout<<"\n\t\t\t\t5. Display list of Account holders";
		cout<<"\n\t\t\t\t6. Delete an Account";
		cout<<"\n\t\t\t\t7. Modify the existing Account";
		cout<<"\n\t\t\t\t8. Exit";
		cout<<"\n\n\t\t\t\tChoose options:[1/2/3/4/5/6/7/8]:: ";
		cin>>ch;

		switch(ch)
		{
		case '1':
			accountDetails();
			break;
		case '2':
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			displayRecords();
			break;
		case '6':
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			deleteAccount(num);
			break;
		 case '7':
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			modifyAccount(num);
			break;
		 case '8':
			cout<<"\n\n\t\t\tThank You.. Visit Again";
            mainpage();
            callExit();
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();//waits for the user to type
    }while(ch!='8');
}

//Set Username & Password here for Login System

int logscreen()
{
  char username[30];
  char password[30];
  int chances = 0;
  int flag = 1;
  do
  {
    cout<<("\n\n\n\n\n\n\n\n\n\n");
    cout<<("\t\t\t\t\t");
    cout<<("Username: ");
    cin>>("%s",username);
    cout<<("\t\t\t\t\t");
    cout<<("\n");
    cout<<("\t\t\t\t\t");
    cout<<("Password: ");
    cin>>("%s",password);
    if(strcmp(username,"admin")==0 && strcmp(password,"yaya")==0)
      {
        cout<<("\n\n");
        cout<<("\t\t\t\t");
        cout<<("You are accessed to the system!\n\n");
        cout<<("\t\t\t\t   Press Enter to continue...");
        fflush(stdin);
        getchar();
        menulist();
        getchar();
        flag =0;
      }
      else
      {
        chances = chances+1;
       cout<<("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        cout<<("\t\t\t\t\t");
        cout<<("No. of attempts remain: %d",3-chances);
        fflush(stdin);
        getchar();
        if(chances>=3)
        {

          cout<<("\t\t\t\t\t\t");
          cout<<("\n");
          cout<<("\t\t\t\t");
          cout<<("   No permission to enter the system!" );
          getchar();
          callExit();
          getchar();
      }
  } //END OF ELSE
 }
 while(true==1);
}


//Actual Execution Starts here :) Main Function Started

int main()
{
    mainpage();
    logscreen();

	return 0;
}
