﻿/**************************************************************************************************

 @File   : [ Hash.h ] ハッシュ値の生成を行うクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _HASH_H_
#define _HASH_H_

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
class Hash
{
public:
     Hash() {}
    ~Hash() {}

    //-----String -> Hash-----//
    static unsigned int CRC32Hash(char* value);
    static unsigned int CRC32Hash(std::string value);

    //-----Number -> Hash-----//
    static unsigned int CRC32Hash(int value);
    static unsigned int CRC32Hash(unsigned int value);

    static const unsigned int CRC32Table[256];
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
