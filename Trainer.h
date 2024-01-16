#pragma once


class Trainer
{
protected:
	int	    db_id;      //inmportant
	string  name;
	string	phone_number;
	int     pay_hour;

public:
	Trainer(int _db_id, string _name, string _phone, int _pay) : db_id(_db_id), name(_name), phone_number(_phone), pay_hour(_pay) {}

	int		getDbID() { return db_id; }
	string  getName() { return name; }
	string	getPhone() { return phone_number; }
	int     getPay() { return pay_hour; }

	int		setDbID(int nid) { db_id = nid; }
	string  setName(string new_Name) { name = new_Name; }
	string	setPhone(string new_phone) { phone_number = new_phone; }
	int     setPay(int new_pay) { pay_hour = new_pay; }
};