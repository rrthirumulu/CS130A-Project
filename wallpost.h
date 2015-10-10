#ifndef WallPost_H
#define WallPost_H

/**
  * A class for wallposts by users in social network
  */

class WallPost
{
	public:
		WallPost(); //default constructor
		WallPost(String p, String u); //constructor
		~WallPost(); //destructor
		String getPost() const;
		void setPost( String p );
		String getTime() const;
		void updateTime();
		String getUsername() const;
		void setUsername(String n);		
		
	private:
		String post; //user's post
		String time; //time post is created/modified
		String username; //author's username
};

#endif