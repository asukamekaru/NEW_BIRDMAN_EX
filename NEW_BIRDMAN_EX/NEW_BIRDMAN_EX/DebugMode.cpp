#include "Main.h"
#include "Base.h"
#include "DebugMode.h"

bool DEBUG_MODE::initialize(){

	return true;
}

void DEBUG_MODE::Release(){

}

bool DEBUG_MODE::Update(){
	return true;
}

void DEBUG_MODE::Render(){
	DrawString( 0 , 0 , "a" , 0x000000 ) ;
}