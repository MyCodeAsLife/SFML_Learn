#pragma once

int getCurrentMission(int x)
{
	int mission(0);
	if ((x > 0) && (x < 400))
		mission = 0;
	if (x > 400)
		mission = 1;
	if (x > 700)
		mission = 2;
	if (x > 2200)
		mission = 3;

	return mission;
}

std::string getTextMission(int currentMission)
{
	std::string missinText = "";
	switch (currentMission)
	{
	case 0:
		missinText = "\nНачальный этап и \nинструкции к игре";
		break;
	case 1:
		missinText = "\nMission 1\n\nВот твоя первая\n миссия, на\n этом уровне \nтебе стоит опасатся\n... бла-бла-бла ...";
		break;
	case 2:
		missinText = "\nMission 2\n Необходимо решить\n логическую задачку,\n чтобы пройти дальше ";
		break;
	case 3:
		missinText = "\nИ так далее \nи тому подобное.....";
		break;
	}

	return missinText;
}