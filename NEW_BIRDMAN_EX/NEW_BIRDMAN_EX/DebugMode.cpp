#include "DxLib.h"
#include "Main.h"
#include "sceneTitle.h"
#include "DebugMode.h"

char *TEXT;
int iNowSelect = 0;

enum{
	NUMBER,
	CHAR_P1,
	CHAR_P2,
	STAGE
};

char *character[14] ={"�o�[�h�}��","�_��","�K�`���s��","���N","�J���E���[","MR.","���[","�T���{�[�O","�V�[�t","�W���j�[��","���X�C���[","zip","��","�f��",};

int iselect = 0;

bool DEBUG_MODE::initialize(){
	TEXT = NULL;
	return true;
}

void DEBUG_MODE::Release(){

}

bool DEBUG_MODE::Update(){

	switch(iNowSelect){
	case NUMBER:
		if(iKey_Check(_KEY_MODE_TRG,_KEY_1))vChangeScene(new SCENE_TITLE());
		if(iKey_Check(_KEY_MODE_TRG,_KEY_2))iNowSelect = CHAR_P1;
		if(iKey_Check(_KEY_MODE_TRG,_KEY_3))TEXT = "no scene _ Key3";
		if(iKey_Check(_KEY_MODE_TRG,_KEY_4))TEXT = "no scene _ Key4";
		if(iKey_Check(_KEY_MODE_TRG,_KEY_5))TEXT = "no scene _ Key5";
		break;
	case CHAR_P1:
		if(iKey_Check(_KEY_MODE_TRG,_KEY_LEFT))iselect = (iselect == 0) ? 13 : iselect -= 1;//��
		if(iKey_Check(_KEY_MODE_TRG,_KEY_RIGHT))iselect = (iselect == 13) ? 0 : iselect += 1;//�E
		if(iKey_Check(_KEY_MODE_TRG,_KEY_SPACE))iNowChar1P = iselect;
		break;
	case CHAR_P2:
		if(iKey_Check(_KEY_MODE_TRG,_KEY_LEFT))iselect = (iselect == 0) ? 13 : iselect -= 1;//��
		if(iKey_Check(_KEY_MODE_TRG,_KEY_RIGHT))iselect = (iselect == 13) ? 0 : iselect += 1;//�E
		if(iKey_Check(_KEY_MODE_TRG,_KEY_SPACE))iNowChar2P = iselect;
		break;
	case STAGE:
		if(iKey_Check(_KEY_MODE_TRG,_KEY_LEFT))iselect = (iselect == 0) ? 13 : iselect -= 1;//��
		if(iKey_Check(_KEY_MODE_TRG,_KEY_RIGHT))iselect = (iselect >= 10) ? 0 : iselect += 1;//�E
		if(iKey_Check(_KEY_MODE_TRG,_KEY_SPACE))iNowStage = iselect;
		break;
	}
	return true;
}

void DEBUG_MODE::Render(){

	switch(iNowSelect){
	case NUMBER:
		SceneSelect();
		break;
	case CHAR_P1:
		CharSelectP1();
		break;
	case CHAR_P2:
		CharSelectP2();
		break;
	case STAGE:
		StageSelect();
		break;
	}
}

void DEBUG_MODE::SceneSelect(){
	SetFontSize(_FONTSIZE_M) ;
	DrawString( 0 , _FONTSIZE_M * 0, "PUSH TO NUMBER KEY ___DEBUG_MODE___" , _COLOR_RED ) ;
	SetFontSize(_FONTSIZE_S) ;
	DrawString( 0 , _FONTSIZE_S * 2, "KEY1 Title" , _COLOR_WHITE ) ;
	DrawString( 0 , _FONTSIZE_S * 3, "KEY2 Main" , _COLOR_WHITE ) ;
	DrawString( 0 , _FONTSIZE_S * 4, "KEY3 ..." , _COLOR_WHITE ) ;
	DrawString( 0 , _FONTSIZE_S * 5, "KEY4 ..." , _COLOR_WHITE ) ;

	SetFontSize(_FONTSIZE_M) ;
	DrawFormatString( 0 , _FONTSIZE_S * 8 , _COLOR_RED , "%s" , TEXT ) ;
}

void DEBUG_MODE::CharSelectP1(){
	SetFontSize(_FONTSIZE_M) ;
	DrawString( 0 , _FONTSIZE_M * 0, "SELECT CHAR P1" , _COLOR_RED ) ;
	DrawString( 0 , _FONTSIZE_M * 1, "PUSH �� ��" , _COLOR_RED ) ;
	DrawString( 0 , _FONTSIZE_M * 1, "PUSH SPACE" , _COLOR_RED ) ;
	DrawFormatString( 0 , _FONTSIZE_S * 8 , _COLOR_RED , "%s" , character[iselect] ) ;
}

void DEBUG_MODE::CharSelectP2(){
	SetFontSize(_FONTSIZE_M) ;
	DrawString( 0 , _FONTSIZE_M * 0, "SELECT CHAR P2" , _COLOR_RED ) ;
	DrawString( 0 , _FONTSIZE_M * 1, "PUSH �� ��" , _COLOR_RED ) ;
	DrawString( 0 , _FONTSIZE_M * 1, "PUSH SPACE" , _COLOR_RED ) ;
	DrawFormatString( 0 , _FONTSIZE_S * 8 , _COLOR_RED , "%s" , character[iselect] ) ;
}

void DEBUG_MODE::StageSelect(){
	SetFontSize(_FONTSIZE_M) ;
	DrawString( 0 , _FONTSIZE_M * 0, "SELECT STAGE" , _COLOR_RED ) ;
	DrawString( 0 , _FONTSIZE_M * 1, "PUSH �� ��" , _COLOR_RED ) ;
	DrawString( 0 , _FONTSIZE_M * 1, "PUSH SPACE" , _COLOR_RED ) ;
	DrawFormatString( 0 , _FONTSIZE_S * 8 , _COLOR_RED , "STAGE %s" , iselect ) ;
}