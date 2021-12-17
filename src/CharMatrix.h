
#pragma once

#include "pch.h"


namespace peyknowruzi
{

inline constexpr int DEFAULT_Y_AXIS_LEN { 20 };
inline constexpr int DEFAULT_X_AXIS_LEN { 20 };
inline constexpr char DEFAULT_FILL_CHARACTER { ' ' };
inline constexpr std::streamsize DEFAULT_BUFFER_SIZE { 169 };
inline constexpr std::size_t CARTESIAN_COMPONENTS_COUNT { 4 };

class CharMatrix
{
public:
	inline CharMatrix( );
	inline CharMatrix( const int Y_AxisLen, const int X_AxisLen, const char fillCharacter );
	inline ~CharMatrix( ) = default;
	inline CharMatrix( const CharMatrix& ) = delete;
	inline CharMatrix& operator=( const CharMatrix& ) = delete;
	inline CharMatrix( CharMatrix&& rhs ) noexcept;
	inline CharMatrix& operator=( CharMatrix&& rhs ) noexcept;

	inline const int& getY_AxisLen( ) const;
	inline const int& getX_AxisLen( ) const;
	inline const char& getFillCharacter( ) const;
	inline std::vector< std::vector<char> >& getCharacterMatrix( ) const;
	void setY_AxisLen( const int Y_AxisLen );
	void setX_AxisLen( const int X_AxisLen );
	void setFillCharacter( const char fillCharacter );
	inline void setCharacterMatrix( const std::array<int, CARTESIAN_COMPONENTS_COUNT>& coordsOfChar ) const;

	bool validateEnteredCoords( const std::array<char, DEFAULT_BUFFER_SIZE>& str_enteredCoords,
								std::array<int, CARTESIAN_COMPONENTS_COUNT>& int_enteredCoords ) const;
	static bool validateEnteredMatrixAttributes( const std::array<char, DEFAULT_BUFFER_SIZE>& str_enteredMatrixAttributes,
												 std::tuple<int, int, char>& tuple_enteredMatrixAttributes );
	int getNumOfInputLines( ) const;
	static auto getMatrixAttributes( );
	void getCoords( ) const;
	inline void writeToOutput( ) const;

	inline static char processCoordsToObtainCharType( const std::array<int, CARTESIAN_COMPONENTS_COUNT>& coordsOfChar );
	static auto createCharMatrix( const int Y_AxisLen = DEFAULT_Y_AXIS_LEN, const int X_AxisLen = DEFAULT_X_AXIS_LEN,
								  const char fillCharacter = DEFAULT_FILL_CHARACTER );
	inline static void initialize( );
	static void launch( );

private:
	int m_Y_AxisLen;
	int m_X_AxisLen;
	char m_fillCharacter;
	mutable std::vector< std::vector<char> > m_characterMatrix;
	inline static const std::unordered_set<char> CHAR_SET { '/', '\\', '|', '-' };
};

}
