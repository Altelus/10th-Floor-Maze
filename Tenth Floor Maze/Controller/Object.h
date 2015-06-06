#ifndef _OBJECT_H_
#define _OBJECT_H_

/* Object Declarations - Scene Component - Model Branch
 *
 * consists of Object base class
 *             Box class
 *             Grid class
 *
 * Object.h
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iObject.h"       // for the Object Interface
#include "ModelSettings.h" // for MAX_RPTS

//-------------------------------- Object -------------------------------------
//
// The Object Primitive is an independent object in the Scene Component
//
class iScene;
enum  PrimitiveType;

class Object : public iObject {

	static iScene*  coordinator;    // points to the scene coordinator

	const iTexture* texture;        // points to the attached texture, if any
	const iSound*   sound;          // points to the attached sound, if any
    const iLight*   light;          // points to the attached light, if any
    const iCamera*  camera;         // points to the attached camera, if any
	Colour          material;       // material reflectivity
	unsigned        flags;          // texture sampling flags

	int             noTexts;        // number of reporting text strings
	const iText*    text[MAX_RPTS]; // points to the reporting text strings
	const wchar_t*  (*data[MAX_RPTS])(wchar_t* s, const iObject*);  
							        // points to the reporting functions

    void release();

  protected:
    Object(Colour c);
    virtual ~Object();

  public:
	static void isCoordinatedBy(iScene* scene) { coordinator = scene; }
    Object(const Object& o);            
    Object& operator=(const Object& o); 
    iObject* clone() const { return NULL; }
	// initialization functions
	void   attach(const iTexture* t, unsigned filter);
	void   attach(const iSound*);
	void   attach(const iLight*);
	void   attach(const iCamera*);
	void   attach(const iText* t, const wchar_t* (*d)(wchar_t* s, const iObject*));
	// execution functions
    virtual void draw(const iTexture*, unsigned) const = 0;
	Colour colour() const { return material; }
	void   draw(bool opacity) const;
	void   report() const;
	// termination functions 
	void   Delete() const { delete this; }
};

//-------------------------------- Board ----------------------------------------
//
// Board is an Object identifiable by two points - lower close left, and
// upper faraway right - plus a colour
//
//class iGraphic;
//class Board : public Object {
//    iGraphic* graphic; // points to the graphic representation
//  protected:
//    Board(float minx, float minz, float maxx, float maxz, float y, Colour c);
//
//  public:
//	friend iObject* CreateBoard(float minx, float minz, float maxx, float maxz, float y, Colour c);
//    Board(const Board& o);            
//    Board& operator=(const Board& o); 
//    iObject* clone() const { return new Board(*this); }
//    void     draw(const iTexture* t, unsigned f) const; 
//	void     suspend() const;
//    void     release() const;
//	virtual  ~Board();
//};

//-------------------------------- Player ----------------------------------------
//
// Player is an Object identifiable by two points - lower close left, and
// upper faraway right - plus a colour
//
class iGraphic;

class Player : public Object {

    iGraphic* graphic; // points to the graphic representation

	// AKV - added health related data to player object
	float currentHealth;	// current health of the player
	float maxHealth;	// the maximum (starting health) of the player

  protected:
    Player(float minx, float miny, float minz, float maxx, float maxy,
     float maxz, Colour c);

  public:
	friend iObject* CreatePlayer(float minx, float miny, float minz, 
	 float maxx, float maxy, float maxz, Colour c);
    Player(const Player& o);            
    Player& operator=(const Player& o); 
    iObject* clone() const { return new Player(*this); }
    void     draw(const iTexture* t, unsigned f) const; 
	void     suspend() const;
    void     release() const;
	virtual  ~Player();

	// AKV
	float health() const { return currentHealth; }
	float totalHealth() const { return maxHealth; }

	// AKV - setter methods for health
	void setHealth(float hlth) { currentHealth = hlth; }
	void setTotalHealth(float maxHlth) { maxHealth = maxHlth; }
};

//-------------------------------- Box ----------------------------------------
//
// Box is an Object identifiable by two points - lower close left, and
// upper faraway right - plus a colour
//
class iGraphic;

class Box : public Object {

    iGraphic* graphic; // points to the graphic representation

  protected:
    Box(float minx, float miny, float minz, float maxx, float maxy,
     float maxz, Colour c);

  public:
	friend iObject* CreateBox(float minx, float miny, float minz, 
	 float maxx, float maxy, float maxz, Colour c);
    Box(const Box& o);            
    Box& operator=(const Box& o); 
    iObject* clone() const { return new Box(*this); }
    void     draw(const iTexture* t, unsigned f) const; 
	void     suspend() const;
    void     release() const;
	virtual  ~Box();
};

//-------------------------------- Grid ---------------------------------------
//
// Grid is a set of mutually perpendicular lines in a plane parallel to the x-y
// plane
//
class Grid : public Object {

    iGraphic* graphic; // points to the graphic representation

  protected:
    Grid(int min, int y, int max, int n, Colour clr);
	virtual ~Grid();

  public:
	friend iObject* CreateGrid(int min, int y, int max, int n, Colour clr);
    Grid(const Grid& o);            
    Grid& operator=(const Grid& o); 
    iObject* clone() const { return new Grid(*this); }
    void  draw(const iTexture* t, unsigned f) const; 
	void  suspend() const;
    void  release() const;
};

//GMOK:-------------------------------- Billboard -------------------------------------
//
//GMOK: A billboard is a simple 2D plane with only 1 face, identifiable by 2 points
//
class Billboard : public Object {

    iGraphic* graphic; // points to the graphic representation

  protected:
    Billboard(float x, float y, float z, float xx, float yy,
      Colour c);

  public:
	friend iObject* CreateBillboard(float x, float y, float z, 
	 float xx, float yy, Colour c);
    Billboard(const Billboard& o);            
    Billboard& operator=(const Billboard& o); 
    iObject* clone() const { return new Billboard(*this); }
    void     draw(const iTexture* t, unsigned f) const; 
	void     suspend() const;
    void     release() const;
	virtual  ~Billboard();
};


// AKV - trap parent object used to handle all types of traps
//-------------------------------- Trap ----------------------------------------
//
/*
 Trap is an Object identifiable by at least:
	- dimensions of the emcompassing trap (box)
	- amount of damage (if any) it deals upon collision	
	- colour
*/
//

enum DirectionFace
{
	Left = 1, Right = 2, Top = 4, Bottom = 8
};

class Trap : public Object
{
	protected:
		float amtDamage;	/*
							 the amount of damage dealt to a player if collided
							 (if < 0 then destructive damage, > 0 bonus, = 0 no change
							*/
		Vector dim_blpt;	// the vector to the left, close point of the trap (minimum)
		Vector dim_trpt;	// the vector to the top, far away point of the trap (maximum)
		int collision;	// when the last collision occurred

		void addSpike(iGraphic* graphic, Vector A, Vector B, Vector C, float maxz, unsigned flags);	// helper function to add spikes

		// helper function that adds vertices for a box
		void addBox(iGraphic* graphic, float minx, float miny, float minz, float maxx, float maxy, float maxz);

	public:
		Trap(float minx, float miny, float minz, float maxx, float maxy, float maxz, float damage, Colour c) : Object(c)
		{
			amtDamage = damage;
			dim_blpt = Vector(minx, miny, minz);
			dim_trpt = Vector(maxx, maxy, maxz);
			collision = 0;
		}

		Trap(const Trap& o);            
		Trap& operator=(const Trap& o); 
		~Trap();
		float damage() const { return amtDamage; }	// gets the amount of damage the trap deals upon collision
		int lastCollision() const { return collision; }	// gets the time when the last collision occurred
		void setCollision(int now) { collision = now; }	// sets the time for latest collision
		
		// get the specified position of the trap's dimensions
		Vector getLowerDimension() const { return dim_blpt; };
		Vector getUpperDimension() const { return dim_trpt; };

		// determines and performs actions if the dimensions provided as parameters are within the trap (collision)
		virtual bool checkCollision(int now, Vector blpt, Vector trpt);

		// trap is "static" by default (unless constant motion logic is performed)
		virtual void move(int delta) { };
};


// AKV-------------------------------------- Trap related helper functions ------------------------------- 

// calculates the normal for the given three points
Vector calculateNormal(Vector p1, Vector p2, Vector p3);

// checks if the subset of a boundry specified by blpt and trpt are within a larger boundry (collision detection)
bool isCollision(Vector blpt, Vector trpt, Vector minBoundry, Vector maxBoundry);
bool isWithinBoundry(Vector v, Vector min, Vector max);	// check if the given point is within the min and max boundry
bool isValueInRange(float val, float min, float max);	// checks if a value is within the range
// AKV---------------------------------------------------------------------------------------------------- 


// AKV - added a Floor Spike object
//-------------------------------- Floor Spike ----------------------------------------
//
/*
 Floor Spike is an Object identifiable by:
	- two points of the base - a lower left and faraway right of the rectange (both on same y level)
	- height the spikes
	- number of spikes
	- amount of damage (if any) it deals upon collision
	- a colour
*/
//
class FloorSpike : public Trap {

   iGraphic* graphic; // points to the graphic representation

  protected:

  public:
	friend iObject* CreateFloorSpike(float minx, float y, float minz, 
	 float maxx, float maxz, int numSpikes, float height, float damage, Colour c, bool includePadding);
	FloorSpike(float minx, float y, float minz, float maxx,
     float maxz, int n, float height, float damage, Colour c, bool includePadding = true);

    FloorSpike(const FloorSpike& o);            
    FloorSpike& operator=(const FloorSpike& o); 
    iObject* clone() const { return new FloorSpike(*this); }
    void draw(const iTexture* t, unsigned f) const;
	void     suspend() const;
    void     release() const;
	void setDimensions(Vector blpt, Vector trpt) { dim_blpt = blpt; dim_trpt = trpt; }
	virtual  ~FloorSpike();
};


// AKV - added a Projectile object
//-------------------------------- Projectile ----------------------------------------
//
/*
 Projectile is an Object identifiable by:
	- two points - lower close left, and upper faraway right
	- amount of damage (if any) it deals upon collision
	- a colour
*/
//
class Projectile : public Trap {

    iGraphic* graphic; // points to the graphic representation
		
	Vector mv;	// the vector used to handle constant movement within boundry (translation vector)
	Vector rot;	// the vector used to handle constant rotation (rotation vector of projectile)
	Vector lowerBound;	// the lower close left point of the box boundry for the projectile (constant movement)
	Vector upperBound;	// the upper faraway right point of the box boundry for the projectile (constant movement)

	bool mvSpecified;	/*
						 whether the movement data has been initialized
						 [whether setBoundry() method was called atleast once]
						*/
	bool mvOn;	// whether constant movement is currently turned on or off

	bool dirInc;	// whether the object is moving in positive or negative direction

  protected:
	  Projectile(float minx, float miny, float minz, float maxx, float maxy,
				 float maxz, float damage, Colour c, ProjectileType prjType);
	
	// adds vertices for a diagonal box with padding in x and y direction from min and max values of box (specified by sx and sy)
	void addDiagonalBox(float minx, float miny, float minz, float maxx, float maxy, float maxz, float sx, float sy, DirectionFace dir, bool includePiller);	

	void populateStar(float minx, float miny, float minz, float maxx, float maxy, float maxz);
  public:
	friend iObject* CreateProjectile(float minx, float miny, float minz, float maxx, float maxy,
				 float maxz, float amtDamage, Colour c, ProjectileType prjType);
    Projectile(const Projectile& o);            
    Projectile& operator=(const Projectile& o); 
    iObject* clone() const { return new Projectile(*this); }
    void draw(const iTexture* t, unsigned f) const;

	void move(int delta);
	void setMovement(Vector minBoundry, Vector maxBoundry, Vector movement);	
	void setRotation(Vector rv);
	void stopMovement();
	void startMovement();

	void     suspend() const;
    void     release() const;
	virtual  ~Projectile();
};


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
class Atom : public Trap {

	iGraphic* graphic;	// since this class is simply a container its pointer to a graphic representation will not be used (i.e. will only be set to NULL)

	Vector rotBox;	// the vector used to handle constant rotation of the box
	Vector rotSpike;	// the vector used to handle constant rotation of the diagonal spike projectiles
   
	// pointers to the objects it manages
	Projectile* diagonalLTR;	// top left to bottom right diagonal that has a spike at each end
	Projectile* diagonalRTL;	// top right to bottom left diagonal that has a spike at each end
	Projectile* originPrj;	// the centered projectile (scaled down by a ratio from outer dimensions)
	
  protected:

  public:
	friend iObject* CreateAtom(float minx, float miny, float minz, 
	 float maxx, float maxy, float maxz, float damage, Colour cBox, Colour cSpikes, ProjectileType embedPrjType, float boxPercentage);

	Atom(float minx, float miny, float minz, 
	 float maxx, float maxy, float maxz, float damage, Colour cBox, Colour cSpikes, ProjectileType embedPrjType,  float boxPercentage);

    Atom(const Atom& o);            
    Atom& operator=(const Atom& o); 
    iObject* clone() const { return new Atom(*this); }
    void draw(const iTexture* t, unsigned f) const;
	void     suspend() const;
    void     release() const;
	virtual  ~Atom();

	void setBoxRotation(Vector rot);
	void setSpikeRotation(Vector rot);

	void move(int delta);	// constant movement of this object is only rotation (since this is not a projectile)

	// attaching texture to the object
	void attach(const iTexture* t, unsigned filter = 0);
	void attachBoxTexture(const iTexture* t, unsigned filter = 0);
	void attachSpikeTexture(const iTexture* t, unsigned filter = 0);

	// all rotations and the translation are now being handled by this class (since the rotation or translation must also be applied to all managed objects)
	void rotatex(float rad);
    void rotatey(float rad);
    void rotatez(float rad);
	void translate(float x, float y, float z);

	// position returns the position of the origin box
    Vector position() const;
};
#endif
