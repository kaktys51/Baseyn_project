#pragma once

class LesonsHour
{
public:
	int group_id;
	int trainer_id;
};

class LesonsDay
{
private:
	LesonsHour one;
	LesonsHour two;
	LesonsHour three;
	LesonsHour four;
	LesonsHour five;
	LesonsHour six;
};

class Road
{
protected:
	string name; 
	LesonsDay monday;
public:
	Road(string _name) : name(_name) {}

	string getName() { return name; }

	string setName(string new_name) { name = new_name; }
};