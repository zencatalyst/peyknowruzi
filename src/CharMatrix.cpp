
#include "CharMatrix.h"



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

inline unsigned int CharMatrix::getNumOfInputLines( const unsigned int& Y_DIM, const unsigned int& X_DIM )
{
	const int MAX_NUM_OF_INPUT_LINES = ( Y_DIM * X_DIM ) / 2 ;
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
	auto uniquePtr2Matrix = CharMatrix::initialize( );
	const unsigned int uint_numOfInputLines = CharMatrix::getNumOfInputLines(
										uniquePtr2Matrix->getY_DIM( ),
										uniquePtr2Matrix->getX_DIM( ) );

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

void CharMatrix::writeToOutput( )
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
