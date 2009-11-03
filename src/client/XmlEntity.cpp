/* Battlestar TUX
 * Copyright (C) 2009 Eliot Eshelman <battlestartux@6by9.net>
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

#include <tinyxml.h>

#include "XmlEntity.h"


XmlEntity::XmlEntity() {}
XmlEntity::~XmlEntity() {}

void XmlEntity::toXml(TiXmlElement* node) const {
    TiXmlElement* entityNode = new TiXmlElement("XmlEntity");

    entityNode->SetAttribute("error", "This XmlEntity did not define toXml().");

    // If a valid XML element wasn't passed, return one.
    // If a valid XML element was passed, link to it.
    if(!node)
        node = entityNode;
    else
        node->LinkEndChild(entityNode);
}
