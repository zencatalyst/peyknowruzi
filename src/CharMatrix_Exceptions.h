
#pragma once

#include "pch.h"


namespace peyknowruzi
{

class Invalid_Fill_Character_Exception : public std::invalid_argument
{
public:
	explicit Invalid_Fill_Character_Exception( const std::string& what_arg );
};

class Invalid_Y_Axis_Len_Exception : public std::invalid_argument
{
public:
	explicit Invalid_Y_Axis_Len_Exception( const std::string& what_arg );
};

class Invalid_X_Axis_Len_Exception : public std::invalid_argument
{
public:
	explicit Invalid_X_Axis_Len_Exception( const std::string& what_arg );
};

}
