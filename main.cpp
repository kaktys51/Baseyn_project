#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "sqlite3.h"
#include <iomanip>

#include <locale>
#include <codecvt>

#include <conio.h>
#include <windows.h>
#include <thread>
#include <chrono>

using namespace std;

#include "Kid.h"
#include "Trainer.h"
#include "Group.h"
#include "Road.h"
#include "Manager.h"

int main()
{
    system("chcp 1251>nul");

	setlocale(LC_ALL, "en_US.UTF-8");
	Manager on;

	on.mainMenu();

	return 0;
}

