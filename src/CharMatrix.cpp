
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


#include "CharMatrix.hpp"
#include "pch.hpp"
#include "Log.hpp"
#include "Util.hpp"


using std::int64_t;
using std::size_t;
using std::streamsize;

namespace peyknowruzi
{

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
inline CharMatrix<unique_ID, sizeT, charT, Allocator>::
CharMatrix( const sizeT Y_AxisLen, const sizeT X_AxisLen,
			const charT fillCharacter, const Allocator& alloc )

	: m_Y_AxisLen { Y_AxisLen }, m_X_AxisLen { X_AxisLen },
	  m_fillCharacter { fillCharacter }, m_characterMatrix { Y_AxisLen * X_AxisLen, fillCharacter, alloc }
{
	for ( size_t last_idx_of_row { m_X_AxisLen - 1 }; last_idx_of_row < m_characterMatrix.size( )
		  ; last_idx_of_row += m_X_AxisLen )
	{
		m_characterMatrix[ last_idx_of_row ] = '\n';
	}
}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
inline CharMatrix<unique_ID, sizeT, charT, Allocator>::
CharMatrix( CharMatrix<unique_ID, sizeT, charT, Allocator>&& rhs ) noexcept

	: m_Y_AxisLen       { std::exchange( rhs.m_Y_AxisLen, 0 ) },
	  m_X_AxisLen       { std::exchange( rhs.m_X_AxisLen, 0 ) },
	  m_fillCharacter   { std::exchange( rhs.m_fillCharacter, 0 ) },
	  m_characterMatrix { std::move( rhs.m_characterMatrix ) }
{
}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
inline CharMatrix<unique_ID, sizeT, charT, Allocator>&
CharMatrix<unique_ID, sizeT, charT, Allocator>::
operator=( CharMatrix<unique_ID, sizeT, charT, Allocator>&& rhs ) noexcept
{
	if ( this != &rhs )
	{
		m_Y_AxisLen       = std::exchange( rhs.m_Y_AxisLen, 0 );
		m_X_AxisLen       = std::exchange( rhs.m_X_AxisLen, 0 );
		m_fillCharacter   = std::exchange( rhs.m_fillCharacter, 0 );
		m_characterMatrix = std::move( rhs.m_characterMatrix );
	}

	return *this;
}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
CharMatrix<unique_ID, sizeT, charT, Allocator>::
operator bool( ) const noexcept
{
	return !m_characterMatrix.empty( );
}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
bool CharMatrix<unique_ID, sizeT, charT, Allocator>::
operator==( const CharMatrix<unique_ID, sizeT, charT, Allocator>& rhs ) const noexcept
{
	return m_Y_AxisLen == rhs.m_Y_AxisLen &&
		   m_X_AxisLen == rhs.m_X_AxisLen &&
		   m_fillCharacter == rhs.m_fillCharacter;
}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
std::partial_ordering CharMatrix<unique_ID, sizeT, charT, Allocator>::
operator<=>( const CharMatrix<unique_ID, sizeT, charT, Allocator>& rhs ) const noexcept
{
	if ( auto cmp { m_Y_AxisLen * m_X_AxisLen <=> rhs.m_Y_AxisLen * rhs.m_X_AxisLen };
		 cmp != 0 ) { return cmp; }

	if ( auto cmp { m_Y_AxisLen <=> rhs.m_Y_AxisLen };
		 cmp != 0 ) { return cmp; }

	return ( m_fillCharacter == rhs.m_fillCharacter ) ?
		   std::partial_ordering::equivalent : std::partial_ordering::unordered;
}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
charT& CharMatrix<unique_ID, sizeT, charT, Allocator>::
operator[ ]( const size_t X_Axis, const size_t Y_Axis ) noexcept
{
	return m_characterMatrix[ Y_Axis * getX_AxisLen( ) + X_Axis ];
}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
const charT& CharMatrix<unique_ID, sizeT, charT, Allocator>::
operator[ ]( const size_t X_Axis, const size_t Y_Axis ) const noexcept
{
	return m_characterMatrix[ Y_Axis * getX_AxisLen( ) + X_Axis ];
}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
[[ nodiscard ]] inline const sizeT&
CharMatrix<unique_ID, sizeT, charT, Allocator>::
getY_AxisLen( ) const noexcept
{
	return m_Y_AxisLen;
}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
[[ nodiscard ]] inline const sizeT&
CharMatrix<unique_ID, sizeT, charT, Allocator>::
getX_AxisLen( ) const noexcept
{
	return m_X_AxisLen;
}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
[[ nodiscard ]] inline const charT&
CharMatrix<unique_ID, sizeT, charT, Allocator>::
getFillCharacter( ) const noexcept
{
	return m_fillCharacter;
}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
[[ nodiscard ]] inline const std::vector<charT, Allocator>&
CharMatrix<unique_ID, sizeT, charT, Allocator>::
getCharacterMatrix( ) const noexcept
{
	return m_characterMatrix;
}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
void CharMatrix<unique_ID, sizeT, charT, Allocator>::
setY_AxisLen( const sizeT Y_AxisLen )
{
	if ( Y_AxisLen > max_allowed_y_axis_len || Y_AxisLen < min_allowed_y_axis_len )
	{
		std::string exceptionMsg;
		exceptionMsg.reserve( 105 );

		exceptionMsg = "Invalid_Y_Axis_Len_Exception: The 'Y-axis length' "
					   "is not allowed to be greater than ";
		exceptionMsg += std::to_string( max_allowed_y_axis_len ) + " and lesser than ";
		exceptionMsg += std::to_string( min_allowed_y_axis_len ) + ".";

		throw std::invalid_argument( exceptionMsg );
	}

	const sizeT& current_Y_AxisLen { getY_AxisLen( ) };
	const sizeT& new_Y_AxisLen { Y_AxisLen };

	if ( new_Y_AxisLen == current_Y_AxisLen ) { return; }

	if ( new_Y_AxisLen > current_Y_AxisLen )
	{
		m_characterMatrix.resize( m_characterMatrix.size( ) + ( new_Y_AxisLen - current_Y_AxisLen ) *
								  getX_AxisLen( ), getFillCharacter( ) );

		for ( size_t last_idx_of_row { ( current_Y_AxisLen + 1 ) * getX_AxisLen( ) - 1 }
			  ; last_idx_of_row < m_characterMatrix.size( ); last_idx_of_row += getX_AxisLen( ) )
		{
			m_characterMatrix[ last_idx_of_row ] = '\n';
		}
	}
	else
	{
		m_characterMatrix.resize( m_characterMatrix.size( ) - ( current_Y_AxisLen - new_Y_AxisLen ) *
								  getX_AxisLen( ) );
	}

	m_Y_AxisLen = { new_Y_AxisLen };
}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
void CharMatrix<unique_ID, sizeT, charT, Allocator>::
setX_AxisLen( const sizeT X_AxisLen )
{
	if ( X_AxisLen > max_allowed_x_axis_len || X_AxisLen < min_allowed_x_axis_len )
	{
		std::string exceptionMsg;
		exceptionMsg.reserve( 106 );

		exceptionMsg = "Invalid_X_Axis_Len_Exception: The 'X-axis length' "
					   "is not allowed to be greater than ";
		exceptionMsg += std::to_string( max_allowed_x_axis_len ) + " and lesser than ";
		exceptionMsg += std::to_string( min_allowed_x_axis_len ) + ".";

		throw std::invalid_argument( exceptionMsg );
	}

	const sizeT& current_X_AxisLen { getX_AxisLen( ) };
	const sizeT& new_X_AxisLen { X_AxisLen };

	if ( new_X_AxisLen == current_X_AxisLen ) { return; }

	if ( new_X_AxisLen > current_X_AxisLen )
	{
		m_characterMatrix.resize( getY_AxisLen( ) * new_X_AxisLen, getFillCharacter( ) );

		for ( auto new_pos { m_characterMatrix.end( ) - 1 },
			  old_pos { m_characterMatrix.begin( ) + ( getY_AxisLen( ) - 1 ) * current_X_AxisLen }
			  ; old_pos >= m_characterMatrix.begin( ); old_pos -= current_X_AxisLen, --new_pos )
		{
			*new_pos = '\n';

			new_pos -= new_X_AxisLen - current_X_AxisLen;
			std::fill_n( new_pos, new_X_AxisLen - current_X_AxisLen, getFillCharacter( ) );

			new_pos -= current_X_AxisLen - 1;
			std::copy_n( old_pos, current_X_AxisLen - 1, new_pos );
		}
	}
	else
	{
		for ( auto new_pos { m_characterMatrix.begin( ) },
			  old_pos { m_characterMatrix.begin( ) }
			  ; old_pos != m_characterMatrix.end( ); old_pos += current_X_AxisLen, ++new_pos )
		{
			std::copy_n( old_pos, new_X_AxisLen - 1, new_pos );

			new_pos += new_X_AxisLen - 1;
			*new_pos = '\n';
		}

		m_characterMatrix.resize( getY_AxisLen( ) * new_X_AxisLen );
	}

	m_X_AxisLen = { new_X_AxisLen };
}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
void CharMatrix<unique_ID, sizeT, charT, Allocator>::
setFillCharacter( const charT fillCharacter )
{
	if ( chars_for_drawing.contains( static_cast<AllowedChars>( fillCharacter ) ) )
	{
		std::string exceptionMsg;
		exceptionMsg.reserve( 131 );

		exceptionMsg = "Invalid_Fill_Character_Exception: The 'fill character' "
					   "is not allowed to be one of the following characters: { ";

		for ( size_t counter { }; const auto ch : chars_for_drawing )
		{
			exceptionMsg += "'";
			exceptionMsg += ch;

			exceptionMsg += ( ++counter != chars_for_drawing.size( ) ) ? "', " : "' }";
		}

		throw std::invalid_argument( exceptionMsg );
	}

	const charT& current_fillCharacter { getFillCharacter( ) };
	const charT& new_fillCharacter { fillCharacter };

	if ( new_fillCharacter == current_fillCharacter ) { return; }

	std::ranges::replace( m_characterMatrix, current_fillCharacter, new_fillCharacter );

	m_fillCharacter = { new_fillCharacter };
}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
void CharMatrix<unique_ID, sizeT, charT, Allocator>::
setCharacterMatrix( const std::array<sizeT, cartesian_components_count>& coordsOfChar ) noexcept
{
	const std::optional< AllowedChars > ch { processCoordsToObtainCharType( coordsOfChar ) };

	if ( const auto& [ x1, y1, x2, y2 ] { coordsOfChar };
		 ch.has_value( ) && chars_for_drawing.contains( *ch ) )
	{
		( *this )[ x1, y1 ] = *ch;
		( *this )[ x2, y2 ] = *ch;
	}
}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
[[ nodiscard ]] std::optional< typename CharMatrix<unique_ID, sizeT, charT, Allocator>::AllowedChars > inline
CharMatrix<unique_ID, sizeT, charT, Allocator>::
processCoordsToObtainCharType( const std::array<sizeT, cartesian_components_count>& coordsOfChar ) noexcept
{
	const auto& [ x1, y1, x2, y2 ] { coordsOfChar };

	const bool isDifferenceOfX_AxisLensEqualTo_1 { util::isDifferenceEqualTo_1( x1, x2 ) };
	const bool isDifferenceOfY_AxisLensEqualTo_1 { util::isDifferenceEqualTo_1( y1, y2 ) };

	if ( isDifferenceOfX_AxisLensEqualTo_1 &&
		 ( y1 == y2 ) )
	{
		return Dash;
	}
	else if ( isDifferenceOfY_AxisLensEqualTo_1 &&
			  ( x1 == x2 ) )
	{
		return VerticalSlash;
	}
	else if ( isDifferenceOfX_AxisLensEqualTo_1 &&
			  isDifferenceOfY_AxisLensEqualTo_1 &&
			  ( ( x1 < x2 && y1 > y2 ) ||
				( x1 > x2 && y1 < y2 ) ) )
	{
		return ForwardSlash;
	}
	else if ( isDifferenceOfX_AxisLensEqualTo_1 &&
			  isDifferenceOfY_AxisLensEqualTo_1 &&
			  ( ( x1 < x2 && y1 < y2 ) ||
				( x1 > x2 && y1 > y2 ) ) )
	{
		return BackSlash;
	}
	else
	{
		return std::nullopt;
	}
}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
[[ nodiscard ]] bool
CharMatrix<unique_ID, sizeT, charT, Allocator>::
validateEnteredMatrixAttributes( const std::string_view str_enteredMatrixAttributes,
								 std::tuple<sizeT, sizeT, charT>&
								 tuple_enteredMatrixAttributes_OUT ) noexcept
{
	static constexpr size_t required_tokens_count { matrix_attributes_count };
	static constexpr std::array<size_t, 1> specificTokenIndexFor_Y_AxisLen { 0 };
	static constexpr std::array<size_t, 1> specificTokenIndexFor_X_AxisLen { 1 };

	std::array< std::string_view, required_tokens_count > foundTokens;

	const size_t foundTokensCount { util::tokenize_fast( str_enteredMatrixAttributes,
														 foundTokens, required_tokens_count ) };

	std::array<sizeT, required_tokens_count> int_enteredMatrix_YX { };

	const bool isValid
	{
		foundTokensCount == required_tokens_count
																								&&
		util::convert_specific_tokens_to_integers<sizeT>( foundTokens, int_enteredMatrix_YX,
															  specificTokenIndexFor_Y_AxisLen,
															  { min_allowed_y_axis_len,
																max_allowed_y_axis_len } )
																								&&
		util::convert_specific_tokens_to_integers<sizeT>( foundTokens, int_enteredMatrix_YX,
															  specificTokenIndexFor_X_AxisLen,
															  { min_allowed_x_axis_len,
																max_allowed_x_axis_len } )
																								&&
		foundTokens[ 2 ].size( ) == 1
																								&&
		!chars_for_drawing.contains( static_cast<AllowedChars>( foundTokens[ 2 ][ 0 ] ) )
	};

	if ( isValid )
	{
		std::get<0>( tuple_enteredMatrixAttributes_OUT ) = int_enteredMatrix_YX[ 0 ];
		std::get<1>( tuple_enteredMatrixAttributes_OUT ) = int_enteredMatrix_YX[ 1 ];
		std::get<2>( tuple_enteredMatrixAttributes_OUT ) = foundTokens[ 2 ][ 0 ];
	}

	return isValid;
}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
[[ nodiscard ]] bool
CharMatrix<unique_ID, sizeT, charT, Allocator>::
validateEnteredNumOfInputLines( const std::string_view str_enteredNumOfInputLines,
								std::array<size_t, 1>& int_enteredNumOfInputLines_OUT ) const noexcept
{
	const size_t max_allowed_num_of_input_lines { ( getY_AxisLen( ) * ( getX_AxisLen( ) - 1 ) ) / 2 };
	const size_t min_allowed_num_of_input_lines { min_possible_num_of_input_lines };

	static constexpr size_t required_tokens_count { 1 };

	std::array< std::string_view, required_tokens_count > foundTokens;

	const size_t foundTokensCount { util::tokenize_fast( str_enteredNumOfInputLines,
														 foundTokens, required_tokens_count ) };

	const bool isValid
	{
		foundTokensCount == required_tokens_count
																						&&
		util::convert_tokens_to_integers<size_t>( foundTokens,
												  int_enteredNumOfInputLines_OUT,
												  { min_allowed_num_of_input_lines,
													max_allowed_num_of_input_lines } )
	};

	return isValid;
}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
[[ nodiscard ]] bool
CharMatrix<unique_ID, sizeT, charT, Allocator>::
validateEnteredCoords( const std::string_view str_enteredCoords,
					   std::array<sizeT, cartesian_components_count>&
					   int_enteredCoords_OUT ) const noexcept
{
	static constexpr size_t required_tokens_count { cartesian_components_count };
	static constexpr std::array<size_t, 2> specificTokensIndicesFor_Y { 1, 3 };
	static constexpr std::array<size_t, 2> specificTokensIndicesFor_X { 0, 2 };

	const sizeT max_allowed_y { getY_AxisLen( ) - 1 };
	const sizeT max_allowed_x { getX_AxisLen( ) - 2 };
	static constexpr sizeT min_allowed_y { 0 };
	static constexpr sizeT min_allowed_x { 0 };

	std::array< std::string_view, required_tokens_count > foundTokens;

	const size_t foundTokensCount { util::tokenize_fast( str_enteredCoords, foundTokens,
														 required_tokens_count ) };

	const bool isValid
	{
		foundTokensCount == required_tokens_count
																									&&
		util::convert_specific_tokens_to_integers<sizeT>( foundTokens, int_enteredCoords_OUT,
															  specificTokensIndicesFor_Y,
															  { min_allowed_y, max_allowed_y } )
																									&&
		util::convert_specific_tokens_to_integers<sizeT>( foundTokens, int_enteredCoords_OUT,
															  specificTokensIndicesFor_X,
															  { min_allowed_x, max_allowed_x } )
	};

	return isValid;
}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
[[ nodiscard ]] auto CharMatrix<unique_ID, sizeT, charT, Allocator>::
getMatrixAttributes( )
{
	static constexpr streamsize stream_size { default_buffer_size };

	std::array<char, stream_size> str_enteredMatrixAttributes { };
	std::tuple<sizeT, sizeT, charT> tuple_enteredMatrixAttributes { };

	bool isValid;

	do
	{
		const size_t lengthOfInputStr { util::get_chars_from_input( std::cin, str_enteredMatrixAttributes ) };

		isValid = validateEnteredMatrixAttributes( { str_enteredMatrixAttributes.data( ), lengthOfInputStr },
												   tuple_enteredMatrixAttributes );

	} while ( !isValid );

	return tuple_enteredMatrixAttributes;
}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
[[ nodiscard ]] size_t CharMatrix<unique_ID, sizeT, charT, Allocator>::
getNumOfInputLines( ) const
{
	static constexpr streamsize stream_size { default_buffer_size };
	static constexpr size_t required_tokens_count { 1 };

	std::array<char, stream_size> str_enteredNumOfInputLines { };
	std::array<size_t, required_tokens_count> int_enteredNumOfInputLines { };

	bool isValid;

	do
	{
		const size_t lengthOfInputStr { util::get_chars_from_input( std::cin, str_enteredNumOfInputLines ) };

		isValid = validateEnteredNumOfInputLines( { str_enteredNumOfInputLines.data( ), lengthOfInputStr },
												  int_enteredNumOfInputLines );

	} while ( !isValid );

	return int_enteredNumOfInputLines[ 0 ];
}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
void CharMatrix<unique_ID, sizeT, charT, Allocator>::
getCoords( const size_t numOfInputLines )
{
	static constexpr streamsize stream_size { default_buffer_size };
	static constexpr size_t required_tokens_count { cartesian_components_count };

	std::array<char, stream_size> str_enteredCoords { };
	std::array<sizeT, required_tokens_count> int_enteredCoords { };

	for ( size_t counter { }; counter < numOfInputLines; ++counter )
	{
		bool isValid;

		do
		{
			const size_t lengthOfInputStr { util::get_chars_from_input( std::cin, str_enteredCoords ) };

			isValid = validateEnteredCoords( { str_enteredCoords.data( ), lengthOfInputStr },
											 int_enteredCoords );

		} while ( !isValid );

		setCharacterMatrix( int_enteredCoords );
	}
}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
void CharMatrix<unique_ID, sizeT, charT, Allocator>::
draw( std::basic_ostream<charT>& output_stream ) const
{
#if PN_DEBUG == 1
	{
	util::ScopedTimer timer;
#endif

	output_stream.write( getCharacterMatrix( ).data( ), static_cast<streamsize>(
						 getCharacterMatrix( ).size( ) ) );

#if PN_DEBUG == 1
	}
#endif

	log( "\nFinished." );
	WAIT;
}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
void CharMatrix<unique_ID, sizeT, charT, Allocator>::
print( ) const
{
	using CharMatrix_t = std::remove_pointer_t<decltype( this )>;

	if constexpr ( std::is_same_v< typename CharMatrix_t::value_type,
								   decltype( std::cout )::char_type > )
	{
		this->draw( std::cout );
	}
	else if constexpr ( std::is_same_v< typename CharMatrix_t::value_type,
										decltype( std::wcout )::char_type > )
	{
		this->draw( std::wcout );
	}
	else
	{
		static_assert( std::is_same_v< typename CharMatrix_t::value_type,
									   decltype( std::cout )::char_type > ||
					   std::is_same_v< typename CharMatrix_t::value_type,
									   decltype( std::wcout )::char_type >,
					   "character type not supported by the current print function" );
	}
}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
std::ofstream& operator<<( std::ofstream& ofs,
						   const CharMatrix<unique_ID, sizeT, charT, Allocator>& char_matrix )
{
	ofs.write( reinterpret_cast<const char*>( &char_matrix.getY_AxisLen( ) ),
			   static_cast<streamsize>( sizeof( char_matrix.getY_AxisLen( ) ) ) );
	ofs.write( reinterpret_cast<const char*>( &char_matrix.getX_AxisLen( ) ),
			   static_cast<streamsize>( sizeof( char_matrix.getX_AxisLen( ) ) ) );
	ofs.write( reinterpret_cast<const char*>( &char_matrix.getFillCharacter( ) ),
			   static_cast<streamsize>( sizeof( char_matrix.getFillCharacter( ) ) ) );
	ofs.write( reinterpret_cast<const char*>( char_matrix.getCharacterMatrix( ).data( ) ),
					 static_cast<streamsize>( char_matrix.getCharacterMatrix( ).size( ) * sizeof( charT ) ) );

	return ofs;
}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
std::ifstream& operator>>( std::ifstream& ifs,
						   CharMatrix<unique_ID, sizeT, charT, Allocator>& char_matrix )
{
	static CharMatrix<unique_ID, sizeT, charT, Allocator> temp_char_matrix
	{ CharMatrix<unique_ID, sizeT, charT, Allocator>::default_y_axis_len,
	  CharMatrix<unique_ID, sizeT, charT, Allocator>::default_x_axis_len,
	  CharMatrix<unique_ID, sizeT, charT, Allocator>::default_fill_character };

	ifs.read( reinterpret_cast<char*>( &temp_char_matrix.m_Y_AxisLen ),
			  static_cast<streamsize>( sizeof( temp_char_matrix.m_Y_AxisLen ) ) );
	ifs.read( reinterpret_cast<char*>( &temp_char_matrix.m_X_AxisLen ),
			  static_cast<streamsize>( sizeof( temp_char_matrix.m_X_AxisLen ) ) );
	ifs.read( reinterpret_cast<char*>( &temp_char_matrix.m_fillCharacter ),
			  static_cast<streamsize>( sizeof( temp_char_matrix.m_fillCharacter ) ) );
	temp_char_matrix.m_characterMatrix.resize( temp_char_matrix.getY_AxisLen( ) *
											   temp_char_matrix.getX_AxisLen( ) );
	ifs.read( reinterpret_cast<char*>( temp_char_matrix.m_characterMatrix.data( ) ),
			  static_cast<streamsize>( temp_char_matrix.m_characterMatrix.size( ) * sizeof( charT ) ) );

	char_matrix.m_Y_AxisLen = temp_char_matrix.getY_AxisLen( );
	char_matrix.setY_AxisLen( temp_char_matrix.getY_AxisLen( ) );
	char_matrix.m_X_AxisLen = temp_char_matrix.getX_AxisLen( );
	char_matrix.setX_AxisLen( temp_char_matrix.getX_AxisLen( ) );
	char_matrix.m_fillCharacter = temp_char_matrix.getFillCharacter( );
	char_matrix.setFillCharacter( temp_char_matrix.getFillCharacter( ) );
	char_matrix.m_characterMatrix.reserve( temp_char_matrix.getCharacterMatrix( ).size( ) );
	char_matrix.m_characterMatrix.clear( );
	std::ranges::copy( temp_char_matrix.getCharacterMatrix( ),
					   std::back_inserter( char_matrix.m_characterMatrix ) );

	return ifs;
}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
template < sizeT Y_AxisLen_v, sizeT X_AxisLen_v,
		   charT fillCharacter_v, bool isFullInputModeEnabled >
requires ( std::is_same_v< Allocator, std::pmr::polymorphic_allocator<charT> > )
void CharMatrix<unique_ID, sizeT, charT, Allocator>::
runScriptForStaticAllocated( )
{
#if FULL_INPUT_MODE_ALLOWED == 1
constexpr bool isFullInputModeAllowed { true };
#else
constexpr bool isFullInputModeAllowed { false };
#endif

static_assert( !( isFullInputModeEnabled ),
			   "‘Allocation_Strategy::static_allocated’ cannot be selected "
			   "when a dynamically allocated buffer is required "
			   "(isFullInputModeEnabled == true)" );

if constexpr ( isFullInputModeAllowed && isFullInputModeEnabled )
{
}
else
{
	using CharMatrix_t = CharMatrix<unique_ID, sizeT, charT, Allocator>;

	static constexpr CharMatrix_t::size_type Y_AxisLen { Y_AxisLen_v };
	static constexpr CharMatrix_t::size_type X_AxisLen { X_AxisLen_v };
	static constexpr CharMatrix_t::value_type fillCharacter { fillCharacter_v };

	static_assert( Y_AxisLen >= CharMatrix_t::min_allowed_y_axis_len &&
				   Y_AxisLen <= CharMatrix_t::max_allowed_y_axis_len,
				   "Y_AxisLen can not be greater than max_allowed_y_axis_len or "
				   "less than min_allowed_y_axis_len" );

	static_assert( X_AxisLen >= CharMatrix_t::min_allowed_x_axis_len &&
				   X_AxisLen <= CharMatrix_t::max_allowed_x_axis_len,
				   "X_AxisLen can not be greater than max_allowed_x_axis_len or "
				   "less than min_allowed_x_axis_len" );

	constexpr size_t buffer_size { Y_AxisLen * X_AxisLen + 500 };
	static auto buffer { std::array< std::byte, buffer_size >{ } };
	const auto buffer_address { buffer.data( ) };
	static std::pmr::monotonic_buffer_resource rsrc { buffer_address, buffer_size };

	static auto matrix { CharMatrix_t( Y_AxisLen, X_AxisLen , fillCharacter, &rsrc ) };

	matrix.getCoords( matrix.getNumOfInputLines( ) );
	matrix.print( );
}

}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
template < sizeT Y_AxisLen_v, sizeT X_AxisLen_v,
		   charT fillCharacter_v, bool isFullInputModeEnabled >
requires ( std::is_same_v< Allocator, std::pmr::polymorphic_allocator<charT> > )
void CharMatrix<unique_ID, sizeT, charT, Allocator>::
runScriptForStackAllocated( )
{
#if FULL_INPUT_MODE_ALLOWED == 1
constexpr bool isFullInputModeAllowed { true };
#else
constexpr bool isFullInputModeAllowed { false };
#endif

static_assert( !( isFullInputModeEnabled ),
			   "‘Allocation_Strategy::stack_allocated’ cannot be selected "
			   "when a dynamically allocated buffer is required "
			   "(isFullInputModeEnabled == true)" );

if constexpr ( isFullInputModeAllowed && isFullInputModeEnabled )
{
}
else
{
	using CharMatrix_t = CharMatrix<unique_ID, sizeT, charT, Allocator>;

	static constexpr CharMatrix_t::size_type Y_AxisLen { Y_AxisLen_v };
	static constexpr CharMatrix_t::size_type X_AxisLen { X_AxisLen_v };
	static constexpr CharMatrix_t::value_type fillCharacter { fillCharacter_v };

	static_assert( Y_AxisLen >= CharMatrix_t::min_allowed_y_axis_len &&
				   Y_AxisLen <= CharMatrix_t::max_allowed_y_axis_len,
				   "Y_AxisLen can not be greater than max_allowed_y_axis_len or "
				   "less than min_allowed_y_axis_len" );

	static_assert( X_AxisLen >= CharMatrix_t::min_allowed_x_axis_len &&
				   X_AxisLen <= CharMatrix_t::max_allowed_x_axis_len,
				   "X_AxisLen can not be greater than max_allowed_x_axis_len or "
				   "less than min_allowed_x_axis_len" );

	constexpr size_t buffer_size { Y_AxisLen * X_AxisLen + 500 };
	auto buffer { std::array< std::byte, buffer_size >{ } };
	const auto buffer_address { buffer.data( ) };
	std::pmr::monotonic_buffer_resource rsrc { buffer_address, buffer_size };

	auto matrix { CharMatrix_t( Y_AxisLen, X_AxisLen , fillCharacter, &rsrc ) };

	matrix.getCoords( matrix.getNumOfInputLines( ) );
	matrix.print( );
}

}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
template < sizeT Y_AxisLen_v, sizeT X_AxisLen_v,
		   charT fillCharacter_v, bool isFullInputModeEnabled >
requires ( std::is_same_v< Allocator, std::allocator<charT> > )
void CharMatrix<unique_ID, sizeT, charT, Allocator>::
runScriptForStackHeapAllocated( )
{
#if FULL_INPUT_MODE_ALLOWED == 1
constexpr bool isFullInputModeAllowed { true };
#else
constexpr bool isFullInputModeAllowed { false };
#endif

	using CharMatrix_t = CharMatrix<unique_ID, sizeT, charT, Allocator>;

if constexpr ( isFullInputModeAllowed && isFullInputModeEnabled )
{
	const auto [ Y_AxisLen, X_AxisLen, fillCharacter ] { CharMatrix_t::getMatrixAttributes( ) };

	auto matrix { CharMatrix_t( Y_AxisLen, X_AxisLen , fillCharacter ) };

	matrix.getCoords( matrix.getNumOfInputLines( ) );
	matrix.print( );
}
else
{
	static constexpr CharMatrix_t::size_type Y_AxisLen { Y_AxisLen_v };
	static constexpr CharMatrix_t::size_type X_AxisLen { X_AxisLen_v };
	static constexpr CharMatrix_t::value_type fillCharacter { fillCharacter_v };

	static_assert( Y_AxisLen >= CharMatrix_t::min_allowed_y_axis_len &&
				   Y_AxisLen <= CharMatrix_t::max_allowed_y_axis_len,
				   "Y_AxisLen can not be greater than max_allowed_y_axis_len or "
				   "less than min_allowed_y_axis_len" );

	static_assert( X_AxisLen >= CharMatrix_t::min_allowed_x_axis_len &&
				   X_AxisLen <= CharMatrix_t::max_allowed_x_axis_len,
				   "X_AxisLen can not be greater than max_allowed_x_axis_len or "
				   "less than min_allowed_x_axis_len" );

	auto matrix { CharMatrix_t( Y_AxisLen, X_AxisLen , fillCharacter ) };

	matrix.getCoords( matrix.getNumOfInputLines( ) );
	matrix.print( );
}

}

template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   util::Character charT, class Allocator >
template < sizeT Y_AxisLen_v, sizeT X_AxisLen_v,
		   charT fillCharacter_v, bool isFullInputModeEnabled >
requires ( std::is_same_v< Allocator, std::allocator<charT> > )
void CharMatrix<unique_ID, sizeT, charT, Allocator>::
runScriptForHeapAllocated( )
{
#if FULL_INPUT_MODE_ALLOWED == 1
constexpr bool isFullInputModeAllowed { true };
#else
constexpr bool isFullInputModeAllowed { false };
#endif

	using CharMatrix_t = CharMatrix<unique_ID, sizeT, charT, Allocator>;

if constexpr ( isFullInputModeAllowed && isFullInputModeEnabled )
{
	const auto [ Y_AxisLen, X_AxisLen, fillCharacter ] { CharMatrix_t::getMatrixAttributes( ) };

	auto matrix { std::make_unique< CharMatrix_t >( Y_AxisLen, X_AxisLen , fillCharacter ) };

	matrix->getCoords( matrix->getNumOfInputLines( ) );
	matrix->print( );
}
else
{
	static constexpr CharMatrix_t::size_type Y_AxisLen { Y_AxisLen_v };
	static constexpr CharMatrix_t::size_type X_AxisLen { X_AxisLen_v };
	static constexpr CharMatrix_t::value_type fillCharacter { fillCharacter_v };

	static_assert( Y_AxisLen >= CharMatrix_t::min_allowed_y_axis_len &&
				   Y_AxisLen <= CharMatrix_t::max_allowed_y_axis_len,
				   "Y_AxisLen can not be greater than max_allowed_y_axis_len or "
				   "less than min_allowed_y_axis_len" );

	static_assert( X_AxisLen >= CharMatrix_t::min_allowed_x_axis_len &&
				   X_AxisLen <= CharMatrix_t::max_allowed_x_axis_len,
				   "X_AxisLen can not be greater than max_allowed_x_axis_len or "
				   "less than min_allowed_x_axis_len" );

	auto matrix { std::make_unique< CharMatrix_t >( Y_AxisLen, X_AxisLen , fillCharacter ) };

	matrix->getCoords( matrix->getNumOfInputLines( ) );
	matrix->print( );
}

}

void inline initialize( )
{
	std::ios_base::sync_with_stdio( false );
}

void runScript( )
{
	// initialize( );

	using CharMatrix_1000 = CharMatrix<1000, std::uint32_t, char>;
	using CharMatrix_1001 = pmr::CharMatrix<1001, std::uint32_t, char>;

enum class Allocation_Strategy
{
	static_allocated,
	stack_allocated,
	stack_heap_allocated,
	heap_allocated,
};

constexpr Allocation_Strategy alloc_strgy { Allocation_Strategy::stack_allocated };

if constexpr ( alloc_strgy == Allocation_Strategy::static_allocated )
{
	constexpr CharMatrix_1001::size_type Y_AxisLen { 36 };
	constexpr CharMatrix_1001::size_type X_AxisLen { 168 };
	constexpr CharMatrix_1001::value_type fillCharacter { ' ' };
	constexpr bool isFullInputModeEnabled { false };

	CharMatrix_1001::runScriptForStaticAllocated<Y_AxisLen, X_AxisLen, fillCharacter, isFullInputModeEnabled>( );
}
else if constexpr ( alloc_strgy == Allocation_Strategy::stack_allocated )
{
	constexpr CharMatrix_1001::size_type Y_AxisLen { 36 };
	constexpr CharMatrix_1001::size_type X_AxisLen { 168 };
	constexpr CharMatrix_1001::value_type fillCharacter { ' ' };
	constexpr bool isFullInputModeEnabled { false };

	CharMatrix_1001::runScriptForStackAllocated<Y_AxisLen, X_AxisLen, fillCharacter, isFullInputModeEnabled>( );
}
else if constexpr ( alloc_strgy == Allocation_Strategy::stack_heap_allocated )
{
	constexpr CharMatrix_1000::size_type Y_AxisLen { 36 };
	constexpr CharMatrix_1000::size_type X_AxisLen { 168 };
	constexpr CharMatrix_1000::value_type fillCharacter { ' ' };
	constexpr bool isFullInputModeEnabled { false };

	CharMatrix_1000::runScriptForStackHeapAllocated<Y_AxisLen, X_AxisLen, fillCharacter, isFullInputModeEnabled>( );
}
else if constexpr ( alloc_strgy == Allocation_Strategy::heap_allocated )
{
	constexpr CharMatrix_1000::size_type Y_AxisLen { 36 };
	constexpr CharMatrix_1000::size_type X_AxisLen { 168 };
	constexpr CharMatrix_1000::value_type fillCharacter { ' ' };
	constexpr bool isFullInputModeEnabled { false };

	CharMatrix_1000::runScriptForHeapAllocated<Y_AxisLen, X_AxisLen, fillCharacter, isFullInputModeEnabled>( );
}
else
{
	static_assert( alloc_strgy == Allocation_Strategy::static_allocated ||
				   alloc_strgy == Allocation_Strategy::stack_allocated ||
				   alloc_strgy == Allocation_Strategy::stack_heap_allocated ||
				   alloc_strgy == Allocation_Strategy::heap_allocated,
				   "Unknown allocation strategy" );
}

}

template class CharMatrix<1001, std::uint32_t, char, std::pmr::polymorphic_allocator<char>>;

}


template < std::size_t unique_ID, std::unsigned_integral sizeT,
		   peyknowruzi::util::Character charT, class Allocator >
std::hash< peyknowruzi::CharMatrix<unique_ID, sizeT, charT, Allocator> >::result_type
std::hash< peyknowruzi::CharMatrix<unique_ID, sizeT, charT, Allocator> >::
operator( )( const argument_type& char_matrix ) const
{
	result_type hashValue { 17 };
	hashValue = 31 * hashValue + std::hash<sizeT>{ }( char_matrix.getY_AxisLen( ) );
	hashValue = 31 * hashValue + std::hash<sizeT>{ }( char_matrix.getX_AxisLen( ) );
	hashValue = 31 * hashValue + std::hash<charT>{ }( char_matrix.getFillCharacter( ) );

	return hashValue;
}
