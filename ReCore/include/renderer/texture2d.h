#pragma once

#include <iostream>
#include <string>
#include <glad.h>

class Texture2D
{
private:
	Texture2D();
public:
    ~Texture2D();

    void UpdateSubImage(int x, int y, int width, int height, unsigned int client_format, unsigned int data_type, unsigned char* data, unsigned int data_size);

public:
    struct TextureFileHead
    {
        char type_[3];
        int mipmap_level_;
        int width_;
        int height_;
        int gl_texture_format_;
        int compress_size_;
    };

    int mipmap_level() { return mipmap_level_; }
    int width() { return width_; }
    int height() { return height_; }
    GLenum gl_texture_format() { return gl_texture_format_; }
    unsigned int texture_handle() { return texture_handle_; }
    void set_texture_handle(unsigned int texture_handle) { texture_handle_ = texture_handle; }

public:
    static Texture2D* LoadFromFile(const std::string& image_file_path);
    static Texture2D* Create(unsigned short width, unsigned short height, unsigned int server_format, unsigned int client_format, unsigned int data_type, unsigned char* data, unsigned int data_size);

private:
    int mipmap_level_;
    int width_;
    int height_;
    GLenum gl_texture_format_;
    unsigned int texture_handle_;//Œ∆¿ÌID

};