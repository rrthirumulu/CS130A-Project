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
 
  while (input != "\n")
  {
	cout << "1. create user\n2. login" << endl;
    getline(cin, input);
    if(input[0] == '1')
    {
	  cout << "username: " << endl;
	  getline(cin, input);
	  cout << "password: " << endl;
	  string pass;
	  getline(cin, pass);
      usenet->addUser(input, pass);    
	
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
        while(input != "quit")
		{

        if(input[0] == '1')
		  cout << x.write() << endl;


        cout << "1. Display Wall\nquit. logs out" << endl;

        getline(cin, input);
		}

	  }
	  else cout << "There was an error" << endl;
    }
  }

}
