
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
using namespace peyknowruzi;


static constexpr uint32_t min_allowed_y_axis_len { 1 };
static constexpr uint32_t min_allowed_x_axis_len { 2 };
static constexpr uint32_t max_allowed_y_axis_len { 50 };
static constexpr uint32_t max_allowed_x_axis_len { 168 };
static constexpr size_t max_possible_num_of_input_lines { ( max_allowed_y_axis_len * ( max_allowed_x_axis_len - 1 ) ) / 2 };
static constexpr size_t min_possible_num_of_input_lines { 0 };
static constexpr size_t matrix_attributes_count { 3 };

static_assert( default_y_axis_len >= min_allowed_y_axis_len && default_y_axis_len <= max_allowed_y_axis_len,
			   "default_y_axis_len can not be greater than max_allowed_y_axis_len or less than min_allowed_y_axis_len" );

static_assert( default_x_axis_len >= min_allowed_x_axis_len && default_x_axis_len <= max_allowed_x_axis_len,
			   "default_x_axis_len can not be greater than max_allowed_x_axis_len or less than min_allowed_x_axis_len" );

static_assert( max_possible_num_of_input_lines <= ( max_allowed_y_axis_len * ( max_allowed_x_axis_len - 1 ) ) / 2 && max_possible_num_of_input_lines >= 0,
			   "max_possible_num_of_input_lines can not be greater than ( max_allowed_y_axis_len * max_allowed_x_axis_len ) / 2 or "
			   "less than 0" );

static_assert( min_possible_num_of_input_lines <= ( max_allowed_y_axis_len * ( max_allowed_x_axis_len - 1 ) ) / 2 && min_possible_num_of_input_lines >= 0
			   && min_possible_num_of_input_lines <= max_possible_num_of_input_lines,
			   "min_possible_num_of_input_lines can not be greater than ( max_allowed_y_axis_len * max_allowed_x_axis_len ) / 2 or "
			   "less than 0 or greater than max_possible_num_of_input_lines" );


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

inline const uint32_t& CharMatrix::getY_AxisLen( ) const noexcept
{
	return m_Y_AxisLen;
}

inline const uint32_t& CharMatrix::getX_AxisLen( ) const noexcept
{
	return m_X_AxisLen;
}

inline const char& CharMatrix::getFillCharacter( ) const noexcept
{
	return m_fillCharacter;
}

inline const std::vector<char>& CharMatrix::getCharacterMatrix( ) const noexcept
{
	return m_characterMatrix;
}

void CharMatrix::setY_AxisLen( const uint32_t Y_AxisLen )
{
	if ( Y_AxisLen == getY_AxisLen( ) ) { return; }

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

	if ( Y_AxisLen > getY_AxisLen( ) )
	{
		m_characterMatrix.resize( m_characterMatrix.size( ) + ( Y_AxisLen - getY_AxisLen( ) ) *
								  getX_AxisLen( ), getFillCharacter( ) );

		for ( size_t last_idx_of_row { ( getY_AxisLen( ) + 1 ) * getX_AxisLen( ) - 1 }
			  ; last_idx_of_row < m_characterMatrix.size( ); last_idx_of_row += getX_AxisLen( ) )
		{
			m_characterMatrix[ last_idx_of_row ] = '\n';
		}
	}
	else
	{
		m_characterMatrix.resize( m_characterMatrix.size( ) - ( getY_AxisLen( ) - Y_AxisLen ) *
								  getX_AxisLen( ) );
	}

	m_Y_AxisLen = { Y_AxisLen };
}

void CharMatrix::setX_AxisLen( const uint32_t X_AxisLen )
{
	if ( X_AxisLen == getX_AxisLen( ) ) { return; }

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

	if ( X_AxisLen > getX_AxisLen( ) )
	{
		m_characterMatrix.resize( getY_AxisLen( ) * X_AxisLen, getFillCharacter( ) );

		for ( auto new_it { m_characterMatrix.end( ) - 1 },
			  old_it { m_characterMatrix.begin( ) + ( getY_AxisLen( ) - 1 ) * getX_AxisLen( ) }
			  ; old_it >= m_characterMatrix.begin( ); old_it -= getX_AxisLen( ), --new_it )
		{
			*new_it = '\n';

			new_it -= X_AxisLen - getX_AxisLen( );
			std::fill_n( new_it, X_AxisLen - getX_AxisLen( ), getFillCharacter( ) );

			new_it -= getX_AxisLen( ) - 1;
			std::copy_n( old_it, getX_AxisLen( ) - 1, new_it );
		}
	}
	else
	{
		for ( auto new_it { m_characterMatrix.begin( ) },
			  old_it { m_characterMatrix.begin( ) }
			  ; old_it != m_characterMatrix.end( ); old_it += getX_AxisLen( ), ++new_it )
		{
			std::copy_n( old_it, X_AxisLen - 1, new_it );

			new_it += X_AxisLen - 1;
			*new_it = '\n';
		}

		m_characterMatrix.resize( getY_AxisLen( ) * X_AxisLen );
	}

	m_X_AxisLen = { X_AxisLen };
}

void CharMatrix::setFillCharacter( const char fillCharacter )
{
	if ( fillCharacter == getFillCharacter( ) ) { return; }

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

	for ( auto& elem : m_characterMatrix )
	{
		if ( elem == getFillCharacter( ) )
		{
			elem = fillCharacter;
		}
	}

	m_fillCharacter = { fillCharacter };
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

bool CharMatrix::validateEnteredMatrixAttributes( const std::array<char, default_buffer_size>& str_enteredMatrixAttributes,
												  std::tuple<uint32_t, uint32_t, char>& tuple_enteredMatrixAttributes_OUT )
{
	constexpr size_t required_tokens_count { matrix_attributes_count };
	constexpr std::array<size_t, 1> specificTokenIndexFor_Y_AxisLen { 0 };
	constexpr std::array<size_t, 1> specificTokenIndexFor_X_AxisLen { 1 };

	const auto [ hasExpectedTokenCount, foundTokens ] { util::tokenize( { str_enteredMatrixAttributes.data( ), str_enteredMatrixAttributes.size( ) },
																		required_tokens_count ) };
	if ( !hasExpectedTokenCount ) { return hasExpectedTokenCount; }

	std::array<uint32_t, required_tokens_count> int_enteredMatrix_YX { };

	const bool isValid { util::convert_specific_tokens_to_integers<uint32_t>( foundTokens, int_enteredMatrix_YX, specificTokenIndexFor_Y_AxisLen,
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

bool CharMatrix::validateEnteredCoords( const std::array<char, default_buffer_size>& str_enteredCoords,
										std::array<uint32_t, cartesian_components_count>& int_enteredCoords_OUT ) const
{
	constexpr size_t required_tokens_count { cartesian_components_count };
	constexpr std::array<size_t, 2> specificTokensIndicesFor_Y { 1, 3 };
	constexpr std::array<size_t, 2> specificTokensIndicesFor_X { 0, 2 };

	const uint32_t max_allowed_y { getY_AxisLen( ) - 1 };
	const uint32_t max_allowed_x { getX_AxisLen( ) - 2 };
	constexpr uint32_t min_allowed_y { 0 };
	constexpr uint32_t min_allowed_x { 0 };

	const auto [ hasExpectedTokenCount, foundTokens ] { util::tokenize( { str_enteredCoords.data( ), str_enteredCoords.size( ) },
																		required_tokens_count ) };
	if ( !hasExpectedTokenCount ) { return hasExpectedTokenCount; }

	const bool isValid { util::convert_specific_tokens_to_integers<uint32_t>( foundTokens, int_enteredCoords_OUT, specificTokensIndicesFor_Y,
						 													  { min_allowed_y, max_allowed_y } )
																																			&&
						 util::convert_specific_tokens_to_integers<uint32_t>( foundTokens, int_enteredCoords_OUT, specificTokensIndicesFor_X,
						 													  { min_allowed_x, max_allowed_x } ) ? true : false };

	return isValid;
}

inline std::optional< CharMatrix::AllowedChars >
CharMatrix::processCoordsToObtainCharType( const std::array<uint32_t, cartesian_components_count>& coordsOfChar ) noexcept
{
	if ( std::abs( static_cast<int64_t>( coordsOfChar[0] ) - static_cast<int64_t>( coordsOfChar[2] ) ) == 1 &&
		 std::abs( static_cast<int64_t>( coordsOfChar[1] ) - static_cast<int64_t>( coordsOfChar[3] ) ) == 1 &&
		 ( ( coordsOfChar[0] < coordsOfChar[2] && coordsOfChar[1] > coordsOfChar[3] ) ||
		   ( coordsOfChar[0] > coordsOfChar[2] && coordsOfChar[1] < coordsOfChar[3] ) ) )
	{
		return ForwardSlash;
	}
	else if ( std::abs( static_cast<int64_t>( coordsOfChar[0] ) - static_cast<int64_t>( coordsOfChar[2] ) ) == 1 &&
			  std::abs( static_cast<int64_t>( coordsOfChar[1] ) - static_cast<int64_t>( coordsOfChar[3] ) ) == 1 &&
			  ( ( coordsOfChar[0] < coordsOfChar[2] && coordsOfChar[1] < coordsOfChar[3] ) ||
			  	( coordsOfChar[0] > coordsOfChar[2] && coordsOfChar[1] > coordsOfChar[3] ) ) )
	{
		return BackSlash;
	}
	else if ( ( coordsOfChar[0] == coordsOfChar[2] ) &&
			  std::abs( static_cast<int64_t>( coordsOfChar[1] ) - static_cast<int64_t>( coordsOfChar[3] ) ) == 1 )
	{
		return VerticalSlash;
	}
	else if ( ( coordsOfChar[1] == coordsOfChar[3] ) &&
			  std::abs( static_cast<int64_t>( coordsOfChar[0] ) - static_cast<int64_t>( coordsOfChar[2] ) ) == 1 )
	{
		return Dash;
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

	constexpr streamsize stream_size { default_buffer_size };
	constexpr size_t required_tokens_count { 1 };

	std::array<char, stream_size> str_numOfInputLines { };
	std::array<size_t, required_tokens_count> int_numOfInputLines { };

	bool isValid;

	do
	{
		util::get_char_input( str_numOfInputLines );

		const auto [ hasExpectedTokenCount, foundTokens ] { util::tokenize( { str_numOfInputLines.data( ), str_numOfInputLines.size( ) },
																			required_tokens_count ) };

		isValid = { hasExpectedTokenCount &&
					util::convert_tokens_to_integers<size_t>( foundTokens, int_numOfInputLines,
															  { min_allowed_num_of_input_lines, max_allowed_num_of_input_lines } ) };

	} while ( !isValid );

	return int_numOfInputLines[0];
}

auto CharMatrix::getMatrixAttributes( )
{
	constexpr streamsize stream_size { default_buffer_size };

	std::array<char, stream_size> str_enteredMatrixAttributes { };
	std::tuple<uint32_t, uint32_t, char> tuple_enteredMatrixAttributes { };

	bool isAcceptable;

	do
	{
		util::get_char_input( str_enteredMatrixAttributes );

		isAcceptable = { validateEnteredMatrixAttributes( str_enteredMatrixAttributes, tuple_enteredMatrixAttributes ) };

	} while ( !isAcceptable );

	return tuple_enteredMatrixAttributes;
}

void CharMatrix::getCoords( )
{
	const size_t numOfInputLines { getNumOfInputLines( ) };

	constexpr streamsize stream_size { default_buffer_size };
	constexpr size_t required_tokens_count { cartesian_components_count };

	std::array<char, stream_size> str_enteredCoords { };
	std::array<uint32_t, required_tokens_count> int_enteredCoords { };

	for ( size_t counter { }; counter < numOfInputLines; ++counter )
	{
		bool isAcceptable;

		do
		{
			util::get_char_input( str_enteredCoords );

			isAcceptable = { validateEnteredCoords( str_enteredCoords, int_enteredCoords ) };

		} while ( !isAcceptable );

		setCharacterMatrix( int_enteredCoords );
	}
}

inline void CharMatrix::writeToOutput( ) const
{
#if PN_DEBUG == 1
	{
	util::Timer timer;
#endif

	std::cout.write( getCharacterMatrix( ).data( ), static_cast<streamsize>( getCharacterMatrix( ).size( ) ) );

#if PN_DEBUG == 1
	}
#endif

	LOG( "\nFinished." );
	WAIT;
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
	constexpr uint32_t Y_AxisLen { 36 };
	constexpr uint32_t X_AxisLen { 168 };
	constexpr char fillCharacter { ' ' };

	static_assert( Y_AxisLen >= min_allowed_y_axis_len && Y_AxisLen <= max_allowed_y_axis_len,
				   "Y_AxisLen can not be greater than max_allowed_y_axis_len or less than min_allowed_y_axis_len" );

	static_assert( X_AxisLen >= min_allowed_x_axis_len && X_AxisLen <= max_allowed_x_axis_len,
				   "X_AxisLen can not be greater than max_allowed_x_axis_len or less than min_allowed_x_axis_len" );
#endif


#define HEAP_ALLOCATED 0

#if HEAP_ALLOCATED == 1
	const std::unique_ptr<CharMatrix> matrix { std::make_unique<CharMatrix>( Y_AxisLen, X_AxisLen , fillCharacter ) };

	matrix->getCoords( );
	matrix->writeToOutput( );
#else
	CharMatrix matrix { Y_AxisLen, X_AxisLen , fillCharacter };

	matrix.getCoords( );
	matrix.writeToOutput( );
#endif
}
