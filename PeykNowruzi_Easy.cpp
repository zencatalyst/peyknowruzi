// PeykNowruzi, easy implementation ( multi platform )
// repo available at https://github.com/Kasra-coder/magical-creations


#include <iostream>
#include <vector>
#include <memory>


class CharMatrix
{
public:
	inline CharMatrix( );
	inline CharMatrix( const int& Y_DIM, const int& X_DIM );
	inline ~CharMatrix( ) = default;
	inline CharMatrix( const CharMatrix& ) = delete;
	inline CharMatrix& operator=( const CharMatrix& ) = delete;
	inline CharMatrix( CharMatrix&& rhs ) noexcept;
	inline CharMatrix& operator=( CharMatrix&& rhs ) noexcept;

	inline const int& getY_DIM( ) const;
	inline const int& getX_DIM( ) const;
	inline std::vector< std::vector<char> >& getCharacterMatrix( );

	inline static char findCharType( const int(&coordArr)[4] );
	inline static auto initialize( const char& ch );
	inline static auto getCoords( );
	inline static void writeToOutput( );

private:
	int _Y_DIM;
	int _X_DIM;
	std::vector< std::vector<char> > _characterMatrix;
};

int main()
{
	CharMatrix::writeToOutput( );

	return 0;
}

inline CharMatrix::CharMatrix( )
	:_Y_DIM( 20 ), _X_DIM( 20 )
{
	_characterMatrix.reserve( _Y_DIM );

	for ( int row = 0; row < _Y_DIM; ++row )
	{
		_characterMatrix.push_back( std::vector<char>( _X_DIM ) );
	}
}

inline CharMatrix::CharMatrix( const int& Y_DIM, const int& X_DIM )
	: _Y_DIM( Y_DIM ), _X_DIM( X_DIM )
{
	_characterMatrix.reserve( _Y_DIM );

	for ( int row = 0; row < _Y_DIM; ++row )
	{
		_characterMatrix.push_back( std::vector<char>( _X_DIM ) );
	}
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

inline char CharMatrix::findCharType( const int(&coordArr)[4] )
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

inline auto CharMatrix::initialize( const char& ch )
{
	const unsigned Y_AXIS_LENGTH = 20;
	const unsigned X_AXIS_LENGTH = 168;
	std::unique_ptr<CharMatrix> up2Matrix = std::make_unique<CharMatrix>( Y_AXIS_LENGTH, X_AXIS_LENGTH );

	const int& Y_DIM = up2Matrix->getY_DIM( );
	const int& X_DIM = up2Matrix->getX_DIM( );
	std::vector< std::vector<char> >& characterMatrix = up2Matrix->getCharacterMatrix( );

	for ( int row = 0; row < Y_DIM; ++row )
	{
		for ( int col = 0; col < X_DIM - 1; ++col )
		{
			characterMatrix[row][col] = ch;
		}
		characterMatrix[row][X_DIM - 1] = '\n';
	}

	return up2Matrix;
}

inline auto CharMatrix::getCoords( )
{
	const char fillCharacter = ' ';
	auto uniquePtr2Matrix = CharMatrix::initialize( fillCharacter );

	int coordArr[4] { 0, 0, 0, 0 };
	const int MAX_ALLOWED_Y = uniquePtr2Matrix->getY_DIM( ) - 1;
	const int MAX_ALLOWED_X = uniquePtr2Matrix->getX_DIM( ) - 1;
	bool isAcceptable = true;

	unsigned int numOfInputLines;
	std::cin >> numOfInputLines;

	for ( unsigned int i = 0; i < numOfInputLines; ++i )
	{
		do
		{
			std::cin >> coordArr[0] >> coordArr[1] >> coordArr[2] >> coordArr[3];
			if ( coordArr[0] > MAX_ALLOWED_X || coordArr[2] > MAX_ALLOWED_X ||
					coordArr[1] > MAX_ALLOWED_Y || coordArr[3] > MAX_ALLOWED_Y )
			{
				isAcceptable = false;
			}
			else
			{
				isAcceptable = true;
			}
		} while ( !isAcceptable );

		char ch = CharMatrix::findCharType( coordArr );
		std::vector< std::vector<char> >& characterMatrix = uniquePtr2Matrix->getCharacterMatrix( );
		if ( ch == '/' )
		{
			characterMatrix[coordArr[1]][coordArr[0]] = '/';
			characterMatrix[coordArr[3]][coordArr[2]] = '/';
		}
		else if ( ch == '\\' )
		{
			characterMatrix[coordArr[1]][coordArr[0]] = '\\';
			characterMatrix[coordArr[3]][coordArr[2]] = '\\';
		}
		else if ( ch == '|' )
		{
			characterMatrix[coordArr[1]][coordArr[0]] = '|';
			characterMatrix[coordArr[3]][coordArr[2]] = '|';
		}
		else if ( ch == '-' )
		{
			characterMatrix[coordArr[1]][coordArr[0]] = '-';
			characterMatrix[coordArr[3]][coordArr[2]] = '-';
		}
		else
		{
			// pass (do nothing!)
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
