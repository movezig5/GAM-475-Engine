//----------------------------------------------------------------------------
// Copyright Ed Keenan 2018
// Gam 475
//----------------------------------------------------------------------------

// COLOR RENDER - Fragment Shader

#version 400 core

out vec4 color;

in VS_OUT
{
    vec4 color;
} fs_in;

void main(void)
{
    color = fs_in.color;
}

// --- End of File -----------------------------------------------------------
