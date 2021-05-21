#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;  // People says it's bad

void RemoveAccount(char ID[]);
void HomeScreen();
void Register();
void Login();
void IDK();

int main()
{
    HomeScreen();
	return 0;
}

void RemoveAccount(char ID[])
{
	if (remove(ID)!=0)
	{
		cout << "failed to delete!"<<endl;
		perror("account removal failed");
	}
	else 
	{
		cout << "Successfully deleted!"<< endl;
		exit(EXIT_SUCCESS);
	}
}

void HomeScreen()
{
	int UserChoice;

	cout << "Enter 1 to Register \nEnter 2 to Login \nEnter 3 to IDK \nEnter 0 to escape" <<endl;
	cin >> UserChoice;

	if (UserChoice == 0)
	{
		cout << "Successfully exited.\n";
		exit(EXIT_SUCCESS);
	}

	else if (UserChoice == 1)
	{
		Register(); /*Check if available, if not; Register */
	}

	else if (UserChoice == 2)
	{
		Login();/*If available, login; if not, suggest register */
	}

	else if (UserChoice == 3)
	{
		IDK();  /*print the info from text file*/
	}
}

void Register()
{
	char name[20], password[20], confirmpassword[20], ID[20], id1[20];
	cout << "Registration-->\nEnter Username: ";
	cin >> ID;
	strcpy(id1, ID);
    strcat(ID,".txt");
    ifstream inputfromfile(ID);
    if(inputfromfile)
    {
    	cout <<"\nID already in use.\nEnter 1 to try again, Enter 2 to return to Home-screen.Enter others to escape\n";
    	int UserChoice;
    	cin >> UserChoice;
    	if(UserChoice==1)
        {
            Register();
            exit(EXIT_SUCCESS);
        }
        else if(UserChoice == 2)
        {
            HomeScreen();
            exit(EXIT_SUCCESS);
        }
        else
        {
            exit(EXIT_SUCCESS);
        }
    }



    cout<< "Name: "; cin>> name; cout<< "Password: "; cin>> password; cout<<"Confirm Password: "; cin>> confirmpassword;
    if (strcmp(password, confirmpassword)!=0)
    {
    	cout<<"Password mismatched\n";
    	cout <<"Try again\n";
    	Register();
    	exit(EXIT_SUCCESS);
    }

    ofstream WriteUserData;
    WriteUserData.open(ID);

    WriteUserData << id1 << "\n" << name <<"\n"<< password << endl;
    WriteUserData.close();
    cout << "Registration Successfull\n" << endl;
}

void Login()
{
	char name[20], password[20], filepassword[20], ID[20], id1[20];
	cout << "Login-->\nEnter Username: ";
	cin >> ID;
	strcpy(id1, ID);
    strcat(ID,".txt");
    ifstream inputfromfile;
    inputfromfile.open(ID);
    if(!inputfromfile)
    {
    	cout <<"\nInvalid ID.\nEnter 1 to try again, Enter 2 to return to Home-screen.\n";
    	int UserChoice;
    	cin >> UserChoice;
    	if(UserChoice==1)
        {
            Login();
            exit(EXIT_SUCCESS);
        }
        else if(UserChoice == 2)
        {
            HomeScreen();
            exit(EXIT_SUCCESS);
        }
        else
        {
            exit(EXIT_FAILURE);
        }
    }

    cout << "Password: "; cin >> password;
    inputfromfile >> id1 >> name >> filepassword; // i want to read  the password only. how to do it?
    if (strcmp(password, filepassword) != 0)
    {
    	cout<< "Wrong Password.\nEnter 1 to try again, Enter 2 to return to Home-screen.\n";
    	int UserChoice;
    	cin >> UserChoice;
    	if(UserChoice==1)
        {
            Login();
            exit(EXIT_SUCCESS);
        }
        else if(UserChoice == 2)
        {
            HomeScreen();
            exit(EXIT_SUCCESS);
        }
        else
        {
            exit(EXIT_FAILURE);
        }
    }
    inputfromfile.close();

    cout <<"Your Username: "<< id1 << "\n" <<"Your Name: " << name << "\n" << "What would you like to do now?\nEnter 5 to remove account.\n";
    int x; cin >> x;
    if (x == 5)
    {
    	RemoveAccount(ID);
    }
}

void IDK()
{
	string Name;
	getline(cin, Name);
	while(Name.length()==0)
	{
		getline(cin,Name);
	}
	cout << Name;
}

