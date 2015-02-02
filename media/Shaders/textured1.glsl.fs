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

varying vec3 N;
varying vec3 L;
varying vec3 V;

uniform sampler2D texture0;

void main(void)
{    
    // Rename these so we don't have problems
    vec3 N_norm = normalize(N);
    vec3 L_norm = normalize(L);
    vec3 V_norm = normalize(V);
    vec3 H_norm = normalize(L + V);

    vec3 diffuse_albedo = texture2D(texture0, textureCoord).xyz;
    vec3 diffuse = max(dot(N_norm, L_norm), 0.0) * diffuse_albedo;
    
    vec3 specular_albedo = vec3(0.1);    
    float specular_power = 50.0;
    
    vec3 specular = pow(max(dot(N_norm, H_norm), 0.0), specular_power) * specular_albedo;

    gl_FragColor = vec4(diffuse + specular, 1.0);    
}