
#include "CharMatrix_Exceptions.h"
#include "CharMatrix.h"

using namespace peyknowruzi;


Invalid_Fill_Character_Exception::Invalid_Fill_Character_Exception( )
{
	exceptionMsg.reserve( 131 );

	exceptionMsg = "Invalid_Fill_Character_Exception: The 'fill character' is not allowed to be one of the following characters: { ";

	size_t appendedElementsCount { };

	for ( auto it = CharMatrix::CHAR_SET.cbegin( ); it != CharMatrix::CHAR_SET.cend( ); ++it )
	{
		exceptionMsg += "'";
		exceptionMsg += *it;

		++appendedElementsCount;
		if ( appendedElementsCount != CharMatrix::CHAR_SET.size( ) ) { exceptionMsg += "', "; }
		else { exceptionMsg += "' }"; }
	}
}

const char* Invalid_Fill_Character_Exception::what( ) const noexcept
{
	return exceptionMsg.c_str( );
}

Invalid_Y_Axis_Len_Exception::Invalid_Y_Axis_Len_Exception( )
{
	exceptionMsg.reserve( 105 );

	exceptionMsg = "Invalid_Y_Axis_Len_Exception: The 'Y-axis length' is not allowed to be greater than ";
	exceptionMsg += std::to_string( MAX_ALLOWED_Y_AXIS_LEN ) + " and lesser than ";
	exceptionMsg += std::to_string( MIN_ALLOWED_Y_AXIS_LEN ) + ".";
}

const char* Invalid_Y_Axis_Len_Exception::what( ) const noexcept
{
	return exceptionMsg.c_str( );
}

Invalid_X_Axis_Len_Exception::Invalid_X_Axis_Len_Exception( )
{
	exceptionMsg.reserve( 106 );

	exceptionMsg = "Invalid_X_Axis_Len_Exception: The 'X-axis length' is not allowed to be greater than ";
	exceptionMsg += std::to_string( MAX_ALLOWED_X_AXIS_LEN ) + " and lesser than ";
	exceptionMsg += std::to_string( MIN_ALLOWED_X_AXIS_LEN ) + ".";
}

const char* Invalid_X_Axis_Len_Exception::what( ) const noexcept
{
	return exceptionMsg.c_str( );
}
