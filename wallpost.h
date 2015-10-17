#ifndef WallPost_H
#define WallPost_H
#include <iostream>
/**
  * A class for wallposts by users in social network
  */

class WallPost
{
	public:
	    WallPost(const WallPost&);
		WallPost(std::string);
		WallPost(std::string p, std::string u); //constructor
		~WallPost(); //destructor
		std::string getPost();
		void setPost( std::string p );
		std::string getTime();
		void updateTime();
		std::string getUsername();
		void setUsername(std::string n);		
		std::string getAllData();

	private:
		std::string post; //user's post
		std::string time; //time post is created/modified
		std::string username; //author's username
};

#endif
