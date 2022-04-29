
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


#define PN_DEBUG 0
//#define GUI_MODE 0
#define FULL_INPUT_MODE 0

#if PN_DEBUG == 1
#define LOG(x) std::clog << ( x ) << std::endl
#define ERR(x) std::cerr << ( x ) << std::endl
#define WAIT std::cin.get( )
#else
#define LOG(x)
#define ERR(x)
#define WAIT
#endif


#include "CharMatrix.h"
#include "Util.h"


using std::uint32_t;
using std::int64_t;
using std::size_t;
using std::streamsize;

namespace peyknowruzi
{

static constexpr uint32_t min_allowed_y_axis_len { 1 };
static constexpr uint32_t min_allowed_x_axis_len { 2 };
static constexpr uint32_t max_allowed_y_axis_len { 50 };
static constexpr uint32_t max_allowed_x_axis_len { 168 };
static constexpr size_t min_possible_num_of_input_lines { 0 };
static constexpr size_t max_possible_num_of_input_lines { ( max_allowed_y_axis_len *
														  ( max_allowed_x_axis_len - 1 ) ) / 2 };

static_assert( CharMatrix::default_y_axis_len >= min_allowed_y_axis_len &&
			   CharMatrix::default_y_axis_len <= max_allowed_y_axis_len,
			   "default_y_axis_len can not be greater than max_allowed_y_axis_len or "
			   "less than min_allowed_y_axis_len" );

static_assert( CharMatrix::default_x_axis_len >= min_allowed_x_axis_len &&
			   CharMatrix::default_x_axis_len <= max_allowed_x_axis_len,
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


inline CharMatrix::CharMatrix( const uint32_t Y_AxisLen, const uint32_t X_AxisLen, const char fillCharacter )
	: m_Y_AxisLen( Y_AxisLen ), m_X_AxisLen( X_AxisLen ), m_fillCharacter( fillCharacter ),
	  m_characterMatrix( Y_AxisLen * X_AxisLen, fillCharacter )
{
	for ( size_t last_idx_of_row { m_X_AxisLen - 1 }; last_idx_of_row < m_characterMatrix.size( )
		  ; last_idx_of_row += m_X_AxisLen )
	{
		m_characterMatrix[ last_idx_of_row ] = '\n';
	}
}

inline CharMatrix::CharMatrix( CharMatrix&& rhs ) noexcept
	: m_Y_AxisLen( rhs.m_Y_AxisLen ), m_X_AxisLen( rhs.m_X_AxisLen ), m_fillCharacter( rhs.m_fillCharacter ),
	  m_characterMatrix( std::move( rhs.m_characterMatrix ) )
{
	rhs.m_Y_AxisLen = 0;
	rhs.m_X_AxisLen = 0;
	rhs.m_fillCharacter = 0;
}

inline CharMatrix& CharMatrix::operator=( CharMatrix&& rhs ) noexcept
{
	if ( this != &rhs )
	{
		m_characterMatrix = std::move( rhs.m_characterMatrix );
		m_Y_AxisLen = rhs.m_Y_AxisLen;
		m_X_AxisLen = rhs.m_X_AxisLen;
		m_fillCharacter = rhs.m_fillCharacter;

		rhs.m_Y_AxisLen = 0;
		rhs.m_X_AxisLen = 0;
		rhs.m_fillCharacter = 0;
	}

	return *this;
}

CharMatrix::operator bool( ) const noexcept
{
	return !m_characterMatrix.empty( );
}

bool CharMatrix::operator==( const CharMatrix& rhs ) const noexcept
{
	return m_Y_AxisLen == rhs.m_Y_AxisLen &&
		   m_X_AxisLen == rhs.m_X_AxisLen &&
		   m_fillCharacter == rhs.m_fillCharacter;
}

std::partial_ordering CharMatrix::operator<=>( const CharMatrix& rhs ) const noexcept
{
	if ( auto cmp { m_Y_AxisLen * m_X_AxisLen <=> rhs.m_Y_AxisLen * rhs.m_X_AxisLen };
		 cmp != 0 ) { return cmp; }

	if ( auto cmp { m_Y_AxisLen <=> rhs.m_Y_AxisLen };
		 cmp != 0 ) { return cmp; }

	return ( m_fillCharacter == rhs.m_fillCharacter ) ?
		   std::partial_ordering::equivalent : std::partial_ordering::unordered;
}

[[ nodiscard ]] inline const uint32_t& CharMatrix::getY_AxisLen( ) const noexcept
{
	return m_Y_AxisLen;
}

[[ nodiscard ]] inline const uint32_t& CharMatrix::getX_AxisLen( ) const noexcept
{
	return m_X_AxisLen;
}

[[ nodiscard ]] inline const char& CharMatrix::getFillCharacter( ) const noexcept
{
	return m_fillCharacter;
}

[[ nodiscard ]] inline const std::vector<char>& CharMatrix::getCharacterMatrix( ) const noexcept
{
	return m_characterMatrix;
}

void CharMatrix::setY_AxisLen( const uint32_t Y_AxisLen )
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

	const uint32_t& current_Y_AxisLen { getY_AxisLen( ) };
	const uint32_t& new_Y_AxisLen { Y_AxisLen };

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

void CharMatrix::setX_AxisLen( const uint32_t X_AxisLen )
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

	const uint32_t& current_X_AxisLen { getX_AxisLen( ) };
	const uint32_t& new_X_AxisLen { X_AxisLen };

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

void CharMatrix::setFillCharacter( const char fillCharacter )
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

	const char& current_fillCharacter { getFillCharacter( ) };
	const char& new_fillCharacter { fillCharacter };

	if ( new_fillCharacter == current_fillCharacter ) { return; }

	std::ranges::replace( m_characterMatrix, current_fillCharacter, new_fillCharacter );

	m_fillCharacter = { new_fillCharacter };
}

inline void CharMatrix::setCharacterMatrix( const std::array<uint32_t, cartesian_components_count>& coordsOfChar ) noexcept
{
	const std::optional< AllowedChars > ch { processCoordsToObtainCharType( coordsOfChar ) };

	if ( ch.has_value( ) && chars_for_drawing.contains( ch.value( ) ) )
	{
		m_characterMatrix[ coordsOfChar[ 1 ] * getX_AxisLen( ) + coordsOfChar[ 0 ] ] = ch.value( );
		m_characterMatrix[ coordsOfChar[ 3 ] * getX_AxisLen( ) + coordsOfChar[ 2 ] ] = ch.value( );
	}
}

[[ nodiscard ]] bool
CharMatrix::validateEnteredMatrixAttributes( const std::string_view str_enteredMatrixAttributes,
											 std::tuple<uint32_t, uint32_t, char>& tuple_enteredMatrixAttributes_OUT ) noexcept
{
	static constexpr size_t required_tokens_count { matrix_attributes_count };
	static constexpr std::array<size_t, 1> specificTokenIndexFor_Y_AxisLen { 0 };
	static constexpr std::array<size_t, 1> specificTokenIndexFor_X_AxisLen { 1 };

	std::array< std::string_view, required_tokens_count > foundTokens;

	const size_t foundTokensCount { util::tokenize_fast( str_enteredMatrixAttributes,
														 foundTokens, required_tokens_count ) };

	std::array<uint32_t, required_tokens_count> int_enteredMatrix_YX { };

	const bool isValid { foundTokensCount == required_tokens_count
																	&&
						 util::convert_specific_tokens_to_integers<uint32_t>( foundTokens, int_enteredMatrix_YX, specificTokenIndexFor_Y_AxisLen,
																			  { min_allowed_y_axis_len, max_allowed_y_axis_len } )
																																				&&
						 util::convert_specific_tokens_to_integers<uint32_t>( foundTokens, int_enteredMatrix_YX, specificTokenIndexFor_X_AxisLen,
																			  { min_allowed_x_axis_len, max_allowed_x_axis_len } )
																																				&&
						 ( foundTokens[ 2 ].size( ) == 1 && !chars_for_drawing.contains( static_cast<AllowedChars>( foundTokens[ 2 ][ 0 ] ) ) ) ? true : false };

	if ( isValid )
	{
		std::get<0>( tuple_enteredMatrixAttributes_OUT ) = int_enteredMatrix_YX[ 0 ];
		std::get<1>( tuple_enteredMatrixAttributes_OUT ) = int_enteredMatrix_YX[ 1 ];
		std::get<2>( tuple_enteredMatrixAttributes_OUT ) = foundTokens[ 2 ][ 0 ];
	}

	return isValid;
}

[[ nodiscard ]] bool
CharMatrix::validateEnteredCoords( const std::string_view str_enteredCoords,
								   std::array<uint32_t, cartesian_components_count>& int_enteredCoords_OUT ) const noexcept
{
	static constexpr size_t required_tokens_count { cartesian_components_count };
	static constexpr std::array<size_t, 2> specificTokensIndicesFor_Y { 1, 3 };
	static constexpr std::array<size_t, 2> specificTokensIndicesFor_X { 0, 2 };

	const uint32_t max_allowed_y { getY_AxisLen( ) - 1 };
	const uint32_t max_allowed_x { getX_AxisLen( ) - 2 };
	static constexpr uint32_t min_allowed_y { 0 };
	static constexpr uint32_t min_allowed_x { 0 };

	std::array< std::string_view, required_tokens_count > foundTokens;

	const size_t foundTokensCount { util::tokenize_fast( str_enteredCoords, foundTokens,
														 required_tokens_count ) };

	const bool isValid { foundTokensCount == required_tokens_count
																	&&
						 util::convert_specific_tokens_to_integers<uint32_t>( foundTokens, int_enteredCoords_OUT, specificTokensIndicesFor_Y,
																			  { min_allowed_y, max_allowed_y } )
																																			&&
						 util::convert_specific_tokens_to_integers<uint32_t>( foundTokens, int_enteredCoords_OUT, specificTokensIndicesFor_X,
																			  { min_allowed_x, max_allowed_x } ) ? true : false };

	return isValid;
}

[[ nodiscard ]] inline std::optional< CharMatrix::AllowedChars >
CharMatrix::processCoordsToObtainCharType( const std::array<uint32_t, cartesian_components_count>& coordsOfChar ) noexcept
{
	const auto& [ x1, y1, x2, y2 ] { coordsOfChar };

	const bool isDifferenceOfX_AxisLensEqualTo_1 { std::abs( static_cast<int64_t>( x1 ) -
															 static_cast<int64_t>( x2 ) ) == 1 };

	const bool isDifferenceOfY_AxisLensEqualTo_1 { std::abs( static_cast<int64_t>( y1 ) -
															 static_cast<int64_t>( y2 ) ) == 1 };

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
		return { };
	}
}

size_t CharMatrix::getNumOfInputLines( ) const
{
	const size_t max_allowed_num_of_input_lines { ( getY_AxisLen( ) * ( getX_AxisLen( ) - 1 ) ) / 2 };
	const size_t min_allowed_num_of_input_lines { min_possible_num_of_input_lines };

	static constexpr streamsize stream_size { default_buffer_size };
	static constexpr size_t required_tokens_count { 1 };

	std::array<char, stream_size> str_numOfInputLines { };
	std::array<size_t, required_tokens_count> int_numOfInputLines { };
	std::array< std::string_view, required_tokens_count > foundTokens;

	bool isValid;

	do
	{
		const size_t lengthOfInputStr { util::get_chars_from_input( std::cin, str_numOfInputLines ) };

		const size_t foundTokensCount { util::tokenize_fast( { str_numOfInputLines.data( ), lengthOfInputStr },
															 foundTokens, required_tokens_count ) };

		isValid = { foundTokensCount == required_tokens_count &&
					util::convert_tokens_to_integers<size_t>( foundTokens, int_numOfInputLines,
															  { min_allowed_num_of_input_lines,
															  	max_allowed_num_of_input_lines } ) };

	} while ( !isValid );

	return int_numOfInputLines[0];
}

auto CharMatrix::getMatrixAttributes( )
{
	static constexpr streamsize stream_size { default_buffer_size };

	std::array<char, stream_size> str_enteredMatrixAttributes { };
	std::tuple<uint32_t, uint32_t, char> tuple_enteredMatrixAttributes { };

	bool isAcceptable;

	do
	{
		const size_t lengthOfInputStr { util::get_chars_from_input( std::cin, str_enteredMatrixAttributes ) };

		isAcceptable = { validateEnteredMatrixAttributes( { str_enteredMatrixAttributes.data( ), lengthOfInputStr },
														  tuple_enteredMatrixAttributes ) };

	} while ( !isAcceptable );

	return tuple_enteredMatrixAttributes;
}

void CharMatrix::getCoords( )
{
	const size_t numOfInputLines { getNumOfInputLines( ) };

	static constexpr streamsize stream_size { default_buffer_size };
	static constexpr size_t required_tokens_count { cartesian_components_count };

	std::array<char, stream_size> str_enteredCoords { };
	std::array<uint32_t, required_tokens_count> int_enteredCoords { };

	for ( size_t counter { }; counter < numOfInputLines; ++counter )
	{
		bool isAcceptable;

		do
		{
			const size_t lengthOfInputStr { util::get_chars_from_input( std::cin, str_enteredCoords ) };

			isAcceptable = { validateEnteredCoords( { str_enteredCoords.data( ), lengthOfInputStr },
													int_enteredCoords ) };

		} while ( !isAcceptable );

		setCharacterMatrix( int_enteredCoords );
	}
}

inline void CharMatrix::draw( std::ostream& output_stream ) const
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

	LOG( "\nFinished." );
	WAIT;
}

std::ofstream& operator<<( std::ofstream& ofs, const CharMatrix& char_matrix )
{
	ofs.write( reinterpret_cast<const char*>( &char_matrix.getY_AxisLen( ) ),
			   sizeof( char_matrix.getY_AxisLen( ) ) );
	ofs.write( reinterpret_cast<const char*>( &char_matrix.getX_AxisLen( ) ),
			   sizeof( char_matrix.getX_AxisLen( ) ) );
	ofs.write( reinterpret_cast<const char*>( &char_matrix.getFillCharacter( ) ),
			   sizeof( char_matrix.getFillCharacter( ) ) );
	ofs.write( reinterpret_cast<const char*>( char_matrix.getCharacterMatrix( ).data( ) ),
											  char_matrix.getCharacterMatrix( ).size( ) );

	return ofs;
}

std::ifstream& operator>>( std::ifstream& ifs, CharMatrix& char_matrix )
{
	static CharMatrix temp_char_matrix { CharMatrix::default_y_axis_len,
										 CharMatrix::default_x_axis_len,
										 CharMatrix::default_fill_character };

	ifs.read( reinterpret_cast<char*>( &temp_char_matrix.m_Y_AxisLen ),
			  sizeof( temp_char_matrix.m_Y_AxisLen ) );
	ifs.read( reinterpret_cast<char*>( &temp_char_matrix.m_X_AxisLen ),
			  sizeof( temp_char_matrix.m_X_AxisLen ) );
	ifs.read( reinterpret_cast<char*>( &temp_char_matrix.m_fillCharacter ),
			  sizeof( temp_char_matrix.m_fillCharacter ) );
	temp_char_matrix.m_characterMatrix.resize( temp_char_matrix.getY_AxisLen( ) *
											   temp_char_matrix.getX_AxisLen( ) );
	ifs.read( reinterpret_cast<char*>( temp_char_matrix.m_characterMatrix.data( ) ),
									   temp_char_matrix.m_characterMatrix.size( ) );

	char_matrix.m_Y_AxisLen = temp_char_matrix.getY_AxisLen( );
	char_matrix.setY_AxisLen( temp_char_matrix.getY_AxisLen( ) );
	char_matrix.m_X_AxisLen = temp_char_matrix.getX_AxisLen( );
	char_matrix.setX_AxisLen( temp_char_matrix.getX_AxisLen( ) );
	char_matrix.m_fillCharacter = temp_char_matrix.getFillCharacter( );
	char_matrix.setFillCharacter( temp_char_matrix.getFillCharacter( ) );
	char_matrix.m_characterMatrix.reserve( temp_char_matrix.getCharacterMatrix( ).size( ) );
	char_matrix.m_characterMatrix.clear( );
	std::copy( temp_char_matrix.getCharacterMatrix( ).cbegin( ),
			   temp_char_matrix.getCharacterMatrix( ).cend( ),
			   std::back_inserter( char_matrix.m_characterMatrix ) );

	return ifs;
}

inline void CharMatrix::initialize( )
{
	std::ios_base::sync_with_stdio( false );
}

void CharMatrix::runScript( )
{
	// initialize( );

#if FULL_INPUT_MODE == 1
	const auto [ Y_AxisLen, X_AxisLen, fillCharacter ] { getMatrixAttributes( ) };
#else
	[[ maybe_unused ]] static constexpr uint32_t Y_AxisLen { 36 };
	[[ maybe_unused ]] static constexpr uint32_t X_AxisLen { 168 };
	[[ maybe_unused ]] static constexpr char fillCharacter { ' ' };

	static_assert( Y_AxisLen >= min_allowed_y_axis_len && Y_AxisLen <= max_allowed_y_axis_len,
				   "Y_AxisLen can not be greater than max_allowed_y_axis_len or "
				   "less than min_allowed_y_axis_len" );

	static_assert( X_AxisLen >= min_allowed_x_axis_len && X_AxisLen <= max_allowed_x_axis_len,
				   "X_AxisLen can not be greater than max_allowed_x_axis_len or "
				   "less than min_allowed_x_axis_len" );
#endif


constexpr bool HEAP_ALLOCATED { false };

if constexpr ( HEAP_ALLOCATED )
{
	const auto matrix { std::make_unique<CharMatrix>( Y_AxisLen, X_AxisLen , fillCharacter ) };

	matrix->getCoords( );
	matrix->draw( std::cout );
}
else
{
	auto matrix { CharMatrix( Y_AxisLen, X_AxisLen , fillCharacter ) };

	matrix.getCoords( );
	matrix.draw( std::cout );
}

}

}
