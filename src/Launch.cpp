
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

// PeykNowruzi, basic implementation ( cross platform )
// repo available at https://github.com/zencatalyst/peyknowruzi


#include "Scripts.h"


namespace pynz = peyknowruzi;


inline static void launch( )
{
	pynz::runScripts( );
}

int main( [[ maybe_unused ]] int argc, [[ maybe_unused ]] char* argv[] )
{
	launch( );

	return 0;
}
