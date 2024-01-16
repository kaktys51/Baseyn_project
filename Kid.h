#pragma once


class Kid
{
protected:
	int	    db_id;      //inmportant
	string  name;
	string	parent_name;
	string	phone_number;
	int     group_db_id; //временно добавить, в будещем возможно удалить
	//дополнительные поля c данными

public:
	Kid(int _db_id, string _name, string _parent_name, string _phone_number, int _group_db_id) : db_id(_db_id), name(_name), parent_name(_parent_name), phone_number(_phone_number), group_db_id(_group_db_id) {}

	int		getDbID() { return db_id; }
	string  getName() { return name; }
	string	getParent() { return parent_name; }
	string	getPhone() { return phone_number; }
	int		getGroupID() { return group_db_id; }

	int		setDbID(int nid) { db_id = nid; }
	string  setName(string new_Name) { name = new_Name; }
	string	setParent(string new_parent) { parent_name = new_parent; }
	string	setPhone(string new_phone) { phone_number = new_phone; }
	int		setGroupID(int new_groupID) { group_db_id = new_groupID; }
};