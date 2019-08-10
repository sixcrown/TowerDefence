#include "Road.h"



Road::Road()
{
	this->InitMapOfTextures();
	this->GetMapFromFile();
	this->SearchForNexusPosition();
}


Road::~Road()
{
	for (auto it : this->MapOfTextures)
	{
		delete it.second;
	}
	for (auto it : this->VofTowers)
	{
		VofTowers.pop_back();
	}
	for (auto it : this->Voftiles)
	{
		Voftiles.pop_back();
	}
}

void Road::GetMapFromFile()
{
	std::fstream file;
	file.open("Config/map.ini");
	if (!file.is_open()) throw("ROAD::COULDNT LOAD MAP.INI");
	file >> this->sizeX;
	file >> this->sizeY;
	file >> this->x;
	file >> this->y;
	for (int j = 0; j < this->y; j++)
	{
		for (int i = 0; i < this->x; i++)
		{
			std::string tmp;
			file >> tmp;
			if (this->MapOfTextures[tmp]) 
			{
				if (tmp == "TurretPlace")
				{
					auto c = std::make_shared<Tiles>(static_cast<float>(i)*this->sizeX, static_cast<float>(j)*this->sizeY, this->MapOfTextures[tmp], tmp);
					auto d = std::make_shared<Tower>(c->getShape());
					this->Voftiles.push_back(d);
				}
				else
				{
					auto c = std::make_shared<Tiles>(static_cast<float>(i)*this->sizeX, static_cast<float>(j)*this->sizeY, this->MapOfTextures[tmp], tmp);
					this->Voftiles.push_back(c);
				}
			}
		}
	}
}

void Road::InitMapOfTextures()
{
	std::fstream file;
	file.open("Config/Available_tiles.ini");
	if (!file.is_open()) throw("ROAD::COULDNT LOAD Available_tiles.ini");
	std::string tmp;
	while (file >> tmp)
	{
		std::string Filename = "Resources/Images/Tiles/" + tmp + ".png";
		this->MapOfTextures[tmp] = new sf::Texture();
		this->MapOfTextures[tmp]->loadFromFile(Filename);
	}

}

void Road::render(sf::RenderTarget * target)
{
	for (auto it : this->Voftiles)
	{
		it->render(target);
	}
}

std::vector<std::shared_ptr<Tower>> Road::ReturnTowers()
{
	for (auto it : this->Voftiles) 
	{
		if (auto tmp =std::dynamic_pointer_cast<Tower>(it))
		{
			
			this->VofTowers.push_back(tmp);
			this->Voftiles.erase(std::remove(Voftiles.begin(),Voftiles.end(),it),Voftiles.end());
		}
	}
	return this->VofTowers;

	
}

void Road::SearchForNexusPosition()
{
	for (auto it : this->Voftiles)
	{
		if (it->getType() == "Base")
		{
			this->NexusPosition = it->getGlobalBounds();
		}
	}
}

const sf::FloatRect Road::ReturnNexusPosition()
{
	return this->NexusPosition;
}
