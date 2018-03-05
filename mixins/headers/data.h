#ifndef DATA_H
#define DATA_H

#include <SFML/Network.hpp>

template <class T>
class networkData {
	public:
		virtual T getData() const {
			return _data;
		}

		virtual void setData(T data) {
			_data = data;
		}

		virtual void package(sf::Packet& packet) =0;
		virtual void extract(sf::Packet& packet) =0;

	private: 
		T _data;
};

#endif