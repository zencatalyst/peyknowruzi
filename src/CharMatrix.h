
#pragma once

#include "Util.h"
#include "pch.h"


static constexpr int DEFAULT_X_DIM { 20 };
static constexpr int DEFAULT_Y_DIM { 20 };
static constexpr char DEFAULT_FILL_CHARACTER { ' ' };
static constexpr std::streamsize DEFAULT_BUFFER_SIZE { 169 };
static constexpr size_t CARTESIAN_COMPONENTS_COUNT { 4 };

class CharMatrix
{
public:
	inline CharMatrix( );
	inline CharMatrix( const int& Y_DIM, const int& X_DIM, const char FILL_CHARACTER = DEFAULT_FILL_CHARACTER );
	inline ~CharMatrix( ) = default;
	inline CharMatrix( const CharMatrix& ) = delete;
	inline CharMatrix& operator=( const CharMatrix& ) = delete;
	inline CharMatrix( CharMatrix&& rhs ) noexcept;
	inline CharMatrix& operator=( CharMatrix&& rhs ) noexcept;

	inline const int& getY_DIM( ) const;
	inline const int& getX_DIM( ) const;
	inline std::vector< std::vector<char> >& getCharacterMatrix( ) const;
	inline void setCharacterMatrix( const int (&coordsOfChar)[CARTESIAN_COMPONENTS_COUNT] ) const;
	inline bool validateUserEnteredCoords( const char (&str_userEnteredCoords)[DEFAULT_BUFFER_SIZE],
											int (&int_userEnteredCoords)[CARTESIAN_COMPONENTS_COUNT] ) const;

	inline int getNumOfInputLines( ) const;
	inline void getCoords( ) const;
	inline void writeToOutput( ) const;

	inline static char findCharType( const int (&coordsOfChar)[CARTESIAN_COMPONENTS_COUNT] );
	inline static auto initialize( );
	static void launch( );

private:
	int _Y_DIM;
	int _X_DIM;
	mutable std::vector< std::vector<char> > _characterMatrix;
	inline static const std::unordered_set<char> CHAR_SET { '/', '\\', '|', '-' };
};
