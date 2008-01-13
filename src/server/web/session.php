<?php

/* session.php
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

	require_once( 'common.php' );

	/* Start PHP session - store user data. */
	function start_game_session() {
		session_start();

var_dump( $_SESSION );

		// User would like to log out.
		if( $_REQUEST['logout'] ) {
			stop_game_session();
			print "<div class=\"logout\">Successfully logged out.</div>\n";
		}
	}


	/* Stop PHP session - log out. */
	function stop_game_session() {
		session_destroy();
	}


	/* Log in a new user.
	 * If the user is already logged in, this is transparent.
	 * Returns true if a user is logged in.  */
	function login( $db ) {
		// User is not currently logged in.
		if( ! $_SESSION['bt_auth'] ) {
			// If this variable is set, the user needs a new account.
			if( $_REQUEST['new_account'] ) {
				$username = html_input( $_REQUEST['new_bt_username'] );
				$password = html_input( $_REQUEST['new_bt_password'] );
				$password_confirm = html_input( $_REQUEST['new_bt_password_confirm'] );
				$email = html_input( $_REQUEST['new_bt_email'] );

				// Determine if any values are missing.
				$submitted = $username || $password || $password_confirm || $email;
				if( ! $username && $submitted )
					print "<div class=\"error\">Please enter a username.</div>\n";
				if( ! $password && $submitted )
					print "<div class=\"error\">Please enter a password.</div>\n";
				if( ! $password_confirm && $submitted )
					print "<div class=\"error\">Please enter a password and password confirmation.</div>\n";
				if( ! $email && $submitted )
					print "<div class=\"error\">Please enter an e-mail address in case of lost password.</div>\n";
				if( strcmp($password, $password_confirm) != 0 ) {
					print "<div class=\"error\">Please ensure the two passwords are identical.</div>\n";
					$password_confirm = false;
				}

				// If all variables are set, try to create account.
				if( $username && $password && $password_confirm && $email ) {
					// Determine if the user already exists.
					$query = mysql_query( "SELECT user_id FROM users WHERE username = '" . validate_sql_string($username) . "' LIMIT 1", $db );
					if( $query && mysql_num_rows($query) )
						print "<div class=\"error\">The user " . html_output($username) . " already exists.</div>\n";
					// Everything is good - create account.
					else {
						mysql_query( "INSERT INTO `users` ( `user_id`, `username`, `password`, `email`, `join_date`, `login_date` ) VALUES ( '', '" . validate_sql_string($username) . "', '" . md5($password) . "', '" . validate_sql_string($email) . "', NOW(), NOW() )", $db );
						$user_id = mysql_insert_id();

						// Account successfully created.
						if( $user_id ) {
							$_SESSION['bt_auth'] = true;
							$_SESSION['bt_username'] = $username;

							return true;
						}
					}
				}

				print "<form class=\"login\" method=\"post\" action=\"/" . BTUX_PATH . "\"><input type=\"hidden\" name=\"new_account\" value=\"true\" />\n";
				print "	<div class=\"heading\">Remote Login Account Creation</div>\n";
				print "	<table>\n";
				print "		<tr><th>Username:</th><td><input name=\"new_bt_username\" value=\"" . html_output($username) . "\" type=\"text\" size=\"16\" maxlength=\"32\" /></td></tr>\n";
				print "		<tr><th>Password:</th><td><input name=\"new_bt_password\" value=\"\" type=\"password\" size=\"16\" maxlength=\"32\" /></td></tr>\n";
				print "		<tr><th>Confirm Password:</th><td><input name=\"new_bt_password_confirm\" value=\"\" type=\"password\" size=\"16\" maxlength=\"32\" /></td></tr>\n";
				print "		<tr><th>E-Mail:</th><td><input name=\"new_bt_email\" value=\"" . html_output($email) . "\" type=\"text\" size=\"32\" maxlength=\"64\" /></td></tr>\n";
				print "		<tr><th colspan=\"2\"><input type=\"submit\" value=\"Create Account\" /></th></tr>\n";
				print "	</table>\n";
				print "</form>\n";
			}

			// User has not yet logged in - but isn't creating a new account.
			else {
				$username = html_input( $_REQUEST['bt_username'] );
				$password = html_input( $_REQUEST['bt_password'] );

				// If these variables are set, the user is trying to log in.
				if( $username && $password ) {
					$query = mysql_query( "SELECT password FROM users WHERE username = '" . validate_sql_string($username) . "' LIMIT 1", $db );
					if( $query && mysql_num_rows($query) ) {
						$query = mysql_fetch_row( $query );

						// If passwords match, user is logged in.
						if( strcmp(md5($password), $query[0]) == 0 ) {
							$_SESSION['bt_auth'] = true;
							$_SESSION['bt_username'] = $username;

							// Update last login time.
							mysql_query( "UPDATE users SET login_date = NOW() WHERE username = '" . validate_sql_string($username) . "' LIMIT 1", $db );

							return true;
						}
					}

					print "<div class=\"error\">Login denied - please try again.</div>\n";
				}

				if( ! $username && $password )
					print "<div class=\"error\">Please enter your username.</div>\n";
				if( ! $password && $username )
					print "<div class=\"error\">Please enter your password.</div>\n";

				print "<form class=\"login\" method=\"post\" action=\"/" . BTUX_PATH . "\">\n";
				print "	<div class=\"heading\">Remote Login</div>\n";
				print "	<table>\n";
				print "		<tr><th>Username:</th><td><input name=\"bt_username\" value=\"" . html_output($username) . "\" type=\"text\" size=\"16\" maxlength=\"32\" /></td></tr>\n";
				print "		<tr><th>Password:</th><td><input name=\"bt_password\" value=\"\" type=\"password\" size=\"16\" maxlength=\"32\" /></td></tr>\n";
				print "		<tr><th colspan=\"2\"><input type=\"submit\" value=\"Login\" /></th></tr>\n";
				print "	</table>\n";
				print "	<div class=\"new_account\"><a href=\"/" . BTUX_PATH . "index.php?new_account=1\">Create New Login Account</a></div>\n";
				print "</form>\n";
			}

			return false;
		}

		// User is already logged in.
		else
			return true;
	}
?>
