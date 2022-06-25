
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


#include "Scripts.hpp"
#include "CharMatrix.hpp"
#include "Log.hpp"
#include "Util.hpp"
#include "pch.hpp"


namespace peyknowruzi
{

void runScripts( )
{
	runScript( );
}

void exit_handler( )
{
#if PN_DEBUG == 1
	using std::string_literals::operator""s;

	log( "\nProgram execution ended in "s +
		 /*( std::stringstream { } << util::retrieve_current_local_time( ) ).str( ) +*/
		 "\n"s );
#endif
}

const int flag { std::atexit( exit_handler ) };

}
