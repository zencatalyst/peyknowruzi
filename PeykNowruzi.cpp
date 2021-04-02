
#include <iostream>
#include <iomanip>
#include <vector>

using std::cin;
using std::cout;


class Character
{
	public:
		inline Character( );
		inline Character( const char& ch, int color = -1 );
		inline ~Character( ) = default;

		inline void setCh( const char& ch );
		inline void setVectorOfCoords( std::vector<int>& coordVec );
		inline void setColor( const int& color );

		inline const std::vector< std::vector<int> >& getVectorOfCoords(  );

		inline static char findCharType( const std::vector<int>& coordVec );
		inline void writeToConsole( );

	private:
		char _ch;
		int _color;
		std::vector< std::vector<int> > _vectorOfCoords;
};

inline void gotoxy( const int(&coordArr)[2] );

// --- main function ---
int main()
{
	system( "cls" );

	Character charForwardSlash( '/' );
	Character charBackSlash( '\\' );
	Character charVerticalSlash( '|' );
	Character charDash( '-' );

	unsigned int numOfSymbols;
	cin >> numOfSymbols;

	std::vector<int> coordVec( 4, 0 );
	for ( unsigned int i = 0; i < numOfSymbols; ++i )
	{
		cin >> coordVec[0] >> coordVec[1] >> coordVec[2] >> coordVec[3];
		char ch = Character::findCharType( coordVec );

		if ( ch == '/' )
		{
			charForwardSlash.setVectorOfCoords( coordVec );
		}
		else if ( ch == '\\' )
		{
			charBackSlash.setVectorOfCoords( coordVec );
		}
		else if ( ch == '|' )
		{
			charVerticalSlash.setVectorOfCoords( coordVec );
		}
		else if ( ch == '-' )
		{
			charDash.setVectorOfCoords( coordVec );
		}
		else
		{
			// pass (do nothing!)
		}

	}

	system( "cls" );

	charForwardSlash.writeToConsole( );
	charBackSlash.writeToConsole( );
	charVerticalSlash.writeToConsole( );
	charDash.writeToConsole( );

	cin.get();
	gotoxy( {0, 20} );
	cin.get();

	system( "cls" );

	return 0;
}

inline Character::Character( )
{
	setCh( '!' );
	setColor( -1 );
}

inline Character::Character( const char& ch, int color )
{
	setCh( ch );
	setColor( color );
}

inline void Character::setCh( const char& ch )
{
	_ch = ch;
}

inline void Character::setVectorOfCoords( std::vector<int>& coordVec )
{
	if ( _ch == '/' && (coordVec[0] > coordVec[2]) )
	{
		int temp = coordVec[0];
		coordVec[0] = coordVec[2];
		coordVec[2] = temp;

		temp = coordVec[1];
		coordVec[1] = coordVec[3];
		coordVec[3] = temp;
	}
	else if ( _ch == '\\' && (coordVec[0] > coordVec[2]) )
	{
		int temp = coordVec[0];
		coordVec[0] = coordVec[2];
		coordVec[2] = temp;

		temp = coordVec[1];
		coordVec[1] = coordVec[3];
		coordVec[3] = temp;
	}
	else if ( _ch == '|' && (coordVec[1] > coordVec[3]) )
	{
		int temp = coordVec[1];
		coordVec[1] = coordVec[3];
		coordVec[3] = temp;
	}
	else if ( _ch == '-' && (coordVec[0] > coordVec[2]) )
	{
		int temp = coordVec[0];
		coordVec[0] = coordVec[2];
		coordVec[2] = temp;
	}

	_vectorOfCoords.push_back( coordVec );
}

inline void Character::setColor( const int& color )
{
	_color = color;
}

inline const std::vector< std::vector<int> >& Character::getVectorOfCoords(  )
{
	return _vectorOfCoords;
}

inline char Character::findCharType( const std::vector<int>& coordVec )
{
	if ( abs(coordVec[0] - coordVec[2]) == 1 && abs(coordVec[1] - coordVec[3]) == 1 &&
				((coordVec[0] < coordVec[2] && coordVec[1] > coordVec[3]) || (coordVec[0] > coordVec[2] && coordVec[1] < coordVec[3])) )
	{
		return '/';
	}
	else if ( abs(coordVec[0] - coordVec[2]) == 1 && abs(coordVec[1] - coordVec[3]) == 1 &&
				((coordVec[0] < coordVec[2] && coordVec[1] < coordVec[3]) || (coordVec[0] > coordVec[2] && coordVec[1] > coordVec[3])) )
	{
		return '\\';
	}
	else if ( (coordVec[0] == coordVec[2]) && abs(coordVec[1] - coordVec[3]) == 1 )
	{
		return '|';
	}
	else if ( abs(coordVec[0] - coordVec[2]) == 1  && (coordVec[1] == coordVec[3]) )
	{
		return '-';
	}
	else
	{
		return '!';
	}
}

inline void Character::writeToConsole( )
{
	for ( const std::vector<int>& coordVec : _vectorOfCoords )
	{
		if ( _ch == '/' )
		{
			gotoxy( {coordVec[0], coordVec[1] - 1} );
			std::cout << '/';
		}
		else if ( _ch == '\\' )
		{
			gotoxy( {coordVec[0], coordVec[1]} );
			std::cout << '\\';
		}
		else if ( _ch == '|' )
		{
			gotoxy( {coordVec[0], coordVec[1]} );
			std::cout << '|';
		}
		else if ( _ch == '-' )
		{
			gotoxy( {coordVec[0], coordVec[1]} );
			std::cout << '-';
		}
		else
		{
			// pass (do nothing!)
		}
	}
}

inline void gotoxy( const int(&coordArr)[2] )
{
	printf( "%c[%d;%df", 0x1B, coordArr[1] + 1, coordArr[0] + 1);
}
