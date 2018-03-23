#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include<vector>
#include<bitset>
#include"protocol.h"
#define get_data std::get<1>(datas)
#define get_over std::get<3>(datas)




int main() {
	int id;
	// Connecting
	std::string ip;
	std::cout << "Podaj ip serwera" << std::endl;
	std::cin >> ip;

	sf::TcpSocket socket;
	socket.connect(ip, 55001);
	std::cout << "Connected" << std::endl;
	
	// Ustalanie ID
	recive(socket, id);
	std::cout << "Ustalony identyfikator to:" << id << std::endl;


	bool test=false;
	while (!test)
	{
		std::cout << "Wybierz co chcesz zrobiæ" << std::endl;
		std::string a;
		std::cin >> a;
		switch (std::stoi(a))
		{
			case(1): //dodawanie
			{ 
				long liczba;
				bool fin=false;
				do {
					do {
						std::cout << "Podaj liczbe do dzilania" << std::endl;
						std::cin >> liczba;
					} while (liczba >= 1048576|| liczba<= -1048576);
					std::string konec;
					std::cout << "To ostatnia liczba? Y/N" << std::endl;
					std::cin >> konec;
					if (konec == "y" || konec == "Y")
					{
						fin = true;
					}
					send(socket,0,id,liczba,false,fin,false);
				} while (!fin);
				auto datas=recive(socket,id);
				if (get_over)
				{
					std::cout << "OverFlow" << std::endl;
				}
				else {
					std::cout << "Wyniki to :" << get_data << std::endl;
				}
				break;
			}
			case(2): //odejmowanie
			{
				
				long liczba;
				bool fin = false;
				do {
					do{
						std::cout << "Podaj liczbe do dzilania" << std::endl;
						std::cin >> liczba;
					} while (liczba >= 1048576||liczba<=-1048576);
					std::string konec;
					std::cout << "To ostatnia liczba? Y/N" << std::endl;
					std::cin >> konec;
					if (konec == "y" || konec == "Y")
					{
						fin = true;
					}
					send(socket, 1, id, liczba, false, fin, false);
				} while (!fin);
				auto datas = recive(socket, id);
				if (get_over)
				{
					std::cout << "OverFlow" << std::endl;
				}
				else {
					std::cout << "Wyniki to :" << get_data << std::endl;
				}
				break;
			}
			case(3): //mnozenie
			{
				long liczba;
				bool fin = false;
				do {
					do {
						std::cout << "Podaj liczbe do dzilania" << std::endl;
						std::cin >> liczba;
					} while (liczba >= 1048576 || liczba <= -1048576);
					std::string konec;
					std::cout << "To ostatnia liczba? Y/N" << std::endl;
					std::cin >> konec;
					if (konec == "y" || konec == "Y")
					{
						fin = true;
					}
					send(socket, 2, id, liczba, false, fin, false);
				} while (!fin);
				auto datas = recive(socket, id);
				if (get_over)
				{
					std::cout << "OverFlow" << std::endl;
				}
				else {
					std::cout << "Wyniki to :" << get_data << std::endl;
				}
				break;
			}
			case(4): //dzielenie
			{
				long liczba;
				bool fin = false;
				do {
					do 
					{
						std::cout << "Podaj liczbe do dzilania inna od 0" << std::endl;
						std::cin >> liczba;
					} while (liczba == 0|| liczba >= 1048576 || liczba <= -1048576);
					std::string konec;
					std::cout << "To ostatnia liczba? Y/N" << std::endl;
					std::cin >> konec;
					if (konec == "y" || konec == "Y")
					{
						fin = true;
					}
					send(socket, 3, id, liczba, false, fin, false);
				} while (!fin);
				auto datas = recive(socket, id);
				if (get_over)
				{
					std::cout << "OverFlow" << std::endl;
				}
				else {
					std::cout << "Wyniki to :" << get_data << std::endl;
				}
				break;
			}
			case(5): //silnia
			{
				long liczba;
				bool fin = true;
				do {
					std::cout << "Podaj liczbe do dzilania nie ujemna" << std::endl;
					std::cin >> liczba;
				} while (liczba < 0||liczba>1048576);
				send(socket, 4, id, liczba, false, fin, false);
				auto datas = recive(socket, id);
				if (get_over)
				{
					std::cout << "OverFlow" << std::endl;
				}
				else {
					std::cout << "Wyniki to :" << get_data << std::endl;
				}
					break;
			}
			case(6): //pow
			{
				long liczba;
				bool fin = false;
				do {
					do {
						std::cout << "Podaj liczbe do dzilania" << std::endl;
						std::cin >> liczba;
					} while (liczba >= 1048576 || liczba <= -1048576);
					std::string konec;
					std::cout << "To ostatnia liczba? Y/N" << std::endl;
					std::cin >> konec;
					if (konec == "y" || konec == "Y")
					{
						fin = true;
					}
					send(socket, 5, id, liczba, false, fin, false);
				} while (!fin);
				auto datas = recive(socket, id);
				if (get_over)
				{
					std::cout << "OverFlow" << std::endl;
				}
				else {
					std::cout << "Wyniki to :" << get_data << std::endl;
				}
				break;
			}
			case(7): //root
			{
				long liczba;
				bool fin = true;
				do {
					std::cout << "Podaj liczbe do dzilania" << std::endl;
					std::cin >> liczba;
				} while (liczba > 1048576||liczba<0);

				send(socket, 6, id, liczba, false, fin, false);
				auto datas = recive(socket, id);
				if (get_over)
				{
					std::cout << "OverFlow" << std::endl;
				}
				else {
					std::cout << "Wyniki to :" << get_data << std::endl;
				}
				break;
			}
			case(8): //prim
			{
				long liczba;
				bool fin = true;
				do {
					std::cout << "Podaj liczbe do dzilania nie ujemna" << std::endl;
					std::cin >> liczba;
				} while (liczba < 2||liczba>1048576);
				send(socket, 7, id, liczba, false, fin, false);
				auto datas = recive(socket, id);
				if (get_over)
				{
					std::cout << "OverFlow" << std::endl;
				}
				else {
					std::cout << "Wyniki to :" << get_data << std::endl;
				}
				break;
			}
			default:
			{
				std::cout << "Nie ma takie operaji. Czy chcesz moze zakonczyc polaczenie? Y/N" << std::endl;
				std::string konec;
				std::cin >> konec;
				if (konec == "y" || konec == "Y")
				{
					test = true;
				}
			}
			
		}

	}

	
	

	
	sf::sleep(sf::seconds(1));
	socket.disconnect();
	
	return 0;
}