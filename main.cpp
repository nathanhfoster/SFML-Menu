#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include "Menu.hpp"


bool checkForMouseTrigger(sf::Sprite &av_Sprite, sf::RenderWindow &av_Window);
void launchMenu(sf::RenderWindow &window);

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "League Project");
	sf::Texture paddleLarge;
	sf::Texture leagueLogo;
	sf::Texture leagueLaunch;
	

	if (!paddleLarge.loadFromFile("Paddle Large.png"))
		window.close();

	if (!leagueLogo.loadFromFile("League Logo.png"))
		window.close();

	if (!leagueLaunch.loadFromFile("League Launch.png"))
		window.close();

	
	// Sprites
	sf::Sprite sprite_Paddle(paddleLarge);
	sf::Sprite sprite_LeagueLogo(leagueLogo);
	sf::Sprite sprite_LeagueLaunch(leagueLaunch);
	

	// Audio
	sf::SoundBuffer mainMenuBuffer;
	if (!mainMenuBuffer.loadFromFile("MainMenuMusic.ogg"))
		window.close();

	sf::SoundBuffer launchBuffer;
	if (!launchBuffer.loadFromFile("LaunchSound.ogg"))
		window.close();

	sf::Sound mainMenuMusic;
	mainMenuMusic.setBuffer(mainMenuBuffer);
	mainMenuMusic.play();

	sf::Sound launchSound;
	launchSound.setBuffer(launchBuffer);

	Menu menu(window.getSize().x, window.getSize().y);

	while (window.isOpen())
	{
		sf::Event event;

		//sf::Vector2i windowPosition = window.getPosition();
		//int mouseX = sf::Mouse::getPosition().x + sprite.getGlobalBounds().width;
		//int mouseY = sf::Mouse::getPosition().y + sprite.getGlobalBounds().height;
		//int mouseX = (sf::Mouse::getPosition().x);
		//int mouseY = (sf::Mouse::getPosition().y);

		//sprite.setPosition(mouseX, mouseY);

		while (window.pollEvent(event))
		{
			sprite_LeagueLogo.setPosition(550, 0);
			sprite_LeagueLaunch.setPosition(100, 50);
			// Polled input handling -- mouse coordinates are in screen space, not window space
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				sprite_Paddle.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))); //Absolute transform
			else
				sprite_Paddle.setPosition(854, 604); // Reset position


			if (checkForMouseTrigger(sprite_Paddle, window))
				std::cout << "Paddle clicked!" << std::endl;

			if (checkForMouseTrigger(sprite_LeagueLaunch, window))
			{
				std::cout << "Launch clicked!" << std::endl;
				window.clear();
				launchSound.play();
				launchMenu(window);
			}

			switch (event.type)
			{
			case sf::Event::KeyReleased:

				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
						std::cout << "Play button has been pressed" << std::endl;
						break;
					case 1:
						std::cout << "Option button has been pressed" << std::endl;
						break;
					case 2:
						window.close();
						break;
					}

					break;
				}

				break;
			case sf::Event::Closed:
				window.close();

				break;

			}
		}

		//window.clear(sf::Color::Black);

		window.clear();

		menu.draw(window);

		window.draw(sprite_Paddle);

		window.draw(sprite_LeagueLogo);

		window.draw(sprite_LeagueLaunch);

		
		window.display();
	}
}

bool checkForMouseTrigger(sf::Sprite &sprite, sf::RenderWindow &window)
{
	int mouseX = sf::Mouse::getPosition().x;
	int mouseY = sf::Mouse::getPosition().y;

	sf::Vector2i windowPosition = window.getPosition();

	if (mouseX > sprite.getPosition().x + windowPosition.x && mouseX < (sprite.getPosition().x + sprite.getGlobalBounds().width + windowPosition.x)
		&& mouseY > sprite.getPosition().y + windowPosition.y + 30 && mouseY < (sprite.getPosition().y + sprite.getGlobalBounds().height + windowPosition.y + 30))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return true;
		}
		return false;
	}
	return false;
}

void launchMenu(sf::RenderWindow &window)
{
	sf::Texture leaguePlay;
	if (!leaguePlay.loadFromFile("League Play.png"))
		window.close();


	sf::Sprite sprite_LeaguePlay(leaguePlay);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			sprite_LeaguePlay.setPosition(100, 250);

			if (checkForMouseTrigger(sprite_LeaguePlay, window))
				std::cout << "Play clicked!" << std::endl;

			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}

			window.clear();
			window.draw(sprite_LeaguePlay);
			window.display();
		}

	}
}