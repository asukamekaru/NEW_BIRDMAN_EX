#include "DxLib.h"
#include "Main.h"
#include "Base.h"
#include "sceneTitle.h"
#include "DebugMode.h"

char TEXT;

bool DEBUG_MODE::initialize(){
	TEXT = NULL;
	return true;
}

void DEBUG_MODE::Release(){

}

bool DEBUG_MODE::Update(){
	if(iKey_Check(_KEY_MODE_TRG,_KEY_1))vChangeScene(new SCENE_TITLE());
	if(iKey_Check(_KEY_MODE_TRG,_KEY_2))TEXT = 'ÉGÉâÅ[';
	if(iKey_Check(_KEY_MODE_TRG,_KEY_3))TEXT = 'ERR';
	if(iKey_Check(_KEY_MODE_TRG,_KEY_4))TEXT = 'ERR';
	if(iKey_Check(_KEY_MODE_TRG,_KEY_5))TEXT = 'ERR';
	return true;
}

void DEBUG_MODE::Render(){
	SetFontSize(_FONTSIZE_M) ;
	DrawString( 0 , _FONTSIZE_M * 0, "PUSH TO NUMBER KEY ___DEBUG_MODE___" , _COLOR_RED ) ;
	SetFontSize(_FONTSIZE_S) ;
	DrawString( 0 , _FONTSIZE_S * 2, "KEY1 Title" , _COLOR_WHITE ) ;
	DrawString( 0 , _FONTSIZE_S * 3, "KEY2 ..." , _COLOR_WHITE ) ;
	DrawString( 0 , _FONTSIZE_S * 4, "KEY3 ..." , _COLOR_WHITE ) ;
	DrawString( 0 , _FONTSIZE_S * 5, "KEY4 ..." , _COLOR_WHITE ) ;

	SetFontSize(_FONTSIZE_M) ;
	DrawFormatString( 0 , _FONTSIZE_S * 8 , _COLOR_RED , "%c" , TEXT ) ;
}