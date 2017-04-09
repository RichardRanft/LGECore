#pragma once
#ifndef _CSURFACE_H_
#define _CSURFACE_H_

#include <SDL.h>
#include <SDL_image.h>

class CSurface {
public:
	CSurface();

public:
	static SDL_Surface* OnLoad(char* File);
	static SDL_Surface* OnLoad(char* File, const SDL_Surface& Surf_Dest);
	static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y);
	static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H);
	static SDL_Surface* ScaleSurface(SDL_Surface* Surface, Uint16 Width, Uint16 Height);
};

#endif