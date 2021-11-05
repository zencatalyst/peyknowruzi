
#include "CharMatrix_Exceptions.h"
#include "CharMatrix.h"

using namespace peyknowruzi;


const char* Invalid_Fill_Character_Exception::what( ) const throw( )
{
	size_t elementCount { };
	std::stringstream ss;

	ss << "Invalid_Fill_Character_Exception: The 'fill character' is not allowed to be one of the following characters: { ";

	for ( auto it = CharMatrix::CHAR_SET.cbegin( ); it != CharMatrix::CHAR_SET.cend( ); ++it )
	{
		++elementCount;
		if ( elementCount == CharMatrix::CHAR_SET.size( ) ) { ss << "'" << *it << "' }"; }
		else { ss << "'" << *it << "', "; }
	}

	const std::string tempMsgStr { ss.str( ) };

	char* Invalid_Fill_Character_Exception_Msg = new char[ tempMsgStr.length( ) + 1 ];
	std::strcpy( Invalid_Fill_Character_Exception_Msg, tempMsgStr.c_str( ) );

	return Invalid_Fill_Character_Exception_Msg;
}

const char* Invalid_Y_Axis_Len_Exception::what( ) const throw( )
{
	std::stringstream ss;

	ss << "Invalid_Y_Axis_Len_Exception: The 'Y-axis length' is not allowed to be greater than " <<
			MAX_ALLOWED_Y_AXIS_LEN << " and lesser than " << MIN_ALLOWED_Y_AXIS_LEN << ".";

	const std::string tempMsgStr { ss.str( ) };

	char* Invalid_Y_Axis_Len_Exception_Msg = new char[ tempMsgStr.length( ) + 1 ];
	std::strcpy( Invalid_Y_Axis_Len_Exception_Msg, tempMsgStr.c_str( ) );

	return Invalid_Y_Axis_Len_Exception_Msg;
}

const char* Invalid_X_Axis_Len_Exception::what( ) const throw( )
{
	std::stringstream ss;

	ss << "Invalid_X_Axis_Len_Exception: The 'X-axis length' is not allowed to be greater than " <<
			MAX_ALLOWED_X_AXIS_LEN << " and lesser than " << MIN_ALLOWED_X_AXIS_LEN << ".";

	const std::string tempMsgStr { ss.str( ) };

	char* Invalid_X_Axis_Len_Exception_Msg = new char[ tempMsgStr.length( ) + 1 ];
	std::strcpy( Invalid_X_Axis_Len_Exception_Msg, tempMsgStr.c_str( ) );

	return Invalid_X_Axis_Len_Exception_Msg;
}
