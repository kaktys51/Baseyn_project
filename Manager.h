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
			int total = 4; //максимальное количество функций в меню

			wcout << L"+++ Менеджер роботи басейну +++\n" << endl;
			wcout << L"*** Головне меню ***\n" << endl;

			wcout << L"1. Список тренерів" << endl;
			wcout << L"2. Список груп" << endl;
			wcout << L"3. Список учнів" << endl;
			wcout << L"4. Графік занять" << endl;
			wcout << endl;
			wcout << L"0. Завершити роботу" << endl;

			wcout << endl;
			wcout << L"Для вибору натисніть клавішу на клавіатурі що співпадае з номером функції." << endl;

			ch = _getch();
			choise = ch - '0';

			while (choise > total || choise < 0)
			{
				wcout << L"Пункта меню за таким номером не існує!\n Спробуйте ще раз!" << endl;
				ch = _getch();
				choise = ch - '0';
			}

			switch (choise)
			{
			case 0://выход
				return;
			case 1: // тренера
				system("cls");
				trainer_actions();
				break;
			case 2: //группы 
				system("cls");
				group_actions();
				break;
			case 3: //ученики 
				system("cls");
				kids_actions();
				break;
			case 4: //график
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
			all_kids = groups_getAllKids(); // получаем всех детей из базы данных
			wcout << endl;
			wcout << setw(45) << right << L"Список усіх учнів!" << endl;
			wcout << endl;
			wcout << setw(14) << right << L"Ім'я" << setw(35) << L"Ім'я одного з батьків" << setw(17) << L"Номер телефону" << L"" << endl;
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

			//блок меню
			wcout << endl;
			wcout << L"1. Редагувати інформацію про учня." << endl;
			wcout << L"2. Створити нового учня." << endl;
			wcout << L"3. Видалити учня." << endl;
			wcout << endl;
			wcout << L"0. Повернутись до меню." << endl;

			int choise = 0;
			char ch = 0;

			ch = _getch();
			choise = ch - '0';

			int temp = 0;// вспомогательная переменная для функций
			while (choise > 3 || choise < 0)
			{
				wcout << L"Пункта меню за таким номером не існує!\n Спробуйте ще раз!" << endl;
				ch = _getch();
				choise = ch - '0';
			}

			switch (choise)
			{
			case 0://выход
				system("cls");
				return;
				break;
			case 1: // редактировать инфо 
				wcout << endl;
				wcout << L"Введить номер учня зі списка вище інформацю якого ви бажаєте редагувати та натисніть Enter" << endl;

				cin >> choise;

				while (choise > all_kids.size() || choise < 1)
				{
					wcout << L"Невірний номер учня, спробуйте ще раз!" << endl;
					cin >> choise;
				}
				wcout << endl;
				wcout << L"Ви впевнені що бажаєте редагувати учня: ";
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
			case 2: // создать нового
				wcout << endl;
				wcout << L"Ви впевнені що бажаєте створити нового учня? " << endl;
				wcout << endl;
				if (exit() == true)
				{
					kids_create();
					this_thread::sleep_for(std::chrono::seconds(1));
					break;
				}
				break;
			case 3: // удалить 
				wcout << endl;
				wcout << L"Введить номер учня зі списка вище якого ви бажаете видалити та натисніть Enter" << endl;

				cin >> choise;

				while (choise > all_kids.size() || choise < 1)
				{
					wcout << L"Невірний номер учня, спробуйте ще раз!" << endl;
					cin >> choise;
				}
				wcout << endl;
				wcout << L"Ви впевнені що бажаєте видалити учня: ";
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
		wcout << L"Введіть ім'я нового учня" << endl;
		wcout << endl;
		getline(wcin, utf16Name);
		wcout << endl;
		wcout << L"Введіть ім'я одного з батьків нового учня " << endl;
		wcout << endl;
		getline(wcin, utf16Parent);
		wcout << endl;
		wcout << L"Введіть номер телефону нового учня" << endl;
		wcout << endl;
		getline(wcin, utf16Phone);

		// конвертация в UTF-8
		wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		string utf8Name = converter.to_bytes(utf16Name);
		string utf8Parent = converter.to_bytes(utf16Parent);
		string utf8Phone = converter.to_bytes(utf16Phone);

		string query = "INSERT INTO Kids (name, parent_name, phone_number) VALUES ('" + utf8Name + "', '" + utf8Parent + "', " + utf8Phone + ")";
		sqlite3_stmt* statement;

		// подготавливаем запрос
		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK) {
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		// выполняем шаги подготовленного запроса
		result = sqlite3_step(statement);

		//возращаем кодировку
		setlocale(LC_ALL, "en_US.UTF-8");

		if (result != SQLITE_DONE)
		{
			cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
		}
		else
		{
			wcout << endl;
			wcout << L"Новий учень успішно створений" << endl;
			wcout << endl;
		}

		sqlite3_finalize(statement);
	}

	void kids_edit(int db_id)
	{
		//меню параметров
		wcout << endl;
		wcout << L"Виберіть що саме ви хочете редагувати:" << endl;
		wcout << endl;

		wcout << L"1. Ім'я" << endl;
		wcout << L"2. Ім'я одного з батьків" << endl;
		wcout << L"3. Номер телефону учня" << endl;

		int choise = 0;
		char ch = 0;

		ch = _getch();
		choise = ch - '0';

		while (choise > 3 || choise < 1)
		{
			wcout << L"Пункта меню за таким номером не існує!\n Спробуйте ще раз!" << endl;
			ch = _getch();
			choise = ch - '0';
		}

		//объявление параметров для запроса
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
		case 1://имя
			wcout << L"Ім'я" << endl;
			setParametr = "name";

			setlocale(LC_ALL, "");

			getline(wcin, utf16Data);
			utf8Text = converter.to_bytes(utf16Data);

			query = "UPDATE Kids SET " + setParametr + " = '" + utf8Text + "' WHERE kid_id = ?";

			outcome = L"Ім'я учня успішно змінено!";
			break;
		case 2://имя одного из родителей
			wcout << L"Ім'я одного з батьків" << endl;
			setParametr = "parent_name";

			setlocale(LC_ALL, "");

			getline(wcin, utf16Data);
			utf8Text = converter.to_bytes(utf16Data);

			query = "UPDATE Kids SET " + setParametr + " = '" + utf8Text + "' WHERE kid_id = ?";

			outcome = L"Ім'я одного з батьків учня успішно змінено!";
			break;
		case 3://телефон
			wcout << L"Номер телефону учня" << endl;
			setParametr = "phone_number";

			setlocale(LC_ALL, "");

			getline(wcin, utf16Data);
			utf8Text = converter.to_bytes(utf16Data);

			query = "UPDATE Kids SET " + setParametr + " = '" + utf8Text + "' WHERE kid_id = ?";

			outcome = L"Номер телефону учня успішно змінено!";
			break;
		default:
			break;
		}

		// Подготавливаем запрос
		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK) {
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		// Привязываем параметры
		sqlite3_bind_int(statement, 1, db_id);

		// Выполняем шаги подготовленного запроса
		result = sqlite3_step(statement);

		//возращаем кодировку
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
		//основная часть удаления

		string query = "DELETE FROM Kids WHERE kid_id = ?;";
		sqlite3_stmt* statement;

		// Подготавливаем запрос
		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK) {
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		// Привязываем параметры
		sqlite3_bind_int(statement, 1, db_id);

		// Выполняем шаги подготовленного запроса
		result = sqlite3_step(statement);

		if (result != SQLITE_DONE)
		{
			cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
		}
		else
		{
			wcout << endl;
			wcout << L"Інформація про учня успішно видалена!" << endl;
			wcout << endl;
		}

		sqlite3_finalize(statement);
	}

	void graf_actions() //меню работы графиков
	{
		bool quit = false;
		int roadNum = 0;
		do
		{
			vector<shared_ptr<Group>> groups = groups_getAll();
			vector<shared_ptr<Trainer>> trainers = trainer_getAll();

			wcout << endl;
			wcout << L"*** Графіки занять на доріжках ***" << endl;
			wcout << endl;


			wcout << L"Оберіть доріжку графік якої бажаєте переглянути" << endl;
			wcout << endl;

			wcout << L"1. Перша доріжка." << endl;
			wcout << L"2. Друга доріжка." << endl;
			wcout << L"3. Третя доріжка." << endl;

			//блок выбора дорожки
			int choise = 0;
			char ch = 0;

			ch = _getch();
			choise = ch - '0';

			while (choise > 3 || choise < 1)
			{
				wcout << L"Пункта меню за таким номером не існує!\n Спробуйте ще раз!" << endl;
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
			wcout << L"1. Редагувати поточну доріжку" << endl;
			wcout << L"2. Переглянути іншу доріжку" << endl;
			wcout << endl;
			wcout << L"0. Повернутись до меню" << endl;

			ch = _getch();
			choise = ch - '0';

			while (choise > 2 || choise < 0)
			{
				wcout << L"Пункта меню за таким номером не існує!\n Спробуйте ще раз!" << endl;
				ch = _getch();
				choise = ch - '0';
			}

			switch (choise)
			{
			case 0:
				wcout << endl;
				wcout << L"Повернутись до меню?" << endl;
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

	void graf_inside(int road)//функция редактирования внутри графика
	{
		int dayOfWeek = 0;
		int choise = 0;
		bool quit = false;
		do
		{
			wcout << endl;
			wcout << L"*** Дії з графіком ***" << endl;
			wcout << endl;

			wcout << L"1. Додати нове заняття." << endl;
			wcout << L"2. Вилучити заняття." << endl;
			wcout << L"3. Замінити групу." << endl;
			wcout << L"4. Замінити тренера." << endl;
			wcout << endl;

			wcout << L"0. Вийти." << endl;

			char ch = 0;

			ch = _getch();
			choise = ch - '0';

			while (choise > 4 || choise < 0)
			{
				wcout << L"Пункта меню за таким номером не існує!\n Спробуйте ще раз!" << endl;
				ch = _getch();
				choise = ch - '0';
			}

			switch (choise)
			{
			case 0:
				return;
				break;
			case 1:// добавить новое знятие в определенное время
				dayOfWeek = graf_choiseDay();
				wcout << L"Додати нове заняття?" << endl;
				if (exit() == true)
				{
					graf_addLesson(dayOfWeek, road);
					this_thread::sleep_for(std::chrono::seconds(1));
					break;
				}
				break;
			case 2:// очистка занятия
				dayOfWeek = graf_choiseDay();
				wcout << L"Ви дійсно бажаєте видалити заняття?" << endl;
				if (exit() == true)
				{
					graf_deleteLesson(dayOfWeek, road);
					this_thread::sleep_for(std::chrono::seconds(1));
					break;
				}
				break;
			case 3:// замена в оределенном занятии группы
				dayOfWeek = graf_choiseDay();
				wcout << L"Ви дійсно бажаєте замінити групу?" << endl;
				if (exit() == true)
				{
					graf_update(1, dayOfWeek, road);
					this_thread::sleep_for(std::chrono::seconds(1));
					break;
				}
				break;
			case 4:// замена в оределенном занятии тренера
				dayOfWeek = graf_choiseDay();
				wcout << L"Ви дійсно бажаєте замінити тренера?" << endl;
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
		wcout << L"Виберіть день тижня:" << endl;
		wcout << endl;

		wcout << L"1. Понеділок" << endl;
		wcout << L"2. Вівторок" << endl;
		wcout << L"3. Середа" << endl;
		wcout << L"4. Четверг" << endl;
		wcout << L"5. П'ятниця" << endl;
		wcout << endl;

		int choise = 0;
		char ch = 0;

		ch = _getch();
		choise = ch - '0';

		while (choise > 5 || choise < 1)
		{
			wcout << L"Пункта меню за таким номером не існує!\n Спробуйте ще раз!" << endl;
			ch = _getch();
			choise = ch - '0';
		}
		return choise;
	}

	void graf_update(int gt, int dayOfWeek, int road)//gt - параметр значение которого влиеет что именно будет изменять запрос 
	{
		//объявление переменных для работы функции
		int choise = 0;
		string road_name = "";
		string dayGroup = "";
		string dayTrainer = "";
		string lessonsHour = "";
		int group_id = 0;
		int trainer_id = 0;
		vector<shared_ptr<Group>> all_Groups = groups_getAll();
		vector<shared_ptr<Trainer>> all_trainers = trainer_getAll();

		//блок выбора часов занятий 
		wcout << endl;
		wcout << L"О котрій годині проходить заняття параметри якого ви бажаєте змінити?" << endl;
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
			wcout << L"Пункта меню за таким номером не існує!\n Спробуйте ще раз!" << endl;
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

		if (gt == 1)//вариант с изменением группы
		{
			wcout << endl;
			wcout << endl;
			wcout << L"Список доступних груп." << endl;
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
			wcout << L"Введіть номер групи для заняття та натисніть Enter" << endl;
			wcout << endl;

			choise = 0;
			cin >> choise;

			while (choise > all_Groups.size() || choise < 1)
			{
				wcout << endl;
				wcout << L"Групи за таким номером не існує!\n Спробуйте ще раз!" << endl;
				cin >> choise;
			}

			for (size_t i = 0; i < all_Groups.size(); ++i)
			{
				group_id = all_Groups[choise - 1]->getDbID();
			}
		}
		else if (gt == 2)//вариант с изменением тренера
		{
			//блок выбора тренера 
			wcout << endl;
			wcout << endl;
			wcout << L"Список доступних тренерів." << endl;
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
			wcout << L"Введіть номер тренера для заняття та натисніть Enter" << endl;
			wcout << endl;

			choise = 0;
			cin >> choise;

			while (choise > all_trainers.size() || choise < 1)
			{
				wcout << endl;
				wcout << L"Тренера за таким номером не існує!\n Спробуйте ще раз!" << endl;
				cin >> choise;
			}

			for (size_t i = 0; i < all_trainers.size(); ++i)
			{
				trainer_id = all_trainers[choise - 1]->getDbID();
			}
		}
		// основаная часть запроса 
		switch (road)//по значению подставляем нужную дорожку
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

		switch (dayOfWeek)//по значению подставляем нужные названия параметров
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
		if (gt == 1)//вариант с изменением группы
		{
			query = "UPDATE " + road_name + " SET " + dayGroup + " = ? WHERE lesson_hours = " + lessonsHour + "";
		}
		else if (gt == 2)//вариант с изменением тренера 
		{
			query = "UPDATE " + road_name + " SET " + dayTrainer + " = ? WHERE lesson_hours = " + lessonsHour + "";
		}
		sqlite3_stmt* statement;

		// Подготавливаем запрос
		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK) {
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		if (gt == 1) { sqlite3_bind_int(statement, 1, group_id); }
		else if (gt == 2) {
			sqlite3_bind_int(statement, 1, trainer_id);
		}

		// Выполняем шаги подготовленного запроса
		result = sqlite3_step(statement);

		//возращаем кодировку
		setlocale(LC_ALL, "en_US.UTF-8");

		if (result != SQLITE_DONE)
		{
			cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
		}
		else
		{
			wcout << endl;
			if (gt == 1) { wcout << L"Групу успішно замінено!" << endl; }
			else if (gt == 2) { wcout << L"Тренера успішно замінено!" << endl; }
			wcout << endl;
		}

		sqlite3_finalize(statement);
	}

	void graf_deleteLesson(int dayOfWeek, int road)
	{
		//объявление переменных для работы функции
		int choise = 0;
		string road_name = "";
		string dayGroup = "";
		string dayTrainer = "";
		string lessonsHour = "";

		//блок выбора часов занятий 

		wcout << endl;
		wcout << L"О котрій годині проходить заняття яке ви бажаєте видалити?" << endl;
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
			wcout << L"Пункта меню за таким номером не існує!\n Спробуйте ще раз!" << endl;
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

		// основаная часть запроса 

		switch (road)//по значению подставляем нужную дорожку
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

		switch (dayOfWeek)//по значению подставляем нужные названия параметров
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

		// Подготавливаем запрос
		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK) {
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		// Выполняем шаги подготовленного запроса
		result = sqlite3_step(statement);

		//возращаем кодировку
		setlocale(LC_ALL, "en_US.UTF-8");

		if (result != SQLITE_DONE)
		{
			cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
		}
		else
		{
			wcout << endl;
			wcout << L"Заняття успішно видалене з графіку" << endl;
			wcout << endl;
		}

		sqlite3_finalize(statement);
	}

	void graf_addLesson(int dayOfWeek, int road)
	{
		//объявление переменных для работы функции
		int choise = 0;
		int group_id = 0;
		int trainer_id = 0;
		string road_name = "";
		string dayGroup = "";
		string dayTrainer = "";
		string lessonsHour = "";
		vector<shared_ptr<Group>> all_Groups = groups_getAll();
		vector<shared_ptr<Trainer>> all_trainers = trainer_getAll();

		//блок выбора часов занятий 

		wcout << endl;
		wcout << L"Оберіть години для заняття" << endl;
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
			wcout << L"Пункта меню за таким номером не існує!\n Спробуйте ще раз!" << endl;
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

		// блок выбора группы
		wcout << endl;
		wcout << endl;
		wcout << L"Список доступних груп." << endl;
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
		wcout << L"Введіть номер групи для заняття та натисніть Enter" << endl;
		wcout << endl;

		choise = 0;
		cin >> choise;

		while (choise > all_Groups.size() || choise < 1)
		{
			wcout << endl;
			wcout << L"Групи за таким номером не існує!\n Спробуйте ще раз!" << endl;
			cin >> choise;
		}

		for (size_t i = 0; i < all_Groups.size(); ++i)
		{
			group_id = all_Groups[choise - 1]->getDbID();
		}

		//блок выбора тренера 
		wcout << endl;
		wcout << endl;
		wcout << L"Список доступних тренерів." << endl;
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
		wcout << L"Введіть номер тренера для заняття та натисніть Enter" << endl;
		wcout << endl;

		choise = 0;
		cin >> choise;

		while (choise > all_trainers.size() || choise < 1)
		{
			wcout << endl;
			wcout << L"Тренера за таким номером не існує!\n Спробуйте ще раз!" << endl;
			cin >> choise;
		}

		for (size_t i = 0; i < all_trainers.size(); ++i)
		{
			trainer_id = all_trainers[choise - 1]->getDbID();
		}

		// основаная часть запроса 

		switch (road)//по значению подставляем нужную дорожку
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

		switch (dayOfWeek)//по значению подставляем нужные названия параметров
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

		// Подготавливаем запрос
		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK) {
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		// Привязываем параметры
		sqlite3_bind_int(statement, 1, group_id);
		sqlite3_bind_int(statement, 2, trainer_id);

		// Выполняем шаги подготовленного запроса
		result = sqlite3_step(statement);

		//возращаем кодировку
		setlocale(LC_ALL, "en_US.UTF-8");

		if (result != SQLITE_DONE)
		{
			cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
		}
		else
		{
			wcout << endl;
			wcout << L"Заняття успішно додано у графік" << endl;
			wcout << endl;
		}

		sqlite3_finalize(statement);
	}

	void graf_printFullRoad(int road) // переделать функцию на цикл вызова graf_RgetByDAY с новым днем каждый цикл
	{
		wstring sRoad = L"";
		switch (road)
		{
		case 1:
			sRoad = L"Перша доріжка";
			break;
		case 2:
			sRoad = L"Друга доріжка";
			break;
		case 3:
			sRoad = L"Третя доріжка";
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
			output = L"Понеділок";
			break;
		case 2://tuesday
			dayGroup = "tuesday_group";
			dayTrainer = "tuesday_trainer";
			output = L"Вівторок";
			break;
		case 3://wednesday
			dayGroup = "wednesday_group";
			dayTrainer = "wednesday_trainer";
			output = L"Середа";
			break;
		case 4://thursday
			dayGroup = "thursday_group";
			dayTrainer = "thursday_trainer";
			output = L"Четверг";
			break;
		case 5://friday
			dayGroup = "friday_group";
			dayTrainer = "friday_trainer";
			output = L"П'ятниця";
			break;
		default:
			break;
		}

		//запрос на данные
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

		wcout << setw(14) << right << L"Години занять" << setw(15) << L"Група" << setw(25) << L"Тренер" << endl;

		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			//получаемые данные из базы данных
			const char* lesson_hours = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));

			//блок поиска названия групп по их ид
			int group_id = sqlite3_column_int(statement, 1);
			if (group_id != NULL) // вывод названия групп по их ид
			{
				//поиск в веторе названия групп через лямду функцию
				auto it = std::find_if(groups.begin(), groups.end(),
					[group_id](const std::shared_ptr<Group>& group) { return group->getDbID() == group_id; });
				if (it != groups.end())
				{
					// как объект найден достаем имя и присваеваем переменной
					group_name = wconvert((*it)->getName());
				}
			}
			else if (group_id == NULL) group_name = L"    --"; // в противном случае ставим пропуски

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
			wcout << L"Список доступних груп." << endl;
			wcout << endl;

			vector<shared_ptr<Group>> all_Groups;
			vector<shared_ptr<Kid>> all_kids;
			all_Groups = groups_getAll(); // получаем все группы 
			all_kids = groups_getAllKids(); // получаем всех детей из базы данных

			for (size_t i = 0; i < all_Groups.size(); ++i) //вывод всех детей по группно
			{
				bool havekids = false;
				cout << setfill('-') << setw(63) << "" << endl;
				cout << setfill(' ') << setw(27) << right << i + 1 << ". " << all_Groups[i]->getName() << ": " << endl;
				cout << endl;
				wcout << setw(10) << right << L"Ім'я" << setw(35) << L"Ім'я одного з батьків" << setw(17) << L"Номер телефону" << L"" << endl;
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
				if (havekids == false) wcout << setw(42) << L"Пуста группа!" << endl;
				wcout << endl;
			}

			for (size_t j = 0; j < all_kids.size(); ++j)// вывод учеников 
			{
				if (all_kids[j]->getGroupID() == NULL)
				{
					cout << setfill('-') << setw(63) << "" << endl;
					wcout << setfill(L' ') << setw(55) << right << L"Учні що не знаходяться в жодній группі:" << endl;
					cout << endl;
					wcout << setw(10) << right << L"Ім'я" << setw(35) << L"Ім'я одного з батьків" << setw(17) << L"Номер телефону" << L"" << endl;
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

			vector<shared_ptr<Kid>> GroupKids; // список дети определенной группы

			int group_id = 0;

			wcout << endl;
			wcout << L"*** Дії меню ***" << endl;
			wcout << endl;

			wcout << L"1. Переглянути групу." << endl;
			wcout << L"2. Редагувати назву групи." << endl;
			wcout << L"3. Створити групу." << endl;
			wcout << L"4. Видалити групу." << endl;
			wcout << endl;
			wcout << L"0. Повернутись до меню." << endl;

			//блок вибора меню
			int choise = 0;
			char ch = 0;

			ch = _getch();
			choise = ch - '0';

			while (choise > 4 || choise < 0)
			{
				wcout << L"Пункта меню за таким номером не існує!\n Спробуйте ще раз!" << endl;
				ch = _getch();
				choise = ch - '0';
			}

			int temp = 0;// вспомогательная переменная для функций
			switch (choise)
			{
			case 0:
				system("cls");
				return;
				break;
			case 1://просмотр группы // добавить фукцию редактирования состава группы
				wcout << endl;
				wcout << L"Введить номер групи зі списка вище та натисніть Enter" << endl;

				cin >> choise;

				while (choise > all_Groups.size() || choise < 1)
				{
					wcout << L"Невірний номер групи, спробуйте ще раз!" << endl;
					cin >> choise;
				}

				for (size_t i = 0; i < all_Groups.size(); ++i)
				{
					group_id = all_Groups[choise - 1]->getDbID();
					break;
				}

				groups_inside(all_Groups, group_id);
				break;
			case 2: //редактирование названия
				wcout << endl;
				wcout << L"Зміна назви групи!" << endl;
				wcout << endl;

				wcout << L"Введить номер групи зі списка вище та натисніть Enter" << endl;

				cin >> choise;

				while (choise > all_Groups.size() || choise < 1)
				{
					wcout << L"Невірний номер групи, спробуйте ще раз!" << endl;
					ch = _getch();
					choise = ch - '0';
				}
				cin.ignore();
				groups_rename(choise);
				this_thread::sleep_for(std::chrono::seconds(1));
				break;
			case 3: // создание новой группы
				wcout << endl;
				wcout << L"Створення нової групи!" << endl;
				wcout << endl;

				groups_create();
				this_thread::sleep_for(std::chrono::seconds(1));
				break;
			case 4: // удаление группы
				wcout << endl;
				wcout << L"Введить номер групи зі списка вище яку ви бажаете видалити та натисніть Enter" << endl;

				cin >> choise;

				while (choise > all_Groups.size() || choise < 1)
				{
					wcout << L"Невірний номер групи, спробуйте ще раз!" << endl;
					ch = _getch();
					choise = ch - '0';
				}
				wcout << L"Ви впевнені що бажаєте видалити групу: ";
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

		const int dayLimit = 1;//максимальное количество занятий в день
		const int weekLimit = 2;//максимальное количество занятий в неделю

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
				wcout << L"У групи '" << gName << L"' перевищений ліміт занять на день !" << endl;
				wcout << L"Будь ласка оптимізуйте ваш графік!" << endl;
				wcout << endl;
				wcout << endl;
				this_thread::sleep_for(std::chrono::seconds(2));
				return;
			}
			if (weekCount > weekLimit)
			{
				wcout << endl;
				wcout << endl;
				wcout << L"У групи '" << gName << L"' перевищений ліміт занять на тиждень !" << endl;
				wcout << L"Будь ласка оптимізуйте ваш графік!" << endl;
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
			output_road = L"Перша доріжка";
			break;
		case 2:
			road_name = "Road2";
			output_road = L"Друга доріжка";
			break;
		case 3:
			road_name = "Road3";
			output_road = L"Третя доріжка";
			break;
		default:
			break;
		}

		switch (dayOFweek)
		{
		case 1://monday
			dayGroup = "monday_group";
			dayTrainer = "monday_trainer";
			output = L"Понеділок";
			break;
		case 2://tuesday
			dayGroup = "tuesday_group";
			dayTrainer = "tuesday_trainer";
			output = L"Вівторок";
			break;
		case 3://wednesday
			dayGroup = "wednesday_group";
			dayTrainer = "wednesday_trainer";
			output = L"Середа";
			break;
		case 4://thursday
			dayGroup = "thursday_group";
			dayTrainer = "thursday_trainer";
			output = L"Четверг";
			break;
		case 5://friday
			dayGroup = "friday_group";
			dayTrainer = "friday_trainer";
			output = L"П'ятниця";
			break;
		default:
			break;
		}

		//запрос на данные
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

			//получаемые данные из базы данных
			const char* lesson_hours = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));

			//блок поиска названия групп по их ид
			int group_id = sqlite3_column_int(statement, 1);
			int trainer_id = sqlite3_column_int(statement, 2);
		}
		sqlite3_finalize(statement);
		return count;
	}

	int groups_grafFinder(int road, int dayOFweek, int group_id)//поиск занятия по данной группе
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
			output_road = L"Перша доріжка";
			break;
		case 2:
			road_name = "Road2";
			output_road = L"Друга доріжка";
			break;
		case 3:
			road_name = "Road3";
			output_road = L"Третя доріжка";
			break;
		default:
			break;
		}

		switch (dayOFweek)
		{
		case 1://monday
			dayGroup = "monday_group";
			dayTrainer = "monday_trainer";
			output = L"Понеділок";
			break;
		case 2://tuesday
			dayGroup = "tuesday_group";
			dayTrainer = "tuesday_trainer";
			output = L"Вівторок";
			break;
		case 3://wednesday
			dayGroup = "wednesday_group";
			dayTrainer = "wednesday_trainer";
			output = L"Середа";
			break;
		case 4://thursday
			dayGroup = "thursday_group";
			dayTrainer = "thursday_trainer";
			output = L"Четверг";
			break;
		case 5://friday
			dayGroup = "friday_group";
			dayTrainer = "friday_trainer";
			output = L"П'ятниця";
			break;
		default:
			break;
		}

		//запрос на данные
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

				wcout << setw(14) << right << L"Години занять" << setw(15) << L"Група" << setw(25) << L"Тренер" << endl;
			}
			//получаемые данные из базы данных
			const char* lesson_hours = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));

			//блок поиска названия групп по их ид
			int group_id = sqlite3_column_int(statement, 1);
			if (group_id != NULL) // вывод названия групп по их ид
			{
				//поиск в веторе названия групп через лямду функцию
				auto it = std::find_if(groups.begin(), groups.end(),
					[group_id](const std::shared_ptr<Group>& group) { return group->getDbID() == group_id; });
				if (it != groups.end())
				{
					// как объект найден достаем имя и присваеваем переменной
					group_name = wconvert((*it)->getName());
				}
			}
			else if (group_id == NULL) group_name = L"    --"; // в противном случае ставим пропуски

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

	void groups_inside(vector<shared_ptr<Group>> all_Groups, int gp_id) // редактирования внутри группы
	{
		do
		{
			vector<shared_ptr<Kid>> GroupKids = groups_getSelected(gp_id);
			vector<shared_ptr<Kid>> all_Kids = groups_getAllKids();

			cout << setfill('-') << setw(63) << "" << endl;
			wcout << setw(40) << L"Вибрана група!" << endl;

			for (size_t i = 0; i < all_Groups.size(); ++i) //вывод всех детей по группно
			{
				if (all_Groups[i]->getDbID() == gp_id)
				{
					cout << setfill('-') << setw(63) << "" << endl;
					cout << setfill(' ') << setw(27) << right << i + 1 << ". " << all_Groups[i]->getName() << ": " << endl;
					cout << endl;
					wcout << setw(10) << right << L"Ім'я" << setw(35) << L"Ім'я одного з батьків" << setw(17) << L"Номер телефону" << L"" << endl;
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
			wcout << L"*** Дії меню ***" << endl;
			wcout << endl;

			wcout << L"1. Добавити учня у групу." << endl;
			wcout << L"2. Видалити учня з групи." << endl;
			wcout << L"3. Шукати заняття у графіку" << endl;
			wcout << endl;
			wcout << L"0. Повернутись до меню." << endl;
			int choise = 0;
			char ch = 0;

			ch = _getch();
			choise = ch - '0';

			while (choise > 3 || choise < 0)
			{
				wcout << L"Пункта меню за таким номером не існує!\n Спробуйте ще раз!" << endl;
				ch = _getch();
				choise = ch - '0';
			}

			int temp = 0; // вспомогательная переменная для функций
			int emptyGraf = 0; //вспомогательная переменная для поиска графика
			bool fullCheck = false;
			switch (choise)
			{
			case 0:
				system("cls");
				return;
				break;
			case 1:// добавиь ученика 
				fullCheck = groups_full(gp_id);
				if (fullCheck == true)
				{
					wcout << endl;
					wcout << L"*** Група має максимальну кількість учнів! ***" << endl;
					wcout << endl;
					this_thread::sleep_for(std::chrono::seconds(1));
					break;
				}
				wcout << endl;
				wcout << L"Виберіть звідки бажаєте добавити учня:" << endl;
				wcout << endl;

				wcout << L"0. Учні без группи" << endl;
				//далее вывод названия групп откуда взять ученика

				wcout << endl;
				wcout << L"Інші групи" << endl;

				for (size_t i = 0; i < all_Groups.size(); ++i) //вывод всех групп
				{
					cout << i + 1 << ". " << all_Groups[i]->getName() << endl;
				}

				wcout << endl;
				wcout << L"Введіть номер группи звідки хочете взяти учня та натисніть ENTER " << endl;
				wcout << endl;
				cin >> choise;

				while (choise > (all_Groups.size() + 1) || choise < 0)
				{
					wcout << L"Групи за таким номером не існує!\n Спробуйте ще раз!" << endl;
					cin >> choise;
				}

				if (choise == 0) //вывод\выбор для учеников без групп
				{
					cout << setfill('-') << setw(63) << "" << endl;
					wcout << setfill(L' ') << setw(55) << right << L"Учні що не знаходяться в жодній группі:" << endl;
					cout << endl;
					wcout << setw(10) << right << L"Ім'я" << setw(35) << L"Ім'я одного з батьків" << setw(17) << L"Номер телефону" << L"" << endl;

					for (size_t j = 0; j < all_Kids.size(); ++j)
					{
						if (all_Kids[j]->getGroupID() == NULL)
						{
							++temp;// для подсчета количество учников без группы
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
					wcout << L"Введить номер учня якого бажаете додати до цієї групи та натисніть Enter" << endl;

					cin >> choise;
					int kid_id = 0;
					while (choise > temp || choise < 1)  //выбор ученика по счетчику temp  
					{
						wcout << L"Невірний номер учня, спробуйте ще раз!" << endl;
						cin >> choise;
					}

					temp = 0; //обнуляем счетчик для повторного цикла с поиском совпадения
					for (size_t j = 0; j < all_Kids.size(); ++j) // повторный цикл для поиска совпадения счетчика и выбора пользователя
					{
						if (all_Kids[j]->getGroupID() == NULL)
						{
							++temp;
							if (temp == choise)
							{
								kid_id = all_Kids[j]->getDbID();// получаем ид для базы данных нужного нам ученика
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
					for (size_t i = 0; i < all_Groups.size(); ++i) //функция для получения ид для базы данных
					{
						group_id = all_Groups[choise - 1]->getDbID();
						break;
					}

					cout << endl;
					wcout << setw(10) << right << L"Ім'я" << setw(35) << L"Ім'я одного з батьків" << setw(17) << L"Номер телефону" << L"" << endl;

					for (size_t j = 0; j < all_Kids.size(); ++j)
					{
						if (all_Kids[j]->getGroupID() == group_id)
						{
							++temp;// для подсчета количество учников без группы
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
					wcout << L"Введить номер учня якого бажаете додати до цієї групи та натисніть Enter" << endl;

					cin >> choise;
					int kid_id = 0;
					while (choise > temp || choise < 1)  //выбор ученика по счетчику temp  
					{
						wcout << L"Невірний номер учня, спробуйте ще раз!" << endl;
						cin >> choise;
					}

					temp = 0; //обнуляем счетчик для повторного цикла с поиском совпадения
					for (size_t j = 0; j < all_Kids.size(); ++j) // повторный цикл для поиска совпадения счетчика и выбора пользователя
					{
						if (all_Kids[j]->getGroupID() == NULL)
						{
							++temp;
							if (temp == choise)
							{
								kid_id = all_Kids[j]->getDbID();// получаем ид для базы данных нужного нам ученика
								break;
							}
						}
					}
					groups_insert(gp_id, kid_id);
					this_thread::sleep_for(std::chrono::seconds(1));
					break;

				}
				break;
			case 2: // удалить ученика из группы
				wcout << endl;
				wcout << L"Введить номер учня якого бажєте видалити з цієї та натисніть Enter" << endl;

				cin >> choise;

				while (choise > all_Groups.size() || choise < 1)
				{
					wcout << L"Невірний номер учня, спробуйте ще раз!" << endl;
					ch = _getch();
					choise = ch - '0';
				}
				wcout << L"Ви впевнені що бажаєте видалити учня: ";
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
			case 3: // поиск данной группы в графике
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
					wcout << L"*** З данною групою занять не знайдено! ***" << endl;
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

		// Подготавливаем запрос
		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK) {
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		// Привязываем параметр
		sqlite3_bind_int(statement, 1, gp_id);
		sqlite3_bind_int(statement, 2, kd_id);

		// Выполняем шаги подготовленного запроса
		result = sqlite3_step(statement);

		if (result != SQLITE_DONE)
		{
			cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
		}
		else
		{
			wcout << endl;
			wcout << L"Учня успішно додано до групи!" << endl;
			wcout << endl;
		}

		sqlite3_finalize(statement);
	}

	void groups_erase(int db_id) // удаление ученика из группы (NULL ид группы)
	{
		string query = "UPDATE kids SET group_id = NULL WHERE kid_id = ?";
		sqlite3_stmt* statement;

		// Подготавливаем запрос
		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK) {
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		// Привязываем параметр
		sqlite3_bind_int(statement, 1, db_id);

		// Выполняем шаги подготовленного запроса
		result = sqlite3_step(statement);

		if (result != SQLITE_DONE)
		{
			cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
		}
		else
		{
			wcout << endl;
			wcout << L"Учня успішно видалено з групи!" << endl;
			wcout << endl;
		}

		sqlite3_finalize(statement);
	}

	vector<shared_ptr<Kid>> groups_getSelected(int db_groupid) // получаем детей по выбранной группе
	{
		vector<shared_ptr<Kid>> GroupKids; //контейнер для всей группи 

		//запрос на данные
		const char* query = "SELECT kid_id, name, parent_name, phone_number, group_id FROM Kids WHERE group_id = ?";
		sqlite3_stmt* statement;

		int result = sqlite3_prepare_v2(db, query, -1, &statement, nullptr);
		if (result != SQLITE_OK)
		{
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return {};
		}

		//привязываем входящее число как прараметр по поиску в базе данных
		sqlite3_bind_int(statement, 1, db_groupid);

		// сделать создание классов людей и поместить их всех в вектор
		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			//получаемые данные из базы данных
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
		wcout << L"Введіть нову назву для групи" << endl;
		wcout << endl;

		setlocale(LC_ALL, "");
		wstring utf16Data;
		getline(wcin, utf16Data);

		// конвертация в UTF-8
		wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		string utf8Text = converter.to_bytes(utf16Data);

		string query = "UPDATE Groups SET group_name = '" + utf8Text + "' WHERE group_id = ?";
		sqlite3_stmt* statement;

		// Подготавливаем запрос
		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK) {
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		// Привязываем параметры
		sqlite3_bind_int(statement, 1, db_id);

		// Выполняем шаги подготовленного запроса
		result = sqlite3_step(statement);

		//возращаем кодировку
		setlocale(LC_ALL, "en_US.UTF-8");

		if (result != SQLITE_DONE)
		{
			cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
		}
		else
		{
			wcout << endl;
			wcout << L"Назва групи успішно оновлена" << endl;
			wcout << endl;
		}

		sqlite3_finalize(statement);
	}

	void groups_create()
	{
		wcout << endl;
		wcout << L"Введіть назву для нової групи" << endl;
		wcout << endl;

		setlocale(LC_ALL, "");
		wstring utf16Data;
		if (wcin.peek() == '\n') {
			// Если есть, считываем его
			wcin.ignore();
		}
		getline(wcin, utf16Data);

		// конвертация в UTF-8
		wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		string utf8Text = converter.to_bytes(utf16Data);

		string query = "INSERT INTO Groups (group_name) VALUES ('" + utf8Text + "')";
		sqlite3_stmt* statement;

		// Подготавливаем запрос
		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK) {
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		// Выполняем шаги подготовленного запроса
		result = sqlite3_step(statement);

		//возращаем кодировку
		setlocale(LC_ALL, "en_US.UTF-8");

		if (result != SQLITE_DONE)
		{
			cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
		}
		else
		{
			wcout << endl;
			wcout << L"Нова группа успішно створена" << endl;
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

			// Подготавливаем запрос
			int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
			if (result != SQLITE_OK) {
				cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
				return;
			}

			// Привязываем параметр
			sqlite3_bind_int(statement, 1, db_id);

			// Выполняем шаги подготовленного запроса
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

		// Подготавливаем запрос
		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK) {
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		// Привязываем параметры
		sqlite3_bind_int(statement, 1, db_id);

		// Выполняем шаги подготовленного запроса
		result = sqlite3_step(statement);

		if (result != SQLITE_DONE)
		{
			cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
		}
		else
		{
			wcout << endl;
			wcout << L"Група успішно видалена" << endl;
			wcout << endl;
		}

		sqlite3_finalize(statement);
	}

	vector<shared_ptr<Kid>> groups_getAllKids()
	{
		vector<shared_ptr<Group>> allGroups = groups_getAll();
		vector<shared_ptr<Kid>> allKids; //контейнер для всей группи 

		//запрос на данные
		const char* query = "SELECT kid_id, name, parent_name, phone_number, group_id FROM Kids";
		sqlite3_stmt* statement;

		int result = sqlite3_prepare_v2(db, query, -1, &statement, nullptr);
		if (result != SQLITE_OK)
		{
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return {};
		}

		// сделать создание классов людей и поместить их всех в вектор
		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			//получаемые данные из базы данных
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


	vector<shared_ptr<Group>> groups_getAll() // получает контейнер с группами (без списка детей)
	{
		vector<shared_ptr<Group>> all_Groups; //контейнер для всей группи 
		all_Groups.reserve(6);

		//запрос на данные
		const char* query = "SELECT group_id, group_name FROM Groups";
		sqlite3_stmt* statement;

		int result = sqlite3_prepare_v2(db, query, -1, &statement, nullptr);
		if (result != SQLITE_OK)
		{
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return {};
		}

		// сделать создание классов людей и поместить их всех в вектор
		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			//получаемые данные из базы данных
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

			wcout << setw(19) << right << L"Ім'я тренера" << setw(23) << L"Номер телефону" << L"" << endl;
			wcout << endl;
			string numeration;
			for (size_t i = 0; i < all_trainers.size(); ++i) //вывод для проверки
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
			wcout << L"1. Редагувати інформацію про тренера" << endl;
			wcout << L"2. Створити нового тренера" << endl;
			wcout << L"3. Видалити тренера" << endl;
			wcout << L"4. Пошук занять із вибраним тренером" << endl;
			wcout << endl;
			wcout << L"0. Повернутись до меню" << endl;

			int choise = 0;
			char ch = 0;

			ch = _getch();
			choise = ch - '0';

			while (choise > 4 || choise < 0)
			{
				wcout << L"Пункта меню за таким номером не існує!\n Спробуйте ще раз!" << endl;
				ch = _getch();
				choise = ch - '0';
			}

			int temp = 0;// вспомогательная переменная для функций
			int emptyGraf = 0;// вспомогательная переменная для поиска в графике
			switch (choise)
			{
			case 0:
				system("cls");
				return;
				break;
			case 1: // редактировать инфо 
				wcout << endl;
				wcout << L"Введить номер тренера зі списка вище інформацю якого ви бажаєте редагувати та натисніть Enter" << endl;

				cin >> choise;

				while (choise > all_trainers.size() || choise < 1)
				{
					wcout << L"Невірний номер тренера, спробуйте ще раз!" << endl;
					cin >> choise;
				}
				wcout << L"Ви впевнені що бажаєте редагувати тренера: ";
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
			case 2: // создать нового
				wcout << endl;
				wcout << L"Ви впевнені що бажаєте створити нового тренера?" << endl;
				if (exit() == true)
				{
					trainer_create();
					this_thread::sleep_for(std::chrono::seconds(1));
					break;
				}
				break;
			case 3: // удалить 
				wcout << endl;
				wcout << L"Введить номер тренера зі списка вище якого ви бажаете видалити та натисніть Enter" << endl;

				cin >> choise;

				while (choise > all_trainers.size() || choise < 1)
				{
					wcout << L"Невірний номер тренера, спробуйте ще раз!" << endl;
					cin >> choise;
				}
				wcout << L"Ви впевнені що бажаєте видалити тренера: ";
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
				wcout << L"Введить номер тренера зі списка вище заняття якого бажаєте знайти" << endl;

				cin >> choise;

				while (choise > all_trainers.size() || choise < 1)
				{
					wcout << L"Невірний номер тренера, спробуйте ще раз!" << endl;
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
					wcout << L"*** З данним тренером занять не знайдено! ***" << endl;
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
					wcout << L"У тренера '" << tName << L"' в один час проходить 2 заняття !\n Будь ласка перевірте ваш графік!";
					wcout << endl;
					wcout << endl;
					this_thread::sleep_for(std::chrono::seconds(2));
					return;
				}
				else if (r1_lesson == r3_lesson && (r1_lesson > 0 || r3_lesson > 0))
				{
					wcout << endl;
					wcout << endl;
					wcout << L"У тренера '" << tName << L"' в один час проходить 2 заняття !\n Будь ласка перевірте ваш графік!";
					wcout << endl;
					wcout << endl;
					this_thread::sleep_for(std::chrono::seconds(2));
					return;
				}
				else if (r2_lesson == r3_lesson && (r2_lesson > 0 || r3_lesson > 0))
				{
					wcout << endl;
					wcout << endl;
					wcout << L"У тренера '" << tName << L"' в один час проходить 2 заняття !\n Будь ласка перевірте ваш графік!";
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

		const int dayLimit = 3;//максимальное количество занятий в день
		const int weekLimit = 9;//максимальное количество занятий в неделю

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
				wcout << L"У тренера '" << tName << L"' перевищений ліміт занять на день !" << endl;
				wcout << L"Будь ласка оптимізуйте ваш графік!" << endl;
				wcout << endl;
				wcout << endl;
				this_thread::sleep_for(std::chrono::seconds(2));
				return;
			}
			if (weekCount > weekLimit)
			{
				wcout << endl;
				wcout << endl;
				wcout << L"У тренера '" << tName << L"'  перевищений ліміт занять на тиждень !" << endl;
				wcout << L"Будь ласка оптимізуйте ваш графік!" << endl;
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
			output_road = L"Перша доріжка";
			break;
		case 2:
			road_name = "Road2";
			output_road = L"Друга доріжка";
			break;
		case 3:
			road_name = "Road3";
			output_road = L"Третя доріжка";
			break;
		default:
			break;
		}

		switch (dayOFweek)
		{
		case 1://monday
			dayGroup = "monday_group";
			dayTrainer = "monday_trainer";
			output = L"Понеділок";
			break;
		case 2://tuesday
			dayGroup = "tuesday_group";
			dayTrainer = "tuesday_trainer";
			output = L"Вівторок";
			break;
		case 3://wednesday
			dayGroup = "wednesday_group";
			dayTrainer = "wednesday_trainer";
			output = L"Середа";
			break;
		case 4://thursday
			dayGroup = "thursday_group";
			dayTrainer = "thursday_trainer";
			output = L"Четверг";
			break;
		case 5://friday
			dayGroup = "friday_group";
			dayTrainer = "friday_trainer";
			output = L"П'ятниця";
			break;
		default:
			break;
		}

		//запрос на данные
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
			//получаемые данные из базы данных
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
			output_road = L"Перша доріжка";
			break;
		case 2:
			road_name = "Road2";
			output_road = L"Друга доріжка";
			break;
		case 3:
			road_name = "Road3";
			output_road = L"Третя доріжка";
			break;
		default:
			break;
		}

		switch (dayOFweek)
		{
		case 1://monday
			dayGroup = "monday_group";
			dayTrainer = "monday_trainer";
			output = L"Понеділок";
			break;
		case 2://tuesday
			dayGroup = "tuesday_group";
			dayTrainer = "tuesday_trainer";
			output = L"Вівторок";
			break;
		case 3://wednesday
			dayGroup = "wednesday_group";
			dayTrainer = "wednesday_trainer";
			output = L"Середа";
			break;
		case 4://thursday
			dayGroup = "thursday_group";
			dayTrainer = "thursday_trainer";
			output = L"Четверг";
			break;
		case 5://friday
			dayGroup = "friday_group";
			dayTrainer = "friday_trainer";
			output = L"П'ятниця";
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

		//запрос на данные
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
			//получаемые данные из базы данных
			int group_id = sqlite3_column_int(statement, 1);
			int trainer_id = sqlite3_column_int(statement, 2);
		}
		sqlite3_finalize(statement);
		if (count > 0) return 1;
		else return 0;
	}

	int trainer_grafFinder(int road, int dayOFweek, int trainer_id)//поиск занятия по данному тренеру
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
			output_road = L"Перша доріжка";
			break;
		case 2:
			road_name = "Road2";
			output_road = L"Друга доріжка";
			break;
		case 3:
			road_name = "Road3";
			output_road = L"Третя доріжка";
			break;
		default:
			break;
		}

		switch (dayOFweek)
		{
		case 1://monday
			dayGroup = "monday_group";
			dayTrainer = "monday_trainer";
			output = L"Понеділок";
			break;
		case 2://tuesday
			dayGroup = "tuesday_group";
			dayTrainer = "tuesday_trainer";
			output = L"Вівторок";
			break;
		case 3://wednesday
			dayGroup = "wednesday_group";
			dayTrainer = "wednesday_trainer";
			output = L"Середа";
			break;
		case 4://thursday
			dayGroup = "thursday_group";
			dayTrainer = "thursday_trainer";
			output = L"Четверг";
			break;
		case 5://friday
			dayGroup = "friday_group";
			dayTrainer = "friday_trainer";
			output = L"П'ятниця";
			break;
		default:
			break;
		}

		//запрос на данные
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

				wcout << setw(14) << right << L"Години занять" << setw(15) << L"Група" << setw(25) << L"Тренер" << endl;
			}
			//получаемые данные из базы данных
			const char* lesson_hours = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));

			//блок поиска названия групп по их ид
			int group_id = sqlite3_column_int(statement, 1);
			if (group_id != NULL) // вывод названия групп по их ид
			{
				//поиск в веторе названия групп через лямду функцию
				auto it = std::find_if(groups.begin(), groups.end(),
					[group_id](const std::shared_ptr<Group>& group) { return group->getDbID() == group_id; });
				if (it != groups.end())
				{
					// как объект найден достаем имя и присваеваем переменной
					group_name = wconvert((*it)->getName());
				}
			}
			else if (group_id == NULL) group_name = L"    --"; // в противном случае ставим пропуски

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
		wcout << L"Введіть ім'я нового тренера" << endl;
		wcout << endl;
		getline(wcin, utf16Name);
		wcout << endl;
		wcout << L"Введіть телефонний номер нового тренера" << endl;
		wcout << endl;
		getline(wcin, utf16Phone);
		wcout << endl;
		wcout << L"Введіть почасову заробітну плату нового тренера" << endl;
		wcout << endl;
		getline(wcin, utf16Pay);

		// конвертация в UTF-8
		wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		string utf8Name = converter.to_bytes(utf16Name);
		string utf8Phone = converter.to_bytes(utf16Phone);
		string utf8Pay = converter.to_bytes(utf16Pay);

		string query = "INSERT INTO Trainers (name, phone_number, pay_hour) VALUES ('" + utf8Name + "', '" + utf8Phone + "', " + utf8Pay + ")";
		sqlite3_stmt* statement;

		// Подготавливаем запрос
		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK) {
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		// Выполняем шаги подготовленного запроса
		result = sqlite3_step(statement);

		//возращаем кодировку
		setlocale(LC_ALL, "en_US.UTF-8");

		if (result != SQLITE_DONE)
		{
			cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
		}
		else
		{
			wcout << endl;
			wcout << L"Новий тренер успішно створений" << endl;
			wcout << endl;
		}

		sqlite3_finalize(statement);
	}

	void trainer_edit(int db_id)
	{
		wcout << endl;
		wcout << L"Виберіть що саме ви хочете редагувати:" << endl;
		wcout << endl;

		wcout << L"1. Ім'я" << endl;
		wcout << L"2. Телефон" << endl;
		wcout << L"3. Почасову заробітну плату" << endl;

		int choise = 0;
		char ch = 0;

		ch = _getch();
		choise = ch - '0';

		while (choise > 3 || choise < 1)
		{
			wcout << L"Пункта меню за таким номером не існує!\n Спробуйте ще раз!" << endl;
			ch = _getch();
			choise = ch - '0';
		}

		//объявление параметров для запроса
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
		case 1://имя
			wcout << L"Ім'я" << endl;
			setParametr = "name";

			setlocale(LC_ALL, "");

			getline(wcin, utf16Data);
			utf8Text = converter.to_bytes(utf16Data);

			query = "UPDATE Trainers SET " + setParametr + " = '" + utf8Text + "' WHERE trainer_id = ?";

			outcome = L"Ім'я тренера успішно змінено!";
			break;
		case 2://телефон
			wcout << L"Телефон" << endl;
			setParametr = "phone_number";

			setlocale(LC_ALL, "");

			getline(wcin, utf16Data);
			utf8Text = converter.to_bytes(utf16Data);

			query = "UPDATE Trainers SET " + setParametr + " = '" + utf8Text + "' WHERE trainer_id = ?";

			outcome = L"Номер телефону тренера успішно змінено!";
			break;
		case 3://зарплата
			wcout << L"Почасову заробітну плату" << endl;
			setParametr = "pay_hour";

			setlocale(LC_ALL, "");

			getline(wcin, utf16Data);
			utf8Text = converter.to_bytes(utf16Data);

			query = "UPDATE Trainers SET " + setParametr + " = '" + utf8Text + "' WHERE trainer_id = ?";

			outcome = L"Заробітню плату тренера успішно змінено!";
			break;
		default:
			break;
		}

		// Подготавливаем запрос
		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK) {
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		// Привязываем параметры
		sqlite3_bind_int(statement, 1, db_id);

		// Выполняем шаги подготовленного запроса
		result = sqlite3_step(statement);

		//возращаем кодировку
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

				// Подготавливаем запрос
				int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
				if (result != SQLITE_OK) {
					cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
					return;
				}

				// Привязываем параметр
				sqlite3_bind_int(statement, 1, db_id);

				// Выполняем шаги подготовленного запроса
				result = sqlite3_step(statement);

				if (result != SQLITE_DONE)
				{
					cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
				}
				else {}

				sqlite3_finalize(statement);

			}
		}

		//основная часть удаления

		string query = "DELETE FROM Trainers WHERE trainer_id = ?";
		sqlite3_stmt* statement;

		// Подготавливаем запрос
		int result = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
		if (result != SQLITE_OK) {
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return;
		}

		// Привязываем параметры
		sqlite3_bind_int(statement, 1, db_id);

		// Выполняем шаги подготовленного запроса
		result = sqlite3_step(statement);

		if (result != SQLITE_DONE)
		{
			cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
		}
		else
		{
			wcout << endl;
			wcout << L"Інформація про тренера успішно видалена!" << endl;
			wcout << endl;
		}

		sqlite3_finalize(statement);
	}

	shared_ptr<Trainer> trainer_getSelected(int db_id)
	{
		shared_ptr<Trainer> trainer1;

		//запрос на данные
		const char* query = "SELECT trainer_id, name, phone_number, pay_hour FROM Trainers WHERE trainer_id = ?";
		sqlite3_stmt* statement;

		int result = sqlite3_prepare_v2(db, query, -1, &statement, nullptr);
		if (result != SQLITE_OK)
		{
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return {};
		}

		// Привязываем параметр
		sqlite3_bind_int(statement, 1, db_id);

		int count = 0;
		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			//получаемые данные из базы данных
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
		vector<shared_ptr<Trainer>> all_Trainers; //контейнер для всей группи 
		all_Trainers.reserve(6);

		//запрос на данные
		const char* query = "SELECT trainer_id, name, phone_number, pay_hour FROM Trainers";
		sqlite3_stmt* statement;

		int result = sqlite3_prepare_v2(db, query, -1, &statement, nullptr);
		if (result != SQLITE_OK)
		{
			cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
			return {};
		}

		// сделать создание классов людей и поместить их всех в вектор
		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			//получаемые данные из базы данных
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

	bool exit()//вспомогательная для выхода
	{

		wcout << L"Для підтведження натисніть клавішу - Y" << endl;
		wcout << L"Для відміни натисніть клавішу - N" << endl;
		while (true)
		{
			char oa = _getch();
			if (oa == 'y' || oa == 'Y' || oa == 'н' || oa == 'Н')
				return true;
			else if (oa == 'n' || oa == 'N' || oa == 'т' || oa == 'Т')
				return false;
		}
	}
	wstring wconvert(string get) // конвертер из обычной строки в короткую
	{
		wstring_convert<codecvt_utf8<wchar_t>> converter;
		wstring wideString = converter.from_bytes(get);
		return wideString;
	}
};