#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <fstream.h>
#include <process.h>
#include <dos.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <graphics.h>

char * A[3] = {"Where were you Born?",
		"What is your Favorite Dish?",
		"What Book did you first read?"};
int mindex = 1;


class ATM
{
	float money;
	public:
		friend int main();
		ATM()
		{
			Update(1);
		}
		void Deposit()
		{
			float add;
			cout<<"Enter Money to be added!\n";
			cin>>add;
			money = money + add;
			Update(2);
		}
		void Withdraw(float sub)
		{
			money = money - sub;
		}
		int WithdrawCheck(float sub)
		{
			if(sub>money)
			{
				cout<<"Not Enough Money in the"
				<<" Machine! Try a different branch.\n";
				return 0;
			}
			else
				return 1;
		}
		int MoneyCheck()
		{
			if(money<=20000)
				return 0;
			else
				return 1;
		}
		void Update(int a)
		{
			if(a==1)
			{
			file:
			ifstream fin("Money.txt",ios::in);
			if(!fin)
			{
				ofstream fout("Money.txt",ios::out);
				fout<<5000000;
				fout.close();
				goto file;
			}
			fin>>money;
			fin.close();
			}
			else if(a==2)
			{
			ofstream fout("Money.txt",ios::out);
			fout<<money;
			fout.close();
			}
		}
		float Money()
		{return money;}
}atm;

class Person
{
	float amount;
	long accountNumber;
	long PIN;
	char address[40];
	float rate;
	int priority;
	int securityQuestion;
	char securityAnswer[50];
	public:
		char name[30];
		int seniorCitizen;
		friend int main();
		friend Person Login(int);
		Person(long a = 0)
		{
			accountNumber = a;
			securityQuestion = -1;
		}
		float Amount()
		{return amount;}
		int Priority()
		{
			if(amount>=1000000||seniorCitizen==1)
				priority = 1;
			else
				priority = 0;
			return priority;
		}
		float Rate()
		{
			if(Priority()==1)
				rate = 7;
			else
				rate = 6.5;
				return rate;
		}
		char * Address()
		{return address;}
		long Pin()
		{return PIN;}
		void Withdraw(float sub)
		{
			amount = amount - sub;
		}
		void Deposit(float sub)
		{
			amount = amount + sub;
		}
		int WithdrawCheck(float sub)
		{
			if(sub>amount)
			{
				cout<<"Not Enough Money in your Account! Try adding some money first!\n";
				return 0;
			}
			else
				return 1;
		}
		void ChangeAddress()
		{
			cout<<"Enter a new Address!\n";
			cin.getline(address,40);
		}
		void Input()
		{
			char ch;
			cout<<"Enter Name!\n";
			cin.getline(name,30);
			cout<<"Enter Amount!\n";
			cin>>amount;
			cin.ignore();
			cout<<"Enter Home Address!\n";
			cin.getline(address,40);
			cout<<"Senior Citizen?(y/n)\n";
			cin>>ch;
			if(ch=='Y'||ch=='y')
				seniorCitizen=1;
			else
				seniorCitizen=0;
			if(Priority()==1||Rate()==7)
				cout<<"Eligible for Priority Service!\n";
			cin.ignore();
			cout<<"Enter a PIN. (Numbers Only)\n";
			cin>>PIN;
			cout<<"Account Number: "<<accountNumber<<"\nPIN: ";
			cout<<PIN;
			cout<<"\nDo you wish to have your Security Question Backup?(y/n)\n";
			cin>>ch;
			if(ch=='Y'||ch=='y')
				SecurityQuestion();
		}
		void ChangePIN()
		{
			long p1,p2;
			cout<<"Enter your old PIN.\n";
			cin>>p1;
			if(p1==PIN)
			{
				cout<<"Enter a New PIN.\n";
				cin>>p1;
				cout<<"Confirm PIN.\n";
				cin>>p2;
				if(p1==p2)
					PIN = p1;
				else
					cout<<"PINs do not match! Aborting!";
			}
			else
				cout<<"Incorrect PIN entered.\n";
		}
		void SecurityQuestion()
		{
			int choice;
			char ch, answer[40];
			if(securityQuestion!=-1)
			{
				cout<<"You already have answered a Previous Security Question!"
				<<" Do you wish to continue?(y/n)\n";
				cin>>ch;
				cin.ignore();
				if(ch!='Y'&&ch!='y')
				{
					return;
				}
			}
			start:
			cout<<"Choose a Preference.(1-3)\n";
			for(int i = 0;i<=2;i++)
			{
				cout<<i+1<<". ";
				puts(A[i]);
			}
			cin>>choice;
			cin.ignore();
			if(choice>=1&&choice<=3)
			{
				Question:
				securityQuestion = choice-1;
				cout<<"You chose Question "<<choice<<", ";
				puts(A[choice-1]);
				cout<<"Enter an Answer!\n";
				cin.getline(answer,50);
				cout<<"You entered ";
				puts(answer);
				cout<<"Do you wish to change?(y/n)\n";
				cin>>ch;
				cin.ignore();
				if(ch=='y'||ch=='Y')
					goto Question;
				else
					strcpy(securityAnswer,answer);
			}
			else
			{
				cout<<"Invalid choice entered. Try Again!\n";
				goto start;
			}
		}
		int RecoverPIN()
		{
			char answer[40];
			if(securityQuestion==-1)
			{
				cout<<"Uh Oh! You haven't set up a recovery option yet."
				<<" Go to Customer Service for a solution!\n";
				return 0;
			}
			puts(A[securityQuestion]);
			cin.getline(answer,40);
			if(strcmpi(securityAnswer,answer)==0)
			{
				cout<<"Success!\n";
				cout<<"Name:\t";
				puts(name);
				cout<<"Account Number:\t"<<accountNumber;
				cout<<"\nPIN: ";
				cout<<PIN;
				cout<<"\nPress any key to continue.\n";
				getch();
				return 1;
			}
			else
			{
				cout<<"Please Try Again in a different session"
				<<"! Quitting!\n";
				return 0;
			}
		}
		void Display()
		{
			cout<<"Account Number:\t"<<accountNumber;
			cout<<"\nName:\t";
			puts(name);
			cout<<"Rate:\t"<<Rate()<<endl;
			cout<<"Amount: "<<amount<<" Rupees!\n";
			if(Priority()==1)
				cout<<"Priority Account!\n";
			else
				cout<<"Regular Account!\n";
		}
		int AccountNumber()
		{return accountNumber;}
		~Person()
		{
		}
};
int getPIN(Person P)
{
	long pwd;
	cout<<"Enter PIN!\n";
	for(int i = 2;i>=0;i--)
	{
		cin>>pwd;
		cin.ignore();
		if(P.Pin()==pwd)
		{
			cout<<"Success!\n";
			return 1;
		}
		if(i!=0)
		{
			cout<<"Incorrect PIN! Try Again! "
			<<i<<" attempts remaining!\n";
		}
	}
	return 0;
}//*****************************************************************
void init()
{
	ifstream fin("Number.txt",ios::in);
	    if(fin)
	{
	    fin.close();
	    return;
	}
	else
	{
	    fin.close();
	    ofstream fout("Number.txt",ios::out);
	    if(fout)
	    {
		 fout<<0;
		 fout.close();
	    }
	}
}//*****************************************************************
int Number(int f=0)
{
	int  a;
	init();
	ifstream fin("Number.txt",ios::in);
	fin>>a;
	fin.close();
	if(f==0)
		return a;
	a++;
	ofstream fout("Number.txt",ios::out);
	fout<<a;
	fout.close();
	return a;
}//*****************************************************************
int Menus()
{
	Person ScanRecords(int);
	int aNum[3] = {8,6,3};
	char * menu[][10] = {{"Withdraw Money.",
			"Account Mini Statement.",
			"Account Transaction Log.",
			"Transfer Money.",
			"Setup a Recovery Question.",
			"Change PIN.",
			"Other Options.",
			"Exit."},
			{"Request ChequeBook.",
			"Request Credit Card.",
			"Request PassBook.",
			"Apply for a Loan.",
			"Change Address.",
			"Go Back."},
			{"Add Records.",
			"Add Money.",
			"Exit."}};
	int choice;
	start:
	clrscr();
	if(mindex==3)
	{
		cout<<"\tDeveloper mode.\n";
	}
	cout<<"Select from a list of options.\n";
	for(int i = 0;i<aNum[mindex-1];i++)
	{
		cout<<i+1<<". ";
		puts(menu[mindex-1][i]);
	}
	cout<<"Enter your choice. (1-"<<aNum[mindex-1]<<")\n";
	cin>>choice;
	if(choice==0)
		return 0;
	 else if(choice>0&&choice<=aNum[mindex-1])
		return choice;
	cout<<"Wrong Choice! Try Again.\n";
	delay(1000);
	goto start;
}//*****************************************************************
char * Current()
{
	time_t tt;
	struct tm * ti;
	time(&tt);
	ti = localtime(&tt);
	return asctime(ti);
}//*****************************************************************
void AccountInfo(Person P)
{       char ch;
	cout<<"Would you like to have a reciept for the transaction?(y/n)\n";
	cin>>ch;
	void LogCheck(int,int);
	if(ch=='y'||ch=='Y')
	{
		P.Display();
		cout<<"Time of Transaction: "<<Current();
		cout<<"Statement: ";
		cprintf(P.name);
		LogCheck(P.AccountNumber(),1);
	}
}//*****************************************************************
void Log(int ac, char c, float money=0,int ac2=0)
{
	ofstream fout("Log.txt",ios::app);
	ofstream fout1("LogHolde.txt",ios::app);
	Person ScanRecords(int);
	char * str,*str2;
	int len;
	switch(c)
	{
		case 'w': strcpy(str," withdrew ");
			  len = 10;
			  break;
		case 't': strcpy(str," transferred ");
			  len = 13;
			  break;
		case 'r': strcpy(str," recieved ");
			  len = 10;
			  break;
		case 'd': strcpy(str,"Credit Card ");
			  len = 12;
			  break;
		case 'p': strcpy(str,"PassBook ");
			  len = 9;
			  break;
		case 'l': strcpy(str,"Loan ");
			  len = 5;
			  break;
		case 'c': strcpy(str,"ChequeBook ");
			  len = 11;
			  break;
		case 'a': strcpy(str,"change in Address ");
			  len = 18;
			  break;
	}
	if(money>0)
	{
		fout.write(str,len);
		fout<<money<<" Rupees";
		if(c=='t')
		{
			char* name2 = ScanRecords(ac2).name;
			fout<<" to "<<name2;
		}
		else if(c=='r')
		{
			char* name2 = ScanRecords(ac2).name;
			fout<<" from "<<name2;
		}
		fout1<<ac<<'\n';
		fout<<" on "<<Current()<<"\n";
	}
	else if(money==0)
	{
		fout<<" has requested for a ";
		fout.write(str,len);
		fout<<"on "<<Current();
		fout<<'\n';
		fout1<<ac<<'\n';
	}
	fout.close();
	fout1.close();
}//*****************************************************************
void LogCheck(int accn,int rev = 0)
{
	Person ScanRecords(int);
	ifstream fin("Log.txt",ios::in);
	ifstream fin1("LogHolde.txt",ios::in);
	if(!fin||!fin1)
	{
		cout<<"Error! Log File Missing. Press any Key to continue.\n";
		fin.close();
		fin1.close();
		return;
	}
	char str[80], ch,*log,* name = ScanRecords(accn).name;
	int x = 0, ctr = 0, num = 0, * N;
	do
	{
		ctr = 0;
		num = 0;
		fin1.getline(str,10);
		for(ctr=0;isdigit(str[ctr]);ctr++)
		{
				ch = str[ctr];
				x = ch - '0';
				N[ctr] = x;
		}
		ctr--;
		for(int i = ctr;i>=0;i--)
		{
			num = num+(N[i]*pow(10,ctr-i));
		}
		fin.getline(str,80);
		if(num==accn)
		{
			strcpy(log,str);
			if(rev==0)
			{
				cprintf(name);
				cprintf(str);
				cout<<endl;
			}
		}
		fin.getline(str,18);
		continue;
	}while(!fin1.eof());
	if(rev==1)
	{
		cprintf(log);
		cout<<endl;
	}
	fin.close();
	fin1.close();
	return;
}//*****************************************************************
int Update(Person P)
{
	Person P1;
	int flag = 0;
	if(P.AccountNumber()<=0||P.AccountNumber()>Number())
	{
		cout<<"Bad Account Number!";
		return 0;
	}
	ifstream fin("Records.dat",ios::in|ios::binary);
	ofstream fout("temp.dat",ios::out|ios::binary);
	if(!fin||!fout)
	{
		cout<<"Couldn't Update!\n";
		return 0;
	}
	while(!(fin.eof()))
	{
		fin.read((char*)&P1,sizeof(P1));
		if(P1.AccountNumber()==P.AccountNumber()&&flag==0)
		{
			fout.write((char*)&P,sizeof(P));
			flag = 1;
			continue;
		}
		else if(P1.AccountNumber()==P.AccountNumber()&&flag==1)
		{
			continue;
		}
		else
			fout.write((char*)&P1,sizeof(P1));
	}
	if(flag==0)
	{
		cout<<"Record Not Found!\n";
	}
	fout.close();
	fin.close();
	remove("Records.dat");
	rename("temp.dat","Records.dat");
	return 1;
}//*****************************************************************
Person Withdraw(Person P)
{
	float sub;
	cout<<"Enter Money to be Withdrawn!\n";
	cin>>sub;
	if(P.WithdrawCheck(sub))
		if(atm.WithdrawCheck(sub))
		{	cout<<"Here is the Cash! "<<sub<<" Rupees!\n";
			atm.Withdraw(sub);
			P.Withdraw(sub);
			atm.Update(2);
			Update(P);
			Log(P.AccountNumber(),'w',sub);
			return P;
		}
	Person P1;
	return P1;
}//*****************************************************************
Person Transfer(Person P1)
{
	Person ScanRecords(int);
	Person P;
	float money;
	int accn;
	char ch;
	cout<<"Enter the Account Number in which you wish to transfer.\n";
	cin>>accn;
	if(accn==P1.AccountNumber())
	{
		cout<<"Can't transfer to self. Aborting!\n";
		return P;
	}
	Person P2 = ScanRecords(accn);
	if(P2.AccountNumber()==0)
	{
		cout<<"The Requested Account Number Doesn't Exist!\n";
		return P;
	}
	cout<<"Enter Amount of money to be transferred.\n";
	cin>>money;
	if(P1.WithdrawCheck(money))
	{
		cout<<"You have "<<P1.Amount()<<" Rupees in your account."
		<<"\nAre you sure you want to transfer "<<money<<" Rupees to ";
		cprintf(P2.name);
		cout<<"\'s account?(y/n)\n";
		cin>>ch;
		cin.ignore();
		if(ch=='Y'||ch=='y')
		{
			P1.Withdraw(money);
			P2.Deposit(money);
			cout<<money<<" Rupees transferred succesfully.\n";
			Update(P1);
			Update(P2);
			Log(P1.AccountNumber(),'t',money,P2.AccountNumber());
			Log(P2.AccountNumber(),'r',money,P1.AccountNumber());
			return P1;
		}
		else
			return P;
	}
	else
	{
		cout<<"Not Enough Money in your Account. Try a lower amount!\n";
		return P;
	}
}//*****************************************************************
int Execute(Person P,int choice)
{
	Person ScanRecords(int);
	int i = 0;
	char ch;
	if(mindex==1)
	{
	switch(choice)
	{
		case 1: P = Withdraw(P);
			if(P.AccountNumber())
				AccountInfo(P);
			break;
		case 2: P.Display();
			break;
		case 3:	LogCheck(P.AccountNumber());
			break;
		case 4: P = Transfer(P);
			if(P.AccountNumber())
				AccountInfo(P);
			break;
		case 5: P.SecurityQuestion();
			Update(P);
			break;
		case 6: P.ChangePIN();
			Update(P);
			break;
		case 7: cout<<"Accessing!\n";
			delay(500);
			break;
		case 8: cout<<"Quitting Session! Have a Nice Day!\n";
			break;
	}
	}
	else if(mindex==2)
	{
	switch(choice)
	{
		case 1: cout<<"Your Selected Address is ";
			cprintf(P.Address());
			cout<<".\nDo you wish to Procure a ChequeBook?(y/n)\n";
			cin>>ch;
			if(ch=='y'||ch=='Y')
			{cout<<"Request Processed Succesfully! "
			<<"It will Arrive in the Mail in about 48 hours.";
			Log(P.AccountNumber(),'c');}
			break;
		case 2: cout<<"Your Selected Address is ";
			cprintf(P.Address());
			cout<<".\nDo you wish to Request a Credit Card?(y/n)\n";
			cin>>ch;
			if(ch=='y'||ch=='Y')
			{cout<<"Request Processed Succesfully! "
			<<"It will Arrive in the Mail in about 48 hours.";
			Log(P.AccountNumber(),'d');}
			break;
		case 3: cout<<"Your Selected Address is ";
			cprintf(P.Address());
			cout<<".\nDo you wish to Procure a PassBook?(y/n)\n";
			cin>>ch;
			if(ch=='y'||ch=='Y')
			{cout<<"Request Processed Succesfully! "
			<<"It will Arrive in the Mail in about 48 hours.";
			Log(P.AccountNumber(),'p');
			}
			break;
		case 4: cout<<"Do you wish to Apply for a Loan?(y/n)\n";
			cin>>ch;
			if(ch=='y'||ch=='Y')
			{
				cout<<"Request Processed Succesfully! "
				<<"You will be contacted by our executive in "
				<<"about 48 hours.";
				Log(P.AccountNumber(),'l');
			}
			break;
		case 5: cout<<"Do you wish to change your Address?(y/n)\n";
			cin>>ch;
			if(ch=='y'||ch=='Y')
			{
				cin.ignore();
				P.ChangeAddress();
				Update(P);
				Log(P.AccountNumber(),'a');
			}
			break;
		case 6: cout<<"Going Back!\n";
			delay(700);
			break;
	}
	}
return 0;
}//*****************************************************************
Person Login(int a=0)
{
	int accn;
	Person ScanRecords(int);
	Person P1(-1),person,P2(-9009);
	if(a>0)
	{
		Person P = ScanRecords(a);
		return P;
	}
	if(Number()==0)
	{
		cout<<"Not Enough Records!\n";
		return P1;
	}
	login:
		clrscr();
		cout<<"Welcome to the ATM!\n";
		cout<<"Enter Your Account Number!\n";
		cin>>accn;
		if(accn==0)
		{
			Person P3(0);
			return P3;
		}
		if(accn==-1)
		{
			return P2;
		}
		person = ScanRecords(accn);
		if(person.accountNumber>0&&person.accountNumber<=Number())
		{
			cout<<"Welcome ";
			cprintf(person.name);
			cout<<"!\n";
			if(getPIN(person)==1)
			{
				return person;
			}
			else
			{
				if(person.RecoverPIN()==1)
				{
					return person;
				}
				else
				{	delay(2000);
					goto login;
				}
			}
		}
		else
		{	cout<<"Bad Account number!\n";
			delay(1000);
			goto login;
		}
}//*****************************************************************
void AddRecords()
{
	char ch = 'n';
	int a = 0;
	ofstream fout("Records.dat",ios::app|ios::binary);
	do
	{
		a = Number(1);
		cout<<"Person "<<a<<".\n";
		Person P(a);
		P.Input();
		fout.write((char *)&P, sizeof(P));
		cout<<"Do you wish to add more records?(y/n)\n";
		cin>>ch;
		cin.ignore();
	}while(ch=='Y'||ch=='y');
	fout.close();
}//*****************************************************************
Person ScanRecords(int accno=-1000)
{
	Person P1;
	ifstream fin("Records.dat",ios::in|ios::binary);
	while(!fin.eof())
	{
		fin.read((char*)&P1,sizeof(P1));
		if(accno==-1000)
		{
			P1.Display();
			continue;
		}
		if(P1.AccountNumber()==accno)
		{
			fin.close();
			return P1;
		}
	}
	fin.close();
	Person P2;
	return P2;
}//*****************************************************************
int main()
{
	clrscr();
	int choice,i=0,logi = 0,ctr=0;
	login:
	Person P = Login(logi);
	logi = P.AccountNumber();
	if(logi==0)
		goto exit;
	if(logi==-1)
	{
		char ch = '\0';
		while(ch!='&')
		{
			ch = getch();
		}
		goto developer;
	}
	if(logi==-9009)
		goto developer;
		//Loop
	choice:
	choice = Menus();
	if(choice==0)
		goto exit;
	i = Execute(P,choice);
	if(choice==7&&mindex==1)
	{
		mindex = 2;
		goto login;
	}
	if(choice==6&&mindex==2)
	{
		mindex = 1;
		goto login;
	}
	if(choice==8&&mindex==1)
	{
		logi = 0;
		delay(1000);
		goto login;
	}
	getch();
	goto login;
	developer:
	mindex = 3;
	choice = Menus();
	cin.ignore();
	if(choice==0)
	{
		goto exit;
	}
	if(choice==1)
		AddRecords();
	else if(choice==2)
	{	atm.Deposit();
		cout<<"Money Deposited!\n";
		delay(1000);
	}
	else if(choice==3)
	{
		cout<<"Exiting!\n";
		delay(1000);
		mindex = 1;
		goto login;
	}
	goto developer;
	exit:
	cout<<"System Override! Press any key to exit!\n";
	getch();
	return 0;
}
