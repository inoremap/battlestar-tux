/* headers.php
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
	require_once( 'settings.php' );


	function printHead() {
		$css_path = '/' . BTUX_PATH . 'default.css';
		$javascript_path = '/' . BTUX_PATH . 'scripts/javascript.js';
		$home = '/' . BTUX_PATH . 'index.php';

		print <<<END_TEXT

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
	"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
<head>
	<title>Battlestar T.U.X.</title>
	<meta name="rating" content="general" />
	<meta name="copyright" content="Copyright 2007-2008 Eliot Eshelman" />
	<meta name="author" content="Eliot Eshelman" />
	<meta http-equiv="window-target" content="_top" />
	<link rel="stylesheet" type="text/css" href="$css_path" />
	<script type="text/javascript" src="$javascript_path"></script>
</head>
<body><a name="top"></a>
	<div id="title">Battlestar T.U.X.</div>
	<div id="menu">
		<div><a href="$home">Images</a></div>
		<div><a href="$home?type=showtags">Tags</a></div>
		<div><a href="$home?type=import">Import</a></div>
		<div><a href="$home?type=settings">Settings</a></div>
	</div>
	<div id="main">

END_TEXT;
	}


	function printFoot() {
		print <<<END_TEXT

	</div>
	<div id="footer">Copyright 2007-2008 Eliot Eshelman</div>
</body>
</html>
END_TEXT;
	}
?>
