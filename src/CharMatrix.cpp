
#define PN_DEBUG 0
#define GUI_MODE 0

#if PN_DEBUG == 1
#define LOG(x) std::cout << (x) << std::endl
#define WAIT std::cin.get( )
#else
#define LOG(x)
#define WAIT
#endif


#include "CharMatrix.h"


class Invalid_Fill_Character_Exception : public std::exception
{
	virtual const char* what( ) const throw( )
	{
		size_t elementCount { };
		std::stringstream ss;

		ss << "Invalid_Fill_Character_Exception: The 'fill character' is not allowed to be one of the following characters: { ";

		for ( auto it = CharMatrix::CHAR_SET.cbegin( ); it != CharMatrix::CHAR_SET.cend( ); ++it )
		{
			++elementCount;
			if ( elementCount == CharMatrix::CHAR_SET.size( ) ) { ss << "'" << *it << "' }"; }
			else { ss << "'" << *it << "', "; }
		}

		const std::string TEMP_MSG_STRING { ss.str( ) };

		char* INVALID_FILL_CHARACTER_EXCEPTION_MSG = new char[ TEMP_MSG_STRING.length( ) + 1 ];
		std::strcpy( INVALID_FILL_CHARACTER_EXCEPTION_MSG, TEMP_MSG_STRING.c_str( ) );

		return INVALID_FILL_CHARACTER_EXCEPTION_MSG;
	}

} Invalid_Fill_Char_Exc;

class Invalid_Y_Axis_Len_Exception : public std::exception
{
	virtual const char* what( ) const throw( )
	{
		std::stringstream ss;

		ss << "Invalid_Y_Axis_Len_Exception: The 'Y-axis length' is not allowed to be greater than " <<
				MAX_ALLOWED_Y_DIM << " and lesser than " << MIN_ALLOWED_Y_DIM << ".";

		const std::string TEMP_MSG_STRING { ss.str( ) };

		char* Invalid_Y_Axis_Len_Exception_Msg = new char[ TEMP_MSG_STRING.length( ) + 1 ];
		std::strcpy( Invalid_Y_Axis_Len_Exception_Msg, TEMP_MSG_STRING.c_str( ) );

		return Invalid_Y_Axis_Len_Exception_Msg;
	}

} Invalid_Y_Axis_Len_Exc;

class Invalid_X_Axis_Len_Exception : public std::exception
{
	virtual const char* what( ) const throw( )
	{
		std::stringstream ss;

		ss << "Invalid_X_Axis_Len_Exception: The 'X-axis length' is not allowed to be greater than " <<
				MAX_ALLOWED_X_DIM << " and lesser than " << MIN_ALLOWED_X_DIM << ".";

		const std::string TEMP_MSG_STRING { ss.str( ) };

		char* Invalid_X_Axis_Len_Exception_Msg = new char[ TEMP_MSG_STRING.length( ) + 1 ];
		std::strcpy( Invalid_X_Axis_Len_Exception_Msg, TEMP_MSG_STRING.c_str( ) );

		return Invalid_X_Axis_Len_Exception_Msg;
	}

} Invalid_X_Axis_Len_Exc;


inline CharMatrix::CharMatrix( )
	:_Y_DIM( DEFAULT_Y_DIM ), _X_DIM( DEFAULT_X_DIM ), _fillCharacter( DEFAULT_FILL_CHARACTER ),
	_characterMatrix( DEFAULT_Y_DIM, std::vector<char>( DEFAULT_X_DIM, DEFAULT_FILL_CHARACTER ) )
{
}

inline CharMatrix::CharMatrix( const int& Y_DIM, const int& X_DIM, const char fillCharacter )
	: _Y_DIM( Y_DIM ), _X_DIM( X_DIM ), _fillCharacter( fillCharacter ),
	_characterMatrix( Y_DIM, std::vector<char>( X_DIM, fillCharacter ) )
{
}

inline CharMatrix::CharMatrix( CharMatrix&& rhs ) noexcept
	:_Y_DIM( rhs._Y_DIM ), _X_DIM( rhs._X_DIM ), _fillCharacter( rhs._fillCharacter ),
	_characterMatrix( std::move( rhs._characterMatrix ) )
{
	rhs._Y_DIM = 0;
	rhs._X_DIM = 0;
	rhs._fillCharacter = 0;
}

inline CharMatrix& CharMatrix::operator=( CharMatrix&& rhs ) noexcept
{
	if ( this != &rhs )
	{
		_characterMatrix = std::move( rhs._characterMatrix );
		_Y_DIM = rhs._Y_DIM;
		_X_DIM = rhs._X_DIM;
		_fillCharacter = rhs._fillCharacter;

		rhs._Y_DIM = 0;
		rhs._X_DIM = 0;
		rhs._fillCharacter = 0;
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

inline const char& CharMatrix::getFillCharacter( ) const
{
	return _fillCharacter;
}

inline std::vector< std::vector<char> >& CharMatrix::getCharacterMatrix( ) const
{
	return _characterMatrix;
}

inline void CharMatrix::setY_DIM( const int& Y_DIM )
{
	if ( Y_DIM == getY_DIM( ) ) { return; }

	if ( Y_DIM > MAX_ALLOWED_Y_DIM || Y_DIM < MIN_ALLOWED_Y_DIM )
	{
		try
		{
			throw Invalid_Y_Axis_Len_Exc;
		}
		catch ( const std::exception& e )
		{
			LOG( e.what( ) );
			return;
		}
	}

	getCharacterMatrix( ).resize( Y_DIM, std::vector<char>( getX_DIM( ), getFillCharacter( ) ) );

	if ( Y_DIM > getY_DIM( ) )
	{
		for ( int i = getY_DIM( ); i < Y_DIM; ++i )
		{
			auto& row = getCharacterMatrix( )[i];

			row[ getX_DIM( ) - 1 ] = '\n';
		}
	}

	_Y_DIM = { Y_DIM };
}

inline void CharMatrix::setX_DIM( const int& X_DIM )
{
	if ( X_DIM == getX_DIM( ) ) { return; }

	if ( X_DIM > MAX_ALLOWED_X_DIM || X_DIM < MIN_ALLOWED_X_DIM )
	{
		try
		{
			throw Invalid_X_Axis_Len_Exc;
		}
		catch ( const std::exception& e )
		{
			LOG( e.what( ) );
			return;
		}
	}

	for ( auto it = getCharacterMatrix( ).begin( ); it != getCharacterMatrix( ).end(); ++it )
	{
		auto& row = *it;

		row.resize( X_DIM, getFillCharacter( ) );
		row[X_DIM - 1] = '\n';
		if ( X_DIM > getX_DIM( ) )
		{
			row[ getX_DIM( ) - 1 ] = getFillCharacter( );
		}
	}

	_X_DIM = { X_DIM };
}

inline void CharMatrix::setFillCharacter( const char& fillCharacter )
{
	if ( fillCharacter == getFillCharacter( ) ) { return; }

	if ( CHAR_SET.count( fillCharacter ) )
	{
		try
		{
			throw Invalid_Fill_Char_Exc;
		}
		catch ( const std::exception& e )
		{
			LOG( e.what( ) );
			return;
		}
	}

	for ( int row = 0; row < getY_DIM( ); ++row )
	{
		for ( int column = 0; column < getX_DIM( ) - 1; ++column )
		{
			if ( _characterMatrix[row][column] == getFillCharacter( ) )
			{
				_characterMatrix[row][column] = fillCharacter;
			}
		}
	}

	_fillCharacter = { fillCharacter };
}

inline void CharMatrix::setCharacterMatrix( const int (&coordsOfChar)[CARTESIAN_COMPONENTS_COUNT] ) const
{
	const char ch { CharMatrix::findCharType( coordsOfChar ) };

	if ( CHAR_SET.count( ch ) )
	{
		_characterMatrix[coordsOfChar[1]][coordsOfChar[0]] = ch;
		_characterMatrix[coordsOfChar[3]][coordsOfChar[2]] = ch;
	}
}

inline bool CharMatrix::validateUserEnteredCoords( const char (&str_userEnteredCoords)[DEFAULT_BUFFER_SIZE], int (&int_userEnteredCoords)[CARTESIAN_COMPONENTS_COUNT] ) const
{
	constexpr size_t REQUIRED_TOKENS_COUNT { CARTESIAN_COMPONENTS_COUNT };
	const std::vector<int> SPECIFIC_TOKENS_INDICES_FOR_Y { 1, 3 };
	const std::vector<int> SPECIFIC_TOKENS_INDICES_FOR_X { 0, 2 };

	const int MAX_ALLOWED_Y { getY_DIM( ) - 1 };
	const int MAX_ALLOWED_X { getX_DIM( ) - 1 };
	constexpr int MIN_ALLOWED_Y { 0 };
	constexpr int MIN_ALLOWED_X { 0 };

	const bool isValid { Util::convert_str_to_valid_ints( str_userEnteredCoords, int_userEnteredCoords, REQUIRED_TOKENS_COUNT,
							SPECIFIC_TOKENS_INDICES_FOR_Y, MIN_ALLOWED_Y, MAX_ALLOWED_Y ) &&
						   Util::convert_str_to_valid_ints( str_userEnteredCoords, int_userEnteredCoords, REQUIRED_TOKENS_COUNT,
							SPECIFIC_TOKENS_INDICES_FOR_X, MIN_ALLOWED_X, MAX_ALLOWED_X ) ? true : false };

	return isValid;
}

inline char CharMatrix::findCharType( const int (&coordsOfChar)[CARTESIAN_COMPONENTS_COUNT] )
{
	if ( abs(coordsOfChar[0] - coordsOfChar[2]) == 1 && abs(coordsOfChar[1] - coordsOfChar[3]) == 1 &&
		((coordsOfChar[0] < coordsOfChar[2] && coordsOfChar[1] > coordsOfChar[3]) ||
		 (coordsOfChar[0] > coordsOfChar[2] && coordsOfChar[1] < coordsOfChar[3])) )
	{
		return '/';
	}
	else if ( abs(coordsOfChar[0] - coordsOfChar[2]) == 1 && abs(coordsOfChar[1] - coordsOfChar[3]) == 1 &&
		((coordsOfChar[0] < coordsOfChar[2] && coordsOfChar[1] < coordsOfChar[3]) ||
		 (coordsOfChar[0] > coordsOfChar[2] && coordsOfChar[1] > coordsOfChar[3])) )
	{
		return '\\';
	}
	else if ( (coordsOfChar[0] == coordsOfChar[2]) && abs(coordsOfChar[1] - coordsOfChar[3]) == 1 )
	{
		return '|';
	}
	else if ( abs(coordsOfChar[0] - coordsOfChar[2]) == 1  && (coordsOfChar[1] == coordsOfChar[3]) )
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
	// constexpr char FILL_CHARACTER = '#';
	constexpr int Y_AXIS_LENGTH { 20 };
	constexpr int X_AXIS_LENGTH { 168 };

	constexpr int MAX_NUM_OF_INPUT_LINES { ( Y_AXIS_LENGTH * X_AXIS_LENGTH ) / 2 };

	static_assert( MAX_NUM_OF_INPUT_LINES >= 0 && MAX_NUM_OF_INPUT_LINES <= INT_MAX
					, "(Y_AXIS_LENGTH * X_AXIS_LENGTH ) / 2 can not be greater than INT_MAX or less than 0" );

	std::unique_ptr<CharMatrix> uniquePtr2Matrix { std::make_unique<CharMatrix>( Y_AXIS_LENGTH, X_AXIS_LENGTH /*, FILL_CHARACTER*/ ) };

	std::vector< std::vector<char> >& characterMatrix { uniquePtr2Matrix->getCharacterMatrix( ) };

	for ( int row = 0; row < Y_AXIS_LENGTH; ++row )
	{
		characterMatrix[row][X_AXIS_LENGTH - 1] = '\n';
	}

	return uniquePtr2Matrix;
}

inline int CharMatrix::getNumOfInputLines( ) const
{
	const int MAX_NUM_OF_INPUT_LINES { ( getY_DIM( ) * getX_DIM( ) ) / 2 };
	constexpr int MIN_NUM_OF_INPUT_LINES { 0 };

	static_assert( MIN_NUM_OF_INPUT_LINES >= 0 && MIN_NUM_OF_INPUT_LINES <= INT_MAX
					, "MIN_NUM_OF_INPUT_LINES can not be greater than INT_MAX or less than 0" );

	constexpr size_t REQUIRED_TOKENS_COUNT { 1 };
	const std::vector<int> SPECIFIC_TOKENS_INDICES;

	constexpr std::streamsize streamSize { DEFAULT_BUFFER_SIZE };
	char str_numOfInputLines[ streamSize ] { };
	int int_numOfInputLines[ REQUIRED_TOKENS_COUNT ] { };
	
	bool isValid { false };

	do
	{
		Util::getCharInput( str_numOfInputLines, streamSize );
		
		isValid = { Util::convert_str_to_valid_ints( str_numOfInputLines, int_numOfInputLines, REQUIRED_TOKENS_COUNT,
									SPECIFIC_TOKENS_INDICES, MIN_NUM_OF_INPUT_LINES, MAX_NUM_OF_INPUT_LINES ) };
	} while ( !isValid );

	return int_numOfInputLines[0];
}

inline void CharMatrix::getCoords( ) const
{
	const int numOfInputLines { getNumOfInputLines( ) };

	constexpr std::streamsize streamSize { DEFAULT_BUFFER_SIZE };
	char str_userEnteredCoords[ streamSize ] { };

	constexpr size_t REQUIRED_TOKENS_COUNT { CARTESIAN_COMPONENTS_COUNT };
	int int_userEnteredCoords[ REQUIRED_TOKENS_COUNT ] { };

	for ( int i = 0; i < numOfInputLines; ++i )
	{
		bool isAcceptable { false };

		do
		{
			Util::getCharInput( str_userEnteredCoords, streamSize );

			isAcceptable = { validateUserEnteredCoords( str_userEnteredCoords, int_userEnteredCoords ) };

		} while ( !isAcceptable );

		setCharacterMatrix( int_userEnteredCoords );
	}
}

inline void CharMatrix::writeToOutput( ) const
{
	const int& Y_DIM { getY_DIM( ) };
	const int& X_DIM { getX_DIM( ) };
	const std::vector< std::vector<char> >& characterMatrix { getCharacterMatrix( ) };

	for ( int row = 0; row < Y_DIM; ++row )
	{
		for ( int col = 0; col < X_DIM; ++col )
		{
			std::cout << characterMatrix[row][col];
		}
	}

	LOG( "\nFinished." );
	WAIT;
}

void CharMatrix::launch( )
{
	const std::unique_ptr<CharMatrix> uniquePtr2Matrix { CharMatrix::initialize( ) };

	uniquePtr2Matrix->getCoords( );
	uniquePtr2Matrix->writeToOutput( );
}
