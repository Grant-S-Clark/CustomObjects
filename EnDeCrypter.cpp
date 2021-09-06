#include "EnDeCrypter.h"

//Statically assigned variables.
short EnDeCrypter::RANGE_MIN = 32;
short EnDeCrypter::RANGE_MAX = 126;
short EnDeCrypter::RANGE_LENGTH = 95;

//Return seed the EnDeCrypter is using.
int  EnDeCrypter::seed() const { return _seed; }
int& EnDeCrypter::seed() { return _seed; }

//Create a new seed for the EnDeCrypter to use.
//SEED MUST BE AT LEAST 51.
void EnDeCrypter::rand_seed() { _seed = rand() + 51; return; }

/*
* Given the integer value of a character, check to see if that value is within
* the ascii range we will be working with (RANGE_MIN <= char_value <= RANGE_MAX).
* If this is true, a seed will be used to determine the offset of the encrypted
* character, along with its place in the string. Using 'i' to represent the index
* of the character within a string, the new character value will be determined like
* so:
*		char_int_value + offset + (i * offset)
*
* You may notice that this formula allows for the character value to travel out of
* range, but if this occurs all that is needed to be done is to mudulus the character
* value by the RANGE_LEGNTH and add the RANGE_MIN to it to get it back into range
* (new_char_int % LENGTH + RANGE_MIN).
* 
* Note: If a character is not within the correct range, it will just be appended
* into the message with no encryption.
*/
std::string EnDeCrypter::encrypt(const std::string s, int seed)
{
	//If no parameter is sent, use saved seed.
	if (seed == -1)
		seed = _seed;
	//If out of range, notify user and return "".
	else if (seed > RAND_MAX + 51 || seed < 51)
	{
		std::cout << "Invalid Seed. Must be at least 51.\n";
		return "";
	}

	std::string new_text;

	for (int i = 0; i < s.size(); i++)
	{
		if ((int)s.at(i) >= RANGE_MIN && (int)s.at(i) <= RANGE_MAX)
			new_text.push_back(get_new_char((int)s.at(i), i, seed));

		else
			new_text.push_back(s.at(i));
	}

	return new_text;
}

char EnDeCrypter::get_new_char(const int char_int, const int i, const int seed)
{
	int new_int;

	new_int = char_int + seed + (i * seed);
	//If it escapes the range max, modulus and add the min
	//to get it back to where it needs to be.
	if (new_int > RANGE_MAX)
	{
		new_int %= RANGE_LENGTH;
		new_int += RANGE_MIN;
	}

	return new_int;
}

/*
* Using an encrypted message and its seed, this for loop will undo the encryption.
* It does so by taking the integer value of the character and subtracting the
* RANGE_MIN from it, and then subtracting the offset (seed) multiplied by i + 1
* modulus RANGE_LENGTH. After this it will add RANGE_LENGTH to that value.
* All together it looks like this:
*
*	((char_int - RANGE_MIN) - ((offset * (i + 1)) % RANGE_LENGTH)) + RANGE_LENGTH
*
* This can be the correct character, but sometimes it steps out of bounds, and if
* so, RANGE_LENGTH is added to the value if it is below RANGE_MIN, and alternatively
* RANGE_LENGTH is subtracted from the value if it is above RANGE_MAX. This
* will leave you with the integer value of the decrypted character.
*
* Note: If the encrypted character is not within the correct range, that means the
* decrypted character is the same as the encrypted character, so it will just be
* appended with no decryption.
*/
std::string EnDeCrypter::decrypt(const std::string s, int seed)
{
	//If no parameter is sent, use saved seed.
	if (seed == -1)
		seed = _seed;
	//If out of range, notify user and return "".
	else if (seed > RAND_MAX + 51 || seed < 51)
	{
		std::cout << "Invalid Seed. Must be at least 51.\n";
		return "";
	}

	std::string old_text;

	for (int i = 0; i < s.size(); i++)
	{
		if ((int)s.at(i) >= RANGE_MIN && (int)s.at(i) <= RANGE_MAX)
			old_text.push_back(get_old_char((int)s.at(i), i, seed));

		else
			old_text.push_back(s.at(i));
	}

	return old_text;
}

char EnDeCrypter::get_old_char(const int char_int, const int i, const int seed)
{
	int old_int;

	old_int = ((char_int - RANGE_MIN) - ((seed * (i + 1)) % RANGE_LENGTH)) + RANGE_LENGTH;

	//If it goes out of range in either direction, add or subtract the total
	//length of the range depending on which direction it went out of range.
	if (old_int > RANGE_MAX)
		old_int -= RANGE_LENGTH;
	else if (old_int < RANGE_MIN)
		old_int += RANGE_LENGTH;

	return old_int;
}