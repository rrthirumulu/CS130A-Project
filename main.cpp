#include "node.h"
#include "linkedlist.h"
#include "wallpost.h"
#include "wall.h"
#include "user.h"
#include "usernetwork.h"
#include <iostream>
using namespace std;

int main()
{
  UserNetwork * usenet = new UserNetwork();
  usenet->read();
  string input = "xxx";
 
  while (input != "3")
  {
	cout << "1. create user\n2. login\n3. quit program" << endl;
    getline(cin, input);
    if(input[0] == '1')
    {
	  cout << "username: " << endl;
	  getline(cin, input);
	  cout << "password: " << endl;
	  string pass;
	  getline(cin, pass);
      if (!usenet->addUser(input, pass)) cout << "There was an error creating the user. Try a different username." << endl;    
	
	}

    if(input[0] == '2')
    {
      cout << "username: " << endl;
	  string user, pass;
	  getline(cin, user);
	  cout << "password: " << endl;
	  getline(cin, pass);

      User x =  usenet->find(user) ;


      if (x.getPassword() == pass)
	  {
		input = "";
        cout << "Sucessfully Logged in." << endl;
        while(input != "2")
		{

        if(input[0] == '1')
		  cout << x.write() << endl;


        cout << "1. Display Wall\n2. logs out" << endl;

        getline(cin, input);
		}

	  }
	  else cout << "There was an error" << endl;
    }
  }

}
