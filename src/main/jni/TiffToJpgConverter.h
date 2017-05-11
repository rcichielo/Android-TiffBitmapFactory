//
// Created by beyka on 5/10/17.
//

#ifndef TIFFSAMPLE_TIFFTOJPGCONVERTER_H
#define TIFFSAMPLE_TIFFTOJPGCONVERTER_H

#include <stdlib.h>
#include <stdio.h>
#include <tiffio.h>
#include "fcntl.h"
#include "unistd.h"
#include "jpeglib.h"
#include <setjmp.h>
#include "BaseTiffConverter.h"

//extern "C" {
//#include "jpeglib.h"
//}

#define LOGI(x) __android_log_print(ANDROID_LOG_DEBUG, "TiffToJpgConverter", "%s", x)
#define LOGII(x, y) __android_log_print(ANDROID_LOG_DEBUG, "TiffToJpgConverter", "%s %d", x, y)
#define LOGIF(x, y) __android_log_print(ANDROID_LOG_DEBUG, "TiffToJpgConverter", "%s %f", x, y)
#define LOGIS(x, y) __android_log_print(ANDROID_LOG_DEBUG, "TiffToJpgConverter", "%s %s", x, y)

#define LOGE(x) __android_log_print(ANDROID_LOG_ERROR, "TiffToJpgConverter", "%s", x)
#define LOGES(x, y) __android_log_print(ANDROID_LOG_ERROR, "TiffToJpgConverter", "%s %s", x, y)

class TiffToJpgConverter : public BaseTiffConverter
{
    public:
        explicit TiffToJpgConverter(JNIEnv *, jclass, jstring, jstring, jobject);
        ~TiffToJpgConverter();
        virtual jboolean convert();

    private:
        static int const DECODE_METHOD_IMAGE = 1;
        static int const DECODE_METHOD_TILE = 2;
        static int const DECODE_METHOD_STRIP = 3;

        static int const JPEG_QUALITY = 90;

        int getDecodeMethod();
        void rotateTileLinesVertical(uint32, uint32, uint32 *, uint32 *);
        void rotateTileLinesHorizontal(uint32, uint32, uint32 *, uint32 *);
        jboolean convertFromImage();
        jboolean convertFromTile();
        jboolean convertFromStrip();

        TIFF *tiffImage;
        short origorientation;
        FILE *jpegFile;
        char jpeg_struct_init;
        struct jpeg_compress_struct cinfo;
        struct jpeg_error_mgr jerr;



};

#endif //TIFFSAMPLE_TIFFTOJPGCONVERTER_H