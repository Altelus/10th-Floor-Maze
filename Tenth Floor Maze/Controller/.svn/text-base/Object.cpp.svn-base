/* Object Implementation - Scene Component - Model Branch
 *
 * consists of Object base class
 *             Box class
 *             Grid class
 *
 * Object.cpp
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iScene.h"           // for the Scene Interface
#include "iGraphic.h"         // for the Graphic Interface
#include "iTexture.h"         // for the Texture Interface
#include "iSound.h"           // for the Sound Interface
#include "iLight.h"           // for the Light Interface
#include "iCamera.h"          // for the Camera Interface
#include "iText.h"            // for the Text Interface
#include "iUtilities.h"       // for error()

#include "Object.h"           // for Object, Box, Grid class declarations
#include "MathDeclarations.h" // for MODEL_Z_AXIS
#include "ModelSettings.h"    // for POINT_LIST, ...

#include "MathDefinitions.h"	// AKV - needed to do 3D math

//-------------------------------- Object -------------------------------------
//
// The Object Primitive represents a single object in the Scene Component
//
// The Scene Coordinator manages the Object Instances
//
iScene* Object::coordinator = NULL;

// Clone create a clone of Object* src and returns the address to its interface
//
iObject* Clone(const iObject* src) {

    return src->clone();
}

// constructor creates a 3-D scene object that is modelled by 'nPrimitives'
// graphics primitives of type 'pType' with material reflectivity 'c'
//
Object::Object(Colour c) : material(c), texture(NULL), sound(NULL), light(NULL), 
 noTexts(0) {
    
    if (!coordinator)
        error(L"Object::00 Couldn\'t access the Scene Coordinator");
    else if(!coordinator->add(this))
        error(L"Object::01 Couldn\'t add the object to the Scene Coordinator");

    flags   = TEX_DEFAULT;

	for (int i = 0; i < MAX_RPTS; i++) {
		text[i] = NULL;
		data[i] = NULL;
	}
}

// copy constructor initializes instance pointers and calls the assignment
// operator
//
Object::Object(const Object& src) {

    if (!coordinator)
        error(L"Object::00 Couldn\'t access the Scene Coordinator");
    else if(!coordinator->add(this))
        error(L"Object::01 Couldn\'t add the object to the Scene Coordinator");

    *this   = src;
}
            
// assignment operator discards old data and creates a copy from
// src - does not copy the texture or the text items attached to 
// src - instead initializes them to NULL - does not copy the 
// Graphic attached to src but creates a clone for the current
// object
//
Object& Object::operator=(const Object& src) {

    if (this != &src) {
        *((Frame*)this) = src;
        material        = src.material;
        flags           = src.flags;
        texture         = src.texture;
        sound           = NULL;
        camera          = NULL;
        light           = NULL;
        noTexts         = 0;
	    for (int i = 0; i < MAX_RPTS; i++) {
		    text[i] = NULL;
		    data[i] = NULL;
	    }
    }

    return *this;
}

// attach attaches iText* t to the object along with a pointer to function d for
// generating the text string to be reported
//
void Object::attach(const iText* t, const wchar_t* (*d)(wchar_t* s, const iObject*)) {

	if (noTexts < MAX_RPTS) {
		text[noTexts] = t;
		data[noTexts] = d;
		noTexts++;
	}
}

// attach attaches iTexture *t to the object and sets the filtering flags
//
void Object::attach(const iTexture* t, unsigned filter) {

	texture = t;
	if (filter) flags = filter;
}

// attach attaches iSound* s to the object and vice versa
//
void Object::attach(const iSound* s) {

	sound = s;
	if (sound)
		(const_cast<iSound*>(sound))->attach(this);
    else
		(const_cast<iSound*>(sound))->attach((iFrame*)NULL);
}

// attach attaches iLight* l to the object and vice versa
//
void Object::attach(const iLight* l) {

	light = l;
	if (light)
		(const_cast<iLight*>(light))->attach(this);
    else
		(const_cast<iLight*>(light))->attach((iFrame*)NULL);
}

// attach attaches iCamera* c to the object and vice versa
//
void Object::attach(const iCamera* c) {

	camera = c;
	if (camera)
		(const_cast<iCamera*>(camera))->attach(this);
    else
		(const_cast<iCamera*>(camera))->attach((iFrame*)NULL);
}

// draw draws the object if its opacity matches the opacity request
//
void Object::draw(bool opacity) const { 
	
	if (opacity == (material.a == 1.0f)) 
		draw(texture, flags); 
}

// report sets the text strings to be reported for the object
//
void Object::report() const {

	wchar_t str[MAX_DESC + 1];
	for (int i = 0; i < noTexts; i++)
		if (text[i] && data[i])
			const_cast<iText*>(text[i])->set(data[i](str, this));
}		

// destructor removes the object from the Scene coordinator
//
Object::~Object() {

    if (coordinator)
        coordinator->remove(this);
    else
        error(L"Object::90 Couldn\'t access the Scene Coordinator");
}

//
//
////-------------------------------- Board -------------------------------------
//// Board is an Object identifiable by two points - lower close left, and
//// upper faraway right - and a colour
//iObject* CreateBoard(float minx, float minz, float maxx, float maxz, float y, Colour c) {
//	return new Board(minx, minz, maxx, maxz, y, c);
//}
//
//// constructor builds the Board from its two extreme points one face at a time
//Board::Board(float minx, float minz, float maxx, float maxz, float y, Colour c) : Object(c) {
//	graphic = CreateGraphic(TRIANGLE_LIST, 12);
//	float x = (minx + maxx) / 2, z = (minz + maxz) / 2;
//    minx -= x;
//    minz -= z;
//    maxx -= x;
//    maxz -= z;
//    Vector p1 = Vector(minx, 0, minz),
//           p2 = Vector(minx, 0, minz),
//           p3 = Vector(maxx, 0, minz),
//           p4 = Vector(maxx, 0, minz);
//    graphic->add(p1, p2, p3, p4, Vector(0, 0, 0));
//    translate(x, y, z);
//}
//
//// copy constructor clones the graphic representation
////
//Board::Board(const Board& src) : Object(src) {
//
//    if (src.graphic)
//        graphic = src.graphic->clone();
//    else
//        graphic = NULL;
//}
//            
//// assignment operator discards old data and creates a copy from
//// src - does not copy the Graphic attached to src but creates a 
//// clone for the current object
////
//Board& Board::operator=(const Board& src) {
//
//    if (this != &src) {
//        *((Object*)this) = src;
//        if (graphic)
//            graphic->Delete();
//        if (src.graphic)
//            graphic = src.graphic->clone();
//        else
//            graphic = NULL;
//    }
//
//    return *this;
//}
//
//// draw draws the graphic representation of the Board
////
//void Board::draw(const iTexture* t, unsigned f) const { 
//    
//    if (graphic) graphic->draw(this, t, f); 
//} 
//
//// suspend suspends the object
////
//void Board::suspend() const { 
//	
//	if (graphic) 
//		const_cast<iGraphic*>(graphic)->suspend(); 
//}
//
//// release releases the object
////
//void Board::release() const { 
//	
//	if (graphic) 
//		const_cast<iGraphic*>(graphic)->release(); 
//}
//
//// destructor deletes the graphic model
////
//Board::~Board() {
//
//    if (graphic)
//        graphic->Delete();
//}



//-------------------------------- Box -------------------------------------
//
// Box is an Object identifiable by two points - lower close left, and
// upper faraway right - and a colour
//
iObject* CreateBox(float minx, float miny, float minz, float maxx, 
 float maxy, float maxz, Colour c) {

	return new Box(minx, miny, minz, maxx, maxy, maxz, c);
}

// constructor builds the Box from its two extreme points one face at a time
//
Box::Box(float minx, float miny, float minz, float maxx, float maxy,
 float maxz, Colour c) : Object(c) {

    graphic = CreateGraphic(TRIANGLE_LIST, 12);

    float x = (minx + maxx) / 2, y = (miny + maxy) / 2, z = (minz + maxz) / 2;
    minx -= x;
    miny -= y;
    minz -= z;
    maxx -= x;
    maxy -= y;
    maxz -= z;
    Vector p1 = Vector(minx, miny, minz),
           p2 = Vector(minx, maxy, minz),
           p3 = Vector(maxx, maxy, minz),
           p4 = Vector(maxx, miny, minz),
           p5 = Vector(minx, miny, maxz),
           p6 = Vector(minx, maxy, maxz),
           p7 = Vector(maxx, maxy, maxz),
           p8 = Vector(maxx, miny, maxz);
    graphic->add(p1, p2, p3, p4, Vector(0, 0, -1)); // front
    graphic->add(p4, p3, p7, p8, Vector(1, 0,  0)); // right
    graphic->add(p8, p7, p6, p5, Vector(0, 0,  1)); // back
    graphic->add(p6, p2, p1, p5, Vector(-1, 0, 0)); // left
    graphic->add(p1, p4, p8, p5, Vector(0, -1, 0)); // bottom
    graphic->add(p2, p6, p7, p3, Vector(0, 1,  0)); // top
    translate(x, y, z);
}

// copy constructor clones the graphic representation
//
Box::Box(const Box& src) : Object(src) {

    if (src.graphic)
        graphic = src.graphic->clone();
    else
        graphic = NULL;
}
            
// assignment operator discards old data and creates a copy from
// src - does not copy the Graphic attached to src but creates a 
// clone for the current object
//
Box& Box::operator=(const Box& src) {

    if (this != &src) {
        *((Object*)this) = src;
        if (graphic)
            graphic->Delete();
        if (src.graphic)
            graphic = src.graphic->clone();
        else
            graphic = NULL;
    }

    return *this;
}

// draw draws the graphic representation of the Box
//
void Box::draw(const iTexture* t, unsigned f) const { 
    
    if (graphic) graphic->draw(this, t, f); 
} 

// suspend suspends the object
//
void Box::suspend() const { 
	
	if (graphic) 
		const_cast<iGraphic*>(graphic)->suspend(); 
}

// release releases the object
//
void Box::release() const { 
	
	if (graphic) 
		const_cast<iGraphic*>(graphic)->release(); 
}

// destructor deletes the graphic model
//
Box::~Box() {

    if (graphic)
        graphic->Delete();
}



//-------------------------------- Player -------------------------------------
//
// Player is an Object identifiable by two points - lower close left, and
// upper faraway right - and a colour
//
iObject* CreatePlayer(float minx, float miny, float minz, float maxx, 
 float maxy, float maxz, Colour c) {

	return new Player(minx, miny, minz, maxx, maxy, maxz, c);
}

// constructor builds the Player from its two extreme points one face at a time
//
Player::Player(float minx, float miny, float minz, float maxx, float maxy,
 float maxz, Colour c) : Object(c) {

    graphic = CreateGraphic(TRIANGLE_LIST, 12);

    float x = (minx + maxx) / 2, y = (miny + maxy) / 2, z = (minz + maxz) / 2;
    minx -= x;
    miny -= y;
    minz -= z;
    maxx -= x;
    maxy -= y;
    maxz -= z;
    Vector p1 = Vector(minx, miny, minz),
           p2 = Vector(minx, maxy, minz),
           p3 = Vector(maxx, maxy, minz),
           p4 = Vector(maxx, miny, minz),
           p5 = Vector(minx, miny, maxz),
           p6 = Vector(minx, maxy, maxz),
           p7 = Vector(maxx, maxy, maxz),
           p8 = Vector(maxx, miny, maxz);
    graphic->add(p1, p2, p3, p4, Vector(0, 0, -1)); // front
    graphic->add(p4, p3, p7, p8, Vector(1, 0,  0)); // right
    graphic->add(p8, p7, p6, p5, Vector(0, 0,  1)); // back
    graphic->add(p6, p2, p1, p5, Vector(-1, 0, 0)); // left
    graphic->add(p1, p4, p8, p5, Vector(0, -1, 0)); // bottom
    graphic->add(p2, p6, p7, p3, Vector(0, 1,  0)); // top
    translate(x, y, z);
}

// copy constructor clones the graphic representation
//
Player::Player(const Player& src) : Object(src) {

    if (src.graphic)
        graphic = src.graphic->clone();
    else
        graphic = NULL;
}
            
// assignment operator discards old data and creates a copy from
// src - does not copy the Graphic attached to src but creates a 
// clone for the current object
//
Player& Player::operator=(const Player& src) {

    if (this != &src) {
        *((Object*)this) = src;
        if (graphic)
            graphic->Delete();
        if (src.graphic)
            graphic = src.graphic->clone();
        else
            graphic = NULL;
    }

    return *this;
}

// draw draws the graphic representation of the Player
//
void Player::draw(const iTexture* t, unsigned f) const { 
    
    if (graphic) graphic->draw(this, t, f); 
} 

// suspend suspends the object
//
void Player::suspend() const { 
	
	if (graphic) 
		const_cast<iGraphic*>(graphic)->suspend(); 
}

// release releases the object
//
void Player::release() const { 
	
	if (graphic) 
		const_cast<iGraphic*>(graphic)->release(); 
}

// destructor deletes the graphic model
//
Player::~Player() {

    if (graphic)
        graphic->Delete();
}



//-------------------------------------- Grid ------------------------------
//
// A Grid is a set of mutually perpendicular lines in a plane defined 
// parallel to the x-y plane
//
iObject* CreateGrid(int min, int y, int max, int n, Colour clr) {

	return new Grid(min, y, max, n, clr);
}

// constructor builds the Grid one line at a time
//
Grid::Grid(int min, int y, int max, int n, Colour clr) : Object(clr) {

    graphic = CreateGraphic(LINE_LIST, 2 * (n + 1));

    int i, inc = (max - min) / (n - 1);
    for (i = min; i <= max; i += inc) {
        graphic->add((float)min, (float)y, (float)i, 0, 1, 0);
        graphic->add((float)max, (float)y, (float)i, 0, 1, 0);
        graphic->add((float)i, (float)y, (float)min, 0, 1, 0);
        graphic->add((float)i, (float)y, (float)max, 0, 1, 0);
    }
}

// copy constructor clones the graphic representation
//
Grid::Grid(const Grid& src) : Object(src) {

    if (src.graphic)
        graphic = src.graphic->clone();
    else
        graphic = NULL;
}
            
// assignment operator discards old data and creates a copy from
// src - does not copy the Graphic attached to src but creates a 
// clone for the current object
//
Grid& Grid::operator=(const Grid& src) {

    if (this != &src) {
        *((Object*)this) = src;
        if (graphic)
            graphic->Delete();
        if (src.graphic)
            graphic = src.graphic->clone();
        else
            graphic = NULL;
    }

    return *this;
}

// draw draws the graphic representation
//
void Grid::draw(const iTexture* t, unsigned f) const { 
    
    if (graphic) graphic->draw(this, t, f); 
} 

// suspend suspends the graphic representation
//
void Grid::suspend() const { 
	
	if (graphic)
		const_cast<iGraphic*>(graphic)->suspend(); 
}

// release releases the graphic representation
//
void Grid::release() const { 
	
	if (graphic) 
		const_cast<iGraphic*>(graphic)->release(); 
}

// destructor deletes the graphic representation
//
Grid::~Grid() {

    if (graphic)
        graphic->Delete();
}

//GMOK:-------------------------------- Billboard -------------------------------------
//
//GMOK: A billboard is a simple 2D plane with only 1 face, identifiable by 2 points
//
iObject* CreateBillboard(float x, float y, float z, float xx, 
 float yy, Colour c) {

	return new Billboard(x, y, z, xx, yy, c);
}

//GMOK: constructor builds the Billboard from its two points
//
Billboard::Billboard(float x, float y, float z, float xx, float yy,
  Colour c) : Object(c) {

    graphic = CreateGraphic(TRIANGLE_LIST, 2);

    Vector p1 = Vector(x, y, z),
           p2 = Vector(x, yy, z),
           p3 = Vector(xx, yy, z),
           p4 = Vector(xx, y, z);

    graphic->add(p3, p4, p1, p2, Vector(0, 0, 0)); //GMOK: front

    translate(x, y, z);
}

//GMOK: copy constructor clones the graphic representation
//
Billboard::Billboard(const Billboard& src) : Object(src) {

    if (src.graphic)
        graphic = src.graphic->clone();
    else
        graphic = NULL;
}
            
//GMOK: assignment operator discards old data and creates a copy from
//GMOK: src - does not copy the Graphic attached to src but creates a 
//GMOK: clone for the current object
//
Billboard& Billboard::operator=(const Billboard& src) {

    if (this != &src) {
        *((Object*)this) = src;
        if (graphic)
            graphic->Delete();
        if (src.graphic)
            graphic = src.graphic->clone();
        else
            graphic = NULL;
    }

    return *this;
}

//GMOK: draw draws the graphic representation of the Billboard
//
void Billboard::draw(const iTexture* t, unsigned f) const { 
    
    if (graphic) graphic->draw(this, t, f); 
} 

//GMOK: suspend suspends the object
//
void Billboard::suspend() const { 
	
	if (graphic) 
		const_cast<iGraphic*>(graphic)->suspend(); 
}

//GMOK: release releases the object
//
void Billboard::release() const { 
	
	if (graphic) 
		const_cast<iGraphic*>(graphic)->release(); 
}

//GMOK: destructor deletes the graphic model
//
Billboard::~Billboard() {

    if (graphic)
        graphic->Delete();
}


// AKV-------------------------------------- Trap -------------------------------------------------------- 

// AKV - check if a collision has occurred for the boundry
bool Trap::checkCollision(int now, Vector blpt, Vector trpt)
{
	bool rc = false;

	// check if enough time has passed between the last collision
	if ( (now - this->lastCollision()) > TRAPS_COLLISION_LATENCY )
	{
		Vector trapMin, trapMax;
		Vector trapPos = this->position();
		float offsetX, offsetY , offsetZ;

		trapMin = this->getLowerDimension();
		trapMax = this->getUpperDimension();

		offsetX = (trapMax.x - trapMin.x) / 2.0f;
		offsetY = (trapMax.y - trapMin.y) / 2.0f;
		offsetZ = (trapMax.z - trapMin.z) / 2.0f;

		// get the box boundry of the trap based on its position and offset values
		trapMin = Vector(trapPos.x - offsetX, trapPos.y - offsetY, trapPos.z - offsetZ);
		trapMax = Vector(trapPos.x + offsetX, trapPos.y + offsetY, trapPos.z + offsetZ);

		rc = isCollision(blpt, trpt, trapMin, trapMax);	// check if the player is "within" the trap

		if (!rc)
			rc = isCollision(trapMin, trapMax, blpt, trpt);	// check if the trap is "within" the player
	}

	return rc;
}

// copy constructor initializes instance pointers and calls the assignment
// operator
//
Trap::Trap(const Trap& src) : Object(src) {    
	*this   = src;
}

// do nothing destructor
Trap::~Trap()
{
}

// assignment operator discards old data and creates a copy from
// src
//
Trap& Trap::operator=(const Trap& src) {

	if (this != &src) {
		*((Object*)this) = src;	// copy over the Object portion of the source

		// trap specific
		amtDamage = src.amtDamage;
		dim_blpt = src.dim_blpt;
		dim_trpt = src.dim_trpt;
		collision = src.collision;
	}

	return *this;
}


// AKV-------------------------------------- Trap related helper functions ------------------------------- 

// calculate the normal of three given points (in units)
Vector calculateNormal(Vector p1, Vector p2, Vector p3)
{
	Vector v1, v2;
	Vector n;

	v1 = p2 - p1;
	v2 = p3 - p1;
	n = cross(v1, v2);
	n = n / n.length();

	return n;
}

// AKV - check if the given point is within the min and max boundry
bool isWithinBoundry(Vector v, Vector min, Vector max)
{
	if ( isValueInRange(v.x, min.x, max.x) &&
		isValueInRange(v.y, min.y, max.y) &&
		isValueInRange(v.z, min.z, max.z) )
		return true;
	else
		return false;
}

// AKV - checks if a value is within the range
bool isValueInRange(float val, float min, float max)
{
	return (val >= min && val <= max);
}

// checks if the subset of a boundry specified by blpt and trpt are within a larger boundry (collision detection)
bool isCollision(Vector blpt, Vector trpt, Vector minBoundry, Vector maxBoundry)
{
	bool rc = false;

	Vector p1, p2, p3, p4, p5, p6, p7, p8;

	// get the vertices of the player's boundries

	// front face vertices
	p1 = blpt;
	p2 = p1;
	p2.y = trpt.y;
	p3 = p2;
	p3.x = trpt.x;
	p4 = p1;
	p4.x = trpt.x;

	// back face vertices
	p5 = p1;
	p5.z = trpt.z;
	p6 = p2;
	p6.z = trpt.z;
	p7 = p3;
	p7.z = trpt.z;
	p8 = p4;
	p8.z = trpt.z;

	if ( isWithinBoundry(p1, minBoundry, maxBoundry) ||
		isWithinBoundry(p2, minBoundry, maxBoundry) ||
		isWithinBoundry(p3, minBoundry, maxBoundry) ||
		isWithinBoundry(p4, minBoundry, maxBoundry) ||
		isWithinBoundry(p5, minBoundry, maxBoundry) ||
		isWithinBoundry(p6, minBoundry, maxBoundry) ||
		isWithinBoundry(p7, minBoundry, maxBoundry) ||
		isWithinBoundry(p8, minBoundry, maxBoundry)
		)
	{
		// collision has occurred
		rc = true;		
	}

	return rc;
}


// AKV - added implementation for Floor Spike

//-------------------------------- Floor Spike ----------------------------------------
//
/*
Floor Spike is an Object identifiable by:
- two points of the base - a lower left and faraway right of the rectange (both on same y level)
- height the spikes
- number of spikes
- a colour
*/
//
iObject* CreateFloorSpike(float minx, float y, float minz, 
	float maxx, float maxz, int numSpikes, float height, float damage, Colour c, bool includePadding) {

		return new FloorSpike(minx, y, minz, maxx, maxz, numSpikes, height, damage, c, includePadding);
}

// constructor builds the Rectangular Pyramid from its two extreme points of the base and height;
// one face at a time
//
FloorSpike::FloorSpike(float minx, float y, float minz, float maxx,
	float maxz, int n, float height, float damage, Colour c, bool includePadding) : Trap(minx, y, minz, maxx, y + height, maxz, damage, c)  {
		
		/*
		#triangles for Floor Spike are:
		- base box = 2 triangles per face for 6 faces = 2 * 6
		- n spikes, where each spike has 5 faces (2 faces are made of a triangle each, while the other 3 are made of 2 triangles each)
				 = n * (triangles of each spike) = n * ((2 * 1) + (3 * 2)) = n * (2 + 6) = 8n		
		Total# = base + spikes = 2 + 8n
		*/
		graphic = CreateGraphic(TRIANGLE_LIST, (2 * 6) + (8 * n));

		float x = (minx + maxx) / 2, z = (minz + maxz) / 2;

		minx -= x;	
		minz -= z;
		maxx -= x;
		maxz -= z;
		y -= y;

		
		const float cMinx = minx;
		const float cMaxx = maxx;

		// create the base box for the floor spikes using a minute ratio of the entire trap's differenc in height
		// using 10% of the spike's height since: maxy = y + height, miny = y, therefore maxy - miny = (y + height) - y = height
		float baseMaxy = y + (height) * 0.1f;
		addBox(graphic, minx, y, minz, maxx, baseMaxy, maxz);

		float pad;

		// ensure that the spikes are a little away from the left and right edges of the base with respect to x axis
		pad = (maxx - minx) * 0.01f;	// 1% of the width of the floor spike trap
		minx += pad;
		maxx -= pad;

		// ensure that the spikes are a little above the base but still within the height specified
		pad = height * 0.01f;	// 1% of the height
		y += pad;
		height -= pad;

		const float spacing = (maxx - minx) * 0.005f;	// spacing is half a percent of the width of the floor spike trap

		float w = (maxx - minx - n * spacing) / n;
		float altHeight = height * 0.55f;	// 55% of the height given

		Vector A, B, C;

		// add each spike side-by-side with alternating height and padding
		for (int i = 0; (i < n) && (minx >= cMinx && minx + w <= cMaxx); i++)
		{
			A = Vector(minx, y, minz);
			C = A;
			C.x = A.x + w;
			B = Vector(A.x + (C.x - A.x)/2.0f,
					   y + ((i %  2 == 0) ? altHeight : height),
					   minz);

			addSpike(graphic, A, B, C, maxz, Top);

			minx += w;

			// add padding between the base and the spikes, if needed
			if (includePadding)
				minx += spacing;
		}

		translate(x, y, z);
}

FloorSpike::FloorSpike(const FloorSpike& src) : Trap(src) {

	if (src.graphic)
		graphic = src.graphic->clone();
	else
		graphic = NULL;
}

// assignment operator discards old data and creates a copy from
// src - does not copy the Graphic attached to src but creates a 
// clone for the current object
//
FloorSpike& FloorSpike::operator=(const FloorSpike& src)  {

	if (this != &src) {
		*((Trap*)this) = src; // copy over Trap specific
		if (graphic)
			graphic->Delete();
		if (src.graphic)
			graphic = src.graphic->clone();
		else
			graphic = NULL;
	}

	return *this;
}

// draw draws the graphic representation of the Box
//
void FloorSpike::draw(const iTexture* t, unsigned f) const { 

	if (graphic) graphic->draw(this, t, f); 
} 

// suspend suspends the object
//
void FloorSpike::suspend() const { 

	if (graphic) 
		const_cast<iGraphic*>(graphic)->suspend(); 
}

// release releases the object
//
void FloorSpike::release() const { 

	if (graphic) 
		const_cast<iGraphic*>(graphic)->release(); 
}

// destructor deletes the graphic model
//
FloorSpike::~FloorSpike() {

	if (graphic)
		graphic->Delete();
}



// AKV - added implementation for Projectile

//-------------------------------- Projectile ----------------------------------------
//
/*
Projectile is an Object identifiable by:
- two points - lower close left, and upper faraway right
- amount of damage (if any) it deals upon collision
- a colour
*/
//
iObject* CreateProjectile(float minx, float miny, float minz, float maxx, float maxy,
	float maxz, float damage, Colour c, ProjectileType prjType) {

		return new Projectile(minx, miny, minz, maxx, maxy, maxz, damage, c, prjType);
}

// constructor builds the Projectile from its two extreme points of the "box" dimension
//
Projectile::Projectile(float minx, float miny, float minz, float maxx, float maxy,
	float maxz, float damage, Colour c, ProjectileType prjType) : Trap(minx, miny, minz, maxx, maxy, maxz, damage, c) {

		Vector A, B, C;
		int noTriangles, noTriBoxes, noTriSpikes;

		// initialize defaults
		dirInc = true;
		amtDamage = damage;
		rot = Vector(0, 0, 0);	// by default there is no rotation applied to the projectile for constant movement
		mv = Vector(0, 0, 0); // by default there is no translation applied to the projectile for constant movement

		// set the dimensions
		dim_blpt = Vector(minx, miny, minz);
		dim_trpt = Vector(maxx, maxy, maxz);

		/*
		 set's the upper and lower bounds of the boundry for constant movement to be its dimensions
		 (this is so that it will allow rotation to occur for constant movement)
		*/
		lowerBound = dim_blpt;
		upperBound = dim_trpt;

		// turn off constant movement (since boundry and translation vector not specified)
		mvOn = false;
		mvSpecified = false;

		switch (prjType)
		{
			case DOUBLE_EDGE_SPEAR:
				/*
				 #triangles for Double Edge Spear projectile are:		
				 - 1 box = 1 * (triangles of each box) = 1 * (6 * 2) = 12
				 - 2 spikes, where each spike has 5 faces (2 faces are made of a triangle each, while the other 3 are made of 2 triangles each)
				 = 2 * (triangles of each spike) = 2 * ((2 * 1) + (3 * 2)) = 2 * (2 + 6) = 16
				 Total# = boxes + spikes = 12 + 16
				*/

				noTriBoxes = 1 * (6 * 2);
				noTriSpikes = 2 * ((2 * 1) + (3 * 2));

				noTriangles = noTriBoxes + noTriSpikes;

				break;

			case CROSS:
				/*
				 #triangles for Cross projectile are:		
				 - 2 boxes = 2 * (triangles of each box) = 2 * (6 * 2) = 24
				 - 4 spikes, where each spike has 5 faces (2 faces are made of a triangle each, while the other 3 are made of 2 triangles each)
				 = 4 * (triangles of each spike) = 4 * ((2 * 1) + (3 * 2)) = 4 * (2 + 6) = 32
				 Total# = boxes + spikes = 24 + 32
				*/

				noTriBoxes = 2 * (6 * 2);
				noTriSpikes = 4 * ((2 * 1) + (3 * 2));

				noTriangles = noTriBoxes + noTriSpikes;

				break;

			case STAR:
				/*
				 #triangles for Star projectile are:		
				 - 4 boxes = 4 * (triangles of each box) = 4 * (6 * 2) = 48
				 - 8 spikes (with base), where each spike has 5 faces (2 faces are made of a triangle each, while the other 3 are made of 2 triangles each)
				 = 8 * (triangles of each spike with base) = 8 * ((2 * 1) + (3 * 2)) = 8 * (2 + 6) = 64
				 Total# = boxes + spikes = 48 + 64
				*/
				noTriangles = (4 * (6 * 2)) +
							  (8 * ((2 * 1) + (3 * 2)));

				break;

			case PIECE_WISE:
				/*
				 #triangles for Piece Wise projectile are:		
				 - 1 box = 1 * (triangles of each box) = 1 * (6 * 2) = 12
				 - 4 spikes, where each spike has 5 faces (2 faces are made of a triangle each, while the other 3 are made of 2 triangles each)
				 = 4 * (triangles of each spike) = 4 * ((2 * 1) + (3 * 2)) = 4 * (2 + 6) = 32
				 Total# = boxes + spikes = 12 + 32
				*/

				noTriBoxes = 1 * (6 * 2);
				noTriSpikes = 4 * ((2 * 1) + (3 * 2));

				noTriangles = noTriBoxes + noTriSpikes;

				break;

			case DIAGONAL_LTR:
			case DIAGONAL_RTL:
				/*
				 #triangles for Diagonal Left to Right (or Right to Left) projectile are:						 
				 - 2 spikes, where each spike has 5 faces (2 faces are made of a triangle each, while the other 3 are made of 2 triangles each)
				 = 2 * (triangles of each spike) = 2 * ((2 * 1) + (3 * 2)) = 2 * (2 + 6) = 16
				 Total# = spikes = 16
				*/
				
				noTriSpikes = 2 * ((2 * 1) + (3 * 2));

				noTriangles = noTriSpikes;
				break;
		}

		graphic = CreateGraphic(TRIANGLE_LIST, noTriangles);

		float x = (minx + maxx) / 2, y = (miny + maxy) / 2, z = (minz + maxz) / 2;

		minx -= x;
		miny -= y;
		minz -= z;
		maxx -= x;
		maxy -= y;
		maxz -= z;

		float diffx = (maxx - minx);
		float diffy = (maxx - minx);

		float spikeSize;
		const float SPIKE_PERCENTAGE = 0.2f;	// size of each spike is 20%
		const float CROSS_SPIKE_PERCENTAGE = 0.25f;	// size of each spike for a Double Edged Spear type is 25%
		unsigned flags;

		float paddingX;
		float paddingY;
		float paddingZ;

		if (prjType == DOUBLE_EDGE_SPEAR)
		{

			// vertical double edge spear (by default)
			spikeSize = diffy * CROSS_SPIKE_PERCENTAGE;
			addBox(graphic, minx, miny + spikeSize, minz, maxx, maxy - spikeSize, maxz);

			flags = Top;
			A = Vector(minx, maxy - spikeSize, minz);
			B = Vector(minx + (maxx-minx)/2.0f, maxy, minz);
			C = Vector(maxx, maxy - spikeSize, minz);
			addSpike(graphic, A, B, C, maxz, flags);	// top spike

			flags = Bottom;
			A = Vector(minx, miny + spikeSize, minz);
			B = Vector(maxx, miny + spikeSize, minz);
			C = Vector(minx + (maxx-minx)/2.0f, miny, minz);
			addSpike(graphic, A, B, C, maxz, flags);	// bottom spike
		}
		else if (prjType == CROSS || prjType == STAR || prjType == PIECE_WISE)
		{
			const float PADDING_PORTION_FACTOR = 2.6f;
			
			paddingX = (maxx - minx) / PADDING_PORTION_FACTOR;
			paddingY = (maxy - miny) / PADDING_PORTION_FACTOR;
			paddingZ = (prjType == STAR) ? (maxz - minz) / 3 : 0.f;

			minz += paddingZ;
			maxz -= paddingZ;

			// horizontal double edge spear
			spikeSize = diffx * SPIKE_PERCENTAGE;

			if (prjType != PIECE_WISE)
				addBox(graphic, minx + spikeSize, miny + paddingY, minz, maxx - spikeSize, maxy - paddingY, maxz);

			flags = Right;
			A = Vector(maxx - spikeSize, miny + paddingY, minz);
			B = A;
			B.y = maxy - paddingY;
			C = Vector(maxx, A.y + (B.y - A.y)/2.0f, minz);
			addSpike(graphic, A, B, C, maxz, flags);	// right spike
			
			Vector p1, p2, p3, p4;
			p1 = Vector(minx, miny + paddingY, minz);
			p2 = Vector(maxx, maxy - paddingY, minz);
			p3 = Vector(minx + spikeSize, maxy - paddingY, minz);
			p4 = Vector(minx + spikeSize, miny + paddingY, minz);

			flags = Left;
			A = Vector(minx, p1.y + (p2.y - p1.y)/2.0f, minz);
			B = p3;
			C = p4;
			addSpike(graphic, A, B, C, maxz, flags);	// left spike


			// vertical double edge spear
			spikeSize = diffy * SPIKE_PERCENTAGE;

			if (prjType != PIECE_WISE)
				addBox(graphic, minx + paddingX, miny + spikeSize, minz, maxx - paddingX, maxy - spikeSize, maxz);

			flags = Top;
			A = Vector(minx + paddingX, maxy - spikeSize, minz);
			C = Vector(maxx - paddingX, maxy - spikeSize, minz);
			B = Vector(A.x + (C.x-A.x)/2.0f, maxy, minz);
			addSpike(graphic, A, B, C, maxz, flags);	// top spike

			flags = Bottom;
			A = Vector(minx + paddingX, miny + spikeSize, minz);
			B = A;
			B.x = maxx - paddingX;
			C = Vector(A.x + (B.x - A.x)/2.0f, miny, minz);
			addSpike(graphic, A, B, C, maxz, flags);	// bottom spike
		}

		if (prjType == STAR)
		{
			float sx, sy;	// the spike sizes for the x and y axis for diagonal (padding in x and y axis from min and max of box)

			paddingX = (maxx - minx) * 0.10f;
			paddingY = (maxy - miny) * 0.10f;

			sx = diffx * (SPIKE_PERCENTAGE / 1.9f);
			sy = diffy * (SPIKE_PERCENTAGE / 1.9f);

			minx += paddingX;
			maxx -= paddingX;
			miny += paddingY;
			maxy -= paddingY;

			// left to right diagonal spear
			addDiagonalBox(minx, miny, minz + paddingZ, maxx, maxy, maxz - paddingZ, sx, sy, Left, true);

			// right to left diagonal spear
			addDiagonalBox(minx, miny, minz + paddingZ, maxx, maxy, maxz - paddingZ, sx, sy, Right, true);
		}
		else if (prjType == PIECE_WISE)
		{
			float midx, midy, midz;
			float scalingFactor = 10.f;
			midx = minx + (maxx - minx) / 2.0f;
			midy = miny + (maxy - miny) / 2.0f;
			midz = minz + (maxz - minz) / 2.0f;

			paddingX = (maxx - minx) / scalingFactor;
			paddingY = (maxy - miny) / scalingFactor;
			paddingZ = (maxz - minz) / scalingFactor;
			
			// add the centered box (scaled by a factor)
			addBox(graphic, midx - paddingX, midy - paddingY, minz, midx + paddingX, midy + paddingY, maxz);

		}
		else if (prjType == DIAGONAL_LTR)
		{
			float sx, sy;	// the spike sizes for the x and y axis for diagonal (padding in x and y axis from min and max of box)

			sx = diffx * SPIKE_PERCENTAGE;
			sy = diffy * SPIKE_PERCENTAGE;

			// left to right diagonal spear
			addDiagonalBox(minx, miny, minz, maxx, maxy, maxz, sx, sy, Left, false);
		}
		else if (prjType == DIAGONAL_RTL)
		{
			float sx, sy;	// the spike sizes for the x and y axis for diagonal (padding in x and y axis from min and max of box)

			sx = diffx * SPIKE_PERCENTAGE;
			sy = diffy * SPIKE_PERCENTAGE;

			// right to left diagonal spear
			addDiagonalBox(minx, miny, minz, maxx, maxy, maxz, sx, sy, Right, false);
		}

		translate(x, y, z);
}

void Projectile::addDiagonalBox(float minx, float miny, float minz, float maxx, float maxy, float maxz, float sx, float sy, DirectionFace dir, bool includePiller)

{
	Vector A;
	Vector B;
	Vector C;
	Vector D;
	Vector AZ, BZ, CZ, DZ;	// the ?Z notation represents that the vector is identical except that it is at maximum z value
	Vector n;

	unsigned flags = 0;
		
	/*
	 Note: the postion comments below only are correct if you visualize the diagonal 3D box by rotating it clockwise (counter-clockwise if direction Right) until it is
		   correctly positioned (i.e. not tilted with respect to the front)
	*/

	if (includePiller)
	{

		if (dir == Left)	// from top left to bottom right
		{
			A = Vector(minx, maxy - sy, minz);
			B = Vector(minx + sx, maxy, minz);
			C = Vector(maxx, miny + sy, minz);
			D = Vector(maxx - sx, miny, minz);
		}
		else if (dir == Right)	// from top right to bottom left
		{
			A = Vector(minx, miny + sy, minz);
			B = Vector(maxx - sx, maxy, minz);
			C = Vector(maxx, maxy - sy, minz);
			D = Vector(minx + sx, miny, minz);
		}

		AZ = A;
		AZ.z = maxz;
		BZ = B;
		BZ.z = maxz; 
		CZ = C;
		CZ.z = maxz;
		DZ = D;
		DZ.z = maxz;

		n = calculateNormal(A, B, D);
		graphic->add(A, B, C, D, n); // front

		n = calculateNormal(DZ, CZ, BZ);
		graphic->add(DZ, CZ, BZ, AZ, n); // back

		n = calculateNormal(B, BZ, CZ);
		graphic->add(B, BZ, CZ, C, n); // top

		n = calculateNormal(AZ, A, D);
		graphic->add(AZ, A, D, DZ, n); // bottom

		n = calculateNormal(A, AZ, BZ);
		graphic->add(A, AZ, BZ, B, n); // left

		n = calculateNormal(DZ, D, C);
		graphic->add(DZ, D, C, CZ, n); // right
	}

	// add the spikes for the diagonal
	if (dir == Left)
	{

		// top left
		A = Vector(minx, maxy - sy, minz);
		B = Vector(minx, maxy, minz);
		C = Vector(minx + sx, maxy, minz);

		flags = Top;
		flags |= Left;
		addSpike(graphic, A, B, C, maxz, flags);

		// bottom right
		A = Vector(maxx - sx, miny, minz);
		B = Vector(maxx, miny + sy, minz);
		C = Vector(maxx, miny, minz);

		flags = Bottom;
		flags |= Right;
		addSpike(graphic, A, B, C, maxz, flags);
	}
	else if (dir == Right)
	{
		
		// top right
		A = Vector(maxx - sx, maxy, minz);
		B = Vector(maxx, maxy, minz);
		C = Vector(maxx, maxy - sy, minz);

		flags = Top;
		flags |= Right;
		addSpike(graphic, A, B, C, maxz, flags);

		// bottom left
		A = Vector(minx, miny, minz);
		B = Vector(minx, miny + sy, minz);
		C = Vector(minx + sx, miny, minz);

		flags = Bottom;
		flags |= Left;
		addSpike(graphic, A, B, C, maxz, flags);
	}
	
}

void Trap::addSpike(iGraphic* graphic, Vector A, Vector B, Vector C, float maxz, unsigned flags)
{
	Vector AZ, BZ, CZ;
	Vector n;

	AZ = A;
	AZ.z = maxz;
	BZ = B;
	BZ.z = maxz; 
	CZ = C;
	CZ.z = maxz;
		
	// front face
	n = calculateNormal(A, B, C);
	graphic->add(A.x, A.y, A.z, n.x, n.y, n.z, 0, 0);
	graphic->add(B.x, B.y, B.z, n.x, n.y, n.z, 0, 1);
	graphic->add(C.x, C.y, C.z, n.x, n.y, n.z, 1, 1);

	// back face
	n = calculateNormal(CZ, BZ, AZ);	// reverse order
	graphic->add(CZ.x, CZ.y, CZ.z, n.x, n.y, n.z, 1, 1);
	graphic->add(BZ.x, BZ.y, BZ.z, n.x, n.y, n.z, 0, 1);
	graphic->add(AZ.x, AZ.y, AZ.z, n.x, n.y, n.z, 0, 0);

	if ((flags - Top - Left) == 0)
	{
		
		// left face
		n = calculateNormal(BZ, B, A);
		graphic->add(BZ, B, A, AZ, n);

		// right face
		n = calculateNormal(A, C, CZ);
		graphic->add(A, C, CZ, AZ, n);

		// top face
		n = calculateNormal(B, BZ, CZ);
		graphic->add(B, BZ, CZ, C, n);
	}
	else if ((flags - Bottom - Right) == 0)
	{

		// left face
		n = calculateNormal(B, A, AZ);
		graphic->add(B, A, AZ, BZ, n);

		// right face
		n = calculateNormal(C, B, BZ);
		graphic->add(C, B, BZ, CZ, n);

		// bottom face
		n = calculateNormal(AZ, A, C);
		graphic->add(AZ, A, C, CZ, n);
	}
	else if ( (flags - Top - Right) == 0 )
	{
		
		// left face
		n = calculateNormal(AZ, A, C);
		graphic->add(AZ, A, C, CZ, n);

		// right face
		n = calculateNormal(B, BZ, CZ);
		graphic->add(B, BZ, CZ, C, n);

		// top face
		n = calculateNormal(A, AZ, BZ);
		graphic->add(A, AZ, BZ, B, n);
	}
	else if ( (flags - Bottom - Left) == 0 )
	{

		// top face
		n = calculateNormal(B, BZ, CZ);
		graphic->add(B, BZ, CZ, C, n);

		// left face
		n = calculateNormal(B, A, AZ);
		graphic->add(B, A, AZ, BZ, n);

		// bottom face
		n = calculateNormal(AZ, A, C);
		graphic->add(AZ, A, C, CZ, n);
	}
	else if ( (flags - Top) == 0 )
	{

		// left face
		n = calculateNormal(B, A, AZ);
		graphic->add(B, A, AZ, BZ, n);

		// right face
		n = calculateNormal(B, BZ, CZ);
		graphic->add(B, BZ, CZ, C, n);

		// bottom face
		n = calculateNormal(AZ, A, C);
		graphic->add(AZ, A, C, CZ, n);
	}
	else if ( (flags - Bottom) == 0 )
	{

		// left face
		n = calculateNormal(AZ, A, C);
		graphic->add(AZ, A, C, CZ, n);

		// right face
		n = calculateNormal(C, B, BZ);
		graphic->add(C, B, BZ, CZ, n);

		// top face
		n = calculateNormal(A, AZ, BZ);
		graphic->add(A, AZ, BZ, B, n);
	}
	else if ( (flags - Right) == 0 )
	{

		// left face
		n = calculateNormal(B, A, AZ);
		graphic->add(B, A, AZ, BZ, n);

		// top face
		n = calculateNormal(B, BZ, CZ);
		graphic->add(B, BZ, CZ, C, n);

		// bottom face
		n = calculateNormal(A, C, CZ);
		graphic->add(A, C, CZ, AZ, n);
	}
	else if ( (flags - Left) == 0 )
	{

		// top face
		n = calculateNormal(AZ, BZ, B);
		graphic->add(AZ, BZ, B, A, n);		

		// bottom face
		n = calculateNormal(CZ, AZ, A);
		graphic->add(CZ, AZ, A, C, n);

		// right face
		n = calculateNormal(BZ, CZ, C);
		graphic->add(BZ, CZ, C, B, n);
	}
}

void Trap::addBox(iGraphic* graphic, float minx, float miny, float minz, float maxx, float maxy, float maxz)
{
	Vector p1 = Vector(minx, miny, minz),
		p2 = Vector(minx, maxy, minz),
		p3 = Vector(maxx, maxy, minz),
		p4 = Vector(maxx, miny, minz),
		p5 = Vector(minx, miny, maxz),
		p6 = Vector(minx, maxy, maxz),
		p7 = Vector(maxx, maxy, maxz),
		p8 = Vector(maxx, miny, maxz);

	graphic->add(p1, p2, p3, p4, Vector(0, 0, -1)); // front
	graphic->add(p8, p7, p6, p5, Vector(0, 0,  1)); // back

	graphic->add(p4, p3, p7, p8, Vector(1, 0,  0)); // right
	graphic->add(p6, p2, p1, p5, Vector(-1, 0, 0)); // left

	graphic->add(p1, p4, p8, p5, Vector(0, -1, 0)); // bottom
	graphic->add(p2, p6, p7, p3, Vector(0, 1,  0)); // top

}

void Projectile::stopMovement()
{
	mvOn = false;
}

void Projectile::startMovement()
{

	// only start the movement if the trap had movement data initialized
	if (mvSpecified)
		mvOn = true;
}

void Projectile::setRotation(Vector rv)
{
	// turn on movement
	mvSpecified = true;
	mvOn = true;
	rot = rv;	// set the rotation vector
}


void Projectile::setMovement(Vector minBoundry, Vector maxBoundry, Vector movement)
{
	bool isValid = false;	// if the trap movement boundry is valid (i.e. greater than or equal to trap dimensions)

	Vector lb = getLowerDimension(),
		   up = getUpperDimension();

	// check if the boundry specified is greater than or equal to the trap dimensions
	float trapDiffX = up.x - lb.x,
		trapDiffY = up.y - lb.y,
		trapDiffZ = up.z - lb.z;

	if ( (maxBoundry.x - minBoundry.x) >= trapDiffX &&
		(maxBoundry.y - minBoundry.y) >= trapDiffY &&
		(maxBoundry.z - minBoundry.z) >= trapDiffZ)
		isValid = true;	//invalid boundry specified

	if (isValid)
	{

		// set the boundries, and translation vector
		lowerBound = minBoundry;
		upperBound = maxBoundry;
		mv = movement;

		// reposition the object to the mid-point of the boundries

		// translate back to starting point
		Vector p = this->position();
		Matrix m(-1);

		// move back to origin (note since we multipled position by a negative identity matrix, means translation back to origin)
		p = p * m;
		this->translate(p.x, p.y, p.z);

		// move to new location (mid-point of the boundries)
		float x = (upperBound.x + lowerBound.x) / 2.0f,
			  y = (upperBound.y + lowerBound.y) / 2.0f,
			  z = (upperBound.z + lowerBound.z) / 2.0f;

		this->translate(x, y, z);

		// turn on constant movement
		mvSpecified = true;
		mvOn = true;
	}
	else
		error(L"Projectile::setMovement() failed due to invalid boundries. Try setting a boundry greater than or equal to the trap dimensions.");
}

void Projectile::move(int delta)
{

	if (mvOn)
	{
		float dx = mv.x * delta,
			  dy = mv.y * delta,
			  dz = mv.z * delta;

		Vector p = this->position();

		Matrix pMat(p.x, p.y, p.z, 1,
			        0, 0, 0, 0,
					0, 0, 0, 0,
					0, 0, 0, 0);

		Matrix postMovement;

		bool ignoreAxisX = (mv.x == 0.f);
		bool ignoreAxisY = (mv.y == 0.f);
		bool ignoreAxisZ = (mv.z == 0.f);

		Vector lb = getLowerDimension();
		Vector ub = getUpperDimension();

		float offsetX = (ub.x - lb.x) / 2.0f,
			offsetY = (ub.y - lb.y) / 2.0f,
			offsetZ = (ub.z - lb.z) / 2.0f;

		// determine the destination from the current position after translation
		postMovement = pMat.translate(mv.x * delta, mv.y * delta, mv.z * delta);

		// move the object only if it is within the boundry
		if ( (ignoreAxisX || (postMovement.m11 + offsetX <= upperBound.x && postMovement.m11 - offsetX >= lowerBound.x)) &&
			 (ignoreAxisY || (postMovement.m12 + offsetY <= upperBound.y && postMovement.m12 - offsetY >= lowerBound.y)) &&
			 (ignoreAxisZ || (postMovement.m13 + offsetZ <= upperBound.z && postMovement.m13 - offsetZ >= lowerBound.z))
		   )
		{

			// constant rotation
			this->rotatex(rot.x);
			this->rotatey(rot.y);
			this->rotatez(rot.z);

			// constant translation
			this->translate(dx, dy, dz);
		}
		else
		{

			// object has reached its boundry, so "reverse" its movement
			dirInc = !dirInc;

			// in opposite direction (must translate in the negative direction for all axis)
			mv *= -1;
		}
	}
}

// copy constructor clones the graphic representation
//
Projectile::Projectile(const Projectile& src) : Trap(src) {

	if (src.graphic)
		graphic = src.graphic->clone();
	else
		graphic = NULL;

	lowerBound = src.lowerBound;
	upperBound = src.upperBound;
	mvSpecified = src.mvSpecified;
	mvOn = src.mvOn;
	dirInc = src.dirInc;

}

// assignment operator discards old data and creates a copy from
// src - does not copy the Graphic attached to src but creates a 
// clone for the current object
//
Projectile& Projectile::operator=(const Projectile& src) {

	if (this != &src) {
		*((Trap*)this) = src;	// copy over the Trap specifics

		if (graphic)
			graphic->Delete();
		if (src.graphic)
			graphic = src.graphic->clone();
		else
			graphic = NULL;

	}

	return *this;
}

// draw draws the graphic representation of the Box
//
void Projectile::draw(const iTexture* t, unsigned f) const { 

	if (graphic) graphic->draw(this, t, f); 
} 

// suspend suspends the object
//
void Projectile::suspend() const { 

	if (graphic) 
		const_cast<iGraphic*>(graphic)->suspend(); 
}

// release releases the object
//
void Projectile::release() const { 

	if (graphic) 
		const_cast<iGraphic*>(graphic)->release(); 
}

// destructor deletes the graphic model
//
Projectile::~Projectile() {

	if (graphic)
		graphic->Delete();
}


// AKV - added a Atom object
//-------------------------------- Atom ----------------------------------------
//
/*
 Atom is an Object identifiable by:
	- two points of the base - a lower left and faraway right of the rectange (both on same y level)
	- amount of damage (if any) it deals upon collision
	- a colour for the origin box and a colour for the spikes
	- the type of projectile type for the embedded origin projectile
	- the percentage of the min and max points specified that the origin projectile should take
	 (with respect to the difference in x and y values from "origin" of the dimensions)
Note: this object is simply a container for two other Projectile objects (i.e. manages it as a single unit)
*/
//

iObject* CreateAtom(float minx, float miny, float minz, 
	 float maxx, float maxy, float maxz, float damage, Colour cBox, Colour cSpikes, ProjectileType embedPrjType, float boxPercentage) {

	return new Atom(minx, miny, minz, maxx, maxy, maxz, damage, cBox, cSpikes, embedPrjType, boxPercentage);
}

// constructor builds the other objects of the Atom from its two extreme points
//
Atom::Atom(float minx, float miny, float minz, 
	 float maxx, float maxy, float maxz, float damage, Colour cBox, Colour cSpikes, ProjectileType embedPrjType, float boxPercentage) : Trap(minx, miny, minz, maxx, maxy, maxz, damage, cBox) {

	// set the pointer to the graphic to be NULL (meaning it is not initialized nor used)
	graphic = NULL;

	// initialize default rotation (none by default)
	rotBox = rotSpike = Vector(0, 0, 0);

	float spikesMaxZ = minz + (maxz - minz) * 0.15f;	// the spikes will only have a fraction of the z-axis range

	// create the objects on dynamic memory
	diagonalLTR = (Projectile*) CreateProjectile(minx, miny, minz, maxx, maxy, spikesMaxZ, damage, cSpikes, DIAGONAL_LTR);
	diagonalRTL = (Projectile*) CreateProjectile(minx, miny, minz, maxx, maxy, spikesMaxZ, damage, cSpikes, DIAGONAL_RTL);

	float paddingX, paddingY, paddingZ;
	float scalingFactor = (boxPercentage <= 0.f || boxPercentage > 1.f) ? (0.1f) : boxPercentage;

	float midx, midy, midz;	// the "origin" of the dimensions specified
	
	midx = minx + (maxx - minx) / 2.0f;
	midy = miny + (maxy - miny) / 2.0f;
	midz = minz + (maxz - minz) / 2.0f;

	paddingX = (maxx - minx) * scalingFactor;
	paddingY = (maxy - miny) * scalingFactor;
	paddingZ = (maxz - minz) * 0.55f;	// depth is constant at only 55%

	// create the centered projectile (scaled by a factor)
	originPrj = (Projectile*) CreateProjectile(midx - paddingX, midy - paddingY, minz, midx + paddingX, midy + paddingY, minx + paddingZ,
												 damage, cBox, embedPrjType);
}

void Atom::attach(const iTexture* t, unsigned filter)
{
	if (t)
	{
		attachBoxTexture(t, filter);
		attachSpikeTexture(t, filter);
	}
}

void Atom::attachBoxTexture(const iTexture* t, unsigned filter)
{
	if (t && originPrj)
		originPrj->attach(t, filter);
}

void Atom::attachSpikeTexture(const iTexture* t, unsigned filter)
{
	if (t)
	{
		if (diagonalLTR)
			diagonalLTR->attach(t, filter);

		if (diagonalRTL)
			diagonalRTL->attach(t, filter);
	}
}

void Atom::setBoxRotation(Vector rot)
{
	rotBox = rot;
}

void Atom::setSpikeRotation(Vector rot)
{
	rotSpike = rot;
}

void Atom::move(int delta)
{
	// the origin projectile is rotated constantly by the rotation specified for the box
	if (originPrj)
	{
		originPrj->rotatex(rotBox.x);
		originPrj->rotatey(rotBox.y);
		originPrj->rotatez(rotBox.z);
	}

	// rotate the diagonal left-to-right projectile by the negative rotation specified for the spike
	if (diagonalLTR)
	{
		diagonalLTR->rotatex(-rotSpike.x);
		diagonalLTR->rotatey(-rotSpike.y);
		diagonalLTR->rotatez(-rotSpike.z);
	}

	// rotate the diagonal right-to-left projectile by the rotation specified for the spike
	if (DIAGONAL_RTL)
	{
		diagonalRTL->rotatex(rotSpike.x);
		diagonalRTL->rotatey(rotSpike.y);
		diagonalRTL->rotatez(rotSpike.z);
	}
}

void Atom::rotatex(float rad)
{
	if (diagonalLTR)
		diagonalLTR->rotatex(rad);

	if (diagonalRTL)
		diagonalRTL->rotatex(rad);

	if (originPrj)
		originPrj->rotatex(rad);
}

void Atom::rotatey(float rad)
{
	if (diagonalLTR)
		diagonalLTR->rotatey(rad);

	if (diagonalRTL)
		diagonalRTL->rotatey(rad);

	if (originPrj)
		originPrj->rotatey(rad);
}

void Atom::rotatez(float rad)
{
	if (diagonalLTR)
		diagonalLTR->rotatez(rad);

	if (diagonalRTL)
		diagonalRTL->rotatez(rad);

	if (originPrj)
		originPrj->rotatez(rad);
}

void Atom::translate(float x, float y, float z)
{
	if (diagonalLTR)
		diagonalLTR->translate(x, y, z);

	if (diagonalRTL)
		diagonalRTL->translate(x, y, z);

	if (originPrj)
		originPrj->translate(x, y, z);
}

Vector Atom::position() const
{
	Vector p = Vector(0, 0, 0);

	if (originPrj)
		p = originPrj->position();

	return p;
}


// copy constructor deletes the current objects it manages and clones the new objects
//
Atom::Atom(const Atom& src) : Trap(src) {

	// delete the previous objects being managed and clone the new objects
	if (diagonalLTR)
		diagonalLTR->Delete();

	if (src.diagonalLTR)
		diagonalLTR = (Projectile*) src.diagonalLTR->clone();
	else
		diagonalLTR = NULL;

	if (diagonalRTL)
		diagonalRTL->Delete();

	if (src.diagonalRTL)
		diagonalRTL = (Projectile*) src.diagonalRTL->clone();
	else
		diagonalRTL = NULL;

	if (originPrj)
		originPrj->Delete();

	if (src.originPrj)
		originPrj = (Projectile*) src.originPrj->clone();
	else
		originPrj = NULL;
}
            
// assignment operator discards old data and creates a copy from
// src - does not copy the object attached to src but creates a 
// clone for the current object
//
Atom& Atom::operator=(const Atom& src) {

    if (this != &src) {
        *((Trap*)this) = src; // copy over the Trap specifics
		
		// graphic representation
		if (graphic)
            graphic->Delete();
        if (src.graphic)
            graphic = src.graphic->clone();
        else
            graphic = NULL;

		// delete the previous objects being managed and clone the new objects
		if (diagonalLTR)
			diagonalLTR->Delete();

		if (src.diagonalLTR)
			diagonalLTR = (Projectile*) src.diagonalLTR->clone();
		else
			diagonalLTR = NULL;

		if (diagonalRTL)
			diagonalRTL->Delete();

		if (src.diagonalRTL)
			diagonalRTL = (Projectile*) src.diagonalRTL->clone();
		else
			diagonalRTL = NULL;

		if (originPrj)
			originPrj->Delete();

		if (src.originPrj)
			originPrj = (Projectile*) src.originPrj->clone();
		else
			originPrj = NULL;
    }

    return *this;
}

// draw draws the graphic representation of the Atom by calling the draw method on the objects it manages in addition to its graphic representation
//
void Atom::draw(const iTexture* t, unsigned f) const { 
    if (graphic)
		graphic->draw(this, t, f); 
	
	if (diagonalLTR)
		diagonalLTR->draw(t, f);

	if (diagonalRTL)
		diagonalRTL->draw(t, f);

	if (originPrj)
		originPrj->draw(t, f);
} 

// suspend suspends the object (i.e. its graphic model) and also on the objects it manages
//
void Atom::suspend() const {
	if (graphic) 
		const_cast<iGraphic*>(graphic)->suspend(); 

	if (diagonalLTR)
		diagonalLTR->suspend();

	if (diagonalRTL)
		diagonalRTL->suspend();

	if (originPrj)
		originPrj->suspend();
}

// release releases the object (i.e. its graphic model) and also on the objects it manages
//
void Atom::release() const { 
	if (graphic) 
		const_cast<iGraphic*>(graphic)->release(); 

	if (diagonalLTR)
		diagonalLTR->release();

	if (diagonalRTL)
		diagonalRTL->release();

	if (originPrj)
		originPrj->release();
}

// destructor deletes its own graphic model, then the graphic model of the objects it manages by calling the delete method on each
//
Atom::~Atom() {
	 if (graphic)
		 graphic->Delete();

	 if (diagonalLTR)
		 diagonalLTR->Delete();

	 if (diagonalRTL)
		 diagonalRTL->Delete();

	 if (originPrj)
		 originPrj->Delete();
}


//-------------------------------- Utilities -----------------------------
//
// orient? returns a text string with the orientation of the local ? axis
// of iObject* object
//
const wchar_t* orientX(wchar_t* str, const iObject* object) {

	if (object) {
        Vector v = object->orientation('x');
		sprintf(str, (int)(100*v.x), (int)(100*v.y), (int)(100*v.z));
	}

	return str;
}

const wchar_t* orientY(wchar_t* str, const iObject* object) {

	if (object) {
		Vector v = object->orientation('y');
		sprintf(str, (int)(100*v.x), (int)(100*v.y), (int)(100*v.z));
	}

	return str;
}

const wchar_t* orientZ(wchar_t* str, const iObject* object) {

	if (object) {
		Vector v = object->orientation('z');
		sprintf(str, (int)(100*v.x), (int)(100*v.y), (int)(100*v.z));
	}

	return str;
}


// AKV - (used for testing) added function to display the position, and min & max boundry of the player
const wchar_t* playerBoundryDetails(wchar_t* str, const iObject* object) {

	if (object) {
		Vector v = object->position();
		Player* pl = (Player*) object;

		// position
		strcpy(str, L"P(", MAX_DESC - 1);
		sprintfAKV(str, (int)(v.x), L" ");
		sprintfAKV(str, (int)(v.y), L" ");

		if (pl)
		{
			sprintfAKV(str, (int)(v.z), L"), LB(");

			// min boundry
			sprintfAKV(str, (int)(v.x - PLAYER_DIM_SIZE_X / 2.0f), L" ");
			sprintfAKV(str, (int)(v.y - PLAYER_DIM_SIZE_Y / 2.0f), L" ");
			sprintfAKV(str, (int)(v.z - PLAYER_DIM_SIZE_Z / 2.0f), L"), UB(");

			// max boundry
			sprintfAKV(str, (int)(v.x + PLAYER_DIM_SIZE_X / 2.0f), L" ");
			sprintfAKV(str, (int)(v.y + PLAYER_DIM_SIZE_Y / 2.0f), L" ");
			sprintfAKV(str, (int)(v.z + PLAYER_DIM_SIZE_Z / 2.0f), L")");
		}
		else
			sprintfAKV(str, (int)(v.z), L")");		
	}

	return str;
}