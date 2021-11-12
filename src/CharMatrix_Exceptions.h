
#pragma once

#include "pch.h"


namespace peyknowruzi
{

class Invalid_Fill_Character_Exception : public std::exception
{
public:
	Invalid_Fill_Character_Exception( );
	const char* what( ) const noexcept override;

private:
	std::string exceptionMsg;
};

class Invalid_Y_Axis_Len_Exception : public std::exception
{
public:
	Invalid_Y_Axis_Len_Exception( );
	const char* what( ) const noexcept override;

private:
	std::string exceptionMsg;
};

class Invalid_X_Axis_Len_Exception : public std::exception
{
public:
	Invalid_X_Axis_Len_Exception( );
	const char* what( ) const noexcept override;

private:
	std::string exceptionMsg;
};

}
