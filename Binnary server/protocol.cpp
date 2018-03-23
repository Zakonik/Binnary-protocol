#include"protocol.h"

int bit_lenght(long a)
{
	if (a < 0)
	{
		a *= -1;
	}
	long i = 0;
	do
	{
		a /= 2;
		i++;
	} while (a > 0);
	return i;
}

void send(sf::TcpSocket & socket, int operation, int id, long data, bool set_id, bool fin, bool overflow)
{
	std::bitset<1024> buffer;

	//sprawdzanie dlugosci wysylanej liczby
	long bitsize = bit_lenght(data);

	//ustawianie operacji
	buffer = operation;

	//ustawainie statusu
	buffer <<= 4;
	if (data < 0 && fin)
	{
		buffer ^= 3;
		data *= -1;
	}
	else if (fin)
	{
		buffer ^= 1;
	}
	else if (data < 0)
	{
		buffer ^= 2;
		data *= -1;
	}
	else if (overflow)
	{
		buffer ^= 4;
		buffer <<= 41;
		buffer ^= id;
		socket.send(&buffer, 6);
		return;

	}
	else if (set_id)
	{
		buffer ^= 8;
		buffer <<= 32;
		buffer ^= 9;
		buffer <<= 9;
		buffer ^= id;
		socket.send(&buffer, 6);
		return;
	}

	//ustawianie wielkosci danych
	buffer <<= 32;
	buffer ^= bitsize+9;

	//ustawianie id
	buffer <<= 9;
	buffer ^= id;

	//ustawianie danych
	buffer <<= bitsize;
	buffer ^= data;

	//wysy³anie
	if (bitsize % 8 != 0)
	{
		buffer <<= 8 - bitsize % 8;
		socket.send(&buffer, (6 + (bitsize + (8 - bitsize % 8)) / 8));
	}
	else
	{
		socket.send(&buffer, 6 + (bitsize / 8));
	}
}

std::tuple<int, long, bool, bool> recive(sf::TcpSocket & socket, int &id)
{
	std::bitset<1024> buffer, temp;
	size_t received;
	int operation, status;
	long data, bitsize;

	//odbiereanie
	socket.receive(&buffer, sizeof(buffer), received);

	//read operation
	temp = buffer;
	temp >>= received * 8 - 3;
	operation = temp.to_ulong();


	//read status
	temp = buffer;
	temp >>= received * 8 - 7;
	temp <<= 1020;
	temp >>= 1020;
	status = temp.to_ulong();

	//read bitsize
	temp = buffer;
	temp >>= received * 8 - 39;
	temp <<= 1024 - 32;
	temp >>= 1024 - 32;
	bitsize = temp.to_ulong();

	//read id
	temp = buffer;
	temp >>= received * 8 - 48;
	temp <<= 1024 - 9;
	temp >>= 1024 - 9;
	if (status == 8)
	{
		id = temp.to_ulong();
	}
	else
	{
		if (id == temp.to_ulong())
		{
			std::cout << "Id is gucci" << std::endl;
		}
		else
		{
			std::cout << "Someone broke id" << std::endl;
		}
	}

	//read data
	temp = buffer;
	temp <<= 1024 - (received - 6) * 8;
	temp >>= 1024 - bitsize+9;
	data = temp.to_ulong();

	if (status == 3 || status == 2)
	{
		data *= -1;
	}

	if (status == 3 || status == 1)
	{
		return std::make_tuple(operation, data, true, false);
	}
	else if (status == 4)
	{
		return std::make_tuple(operation, data, false, true);
	}
	else
	{
		return std::make_tuple(operation, data, false, false);
	}

}
