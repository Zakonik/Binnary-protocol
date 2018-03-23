#include<SFML\Network.hpp>
#include<iostream>
#include<vector>
#include<bitset>
#include<random>
#include<array>
#include<math.h>
#include"protocol.h"

#define get_op std::get<0>(datas)
#define get_data std::get<1>(datas)
#define get_fin std::get<2>(datas)

long random(long a, long b)
{
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(a, b);
	return dist(rng);
}

int main() {
	int id = random(0, 511);
	std::array<long, 8> results;
	std::array<bool, 8> first;
	results.fill(0);
	first.fill(true);

	// Create a listener to wait for incoming connections on port 55001
	sf::TcpListener listener;
	std::cout << "Słucham" << std::endl;
	listener.listen(55001);

	// Wait for a connection
	sf::TcpSocket socket;
	listener.accept(socket);

	send(socket, 0, id, 0, true, false, false);
	
	while (true)
	{
		auto datas = recive(socket, id);
		
		switch (get_op)
		{
			case(0): // +
			{
				if (first[get_op])
				{
					results[get_op] = get_data;
					first[get_op] = false;
				}
				else
				{
					results[get_op] += get_data;
				}
				if (get_fin)
				{
					if (results[get_op]>=1048576|| results[get_op] <= -1048576)
					{
						send(socket, get_op, id, results[get_op], false, false,true);
					}
					else
					{
						send(socket, get_op, id, results[get_op], false, false, false);
					}
					first[get_op] = true;
				}
				break;
			}
			case(1): // -
			{
				if (first[get_op])
				{
					results[get_op] = get_data;
					first[get_op] = false;
				}
				else
				{
					results[get_op] -= get_data;
				}
				if (get_fin)
				{
					if (results[get_op] >= 1048576 || results[get_op] <= -1048576)
					{
						send(socket, get_op, id, results[get_op], false, false, true);
					}
					else
					{
						send(socket, get_op, id, results[get_op], false, false, false);
					}
					first[get_op] = true;
				}
				break;
			}
			case(2): // *
			{
				if (first[get_op])
				{
					results[get_op] = get_data;
					first[get_op] = false;
				}
				else
				{
					results[get_op] *= get_data;
				}
				if (get_fin)
				{
					if (results[get_op] >= 1048576 || results[get_op] <= -1048576)
					{
						send(socket, get_op, id, results[get_op], false, false, true);
					}
					else
					{
						send(socket, get_op, id, results[get_op], false, false, false);
					}
					first[get_op] = true;
				}
				break;
			}
			case(3): // /
			{
				if (first[get_op])
				{
					results[get_op] = get_data;
					first[get_op] = false;
				}
				else
				{
					results[get_op] /= get_data;
				}
				if (get_fin)
				{
					if (results[get_op] >= 1048576 || results[get_op] <= -1048576)
					{
						send(socket, get_op, id, results[get_op], false, false, true);
					}
					else
					{
						send(socket, get_op, id, results[get_op], false, false, false);
					}
					first[get_op] = true;
				}
				break;
			}
			case(4): // factorial
			{
				long factorial = 1;
				for (int i = 1; i <= get_data; i++)
				{
					factorial *= i;
				}
				results[get_op] = factorial;
				if (get_fin)
				{
					if (results[get_op] >= 1048576 || results[get_op] <= -1048576)
					{
						send(socket, get_op, id, results[get_op], false, false, true);
					}
					else
					{
						send(socket, get_op, id, results[get_op], false, false, false);
					}
					first[get_op] = true;
				}
				break;
			}
			case(5)://pow
			{
				if (first[get_op])
				{
					results[get_op] = get_data;
					first[get_op] = false;
				}
				else
				{
					results[get_op] += pow(results[get_op], get_data);
				}
				if (get_fin)
				{
					if (results[get_op] >= 1048576 || results[get_op] <= -1048576)
					{
						send(socket, get_op, id, results[get_op], false, false, true);
					}
					else
					{
						send(socket, get_op, id, results[get_op], false, false, false);
					}
					first[get_op] = true;
				}
				break;
			}
			case(6): //root
			{
				results[get_op] = sqrt(get_data);
				if (get_fin)
				{
					if (results[get_op] >= 1048576 || results[get_op] <= -1048576)
					{
						send(socket, get_op, id, results[get_op], false, false, true);
					}
					else
					{
						send(socket, get_op, id, results[get_op], false, false, false);
					}
					first[get_op] = true;
				}
				break;
			}
			case(7): //prime
			{
				bool isPrime = true;
				long n = get_data;
				for (int i = 2; i <= n / 2; ++i)
				{
					if (n % i == 0)
					{
						isPrime = false;
						break;
					}
				}
				if (isPrime)
				{
					results[get_op] = 1;
				}
				else
				{
					results[get_op] = 0;
				}
				if (get_fin)
				{
					if (results[get_op] >= 1048576 || results[get_op] <= -1048576)
					{
						send(socket, get_op, id, results[get_op], false, false, true);
					}
					else
					{
						send(socket, get_op, id, results[get_op], false, false, false);
					}
					first[get_op] = true;
				}
				break;
			}
		}

	}

	socket.disconnect();
	return 0;
}