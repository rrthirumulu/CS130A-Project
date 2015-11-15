#include <iostream>
#include <chrono> // used for date
#include <ctime>
#include "wallpost.h"

WallPost::WallPost(const WallPost &wp )
{
	post = wp.post;
	username = wp.username;
	time = wp.time;
}

WallPost::WallPost(std::string p) { post = p; username="blank"; updateTime(); }

WallPost::WallPost(std::string p, std::string u)
{
	post = p;
	username = u;
	updateTime();
}

WallPost::WallPost(std::string p, std::string u, std::string t)
{
  post = p;
  username = u;
  time = t;
}

WallPost::~WallPost()
{
	post.clear();
	username.clear();
	time.clear();
}
std::string WallPost::getPost() { return post; }

void WallPost::setPost(std::string p) { post = p; }

std::string WallPost::getTime() { return time; }

void WallPost::updateTime()
{
  std::chrono::time_point<std::chrono::system_clock> time_point;
  time_point = std::chrono::system_clock::now();
  std::time_t ttp = std::chrono::system_clock::to_time_t(time_point);
  time = std::ctime(&ttp);
  //std::string t = std::chrono::system_clock::now();
}
void WallPost::setUsername(std::string n) { username = n; }

std::string WallPost::getUsername() { return username; }

std::string WallPost::getAllData()
{
	return post + "\n" + username + "\n" + time;
}
