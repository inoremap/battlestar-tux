<?php

/* emission_lines.php
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


require_once( '../../db.php' );
require_once( '../../settings.php' );


$db = connect_db();

$line_plot = imagecreatefrompng( 'emission_plot.png' );

($atomic_num = $_REQUEST['atomic_num']) || ($atomic_num = 1);
$line_plot = generate_emission_plot( $line_plot, $db, $atomic_num );

/* We'll be sending a PNG image instead of text. */
header( 'Content-type: image/png' );
imagesavealpha( $line_plot, true );
imagepng( $line_plot, NULL, 9, PNG_NO_FILTER );
imagedestroy( $line_plot );


/* Generate spectral emission line plot for element. */
function generate_emission_plot( $plot, $db, $atomic_num ) {
	/* Load emission lines. */
	$lines = array();
	$lines[0] = imagecreatefrompng( 'lines/0.png' );
	$lines[1] = imagecreatefrompng( 'lines/1.png' );
	$lines[2] = imagecreatefrompng( 'lines/2.png' );
	$lines[3] = imagecreatefrompng( 'lines/3.png' );
	$lines[4] = imagecreatefrompng( 'lines/4.png' );
	$lines[5] = imagecreatefrompng( 'lines/5.png' );
	$lines[6] = imagecreatefrompng( 'lines/6.png' );
	$lines[8] = imagecreatefrompng( 'lines/8.png' );
	$lines[9] = imagecreatefrompng( 'lines/9.png' );
	$lines[10] = imagecreatefrompng( 'lines/10.png' );
	$lines[17] = imagecreatefrompng( 'lines/17.png' );
	$lines[18] = imagecreatefrompng( 'lines/18.png' );

	/* Overlay lines onto plot. */
	$query = mysql_query( "SELECT * FROM element_emission WHERE atomic_number = '$atomic_num' ORDER BY intensity", $db );
	if( $query && mysql_num_rows($query) ) {
		/* Add each emission line individually. */
		while( $emission_line = mysql_fetch_row($query) ) {
			$wavelength = $emission_line[1];
			$intensity = $emission_line[2];
			$type = $emission_line[3];

			$pos = intval( log10($wavelength) * -100 + 550 - 30 );
			$width = 60;
			if( ($pos + $width) > 800 )
				$width = 800 - $pos;
			imagecopy( $plot, $lines[$type], $pos, 10, 0, 0, $width, 30 );

			/* For debugging */
if( $_REQUEST['debug'] ) {
				print "i: $i\tElement: $atomic_num\tWavelength: $wavelength\tIntensity: $intensity\tType: $type\tPosition: $pos\tWidth: $width";
				print "<br>\n";
			}
		}
	}

	return $plot;
}


?>
