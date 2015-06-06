/* DeviceTexture Implementation - GraphicsCard Component - Direct Device Branch
 *
 * DeviceTexture.cpp
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iTexture.h"         // for the Texture Interface
#include "iDisplay.h"         // for the Display Interface
#include "iUtilities.h"       // for error()

#include "DeviceTexture.h"    // for the DeviceTexture class declaration
#include "MathDeclarations.h" // for Matrix, Vector and Colour
#include "Configuration.h"    // for TEX_? and SPRITE_? 

//-------------------------------- DeviceTexture ------------------------------
//
// The DeviceTexture Primitive represents a texture in the Graphics Card
// Component
//
// The Display object provides the API connectivity for the device texture objects
//
iDisplay* DeviceTexture::display = NULL;

iDeviceTexture* CreateDeviceTexture() {

	return new DeviceTexture();
}

// constructor initializes the texture identifier
//
DeviceTexture::DeviceTexture() {

    tex = NULL;
}

DeviceTexture::DeviceTexture(const DeviceTexture& src) {

    tex   = NULL;
    *this = src;    
}

DeviceTexture& DeviceTexture::operator=(const DeviceTexture& src) {

    if (this != &src) {
        suspend();
        tex = NULL;
    }

    return *this;
}

// setup creates the device texture from the texture file
//
void DeviceTexture::setup(const iTexture* texture, int width, int height, 
 int key) {

    // create a texture COM object from the texture file
    //
	if (texture->filename() && FAILED(D3DXCreateTextureFromFileEx(
	 ((LPDIRECT3DDEVICE9)display->device()), texture->filename(), width, height, 
     D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, 
     D3DX_DEFAULT, key, NULL, NULL, &tex))) {
		error(L"DeviceTexture::11 Failed to load texture from file");
		tex = NULL;
	}

}

// attach attaches the device texture to sampling stage i
//
void DeviceTexture::attach(const iTexture* texture, int i, unsigned flags)
{

	if (!tex) setup(texture, 0, 0, 0);

    if (tex) {
        ((LPDIRECT3DDEVICE9)display->device())->SetTexture(i, tex);
		setSamplerState(i, flags);
    }

}

// setSamplerState sets the sampling state for the texture according 
// to the filtering flags
//
void DeviceTexture::setSamplerState(int i, unsigned flags) const {

    if (flags & TEX_MIN_POINT)
        ((LPDIRECT3DDEVICE9)display->device())->SetSamplerState(i, D3DSAMP_MINFILTER, 
	     D3DTEXF_POINT);
    else if (flags & TEX_MIN_LINEAR)
        ((LPDIRECT3DDEVICE9)display->device())->SetSamplerState(i, D3DSAMP_MINFILTER, 
		 D3DTEXF_LINEAR);
    else if (flags & TEX_MIN_ANISOTROPIC)
        ((LPDIRECT3DDEVICE9)display->device())->SetSamplerState(i, D3DSAMP_MINFILTER, 
		 D3DTEXF_ANISOTROPIC); 
    if (flags & TEX_MAG_POINT)
        ((LPDIRECT3DDEVICE9)display->device())->SetSamplerState(i, D3DSAMP_MAGFILTER, 
		 D3DTEXF_POINT);
    else if (flags & TEX_MAG_LINEAR)
        ((LPDIRECT3DDEVICE9)display->device())->SetSamplerState(i, D3DSAMP_MAGFILTER, 
		 D3DTEXF_LINEAR);
    else if (flags & TEX_MAG_ANISOTROPIC)
        ((LPDIRECT3DDEVICE9)display->device())->SetSamplerState(i, D3DSAMP_MAGFILTER, 
		 D3DTEXF_ANISOTROPIC);
}

// draw draws the device texture directly
//
void DeviceTexture::draw(const iTexture* texture, float x, float y, 
 float w, float h, unsigned char alpha) {

	if (!tex) setup(texture, (int)(display->width() * w), 
	 (int)(display->height() * h), 0xFF000000);

	if (tex) {
		Vector topLeft(display->width() * x, 
		 display->height() * y, 0);
		((LPD3DXSPRITE)display->spriteManager())->Draw(tex, NULL, NULL, 
		 (D3DXVECTOR3*)&topLeft, 
		 D3DCOLOR_RGBA(SPRITE_R, SPRITE_G, SPRITE_B, alpha));
	}
}

//GMOK: Draws a texture scaled by x value
//GMOK: percent scales the x value
void DeviceTexture::draw(const iTexture* texture, float x, float y, 
 float w, float h, unsigned char alpha, float percent) {

	
	if (!tex) setup(texture, (int)(display->width() * w), 
	 (int)(display->height() * h), 0xFF000000);

	if (tex) {
		Vector topLeft(display->width() * x, 
		 display->height() * y, 0);

		//GMOK: set percent to scale by
		float xScale = 1.0f*percent;

		D3DXMATRIX mat;

		//GMOK: set scaling vector
		D3DXVECTOR2 scaling(xScale,1.0f);

		//GMOK: set scaling matrix
		D3DXMatrixTransformation2D(&mat,NULL,NULL,&scaling,NULL,NULL,NULL);

		//GMOK: scale the texture with the created matrix
		((LPD3DXSPRITE)display->spriteManager())->SetTransform(&mat);

		//GMOK: correct for x translation resulting from scaling
		topLeft.x /= xScale;

		((LPD3DXSPRITE)display->spriteManager())->Draw(tex, NULL, NULL, 
		 (D3DXVECTOR3*)&topLeft, 
		 D3DCOLOR_RGBA(SPRITE_R, SPRITE_G, SPRITE_B, alpha));

		//GMOK: reset to identity matrix for future
		D3DXMatrixTransformation2D(&mat,NULL,NULL,NULL,NULL,NULL,NULL);
		((LPD3DXSPRITE)display->spriteManager())->SetTransform(&mat);
	}
}

//draws the portion of the texture specified by a rectangle
void DeviceTexture::draw(const iTexture* texture, float x, float y, 
 float w, float h, unsigned char alpha, float l, float r, float tt, float b, float xMax, float yMax) {

	//actual texture width and height
	float tWidth = display->width() * w;
	float tHeight = display->height() * h;

	if (!tex) setup(texture, tWidth, tHeight, 0xFF000000);

	RECT rect;
		SetRect(&rect, 
		 (int)l*(tWidth/xMax),
		 (int)tt*(tHeight/yMax),
		 (int)r*(tWidth/xMax), 
		 (int)b*(tHeight/yMax));

	if (tex) {
		Vector topLeft(display->width() * x, 
		 display->height() * y, 0);
		((LPD3DXSPRITE)display->spriteManager())->Draw(tex, (RECT*)&rect, NULL, 
		 (D3DXVECTOR3*)&topLeft, 
		 D3DCOLOR_RGBA(SPRITE_R, SPRITE_G, SPRITE_B, alpha));
	}
}

// detach detaches the device texture from sampling stage i
//
void DeviceTexture::detach(int i) {

    if (tex)
        ((LPDIRECT3DDEVICE9)display->device())->SetTexture(i, NULL);
}

// suspend releases the device texture
//
void DeviceTexture::suspend() {

    // release the Interface to the texture COM object
    if (tex) {
        tex->Release();
        tex = NULL;
    }
}

// releases suspends the device texture
//
void DeviceTexture::release() {

    suspend();
}

// destructor suspends the device texture 
//
DeviceTexture::~DeviceTexture() {

   release();
}
