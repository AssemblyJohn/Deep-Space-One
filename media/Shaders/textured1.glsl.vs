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
uniform vec3 light_pos = vec3(0, 0, 0);

varying vec2 textureCoord;

varying vec3 N;
varying vec3 L;
varying vec3 V;

void main(void)
{	
	// Better float precision in view space
    vec4 P = uni_mv * att_vertex;

    N = mat3(uni_mv) * att_normal;
    L = light_pos - P.xyz;
    V = -P.xyz;

	// Mirror
	textureCoord = vec2(att_uv.x, 1.0f - att_uv.y);

    gl_Position = uni_proj * P;
}