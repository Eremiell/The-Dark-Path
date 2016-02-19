#ifndef RESOURCE_HANDLER_HPP
#define RESOURCE_HANDLER_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include <cassert>
#include <type_traits>
#include <SFML/Graphics.hpp>

namespace tdp {

	struct EnumClassHash {
		template <typename Identifier>
		std::size_t operator()(Identifier id) const {
			return static_cast<std::size_t>(id);
		}
	};

	enum class Textures {Character, Landscape, Last, First = Character};
/*
	Textures operator++(Textures &texture) {
		return texture = static_cast<Textures>(static_cast<std::size_t>(texture) + 1);
	}

	Textures operator*(Textures texture) {
		return texture;
	}

	Textures begin(Textures texture) {
		return Textures::First;
	}

	Textures end(Textures texture) {
		return Textures::Last;
	}
*/
	const std::unordered_map<Textures, std::string, EnumClassHash> texture_labels = {{Textures::Character, "Character"}, {Textures::Landscape, "Landscape"}};

	template <typename Resource, typename Identifier>
	class ResourceHolder {
		public:
			void load(Identifier id, const std::string &filename);
			template <typename Parameter>
			void load(Identifier id, const std::string &filename, const Parameter &second_param);
			Resource& get(Identifier id);
			const Resource& get(Identifier id) const;
		private:
			void insert_resource(Identifier id, std::unique_ptr<Resource> resource);
			std::unordered_map<Identifier, std::unique_ptr<Resource>, EnumClassHash> resource_map;
	};

	typedef ResourceHolder<sf::Texture, Textures> TextureHolder;

	template <typename Resource, typename Identifier>
	void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string &filename) {
		std::unique_ptr<Resource> resource(new Resource());
		if (!resource->loadFromFile(filename)) {
			throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
		}
		this->insert_resource(id, std::move(resource));
		return;
	}

	template <typename Resource, typename Identifier>
	template <typename Parameter>
	void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string &filename, const Parameter &second_param) {
		std::unique_ptr<Resource> resource(new Resource());
		if (!resource->loadFromFile(filename, second_param)) {
			throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
		}
		this->insert_resource(id, std::move(resource));
		return;
	}

	template <typename Resource, typename Identifier>
	Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) {
		auto found = this->resource_map.find(id);
		assert(found != this->resource_map.end());
		return *found->second;
	}

	template <typename Resource, typename Identifier>
	const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const {
		auto found = this->resource_map.find(id);
		assert(found != this->resource_map.end());
		return *found->second;
	}

	template <typename Resource, typename Identifier>
	void ResourceHolder<Resource, Identifier>::insert_resource(Identifier id, std::unique_ptr<Resource> resource) {
		auto inserted = this->resource_map.insert(std::make_pair(id, std::move(resource)));
		assert(inserted.second);
		return;
	}

}

#endif
