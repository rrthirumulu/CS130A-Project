#include "node.h"
#include "linkedlist.h"
#include "wallpost.h"
#include "wall.h"
#include "user.h"
#include "usernetwork.h"
#include "list.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
using namespace std;

int main()
{
  UserNetwork * usenet = new UserNetwork();
  usenet->read();
  usenet->read_friends();
//  cout << "Here i am:" <<  usenet->find("charlie").getUsername() << endl;
//  usenet->find("charlie").print_friends();
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

      User & x =  usenet->find(user) ;


      if (x.getPassword() == pass)
	  {
		input = "";
        cout << "Sucessfully Logged in." << endl;
       



        //Check for friend requests and handle
        string l, ll;
        bool frequest = false;
        ifstream myfriends ("friend_requests.txt");
        int i = 0;
        map<int, string> names;
        if(myfriends.is_open())
        {
          while(getline(myfriends, l) && getline(myfriends, ll) )
          {
            if(ll == x.getUsername())
            {
              if (frequest == false) cout << "You have some friend requests!" << endl;
              frequest = true;
              names[i] = l;
              i++;
            }
          }
          cout << "i variable counter: " << i << endl;
          for(int j=0; j<i; j++)
            cout << j << ". " << names[j] << endl;
        }
        myfriends.close();
        // Output variable: names (names[1], names[2])


        // Add friend to friend list
        std::ofstream add_friends;
        add_friends.open("data_friends.txt", std::ios_base::app);
        while(l[0] != 'c' && l[0] != 'C' && names.size() != 0)
        {
         try {
          cout << "Please enter a number to add friend. Enter 'C' to continue" << endl;
          for(int i=0; i<names.size(); i++)
            if( names[i].length() > 0 )
              cout << i << ". " << names[i] << endl;
          getline(cin, l);
          cout << "You have successfully added " << names[stoi(l)] << endl;
          add_friends << names[stoi(l)] << "\n" << x.getUsername() << endl;
          names.erase(stoi(l));
         } catch (std::invalid_argument e) {}
        }




        // Rewrite friend_requests.txt from map AND file
        ifstream my_f("friend_requests.txt");
        map<string, string> relation;
        string write_to;
        if(my_f.is_open())
        {
          while(getline(my_f, l) && getline(my_f, ll) )
            if (ll != x.getUsername())
            {
              relation[l] = ll;
              //cout << "ADDING TO RELATION:" << l << "\t" << ll << endl;
              write_to += l + "\n" + ll + "\n";
            }
        }
        my_f.close();

        //cout << relation.size() << endl;
        // Add everything related to username (but NOT the already added friends)
        //cout << "BEGIN: " << endl; 
        for (std::map<int, string>::iterator it=names.begin(); it!=names.end(); ++it)
        {
          //cout << it->second << it->second.length() << endl;
          if((it->second).length() > 1)
          {
            relation[it->second] = x.getUsername();
            //cout << "ADDING TO RELATION:" << it->second << "\t" << x.getUsername() << endl;
            write_to += it->second + "\n" + x.getUsername() + "\n";
          }
        }
        //cout << "END" << endl;
        //cout << relation.size() << endl; //// BEGIN HERE SIZE IS BAD
        //for(std::map<string, string>::iterator it = relation.begin(); it !=relation.end(); ++it)
        //  cout << it->first << " => " << it->second << endl;
        //cout << "HERE:\n" << write_to << endl; 


        // WRITE TO FILE
        ofstream newFile("friend_requests.txt");
        newFile << write_to;
        newFile.close();







        while(input != "2")
		{

        if(input[0] == 'a') // Create a new wallpost
        {
          cout << "You chose to create a new wall post.\nEnter your post:" << endl;
          string post;
          getline(cin, post);
          x.addPost(post, x.getUsername());
        }
        if(input[0] == 'b') // Delete a wallpost
        {
          cout << "Please enter the # of the wallpost from the top (index 0) you wish to delete:" << endl;
          string num; getline(cin, num);
          x.deletePost( stoi(num) ); // stoi needs -std=c++11 flag when compiling
        }
        if(input[0] == 'c') // Edit a wallpost
        {
          cout << "Please enter a new password:"<<endl;
          string pass; getline(cin, pass);
          x.setPassword(pass);
        }
        if(input[0] == 'd')
        {
          ofstream myfile;
          myfile.open("data.txt");
          myfile << usenet->write();
          myfile.close();
          cout << usenet->write() << endl;
          break;
        }
        if(input[0] == 'e')
        {
          cout << "Are you sure? (y/n):" << endl;
          string conf;  getline(cin, conf);
          if( conf[0] == 'y' || conf[0] == 'Y')
          {
            // Handle WALL
            bool turnt = false;
            string name = x.getUsername();
            std::ifstream myfile("data.txt");
            string line, complete="";
            if(myfile.is_open())
            {
              while( getline(myfile, line) ){
                if(line==name) turnt = true;
                if(line[0]==0) turnt = false;
                if( !turnt ) complete += line + "\n";
              }
              myfile.close();
            }
            ofstream myf;
            myf.open("data.txt");
            myf << complete;
            myf.close();
            // Handle Friends

            break;
          }
        }
        if(input[0] == 'f') // Search for user
        {
          cout << "Which user would you like to search for?" << endl;
          string n;
          bool not_found = true;
          getline(cin, n); int i =0; 
          for(Node<User> * tmp =usenet->begin(); tmp != NULL; i++, tmp=tmp->next)
          {
            size_t found = tmp->getData().getUsername().find(n);
            if (found != std::string::npos)
            {
              if(not_found)
                cout << "Please choose one of the following numbers:"<<endl;
              cout << i << ". " << tmp->getData().getUsername() << endl;
              not_found = false;
            }
          }
          // Select the result
          if(not_found)
          {
            cout << "There was no user that matched" << endl;
            break;
          }
          getline(cin, n);
          x.send_friend_request(usenet->get(stoi(n)).getUsername());

        }
        if(input[0] == 'i') // Display/delete friends
        {
          vector<string> my_friends;
          // Read all friends into array
          ifstream myfriends ("data_friends.txt");
          if(myfriends.is_open())
          {
            while(getline(myfriends, l) && getline(myfriends, ll) )
            {
              if (l  == x.getUsername())
                my_friends.push_back( ll );
              if (ll == x.getUsername())
                my_friends.push_back( l  );
            }
          }
          myfriends.close();

          while(input[0] != 'c')
          {
            if (my_friends.size() == 0)
            {
              cout << "You have no friends :)" << endl;
              break;
            }


            cout << "Enter the number of the friend to delete, or press c to continue" << endl;
            // Display friends
            vector<string>::const_iterator i;
            int j =0 ;
            for(i = my_friends.begin(); i != my_friends.end(); ++i, j++)
            {
             cout << j << ".\t" << *i << endl; 
            }
          

            // Delete Friend from file
       

            getline(cin, input);
            if (input[0] != 'c')
            {
              string my_deleted = my_friends[stoi(input)]; 
              string outf;
              ifstream myfriends2 ("data_friends.txt");
              if(myfriends2.is_open())
              {
                while(getline(myfriends2, l) && getline(myfriends2, ll))
                {
                  if( !( (l == my_deleted && ll == x.getUsername() ) || (l == x.getUsername() && ll == my_deleted) ) )
                    outf += l + "\n" + ll + "\n";
                }
              }

              ofstream my_d("data_friends.txt");
              my_d << outf;
              my_d.close();

              // Remove from list
              my_friends.erase(my_friends.begin() + stoi(input));
            }

          }
        }



        if(input[0] == '1') // Display Wall
		  cout << x.write() << endl;


        cout << "1. Display Wall\n2. Log out" << endl;
        cout << "a. Create wallpost\nb. Delete wallpost\nc. Change your password\n" 
             << "d. Logout\ne. Delete account\nf. Search for friends to add.\n"
             << "i. Display/delete friends" << endl;
        getline(cin, input);
		}

	  }
	  else cout << "There was an error" << endl;
    }
  }

}
