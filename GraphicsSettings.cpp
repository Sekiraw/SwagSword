#include "precom.h"
#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings()
{
	this->title = "DEFAULT";
	this->resolution = sf::VideoMode::getDesktopMode();
	this->fullscreen = false;
	this->vSync = false;
	this->frameRateLimit = 120;
	this->contextSettings.antialiasingLevel = 0;
	this->videoModes = sf::VideoMode::getFullscreenModes();
}

void GraphicsSettings::saveToFile(const std::string path)
{
	std::ofstream ofs(path);

	this->videoModes = sf::VideoMode::getFullscreenModes();

	if (ofs.is_open()) {
		ofs << this->resolution.width << " " << this->resolution.height;
		ofs << this->fullscreen;
		ofs << this->frameRateLimit;
		ofs << this->vSync;
		ofs << this->contextSettings.antialiasingLevel;
	}
	ofs.close();
}
void GraphicsSettings::loadFromFile(const std::string path)
{
	std::ifstream ifs(path);

	this->videoModes = sf::VideoMode::getFullscreenModes();

	if (ifs.is_open()) {
		std::getline(ifs, this->title);
		ifs >> this->resolution.width >> this->resolution.height;
		ifs >> this->fullscreen;
		ifs >> this->frameRateLimit;
		ifs >> this->vSync;
		ifs >> this->contextSettings.antialiasingLevel;
	}
	ifs.close();
}