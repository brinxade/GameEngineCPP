#include"Camera.h"

const glm::mat4 Camera::DEFAULT_PROJECTION=glm::perspective(PROJECTION_FOV, (float)WINDOW_WIDTH / WINDOW_HEIGHT, PROJECTION_NEAR, PROJECTION_FAR);