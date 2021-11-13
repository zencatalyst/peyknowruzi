
#include "CharMatrix_Exceptions.h"

using namespace peyknowruzi;


Invalid_Fill_Character_Exception::Invalid_Fill_Character_Exception( const std::string& what_arg )
: std::invalid_argument( what_arg )
{
}

Invalid_Y_Axis_Len_Exception::Invalid_Y_Axis_Len_Exception( const std::string& what_arg )
: std::invalid_argument( what_arg )
{
}

Invalid_X_Axis_Len_Exception::Invalid_X_Axis_Len_Exception( const std::string& what_arg )
: std::invalid_argument( what_arg )
{
}
