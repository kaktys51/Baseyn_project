#pragma once


class Group //не хранит в себе всех участников, используется для названия и db_id группы
{
protected:
	int		db_id;		//inmportant
	string  name;
	bool    lesson1 = false; 
	bool    lesson2 = false;

public:
	Group(int _db_id, string _name) : db_id(_db_id), name(_name) {}

	int		getDbID() { return db_id; }
	string  getName() { return name; }

	int		setDbId(int nid) { db_id = nid; }
	string  setName(string new_Name) { name = new_Name; }

};