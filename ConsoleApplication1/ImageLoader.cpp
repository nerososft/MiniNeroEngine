#include "ImageLoader.h"
#include "picoPNG.h"
#include "IOManager.h"
#include "Errors.h"

namespace NeroEngine {
	GLTexture ImageLoader::loadPNG(std::string filePath) {
		GLTexture texture = {};
		std::vector<unsigned char> in;
		std::vector<unsigned char> out;

		unsigned long width, height;

		if (IOManager::readFileToBuffer(filePath, in) == false) {
			fatalError("�ļ�" + filePath + "��ȡ����");
		}

		int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
		if (errorCode != 0) {
			fatalError("decodePNG ����" + std::to_string(errorCode));
		}

		glGenTextures(1, &(texture.id));

		glBindTexture(GL_TEXTURE_2D, texture.id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		texture.width = width;
		texture.height = height;

		return texture;

	}

	TGATexture ImageLoader::loadTGA(const char* filePath) {

		GLubyte     TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };    // Uncompressed TGA Header  
		GLubyte     TGAcompare[12];                             // Used To Compare TGA Header  
		GLubyte     header[6];                                  // First 6 Useful Bytes From The Header  
		GLuint      bytesPerPixel;                              // Holds Number Of Bytes Per Pixel Used In The TGA File  
		GLuint      imageSize;                                  // Used To Store The Image Size When Setting Aside Ram  
		GLuint      temp;                                       // Temporary Variable  
		GLuint      type = GL_RGBA;                               // Set The Default GL Mode To RBGA (32 BPP)  

		FILE *file = fopen(filePath, "rb");                     // Open The TGA File  


		TGATexture *texture = new TGATexture();

		if (file == NULL ||                                       // Does File Even Exist?  
			fread(TGAcompare, 1, sizeof(TGAcompare), file) != sizeof(TGAcompare) ||  // Are There 12 Bytes To Read?  
			memcmp(TGAheader, TGAcompare, sizeof(TGAheader)) != 0 ||  // Does The Header Match What We Want?  
			fread(header, 1, sizeof(header), file) != sizeof(header))                // If So Read Next 6 Header Bytes  
			{
			if (file == NULL) {                                   // Did The File Even Exist? *Added Jim Strong*  
			}
			else
			{
				fclose(file);                                   // If Anything Failed, Close The File                            // Return False  
			}
		}

		texture->width = header[1] * 256 + header[0];           // Determine The TGA Width  (highbyte*256+lowbyte)  
		texture->height = header[3] * 256 + header[2];           // Determine The TGA Height (highbyte*256+lowbyte)  

																 //OpenGL������ֻ��ʹ��24λ����32λ��TGAͼ��  
		if (texture->width <= 0 ||                              // Is The Width Less Than Or Equal To Zero  
			texture->height <= 0 ||                              // Is The Height Less Than Or Equal To Zero  
			(header[4] != 24 && header[4] != 32))                   // Is The TGA 24 or 32 Bit?  
		{
			fclose(file);                                       // If Anything Failed, Close The File                                        // Return False  
		}

		texture->bpp = header[4];                            // Grab The TGA's Bits Per Pixel (24 or 32)  
		bytesPerPixel = texture->bpp / 8;                        // Divide By 8 To Get The Bytes Per Pixel  
		imageSize = texture->width*texture->height*bytesPerPixel;   // Calculate The Memory Required For The TGA Data  

		texture->imageData = (GLubyte *)malloc(imageSize);     // Reserve Memory To Hold The TGA Data  

		if (texture->imageData == NULL ||                          // Does The Storage Memory Exist?  
			fread(texture->imageData, 1, imageSize, file) != imageSize)    // Does The Image Size Match The Memory Reserved?  
		{
			if (texture->imageData != NULL)                     // Was Image Data Loaded  
				free(texture->imageData);                        // If So, Release The Image Data  

			fclose(file);                                       // Close The File  
		}

		//RGB���ݸ�ʽת����������OpenGL��ʹ��  
		for (GLuint i = 0; i<int(imageSize); i += bytesPerPixel)      // Loop Through The Image Data  
		{                                                       // Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)  
			temp = texture->imageData[i];                          // Temporarily Store The Value At Image Data 'i'  
			texture->imageData[i] = texture->imageData[i + 2];    // Set The 1st Byte To The Value Of The 3rd Byte  
			texture->imageData[i + 2] = temp;                    // Set The 3rd Byte To The Value In 'temp' (1st Byte Value)  
		}

		fclose(file);                                          // Close The File  

															   // Build A Texture From The Data  
		glGenTextures(1, &texture[0].texID);                    // Generate OpenGL texture IDs  

		glBindTexture(GL_TEXTURE_2D, texture[0].texID);         // Bind Our Texture  
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   // Linear Filtered  
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   // Linear Filtered  

		if (texture[0].bpp == 24)                                 // Was The TGA 24 Bits  
		{
			type = GL_RGB;                                        // If So Set The 'type' To GL_RGB  
		}

		glTexImage2D(GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height, 0, type, GL_UNSIGNED_BYTE, texture[0].imageData);

		return texture[0];
	}
};