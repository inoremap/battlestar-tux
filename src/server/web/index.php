<?php

/* index.php
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


require_once( 'db.php' );
require_once( 'headers.php' );
require_once( 'elements.php' );
require_once( 'information.php' );
require_once( 'session.php' );

$db = connect_db();

/* If the database is unavailable, it's best to stop now. */
if( ! $db ) {
		print "<div class=\"error\">This page is temporarily unavailable.</div>\n";
		exit( 1 );
}


start_game_session( $db );
print_head();


($panel = $_REQUEST['panel']) || ($panel = 'overview');


// Ensure the user is logged in.
if( login($db) ) {
	print_nav();

	// Print overview of user's game.
	if( strcmp($panel,'overview') == 0 )
		print "Overview\n";

	// Display user's inventory.
	elseif( strcmp($panel,'inventory') == 0 )
		print "Inventory\n";

	// Manage production of units.
	elseif( strcmp($panel,'production') == 0 )
		print "Production\n";

	// Display atomic element properties.
	elseif( strcmp($panel,'elements') == 0 ) {
		if( $element = $_REQUEST['element'] )
			print_element( $db, validate_num($element, 1, false) );
		($temperature = $_GET['temperature']) || ($temperature = $_POST['temperature']) || ($temperature = $_SESSION['temperature']);
		$_SESSION['temperature'] = validate_num( $temperature, 273, false );

		print_periodic( $db );
	}

	// Print general game information.
	elseif( strcmp($panel,'information') == 0 ) {
		print_game_info( $db );
	}
}

// User not logged in.
else {
	print_nav();


	// Print general game information.
	if( strcmp($panel,'information') == 0 ) {
		print_game_info( $db );
	}
}

print_foot();


?>
