//*****************************************************************************
//  ÉJÉÅÉâÇìÆÇ©Ç∑êl
//  author: íÜìáè´ç_
//  update: 2016/02/24
//*****************************************************************************
#ifndef _CAMERA_DIRECTOR_H_
#define _CAMERA_DIRECTOR_H_

#include "main.h"

#include <d3dx9.h>

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class BattleActor;
class Camera;
class CameraDirector{
public:

	CameraDirector(BattleActor* owner, Camera* camera);

	virtual ~CameraDirector();

	virtual void Update(void);

	//accessor
protected:
	BattleActor* _owner;
	Camera* _camera;
};



#endif//_NUMBER_H_