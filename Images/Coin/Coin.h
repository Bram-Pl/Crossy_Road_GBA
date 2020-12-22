
//{{BLOCK(Coin)

//======================================================================
//
//	Coin, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 17 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 1088 + 2048 = 3648
//
//	Time-stamp: 2020-12-18, 15:06:25
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_COIN_H
#define GRIT_COIN_H

#define CoinTilesLen 1088
extern const unsigned int CoinTiles[272];

#define CoinMapLen 2048
extern const unsigned short CoinMap[1024];

#define CoinPalLen 512
extern const unsigned short CoinPal[256];

#endif // GRIT_COIN_H

//}}BLOCK(Coin)
