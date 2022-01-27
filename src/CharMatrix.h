
#pragma once

#include "pch.h"


namespace peyknowruzi
{

inline constexpr int default_y_axis_len { 20 };
inline constexpr int default_x_axis_len { 20 };
inline constexpr char default_fill_character { ' ' };
inline constexpr std::streamsize default_buffer_size { 169 };
inline constexpr std::size_t cartesian_components_count { 4 };

class CharMatrix
{
private:
	enum AllowedChars : char
	{
		ForwardSlash = '/',
		BackSlash = '\\',
		VerticalSlash = '|',
		Dash = '-'
	};

public:
	CharMatrix( const int Y_AxisLen = default_y_axis_len, const int X_AxisLen = default_x_axis_len,
				const char fillCharacter = default_fill_character );
	CharMatrix( CharMatrix&& rhs ) noexcept;
	CharMatrix& operator=( CharMatrix&& rhs ) noexcept;

	const int& getY_AxisLen( ) const;
	const int& getX_AxisLen( ) const;
	const char& getFillCharacter( ) const;
	std::vector< std::vector<char> >& getCharacterMatrix( ) const;
	void setY_AxisLen( const int Y_AxisLen );
	void setX_AxisLen( const int X_AxisLen );
	void setFillCharacter( const char fillCharacter );
	void setCharacterMatrix( const std::array<int, cartesian_components_count>& coordsOfChar ) const;

	bool validateEnteredCoords( const std::array<char, default_buffer_size>& str_enteredCoords,
								std::array<int, cartesian_components_count>& int_enteredCoords ) const;
	static bool validateEnteredMatrixAttributes( const std::array<char, default_buffer_size>& str_enteredMatrixAttributes,
												 std::tuple<int, int, char>& tuple_enteredMatrixAttributes );
	int getNumOfInputLines( ) const;
	static auto getMatrixAttributes( );
	void getCoords( ) const;
	void writeToOutput( ) const;

	static std::optional<AllowedChars> processCoordsToObtainCharType( const std::array<int, cartesian_components_count>& coordsOfChar );
	static auto createCharMatrix( const int Y_AxisLen = default_y_axis_len, const int X_AxisLen = default_x_axis_len,
								  const char fillCharacter = default_fill_character );
	static void initialize( );
	static void runScript( );

private:
	int m_Y_AxisLen;
	int m_X_AxisLen;
	char m_fillCharacter;
	mutable std::vector< std::vector<char> > m_characterMatrix;

	inline static const std::unordered_set< AllowedChars > chars_for_drawing { ForwardSlash, BackSlash, VerticalSlash, Dash };
};

}
