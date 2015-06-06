/* Camera Implementation - Camera Component - Model Branch
 *
 * Camera.cpp
 * fwk4gps version 1.0
 * gam666/dps901
 * August 30 2010
 * copyright (c) 2010 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#include "iContext.h"        // for the Context Interface
#include "iViewing.h"        // for the Viewing Interface
#include "iUtilities.h"      // for error(), sprintf()

#include "FirstPersonCamera.h"          // for Camera class declaration
#include "MathDefinitions.h" // for math functions in model coordinates
#include "ModelSettings.h"   // for FLOOR, FORWARD_SPEED, ROT_SPEED, MAX_DESC

//-------------------------------- Camera -------------------------------------
//
// The Camera Primitive represents one viewpoint in the Viewing Component
//
// The Viewing Coordinator manages the Camera Instances
//
iViewing* FirstPersonCamera::coordinator = NULL;

// CreateCamera creates a Camera object, which implements the Camera Primitive
//
iCamera* CreateFirstPersonCamera(iContext* c) {
	return new FirstPersonCamera(c);
}

iCamera* CreateFirstPersonCameraWithMap(iContext* c, int map[20][20], int tileSize) {
	return new FirstPersonCamera(c, map, tileSize);
}

// constructor adds the Camera Instance to the Viewing Coordinator
//
FirstPersonCamera::FirstPersonCamera(iContext* c, int map[20][20], int tileSize) : context(c), host(NULL) {
	bumping_effect_coordinate = 0.0f;
	breathing_effect_coordinate = 0.0;
	breathing_effect_frequency = RYAN_DEFAULT_BREATHING_FREQUENCY;
	breathing_effect_magnitude = RYAN_DEFAULT_BREATHING_MAGNITUDE;
    if (!coordinator) error(L"Camera::00 Couldn\'t access the Viewing Coordinator");
    else if(!coordinator->add(this)) error(L"Camera::01 Couldn\'t add the camera to the Viewing Coordinator");
    #if MODEL_Z_AXIS == FAR_TO_NEAR
    rotatey(3.14159f);
    #endif
	/* RYAN: Copying map array */
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			received_map[i][j] = int(map[i][j]) % 4;
		}
	}
	tile_size = tileSize;
	point_of_interest_y = 0.0f;
    camera_text = CreateText(0, 0.2f, 1.0f, 0.4f, TXT_DEFAULT, L" Camera text ");
}
FirstPersonCamera::FirstPersonCamera(iContext* c) : context(c), host(NULL) {
	bumping_effect_coordinate = 0.0f;
	breathing_effect_coordinate = 0.0;
	breathing_effect_frequency = RYAN_DEFAULT_BREATHING_FREQUENCY;
	breathing_effect_magnitude = RYAN_DEFAULT_BREATHING_MAGNITUDE;
    if (!coordinator) error(L"Camera::00 Couldn\'t access the Viewing Coordinator");
    else if(!coordinator->add(this)) error(L"Camera::01 Couldn\'t add the camera to the Viewing Coordinator");
    #if MODEL_Z_AXIS == FAR_TO_NEAR
    rotatey(3.14159f);
    #endif
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			received_map[i][j] = 0;
		}
	}
	tile_size = 10;
	point_of_interest_y = 0.0f;
}

// attach attaches the Camera Instance to host Frame f
//
void FirstPersonCamera::attach(const iFrame* f) {

    host = f;
}

// update adjusts the camera's viewpoint and heading according
// to the user's interventions
//
void FirstPersonCamera::update(int delta) {

    int dx = 0, // pitch up/down
        dy = 0, // yaw left/right
        dz = 0; // advance/retreat

    // joystick input
    int jy = context->get(GF_CT_DSPY);
    int jr = context->get(GF_CT_ROTZ);
    //if (jy) dz = (int)(jy * CTR_DISPLACEMENT_FACTOR);
    //if (jr) dy = -(int)(jr * CTR_ROTATION_FACTOR); // can't test. ordered joystick. 

	// mouse input
	int x = context->get(GF_MS_POSX);
    int y = context->get(GF_MS_POSY);
    int z = context->get(GF_MS_ORIZ);
	if (x) dy -= (int)(x * RYAN_MOUSE_PANNING_SENSITIVITY); /* RYAN: added constant. See ModelSettings.h */
	


	float point_of_interest_sensitivity = 300.0f;
	if (y) {
		point_of_interest_y -= y;
		if (point_of_interest_y > point_of_interest_sensitivity) { point_of_interest_y = point_of_interest_sensitivity; }
		else if (point_of_interest_y < -point_of_interest_sensitivity) { point_of_interest_y = -point_of_interest_sensitivity; }
		//this->orient(*(new Matrix(*_trans))); 
	}
	Vector* t = new Vector(0, point_of_interest_y / point_of_interest_sensitivity, 0);
	wchar_t str[100];
	//Vector cur_heading = orientation('z');
	//wsprintf(str, L"cur heading[.%d .%d .%d]", int(cur_heading.x * 1000), int(cur_heading.y * 1000), int(cur_heading.z*1000));
	wsprintf(str, L"point of interest y [0 .%d 0] dy: %d", int(point_of_interest_y * 1000), y);
	//wsprintf(str, L"current position in the cell (%d,%d) case: %d ", int(current_x_in_the_cell), int(current_z_in_the_cell), _case);
	camera_text->set(str);

	//if (y) dx -= (int)(y * MOUSE_DISPLACEMENT_TO_WORLD_DISPLACEMENT); /* RYAN: z-displacement is controlled by keyboard. */ 
	//if (z) dx += (int)(z * MOUSE_ROTATION_TO_WORLD_ROTATION); /* RYAN: mouse wheel will not be used for now */
		
	// keyboard input
    if (context->pressed(CAM_ADVANCE)) dz += int(float(delta) * RYAN_CAMERA_ADVANCE_COEFFICIENT); /* RYAN: Added constant. Makes the movement faster */
    if (context->pressed(CAM_RETREAT)) dz -= int(float(delta) * RYAN_CAMERA_RETREAT_COEFFICIENT); /* RYAN: Added constant. See ModelSettings.h */
    if (context->pressed(CAM_YAW_LEFT)) dy += int(float(delta) * RYAN_KEYBOARD_PANNING_SENSITIVITY); /* RYAN: not needed */
    if (context->pressed(CAM_YAW_RIGHT)) dy -= int(float(delta) * RYAN_KEYBOARD_PANNING_SENSITIVITY); /* RYAN: not needed */
    //if (context->pressed(CAM_PITCH_UP)) dx -= delta; /* RYAN: not needed */
    //if (context->pressed(CAM_PITCH_DOWN)) dx += delta; /* RYAN: not needed */

	/* RYAN: accumulate displacement magnitudes and translate once */
	float disp_x = 0.0f;
	float disp_y = 0.0f;
	float disp_z = 0.0f;
	bool stop_breathing = false; /* RYAN: increases brething frequency if true */
	
	// adjust camera vectors
	if (dx || dy || dz) {
        // yaw left/right
		if (dy)
            rotatey(dy * ROT_SPEED);
		// pitch up/down
        if (dx) 
            rotatex(dx * ROT_SPEED);
		// Move forward/backward
        if (dz) { 
			stop_breathing = true;
			/* RYAN: Bumping effect */
			bumping_effect_coordinate += RYAN_STEPPING_FREQUENCY;
			float bumping_disp_y = sinf(bumping_effect_coordinate) * RYAN_STEPPING_MAGNITUDE;
			/* RYAN: Bumping effect end */
			Vector heading = orientation('z');
            Vector disp = (dz * FORWARD_SPEED) * heading; 
            //translate(disp.x, disp.y, disp.z * MODEL_Z_AXIS); /* RYAN: Translate all at once below */
			disp_x = disp.x;
			disp_y = disp.y + bumping_disp_y;
			disp_z = disp.z;
			// bottom out when we hit the floor
            Vector p = position();
            if (p.y <= FLOOR) {
				//translate(0, FLOOR - p.y, 0); /* RYAN: Translate all at once below */
                disp_y += FLOOR - p.y;
                heading = normal(heading);
                if (heading.y < 0) {
                    float rot = atanf(heading.y);
                    rotatex(rot);
                }
            }
        }

    }
	/* RYAN: simulating breathing */
	if (!stop_breathing) {
		breathing_effect_frequency -= RYAN_BREATHING_FREQUENCY_COEFFICIENT;
		breathing_effect_magnitude -= RYAN_BREATHING_MAGNITUDE_COEFFICIENT;
		if (breathing_effect_frequency < RYAN_DEFAULT_BREATHING_FREQUENCY) breathing_effect_frequency = RYAN_DEFAULT_BREATHING_FREQUENCY;
		if (breathing_effect_magnitude < RYAN_DEFAULT_BREATHING_MAGNITUDE) breathing_effect_magnitude = RYAN_DEFAULT_BREATHING_MAGNITUDE;
	} else {
		breathing_effect_frequency += (RYAN_BREATHING_FREQUENCY_COEFFICIENT * 2);
		breathing_effect_magnitude += (RYAN_BREATHING_MAGNITUDE_COEFFICIENT * 2);
		if (breathing_effect_frequency > RYAN_MAXIMUM_BREATHING_FREQUENCY) breathing_effect_frequency = RYAN_MAXIMUM_BREATHING_FREQUENCY;
		if (breathing_effect_magnitude > RYAN_MAXIMUM_BREATHING_MAGNITUDE) breathing_effect_magnitude = RYAN_MAXIMUM_BREATHING_MAGNITUDE;
	}
	breathing_effect_coordinate += breathing_effect_frequency;
	//translate(0, sinf(breathing_effect_coordinate) * breathing_effect_magnitude, 0);
	disp_y += sinf(breathing_effect_coordinate) * breathing_effect_magnitude;
	/* RYAN: SIMPLE COLLISION DETECTION AGAINST THE WALLS */
	Vector current_position = position();
	float current_x = current_position.x;
	float current_z = current_position.z;
	float target_x = current_position.x + disp_x;
	float target_z = current_position.z + disp_z;
	// revising displacements;
	float tile_offset = tile_size * 10;
	float safe_display_offset = 2.5f;
	float wall_thickness = 0.0f;
	float calculation_accuracy = 1000.0f;
	float current_x_in_the_cell = (int((current_x + tile_offset) * calculation_accuracy) % int(tile_size * calculation_accuracy)) / calculation_accuracy;
	float current_z_in_the_cell = (int((current_z + tile_offset) * calculation_accuracy) % int(tile_size * calculation_accuracy)) / calculation_accuracy;
	if (target_x > current_x) target_x += safe_display_offset;
	if (target_x < current_x) target_x -= safe_display_offset;
	if (target_z > current_z) target_z += safe_display_offset;
	if (target_z < current_z) target_z -= safe_display_offset;	
	int current_tile_index_x = int(floor((current_x + tile_offset) / tile_size));
	int target_tile_index_x = int(floor((target_x + tile_offset) / tile_size));
	int current_tile_index_z = int(floor((current_z + tile_offset) / tile_size));
	int target_tile_index_z = int(floor((target_z + tile_offset) / tile_size));
	int _case = 0;
	int _code = 0;
	
	if (current_tile_index_x >= 0 && current_tile_index_x < 20 && current_tile_index_z >= 0 && current_tile_index_z < 20) 
		_code =received_map[current_tile_index_z][current_tile_index_x];
	if (target_tile_index_x > current_tile_index_x) {
		// moving in pos-x direction - to left
		if (target_tile_index_x < 20) {
			int target_tile_code = received_map[current_tile_index_z][target_tile_index_x];
			if (target_tile_code == 2 || target_tile_code == 3) { disp_x = 0.0f; _case = 1;}
			else if (target_tile_code == 1 && current_z_in_the_cell < safe_display_offset + wall_thickness) {_case = 91; disp_x = 0.0f; }
			else if (current_z_in_the_cell > tile_size - safe_display_offset && current_tile_index_z + 1 < 20) {
				if (received_map[current_tile_index_z + 1][target_tile_index_x] == 1) { disp_x = 0.0f; _case = 92; }
			}
		} else { disp_x = 0.0f; _case = 2;}
	} else if (target_tile_index_x < current_tile_index_x) {
		// movingin in neg-x direction
		if (target_tile_index_x >= 0) {
			int current_tile_code = received_map[current_tile_index_z][current_tile_index_x];
			if (current_tile_code == 2 || current_tile_code == 3) { disp_x = 0.0f; _case = 3;}
			else {
				if ((received_map[current_tile_index_z][target_tile_index_x] == 1 || 
					received_map[current_tile_index_z][target_tile_index_x] == 3) && 
					current_z_in_the_cell < safe_display_offset + wall_thickness) { _case = 93; disp_x = 0.0f; }
				else if (current_z_in_the_cell > tile_size - safe_display_offset) { 
					if (current_tile_index_z + 1 < 20) {
						int target_code = received_map[current_tile_index_z + 1][target_tile_index_x];
						if (target_code == 1 || target_code == 3) {_case = 94; disp_x = 0.0f; }
					}
				}
			}
		} else { disp_x = 0.0f; _case=4;}
	} 
	if (target_tile_index_z > current_tile_index_z) {
		// moving in pos-z direction // check next cell
		if (target_tile_index_x < 20) {
			int target_tile_code = received_map[target_tile_index_z][current_tile_index_x];
			if (target_tile_code == 1 || target_tile_code == 3) { disp_z = 0.0f; _case = 5;}
			else if (target_tile_code == 2 && current_x_in_the_cell < safe_display_offset + wall_thickness)  { _case = 81; disp_z = 0.0f; }
			else {
				if (current_x_in_the_cell > tile_size - safe_display_offset && current_tile_index_x + 1 < 20) {
					if (received_map[target_tile_index_z][current_tile_index_x + 1] == 2) { disp_z = 0.0f; _case = 82; }
				}
			}
		} else { disp_z = 0.0f; _case = 6;}
	} else if (target_tile_index_z < current_tile_index_z) {
		// moving in neg-z direction // check current cell
		if (target_tile_index_z < 20) {
			int current_tile_code = received_map[current_tile_index_z][current_tile_index_x];
			if (current_tile_code == 1 || current_tile_code == 3) { disp_z = 0.0f; _case = 7;}
			else {
				int target_code = received_map[target_tile_index_z][current_tile_index_x];
				if ((target_code == 2 || target_code == 3) && current_x_in_the_cell < safe_display_offset + wall_thickness)  { _case = 83; disp_z = 0.0f; } 
				else if (current_x_in_the_cell > tile_size - safe_display_offset && current_tile_index_x + 1 < 20) { 
					target_code = received_map[target_tile_index_z][current_tile_index_x + 1];
					if (target_code == 2 || target_code == 3) { disp_z = 0.0f;_case = 84; }
				}
			}
		} else { disp_z = 0.0f; _case = 8;}
	}
	


    // store the current viewpoint, heading and up direction
    Vector p = host ? position() * host->world() : position();
    Vector h = host ? orientation('z') * host->rotation() : orientation('z');
    Vector u = host ? orientation('y') * host->rotation() : orientation('y');
	
	/* RYAN: COLLISION DETECTION CODE ENDS */
	translate(disp_x, disp_y, disp_z);
	if (context->pressed(TENTH_FLOOR_STARTOVER)) {
		/* RYAN: R key is remapped. Moves character to the start point */
		translate(-95 - position().x, 0, -95 - position().z);
		Vector* direction = new Vector(h.x, 0, h.y); 
	}
	
	


    context->set(GF_CA_POSN, p);
    context->set(GF_CA_HEAD, h + *t);
    context->set(GF_CA_UP,   u);
}

// destructor removes the Camera Instance from the Viewing Coordinator
//
FirstPersonCamera::~FirstPersonCamera() {

    if (coordinator)
        coordinator->remove(this);
    else
        error(L"Camera::90 Couldn\'t access the Viewing Coordinator");
}

// position returns the text string with the camera's position
//
const wchar_t* position(wchar_t* str, const iCamera* camera) {

	if (camera) {
        Vector p = camera->position();
        p.z *= Z_AXIS;
		sprintf(str, (int)p.x, (int)p.y, (int)p.z);
	}

	return str;
}

// heading returns the text string with the camera's heading
//
const wchar_t* heading(wchar_t* str, const iCamera* camera) {

	if (camera) {
        Vector h = camera->orientation('z');
        h.z *= Z_AXIS;
		sprintf(str, (int)(100 * h.x), (int)(100 * h.y), (int)(100 * h.z));
	}

	return str;
}
