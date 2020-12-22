
//{{BLOCK(Water)

//======================================================================
//
//	Water, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 121 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 7744 + 2048 = 10304
//
//	Time-stamp: 2020-12-18, 15:09:38
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_WATER_H
#define GRIT_WATER_H

#define WaterTilesLen 7744
extern const unsigned int WaterTiles[1936];

#define WaterMapLen 2048
extern const unsigned short WaterMap[1024];

#define WaterPalLen 512
extern const unsigned short WaterPal[256];

#endif // GRIT_WATER_H

//}}BLOCK(Water)
