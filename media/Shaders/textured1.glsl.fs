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

varying vec2 textureCoord;

uniform sampler2D texture0;

void main(void)
{
    gl_FragColor = texture2D(texture0, textureCoord);
}