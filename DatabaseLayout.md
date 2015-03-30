#summary Server's Data Storage and Layout
#labels Phase-Design,Phase-Implementation


## Battlestar T.U.X. Game Data ##


### Atomic Element Emission Lines ###
Object properties in game are determined by their chemical make-up.  Their behavior when they are energized is mostly determined by the emission lines of their atoms.  Appearance may also be determined here, as many elements emit visible light when they are energized.

#  #
element\_emission
| **Column Name** | **Description** | **Data Type** |
|:----------------|:----------------|:--------------|
| atomic\_number | Atomic Number of Element (number of protons) | tinyint(1) |
| wavelength | Wavelength of electomagnetic emissions when energized (nanometers). | float |
| intensity | Strength of emissions at this wavelength (relative value [0-1000]). | float |
| attributes | Special features of emission wavelength, if any. | tinyint(1) |


### Atomic Elements ###
Chemical and physical properties of objects are determined by the atomic elements in them.When new objects are created, most of their characteristics will be based on the data here.

#  #
elements
| **Column Name** | **Description** | **Data Type** |
|:----------------|:----------------|:--------------|
| atomic\_number | Atomic Number of Element (number of protons) | tinyint(1) |
| name | Full name of element. | char(13) |
| symbol | One, two, or three letter abbreviation. | char(3) |
| period | Element's period on Periodic Table (column). | tinyint(1) |
| group | Element's group on Periodic Table (row). | tinyint(1) |
| density | Element's density (g/cm<sup>3</sup>) at 273K<sup>1</sup> **(needs reference)**. | float |
| melting\_point | Temperature at which element becomes a liquid<sup>1</sup>. | float |
| boiling\_point | Temperature at which element becomes a gas<sup>1</sup>. | float |
| color | Element's appearance (hex color code). | char(6) |


### Objects ###
All physical entities will be listed in this table.

#  #
objects
| **Column Name** | **Description** | **Data Type** |
|:----------------|:----------------|:--------------|
| object\_id | Unique ID number of this object. | int(4) |
| parent\_id | ID number of the parent object, if any. | int(4) |
| creation\_date | Date and time the object was created. | datetime |
| mass | Mass of object (kilograms). | float |
| melting\_point | Temperature at which object will become a liquid<sup>1</sup>. | float |
| boiling\_point | Temperature at which object will become a gas<sup>1</sup>. | float |
| defect\_rate | Statistical likelihood of defects in the object (values [0,1]). | float |
| energy\_input | Minimum amount of energy required to activate the object. | float |
| energy\_output | Maximum amount of energy produced by object when activated. | float |
| energy\_storage | Maximum amount of energy the object can store. | float |
| name | User defined name for object. | char(32) |
| object\_type | Type of object. | smallint(2) |


### Object Ownership ###
Determine which user owns which objects.

#  #
ownership
| **Column Name** | **Description** | **Data Type** |
|:----------------|:----------------|:--------------|
| user\_id | ID number of the user. | mediumint(3) |
| object\_id | ID number of the object. | int(4) |


### Game Users ###
All players of the game must be registered and logged in.

#  #
users
| **Column Name** | **Description** | **Data Type** |
|:----------------|:----------------|:--------------|
| user\_id | Unique user ID number. | mediumint(3) |
| username | Unique username. | char(32) |
| password | User's password (7+ characters) | char(32) |
| email | User's e-mail address. | char(64) |
| join\_date | Date and time the user signed up. | datetime |
| login\_date | Date and time the user last logged in. | datetime |
| logged\_in | Whether the user is currently logged in ((W)eb, (G)ame, or (0)). | char(1) |



<sup>1</sup> At standard pressure on Earth (sea level).