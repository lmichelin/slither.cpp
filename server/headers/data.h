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

		virtual void send(sf::TcpSocket& socket, int header, sf::Socket::Status& status) =0;
		virtual void receive(sf::TcpSocket& socket, int& header, sf::Socket::Status& status) =0;

	private: 
		T _data;
};