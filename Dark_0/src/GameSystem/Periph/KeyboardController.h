#pragma once

#include <GameSystem/Creative/AppObject.h>
#include "Window.h"

namespace dark {

    class KeyboardController {

    public:
        struct KeyMappings {
            int moveLeft = GLFW_KEY_A;
            int moveRight = GLFW_KEY_D;
            int moveForward = GLFW_KEY_W;
            int moveBackward = GLFW_KEY_S;
            int moveUp = GLFW_KEY_E;
            int moveDown = GLFW_KEY_Q;
            int lookLeft = GLFW_KEY_LEFT;
            int lookRight = GLFW_KEY_RIGHT;
            int lookUp = GLFW_KEY_UP;
            int lookDown = GLFW_KEY_DOWN;
        };

        void moveInPlaneXZ(GLFWwindow* window, float dt, AppObject& appObject);

        KeyMappings keys{};
        float moveSpeed{ 0.01f };
        float lookSpeed{ 0.004f };

    };

}