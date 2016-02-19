#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "inc/resource_holder.hpp"

namespace tdp {

	class Game : private sf::NonCopyable {
		public:
			Game();
			void run();
		private:
			void process_events();
			void update(sf::Time delta_time);
			void render();
			void handle_player_input(sf::Keyboard::Key key, bool is_pressed);
			void update_statistics(sf::Time delta_time);
			sf::RenderWindow window;
			TextureHolder textures;
			sf::Sprite player;
			sf::Sprite landscape;
			bool is_moving_up;
			bool is_moving_down;
			bool is_moving_left;
			bool is_moving_right;
			static const sf::Time TIME_PER_FRAME;
			static const float PLAYER_SPEED;
			sf::Font font;
			sf::Text statistics_text;
			sf::Time statistics_update_time;
			std::size_t statistics_num_frames;
	};

}

#endif
