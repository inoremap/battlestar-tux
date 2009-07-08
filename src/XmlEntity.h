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


#ifndef XmlEntity_H
#define XmlEntity_H

class TiXmlElement;

/** XmlEntity provides an XML input/output interface for game objects.
 *
 * Each game object will need to define toXml() for serializing the data into
 * XML.  Most (all?) will also need to provide a constructor which builds the
 * object using XML input.
 */
class XmlEntity {
public:
    /// Default constructor.
    XmlEntity();

    /// Default destructor.
    virtual ~XmlEntity();

    /** Build XML structure with entity data/attributes.
     *
     * @param node XML element to add data to.  If node is NULL, a new node
     * will be automatically created.
     *
     * @attention This function creates a new TiXmlElement object, but will
     * rely on the caller to delete the object.
     */
    virtual void toXml(TiXmlElement* node) const;

private:
    XmlEntity(const XmlEntity&);
    XmlEntity& operator=(const XmlEntity&);
};


inline std::ostream & operator<<(std::ostream& out, XmlEntity* entity) {
    TiXmlElement* node = NULL;
    entity->toXml(node);

    out << node;
    delete node;

    return out;
}


#endif
