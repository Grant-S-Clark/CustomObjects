#ifndef ENDECRYPTER_CLASS
#define ENDECRYPTER_CLASS

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

class EnDeCrypter
{
public:
	EnDeCrypter() { srand(time(NULL)); _seed = rand(); return; }
	EnDeCrypter(const int seed) : _seed(seed) { srand(time(NULL)); return; }
	~EnDeCrypter() { return; }

	//Seed functions.
	int seed() const;
	int& seed();
	void rand_seed();

	std::string encrypt(const std::string, const int seed = -1);
	std::string decrypt(const std::string, const int seed = -1);

private:
	//Range variables.
	static short RANGE_MIN;
	static short RANGE_MAX;
	static short RANGE_LENGTH;

	int _seed;

	char get_new_char(const int, const int, const int);
	char get_old_char(const int, const int, const int);
};

#endif