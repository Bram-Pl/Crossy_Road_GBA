
//{{BLOCK(Tree)

//======================================================================
//
//	Tree, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 17 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 1088 + 2048 = 3648
//
//	Time-stamp: 2020-12-18, 15:08:57
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TREE_H
#define GRIT_TREE_H

#define TreeTilesLen 1088
extern const unsigned int TreeTiles[272];

#define TreeMapLen 2048
extern const unsigned short TreeMap[1024];

#define TreePalLen 512
extern const unsigned short TreePal[256];

#endif // GRIT_TREE_H

//}}BLOCK(Tree)
