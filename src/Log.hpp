
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


#pragma once

#include "pch.hpp"


#if PN_DEBUG == 1
#define LOG(x) std::clog << ( x ) << std::endl
#define ERR(x) std::cerr << ( x ) << std::endl
#define WAIT std::cin.get( )
#else
#define LOG(x)
#define ERR(x)
#define WAIT
#endif


namespace peyknowruzi
{

inline void log( [[ maybe_unused ]] const std::string& msg )
{
#if PN_DEBUG == 1
	std::clog << msg << std::endl;
#endif
}

}
