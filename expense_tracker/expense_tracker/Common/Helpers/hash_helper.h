#pragma once
#include <string>
#include <sstream>
#include "openssl/sha.h"
#include <iomanip>

using namespace std;

class hash_helper
{
public:
  	static string create_sha256_hash_str(string value)
	{
		unsigned char hash[SHA256_DIGEST_LENGTH];
		SHA256_CTX sha256;
		SHA256_Init(&sha256);
		SHA256_Update(&sha256, value.c_str(), value.size());
		SHA256_Final(hash, &sha256);
		stringstream ss;
		for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
		{
			ss << hex << setw(2) << setfill('0') << (int)hash[i];
		}
		return ss.str();
	}
};