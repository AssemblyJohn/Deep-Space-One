#include "Config.h"

#include "std.h"

#ifdef EN_DEBUG
	#define DEFAULT_DEBUG true
#else
	#define DEFAULT_DEBUG false
#endif

bool enConfig::debugAabb = DEFAULT_DEBUG;
bool enConfig::debugPhysics = DEFAULT_DEBUG;
bool enConfig::fullscreen = false;
bool enConfig::initialized = false;

int enConfig::windowWidth = 800;
int enConfig::windowHeight = 600;

void enConfig::Initialize()
{
	initialized = true;
	
	FILE *file = fopen("config.ini", "r");
	
	
#ifdef EN_DEBUG
	// assert(file);
	return;
#else
	return;
#endif
	
	char buff[100];
	char parseBuff[100];
	char *header;

	while (fgets(buff, 100, file))
	{
		strcpy(parseBuff, buff);
		header = strtok(buff, " ");

		if (strcmp(header, "RESOLUTION") == 0)
		{
			strtok(parseBuff, " ");
			windowWidth = atoi(strtok(NULL, " "));
			windowHeight = atoi(strtok(NULL, " "));
		}
		else if (strcmp(header, "FULLSCREEN") == 0)
		{
			strtok(parseBuff, " ");
			fullscreen = (bool)atoi(strtok(NULL, " "));
		}
		else if (strcmp(header, "AABBDEBUG") == 0)
		{
			strtok(parseBuff, " ");
			debugAabb = (bool)atoi(strtok(NULL, " "));
		}
		else if (strcmp(header, "PHYSICSDEBUG") == 0)
		{
			strtok(parseBuff, " ");
			debugPhysics = (bool)atoi(strtok(NULL, " "));
		}
	}

}

int enConfig::WindowWidth()
{
	EN_ASSERT(enConfig::initialized);
	return windowWidth;
}

int enConfig::WindowHeight()
{
	EN_ASSERT(enConfig::initialized);
	return windowHeight;
}

bool enConfig::Fullscreen()
{
	EN_ASSERT(enConfig::initialized);
	return fullscreen;
}

bool enConfig::DebugAABB()
{
	EN_ASSERT(enConfig::initialized);
	return debugAabb;
}

bool enConfig::DebugPhysics()
{
	EN_ASSERT(enConfig::initialized);
	return debugPhysics;
}