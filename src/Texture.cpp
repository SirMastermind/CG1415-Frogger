//
//  Texture.cpp
//  Proj_CG
//
//  Created by Tomás Alves on 11/11/14.
//  Copyright (c) 2014 Tomás Alves. All rights reserved.
//

#include "Texture.h"
#include "string.h"

Texture::Texture(void* data, int w, int h, int format){
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, format, GL_UNSIGNED_BYTE, data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture* Texture::loadBMP(const char* filename) {
    FILE* fp;
    fp = fopen(filename, "r");
    if(!fp) {
        cout << filename << " could not be loaded!" << endl;
        fclose(fp);
        return NULL;
    }
    char* headerField;
    headerField = (char*) malloc(sizeof(char)*3);
    fread(headerField, 2, sizeof(char), fp);
    headerField[2]='\0';
    if(strcmp(headerField, "BM")) {
        delete [] headerField;
        cout << "File is not a bitmap." << headerField << endl;
        fclose(fp);
        return NULL;
    }
    
    delete [] headerField;
    
    unsigned int bmpDataLocation;
    
    unsigned int bmpWidth;
    unsigned int bmpHeight;
    unsigned short numColorPlanes;
    unsigned short bitsPerPixel;
    unsigned int compressionMethod;
    unsigned int bmpDataSize;
    
    fseek(fp, 0x000A, SEEK_SET);
    fread(&bmpDataLocation, 1, sizeof(unsigned int), fp);
    
    fseek(fp, 0x0012, SEEK_SET);
    fread(&bmpWidth, 1, sizeof(unsigned int), fp);
    fseek(fp, 0x0016, SEEK_SET);
    fread(&bmpHeight, 1, sizeof(unsigned int), fp);
    bmpHeight = bmpWidth;
    fseek(fp, 0x001A, SEEK_SET);
    fread(&numColorPlanes, 1, sizeof(unsigned short), fp);
    fseek(fp, 0x001C, SEEK_SET);
    fread(&bitsPerPixel, 1, sizeof(unsigned short), fp);
    fseek(fp, 0x001E, SEEK_SET);
    fread(&compressionMethod, 1, sizeof(unsigned int), fp);
    fseek(fp, 0x0022, SEEK_SET);
    fread(&bmpDataSize, 1, sizeof(unsigned int), fp);
    
    if(numColorPlanes != 1 or bitsPerPixel != 24 or compressionMethod != 0) {
        cout << "File is not RAW BMP24." << endl;
        fclose(fp);
        return NULL;
    }
    
    unsigned char* bmpData = new unsigned char[bmpDataSize];
    
    fseek(fp, bmpDataLocation, SEEK_SET);
    fread(bmpData, bmpDataSize, sizeof(unsigned char), fp);
    
    fclose(fp);
    
    Texture* result = new Texture(bmpData, bmpWidth, bmpHeight, GL_RGB);
    
    return result;
}

unsigned int Texture::gettextureID() {
    return this->textureID;
}