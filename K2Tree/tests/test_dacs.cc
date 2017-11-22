//
// Created by zhaocheng on 17-11-22.
//

#include <gtest/gtest.h>
#include <cstdlib>
#include <string>
#include <utils/file.h>
extern "C" {
    #include <dacs.h>
}

TEST(dacs, test1) {
    typedef unsigned int uint;
    uint * list, bytesFile, listLength,i;
    FILE * flist;
    const char* file_in = "tmp.bin";
    char* file_out = "ret.bin";

    bytesFile = libk2tree::utils::get_file_size(file_in);
    listLength = bytesFile / sizeof(uint);
    if (!bytesFile) {
        fprintf(stderr, "\nFILE EMPTY OR FILE NOT FOUND !!\nConstruction aborted\n");
        exit(0);
    }

    flist = fopen(file_in,"r");
    list = (uint *) malloc(sizeof(uint)*listLength);
    fread(list,sizeof(uint),listLength,flist);
    fclose(flist);


    FTRep* listRep = createFT(list,listLength);

    uint * listaux;


    /*Test: decompression*/
    listaux = decompressFT(listRep,listLength);
    uint conterrors = 0;
    for(i=0;i<listLength;i++)
        if(listaux[i]!=list[i]){
            fprintf(stderr,"Error on decompressFT, the %d-th decompressed element does not match with the original list\n",i+1);
            conterrors ++;
        }
    fprintf(stderr," Test: decompression -> %d mismatches\n", conterrors);
    free(listaux);

    /*Test: direct access*/


    uint value;
    conterrors = 0;
    for(i=0;i<listLength;i++){
        value = accessFT(listRep, i+1);
        if(value!=list[i]){
            conterrors ++;
            fprintf(stderr,"Error on decompressFT, the %d-th decompressed element does not match with the original list\n",i+1);
        }
    }
    fprintf(stderr," Test: direct access -> %d mismatches\n", conterrors);


    saveFT(listRep,file_out);
    fprintf(stderr,"\n\n Representation saved.\n");

    destroyFT(listRep);
    free(list);
}