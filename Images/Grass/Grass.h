
//{{BLOCK(Grass)

//======================================================================
//
//	Grass, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 121 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 7744 + 2048 = 10304
//
//	Time-stamp: 2020-12-18, 15:07:20
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_GRASS_H
#define GRIT_GRASS_H

#define GrassTilesLen 7744
extern const unsigned int GrassTiles[1936];

#define GrassMapLen 2048
extern const unsigned short GrassMap[1024];

#define GrassPalLen 512
extern const unsigned short GrassPal[256];

#endif // GRIT_GRASS_H

//}}BLOCK(Grass)
