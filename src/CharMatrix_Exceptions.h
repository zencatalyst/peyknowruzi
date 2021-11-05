
#pragma once

#include "pch.h"


namespace peyknowruzi
{

class Invalid_Fill_Character_Exception : public std::exception
{
public:
	virtual const char* what( ) const throw( );
};

class Invalid_Y_Axis_Len_Exception : public std::exception
{
public:
	virtual const char* what( ) const throw( );
};

class Invalid_X_Axis_Len_Exception : public std::exception
{
public:
	virtual const char* what( ) const throw( );
};

}
