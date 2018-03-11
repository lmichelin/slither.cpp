/*
 * Template class to create data packets to be send and received between the client and the server
*/
#ifndef DATA_H
#define DATA_H

#include <SFML/Network.hpp>

template <class T>
class networkData {
	public:

		/////////////////
		//   Getters   //
		/////////////////

		virtual T getData() const {
			return _data;
		}

		/////////////////
		//   Setters   //
		/////////////////

		virtual void setData(T data) {
			_data = data;
		}

		// Package and extract data in packets
		virtual void package(sf::Packet& packet) =0;
		virtual void extract(sf::Packet& packet) =0;

	private: 

		// Data to be sent and received
		T _data;
};

#endif