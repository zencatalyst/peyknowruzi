// PeykNowruzi, easy implementation ( multi platform )
// repo available at https://github.com/Kasra-coder/magical-creations


#include <iostream>
#include <vector>
#include <memory>
#include <unordered_set>
#include <climits>


class CharMatrix
{
public:
	inline CharMatrix( );
	inline CharMatrix( const int& Y_DIM, const int& X_DIM, const char FILL_CHARACTER = ' ' );
	inline ~CharMatrix( ) = default;
	inline CharMatrix( const CharMatrix& ) = delete;
	inline CharMatrix& operator=( const CharMatrix& ) = delete;
	inline CharMatrix( CharMatrix&& rhs ) noexcept;
	inline CharMatrix& operator=( CharMatrix&& rhs ) noexcept;

	inline const int& getY_DIM( ) const;
	inline const int& getX_DIM( ) const;
	inline std::vector< std::vector<char> >& getCharacterMatrix( );

	inline static char findCharType( const long int(&coordArr)[4] );
	inline static auto initialize( );
	inline static unsigned long int getNumOfInputLines( );
	inline static auto getCoords( );
	inline static void writeToOutput( );

private:
	int _Y_DIM;
	int _X_DIM;
	std::vector< std::vector<char> > _characterMatrix;
	inline static const std::unordered_set<char> CHAR_SET { '/', '\\', '|', '-' };
};

class Util
{
public:
	inline static auto isLongInt( const std::string& inputStr, const long int minValue = LONG_MIN, const long int maxValue = LONG_MAX );
};

int main()
{
	CharMatrix::writeToOutput( );

	return 0;
}

inline auto Util::isLongInt( const std::string& inputStr, const long int minValue, const long int maxValue )
{
	size_t pos = 0;
	bool isAcceptable = true;
	long int resultLongInt = 0;

	try
	{
		resultLongInt = std::stol( inputStr, &pos, 10 );

		if ( pos != inputStr.length( ) )
		{
			isAcceptable = false;
		}
		if ( isAcceptable )
		{
			isAcceptable = ( (resultLongInt > maxValue || resultLongInt < minValue) ) ? false : true;
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

	struct retVals
	{
		bool _isAcceptable;
		long int _resultLongInt;
	};

	return retVals { isAcceptable, resultLongInt };
}

inline CharMatrix::CharMatrix( )
	:_Y_DIM( 20 ), _X_DIM( 20 ), _characterMatrix( 20, std::vector<char>( 20, ' ' ) )
{
}

inline CharMatrix::CharMatrix( const int& Y_DIM, const int& X_DIM, const char FILL_CHARACTER )
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

inline const int& CharMatrix::getY_DIM( ) const
{
	return _Y_DIM;
}

inline const int& CharMatrix::getX_DIM( ) const
{
	return _X_DIM;
}

inline std::vector< std::vector<char> >& CharMatrix::getCharacterMatrix( )
{
	return _characterMatrix;
}

inline char CharMatrix::findCharType( const long int(&coordArr)[4] )
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

	const int& Y_DIM = up2Matrix->getY_DIM( );
	const int& X_DIM = up2Matrix->getX_DIM( );
	std::vector< std::vector<char> >& characterMatrix = up2Matrix->getCharacterMatrix( );

	for ( int row = 0; row < Y_DIM; ++row )
	{
		characterMatrix[row][X_DIM - 1] = '\n';
	}

	return up2Matrix;
}

inline unsigned long int CharMatrix::getNumOfInputLines( )
{
	constexpr long int MAX_NUM_OF_INPUT_LINES = 1000000;
	constexpr long int MIN_NUM_OF_INPUT_LINES = 0;
	std::string str_numOfInputLines;
	bool isAcceptable = true;
	long int li_numOfInputLines = 0;

	do
	{
		std::getline( std::cin, str_numOfInputLines );
		auto retValues = Util::isLongInt( str_numOfInputLines, MIN_NUM_OF_INPUT_LINES, MAX_NUM_OF_INPUT_LINES );
		isAcceptable = retValues._isAcceptable;
		li_numOfInputLines = retValues._resultLongInt;

	} while ( !isAcceptable );

	return ( unsigned long int )li_numOfInputLines;
}

inline auto CharMatrix::getCoords( )
{
	const unsigned long int uli_numOfInputLines = CharMatrix::getNumOfInputLines( );
	auto uniquePtr2Matrix = CharMatrix::initialize( );

	size_t pos = 0;
	bool isAcceptable = true;
	std::string str_coord;
	long int coordArr[4] { 0, 0, 0, 0 };
	const long int MAX_ALLOWED_Y = uniquePtr2Matrix->getY_DIM( ) - 1;
	const long int MAX_ALLOWED_X = uniquePtr2Matrix->getX_DIM( ) - 1;

	for ( unsigned long int i = 0; i < uli_numOfInputLines; ++i )
	{
		do
		{
			isAcceptable = true;

			std::cin >> coordArr[0] >> coordArr[1] >> coordArr[2] >> coordArr[3];

			isAcceptable = ( coordArr[0] > MAX_ALLOWED_X || coordArr[2] > MAX_ALLOWED_X ||
					coordArr[1] > MAX_ALLOWED_Y || coordArr[3] > MAX_ALLOWED_Y ) ? false : true ;

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

	const int& Y_DIM = uniquePtr2Matrix->getY_DIM( );
	const int& X_DIM = uniquePtr2Matrix->getX_DIM( );
	const std::vector< std::vector<char> >& characterMatrix = uniquePtr2Matrix->getCharacterMatrix( );

	for ( int row = 0; row < Y_DIM; ++row )
	{
		for ( int col = 0; col < X_DIM; ++col )
		{
			std::cout << characterMatrix[row][col];
		}
	}
}
