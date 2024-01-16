#pragma once

class Manager
{
protected:
	sqlite3* db;
public:
	Manager() {
		int result = sqlite3_open("baseyn.db", &db);
		if (result != SQLITE_OK)
		{
			cerr << "Error opening SQLite database: " << sqlite3_errmsg(db) << endl;
			throw runtime_error("Failed to open SQLite database");
		}
	}

	~Manager()
	{
		if (db)
		{
			sqlite3_close(db);
		}
	}

	void mainMenu()
	{
		bool quit = false;
		do
		{
			int choise = 0;
			char ch = 0;
			int total = 4; //������������ ���������� ������� � ����

			wcout << L"+++ �������� ������ ������� +++\n" << endl;
			wcout << L"*** ������� ���� ***\n" << endl;

			wcout << L"1. ������ �������" << endl;
			wcout << L"2. ������ ����" << endl;
			wcout << L"3. ������ ����" << endl;
			wcout << L"4. ������ ������" << endl;
			wcout << endl;
			wcout << L"0. ��������� ������" << endl;

			wcout << endl;
			wcout << L"��� ������ �������� ������ �� �������� �� �������� � ������� �������." << endl;

			ch = _getch();
			choise = ch - '0';

			while (choise > total || choise < 0)
			{
				wcout << L"������ ���� �� ����� ������� �� ����!\n ��������� �� ���!" << endl;
				ch = _getch();
				choise = ch - '0';
			}

			switch (choise)
			{
			case 0://�����
				return;
			case 1: // �������
				system("cls");
				trainer_actions();
				break;
			case 2: //������ 
				system("cls");
				group_actions();
				break;
			case 3: //������� 
				system("cls");
				kids_actions();
				break;
			case 4: //������
				system("cls");
				graf_actions();
				break;
			default:
				break;
			}
		} while (quit == false);
	}

	void kids_actions()
	{
		bool quit = false;
		do
		{
			vector<shared_ptr<Kid>> all_kids;
			all_kids = groups_getAllKids(); // �������� ���� ����� �� ���� ������
			wcout << endl;
			wcout << setw(45) << right << L"������ ��� ����!" << endl;
			wcout << endl;
			wcout << setw(14) << right << L"��'�" << setw(35) << L"��'� ������ � ������" << setw(17) << L"����� ��������" << L"" << endl;
			for (size_t i = 0; i < all_kids.size(); ++i)
			{
				if (i < 9)
				{
					cout << i + 1 << ".  ";
				}
				else cout << i + 1 << ". ";
				wcout << setw(22) << left << wconvert(all_kids[i]->getName()) << right << "| ";
				wcout << setw(22) << left << wconvert(all_kids[i]->getParent()) << right << "| ";
				wcout << setw(14) << left << wconvert(all_kids[i]->getPhone()) << right << "| " << endl;
			}

			//���� ����
			wcout << endl;
			wcout << L"1. ���������� ���������� ��� ����." << endl;
			wcout << L"2. �������� ������ ����." << endl;
			wcout << L"3. �������� ����." << endl;
			wcout << endl;
			wcout << L"0. ����������� �� ����." << endl;

			int choise = 0;
			char ch = 0;

			ch = _getch();
			choise = ch - '0';

			int temp = 0;// ��������������� ���������� ��� �������
			while (choise > 3 || choise < 0)
			{
				wcout << L"������ ���� �� ����� ������� �� ����!\n ��������� �� ���!" << endl;
				ch = _getch();
				choise = ch - '0';
			}

			switch (choise)
			{
			case 0://�����
				system("cls");
				return;
				break;
			case 1: // ������������� ���� 
				wcout << endl;
				wcout << L"������� ����� ���� � ������ ���� ��������� ����� �� ������ ���������� �� �������� Enter" << endl;

				cin >> choise;

				while (choise > all_kids.size() || choise < 1)
				{
					wcout << L"������� ����� ����, ��������� �� ���!" << endl;
					cin >> choise;
				}
				wcout << endl;
				wcout << L"�� ������� �� ������ ���������� ����: ";
				for (size_t i = 0; i < all_kids.size(); ++i)
				{
					cout << all_kids[choise - 1]->getName() << " ?" << endl;
					temp = all_kids[choise - 1]->getDbID();
					break;
				}
				wcout << endl;
				if (exit() == true)
				{
					kids_edit(temp);
					this_thread::sleep_for(std::chrono::seconds(1));
					break;
				}
				break;
			case 2: // ������� ������
				wcout << endl;
				wcout << L"�� ������� �� ������ �������� ������ ����? " << endl;
				wcout << endl;
				if (exit() == true)
				{
					kids_create();
					this_thread::sleep_for(std::chrono::seconds(1));
					break;
				}
				break;
			case 3: // ������� 
				wcout << endl;
				wcout << L"������� ����� ���� � ������ ���� ����� �� ������� �������� �� �������� Enter" << endl;

				cin >> choise;

				while (choise > all_kids.size() || choise < 1)
				{
					wcout << L"������� ����� ����, ��������� �� ���!" << endl;
					cin >> choise;
				}
				wcout << endl;
				wcout << L"�� ������� �� ������ �������� ����: ";
				wcout << endl;
				for (size_t i = 0; i < all_kids.size(); ++i)
				{
					cout << all_kids[choise - 1]->getName() << " ?" << endl;
					temp = all_kids[choise - 1]->getDbID();
					break;
				}
				if (exit() == true)
				{
					kids_delete(temp);
					this_thread::sleep_for(std::chrono::seconds(1));
					break;
				}
				break;
			default:
				break;
			}
		} while (quit == false);
	}

	void kids_create()
	{
		setlocale(LC_ALL, "");
		wstring utf16Name;
		wstring utf16Parent;
		wstring utf16Phone;

		if (wcin.peek() == '\n') 
		{
			wcin.ignore();
		}
		wcout << endl;
		wcout << L"������ ��'� ������ ����" << endl;
		wcout << endl;
		getline(wcin, utf16Name);
		wcout << endl;
		wcout << L"������ ��'� ������ � ������ ������ ���� " << endl;
		wcout << endl;
		getline(wcin, utf16Parent);
		wcout << endl;
		wcout << L"������ ����� �������� ������ ����" << endl;
		wcout << endl;
		getline(wcin, utf16Phone);

		// ����������� � UTF-8
		wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		string utf8Name = converter.to_bytes(utf16Name);
		string utf8Parent = converter.to_bytes(utf16Parent);
		string utf8Phone = converter.to_bytes(utf16Phone);

		string query = "INSERT INTO Kids (name, parent_name, phone_number) VALUES ('" + utf8Name + "', '" + utf8Parent + "', " + utf8Phone + ")";
		sqlite3_stmt* statement;

		// �������������� ������
		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK) {
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		// ��������� ���� ��������������� �������
		result = sqlite3_step(statement);

		//��������� ���������
		setlocale(LC_ALL, "en_US.UTF-8");

		if (result != SQLITE_DONE)
		{
			cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
		}
		else
		{
			wcout << endl;
			wcout << L"����� ����� ������ ���������" << endl;
			wcout << endl;
		}

		sqlite3_finalize(statement);
	}

	void kids_edit(int db_id)
	{
		//���� ����������
		wcout << endl;
		wcout << L"������� �� ���� �� ������ ����������:" << endl;
		wcout << endl;

		wcout << L"1. ��'�" << endl;
		wcout << L"2. ��'� ������ � ������" << endl;
		wcout << L"3. ����� �������� ����" << endl;

		int choise = 0;
		char ch = 0;

		ch = _getch();
		choise = ch - '0';

		while (choise > 3 || choise < 1)
		{
			wcout << L"������ ���� �� ����� ������� �� ����!\n ��������� �� ���!" << endl;
			ch = _getch();
			choise = ch - '0';
		}

		//���������� ���������� ��� �������
		string setParametr;
		wstring outcome;

		wstring utf16Data;
		string utf8Text;
		wstring_convert<std::codecvt_utf8<wchar_t>> converter;

		string query;
		sqlite3_stmt* statement;

		wcin.ignore();
		switch (choise)
		{
		case 1://���
			wcout << L"��'�" << endl;
			setParametr = "name";

			setlocale(LC_ALL, "");

			getline(wcin, utf16Data);
			utf8Text = converter.to_bytes(utf16Data);

			query = "UPDATE Kids SET " + setParametr + " = '" + utf8Text + "' WHERE kid_id = ?";

			outcome = L"��'� ���� ������ ������!";
			break;
		case 2://��� ������ �� ���������
			wcout << L"��'� ������ � ������" << endl;
			setParametr = "parent_name";

			setlocale(LC_ALL, "");

			getline(wcin, utf16Data);
			utf8Text = converter.to_bytes(utf16Data);

			query = "UPDATE Kids SET " + setParametr + " = '" + utf8Text + "' WHERE kid_id = ?";

			outcome = L"��'� ������ � ������ ���� ������ ������!";
			break;
		case 3://�������
			wcout << L"����� �������� ����" << endl;
			setParametr = "phone_number";

			setlocale(LC_ALL, "");

			getline(wcin, utf16Data);
			utf8Text = converter.to_bytes(utf16Data);

			query = "UPDATE Kids SET " + setParametr + " = '" + utf8Text + "' WHERE kid_id = ?";

			outcome = L"����� �������� ���� ������ ������!";
			break;
		default:
			break;
		}

		// �������������� ������
		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK) {
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		// ����������� ���������
		sqlite3_bind_int(statement, 1, db_id);

		// ��������� ���� ��������������� �������
		result = sqlite3_step(statement);

		//��������� ���������
		setlocale(LC_ALL, "en_US.UTF-8");

		if (result != SQLITE_DONE)
		{
			cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
		}
		else
		{
			wcout << endl;
			wcout << outcome << endl;
			wcout << endl;
		}

		sqlite3_finalize(statement);
	}

	void kids_delete(int db_id)
	{
		//�������� ����� ��������

		string query = "DELETE FROM Kids WHERE kid_id = ?;";
		sqlite3_stmt* statement;

		// �������������� ������
		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK) {
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		// ����������� ���������
		sqlite3_bind_int(statement, 1, db_id);

		// ��������� ���� ��������������� �������
		result = sqlite3_step(statement);

		if (result != SQLITE_DONE)
		{
			cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
		}
		else
		{
			wcout << endl;
			wcout << L"���������� ��� ���� ������ ��������!" << endl;
			wcout << endl;
		}

		sqlite3_finalize(statement);
	}

	void graf_actions() //���� ������ ��������
	{
		bool quit = false;
		int roadNum = 0;
		do
		{
			vector<shared_ptr<Group>> groups = groups_getAll();
			vector<shared_ptr<Trainer>> trainers = trainer_getAll();

			wcout << endl;
			wcout << L"*** ������� ������ �� ������� ***" << endl;
			wcout << endl;


			wcout << L"������ ������ ������ ��� ������ �����������" << endl;
			wcout << endl;

			wcout << L"1. ����� ������." << endl;
			wcout << L"2. ����� ������." << endl;
			wcout << L"3. ����� ������." << endl;

			//���� ������ �������
			int choise = 0;
			char ch = 0;

			ch = _getch();
			choise = ch - '0';

			while (choise > 3 || choise < 1)
			{
				wcout << L"������ ���� �� ����� ������� �� ����!\n ��������� �� ���!" << endl;
				ch = _getch();
				choise = ch - '0';
			}

			roadNum = choise;

			graf_printFullRoad(roadNum);

			for (size_t i = 0; i < groups.size(); ++i)
			{
				groups_limiter(groups[i]->getDbID());
			}

			for (size_t i = 0; i < trainers.size(); ++i)
			{
				trainer_limiter(trainers[i]->getDbID());
				trainer_anti_dup(trainers[i]->getDbID());
			}



			wcout << endl;
			wcout << L"1. ���������� ������� ������" << endl;
			wcout << L"2. ����������� ���� ������" << endl;
			wcout << endl;
			wcout << L"0. ����������� �� ����" << endl;

			ch = _getch();
			choise = ch - '0';

			while (choise > 2 || choise < 0)
			{
				wcout << L"������ ���� �� ����� ������� �� ����!\n ��������� �� ���!" << endl;
				ch = _getch();
				choise = ch - '0';
			}

			switch (choise)
			{
			case 0:
				wcout << endl;
				wcout << L"����������� �� ����?" << endl;
				wcout << endl;
				if (exit() == true)
				{
					system("cls");
					return;
				}
				break;
			case 1:
				graf_inside(roadNum);
				break;
			case 2:
				system("cls");
				break;
			default:
				break;
			}

		} while (quit == false);
	}

	void graf_inside(int road)//������� �������������� ������ �������
	{
		int dayOfWeek = 0;
		int choise = 0;
		bool quit = false;
		do
		{
			wcout << endl;
			wcout << L"*** ĳ� � �������� ***" << endl;
			wcout << endl;

			wcout << L"1. ������ ���� �������." << endl;
			wcout << L"2. �������� �������." << endl;
			wcout << L"3. ������� �����." << endl;
			wcout << L"4. ������� �������." << endl;
			wcout << endl;

			wcout << L"0. �����." << endl;

			char ch = 0;

			ch = _getch();
			choise = ch - '0';

			while (choise > 4 || choise < 0)
			{
				wcout << L"������ ���� �� ����� ������� �� ����!\n ��������� �� ���!" << endl;
				ch = _getch();
				choise = ch - '0';
			}

			switch (choise)
			{
			case 0:
				return;
				break;
			case 1:// �������� ����� ������ � ������������ �����
				dayOfWeek = graf_choiseDay();
				wcout << L"������ ���� �������?" << endl;
				if (exit() == true)
				{
					graf_addLesson(dayOfWeek, road);
					this_thread::sleep_for(std::chrono::seconds(1));
					break;
				}
				break;
			case 2:// ������� �������
				dayOfWeek = graf_choiseDay();
				wcout << L"�� ����� ������ �������� �������?" << endl;
				if (exit() == true)
				{
					graf_deleteLesson(dayOfWeek, road);
					this_thread::sleep_for(std::chrono::seconds(1));
					break;
				}
				break;
			case 3:// ������ � ����������� ������� ������
				dayOfWeek = graf_choiseDay();
				wcout << L"�� ����� ������ ������� �����?" << endl;
				if (exit() == true)
				{
					graf_update(1, dayOfWeek, road);
					this_thread::sleep_for(std::chrono::seconds(1));
					break;
				}
				break;
			case 4:// ������ � ����������� ������� �������
				dayOfWeek = graf_choiseDay();
				wcout << L"�� ����� ������ ������� �������?" << endl;
				if (exit() == true)
				{
					graf_update(2, dayOfWeek, road);
					this_thread::sleep_for(std::chrono::seconds(1));
					break;
				}
				break;
			default:
				break;
			}
		} while (quit == false);
	}

	int graf_choiseDay()
	{
		wcout << endl;
		wcout << L"������� ���� �����:" << endl;
		wcout << endl;

		wcout << L"1. ��������" << endl;
		wcout << L"2. ³������" << endl;
		wcout << L"3. ������" << endl;
		wcout << L"4. �������" << endl;
		wcout << L"5. �'������" << endl;
		wcout << endl;

		int choise = 0;
		char ch = 0;

		ch = _getch();
		choise = ch - '0';

		while (choise > 5 || choise < 1)
		{
			wcout << L"������ ���� �� ����� ������� �� ����!\n ��������� �� ���!" << endl;
			ch = _getch();
			choise = ch - '0';
		}
		return choise;
	}

	void graf_update(int gt, int dayOfWeek, int road)//gt - �������� �������� �������� ������ ��� ������ ����� �������� ������ 
	{
		//���������� ���������� ��� ������ �������
		int choise = 0;
		string road_name = "";
		string dayGroup = "";
		string dayTrainer = "";
		string lessonsHour = "";
		int group_id = 0;
		int trainer_id = 0;
		vector<shared_ptr<Group>> all_Groups = groups_getAll();
		vector<shared_ptr<Trainer>> all_trainers = trainer_getAll();

		//���� ������ ����� ������� 
		wcout << endl;
		wcout << L"� ����� ����� ��������� ������� ��������� ����� �� ������ ������?" << endl;
		wcout << endl;

		wcout << L"1. 9:00 - 11:00 " << endl;
		wcout << L"2. 11:00 - 13:00 " << endl;
		wcout << L"3. 13:00 - 15:00 " << endl;
		wcout << L"4. 15:00 - 17:00 " << endl;
		wcout << L"5. 17:00 - 19:00 " << endl;
		wcout << L"6. 19:00 - 21:00 " << endl;

		char ch = 0;

		ch = _getch();
		choise = ch - '0';

		while (choise > 6 || choise < 1)
		{
			wcout << endl;
			wcout << L"������ ���� �� ����� ������� �� ����!\n ��������� �� ���!" << endl;
			ch = _getch();
			choise = ch - '0';
		}

		switch (choise)
		{
		case 1:
			lessonsHour = "'9-11'";
			break;
		case 2:
			lessonsHour = "'11-13'";
			break;
		case 3:
			lessonsHour = "'13-15'";
			break;
		case 4:
			lessonsHour = "'15-17'";
			break;
		case 5:
			lessonsHour = "'17-19'";
			break;
		case 6:
			lessonsHour = "'19-21'";
			break;
		default:
			break;
		}

		if (gt == 1)//������� � ���������� ������
		{
			wcout << endl;
			wcout << endl;
			wcout << L"������ ��������� ����." << endl;
			wcout << endl;
			for (size_t i = 0; i < all_Groups.size(); ++i)
			{
				if (i < 9)
				{
					cout << i + 1 << ".  ";
				}
				else cout << i + 1 << ". ";
				wcout << wconvert(all_Groups[i]->getName()) << endl;
			}

			wcout << endl;
			wcout << L"������ ����� ����� ��� ������� �� �������� Enter" << endl;
			wcout << endl;

			choise = 0;
			cin >> choise;

			while (choise > all_Groups.size() || choise < 1)
			{
				wcout << endl;
				wcout << L"����� �� ����� ������� �� ����!\n ��������� �� ���!" << endl;
				cin >> choise;
			}

			for (size_t i = 0; i < all_Groups.size(); ++i)
			{
				group_id = all_Groups[choise - 1]->getDbID();
			}
		}
		else if (gt == 2)//������� � ���������� �������
		{
			//���� ������ ������� 
			wcout << endl;
			wcout << endl;
			wcout << L"������ ��������� �������." << endl;
			wcout << endl;
			for (size_t i = 0; i < all_trainers.size(); ++i)
			{
				if (i < 9)
				{
					cout << i + 1 << ".  ";
				}
				else cout << i + 1 << ". ";
				wcout << wconvert(all_trainers[i]->getName()) << endl;
			}

			wcout << endl;
			wcout << L"������ ����� ������� ��� ������� �� �������� Enter" << endl;
			wcout << endl;

			choise = 0;
			cin >> choise;

			while (choise > all_trainers.size() || choise < 1)
			{
				wcout << endl;
				wcout << L"������� �� ����� ������� �� ����!\n ��������� �� ���!" << endl;
				cin >> choise;
			}

			for (size_t i = 0; i < all_trainers.size(); ++i)
			{
				trainer_id = all_trainers[choise - 1]->getDbID();
			}
		}
		// ��������� ����� ������� 
		switch (road)//�� �������� ����������� ������ �������
		{
		case 1:
			road_name = "Road1";
			break;
		case 2:
			road_name = "Road2";
			break;
		case 3:
			road_name = "Road3";
			break;
		default:
			break;
		}

		switch (dayOfWeek)//�� �������� ����������� ������ �������� ����������
		{
		case 1://monday
			dayGroup = "monday_group";
			dayTrainer = "monday_trainer";
			break;
		case 2://tuesday
			dayGroup = "tuesday_group";
			dayTrainer = "tuesday_trainer";
			break;
		case 3://wednesday
			dayGroup = "wednesday_group";
			dayTrainer = "wednesday_trainer";
			break;
		case 4://thursday
			dayGroup = "thursday_group";
			dayTrainer = "thursday_trainer";
			break;
		case 5://friday
			dayGroup = "friday_group";
			dayTrainer = "friday_trainer";
			break;
		default:
			break;
		}

		string query;
		if (gt == 1)//������� � ���������� ������
		{
			query = "UPDATE " + road_name + " SET " + dayGroup + " = ? WHERE lesson_hours = " + lessonsHour + "";
		}
		else if (gt == 2)//������� � ���������� ������� 
		{
			query = "UPDATE " + road_name + " SET " + dayTrainer + " = ? WHERE lesson_hours = " + lessonsHour + "";
		}
		sqlite3_stmt* statement;

		// �������������� ������
		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK) {
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		if (gt == 1) { sqlite3_bind_int(statement, 1, group_id); }
		else if (gt == 2) {
			sqlite3_bind_int(statement, 1, trainer_id);
		}

		// ��������� ���� ��������������� �������
		result = sqlite3_step(statement);

		//��������� ���������
		setlocale(LC_ALL, "en_US.UTF-8");

		if (result != SQLITE_DONE)
		{
			cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
		}
		else
		{
			wcout << endl;
			if (gt == 1) { wcout << L"����� ������ �������!" << endl; }
			else if (gt == 2) { wcout << L"������� ������ �������!" << endl; }
			wcout << endl;
		}

		sqlite3_finalize(statement);
	}

	void graf_deleteLesson(int dayOfWeek, int road)
	{
		//���������� ���������� ��� ������ �������
		int choise = 0;
		string road_name = "";
		string dayGroup = "";
		string dayTrainer = "";
		string lessonsHour = "";

		//���� ������ ����� ������� 

		wcout << endl;
		wcout << L"� ����� ����� ��������� ������� ��� �� ������ ��������?" << endl;
		wcout << endl;

		wcout << L"1. 9:00 - 11:00 " << endl;
		wcout << L"2. 11:00 - 13:00 " << endl;
		wcout << L"3. 13:00 - 15:00 " << endl;
		wcout << L"4. 15:00 - 17:00 " << endl;
		wcout << L"5. 17:00 - 19:00 " << endl;
		wcout << L"6. 19:00 - 21:00 " << endl;

		char ch = 0;

		ch = _getch();
		choise = ch - '0';

		while (choise > 6 || choise < 1)
		{
			wcout << endl;
			wcout << L"������ ���� �� ����� ������� �� ����!\n ��������� �� ���!" << endl;
			ch = _getch();
			choise = ch - '0';
		}

		switch (choise)
		{
		case 1:
			lessonsHour = "'9-11'";
			break;
		case 2:
			lessonsHour = "'11-13'";
			break;
		case 3:
			lessonsHour = "'13-15'";
			break;
		case 4:
			lessonsHour = "'15-17'";
			break;
		case 5:
			lessonsHour = "'17-19'";
			break;
		case 6:
			lessonsHour = "'19-21'";
			break;
		default:
			break;
		}

		// ��������� ����� ������� 

		switch (road)//�� �������� ����������� ������ �������
		{
		case 1:
			road_name = "Road1";
			break;
		case 2:
			road_name = "Road2";
			break;
		case 3:
			road_name = "Road3";
			break;
		default:
			break;
		}

		switch (dayOfWeek)//�� �������� ����������� ������ �������� ����������
		{
		case 1://monday
			dayGroup = "monday_group";
			dayTrainer = "monday_trainer";
			break;
		case 2://tuesday
			dayGroup = "tuesday_group";
			dayTrainer = "tuesday_trainer";
			break;
		case 3://wednesday
			dayGroup = "wednesday_group";
			dayTrainer = "wednesday_trainer";
			break;
		case 4://thursday
			dayGroup = "thursday_group";
			dayTrainer = "thursday_trainer";
			break;
		case 5://friday
			dayGroup = "friday_group";
			dayTrainer = "friday_trainer";
			break;
		default:
			break;
		}

		string query = "UPDATE " + road_name + " SET " + dayGroup + " = NULL, " + dayTrainer + " = NULL WHERE lesson_hours = " + lessonsHour + "";
		sqlite3_stmt* statement;

		// �������������� ������
		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK) {
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		// ��������� ���� ��������������� �������
		result = sqlite3_step(statement);

		//��������� ���������
		setlocale(LC_ALL, "en_US.UTF-8");

		if (result != SQLITE_DONE)
		{
			cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
		}
		else
		{
			wcout << endl;
			wcout << L"������� ������ �������� � �������" << endl;
			wcout << endl;
		}

		sqlite3_finalize(statement);
	}

	void graf_addLesson(int dayOfWeek, int road)
	{
		//���������� ���������� ��� ������ �������
		int choise = 0;
		int group_id = 0;
		int trainer_id = 0;
		string road_name = "";
		string dayGroup = "";
		string dayTrainer = "";
		string lessonsHour = "";
		vector<shared_ptr<Group>> all_Groups = groups_getAll();
		vector<shared_ptr<Trainer>> all_trainers = trainer_getAll();

		//���� ������ ����� ������� 

		wcout << endl;
		wcout << L"������ ������ ��� �������" << endl;
		wcout << endl;

		wcout << L"1. 9:00 - 11:00 " << endl;
		wcout << L"2. 11:00 - 13:00 " << endl;
		wcout << L"3. 13:00 - 15:00 " << endl;
		wcout << L"4. 15:00 - 17:00 " << endl;
		wcout << L"5. 17:00 - 19:00 " << endl;
		wcout << L"6. 19:00 - 21:00 " << endl;

		char ch = 0;

		ch = _getch();
		choise = ch - '0';

		while (choise > 6 || choise < 1)
		{
			wcout << endl;
			wcout << L"������ ���� �� ����� ������� �� ����!\n ��������� �� ���!" << endl;
			ch = _getch();
			choise = ch - '0';
		}

		switch (choise)
		{
		case 1:
			lessonsHour = "'9-11'";
			break;
		case 2:
			lessonsHour = "'11-13'";
			break;
		case 3:
			lessonsHour = "'13-15'";
			break;
		case 4:
			lessonsHour = "'15-17'";
			break;
		case 5:
			lessonsHour = "'17-19'";
			break;
		case 6:
			lessonsHour = "'19-21'";
			break;
		default:
			break;
		}

		// ���� ������ ������
		wcout << endl;
		wcout << endl;
		wcout << L"������ ��������� ����." << endl;
		wcout << endl;
		for (size_t i = 0; i < all_Groups.size(); ++i)
		{
			if (i < 9)
			{
				cout << i + 1 << ".  ";
			}
			else cout << i + 1 << ". ";
			wcout << wconvert(all_Groups[i]->getName()) << endl;
		}

		wcout << endl;
		wcout << L"������ ����� ����� ��� ������� �� �������� Enter" << endl;
		wcout << endl;

		choise = 0;
		cin >> choise;

		while (choise > all_Groups.size() || choise < 1)
		{
			wcout << endl;
			wcout << L"����� �� ����� ������� �� ����!\n ��������� �� ���!" << endl;
			cin >> choise;
		}

		for (size_t i = 0; i < all_Groups.size(); ++i)
		{
			group_id = all_Groups[choise - 1]->getDbID();
		}

		//���� ������ ������� 
		wcout << endl;
		wcout << endl;
		wcout << L"������ ��������� �������." << endl;
		wcout << endl;
		for (size_t i = 0; i < all_trainers.size(); ++i)
		{
			if (i < 9)
			{
				cout << i + 1 << ".  ";
			}
			else cout << i + 1 << ". ";
			wcout << wconvert(all_trainers[i]->getName()) << endl;
		}

		wcout << endl;
		wcout << L"������ ����� ������� ��� ������� �� �������� Enter" << endl;
		wcout << endl;

		choise = 0;
		cin >> choise;

		while (choise > all_trainers.size() || choise < 1)
		{
			wcout << endl;
			wcout << L"������� �� ����� ������� �� ����!\n ��������� �� ���!" << endl;
			cin >> choise;
		}

		for (size_t i = 0; i < all_trainers.size(); ++i)
		{
			trainer_id = all_trainers[choise - 1]->getDbID();
		}

		// ��������� ����� ������� 

		switch (road)//�� �������� ����������� ������ �������
		{
		case 1:
			road_name = "Road1";
			break;
		case 2:
			road_name = "Road2";
			break;
		case 3:
			road_name = "Road3";
			break;
		default:
			break;
		}

		switch (dayOfWeek)//�� �������� ����������� ������ �������� ����������
		{
		case 1://monday
			dayGroup = "monday_group";
			dayTrainer = "monday_trainer";
			break;
		case 2://tuesday
			dayGroup = "tuesday_group";
			dayTrainer = "tuesday_trainer";
			break;
		case 3://wednesday
			dayGroup = "wednesday_group";
			dayTrainer = "wednesday_trainer";
			break;
		case 4://thursday
			dayGroup = "thursday_group";
			dayTrainer = "thursday_trainer";
			break;
		case 5://friday
			dayGroup = "friday_group";
			dayTrainer = "friday_trainer";
			break;
		default:
			break;
		}

		string query = "UPDATE " + road_name + " SET " + dayGroup + " = ?, " + dayTrainer + " = ? WHERE lesson_hours = " + lessonsHour + "";
		sqlite3_stmt* statement;

		// �������������� ������
		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK) {
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		// ����������� ���������
		sqlite3_bind_int(statement, 1, group_id);
		sqlite3_bind_int(statement, 2, trainer_id);

		// ��������� ���� ��������������� �������
		result = sqlite3_step(statement);

		//��������� ���������
		setlocale(LC_ALL, "en_US.UTF-8");

		if (result != SQLITE_DONE)
		{
			cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
		}
		else
		{
			wcout << endl;
			wcout << L"������� ������ ������ � ������" << endl;
			wcout << endl;
		}

		sqlite3_finalize(statement);
	}

	void graf_printFullRoad(int road) // ���������� ������� �� ���� ������ graf_RgetByDAY � ����� ���� ������ ����
	{
		wstring sRoad = L"";
		switch (road)
		{
		case 1:
			sRoad = L"����� ������";
			break;
		case 2:
			sRoad = L"����� ������";
			break;
		case 3:
			sRoad = L"����� ������";
			break;
		default:
			break;
		}

		wcout << setw(64) << setfill(L'_') << L"" << endl;
		wcout << setw(25) << setfill(L' ') << right << "*" << sRoad << "*" << endl;
		wcout << endl;

		for (int i = 0; i < 5; ++i)
		{
			graf_RgetByDAY(road, i + 1);
		}

	}

	void graf_RgetByDAY(int road, int dayOFweek)
	{
		vector<shared_ptr<Group>> groups = groups_getAll();
		vector<shared_ptr<Trainer>> trainers = trainer_getAll();
		wstring group_name = L" ";
		wstring trainer_name = L" ";

		string road_name = "";
		string dayGroup = "";
		string dayTrainer = "";
		wstring output = L" ";

		switch (road)
		{
		case 1:
			road_name = "Road1";
			break;
		case 2:
			road_name = "Road2";
			break;
		case 3:
			road_name = "Road3";
			break;
		default:
			break;
		}

		switch (dayOFweek)
		{
		case 1://monday
			dayGroup = "monday_group";
			dayTrainer = "monday_trainer";
			output = L"��������";
			break;
		case 2://tuesday
			dayGroup = "tuesday_group";
			dayTrainer = "tuesday_trainer";
			output = L"³������";
			break;
		case 3://wednesday
			dayGroup = "wednesday_group";
			dayTrainer = "wednesday_trainer";
			output = L"������";
			break;
		case 4://thursday
			dayGroup = "thursday_group";
			dayTrainer = "thursday_trainer";
			output = L"�������";
			break;
		case 5://friday
			dayGroup = "friday_group";
			dayTrainer = "friday_trainer";
			output = L"�'������";
			break;
		default:
			break;
		}

		//������ �� ������
		string query = "SELECT lesson_hours," + dayGroup + " , " + dayTrainer + " FROM " + road_name + " ";
		sqlite3_stmt* statement;

		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK)
		{
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		wcout << setw(64) << setfill(L'-') << L"" << endl;
		wcout << setw(27) << setfill(L' ') << right << "*" << output << "*" << endl;
		wcout << endl;

		wcout << setw(14) << right << L"������ ������" << setw(15) << L"�����" << setw(25) << L"������" << endl;

		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			//���������� ������ �� ���� ������
			const char* lesson_hours = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));

			//���� ������ �������� ����� �� �� ��
			int group_id = sqlite3_column_int(statement, 1);
			if (group_id != NULL) // ����� �������� ����� �� �� ��
			{
				//����� � ������ �������� ����� ����� ����� �������
				auto it = std::find_if(groups.begin(), groups.end(),
					[group_id](const std::shared_ptr<Group>& group) { return group->getDbID() == group_id; });
				if (it != groups.end())
				{
					// ��� ������ ������ ������� ��� � ����������� ����������
					group_name = wconvert((*it)->getName());
				}
			}
			else if (group_id == NULL) group_name = L"    --"; // � ��������� ������ ������ ��������

			int trainer_id = sqlite3_column_int(statement, 2);
			if (trainer_id != NULL)
			{
				auto it1 = std::find_if(trainers.begin(), trainers.end(),
					[trainer_id](const std::shared_ptr<Trainer>& trainer) { return trainer->getDbID() == trainer_id; });
				if (it1 != trainers.end())
				{
					trainer_name = wconvert((*it1)->getName());
				}
			}
			else if (trainer_id == NULL) trainer_name = L"        --";

			wcout << setw(7) << left << L" " << setw(15) << lesson_hours << setw(21) << group_name << setw(25) << trainer_name << endl;
		}
		wcout << setw(64) << setfill(L'-') << L"" << endl;
		wcout << setfill(L' ') << L"" << endl;
		cout << endl;

		sqlite3_finalize(statement);
	}

	void group_actions()
	{
		bool quit = false;
		do
		{
			wcout << endl;
			wcout << L"������ ��������� ����." << endl;
			wcout << endl;

			vector<shared_ptr<Group>> all_Groups;
			vector<shared_ptr<Kid>> all_kids;
			all_Groups = groups_getAll(); // �������� ��� ������ 
			all_kids = groups_getAllKids(); // �������� ���� ����� �� ���� ������

			for (size_t i = 0; i < all_Groups.size(); ++i) //����� ���� ����� �� �������
			{
				bool havekids = false;
				cout << setfill('-') << setw(63) << "" << endl;
				cout << setfill(' ') << setw(27) << right << i + 1 << ". " << all_Groups[i]->getName() << ": " << endl;
				cout << endl;
				wcout << setw(10) << right << L"��'�" << setw(35) << L"��'� ������ � ������" << setw(17) << L"����� ��������" << L"" << endl;
				for (size_t j = 0; j < all_kids.size(); ++j)
				{
					if (all_kids[j]->getGroupID() == all_Groups[i]->getDbID())
					{
						havekids = true;

						wcout << setw(22) << left << wconvert(all_kids[j]->getName()) << right << "| ";
						wcout << setw(22) << left << wconvert(all_kids[j]->getParent()) << right << "| ";
						wcout << setw(14) << left << wconvert(all_kids[j]->getPhone()) << right << "| " << endl;
					}
				}
				if (havekids == false) wcout << setw(42) << L"����� ������!" << endl;
				wcout << endl;
			}

			for (size_t j = 0; j < all_kids.size(); ++j)// ����� �������� 
			{
				if (all_kids[j]->getGroupID() == NULL)
				{
					cout << setfill('-') << setw(63) << "" << endl;
					wcout << setfill(L' ') << setw(55) << right << L"��� �� �� ����������� � ����� �����:" << endl;
					cout << endl;
					wcout << setw(10) << right << L"��'�" << setw(35) << L"��'� ������ � ������" << setw(17) << L"����� ��������" << L"" << endl;
					break;
				}

			}

			for (size_t j = 0; j < all_kids.size(); ++j)
			{
				if (all_kids[j]->getGroupID() == NULL)
				{
					wcout << setw(22) << left << wconvert(all_kids[j]->getName()) << right << "| ";
					wcout << setw(22) << left << wconvert(all_kids[j]->getParent()) << right << "| ";
					wcout << setw(14) << left << wconvert(all_kids[j]->getPhone()) << right << "| " << endl;
				}
			}

			vector<shared_ptr<Kid>> GroupKids; // ������ ���� ������������ ������

			int group_id = 0;

			wcout << endl;
			wcout << L"*** ĳ� ���� ***" << endl;
			wcout << endl;

			wcout << L"1. ����������� �����." << endl;
			wcout << L"2. ���������� ����� �����." << endl;
			wcout << L"3. �������� �����." << endl;
			wcout << L"4. �������� �����." << endl;
			wcout << endl;
			wcout << L"0. ����������� �� ����." << endl;

			//���� ������ ����
			int choise = 0;
			char ch = 0;

			ch = _getch();
			choise = ch - '0';

			while (choise > 4 || choise < 0)
			{
				wcout << L"������ ���� �� ����� ������� �� ����!\n ��������� �� ���!" << endl;
				ch = _getch();
				choise = ch - '0';
			}

			int temp = 0;// ��������������� ���������� ��� �������
			switch (choise)
			{
			case 0:
				system("cls");
				return;
				break;
			case 1://�������� ������ // �������� ������ �������������� ������� ������
				wcout << endl;
				wcout << L"������� ����� ����� � ������ ���� �� �������� Enter" << endl;

				cin >> choise;

				while (choise > all_Groups.size() || choise < 1)
				{
					wcout << L"������� ����� �����, ��������� �� ���!" << endl;
					cin >> choise;
				}

				for (size_t i = 0; i < all_Groups.size(); ++i)
				{
					group_id = all_Groups[choise - 1]->getDbID();
					break;
				}

				groups_inside(all_Groups, group_id);
				break;
			case 2: //�������������� ��������
				wcout << endl;
				wcout << L"���� ����� �����!" << endl;
				wcout << endl;

				wcout << L"������� ����� ����� � ������ ���� �� �������� Enter" << endl;

				cin >> choise;

				while (choise > all_Groups.size() || choise < 1)
				{
					wcout << L"������� ����� �����, ��������� �� ���!" << endl;
					ch = _getch();
					choise = ch - '0';
				}
				cin.ignore();
				groups_rename(choise);
				this_thread::sleep_for(std::chrono::seconds(1));
				break;
			case 3: // �������� ����� ������
				wcout << endl;
				wcout << L"��������� ���� �����!" << endl;
				wcout << endl;

				groups_create();
				this_thread::sleep_for(std::chrono::seconds(1));
				break;
			case 4: // �������� ������
				wcout << endl;
				wcout << L"������� ����� ����� � ������ ���� ��� �� ������� �������� �� �������� Enter" << endl;

				cin >> choise;

				while (choise > all_Groups.size() || choise < 1)
				{
					wcout << L"������� ����� �����, ��������� �� ���!" << endl;
					ch = _getch();
					choise = ch - '0';
				}
				wcout << L"�� ������� �� ������ �������� �����: ";
				for (size_t i = 0; i < all_Groups.size(); ++i)
				{
					cout << all_Groups[choise - 1]->getName() << " ?" << endl;
					temp = all_Groups[choise - 1]->getDbID();
					break;
				}
				if (exit() == true)
				{
					groups_delete(temp);
					this_thread::sleep_for(std::chrono::seconds(1));
					break;
				}
				else
					break;
			default:
				break;
			}
		} while (quit == false);
	}

	bool groups_full(int gp_id)
	{
		vector<shared_ptr<Kid>> group_kids = groups_getSelected(gp_id);
		if (group_kids.size() >= 10) return true;
		else return false;
	}

	void groups_limiter(int gp_id)
	{
		vector<shared_ptr<Group>> groups = groups_getAll();
		wstring gName;
		for (size_t i = 0; i < groups.size(); ++i)
		{
			if (groups[i]->getDbID() == gp_id) gName = wconvert(groups[i]->getName());
		}
		int dayCount = 0;
		int weekCount = 0;

		const int dayLimit = 1;//������������ ���������� ������� � ����
		const int weekLimit = 2;//������������ ���������� ������� � ������

		for (int d = 0; d < 5; ++d)
		{
			dayCount = 0;
			dayCount += groups_limiterP2(1, d + 1, gp_id);
			dayCount += groups_limiterP2(2, d + 1, gp_id);
			dayCount += groups_limiterP2(3, d + 1, gp_id);
			weekCount += dayCount;
			if (dayCount > dayLimit)
			{
				wcout << endl;
				wcout << endl;
				wcout << L"� ����� '" << gName << L"' ����������� ��� ������ �� ���� !" << endl;
				wcout << L"���� ����� ���������� ��� ������!" << endl;
				wcout << endl;
				wcout << endl;
				this_thread::sleep_for(std::chrono::seconds(2));
				return;
			}
			if (weekCount > weekLimit)
			{
				wcout << endl;
				wcout << endl;
				wcout << L"� ����� '" << gName << L"' ����������� ��� ������ �� ������� !" << endl;
				wcout << L"���� ����� ���������� ��� ������!" << endl;
				wcout << endl;
				wcout << endl;
				this_thread::sleep_for(std::chrono::seconds(2));
				return;
			}
		}
	}

	int groups_limiterP2(int road, int dayOFweek, int group_id)
	{
		wstring group_name = L" ";
		wstring trainer_name = L" ";

		string road_name = "";
		string dayGroup = "";
		string dayTrainer = "";
		wstring output = L" ";
		wstring output_road = L"";

		switch (road)
		{
		case 1:
			road_name = "Road1";
			output_road = L"����� ������";
			break;
		case 2:
			road_name = "Road2";
			output_road = L"����� ������";
			break;
		case 3:
			road_name = "Road3";
			output_road = L"����� ������";
			break;
		default:
			break;
		}

		switch (dayOFweek)
		{
		case 1://monday
			dayGroup = "monday_group";
			dayTrainer = "monday_trainer";
			output = L"��������";
			break;
		case 2://tuesday
			dayGroup = "tuesday_group";
			dayTrainer = "tuesday_trainer";
			output = L"³������";
			break;
		case 3://wednesday
			dayGroup = "wednesday_group";
			dayTrainer = "wednesday_trainer";
			output = L"������";
			break;
		case 4://thursday
			dayGroup = "thursday_group";
			dayTrainer = "thursday_trainer";
			output = L"�������";
			break;
		case 5://friday
			dayGroup = "friday_group";
			dayTrainer = "friday_trainer";
			output = L"�'������";
			break;
		default:
			break;
		}

		//������ �� ������
		string query = "SELECT lesson_hours, " + dayGroup + " , " + dayTrainer + " FROM " + road_name + " WHERE " + dayGroup + " = ?";
		sqlite3_stmt* statement;

		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK)
		{
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return 0;
		}

		sqlite3_bind_int(statement, 1, group_id);

		int count = 0;

		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			++count;

			//���������� ������ �� ���� ������
			const char* lesson_hours = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));

			//���� ������ �������� ����� �� �� ��
			int group_id = sqlite3_column_int(statement, 1);
			int trainer_id = sqlite3_column_int(statement, 2);
		}
		sqlite3_finalize(statement);
		return count;
	}

	int groups_grafFinder(int road, int dayOFweek, int group_id)//����� ������� �� ������ ������
	{

		vector<shared_ptr<Group>> groups = groups_getAll();
		vector<shared_ptr<Trainer>> trainers = trainer_getAll();
		wstring group_name = L" ";
		wstring trainer_name = L" ";

		string road_name = "";
		string dayGroup = "";
		string dayTrainer = "";
		wstring output = L" ";
		wstring output_road = L"";

		switch (road)
		{
		case 1:
			road_name = "Road1";
			output_road = L"����� ������";
			break;
		case 2:
			road_name = "Road2";
			output_road = L"����� ������";
			break;
		case 3:
			road_name = "Road3";
			output_road = L"����� ������";
			break;
		default:
			break;
		}

		switch (dayOFweek)
		{
		case 1://monday
			dayGroup = "monday_group";
			dayTrainer = "monday_trainer";
			output = L"��������";
			break;
		case 2://tuesday
			dayGroup = "tuesday_group";
			dayTrainer = "tuesday_trainer";
			output = L"³������";
			break;
		case 3://wednesday
			dayGroup = "wednesday_group";
			dayTrainer = "wednesday_trainer";
			output = L"������";
			break;
		case 4://thursday
			dayGroup = "thursday_group";
			dayTrainer = "thursday_trainer";
			output = L"�������";
			break;
		case 5://friday
			dayGroup = "friday_group";
			dayTrainer = "friday_trainer";
			output = L"�'������";
			break;
		default:
			break;
		}

		//������ �� ������
		string query = "SELECT lesson_hours, " + dayGroup + " , " + dayTrainer + " FROM " + road_name + " WHERE " + dayGroup + " = ?";
		sqlite3_stmt* statement;

		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK)
		{
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return 0;
		}

		sqlite3_bind_int(statement, 1, group_id);

		int count = 0;

		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			++count;
			if (count == 1)
			{
				wcout << setw(64) << setfill(L'_') << L"" << endl;
				wcout << setw(24) << setfill(L' ') << right << "*" << output_road << "*" << endl;
				wcout << endl;

				wcout << setw(64) << setfill(L'-') << L"" << endl;
				wcout << setw(27) << setfill(L' ') << right << "*" << output << "*" << endl;
				wcout << endl;

				wcout << setw(14) << right << L"������ ������" << setw(15) << L"�����" << setw(25) << L"������" << endl;
			}
			//���������� ������ �� ���� ������
			const char* lesson_hours = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));

			//���� ������ �������� ����� �� �� ��
			int group_id = sqlite3_column_int(statement, 1);
			if (group_id != NULL) // ����� �������� ����� �� �� ��
			{
				//����� � ������ �������� ����� ����� ����� �������
				auto it = std::find_if(groups.begin(), groups.end(),
					[group_id](const std::shared_ptr<Group>& group) { return group->getDbID() == group_id; });
				if (it != groups.end())
				{
					// ��� ������ ������ ������� ��� � ����������� ����������
					group_name = wconvert((*it)->getName());
				}
			}
			else if (group_id == NULL) group_name = L"    --"; // � ��������� ������ ������ ��������

			int trainer_id = sqlite3_column_int(statement, 2);
			if (trainer_id != NULL)
			{
				auto it1 = std::find_if(trainers.begin(), trainers.end(),
					[trainer_id](const std::shared_ptr<Trainer>& trainer) { return trainer->getDbID() == trainer_id; });
				if (it1 != trainers.end())
				{
					trainer_name = wconvert((*it1)->getName());
				}
			}
			else if (trainer_id == NULL) trainer_name = L"        --";

			wcout << setw(7) << left << L" " << setw(15) << lesson_hours << setw(21) << group_name << setw(25) << trainer_name << endl;
		}
		if (count != 0)
		{
			wcout << setw(64) << setfill(L'-') << L"" << endl;
			wcout << setfill(L' ') << L"" << endl;
			cout << endl;
		}

		sqlite3_finalize(statement);
		if (count != 0) { return 1; }
		else { return 0; }
	}

	void groups_inside(vector<shared_ptr<Group>> all_Groups, int gp_id) // �������������� ������ ������
	{
		do
		{
			vector<shared_ptr<Kid>> GroupKids = groups_getSelected(gp_id);
			vector<shared_ptr<Kid>> all_Kids = groups_getAllKids();

			cout << setfill('-') << setw(63) << "" << endl;
			wcout << setw(40) << L"������� �����!" << endl;

			for (size_t i = 0; i < all_Groups.size(); ++i) //����� ���� ����� �� �������
			{
				if (all_Groups[i]->getDbID() == gp_id)
				{
					cout << setfill('-') << setw(63) << "" << endl;
					cout << setfill(' ') << setw(27) << right << i + 1 << ". " << all_Groups[i]->getName() << ": " << endl;
					cout << endl;
					wcout << setw(10) << right << L"��'�" << setw(35) << L"��'� ������ � ������" << setw(17) << L"����� ��������" << L"" << endl;
					break;
				}
			}
			for (size_t j = 0; j < GroupKids.size(); ++j)
			{
				if (j < 9)
				{
					cout << j + 1 << ".  ";
				}
				else cout << j + 1 << ". ";
				wcout << setw(22) << left << wconvert(GroupKids[j]->getName()) << right << "| ";
				wcout << setw(22) << left << wconvert(GroupKids[j]->getParent()) << right << "| ";
				wcout << setw(14) << left << wconvert(GroupKids[j]->getPhone()) << right << "| " << endl;

			}
			wcout << endl;
			wcout << L"*** ĳ� ���� ***" << endl;
			wcout << endl;

			wcout << L"1. �������� ���� � �����." << endl;
			wcout << L"2. �������� ���� � �����." << endl;
			wcout << L"3. ������ ������� � �������" << endl;
			wcout << endl;
			wcout << L"0. ����������� �� ����." << endl;
			int choise = 0;
			char ch = 0;

			ch = _getch();
			choise = ch - '0';

			while (choise > 3 || choise < 0)
			{
				wcout << L"������ ���� �� ����� ������� �� ����!\n ��������� �� ���!" << endl;
				ch = _getch();
				choise = ch - '0';
			}

			int temp = 0; // ��������������� ���������� ��� �������
			int emptyGraf = 0; //��������������� ���������� ��� ������ �������
			bool fullCheck = false;
			switch (choise)
			{
			case 0:
				system("cls");
				return;
				break;
			case 1:// ������� ������� 
				fullCheck = groups_full(gp_id);
				if (fullCheck == true)
				{
					wcout << endl;
					wcout << L"*** ����� �� ����������� ������� ����! ***" << endl;
					wcout << endl;
					this_thread::sleep_for(std::chrono::seconds(1));
					break;
				}
				wcout << endl;
				wcout << L"������� ����� ������ �������� ����:" << endl;
				wcout << endl;

				wcout << L"0. ��� ��� ������" << endl;
				//����� ����� �������� ����� ������ ����� �������

				wcout << endl;
				wcout << L"���� �����" << endl;

				for (size_t i = 0; i < all_Groups.size(); ++i) //����� ���� �����
				{
					cout << i + 1 << ". " << all_Groups[i]->getName() << endl;
				}

				wcout << endl;
				wcout << L"������ ����� ������ ����� ������ ����� ���� �� �������� ENTER " << endl;
				wcout << endl;
				cin >> choise;

				while (choise > (all_Groups.size() + 1) || choise < 0)
				{
					wcout << L"����� �� ����� ������� �� ����!\n ��������� �� ���!" << endl;
					cin >> choise;
				}

				if (choise == 0) //�����\����� ��� �������� ��� �����
				{
					cout << setfill('-') << setw(63) << "" << endl;
					wcout << setfill(L' ') << setw(55) << right << L"��� �� �� ����������� � ����� �����:" << endl;
					cout << endl;
					wcout << setw(10) << right << L"��'�" << setw(35) << L"��'� ������ � ������" << setw(17) << L"����� ��������" << L"" << endl;

					for (size_t j = 0; j < all_Kids.size(); ++j)
					{
						if (all_Kids[j]->getGroupID() == NULL)
						{
							++temp;// ��� �������� ���������� ������� ��� ������
							if (temp < 9)
							{
								cout << temp << ".  ";
							}
							else cout << temp << ". ";
							wcout << setw(22) << left << wconvert(all_Kids[j]->getName()) << right << "| ";
							wcout << setw(22) << left << wconvert(all_Kids[j]->getParent()) << right << "| ";
							wcout << setw(14) << left << wconvert(all_Kids[j]->getPhone()) << right << "| " << endl;
						}
					}
					wcout << endl;
					wcout << L"������� ����� ���� ����� ������� ������ �� ���� ����� �� �������� Enter" << endl;

					cin >> choise;
					int kid_id = 0;
					while (choise > temp || choise < 1)  //����� ������� �� �������� temp  
					{
						wcout << L"������� ����� ����, ��������� �� ���!" << endl;
						cin >> choise;
					}

					temp = 0; //�������� ������� ��� ���������� ����� � ������� ����������
					for (size_t j = 0; j < all_Kids.size(); ++j) // ��������� ���� ��� ������ ���������� �������� � ������ ������������
					{
						if (all_Kids[j]->getGroupID() == NULL)
						{
							++temp;
							if (temp == choise)
							{
								kid_id = all_Kids[j]->getDbID();// �������� �� ��� ���� ������ ������� ��� �������
								break;
							}
						}
					}

					groups_insert(gp_id, kid_id);
					this_thread::sleep_for(std::chrono::seconds(1));
					break;
				}
				else
				{
					int group_id = 0;
					temp = 0;
					for (size_t i = 0; i < all_Groups.size(); ++i) //������� ��� ��������� �� ��� ���� ������
					{
						group_id = all_Groups[choise - 1]->getDbID();
						break;
					}

					cout << endl;
					wcout << setw(10) << right << L"��'�" << setw(35) << L"��'� ������ � ������" << setw(17) << L"����� ��������" << L"" << endl;

					for (size_t j = 0; j < all_Kids.size(); ++j)
					{
						if (all_Kids[j]->getGroupID() == group_id)
						{
							++temp;// ��� �������� ���������� ������� ��� ������
							if (temp < 9)
							{
								cout << temp << ".  ";
							}
							else cout << temp << ". ";
							wcout << setw(22) << left << wconvert(all_Kids[j]->getName()) << right << "| ";
							wcout << setw(22) << left << wconvert(all_Kids[j]->getParent()) << right << "| ";
							wcout << setw(14) << left << wconvert(all_Kids[j]->getPhone()) << right << "| " << endl;
						}
					}

					wcout << endl;
					wcout << L"������� ����� ���� ����� ������� ������ �� ���� ����� �� �������� Enter" << endl;

					cin >> choise;
					int kid_id = 0;
					while (choise > temp || choise < 1)  //����� ������� �� �������� temp  
					{
						wcout << L"������� ����� ����, ��������� �� ���!" << endl;
						cin >> choise;
					}

					temp = 0; //�������� ������� ��� ���������� ����� � ������� ����������
					for (size_t j = 0; j < all_Kids.size(); ++j) // ��������� ���� ��� ������ ���������� �������� � ������ ������������
					{
						if (all_Kids[j]->getGroupID() == NULL)
						{
							++temp;
							if (temp == choise)
							{
								kid_id = all_Kids[j]->getDbID();// �������� �� ��� ���� ������ ������� ��� �������
								break;
							}
						}
					}
					groups_insert(gp_id, kid_id);
					this_thread::sleep_for(std::chrono::seconds(1));
					break;

				}
				break;
			case 2: // ������� ������� �� ������
				wcout << endl;
				wcout << L"������� ����� ���� ����� ����� �������� � ���� �� �������� Enter" << endl;

				cin >> choise;

				while (choise > all_Groups.size() || choise < 1)
				{
					wcout << L"������� ����� ����, ��������� �� ���!" << endl;
					ch = _getch();
					choise = ch - '0';
				}
				wcout << L"�� ������� �� ������ �������� ����: ";
				for (size_t i = 0; i < GroupKids.size(); ++i)
				{
					cout << GroupKids[choise - 1]->getName() << " ?" << endl;
					temp = GroupKids[choise - 1]->getDbID();
					break;
				}
				if (exit() == true)
				{
					groups_erase(temp);
					this_thread::sleep_for(std::chrono::seconds(1));
					break;
				}
				break;
			case 3: // ����� ������ ������ � �������
				emptyGraf = 0;
				for (int r = 0; r < 3; ++r)
				{
					for (int d = 0; d < 5; ++d)
					{
						emptyGraf += groups_grafFinder(r + 1, d + 1, gp_id);
					}
				}
				if (emptyGraf == 0)
				{
					wcout << endl;
					wcout << L"*** � ������ ������ ������ �� ��������! ***" << endl;
					wcout << endl;
				}
				this_thread::sleep_for(std::chrono::seconds(1));
				break;
			default:
				break;
			}
		} while (true);
	}

	void groups_insert(int gp_id, int kd_id)
	{
		string query = "UPDATE kids SET group_id = ? WHERE kid_id = ?";
		sqlite3_stmt* statement;

		// �������������� ������
		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK) {
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		// ����������� ��������
		sqlite3_bind_int(statement, 1, gp_id);
		sqlite3_bind_int(statement, 2, kd_id);

		// ��������� ���� ��������������� �������
		result = sqlite3_step(statement);

		if (result != SQLITE_DONE)
		{
			cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
		}
		else
		{
			wcout << endl;
			wcout << L"���� ������ ������ �� �����!" << endl;
			wcout << endl;
		}

		sqlite3_finalize(statement);
	}

	void groups_erase(int db_id) // �������� ������� �� ������ (NULL �� ������)
	{
		string query = "UPDATE kids SET group_id = NULL WHERE kid_id = ?";
		sqlite3_stmt* statement;

		// �������������� ������
		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK) {
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		// ����������� ��������
		sqlite3_bind_int(statement, 1, db_id);

		// ��������� ���� ��������������� �������
		result = sqlite3_step(statement);

		if (result != SQLITE_DONE)
		{
			cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
		}
		else
		{
			wcout << endl;
			wcout << L"���� ������ �������� � �����!" << endl;
			wcout << endl;
		}

		sqlite3_finalize(statement);
	}

	vector<shared_ptr<Kid>> groups_getSelected(int db_groupid) // �������� ����� �� ��������� ������
	{
		vector<shared_ptr<Kid>> GroupKids; //��������� ��� ���� ������ 

		//������ �� ������
		const char* query = "SELECT kid_id, name, parent_name, phone_number, group_id FROM Kids WHERE group_id = ?";
		sqlite3_stmt* statement;

		int result = sqlite3_prepare_v2(db, query, -1, &statement, nullptr);
		if (result != SQLITE_OK)
		{
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return {};
		}

		//����������� �������� ����� ��� ��������� �� ������ � ���� ������
		sqlite3_bind_int(statement, 1, db_groupid);

		// ������� �������� ������� ����� � ��������� �� ���� � ������
		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			//���������� ������ �� ���� ������
			int kid_id = sqlite3_column_int(statement, 0);
			const char* name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
			const char* parent_name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));
			const char* phone_number = reinterpret_cast<const char*>(sqlite3_column_text(statement, 3));
			int group_id = sqlite3_column_int(statement, 4);

			auto kid1 = make_shared<Kid>(kid_id, name, parent_name, phone_number, group_id);
			GroupKids.push_back(kid1);
		}

		sqlite3_finalize(statement);
		return GroupKids;
	}

	void groups_rename(int db_id)
	{
		wcout << endl;
		wcout << L"������ ���� ����� ��� �����" << endl;
		wcout << endl;

		setlocale(LC_ALL, "");
		wstring utf16Data;
		getline(wcin, utf16Data);

		// ����������� � UTF-8
		wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		string utf8Text = converter.to_bytes(utf16Data);

		string query = "UPDATE Groups SET group_name = '" + utf8Text + "' WHERE group_id = ?";
		sqlite3_stmt* statement;

		// �������������� ������
		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK) {
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		// ����������� ���������
		sqlite3_bind_int(statement, 1, db_id);

		// ��������� ���� ��������������� �������
		result = sqlite3_step(statement);

		//��������� ���������
		setlocale(LC_ALL, "en_US.UTF-8");

		if (result != SQLITE_DONE)
		{
			cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
		}
		else
		{
			wcout << endl;
			wcout << L"����� ����� ������ ��������" << endl;
			wcout << endl;
		}

		sqlite3_finalize(statement);
	}

	void groups_create()
	{
		wcout << endl;
		wcout << L"������ ����� ��� ���� �����" << endl;
		wcout << endl;

		setlocale(LC_ALL, "");
		wstring utf16Data;
		if (wcin.peek() == '\n') {
			// ���� ����, ��������� ���
			wcin.ignore();
		}
		getline(wcin, utf16Data);

		// ����������� � UTF-8
		wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		string utf8Text = converter.to_bytes(utf16Data);

		string query = "INSERT INTO Groups (group_name) VALUES ('" + utf8Text + "')";
		sqlite3_stmt* statement;

		// �������������� ������
		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK) {
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		// ��������� ���� ��������������� �������
		result = sqlite3_step(statement);

		//��������� ���������
		setlocale(LC_ALL, "en_US.UTF-8");

		if (result != SQLITE_DONE)
		{
			cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
		}
		else
		{
			wcout << endl;
			wcout << L"���� ������ ������ ��������" << endl;
			wcout << endl;
		}

		sqlite3_finalize(statement);
	}

	void groups_delete(int db_id)
	{

		vector<shared_ptr<Kid>> Group_kids = groups_getSelected(db_id);

		if (Group_kids.empty() == false)
		{
			string query = "UPDATE kids SET group_id = NULL WHERE group_id = ?";
			sqlite3_stmt* statement;

			// �������������� ������
			int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
			if (result != SQLITE_OK) {
				cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
				return;
			}

			// ����������� ��������
			sqlite3_bind_int(statement, 1, db_id);

			// ��������� ���� ��������������� �������
			result = sqlite3_step(statement);

			if (result != SQLITE_DONE)
			{
				cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
			}
			else
			{
			}

			sqlite3_finalize(statement);
		}

		string query = "DELETE FROM Groups WHERE group_id = ?";
		sqlite3_stmt* statement;

		// �������������� ������
		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK) {
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		// ����������� ���������
		sqlite3_bind_int(statement, 1, db_id);

		// ��������� ���� ��������������� �������
		result = sqlite3_step(statement);

		if (result != SQLITE_DONE)
		{
			cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
		}
		else
		{
			wcout << endl;
			wcout << L"����� ������ ��������" << endl;
			wcout << endl;
		}

		sqlite3_finalize(statement);
	}

	vector<shared_ptr<Kid>> groups_getAllKids()
	{
		vector<shared_ptr<Group>> allGroups = groups_getAll();
		vector<shared_ptr<Kid>> allKids; //��������� ��� ���� ������ 

		//������ �� ������
		const char* query = "SELECT kid_id, name, parent_name, phone_number, group_id FROM Kids";
		sqlite3_stmt* statement;

		int result = sqlite3_prepare_v2(db, query, -1, &statement, nullptr);
		if (result != SQLITE_OK)
		{
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return {};
		}

		// ������� �������� ������� ����� � ��������� �� ���� � ������
		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			//���������� ������ �� ���� ������
			int kid_id = sqlite3_column_int(statement, 0);
			const char* name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
			const char* parent_name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));
			const char* phone_number = reinterpret_cast<const char*>(sqlite3_column_text(statement, 3));
			int group_id = sqlite3_column_int(statement, 4);

			auto kid1 = make_shared<Kid>(kid_id, name, parent_name, phone_number, group_id);
			allKids.push_back(kid1);
		}

		sqlite3_finalize(statement);
		return allKids;
	}


	vector<shared_ptr<Group>> groups_getAll() // �������� ��������� � �������� (��� ������ �����)
	{
		vector<shared_ptr<Group>> all_Groups; //��������� ��� ���� ������ 
		all_Groups.reserve(6);

		//������ �� ������
		const char* query = "SELECT group_id, group_name FROM Groups";
		sqlite3_stmt* statement;

		int result = sqlite3_prepare_v2(db, query, -1, &statement, nullptr);
		if (result != SQLITE_OK)
		{
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return {};
		}

		// ������� �������� ������� ����� � ��������� �� ���� � ������
		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			//���������� ������ �� ���� ������
			int group_id = sqlite3_column_int(statement, 0);
			const char* name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));

			auto tool1 = make_shared<Group>(group_id, name);
			all_Groups.push_back(tool1);
		}

		sqlite3_finalize(statement);
		return all_Groups;
	}

	void trainer_actions()
	{
		do
		{
			vector<shared_ptr<Trainer>> all_trainers = trainer_getAll();

			wcout << setw(19) << right << L"��'� �������" << setw(23) << L"����� ��������" << L"" << endl;
			wcout << endl;
			string numeration;
			for (size_t i = 0; i < all_trainers.size(); ++i) //����� ��� ��������
			{
				if (i < 9)
				{
					cout << i + 1 << ".  ";
				}
				else cout << i + 1 << ". ";
				wcout << setw(22) << left << wconvert(all_trainers[i]->getName()) << right << "| ";
				wcout << setw(14) << left << wconvert(all_trainers[i]->getPhone()) << right << "| " << endl;
			}

			wcout << endl;
			wcout << L"1. ���������� ���������� ��� �������" << endl;
			wcout << L"2. �������� ������ �������" << endl;
			wcout << L"3. �������� �������" << endl;
			wcout << L"4. ����� ������ �� �������� ��������" << endl;
			wcout << endl;
			wcout << L"0. ����������� �� ����" << endl;

			int choise = 0;
			char ch = 0;

			ch = _getch();
			choise = ch - '0';

			while (choise > 4 || choise < 0)
			{
				wcout << L"������ ���� �� ����� ������� �� ����!\n ��������� �� ���!" << endl;
				ch = _getch();
				choise = ch - '0';
			}

			int temp = 0;// ��������������� ���������� ��� �������
			int emptyGraf = 0;// ��������������� ���������� ��� ������ � �������
			switch (choise)
			{
			case 0:
				system("cls");
				return;
				break;
			case 1: // ������������� ���� 
				wcout << endl;
				wcout << L"������� ����� ������� � ������ ���� ��������� ����� �� ������ ���������� �� �������� Enter" << endl;

				cin >> choise;

				while (choise > all_trainers.size() || choise < 1)
				{
					wcout << L"������� ����� �������, ��������� �� ���!" << endl;
					cin >> choise;
				}
				wcout << L"�� ������� �� ������ ���������� �������: ";
				for (size_t i = 0; i < all_trainers.size(); ++i)
				{
					cout << all_trainers[choise - 1]->getName() << " ?" << endl;
					temp = all_trainers[choise - 1]->getDbID();
					break;
				}
				if (exit() == true)
				{
					trainer_edit(temp);
					this_thread::sleep_for(std::chrono::seconds(1));
					break;
				}
				break;
			case 2: // ������� ������
				wcout << endl;
				wcout << L"�� ������� �� ������ �������� ������ �������?" << endl;
				if (exit() == true)
				{
					trainer_create();
					this_thread::sleep_for(std::chrono::seconds(1));
					break;
				}
				break;
			case 3: // ������� 
				wcout << endl;
				wcout << L"������� ����� ������� � ������ ���� ����� �� ������� �������� �� �������� Enter" << endl;

				cin >> choise;

				while (choise > all_trainers.size() || choise < 1)
				{
					wcout << L"������� ����� �������, ��������� �� ���!" << endl;
					cin >> choise;
				}
				wcout << L"�� ������� �� ������ �������� �������: ";
				for (size_t i = 0; i < all_trainers.size(); ++i)
				{
					cout << all_trainers[choise - 1]->getName() << " ?" << endl;
					temp = all_trainers[choise - 1]->getDbID();
					break;
				}
				if (exit() == true)
				{
					trainer_delete(temp);
					this_thread::sleep_for(std::chrono::seconds(1));
					break;
				}
			case 4:
				wcout << endl;
				wcout << L"������� ����� ������� � ������ ���� ������� ����� ������ ������" << endl;

				cin >> choise;

				while (choise > all_trainers.size() || choise < 1)
				{
					wcout << L"������� ����� �������, ��������� �� ���!" << endl;
					cin >> choise;
				}

				for (size_t i = 0; i < all_trainers.size(); ++i)
				{
					temp = all_trainers[choise - 1]->getDbID();
					break;
				}
				emptyGraf = 0;
				trainer_limiter(temp);
				for (int r = 0; r < 3; ++r)
				{
					for (int d = 0; d < 5; ++d)
					{
						emptyGraf += trainer_grafFinder(r + 1, d + 1, temp);
					}
				}
				if (emptyGraf == 0)
				{
					wcout << endl;
					wcout << L"*** � ������ �������� ������ �� ��������! ***" << endl;
					wcout << endl;
				}
				break;
			default:
				break;
			}
		} while (true);
	}

	void trainer_anti_dup(int trainer_id)
	{
		vector<shared_ptr<Trainer>> trainers = trainer_getAll();
		wstring tName;
		for (size_t i = 0; i < trainers.size(); ++i)
		{
			if (trainers[i]->getDbID() == trainer_id) tName = wconvert(trainers[i]->getName());
		}

		int r1_lesson = 0;
		int r2_lesson = 0;
		int r3_lesson = 0;

		for (int d = 1; d < 5; ++d)
		{
			for (int l = 1; l < 6; ++l)
			{
				r1_lesson = 0;
				r2_lesson = 0;
				r3_lesson = 0;
				r1_lesson = trainer_limeterP3(1, d, l, trainer_id);
				r2_lesson = trainer_limeterP3(2, d, l, trainer_id);
				r3_lesson = trainer_limeterP3(3, d, l, trainer_id);

				if (r1_lesson == r2_lesson && (r1_lesson > 0 || r2_lesson > 0))
				{
					wcout << endl;
					wcout << endl;
					wcout << L"� ������� '" << tName << L"' � ���� ��� ��������� 2 ������� !\n ���� ����� �������� ��� ������!";
					wcout << endl;
					wcout << endl;
					this_thread::sleep_for(std::chrono::seconds(2));
					return;
				}
				else if (r1_lesson == r3_lesson && (r1_lesson > 0 || r3_lesson > 0))
				{
					wcout << endl;
					wcout << endl;
					wcout << L"� ������� '" << tName << L"' � ���� ��� ��������� 2 ������� !\n ���� ����� �������� ��� ������!";
					wcout << endl;
					wcout << endl;
					this_thread::sleep_for(std::chrono::seconds(2));
					return;
				}
				else if (r2_lesson == r3_lesson && (r2_lesson > 0 || r3_lesson > 0))
				{
					wcout << endl;
					wcout << endl;
					wcout << L"� ������� '" << tName << L"' � ���� ��� ��������� 2 ������� !\n ���� ����� �������� ��� ������!";
					wcout << endl;
					wcout << endl;
					this_thread::sleep_for(std::chrono::seconds(2));
					return;
				}

			}
		}
	}

	void trainer_limiter(int trainer_id)
	{
		vector<shared_ptr<Trainer>> trainers = trainer_getAll();
		wstring tName;
		for (size_t i = 0; i < trainers.size(); ++i)
		{
			if (trainers[i]->getDbID() == trainer_id) tName = wconvert(trainers[i]->getName());
		}
		int dayCount = 0;
		int weekCount = 0;

		const int dayLimit = 3;//������������ ���������� ������� � ����
		const int weekLimit = 9;//������������ ���������� ������� � ������

		for (int d = 0; d < 5; ++d)
		{
			dayCount = 0;
			dayCount += trainer_limiterP2(1, d + 1, trainer_id);
			dayCount += trainer_limiterP2(2, d + 1, trainer_id);
			dayCount += trainer_limiterP2(3, d + 1, trainer_id);
			weekCount += dayCount;
			if (dayCount > dayLimit)
			{
				wcout << endl;
				wcout << endl;
				wcout << L"� ������� '" << tName << L"' ����������� ��� ������ �� ���� !" << endl;
				wcout << L"���� ����� ���������� ��� ������!" << endl;
				wcout << endl;
				wcout << endl;
				this_thread::sleep_for(std::chrono::seconds(2));
				return;
			}
			if (weekCount > weekLimit)
			{
				wcout << endl;
				wcout << endl;
				wcout << L"� ������� '" << tName << L"'  ����������� ��� ������ �� ������� !" << endl;
				wcout << L"���� ����� ���������� ��� ������!" << endl;
				wcout << endl;
				wcout << endl;
				this_thread::sleep_for(std::chrono::seconds(2));
				return;
			}
		}
	}

	int trainer_limiterP2(int road, int dayOFweek, int trainer_id)
	{
		wstring group_name = L" ";
		wstring trainer_name = L" ";

		string road_name = "";
		string dayGroup = "";
		string dayTrainer = "";
		wstring output = L" ";
		wstring output_road = L"";

		switch (road)
		{
		case 1:
			road_name = "Road1";
			output_road = L"����� ������";
			break;
		case 2:
			road_name = "Road2";
			output_road = L"����� ������";
			break;
		case 3:
			road_name = "Road3";
			output_road = L"����� ������";
			break;
		default:
			break;
		}

		switch (dayOFweek)
		{
		case 1://monday
			dayGroup = "monday_group";
			dayTrainer = "monday_trainer";
			output = L"��������";
			break;
		case 2://tuesday
			dayGroup = "tuesday_group";
			dayTrainer = "tuesday_trainer";
			output = L"³������";
			break;
		case 3://wednesday
			dayGroup = "wednesday_group";
			dayTrainer = "wednesday_trainer";
			output = L"������";
			break;
		case 4://thursday
			dayGroup = "thursday_group";
			dayTrainer = "thursday_trainer";
			output = L"�������";
			break;
		case 5://friday
			dayGroup = "friday_group";
			dayTrainer = "friday_trainer";
			output = L"�'������";
			break;
		default:
			break;
		}

		//������ �� ������
		string query = "SELECT lesson_hours, " + dayGroup + " , " + dayTrainer + " FROM " + road_name + " WHERE " + dayTrainer + " = ?";
		sqlite3_stmt* statement;

		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK)
		{
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return 0;
		}

		sqlite3_bind_int(statement, 1, trainer_id);

		int count = 0;
		int lesson_count = 0;
		int dayLesson_count = 0;

		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			++count;
			//���������� ������ �� ���� ������
			const char* lesson_hours = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));
			int group_id = sqlite3_column_int(statement, 1);
			int trainer_id = sqlite3_column_int(statement, 2);
		}
		sqlite3_finalize(statement);
		return count;
	}

	int trainer_limeterP3(int road, int dayOFweek, int lesson, int trainer_id)
	{
		wstring group_name = L" ";
		wstring trainer_name = L" ";

		string road_name = "";
		string dayGroup = "";
		string dayTrainer = "";
		string lessonsHour = "";
		wstring output = L" ";
		wstring output_road = L"";

		switch (road)
		{
		case 1:
			road_name = "Road1";
			output_road = L"����� ������";
			break;
		case 2:
			road_name = "Road2";
			output_road = L"����� ������";
			break;
		case 3:
			road_name = "Road3";
			output_road = L"����� ������";
			break;
		default:
			break;
		}

		switch (dayOFweek)
		{
		case 1://monday
			dayGroup = "monday_group";
			dayTrainer = "monday_trainer";
			output = L"��������";
			break;
		case 2://tuesday
			dayGroup = "tuesday_group";
			dayTrainer = "tuesday_trainer";
			output = L"³������";
			break;
		case 3://wednesday
			dayGroup = "wednesday_group";
			dayTrainer = "wednesday_trainer";
			output = L"������";
			break;
		case 4://thursday
			dayGroup = "thursday_group";
			dayTrainer = "thursday_trainer";
			output = L"�������";
			break;
		case 5://friday
			dayGroup = "friday_group";
			dayTrainer = "friday_trainer";
			output = L"�'������";
			break;
		default:
			break;
		}

		switch (lesson)
		{
		case 1:
			lessonsHour = "'9-11'";
			break;
		case 2:
			lessonsHour = "'11-13'";
			break;
		case 3:
			lessonsHour = "'13-15'";
			break;
		case 4:
			lessonsHour = "'15-17'";
			break;
		case 5:
			lessonsHour = "'17-19'";
			break;
		case 6:
			lessonsHour = "'19-21'";
			break;
		default:
			break;
		}

		//������ �� ������
		string query = "SELECT " + dayGroup + " , " + dayTrainer + " FROM " + road_name + " WHERE lesson_hours = " + lessonsHour + " AND " + dayTrainer + " = ?";
		sqlite3_stmt* statement;

		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK)
		{
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return 0;
		}

		sqlite3_bind_int(statement, 1, trainer_id);

		int count = 0;
		int lesson_count = 0;
		int dayLesson_count = 0;

		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			++count;
			//���������� ������ �� ���� ������
			int group_id = sqlite3_column_int(statement, 1);
			int trainer_id = sqlite3_column_int(statement, 2);
		}
		sqlite3_finalize(statement);
		if (count > 0) return 1;
		else return 0;
	}

	int trainer_grafFinder(int road, int dayOFweek, int trainer_id)//����� ������� �� ������� �������
	{
		vector<shared_ptr<Group>> groups = groups_getAll();
		vector<shared_ptr<Trainer>> trainers = trainer_getAll();
		wstring group_name = L" ";
		wstring trainer_name = L" ";

		string road_name = "";
		string dayGroup = "";
		string dayTrainer = "";
		wstring output = L" ";
		wstring output_road = L"";

		switch (road)
		{
		case 1:
			road_name = "Road1";
			output_road = L"����� ������";
			break;
		case 2:
			road_name = "Road2";
			output_road = L"����� ������";
			break;
		case 3:
			road_name = "Road3";
			output_road = L"����� ������";
			break;
		default:
			break;
		}

		switch (dayOFweek)
		{
		case 1://monday
			dayGroup = "monday_group";
			dayTrainer = "monday_trainer";
			output = L"��������";
			break;
		case 2://tuesday
			dayGroup = "tuesday_group";
			dayTrainer = "tuesday_trainer";
			output = L"³������";
			break;
		case 3://wednesday
			dayGroup = "wednesday_group";
			dayTrainer = "wednesday_trainer";
			output = L"������";
			break;
		case 4://thursday
			dayGroup = "thursday_group";
			dayTrainer = "thursday_trainer";
			output = L"�������";
			break;
		case 5://friday
			dayGroup = "friday_group";
			dayTrainer = "friday_trainer";
			output = L"�'������";
			break;
		default:
			break;
		}

		//������ �� ������
		string query = "SELECT lesson_hours, " + dayGroup + " , " + dayTrainer + " FROM " + road_name + " WHERE " + dayTrainer + " = ?";
		sqlite3_stmt* statement;

		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK)
		{
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return 0;
		}

		sqlite3_bind_int(statement, 1, trainer_id);

		int count = 0;

		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			++count;
			if (count == 1)
			{
				wcout << setw(64) << setfill(L'_') << L"" << endl;
				wcout << setw(24) << setfill(L' ') << right << "*" << output_road << "*" << endl;
				wcout << endl;

				wcout << setw(64) << setfill(L'-') << L"" << endl;
				wcout << setw(27) << setfill(L' ') << right << "*" << output << "*" << endl;
				wcout << endl;

				wcout << setw(14) << right << L"������ ������" << setw(15) << L"�����" << setw(25) << L"������" << endl;
			}
			//���������� ������ �� ���� ������
			const char* lesson_hours = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));

			//���� ������ �������� ����� �� �� ��
			int group_id = sqlite3_column_int(statement, 1);
			if (group_id != NULL) // ����� �������� ����� �� �� ��
			{
				//����� � ������ �������� ����� ����� ����� �������
				auto it = std::find_if(groups.begin(), groups.end(),
					[group_id](const std::shared_ptr<Group>& group) { return group->getDbID() == group_id; });
				if (it != groups.end())
				{
					// ��� ������ ������ ������� ��� � ����������� ����������
					group_name = wconvert((*it)->getName());
				}
			}
			else if (group_id == NULL) group_name = L"    --"; // � ��������� ������ ������ ��������

			int trainer_id = sqlite3_column_int(statement, 2);
			if (trainer_id != NULL)
			{
				auto it1 = std::find_if(trainers.begin(), trainers.end(),
					[trainer_id](const std::shared_ptr<Trainer>& trainer) { return trainer->getDbID() == trainer_id; });
				if (it1 != trainers.end())
				{
					trainer_name = wconvert((*it1)->getName());
				}
			}
			else if (trainer_id == NULL) trainer_name = L"        --";


			wcout << setw(7) << left << L" " << setw(15) << lesson_hours << setw(21) << group_name << setw(25) << trainer_name << endl;
		}
		if (count != 0)
		{
			wcout << setw(64) << setfill(L'-') << L"" << endl;
			wcout << setfill(L' ') << L"" << endl;
			cout << endl;
		}

		sqlite3_finalize(statement);
		if (count != 0) { return 1; }
		else { return 0; }
	}

	void trainer_create()
	{
		setlocale(LC_ALL, "");
		wstring utf16Name;
		wstring utf16Phone;
		wstring utf16Pay;

		if (wcin.peek() == '\n')
		{
			wcin.ignore();
		}
		wcout << endl;
		wcout << L"������ ��'� ������ �������" << endl;
		wcout << endl;
		getline(wcin, utf16Name);
		wcout << endl;
		wcout << L"������ ���������� ����� ������ �������" << endl;
		wcout << endl;
		getline(wcin, utf16Phone);
		wcout << endl;
		wcout << L"������ �������� �������� ����� ������ �������" << endl;
		wcout << endl;
		getline(wcin, utf16Pay);

		// ����������� � UTF-8
		wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		string utf8Name = converter.to_bytes(utf16Name);
		string utf8Phone = converter.to_bytes(utf16Phone);
		string utf8Pay = converter.to_bytes(utf16Pay);

		string query = "INSERT INTO Trainers (name, phone_number, pay_hour) VALUES ('" + utf8Name + "', '" + utf8Phone + "', " + utf8Pay + ")";
		sqlite3_stmt* statement;

		// �������������� ������
		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK) {
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		// ��������� ���� ��������������� �������
		result = sqlite3_step(statement);

		//��������� ���������
		setlocale(LC_ALL, "en_US.UTF-8");

		if (result != SQLITE_DONE)
		{
			cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
		}
		else
		{
			wcout << endl;
			wcout << L"����� ������ ������ ���������" << endl;
			wcout << endl;
		}

		sqlite3_finalize(statement);
	}

	void trainer_edit(int db_id)
	{
		wcout << endl;
		wcout << L"������� �� ���� �� ������ ����������:" << endl;
		wcout << endl;

		wcout << L"1. ��'�" << endl;
		wcout << L"2. �������" << endl;
		wcout << L"3. �������� �������� �����" << endl;

		int choise = 0;
		char ch = 0;

		ch = _getch();
		choise = ch - '0';

		while (choise > 3 || choise < 1)
		{
			wcout << L"������ ���� �� ����� ������� �� ����!\n ��������� �� ���!" << endl;
			ch = _getch();
			choise = ch - '0';
		}

		//���������� ���������� ��� �������
		string setParametr;
		wstring outcome;

		wstring utf16Data;
		string utf8Text;
		wstring_convert<std::codecvt_utf8<wchar_t>> converter;

		string query;
		sqlite3_stmt* statement;

		wcin.ignore();
		switch (choise)
		{
		case 1://���
			wcout << L"��'�" << endl;
			setParametr = "name";

			setlocale(LC_ALL, "");

			getline(wcin, utf16Data);
			utf8Text = converter.to_bytes(utf16Data);

			query = "UPDATE Trainers SET " + setParametr + " = '" + utf8Text + "' WHERE trainer_id = ?";

			outcome = L"��'� ������� ������ ������!";
			break;
		case 2://�������
			wcout << L"�������" << endl;
			setParametr = "phone_number";

			setlocale(LC_ALL, "");

			getline(wcin, utf16Data);
			utf8Text = converter.to_bytes(utf16Data);

			query = "UPDATE Trainers SET " + setParametr + " = '" + utf8Text + "' WHERE trainer_id = ?";

			outcome = L"����� �������� ������� ������ ������!";
			break;
		case 3://��������
			wcout << L"�������� �������� �����" << endl;
			setParametr = "pay_hour";

			setlocale(LC_ALL, "");

			getline(wcin, utf16Data);
			utf8Text = converter.to_bytes(utf16Data);

			query = "UPDATE Trainers SET " + setParametr + " = '" + utf8Text + "' WHERE trainer_id = ?";

			outcome = L"�������� ����� ������� ������ ������!";
			break;
		default:
			break;
		}

		// �������������� ������
		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK) {
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		// ����������� ���������
		sqlite3_bind_int(statement, 1, db_id);

		// ��������� ���� ��������������� �������
		result = sqlite3_step(statement);

		//��������� ���������
		setlocale(LC_ALL, "en_US.UTF-8");

		if (result != SQLITE_DONE)
		{
			cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
		}
		else
		{
			wcout << endl;
			wcout << outcome << endl;
			wcout << endl;
		}

		sqlite3_finalize(statement);
	}

	void trainer_delete(int db_id)
	{
		string road = "";
		string dayTrainer = "";

		for (int i = 0; i < 3; ++i)
		{
			if (i == 0) { road = "Road1"; }
			else if (i == 1) { road = "Road2"; }
			else if (i == 2) { road = "Road3"; }

			for (int dayOFweek = 0; dayOFweek < 5; ++dayOFweek)
			{

				switch (dayOFweek)
				{
				case 0://monday
					dayTrainer = "monday_trainer";
					break;
				case 1://tuesday
					dayTrainer = "tuesday_trainer";
					break;
				case 2://wednesday
					dayTrainer = "wednesday_trainer";
					break;
				case 3://thursday
					dayTrainer = "thursday_trainer";
					break;
				case 4://friday
					dayTrainer = "friday_trainer";
					break;
				default:
					break;
				}

				string query = "UPDATE " + road + " SET " + dayTrainer + " = NULL WHERE " + dayTrainer + " = ?";
				sqlite3_stmt* statement;

				// �������������� ������
				int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
				if (result != SQLITE_OK) {
					cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
					return;
				}

				// ����������� ��������
				sqlite3_bind_int(statement, 1, db_id);

				// ��������� ���� ��������������� �������
				result = sqlite3_step(statement);

				if (result != SQLITE_DONE)
				{
					cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
				}
				else {}

				sqlite3_finalize(statement);

			}
		}

		//�������� ����� ��������

		string query = "DELETE FROM Trainers WHERE trainer_id = ?";
		sqlite3_stmt* statement;

		// �������������� ������
		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK) {
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		// ����������� ���������
		sqlite3_bind_int(statement, 1, db_id);

		// ��������� ���� ��������������� �������
		result = sqlite3_step(statement);

		if (result != SQLITE_DONE)
		{
			cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
		}
		else
		{
			wcout << endl;
			wcout << L"���������� ��� ������� ������ ��������!" << endl;
			wcout << endl;
		}

		sqlite3_finalize(statement);
	}

	shared_ptr<Trainer> trainer_getSelected(int db_id)
	{
		shared_ptr<Trainer> trainer1;

		//������ �� ������
		const char* query = "SELECT trainer_id, name, phone_number, pay_hour FROM Trainers WHERE trainer_id = ?";
		sqlite3_stmt* statement;

		int result = sqlite3_prepare_v2(db, query, -1, &statement, nullptr);
		if (result != SQLITE_OK)
		{
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return {};
		}

		// ����������� ��������
		sqlite3_bind_int(statement, 1, db_id);

		int count = 0;
		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			//���������� ������ �� ���� ������
			int trainer_id = sqlite3_column_int(statement, 0);
			const char* name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
			const char* phone_number = reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));
			int pay_hour = sqlite3_column_int(statement, 3);

			trainer1 = make_shared<Trainer>(trainer_id, name, phone_number, pay_hour);
		}

		sqlite3_finalize(statement);
		return trainer1;
	}

	vector<shared_ptr<Trainer>> trainer_getAll()
	{
		vector<shared_ptr<Trainer>> all_Trainers; //��������� ��� ���� ������ 
		all_Trainers.reserve(6);

		//������ �� ������
		const char* query = "SELECT trainer_id, name, phone_number, pay_hour FROM Trainers";
		sqlite3_stmt* statement;

		int result = sqlite3_prepare_v2(db, query, -1, &statement, nullptr);
		if (result != SQLITE_OK)
		{
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return {};
		}

		// ������� �������� ������� ����� � ��������� �� ���� � ������
		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			//���������� ������ �� ���� ������
			int trainer_id = sqlite3_column_int(statement, 0);
			const char* name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
			const char* phone_number = reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));
			int pay_hour = sqlite3_column_int(statement, 3);

			auto tool1 = make_shared<Trainer>(trainer_id, name, phone_number, pay_hour);
			all_Trainers.push_back(tool1);
		}

		sqlite3_finalize(statement);
		return all_Trainers;
	}

	bool exit()//��������������� ��� ������
	{

		wcout << L"��� ����������� �������� ������ - Y" << endl;
		wcout << L"��� ����� �������� ������ - N" << endl;
		while (true)
		{
			char oa = _getch();
			if (oa == 'y' || oa == 'Y' || oa == '�' || oa == '�')
				return true;
			else if (oa == 'n' || oa == 'N' || oa == '�' || oa == '�')
				return false;
		}
	}
	wstring wconvert(string get) // ��������� �� ������� ������ � ��������
	{
		wstring_convert<codecvt_utf8<wchar_t>> converter;
		wstring wideString = converter.from_bytes(get);
		return wideString;
	}
};