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
#include <algorithm>
//#include <list>
#include <typeinfo>

using namespace std;

int find_apart(string , string, bool);
void print_vec(vector< vector<string> >);
void print_vec(vector<string>);
bool contains(vector<string>, string);
bool contains(vector< vector<string> >, string);

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

      if (usenet->exists(user) && x.getPassword() == pass)
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
          //for(int j=0; j<i; j++)
            //cout << j << ". " << names[j] << endl;
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






        input = "";
        while(input != "2")
		{
        usenet->write(); // REFRESH FILE STREAM

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
        /*
        if(input[0] == 'd')
        {
          ofstream myfile;
          myfile.open("data.txt");
          myfile << usenet->write();
          myfile.close();
          cout << usenet->write() << endl;
          break;
        }*/
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

        if(input[0] == 'j') // Add post to friends wall.
        {
          // Choose the friend/
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
          if (my_friends.size() == 0)
          {
            cout << "You have no friends :)" << endl;
            break;
          }
          cout << "Enter the number of the friend." << endl;
          // Display friends
          vector<string>::const_iterator i;
          int j =0 ;
          for(i = my_friends.begin(); i != my_friends.end(); ++i, j++)
          {
            cout << j << ".\t" << *i << endl;
          }

          getline(cin, input);
          string my_frnd = my_friends[stoi(input)];
          User & y =  usenet->find(my_frnd);

          cout << "Write on " << my_frnd << "'s wall:" << endl;
          string post;
          getline(cin, post);
          y.addPost(post, x.getUsername());


        }

        if(input[0] == 'k')
        {
          // Choose the friend/
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
          if (my_friends.size() == 0)
          {
            cout << "You have no friends :)" << endl;
            break;
          }
          cout << "Enter the number of the friend." << endl;
          // Display friends
          vector<string>::const_iterator i;
          int j =0 ;
          for(i = my_friends.begin(); i != my_friends.end(); ++i, j++)
          {
            cout << j << ".\t" << *i << endl;
          }

          getline(cin, input);
          string my_frnd = my_friends[stoi(input)];
          
          // GET FRIENDS WALL:
          User & y =  usenet->find(my_frnd);
          Node<WallPost> * wallptr = y.getWall()->begin();
          int ii = 0;
          bool found = false;
          for(Node<WallPost> * ptr = wallptr; ptr != NULL; ptr=ptr->next, ii++)
          {
            if(ptr->getData().getUsername() == x.getUsername() )
            {
              found = true;
              cout << ii << ". " << ptr->getData().getPost() << endl;
            }
          }
          if(!found)
          {
            cout << "You have not posted on this users wall!" << endl;
            break;
          }
          cout << "Number of post you wish to delete: " << endl;

          getline(cin, input);
          y.deletePost( stoi(input) ); // stoi needs -std=c++11 flag when compiling
          cout << "Successful" << endl;
        }

        





        if(input[0] == 'm') // delete comment on friend
        {
          string name, numb, commenter, comment;

          // Choose the friend/
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
          if (my_friends.size() == 0)
          {
            cout << "You have no friends :)" << endl;
            break;
          }
          cout << "Enter the number of the friend." << endl;
          // Display friends
          vector<string>::const_iterator i;
          int j =0 ;
          for(i = my_friends.begin(); i != my_friends.end(); ++i, j++)
          {
            cout << j << ".\t" << *i << endl;
          }

          getline(cin, input);
          string my_frnd = my_friends[stoi(input)];

          // GET FRIENDS WALL:
          User & y =  usenet->find(my_frnd);
          Node<WallPost> * wallptr = y.getWall()->begin();
          int k =0, kk=0;
          for(Node<WallPost> * ptr = wallptr; ptr != NULL; ptr = ptr->next, kk++)
          {
            cout << ptr->getData().getAllData();
            // Open comment file, see if it exists for current user, display
            ifstream my_com ("data_comments.txt");
            if(my_com.is_open())
            {
              while( getline(my_com, name) && getline(my_com, numb) && getline(my_com, commenter) && getline(my_com, comment) )
              {
                if(y.getUsername() == name && x.getUsername() == commenter && stoi(numb) == kk)
                {
                  cout << k << "\t" << commenter << ": " << comment << endl;
                  k++;
                }
              }
            }
          }

          if(k == 0) cout << "There were no comment's to delete.. sorry!" << endl;
          else
          {
            k=0; 
            cout << "Select a comment to delete: "<< endl;
            getline(cin, input);
            int my_deleted_comment = stoi(input);
            string write_file;
            ifstream my_com ("data_comments.txt");
            if(my_com.is_open())
            {
              while( getline(my_com, name) && getline(my_com, numb) && getline(my_com, commenter) && getline(my_com, comment) )
              {
                if(y.getUsername() == name && x.getUsername() == commenter)
                  k++;
                if( !(y.getUsername() == name && x.getUsername() == commenter && my_deleted_comment == k-1) )
                  write_file += name+"\n"+numb+"\n"+commenter+"\n"+comment+"\n";
              }
            }
             
            cout << write_file << endl;

            std::ofstream remove_comments;
            remove_comments.open("data_comments.txt");
            remove_comments << write_file << endl;
            remove_comments.close();
          }
        }

          if(input[0] == 'p')
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
          getline(cin, n);
          if(not_found)
          {
            cout << "There was no user that matched" << endl;
          } else {
          cout << "You and " << usenet->get(stoi(n)).getUsername() 
               << " are " <<
          find_apart(x.getUsername(), usenet->get(stoi(n)).getUsername(), false)
               << " friend(s) apart" << endl;
          }
          }


          if(input[0] == 'q') find_apart(x.getUsername(), "re-using functions is fun!", true);



        if(input[0] == 'r')
        {
        if(usenet->exists("my_created_user_"+to_string(999))) cout << "You can only call this function once" << endl;
        else{
          // Create 100000 people.
          vector<User> lots;
          for(int i=0; i < 1000; i++)
          {
           usenet->addUser("my_created_user_"+ to_string(i), "my_password_"+to_string(i));
           usenet->write();
           User & my_user_i = usenet->find("my_created_user_"+to_string(i));
           if(i > 100)
           {
            std::ofstream add_lots;
            add_lots.open("data_friends.txt", std::ios_base::app);
            for(int j = i-100; j<i; j++)
              add_lots << "my_created_user_" << to_string(i) << "\nmy_created_user_" << to_string(j) << endl;
            
           }
           for(int j = 0; j<5; j++)
            my_user_i.addPost("My name is " + to_string(i) + " and this is post #" + to_string(j));
          }
        }}










        if(input[0] == 'l') // View or comment on friend
        {
          string name, numb, commenter, comment;

          // Choose the friend/
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
          if (my_friends.size() == 0)
          {
            cout << "You have no friends :)" << endl;
            break;
          }
          cout << "Enter the number of the friend." << endl;
          // Display friends
          vector<string>::const_iterator i;
          int j =0 ;
          for(i = my_friends.begin(); i != my_friends.end(); ++i, j++)
          { 
            cout << j << ".\t" << *i << endl;
          }

          getline(cin, input);
          string my_frnd = my_friends[stoi(input)];

          // GET FRIENDS WALL:
          User & y =  usenet->find(my_frnd);
          Node<WallPost> * wallptr = y.getWall()->begin();
          int k =0;
          for(Node<WallPost> * ptr = wallptr; ptr != NULL; ptr = ptr->next, k++)
          {
            cout << k << ". " << ptr->getData().getAllData();
            // Open comment file, see if it exists for current user, display
            ifstream my_com ("data_comments.txt");
            if(my_com.is_open())
            {
              while( getline(my_com, name) && getline(my_com, numb) && getline(my_com, commenter) && getline(my_com, comment) )
              {
                if(y.getUsername() == name && stoi(numb) == k)
                  cout << "\t" << commenter << ": " << comment << endl;
              }
            }
          }
          cout << "Please enter the number you wish to comment on, or 'c' to continue" << endl;
          getline(cin, input);
          if (input[0] == 'c') goto finald;

          // Make comment file.
          // <name>
          // number
          // <commenter name>
          // <comment>
          // REPEAT
          name = my_frnd;
          numb = input;
          commenter = x.getUsername();
          cout << "Please enter your comment" << endl;
          getline(cin, comment);
          
          std::ofstream add_comments;
          add_comments.open("data_comments.txt", std::ios_base::app);
          add_comments << name << "\n" << numb << "\n" << commenter << "\n" << comment << "\n";
          add_comments.close();
        }




        

        if(input[0] == '1') // Display Wall
		  cout << x.write() << endl;

        finald:
        cout << "1. Display Wall\n2. Log out" << endl;
        cout << "a. Create wallpost\nb. Delete wallpost\nc. Change your password\n" 
             << "e. Delete account\nf. Search for friends to add.\n"
             << "i. Display/delete friends\n" 
             << "j. Add post to Friends wall\n"
             << "k. View/delete post from Friends wall\n" 
             << "l. View/comment friends wall\n" 
             << "m. Delete comment from friends wall\n" 
             << "p. Find degree of separation\n"
             << "q. Show all friends with degree of separation = 3\n"
             << "r. Populate data with 10000's of peoples." << endl;
        getline(cin, input);
		}

	  }
	  else cout << "There was an error" << endl;
    }
  }

} 
int find_apart(string begin, string user, bool print_list)
{
 // cout << "ENTER" << endl;
  vector< vector<string> > friends;
  vector< string > used { begin };
  vector< vector<string> > degree(1);
  string tmp1, tmp2;
  
  ifstream file ("data_friends.txt");

  // Push to friends
  // [Friend 1, Friend 2]
  // [Friend 1, Friend 3]
  // [Friend 3, Friend 4]
  while(getline(file, tmp1), getline(file, tmp2))
    friends.push_back( {tmp1, tmp2} );

//cout << "FRIENDS:" << endl;
//print_vec(friends);
//cout << contains(friends, "a");

  // Push the 0-degree friends into degree and used
  //for(vector< vector<string> >::iterator it = friends.begin(); it != friends.end(); ++it)
  for(size_t it = 0; it < friends.size(); it++)
  {
    if( friends[it][0] == begin )
    {
      //if(friends[it][1] == user) return 0;
      degree[0].push_back(friends[it][1]);
    }
    if( friends[it][1] == begin )
    {
      //if(friends[it][0] == user) return 0;
      degree[0].push_back(friends[it][0]);
    }
  }
 // cout << "DEGREE:" << endl;
  //print_vec(degree);
  //vector<string> tmp;
  // Loop through degree
  vector<string> tmp;
  for(size_t it = 0; it < degree.size(); it++)
  {
   // cout << "Degree size: " << degree.size() << endl;
   // cout << "iterator: " << it << endl;
   // cout << "USED: "; print_vec(used);
   // cout << "TMP: "; print_vec(tmp);
    tmp.clear();
    //Loop through each element of degree
    for(size_t it2 = 0; it2 < degree[it].size(); it2++)
    { //cout << "Loop each element: " << degree[it][it2] << endl;
      // If username has not already been used:
      vector<string>::iterator ax = find(used.begin(), used.end(), degree[it][it2]);
      //if( ax != used.end() )
      //
      
      //
      //
      //
      
      if( !(contains( used,  degree[it][it2]) ) )
      { 
        //cout << "Not found in used :D" << endl;
        used.push_back(degree[it][it2]);
        // Find its friends and add them to tmp if they have not been used.
        for(size_t it3 =0; it3 < friends.size(); it3++)
        { //cout << "Looking at friends: " << friends[it3][0] << " | " << friends[it3][1] << endl;
          if(friends[it3][0] == degree[it][it2] && find(used.begin(), used.end(), friends[it3][1]) == used.end() )
            tmp.push_back(friends[it3][1]);
          if(friends[it3][1] == degree[it][it2] && find(used.begin(), used.end(), friends[it3][0]) == used.end() )
            tmp.push_back(friends[it3][0]);
        }
      } //else cout << *ax << " already in used, not searching" << endl;
    }
    if (tmp.size() )
    {
 //     if( contains( tmp, user)) return it;
      degree.push_back(tmp);
    }
  }



  if(print_list)
  {
    if(degree.size() < 3) cout << "tit" << endl;
    else{
      cout << "Friends that are 3 away: ";
      print_vec(degree[2]);
      }
    
  }




  for(size_t it = 0; it < degree.size(); it++)
  {
    if( contains( degree[it], user ) ) return it;
  }



  //print_vec(degree);
  return -1;
  //cout << "EXIT" << endl;
}

void print_vec( vector< vector<string> > v)
{
  int j =0;
  for(vector <vector<string> >::iterator it = v.begin(); it != v.end(); ++it)
  {
    cout << j++ << ". ";
    for(vector<string>::iterator i = (*it).begin(); i != (*it).end(); ++i)
      cout << *i << " | ";
    cout << "\b\b  " << endl;
  }
}

void print_vec( vector<string> v)
{
  for(size_t x=0; x < v.size(); x++)
    cout << v[x] << " | ";
    cout << "\b\b  " << endl;
}

bool contains( vector<string> v, string s)
{
  for(size_t it=0; it < v.size(); it++)
    if(v[it] == s) return true;
  return false;

}

bool contains( vector< vector<string> > v, string s)
{
  for(size_t it=0; it < v.size(); it++)
    if (contains(v[it], s)) return true;
  return false;
}
