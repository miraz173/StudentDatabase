#include <iostream>
#include <fstream>
#include <cstring>
//#include <string>
//#include <sstream>

using namespace std;  // People says it's bad. use "std::cin" instead of "cin" and remove "using namespace std".

void RemoveAccount(string ID_txt);
string StringInput();
void HomeScreen();
void Register();
void Login();


int main()
{
    HomeScreen();
	return 0;
}

void RemoveAccount(string ID_txt)
{
	if (remove(ID_txt.c_str())!=0)
	{
		cout << "failed to delete!"<<endl;
		perror("account removal failed");
	}
	else //(remove(ID_txt.c_str())==0)
	{
		cout << "Successfully deleted!"<< endl;
		exit(EXIT_SUCCESS);
	}
}

string StringInput()  //returns null-terminated string
{
    string input;
    getline(cin, input);
    while(input.length()==0)
    {
        getline(cin, input);
    }
    return input.c_str();
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
		StringInput();  /*print the info from text file*/
	}
}

void Register()
{
	string name, ID_txt, ID;
    char password[20], confirmpassword[20];
	cout << "Registration-->\nEnter Username: ";
	ID = StringInput();
	ID_txt = ID;
    ID_txt = ID_txt + ".txt";
    ifstream inputfromfile(ID_txt); //tries to open file to write or read (?)
    if(inputfromfile) //inputfromfile =1/file is opened; which means file already exists, id already exists
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



    cout<< "Name: "; name = StringInput(); cout<< "Password: "; cin >> password; cout<< "Confirm Password: "; cin >> confirmpassword;
    if (strcmp(password, confirmpassword)!=0)
    {
    	cout<<"Password mismatched\n";
    	cout <<"Try again\n";
    	Register();
    	exit(EXIT_SUCCESS);
    }

    ofstream WriteUserData;
    WriteUserData.open(ID_txt);

    WriteUserData << ID << "\n" << name <<"\n"<< password << endl;
    WriteUserData.close();
    cout << "Registration Successfull\n" << endl;
}

void Login()
{
	string name, ID_txt, ID;
    char password[20], confirmpassword[20], filepassword[20];
	cout << "Login-->\nEnter Username: ";
	ID = StringInput();
	ID_txt = ID;
    ID_txt = ID_txt + ".txt";
    ifstream inputfromfile;
    inputfromfile.open(ID_txt.c_str());
    if(!inputfromfile) //if file couldn't be opened
    {
    	cout <<"\nInvalid Username.\nEnter 1 to try again, Enter 2 to return to Home-screen.\n";
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
    getline(inputfromfile, ID); getline(inputfromfile, name); inputfromfile.getline(filepassword, 20, '\n'); // I want to read the password only. how to do it?
    if (strcmp(password, filepassword)!=0)
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

    cout <<"Your Username: "<< ID << "\n" <<"Your Name: " << name << "\n" << "What would you like to do now?\nEnter 5 to remove account.\n";
    int x; cin >> x;
    if (x == 5)
    {
    	RemoveAccount(ID_txt.c_str());
    }
}