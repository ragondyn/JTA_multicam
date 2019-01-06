#ifndef SCENARIO_H
#define SCENARIO_H

#include "script.h"
#include <string>
#include "dictionary.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <gdiplus.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include "keyboard.h"

#pragma comment (lib,"Gdiplus.lib")

const int max_number_of_peds = 1024;					// size of the pedestrians array
const int number_of_joints = 21;							// size of the joint_ID subset
const float JOINT_DELTA = 0;
const int max_wpeds = 256;
const int max_number_of_cams = 8;						// size of the camera array

typedef struct wPed {
	Ped ped;
	bool goingTo = true;
	Vector3 from, to;
	int stopTime;
	int timeFix = -1;
	float speed;
} wPed;

class DatasetAnnotator
{
public:
	DatasetAnnotator(std::string output_path, const char* file_scenario, int max_samples, int is_night);
	int update();
	~DatasetAnnotator();

private:
	std::string output_path;
	int sequence_index;
	Player player;
	Ped playerPed;
	std::string line;								// string use the safe the fram data-line
	std::string log;
	Cam camera;										// camera #2remove
	//Cam cameras[max_number_of_cams];				// cameras
	int number_of_cameras;
	Vector3 cam_coords[max_number_of_cams];								// coordinates of the camera 2remove
	Vector3 cam_rot[max_number_of_cams];
	Vector3 wanderer;
	Ped entity_cam;
	Vector3 ped_spawn_pos;
	bool SHOW_JOINT_RECT;							// bool used to switch the rectangle drawing around the joint
	Ped ped_spawned[max_number_of_peds];
	int n_peds;
	int max_samples;
	std::vector<const char*> bad_scenarios; // 36
	int ped_with_cam;
	const char* file_scenario;
	wPed wPeds[max_wpeds];
	wPed wPeds_scenario[max_wpeds];
	int nwPeds = 0;
	int nwPeds_scenario = 0;
	int moving;
	Vector3 A, B, C;

	int windowWidth;
	int windowHeight;
	int secondsBeforeSaveImages;
	int captureFreq;								// How often to save samples
	int joint_int_codes[number_of_joints];
	int fov;
	int max_waiting_time = 0;
	int is_night;

	HWND hWnd;
	HDC hWindowDC;
	HDC hCaptureDC;
	HBITMAP hCaptureBitmap;

	float recordingPeriod;
	std::clock_t lastRecordingTime;
	int nsample;
	std::ofstream coords_file;								// file used to save joints coordinates data
	std::ofstream log_file;									// file used to save joints coordinates data

	CLSID pngClsid;

	void get_2D_from_3D(Vector3 v, float *x, float *y, int indexCam);
	void save_frame(int indexCam);																		// function used to capture frames internally, then private
	void setCameraFixed(Vector3 coords, Vector3 rot, float cam_z, int fov, int indexCam);
	void setCameraMoving(Vector3 A, Vector3 B, Vector3 C, int fov);							// function used to set the camera stuff
	void spawnPed(Vector3 spawnAreaCenter, int numPed);										// function used to spawn pedestrians at the beginning of the scenario
	Vector3 teleportPlayer(Vector3 pos);													// function used to teleport the player to a random position returned by the function
	void draw_text(char *text, float x, float y, float scale);
	void addwPed(Ped p, Vector3 from, Vector3 to, int stop, float spd);
	void spawn_peds_flow(Vector3 pos, Vector3 goFrom, Vector3 goTo, int npeds, int ngroup, int currentBehaviour, int task_time, int type, int radius, 
		int min_lenght, int time_between_walks, int spawning_radius, float speed);
	void spawn_peds(Vector3 pos, Vector3 goFrom, Vector3 goTo, int npeds, int ngroup, int currentBehaviour,
		int task_time, int type, int radius, int min_lenght, int time_between_walks, int spawning_radius, float speed);
	void loadScenario(const char* fname);
	void walking_peds();
	int myreadLine(FILE *f, Vector3 *pos, int *nPeds, int *ngroup, int *currentBehaviour, float *speed, Vector3 *goFrom, Vector3 *goTo, int *task_time,
		int *type, int *radius, int *min_lenght, int *time_between_walks, int *spawning_radius);
	
	void addwPed_scenario(Ped p);
	Cam lockCam(Vector3 pos, Vector3 rot);
};

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

#endif // !SCENARIO_H
