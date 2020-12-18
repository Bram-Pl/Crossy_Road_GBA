
//{{BLOCK(Car)

//======================================================================
//
//	Car, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 14 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 896 + 2048 = 3456
//
//	Time-stamp: 2020-12-18, 15:05:22
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_CAR_H
#define GRIT_CAR_H

#define CarTilesLen 896
extern const unsigned int CarTiles[224];

#define CarMapLen 2048
extern const unsigned short CarMap[1024];

#define CarPalLen 512
extern const unsigned short CarPal[256];

#endif // GRIT_CAR_H

//}}BLOCK(Car)
