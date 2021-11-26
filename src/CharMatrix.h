
#pragma once

#include "pch.h"


namespace peyknowruzi
{

inline constexpr char DEFAULT_FILL_CHARACTER { ' ' };
inline constexpr std::streamsize DEFAULT_BUFFER_SIZE { 169 };
inline constexpr std::size_t CARTESIAN_COMPONENTS_COUNT { 4 };

class CharMatrix
{
public:
	inline CharMatrix( );
	inline CharMatrix( const int& Y_AxisLen, const int& X_AxisLen, const char fillCharacter = DEFAULT_FILL_CHARACTER );
	inline ~CharMatrix( ) = default;
	inline CharMatrix( const CharMatrix& ) = delete;
	inline CharMatrix& operator=( const CharMatrix& ) = delete;
	inline CharMatrix( CharMatrix&& rhs ) noexcept;
	inline CharMatrix& operator=( CharMatrix&& rhs ) noexcept;

	inline const int& getY_AxisLen( ) const;
	inline const int& getX_AxisLen( ) const;
	inline const char& getFillCharacter( ) const;
	inline std::vector< std::vector<char> >& getCharacterMatrix( ) const;
	void setY_AxisLen( const int& Y_AxisLen );
	void setX_AxisLen( const int& X_AxisLen );
	void setFillCharacter( const char& fillCharacter );
	inline void setCharacterMatrix( const int (&coordsOfChar)[CARTESIAN_COMPONENTS_COUNT] ) const;

	bool validateUserEnteredCoords( const char (&str_userEnteredCoords)[DEFAULT_BUFFER_SIZE],
											int (&int_userEnteredCoords)[CARTESIAN_COMPONENTS_COUNT] ) const;
	int getNumOfInputLines( ) const;
	void getCoords( ) const;
	inline void writeToOutput( ) const;

	inline static char findCharType( const int (&coordsOfChar)[CARTESIAN_COMPONENTS_COUNT] );
	static auto initialize( );
	static void launch( );

private:
	int m_Y_AxisLen;
	int m_X_AxisLen;
	char m_fillCharacter;
	mutable std::vector< std::vector<char> > m_characterMatrix;
	inline static const std::unordered_set<char> CHAR_SET { '/', '\\', '|', '-' };
};

}
