
-- создание таблицы групп

-- CREATE TABLE Groups (
--     group_id INTEGER PRIMARY KEY AUTOINCREMENT,
--     group_name TEXT NOT NULL
-- );


-- создание (базовых) групп

-- INSERT INTO Groups (group_name) VALUES ('Группа 1');
-- INSERT INTO Groups (group_name) VALUES ('Группа 2');
-- INSERT INTO Groups (group_name) VALUES ('Группа 3');
-- INSERT INTO Groups (group_name) VALUES ('Группа 4');
-- INSERT INTO Groups (group_name) VALUES ('Группа 5');

-- INSERT INTO Groups (group_name) VALUES ('Тестововая');

--вспомогаткельные команды 
-- DELETE FROM Groups WHERE group_id = 1;

-- UPDATE Groups
-- SET group_name = 'імя'
-- WHERE group_id = 5;

-- создание таблицы детей с зависимостью от групп

-- CREATE TABLE Kids (
--     kid_id INTEGER PRIMARY KEY AUTOINCREMENT,
--     name TEXT NOT NULL,
--     parent_name TEXT NOT NULL,
--     phone_number TEXT NOT NULL,
--     group_id INTEGER,
--     FOREIGN KEY (group_id) REFERENCES Groups(group_id) ON DELETE SET NULL
-- );

--удаление таблицы (на всякий случай)
--DROP TABLE Kids;

-- заполнение первых 2 базовых групп

-- INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Шинкаренко Іван', 'Олена Шинкаренко',  '+380988865206', 1);
-- INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Таращук Оксана', 'Таращук Тамара',  '+380507335855', 1);
-- INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Панасюк Марія', 'Панасюк Сергій',  '+380921084150', 1);
--  INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Петренко Анастасія', 'Петренко Дмитро',  '+380999549323', 1);
--  INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Броварчук Анатолій', 'Броварчук Валерій',  '+380636369185', 1);
--  INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Тарасович Дмитро', 'Тарасович Олександра',  '+380949376171', 1);
--  INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Крамаренко Володимир', 'Крамаренко Всеволод',  '+380919167028', 1);
--  INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Шевчук Юрій', 'Шевчук Станіслав',  '+380979199954', 1);
--  INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Василенко Раїса', 'Василенко Віра',  '+380983987966', 1);
--  INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Таращук Оксана', 'Таращук Сергій',  '+380664143216', 1);

-- INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Пономаренко Євгенія', 'Пономаренко Геннадій',  '+380671238484', 2);
-- INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Василенко Геннадій', 'Василенко Валентина',  '+380922926116', 2);
-- INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Павлюк Віктор', 'Павлюк Станіслав',  '+380666911045', 2);
-- INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Кравченко Інна', 'Кравченко Оксана',  '+380951256860', 2);
-- INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Петренко Володимир', 'Петренко Станіслав',  '+380678256147', 2);
-- INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Микитюк Кіра', 'Микитюк Наташа',  '+380961340427', 2);
-- INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Борисівна Єлизавета', 'Борисівна Ігор',  '+380966022707', 2);
-- INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Захарчук Віктор', 'Захарчук Василь',  '+380672897872', 2);

-- INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Захарчук Віктор', 'Захарчук Василь',  '+380672897872', 3);
-- INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Таращук Віра', 'Таращук Ольга',  '+380665460126', 3);
-- INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Гнатюк Марина', 'Гнатюк Євгенія',  '+380973785232', 3);
-- INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Петренко Ігор', 'Петренко Анастасія',  '+380952641042', 3);
-- INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Василенко Ніна', 'Василенко Федір',  '+380990444167', 3);
-- INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Лисенко Лев', 'Лисенко Юлія',  '+380929782761', 3);

-- INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Захарчук Микита', 'Захарчук Галина',  '+380675391100', 4);
-- INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Кравченко Валерій', 'Кравченко Софія',  '+380976340732', 4);
-- INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Сергієнко Софія', 'Сергієнко Анастасія',  '+380988370463', 4);
-- INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Романченко Катерина', 'Романченко Євгеній',  '+380990068069', 4);
-- INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Микитюк Віра', 'Микитюк Галина',  '+380957519222', 4);

-- INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Дмитренко Віра', 'Дмитренко Валентина',  '+380987422348', 5);
-- INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Броваренко Іван', 'Броваренко Борис',  '+380983201003', 5);
-- INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Таращук Тарас', 'Таращук Поліна',  '+380961117573', 5);


-- INSERT INTO Kids (name, parent_name, phone_number) VALUES ('Сергієнко Ярослава', 'Сергієнко Раїса ',  '+380974967590');
-- INSERT INTO Kids (name, parent_name, phone_number) VALUES ('Шевчук Григорій', 'Шевчук Валерій ',  '+380978377884');
-- INSERT INTO Kids (name, parent_name, phone_number) VALUES ('Броваренко Вікторія', 'Броваренко Валерій ',  '+380970355792');
-- INSERT INTO Kids (name, parent_name, phone_number) VALUES ('Захарчук Ніна', 'Захарчук Валерій ',  '+380984929964');
-- INSERT INTO Kids (name, parent_name, phone_number) VALUES ('Мірошниченко Вадим', 'Мірошниченко Валентина ',  '+380636873675');

--INSERT INTO Kids (name, parent_name, phone_number, group_id) VALUES ('Тестове дитя', 'Тестовий Батько ',  '+380978371284', 10);

-- UPDATE Kids
-- SET name = 'Some name'
-- WHERE kid_id = 14;

 --DELETE FROM Kids WHERE group_id = 10;

-- UPDATE kids
-- SET group_id = NULL
-- WHERE kid_id = 7;

-- создание таблицы тренеров без зависимостей

-- CREATE TABLE Trainers (
--     trainer_id INTEGER PRIMARY KEY AUTOINCREMENT,
--     name TEXT NOT NULL,
--     phone_number TEXT NOT NULL,
--     pay_hour INTEGER NOT NULL
-- );


--создание базовых тренеров 

-- INSERT INTO Trainers (name, phone_number, pay_hour) VALUES ('Мельниченко Геннадій', '+380919536932', 100);
-- INSERT INTO Trainers (name, phone_number, pay_hour) VALUES ('Пономарчук Валентина', '+380630517173', 100);
-- INSERT INTO Trainers (name, phone_number, pay_hour) VALUES ('Романченко Микита', '+380678578535', 100);
-- INSERT INTO Trainers (name, phone_number, pay_hour) VALUES ('Крамарчук Данил', '+380961485385', 100);
-- INSERT INTO Trainers (name, phone_number, pay_hour) VALUES ('Романівна Софія', '+380987628874', 100);
-- INSERT INTO Trainers (name, phone_number, pay_hour) VALUES ('Васильчук Микита', '+380663879444', 100);

-- INSERT INTO Trainers (name, phone_number, pay_hour) VALUES ('тестовый тренер1', '+380961485385', 100);
-- INSERT INTO Trainers (name, phone_number, pay_hour) VALUES ('тестовый тренер2', '+380961485385', 100);

-- UPDATE Trainers
-- SET name = 'Some name'
-- WHERE lesson_hours = '9-11', trainer_id = 10;

-- создание таблицы дорожки с графиком занятий по 2 часа по дням, с зависимостями от групп и тренера
-- создать 3 дорожки

-- CREATE TABLE Road3 (
--     lesson_hours TEXT NOT NULL,
--     monday_group INTEGER,
--     monday_trainer INTEGER,
--     tuesday_group INTEGER,
--     tuesday_trainer INTEGER,
--     wednesday_group INTEGER,
--     wednesday_trainer INTEGER,
--     thursday_group INTEGER,
--     thursday_trainer INTEGER,
--     friday_group INTEGER,
--     friday_trainer INTEGER,

--     FOREIGN KEY (monday_group) REFERENCES Groups(group_id) ON DELETE SET NULL,
--     FOREIGN KEY (tuesday_group) REFERENCES Groups(group_id) ON DELETE SET NULL,
--     FOREIGN KEY (wednesday_group) REFERENCES Groups(group_id) ON DELETE SET NULL,
--     FOREIGN KEY (thursday_group) REFERENCES Groups(group_id) ON DELETE SET NULL,
--     FOREIGN KEY (friday_group) REFERENCES Groups(group_id) ON DELETE SET NULL,

--     FOREIGN KEY (monday_trainer) REFERENCES Trainers(trainer_id) ON DELETE SET NULL,
--     FOREIGN KEY (tuesday_trainer) REFERENCES Trainers(trainer_id) ON DELETE SET NULL,
--     FOREIGN KEY (wednesday_trainer) REFERENCES Trainers(trainer_id) ON DELETE SET NULL,
--     FOREIGN KEY (thursday_trainer) REFERENCES Trainers(trainer_id) ON DELETE SET NULL,
--     FOREIGN KEY (friday_trainer) REFERENCES Trainers(trainer_id) ON DELETE SET NULL
-- );



--заполнение дорожки часами для занятий
--сделать для каждой дорожки 

-- INSERT INTO Road1 (lesson_hours) VALUES ('9-11');
-- INSERT INTO Road1 (lesson_hours) VALUES ('11-13');
-- INSERT INTO Road1 (lesson_hours) VALUES ('13-15');
-- INSERT INTO Road1 (lesson_hours) VALUES ('15-17');
-- INSERT INTO Road1 (lesson_hours) VALUES ('17-19');
-- INSERT INTO Road1 (lesson_hours) VALUES ('19-21');

--  INSERT INTO Road2 (lesson_hours) VALUES ('9-11');
--  INSERT INTO Road2 (lesson_hours) VALUES ('11-13');
--  INSERT INTO Road2 (lesson_hours) VALUES ('13-15');
--  INSERT INTO Road2 (lesson_hours) VALUES ('15-17');
--  INSERT INTO Road2 (lesson_hours) VALUES ('17-19');
--  INSERT INTO Road2 (lesson_hours) VALUES ('19-21');

--  INSERT INTO Road3 (lesson_hours) VALUES ('9-11');
--  INSERT INTO Road3 (lesson_hours) VALUES ('11-13');
--  INSERT INTO Road3 (lesson_hours) VALUES ('13-15');
--  INSERT INTO Road3 (lesson_hours) VALUES ('15-17');
--  INSERT INTO Road3 (lesson_hours) VALUES ('17-19');
--  INSERT INTO Road3 (lesson_hours) VALUES ('19-21');

--PRAGMA encoding;

-- UPDATE Road1
-- SET monday_trainer = 4
-- SET monday_group = 1
-- WHERE lesson_hours = '11-13';