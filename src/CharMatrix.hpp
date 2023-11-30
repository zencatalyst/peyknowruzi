
// PeykNowruzi - Basic ASCII-Art Generator
// Copyright (C) 2021-2022 Kasra Hashemi

/*

 This file is part of PeykNowruzi.

 PeykNowruzi is free software: you can redistribute it and/or modify it
 under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License,
 or (at your option) any later version.

 PeykNowruzi is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty
 of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along
 with PeykNowruzi. If not, see <https://www.gnu.org/licenses/>.

*/


#pragma once

#include "pch.hpp"
#include "Util.hpp"


namespace peyknowruzi
{

inline constexpr std::streamsize default_buffer_size { 169 };

template <std::size_t unique_ID, std::unsigned_integral sizeT>
requires ( !std::is_const_v<sizeT> && !std::is_volatile_v<sizeT> )
inline constexpr sizeT CharMatrix_default_y_axis_len_value { 20 };

template <std::size_t unique_ID, std::unsigned_integral sizeT>
requires ( !std::is_const_v<sizeT> && !std::is_volatile_v<sizeT> )
inline constexpr sizeT CharMatrix_default_x_axis_len_value { 20 };

template <std::size_t unique_ID, util::Character charT>
requires ( !std::is_const_v<charT> && !std::is_volatile_v<charT> )
inline constexpr charT CharMatrix_default_fill_character_value { ' ' };

template <std::size_t unique_ID, std::unsigned_integral sizeT>
requires ( !std::is_const_v<sizeT> && !std::is_volatile_v<sizeT> )
inline constexpr sizeT CharMatrix_min_allowed_y_axis_len_value { 1 };

template <std::size_t unique_ID, std::unsigned_integral sizeT>
requires ( !std::is_const_v<sizeT> && !std::is_volatile_v<sizeT> )
inline constexpr sizeT CharMatrix_min_allowed_x_axis_len_value { 2 };

template <std::size_t unique_ID, std::unsigned_integral sizeT>
requires ( !std::is_const_v<sizeT> && !std::is_volatile_v<sizeT> )
inline constexpr sizeT CharMatrix_max_allowed_y_axis_len_value { 100 };

template <std::size_t unique_ID, std::unsigned_integral sizeT>
requires ( !std::is_const_v<sizeT> && !std::is_volatile_v<sizeT> )
inline constexpr sizeT CharMatrix_max_allowed_x_axis_len_value { 200 };


template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator = std::allocator<charT> >
requires ( !std::is_const_v<sizeT> && !std::is_volatile_v<sizeT> &&
		   !std::is_const_v<charT> && !std::is_volatile_v<charT> )
class CharMatrix
{
public:
	using size_type      = sizeT;
	using value_type     = charT;
	using allocator_type = Allocator;

public:
	inline static constexpr size_type
	default_y_axis_len { CharMatrix_default_y_axis_len_value< unique_ID, size_type > };

	inline static constexpr size_type
	default_x_axis_len { CharMatrix_default_x_axis_len_value< unique_ID, size_type > };

	inline static constexpr value_type
	default_fill_character { CharMatrix_default_fill_character_value< unique_ID, value_type > };

	inline static constexpr size_type
	min_allowed_y_axis_len { CharMatrix_min_allowed_y_axis_len_value< unique_ID, size_type > };

	inline static constexpr size_type
	min_allowed_x_axis_len { CharMatrix_min_allowed_x_axis_len_value< unique_ID, size_type > };

	inline static constexpr size_type
	max_allowed_y_axis_len { CharMatrix_max_allowed_y_axis_len_value< unique_ID, size_type > };

	inline static constexpr size_type
	max_allowed_x_axis_len { CharMatrix_max_allowed_x_axis_len_value< unique_ID, size_type > };

	inline static constexpr std::size_t matrix_attributes_count { 3 };
	inline static constexpr std::size_t cartesian_components_count { 4 };
	inline static constexpr std::size_t min_possible_num_of_input_lines { 0 };
	inline static constexpr std::size_t max_possible_num_of_input_lines { ( max_allowed_y_axis_len *
																		  ( max_allowed_x_axis_len - 1 ) ) / 2 };

	static_assert( default_y_axis_len >= min_allowed_y_axis_len &&
				   default_y_axis_len <= max_allowed_y_axis_len,
				   "default_y_axis_len can not be greater than max_allowed_y_axis_len or "
				   "less than min_allowed_y_axis_len" );

	static_assert( default_x_axis_len >= min_allowed_x_axis_len &&
				   default_x_axis_len <= max_allowed_x_axis_len,
				   "default_x_axis_len can not be greater than max_allowed_x_axis_len or "
				   "less than min_allowed_x_axis_len" );

	static_assert( max_possible_num_of_input_lines <= max_allowed_y_axis_len * ( max_allowed_x_axis_len - 1 ) / 2 &&
				   max_possible_num_of_input_lines >= 0,
				   "max_possible_num_of_input_lines can not be greater than "
				   "( max_allowed_y_axis_len * max_allowed_x_axis_len ) / 2 or less than 0" );

	static_assert( min_possible_num_of_input_lines <= max_allowed_y_axis_len * ( max_allowed_x_axis_len - 1 ) / 2 &&
				   min_possible_num_of_input_lines >= 0 &&
				   min_possible_num_of_input_lines <= max_possible_num_of_input_lines,
				   "min_possible_num_of_input_lines can not be greater than "
				   "( max_allowed_y_axis_len * max_allowed_x_axis_len ) / 2 or less than 0 or "
				   "greater than max_possible_num_of_input_lines" );

private:
	enum AllowedChars : value_type
	{
		Dash		  = static_cast<value_type>( '-' ) ,
		BackSlash	  = static_cast<value_type>( '\\' ),
		ForwardSlash  = static_cast<value_type>( '/' ) ,
		VerticalSlash = static_cast<value_type>( '|' ) ,
	};

	inline static const std::unordered_set< AllowedChars > chars_for_drawing { Dash,
																			   BackSlash,
																			   ForwardSlash,
																			   VerticalSlash };

public:
	explicit CharMatrix( const size_type Y_AxisLen = default_y_axis_len,
						 const size_type X_AxisLen = default_x_axis_len,
						 const value_type fillCharacter = default_fill_character,
						 const allocator_type& alloc = allocator_type { } );
	CharMatrix( CharMatrix&& rhs ) noexcept;
	CharMatrix& operator=( CharMatrix&& rhs ) noexcept;

	explicit operator bool( ) const noexcept;
	bool operator==( const CharMatrix& rhs ) const noexcept;
	std::partial_ordering operator<=>( const CharMatrix& rhs ) const noexcept;
	value_type& operator[ ]( const std::size_t X_Axis, const std::size_t Y_Axis ) noexcept;
	const value_type& operator[ ]( const std::size_t X_Axis, const std::size_t Y_Axis ) const noexcept;

	[[ nodiscard ]] const size_type& getY_AxisLen( ) const noexcept;
	[[ nodiscard ]] const size_type& getX_AxisLen( ) const noexcept;
	[[ nodiscard ]] const value_type& getFillCharacter( ) const noexcept;
	[[ nodiscard ]] const std::vector<value_type, allocator_type>& getCharacterMatrix( ) const noexcept;

	void setY_AxisLen( const size_type Y_AxisLen );
	void setX_AxisLen( const size_type X_AxisLen );
	void setFillCharacter( const value_type fillCharacter );
	void setCharacterMatrix( const std::array<size_type, cartesian_components_count>&
							 coordsOfChar ) noexcept;

	[[ nodiscard ]] std::optional<AllowedChars> static
	processCoordsToObtainCharType( const std::array<size_type, cartesian_components_count>&
								   coordsOfChar ) noexcept;

	[[ nodiscard ]] bool static
	validateEnteredMatrixAttributes( const std::string_view str_enteredMatrixAttributes,
									 std::tuple<size_type, size_type, value_type>&
									 tuple_enteredMatrixAttributes_OUT ) noexcept;

	[[ nodiscard ]] bool
	validateEnteredNumOfInputLines( const std::string_view str_enteredNumOfInputLines,
									std::array<size_t, 1>&
									int_enteredNumOfInputLines_OUT ) const noexcept;

	[[ nodiscard ]] bool
	validateEnteredCoords( const std::string_view str_enteredCoords,
						   std::array<size_type, cartesian_components_count>&
						   int_enteredCoords_OUT ) const noexcept;

	[[ nodiscard ]] auto static getMatrixAttributes( );
	[[ nodiscard ]] std::size_t getNumOfInputLines( ) const;
	void getCoords( const std::size_t numOfInputLines );

	void draw( std::basic_ostream<value_type>& output_stream ) const;
	void print( ) const;

	template < std::size_t UniqID, std::unsigned_integral SizeT,
			   util::Character CharT, class Alloc>
	friend std::ofstream& operator<<( std::ofstream& ofs,
									  const CharMatrix<UniqID, SizeT, CharT, Alloc>& char_matrix );

	template < std::size_t UniqID, std::unsigned_integral SizeT,
			   util::Character CharT, class Alloc>
	friend std::ifstream& operator>>( std::ifstream& ifs,
									  CharMatrix<UniqID, SizeT, CharT, Alloc>& char_matrix );

	template < size_type Y_AxisLen_v, size_type X_AxisLen_v,
			   value_type fillCharacter_v, bool isFullInputModeEnabled >
	requires ( std::is_same_v< allocator_type, std::pmr::polymorphic_allocator<value_type> > )
	void static runScriptForStaticAllocated( );

	template < size_type Y_AxisLen_v, size_type X_AxisLen_v,
			   value_type fillCharacter_v, bool isFullInputModeEnabled >
	requires ( std::is_same_v< allocator_type, std::pmr::polymorphic_allocator<value_type> > )
	void static runScriptForStackAllocated( );

	template < size_type Y_AxisLen_v, size_type X_AxisLen_v,
			   value_type fillCharacter_v, bool isFullInputModeEnabled >
	requires ( std::is_same_v< allocator_type, std::allocator<value_type> > )
	void static runScriptForStackHeapAllocated( );

	template < size_type Y_AxisLen_v, size_type X_AxisLen_v,
			   value_type fillCharacter_v, bool isFullInputModeEnabled >
	requires ( std::is_same_v< allocator_type, std::allocator<value_type> > )
	void static runScriptForHeapAllocated( );

private:
	size_type m_Y_AxisLen;
	size_type m_X_AxisLen;
	value_type m_fillCharacter;
	std::vector<value_type, allocator_type> m_characterMatrix;
};

namespace pmr
{
	template < std::size_t unique_ID,
			   std::unsigned_integral sizeT,
			   util::Character charT >
	using CharMatrix = CharMatrix< unique_ID, sizeT, charT,
								   std::pmr::polymorphic_allocator<charT> >;
}


void initialize( );
void runScript( );

}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   peyknowruzi::util::Character charT, class Allocator >
struct std::hash< peyknowruzi::CharMatrix<unique_ID, sizeT, charT, Allocator> >
{
	using argument_type = peyknowruzi::CharMatrix<unique_ID, sizeT, charT, Allocator>;
	using result_type = std::size_t;

	result_type operator( )( const argument_type& char_matrix ) const;
};
