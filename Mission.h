#pragma once

int getCurrentMission(int x)
{
	if ((x > 0) && (x < 400))
		return 0;
	if ((x > 400) && (x < 700))
		return 1;
	if ((x > 700) && (x < 2200))
		return 2;
	if (x > 2200)
		return 3;
	return 0;
}

std::string getTextMission(int currentMission)
{
	std::string missionText("");
	switch (currentMission)
	{
	case 0:
		missionText = "\nНачальный этап и \nинструкции к игре";
		break;
	case 1:
		missionText = "\nMission 1\n\nВот твоя первая\n миссия, на \n этом уровне \n тебе стоит опасатся \n бла... бла... бла";
		break;
	case 2:
		missionText = "\nMission 2\n Необходимо решить\n логическую задачку,\n чтобы пройти дальше";
		break;
	case 3:
		missionText = "\nИ так далее \nи тому подобное.....";
		break;
	}
	return missionText;
}