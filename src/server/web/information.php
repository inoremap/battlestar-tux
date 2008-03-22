<?php

/* information.php
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


/* General "out of character" game information.
 * Any information that would be considered in-game belongs elsewhere. */
function print_game_info( $db ) {
	print "<div class=\"content\">\n";
	print "	<div class=\"heading\">Current Game Statistics</div>\n";

	/* Find out who user is. */
	$query = mysql_query( "SELECT * FROM users WHERE username = '" . $_SESSION['bt_username'] . "' LIMIT 1", $db );
	if( $query && mysql_num_rows($query) ) {
		$query = mysql_fetch_row( $query );
		print "	<p>You have been logged in as \"$query[1]\" since $query[5].</p>\n";
	}
	else {
		print "	<p>You are not currently logged in.</p>\n";
	}

	/* Determine number of logged in users. */
	$query = mysql_query( "SELECT COUNT(*) FROM users WHERE logged_in != '0'", $db );
	if( $query && mysql_num_rows($query) ) {
		$query = mysql_fetch_row( $query );
		print "	<p>Users currently online: $query[0]</p>\n";
	}

	print "</div>\n";

	print "<div class=\"content\">\n";
	print "	<div class=\"heading\">Technical Details</div>\n";
	print "	<p>Battlestar T.U.X. is an open source game, meaning all the tools and resources used to create the game are freely available for download and reuse.  The game may be expanded and improved by anyone with the time and motivation, even if the original developers disappear.</p>\n";
	print "	<p>The servers running the game are not free, as they consume actual electrical and bandwidth resources.  Everyone who enjoys Battlestar T.U.X. is encouraged to contribute in one way or another, even if it's nothing more than a small donation.</p>\n";
	print "	<p>Anyone wishing to help out with the project or to learn more should visit the developer's page:\n";
	print "	<br /><a href=\"http://code.google.com/p/battlestar-tux/\">http://code.google.com/p/battlestar-tux/</a></p>\n";
	print "</div>\n";

	print "<div class=\"content\">\n";
	print "	<div class=\"heading\">Frequently Asked Questions</div>\n";
	print "		<ul class=\"text\">\n";

	print "			<li><p class=\"subheading\">Are the chemistry and physics simulations accurate? Can I use them to finish my homework/research?</p>\n";
	print "			<p>Although many of the values, characteristics and reactions in Battlestar T.U.X. are modeled after current scientific findings and theories, we have a very incomplete understanding of the universe.  If you look deeply enough, you will see elements that are not factual (although I *might* have guessed right).  For truly accurate scientific information, do your own research or look at the developer's <a href=\"http://code.google.com/p/battlestar-tux/wiki/THANKS\">references</a> section.</p>\n";
	print "			</li>\n";

	print "			<li><p class=\"subheading\">I have a great idea for an improvement to the game.  When can you add it?</p>\n";
	print "			<p>Any new feature ideas or game patches will be listed and discussed on the developer's <a href=\"http://code.google.com/p/battlestar-tux/issues/list\">issues</a> page.  Please list your feature requests and ideas there.  Although this is an open source project, development is already headed in a particular direction and resources are limited.  Some suggestions won't be possible and others won't fit the goals of this game.</p>\n";

	print "			</li>\n";
	print "		</ul>\n";
	print "</div>\n";
}


?>
