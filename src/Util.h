
#pragma once

#include <vector>
#include <climits>
#include <cstring>
#include <unordered_set>


class Util
{
public:
	inline static bool tokenize( std::string& inputStr, const unsigned int& tokenCount,
										std::vector< std::string >& foundedTokens );

	static bool isUInt( std::string& inputStr, const unsigned int& tokenCount, std::vector<unsigned int>& result_Uints,
			const std::vector<unsigned int>& specificTokensIndices, const int minValue = 0, const int maxValue = INT_MAX );
};
