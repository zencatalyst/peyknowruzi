// PeykNowruzi, easy implementation ( multi platform )
// repo available at https://github.com/Kasra-coder/magical-creations


#include <iostream>
#include <vector>
#include <memory>
#include <unordered_set>
#include <string>
#include <climits>
#include <cstring>


class CharMatrix
{
public:
	inline CharMatrix( );
	inline CharMatrix( const unsigned int& Y_DIM, const unsigned int& X_DIM, const char FILL_CHARACTER = ' ' );
	inline ~CharMatrix( ) = default;
	inline CharMatrix( const CharMatrix& ) = delete;
	inline CharMatrix& operator=( const CharMatrix& ) = delete;
	inline CharMatrix( CharMatrix&& rhs ) noexcept;
	inline CharMatrix& operator=( CharMatrix&& rhs ) noexcept;

	inline const unsigned int& getY_DIM( ) const;
	inline const unsigned int& getX_DIM( ) const;
	inline std::vector< std::vector<char> >& getCharacterMatrix( );

	inline static char findCharType( const unsigned int(&coordArr)[4] );
	inline static auto initialize( );
	inline static unsigned int getNumOfInputLines( );
	inline static auto getCoords( );
	inline static void writeToOutput( );

private:
	unsigned int _Y_DIM;
	unsigned int _X_DIM;
	std::vector< std::vector<char> > _characterMatrix;
	inline static const std::unordered_set<char> CHAR_SET { '/', '\\', '|', '-' };
};

class Util
{
public:
	inline static bool tokenize( std::string& inputStr, const unsigned int& tokenCount,
										std::vector< std::string >& foundedTokens );

	inline static bool isUInt( std::string& inputStr, const unsigned int& tokenCount, std::vector<unsigned int>& result_Uints,
			const std::vector<unsigned int>& specificTokensIndices, const int minValue = 0, const int maxValue = INT_MAX );
};

int main( )
{
	CharMatrix::writeToOutput( );

	return 0;
}

inline bool Util::tokenize( std::string& inputStr, const unsigned int& tokenCount, std::vector< std::string >& foundedTokens )
{
	bool isAcceptable = true;

	char* ptr2FirstChar = &inputStr[0];
	char* ptr2NextToken = strtok( ptr2FirstChar,   "	 " );

	while ( ptr2NextToken )
	{
		foundedTokens.push_back( ptr2NextToken );
	    ptr2NextToken = strtok( NULL, " 	" );
	}

	isAcceptable = ( foundedTokens.size( ) != tokenCount ) ? false : true;

	return isAcceptable;
}

inline bool Util::isUInt( std::string& inputStr, const unsigned int& tokenCount, std::vector<unsigned int>& result_Uints,
				const std::vector<unsigned int>& specificTokensIndices, const int minValue, const int maxValue )
{
	bool isAcceptable = ( minValue < 0 || maxValue < 0 ) ? false : true;

	if ( !isAcceptable ) { return isAcceptable; }

	std::vector< std::string > foundedTokens;
	foundedTokens.reserve( tokenCount );

	isAcceptable = tokenize( inputStr, tokenCount, foundedTokens );

	if ( !isAcceptable )
	{
		return isAcceptable;
	}

	size_t pos = 0;
	unsigned int j = 0;

	for ( unsigned int i = 0; i < foundedTokens.size( ); ++i )
	{
		isAcceptable = true;

		if ( !specificTokensIndices.empty( ) )
		{
			if ( j < specificTokensIndices.size( ) )
			{
				i = specificTokensIndices[j];
			}
			else
			{
				break;
			}
			++j;
		}

		try
		{
			int result_Int = std::stoi( foundedTokens[i], &pos, 10 );

			if ( pos != foundedTokens[i].length( ) )
			{
				isAcceptable = false;
			}
			if ( isAcceptable )
			{
				isAcceptable = ( (result_Int > maxValue || result_Int < minValue) ) ? false : true;
			}
			if ( isAcceptable )
			{
				result_Uints[i] = result_Int;
			}
		}
		catch( const std::invalid_argument& ia )
		{
			isAcceptable = false;
		}
		catch ( const std::out_of_range& oor )
		{
			isAcceptable = false;
		}
		catch ( const std::exception& e )
		{
			isAcceptable = false;
		}
		catch ( ... )
		{
			isAcceptable = false;
		}

		if ( !isAcceptable )
		{
			break;
		}
	}

	return isAcceptable;
}

inline CharMatrix::CharMatrix( )
	:_Y_DIM( 20 ), _X_DIM( 20 ), _characterMatrix( 20, std::vector<char>( 20, ' ' ) )
{
}

inline CharMatrix::CharMatrix( const unsigned int& Y_DIM, const unsigned int& X_DIM, const char FILL_CHARACTER )
	: _Y_DIM( Y_DIM ), _X_DIM( X_DIM ), _characterMatrix( Y_DIM, std::vector<char>( X_DIM, FILL_CHARACTER ) )
{
}

inline CharMatrix::CharMatrix( CharMatrix&& rhs ) noexcept
	:_Y_DIM( rhs._Y_DIM ), _X_DIM( rhs._X_DIM )
{
	_characterMatrix = std::move( rhs._characterMatrix );
	
	rhs._Y_DIM = 0;
	rhs._X_DIM = 0;
}

inline CharMatrix& CharMatrix::operator=( CharMatrix&& rhs ) noexcept
{
	if ( this != &rhs )
	{
		_characterMatrix = std::move( rhs._characterMatrix );
		_Y_DIM = rhs._Y_DIM;
		_X_DIM = rhs._X_DIM;

		rhs._Y_DIM = 0;
		rhs._X_DIM = 0;
	}

	return *this;
}

inline const unsigned int& CharMatrix::getY_DIM( ) const
{
	return _Y_DIM;
}

inline const unsigned int& CharMatrix::getX_DIM( ) const
{
	return _X_DIM;
}

inline std::vector< std::vector<char> >& CharMatrix::getCharacterMatrix( )
{
	return _characterMatrix;
}

inline char CharMatrix::findCharType( const unsigned int(&coordArr)[4] )
{
	if ( abs(coordArr[0] - coordArr[2]) == 1 && abs(coordArr[1] - coordArr[3]) == 1 &&
				((coordArr[0] < coordArr[2] && coordArr[1] > coordArr[3]) || (coordArr[0] > coordArr[2] && coordArr[1] < coordArr[3])) )
	{
		return '/';
	}
	else if ( abs(coordArr[0] - coordArr[2]) == 1 && abs(coordArr[1] - coordArr[3]) == 1 &&
				((coordArr[0] < coordArr[2] && coordArr[1] < coordArr[3]) || (coordArr[0] > coordArr[2] && coordArr[1] > coordArr[3])) )
	{
		return '\\';
	}
	else if ( (coordArr[0] == coordArr[2]) && abs(coordArr[1] - coordArr[3]) == 1 )
	{
		return '|';
	}
	else if ( abs(coordArr[0] - coordArr[2]) == 1  && (coordArr[1] == coordArr[3]) )
	{
		return '-';
	}
	else
	{
		return '!';
	}
}

inline auto CharMatrix::initialize( )
{
	//constexpr char FILL_CHARACTER = '-';
	constexpr unsigned int Y_AXIS_LENGTH = 20;
	constexpr unsigned int X_AXIS_LENGTH = 168;
	std::unique_ptr<CharMatrix> up2Matrix = std::make_unique<CharMatrix>( Y_AXIS_LENGTH, X_AXIS_LENGTH /*, FILL_CHARACTER*/ );

	const unsigned int& Y_DIM = up2Matrix->getY_DIM( );
	const unsigned int& X_DIM = up2Matrix->getX_DIM( );
	std::vector< std::vector<char> >& characterMatrix = up2Matrix->getCharacterMatrix( );

	for ( unsigned int row = 0; row < Y_DIM; ++row )
	{
		characterMatrix[row][X_DIM - 1] = '\n';
	}

	return up2Matrix;
}

inline unsigned int CharMatrix::getNumOfInputLines( )
{
	constexpr int MAX_NUM_OF_INPUT_LINES = 1000000;
	constexpr int MIN_NUM_OF_INPUT_LINES = 0;
	constexpr unsigned int REQUIRED_TOKENS_COUNT = 1;
	const std::vector<unsigned int> SPECIFIC_TOKENS_INDICES;

	std::string str_numOfInputLines;
	std::vector<unsigned int> uint_numOfInputLines;
	uint_numOfInputLines.reserve( REQUIRED_TOKENS_COUNT );
	
	bool isAcceptable = true;

	do
	{
		std::getline( std::cin, str_numOfInputLines );
		isAcceptable = Util::isUInt( str_numOfInputLines, REQUIRED_TOKENS_COUNT, uint_numOfInputLines,
									SPECIFIC_TOKENS_INDICES, MIN_NUM_OF_INPUT_LINES, MAX_NUM_OF_INPUT_LINES );

	} while ( !isAcceptable );

	return uint_numOfInputLines[0];
}

inline auto CharMatrix::getCoords( )
{
	const unsigned int uint_numOfInputLines = CharMatrix::getNumOfInputLines( );
	auto uniquePtr2Matrix = CharMatrix::initialize( );

	constexpr unsigned int REQUIRED_TOKENS_COUNT = 4;
	const std::vector<unsigned int> SPECIFIC_TOKENS_INDICES_FOR_Y {1, 3};
	const std::vector<unsigned int> SPECIFIC_TOKENS_INDICES_FOR_X {0, 2};

	const unsigned int MAX_ALLOWED_Y = uniquePtr2Matrix->getY_DIM( ) - 1;
	const unsigned int MAX_ALLOWED_X = uniquePtr2Matrix->getX_DIM( ) - 1;
	constexpr unsigned int MIN_ALLOWED_Y = 0;
	constexpr unsigned int MIN_ALLOWED_X = 0;

	std::string str_userEnteredCoords;
	std::string str_userEnteredCoords_dup;
	std::vector<unsigned int> uint_userEnteredCoords;
	uint_userEnteredCoords.reserve( REQUIRED_TOKENS_COUNT );

	bool isAcceptable = true;
	unsigned int coordArr[4];

	for ( unsigned int i = 0; i < uint_numOfInputLines; ++i )
	{
		do
		{
			std::getline( std::cin, str_userEnteredCoords );
			str_userEnteredCoords_dup = str_userEnteredCoords;

			isAcceptable = Util::isUInt( str_userEnteredCoords, REQUIRED_TOKENS_COUNT, uint_userEnteredCoords,
											SPECIFIC_TOKENS_INDICES_FOR_Y, MIN_ALLOWED_Y, MAX_ALLOWED_Y );

			if ( isAcceptable )
			{
				coordArr[1] = uint_userEnteredCoords[1];
				coordArr[3] = uint_userEnteredCoords[3];

				isAcceptable = Util::isUInt( str_userEnteredCoords_dup, REQUIRED_TOKENS_COUNT, uint_userEnteredCoords,
											SPECIFIC_TOKENS_INDICES_FOR_X, MIN_ALLOWED_X, MAX_ALLOWED_X );

				if ( isAcceptable )
				{
					coordArr[0] = uint_userEnteredCoords[0];
					coordArr[2] = uint_userEnteredCoords[2];
				}
			}

		} while ( !isAcceptable );

		const char ch = CharMatrix::findCharType( coordArr );
		std::vector< std::vector<char> >& characterMatrix = uniquePtr2Matrix->getCharacterMatrix( );
		
		if ( CHAR_SET.count( ch ) )
		{
			characterMatrix[coordArr[1]][coordArr[0]] = ch;
			characterMatrix[coordArr[3]][coordArr[2]] = ch;
		}
	}

	return uniquePtr2Matrix;
}

inline void CharMatrix::writeToOutput( )
{
	auto uniquePtr2Matrix = CharMatrix::getCoords( );

	const unsigned int& Y_DIM = uniquePtr2Matrix->getY_DIM( );
	const unsigned int& X_DIM = uniquePtr2Matrix->getX_DIM( );
	const std::vector< std::vector<char> >& characterMatrix = uniquePtr2Matrix->getCharacterMatrix( );

	for ( unsigned int row = 0; row < Y_DIM; ++row )
	{
		for ( unsigned int col = 0; col < X_DIM; ++col )
		{
			std::cout << characterMatrix[row][col];
		}
	}
}
