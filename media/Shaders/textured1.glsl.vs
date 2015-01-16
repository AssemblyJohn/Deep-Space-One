/**
 * Copyright (c) 2015 Lazu Ioan-Bogdan
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, without any restrictions.
 */

#version 120

attribute vec4 att_vertex;
attribute vec3 att_normal;
attribute vec2 att_uv;

uniform mat4 uni_mv;
uniform mat4 uni_proj;

varying vec2 textureCoord;

void main(void)
{
	textureCoord = vec2(att_uv.x, 1.0f - att_uv.y); // Mirror
	
    gl_Position = uni_proj * uni_mv * att_vertex;
}