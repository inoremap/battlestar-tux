#!/usr/bin/env python
#
# Copyright (c) 2011 Eliot Eshelman
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
###############################################################################

import logging

import Application


def initializeLogging():
    """Set up logging of in-game info/warnings/errors.
    All log messages are written to file and to the console, but the file
    and the console may have different log levels (e.g. DEBUG vs INFO).
    
    OGRE and CEGUI automatically create their own logs.
    """
    logging.basicConfig(level=logging.DEBUG,
                format='%(asctime)s %(levelname)-8s %(message)s',
                filename='BattlestarTUX.log',
                filemode='w')
    console = logging.StreamHandler()
    console.setLevel(logging.DEBUG)
    # set a format which is simpler for console use
    formatter = logging.Formatter('[battlestar-tux]: %(levelname)-8s %(message)s')
    console.setFormatter(formatter)
    logging.getLogger('').addHandler(console)
    logging.info("Game is starting...")


if __name__ == '__main__':
    initializeLogging()

    try:
        Application.go()
    except Exception:
        logging.exception("An unexpected error occurred. Application exiting...")
    finally:
        logging.info("Game is done - End Of Line")
        logging.shutdown()
