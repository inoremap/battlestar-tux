/* Battlestar TUX
 * Copyright (C) 2010 Eliot Eshelman <battlestartux@6by9.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef UniqueNames_H
#define UniqueNames_H

#include <string>


// Code adapted from post by vitefalcon on Ogre 3D forums:
// http://www.ogre3d.org/forums/viewtopic.php?f=2&t=58048  (11/03/2010)


/** UniqueNames provides unique name IDs for game objects.
 * Ogre will throw exceptions if objects have the same names.
 */
class UniqueNames {
public:
    /// Get next default unique ID string.
    static std::string Next();

    /// Get next unique ID starting with prefix.
    static std::string Next(const std::string& prefix);

    /// Count number of unique names with default prefix.
    static size_t Count();

    /// Count number of unique names with prefix.
    static size_t Count(const std::string& prefix);

private:
    UniqueNames();
    ~UniqueNames();
    UniqueNames(const UniqueNames&);
    UniqueNames& operator=(const UniqueNames&);

    typedef std::map<std::string, uint32_t> NameCountMap;
    static NameCountMap s_nameCount;
};


#endif

