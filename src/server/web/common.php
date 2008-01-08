/* common.php
 *
 * Copyright 2008 Eliot Eshelman
 * battlestartux@6by9.net
 *
 *
 *  This file is part of Battlestar Tux.
 *
 *  Battlestar Tux is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  Battlestar Tux is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Battlestar Tux; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */


<?php

	/* Ensure that user input is safe and valid.
	 * Any value that is not a number will be replaced by $default.
	 * Caller may specify whether negative numbers and 0 are allowed. */
	function validateNum( $num, $default, $allowZero ) {
		if( !is_numeric($num) )
			$num = $default;
		else
			if( $allowZero ) {
				if( $num < 0 )
					$num = $default;
			}
			else {
				if( $num <= 0 )
					$num = $default;
			}

		return $num;
	}


	/* Ensure that user input is safe and valid.
	 * Remove any potential attacks from strings. */
	function validateTagString( $string ) {
		return mysql_real_escape_string( stripslashes($string) );
	}

?>
