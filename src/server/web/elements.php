<?php

/* elements.php
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


/* Print detailed atomic properties. */
function print_element( $db, $atomic_num ) {
	$query = mysql_query( "SELECT * FROM elements WHERE atomic_number = '$atomic_num' LIMIT 1", $db );
	if( $query && mysql_num_rows($query) ) {
		$query = mysql_fetch_row( $query );

		print "<div class=\"content\">\n";
		print "	<div class=\"heading\">$query[1] ($query[2])</div>\n";
		print "	<div>Density: $query[5] g/cm<sup>3</sup></div>\n";
		print "	<div>Melting Point: $query[6] Kelvin</div>\n";
		print "	<div>Boiling Point: $query[7] Kelvin</div>\n";
		print "	<div>Emission/Absorbtion Properties:<br /><img src=\"/" . BTUX_PATH . "/images/emission_lines/emission_plot.php?atomic_num=$atomic_num\" width=800 height=150 alt=\"$query[1] Emission/Absorbtion\" /></div>\n";
		print "</div>\n";
	}
}


/* Print periodic table of elements. Determine phase based on current temperature. */
function print_periodic( $db ) {
	print "<div class=\"content\">\n";
	print "	<div class=\"heading\">Atomic Elements</div>\n";
	print "	<table class=\"periodic\">\n";

	// Print all elements but the lanthanides and actinides.
	for( $e = 1; $e <= 118; $e++ ) {
		// The top of the table doesn't list elements consecutively.
		if( $e == 2 )
			print "			<td class=\"blank\" colspan=\"16\">&nbsp;</td>\n";
		elseif( $e == 5 )
			print "			<td class=\"blank\" colspan=\"10\">&nbsp;</td>\n";
		elseif( $e == 13 )
			print "			<td class=\"blank\" colspan=\"10\">&nbsp;</td>\n";
		// These elements are at the beginning of a row.
		elseif( $e == 1 )
			print "		<tr>\n";
		elseif( $e == 3 )
			print "		<tr>\n";
		elseif( $e == 11 )
			print "		<tr>\n";
		elseif( $e == 19 )
			print "		<tr>\n";
		elseif( $e == 37 )
			print "		<tr>\n";
		elseif( $e == 55 )
			print "		<tr>\n";
		elseif( $e == 87 )
			print "		<tr>\n";
		// The lanthanides and actinides are printed later.
		if( $e == 57 ) {
			print "			<td class=\"blank\">*</td>\n";
			$e = 72;
		}
		elseif( $e == 89 ) {
			print "			<td class=\"blank\">**</td>\n";
			$e = 104;
		}


		// Print the element with the given atomic number.
		print_element_cell( $db, $e, $_SESSION['temperature'] );


		// These elements are at the end of a row.
		if( $e == 2 )
			print "		</tr>\n";
		elseif( $e == 10 )
			print "		</tr>\n";
		elseif( $e == 18 )
			print "		</tr>\n";
		elseif( $e == 36 )
			print "		</tr>\n";
		elseif( $e == 54 )
			print "		</tr>\n";
		elseif( $e == 86 )
			print "		</tr>\n";
		elseif( $e == 118 )
			print "		</tr>\n";
	}

	print "		<tr><td class=\"blank\" colspan=\"18\">&nbsp;</td></tr>\n";

	// Print the lanthanides and actinides.
	for( $e = 57; $e <= 103; $e++ ) {
		// These elements are at the beginning of a row.
		if( $e == 57 ) {
			print "		<tr>\n";
			print "			<td class=\"blank\" colspan=\"3\">* Lanthanides</td>\n";
		}
		elseif( $e == 89 ) {
			print "		<tr>\n";
			print "			<td class=\"blank\" colspan=\"3\">** Actinides</td>\n";
		}


		// Print the element with the given atomic number.
		print_element_cell( $db, $e, $_SESSION['temperature'] );


		// These elements are at the end of a row.
		if( $e == 71 ) {
			print "		</tr>\n";

			// skip ahead to actinides
			$e = 88;
		}
		elseif( $e == 103 )
			print "		</tr>\n";
	}


	// Form for changing temperature.
	print "		<tr><td class=\"blank\" colspan=\"18\"><form method=\"post\" action=\"/" . BTUX_PATH . "index.php?panel=elements\">\n";
	print "			Temperature: <input name=\"temperature\" value=\"" . html_output($_SESSION['temperature']) . "\" type=\"text\" size=\"6\" maxlength=\"5\" /><input type=\"submit\" value=\"Change\" />\n";
	print "		</form></td></tr>\n";



	print "	</table>\n";
	print "</div>\n";
}


/* Print a single element and its properties. */
function print_element_cell( $db, $atomic_num, $temperature ) {
	$query = mysql_query( "SELECT * FROM elements WHERE atomic_number = '$atomic_num' LIMIT 1", $db );
	if( $query && mysql_num_rows($query) ) {
		$query = mysql_fetch_row( $query );

		// Determine the element's phase at 0 celsius.
		$phase = 'solid';
		if( $query[7] < $temperature )
			$phase = 'gas';
		elseif( $query[6] < $temperature )
			$phase = 'liquid';

		print "			<td class=\"$phase\"><a class=\"element\" href=\"/" . BTUX_PATH . "index.php?panel=elements&amp;element=$atomic_num\"><div class=\"symbol\">$query[2]</div><div class=\"number\">$query[0]</div></a></td>\n";
	}
}


?>
