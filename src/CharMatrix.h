
#pragma once

#include "Util.h"
#include "pch.h"

static constexpr int MIN_ALLOWED_Y_DIM { 0 };
static constexpr int MIN_ALLOWED_X_DIM { 1 };
static constexpr int MAX_ALLOWED_Y_DIM { 50 };
static constexpr int MAX_ALLOWED_X_DIM { 168 };
static constexpr int DEFAULT_X_DIM { 20 };
static constexpr int DEFAULT_Y_DIM { 20 };
static constexpr char DEFAULT_FILL_CHARACTER { ' ' };
static constexpr std::streamsize DEFAULT_BUFFER_SIZE { 169 };
static constexpr size_t CARTESIAN_COMPONENTS_COUNT { 4 };

class CharMatrix
{
public:
	inline CharMatrix( );
	inline CharMatrix( const int& Y_DIM, const int& X_DIM, const char fillCharacter = DEFAULT_FILL_CHARACTER );
	inline ~CharMatrix( ) = default;
	inline CharMatrix( const CharMatrix& ) = delete;
	inline CharMatrix& operator=( const CharMatrix& ) = delete;
	inline CharMatrix( CharMatrix&& rhs ) noexcept;
	inline CharMatrix& operator=( CharMatrix&& rhs ) noexcept;

	inline const int& getY_DIM( ) const;
	inline const int& getX_DIM( ) const;
	inline const char& getFillCharacter( ) const;
	inline std::vector< std::vector<char> >& getCharacterMatrix( ) const;
	inline void setY_DIM( const int& Y_DIM );
	inline void setX_DIM( const int& X_DIM );
	inline void setFillCharacter( const char& fillCharacter );
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
	char _fillCharacter;
	mutable std::vector< std::vector<char> > _characterMatrix;
	inline static const std::unordered_set<char> CHAR_SET { '/', '\\', '|', '-' };

	friend class Invalid_Fill_Character_Exception;
	friend class Invalid_Y_Axis_Len_Exception;
	friend class Invalid_X_Axis_Len_Exception;
};
