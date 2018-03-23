#pragma once
#include<SFML\Network.hpp>
#include<iostream>
#include<vector>
#include<bitset>
#include<array>
#include<tuple>

int bit_lenght(long a);


void send(sf::TcpSocket &socket, int operation, int id , long data, bool set_id,bool fin,bool overflow);

std::tuple<int, long, bool, bool> recive(sf::TcpSocket &socket, int &id);