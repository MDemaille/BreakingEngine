#version 130
//precision highp float;
attribute vec3 position;
attribute vec3 normal;
uniform vec4 color;

uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

varying vec3 fNormal;
varying vec3 fPosition;

void main()
{
    fNormal = normalize(normalMatrix * normal);
    vec4 pos = modelViewMatrix * gl_Vertex;
    fPosition = pos.xyz;
    gl_FrontColor = gl_Color;
    gl_Position = projectionMatrix * pos;
}
