
#pragma once

#include "pch.h"


namespace peyknowruzi
{

inline constexpr std::uint32_t default_y_axis_len { 20 };
inline constexpr std::uint32_t default_x_axis_len { 20 };
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
	CharMatrix( const std::uint32_t Y_AxisLen = default_y_axis_len,
				const std::uint32_t X_AxisLen = default_x_axis_len,
				const char fillCharacter = default_fill_character );
	CharMatrix( CharMatrix&& rhs ) noexcept;
	CharMatrix& operator=( CharMatrix&& rhs ) noexcept;

	const std::uint32_t& getY_AxisLen( ) const noexcept;
	const std::uint32_t& getX_AxisLen( ) const noexcept;
	const char& getFillCharacter( ) const noexcept;
	const std::vector< std::vector<char> >& getCharacterMatrix( ) const noexcept;
	void setY_AxisLen( const std::uint32_t Y_AxisLen );
	void setX_AxisLen( const std::uint32_t X_AxisLen );
	void setFillCharacter( const char fillCharacter );
	void setCharacterMatrix( const std::array<std::uint32_t, cartesian_components_count>& coordsOfChar );

	bool validateEnteredCoords( const std::array<char, default_buffer_size>& str_enteredCoords,
								std::array<std::uint32_t, cartesian_components_count>& int_enteredCoords_OUT ) const;

	static bool validateEnteredMatrixAttributes( const std::array<char, default_buffer_size>& str_enteredMatrixAttributes,
												 std::tuple<std::uint32_t, std::uint32_t, char>& tuple_enteredMatrixAttributes_OUT );
	static std::optional<AllowedChars>
	processCoordsToObtainCharType( const std::array<std::uint32_t, cartesian_components_count>& coordsOfChar ) noexcept;

	std::size_t getNumOfInputLines( ) const;
	static auto getMatrixAttributes( );
	void getCoords( );
	void writeToOutput( ) const;

	static void initialize( );
	static void runScript( );

private:
	std::uint32_t m_Y_AxisLen;
	std::uint32_t m_X_AxisLen;
	char m_fillCharacter;
	std::vector< std::vector<char> > m_characterMatrix;

	inline static const std::unordered_set< AllowedChars > chars_for_drawing { ForwardSlash, BackSlash, VerticalSlash, Dash };
};

}
