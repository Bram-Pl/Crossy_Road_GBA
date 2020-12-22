
//{{BLOCK(Road)

//======================================================================
//
//	Road, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 25 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 1600 + 2048 = 4160
//
//	Time-stamp: 2020-12-18, 15:08:42
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_ROAD_H
#define GRIT_ROAD_H

#define RoadTilesLen 1600
extern const unsigned int RoadTiles[400];

#define RoadMapLen 2048
extern const unsigned short RoadMap[1024];

#define RoadPalLen 512
extern const unsigned short RoadPal[256];

#endif // GRIT_ROAD_H

//}}BLOCK(Road)
