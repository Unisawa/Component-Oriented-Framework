/**************************************************************************************************

 @File   : [ Constant.h ] プログラム内で使用する定数を全て管理するクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//

//***********************************************************************************************//
//                                                                                               //
//  @Class                                                                                       //
//                                                                                               //
//***********************************************************************************************//
class Constant
{
public:
     Constant() {}
    ~Constant() {}

    //-----Application Setting-----//
    static const std::string WINDOW_NAME;

    //-----Screen Size-----//
    static const float SCREEN_WIDTH;
    static const float SCREEN_HEIGHT;
    static const float SCREEN_WIDTH_HALF;
    static const float SCREEN_HEIGHT_HALF;

    //-----FilePath-----//
    static const std::string PATH_RESOURCE;
    static const std::string PATH_DATABASE;
    static const std::string PATH_NETWORK;
    static const std::string PATH_TEXTURE;
    static const std::string PATH_SHADER;
    static const std::string PATH_MAP;

    static const std::string PATH_MODEL;
    static const std::string PATH_MOTION;

    static const std::string PATH_AUDIO;
    static const std::string PATH_VOICE;
    static const std::string PATH_BGM;
    static const std::string PATH_SE;

    //-----Message-----//
    static const int MESSAGE_ERROR;
    static const int MESSAGE_SUCCESS;
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//