#include "inc/game.hpp"

namespace tdp {

	const float Game::PLAYER_SPEED = 100.f;
	const sf::Time Game::TIME_PER_FRAME = sf::seconds(1.f / 60.f);

	Game::Game() : window(sf::VideoMode(640, 480), "The Dark Path"), textures(), player(), landscape(), is_moving_up(false), is_moving_down(false), is_moving_left(false), is_moving_right(false), font(), statistics_text(), statistics_update_time(), statistics_num_frames(0) {
		this->textures.load(Textures::Character, "media/textures/character.png");
		this->textures.load(Textures::Landscape, "media/textures/landscape.jpg");
		this->player.setTexture(this->textures.get(Textures::Character));
		this->player.setPosition(200.f, 200.f);
		this->landscape.setTexture(this->textures.get(Textures::Landscape));
		if (!this->font.loadFromFile("media/fonts/font.ttf")) {
			throw std::runtime_error("Game::Game - Failed to load media/fonts/font.ttf");
		}
		this->statistics_text.setFont(this->font);
		this->statistics_text.setPosition(5.f, 5.f);
		this->statistics_text.setCharacterSize(10);
	}

	void Game::run() {
		sf::Clock clock;
		sf::Time time_since_last_update = sf::Time::Zero;
		while (this->window.isOpen()) {
			sf::Time elapsed_time = clock.restart();
			time_since_last_update += elapsed_time;
			while (time_since_last_update >= this->TIME_PER_FRAME) {
				time_since_last_update -= this->TIME_PER_FRAME;
				this->process_events();
				this->update(this->TIME_PER_FRAME);
			}
			this->update_statistics(elapsed_time);
			this->render();
		}
		return;
	}

	void Game::process_events() {
		sf::Event event;
		while (this->window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape) {
						this->window.close();
					}
					else {
						this->handle_player_input(event.key.code, true);
					}
					break;
				case sf::Event::KeyReleased:
					this->handle_player_input(event.key.code, false);
					break;
				case sf::Event::Closed:
					this->window.close();
					break;
			}
		}
		return;
	}

	void Game::update(sf::Time delta_time) {
		sf::Vector2f movement(0.f, 0.f);
		if (this->is_moving_up) {
			movement.y -= this->PLAYER_SPEED;
		}
		if (this->is_moving_down) {
			movement.y += this->PLAYER_SPEED;
		}
		if (this->is_moving_left) {
			movement.x -= this->PLAYER_SPEED;
		}
		if (this->is_moving_right) {
			movement.x += this->PLAYER_SPEED;
		}
		this->player.move(movement * delta_time.asSeconds());
		return;
	}

	void Game::render() {
		this->window.clear();
		this->window.draw(this->landscape);
		this->window.draw(this->player);
		this->window.draw(this->statistics_text);
		this->window.display();
		return;
	}

	void Game::handle_player_input(sf::Keyboard::Key key, bool is_pressed) {
		if (key == sf::Keyboard::W || key == sf::Keyboard::Up) {
			this->is_moving_up = is_pressed;
		}
		else if (key == sf::Keyboard::S || key == sf::Keyboard::Down) {
			this->is_moving_down = is_pressed;
		}
		else if (key == sf::Keyboard::A || key == sf::Keyboard::Left) {
			this->is_moving_left = is_pressed;
		}
		else if (key == sf::Keyboard::D || key == sf::Keyboard::Right) {
			this->is_moving_right = is_pressed;
		}
		return;
	}

	void Game::update_statistics(sf::Time delta_time) {
		this->statistics_update_time += delta_time;
		++this->statistics_num_frames;
		if (this->statistics_update_time >= sf::seconds(1.f)) {
			this->statistics_text.setString(L"Frames / Second = " + std::to_wstring(this->statistics_num_frames) + L"\nTime / Update = " + std::to_wstring(this->statistics_update_time.asMicroseconds() / this->statistics_num_frames) + L" µs");
			this->statistics_update_time -= sf::seconds(1.f);
			this->statistics_num_frames = 0;
		}
		return;
	}

}
