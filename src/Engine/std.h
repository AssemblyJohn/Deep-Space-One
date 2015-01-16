#ifndef EN_STD_H
#define EN_STD_H

// Exterior
#include <string.h>

#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"

// OpenGL
#include "glinclude.h"

// Types
#include "types.h"
#include "Scalar.h"

// Utilitaries
#include "Profiler.h"
#include "Memory.h"
#include "String.h"
#include "Timing.h"
#include "Threading.h"

#include "Importer.h"

// System
#include "Input.h"

#include "Config.h"
#include "Video.h"

// Runtime
#include "Class.h"

// Math stuff
#include "Vector.h"
#include "Matrix.h"
#include "Math.h"
#include "AABB.h"
#include "Edge.h"

// Render stuff
#include "Mesh.h"
#include "Texture.h"
#include "Model.h"

#include "Renderer.h"
#include "DriverOgl.h"
#include "Program.h"
#include "ShaderUtils.h"

// Render utils
#include "ModelManager.h"

// Game
#include "Game.h"
#include "PhysicsEngine.h"

// Components
#include "Script.h"
#include "Physics.h"

// View
#include "Camera.h"

#endif