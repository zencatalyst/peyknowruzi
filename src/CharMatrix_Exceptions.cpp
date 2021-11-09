
#include "CharMatrix_Exceptions.h"
#include "CharMatrix.h"

using namespace peyknowruzi;


const char* Invalid_Fill_Character_Exception::what( ) const throw( )
{
	std::string tempMsg;
	tempMsg.reserve( 131 );

	tempMsg = "Invalid_Fill_Character_Exception: The 'fill character' is not allowed to be one of the following characters: { ";

	size_t appendedElementsCount { };

	for ( auto it = CharMatrix::CHAR_SET.cbegin( ); it != CharMatrix::CHAR_SET.cend( ); ++it )
	{
		tempMsg += "'";
		tempMsg += *it;

		++appendedElementsCount;
		if ( appendedElementsCount != CharMatrix::CHAR_SET.size( ) ) { tempMsg += "', "; }
		else { tempMsg += "' }"; }
	}

	char* Invalid_Fill_Character_Exception_Msg = new char[ tempMsg.length( ) + 1 ];
	std::strcpy( Invalid_Fill_Character_Exception_Msg, tempMsg.c_str( ) );

	return const_cast<const char*>( Invalid_Fill_Character_Exception_Msg );
}

const char* Invalid_Y_Axis_Len_Exception::what( ) const throw( )
{
	std::string tempMsg;
    tempMsg.reserve( 105 );

	tempMsg = "Invalid_Y_Axis_Len_Exception: The 'Y-axis length' is not allowed to be greater than ";
	tempMsg += std::to_string( MAX_ALLOWED_Y_AXIS_LEN ) + " and lesser than ";
	tempMsg += std::to_string( MIN_ALLOWED_Y_AXIS_LEN ) + ".";

	char* Invalid_Y_Axis_Len_Exception_Msg = new char[ tempMsg.length( ) + 1 ];
	std::strcpy( Invalid_Y_Axis_Len_Exception_Msg, tempMsg.c_str( ) );

	return const_cast<const char*>( Invalid_Y_Axis_Len_Exception_Msg );
}

const char* Invalid_X_Axis_Len_Exception::what( ) const throw( )
{
	std::string tempMsg;
    tempMsg.reserve( 106 );

	tempMsg = "Invalid_X_Axis_Len_Exception: The 'X-axis length' is not allowed to be greater than ";
	tempMsg	+= std::to_string( MAX_ALLOWED_X_AXIS_LEN ) + " and lesser than ";
	tempMsg	+= std::to_string( MIN_ALLOWED_X_AXIS_LEN ) + ".";

	char* Invalid_X_Axis_Len_Exception_Msg = new char[ tempMsg.length( ) + 1 ];
	std::strcpy( Invalid_X_Axis_Len_Exception_Msg, tempMsg.c_str( ) );

	return const_cast<const char*>( Invalid_X_Axis_Len_Exception_Msg );
}
