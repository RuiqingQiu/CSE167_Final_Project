//
//  Sound.cpp
//  CSE167 Final Project
//
//  Created by Mingshan Wang on 12/12/14.
//  Copyright (c) 2014 Ruiqing Qiu. All rights reserved.
//

#include "Sound.h"
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

using namespace std;


Sound::Sound(int format, int sampleRate, void* data,int size){
    alGetError(); // clear any error messages
    // Generate buffers, or else no sound will happen!
    alGenBuffers((ALuint)1, &bufferID);
    if(alGetError() != AL_NO_ERROR)
    {
        printf("- Error creating buffers !!\n");
        exit(1);
    }
    else
    {
        printf("init() - No errors yet.\n");
    }
    
    alBufferData(bufferID,format,data,size,sampleRate);
    alGenSources((ALuint)1, &sourceID);
    alSourcei(sourceID, AL_BUFFER, bufferID);
    alSourcePlay(sourceID);
    
    this->format = format;
    this->sampleRate = sampleRate;
    this->data = data;
    this->size = size;
    
    //cout << "passed " << endl;
}


void Sound::play(){
    int state;
    alGetSourcei(sourceID, AL_SOURCE_STATE, &state);
    if(state != AL_PLAYING){
        alSourcePlay(sourceID);
    }
    
}

Sound* Sound::loadWAVE(const char* filename){
    FILE* fp = NULL;
    fp = fopen(filename, "rb");
    if(!fp){
        cout << "Couldn't open " << filename << "!" << endl;
        fclose(fp);
        return NULL;
    }
    
      //char* tmp = new char[4];
      char* ChunkID = new char[4];
      fread(ChunkID, 4, sizeof(char), fp);

//    ChunkID[0] = tmp[0];
//    ChunkID[1] = tmp[1];
//    ChunkID[2] = tmp[2];
//    ChunkID[3] = tmp[3];
//    //cout << ChunkID << endl;
//  
//    if(strcmp(ChunkID, "RIFF")){
//        delete[] ChunkID;
//        cout << "NOT RIFF " << endl;
//        fclose(fp);
//        return NULL;
//    }
    
    fseek(fp, 8, SEEK_SET);
    char* Format = new char[4];
    fread(Format, 4, sizeof(char), fp);
    //cout << Format << endl;
    
    if(strcmp(Format, "WAVE")){
        //delete [] ChunkID;
        delete[] Format;
        cout << "NOT WAVE " << endl;
        fclose(fp);
        return NULL;
    }
    
    char* SubChunk1ID = new char[4];
    fread(SubChunk1ID, 4, sizeof(char), fp);
    //cout << SubChunk1ID << endl;
    
    if(strcmp(SubChunk1ID, "fmt ")){
        delete [] ChunkID;
        delete[] Format;
        delete [] SubChunk1ID;
        cout << "Corrupt! " << endl;
        fclose(fp);
        return NULL;
    }
    
    unsigned int SubChunk1Size;
    fread(&SubChunk1Size, 1, sizeof(unsigned int), fp);
    //cout << SubChunk1Size << endl;
    unsigned int SubChunk2Location = (unsigned int)ftell(fp)+  SubChunk1Size;
    
    unsigned short AudioFormat;
    fread(&AudioFormat, 1, sizeof(unsigned short), fp);
    if(AudioFormat != 1){
        delete [] ChunkID;
        delete[] Format;
        delete [] SubChunk1ID;
        cout << "Audio is not PCM ! " << endl;
        fclose(fp);
        return NULL;
     }
    
    unsigned short NumChannels;
    fread(&NumChannels, 1, sizeof(unsigned short), fp);
    unsigned int SampleRate;
    fread(&SampleRate, 1, sizeof(unsigned int), fp);
    
    fseek(fp, 34, SEEK_SET);
    
    unsigned short BitsPerSample;
    fread(&BitsPerSample, 1, sizeof(unsigned short), fp);
    //cout << "bits per sample : "<<BitsPerSample << endl;
    
    int ALFormat;
    if(NumChannels == 1 && BitsPerSample == 8){
        ALFormat = AL_FORMAT_MONO8;
    }
    else if(NumChannels == 1 && BitsPerSample == 16){
        ALFormat = AL_FORMAT_MONO16;
    }
    else if(NumChannels == 2 && BitsPerSample == 8){
        ALFormat = AL_FORMAT_STEREO8;
    }
    else if(NumChannels == 2 && BitsPerSample == 16){
        ALFormat = AL_FORMAT_STEREO16;
    }else{
        delete [] ChunkID;
        delete[] Format;
        delete [] SubChunk1ID;
        cout << "Audio is not correctly formatted ! " << endl;
        fclose(fp);
        return NULL;
    }
    
    fseek(fp, SubChunk2Location, SEEK_SET);
    char* SubChunk2ID = new char[4];
    fread(SubChunk2ID, 4, sizeof(char), fp);
    
    //cout << SubChunk2ID << endl;
    if(strcmp(SubChunk2ID, "data")){
        delete [] ChunkID;
        delete [] Format;
        delete [] SubChunk1ID;
        delete [] SubChunk2ID;
        cout << "Corrupt ! " << endl;
        fclose(fp);
        return NULL;
     }
    
    unsigned int SubChunk2Size;
    fread(&SubChunk2Size, 1, sizeof(unsigned int), fp);
    cout << "SubChunk2Size is " << SubChunk2Size;
    
    unsigned char* Data = new unsigned char(SubChunk2Size);
    fread(Data, SubChunk2Size, sizeof(unsigned char), fp);
    cout << "Data is " << Data << endl;
    
    /*
    delete [] ChunkID;
    delete [] Format;
    delete [] SubChunk1ID;
    delete [] SubChunk2ID;
    */
    fclose(fp);
    return new Sound(ALFormat,SampleRate,Data,SubChunk2Size);
}

