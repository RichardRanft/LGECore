#include "CSurface.h"

CSurface::CSurface() 
{

}

CSurface::CSurface(lua_State* L)
{
	m_state = L;
}

CSurface::~CSurface()
{

}

SDL_Surface* CSurface::OnLoad(char* File) {
	SDL_Surface* Surf_Temp = NULL;
	SDL_Surface* Surf_Return = NULL;

	if ((Surf_Temp = IMG_Load(File)) == NULL) {
		if ((Surf_Temp = IMG_Load(File)) == NULL)
		{
			return NULL;
		}
	}

	Surf_Return = SDL_ConvertSurfaceFormat(Surf_Temp, 0, 0);
	SDL_FreeSurface(Surf_Temp);

	return Surf_Return;
}

SDL_Surface* CSurface::OnLoad(char* File, const SDL_Surface& Surf_Dest) {
	SDL_Surface* Surf_Temp = NULL;
	SDL_Surface* Surf_Return = NULL;

	if ((Surf_Temp = SDL_LoadBMP(File)) == NULL) {
		if ((Surf_Temp = IMG_Load(File)) == NULL)
		{
			return NULL;
		}
	}

	Surf_Return = SDL_ConvertSurfaceFormat(Surf_Temp, Surf_Dest.format->format, Surf_Dest.flags);
	SDL_FreeSurface(Surf_Temp);

	return Surf_Return;
}

bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y) {
	if (Surf_Dest == NULL || Surf_Src == NULL) {
		return false;
	}

	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;

	SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);

	return true;
}

bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H) {
	if (Surf_Dest == NULL || Surf_Src == NULL) {
		return false;
	}

	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;

	SDL_Rect SrcR;

	SrcR.x = X2;
	SrcR.y = Y2;
	SrcR.w = W;
	SrcR.h = H;

	SDL_BlitSurface(Surf_Src, &SrcR, Surf_Dest, &DestR);

	return true;
}

SDL_Surface* CSurface::ScaleSurface(SDL_Surface* Surface, Uint16 Width, Uint16 Height)
{
	if (!Surface || !Width || !Height)
		return 0;

	SDL_Surface *_ret = SDL_CreateRGBSurface(Surface->flags, Width, Height, Surface->format->BitsPerPixel,
		Surface->format->Rmask, Surface->format->Gmask, Surface->format->Bmask, Surface->format->Amask);

	double    _stretch_factor_x = (static_cast<double>(Width) / static_cast<double>(Surface->w)),
		_stretch_factor_y = (static_cast<double>(Height) / static_cast<double>(Surface->h));

	SDL_Rect *src = new SDL_Rect(Surface->clip_rect);
	SDL_Rect *tgt = new SDL_Rect(_ret->clip_rect);
	int res = SDL_BlitScaled(Surface, src, _ret, tgt);

	return _ret;
}

// Lua interface
int CSurface::setTarget(lua_State* L)
{
	return 1;
}

int CSurface::getTarget(lua_State* L)
{
	return 1;
}

int CSurface::setScale(lua_State* L)
{
	return 1;
}

int CSurface::getScale(lua_State* L)
{
	return 1;
}

int CSurface::setPosition(lua_State* L)
{
	return 1;
}

int CSurface::getPosition(lua_State* L)
{
	return 1;
}

const char *CSurface::className = "CSurface";
const Luna < CSurface >::FunctionType CSurface::methods[] = {
	{ "setTarget", &CSurface::setTarget },
	{ "getTarget", &CSurface::getTarget },
	{ "setScale", &CSurface::setScale },
	{ "getScale", &CSurface::getScale },
	{ "setScale", &CSurface::setScale },
	{ "getScale", &CSurface::getScale },
	{ "setPosition", &CSurface::setPosition },
	{ "getPosition", &CSurface::getPosition },
	{ 0 }
};

const Luna < CSurface >::PropertyType CSurface::properties[] = {
	{ 0 }
};
