#include "renderer/texture2d.h"
#include <fstream>

Texture2D::Texture2D() : mipmap_level_(0), width_(0), height_(0), gl_texture_format_(0), texture_handle_(0)
{

}

Texture2D::~Texture2D() {
    if (texture_handle_ > 0) {
        //RenderTaskProducer::ProduceRenderTaskDeleteTextures(1, &texture_handle_);
    }
}

void Texture2D::UpdateSubImage(int x, int y, int width, int height, unsigned int client_format, unsigned int data_type,
    unsigned char* data, unsigned int data_size) {
    if (width <= 0 || height <= 0) {
        return;
    }
    //RenderTaskProducer::ProduceRenderTaskUpdateTextureSubImage2D(texture_handle_, x, y, width, height, client_format, data_type, data, data_size);
}

Texture2D* Texture2D::LoadFromFile(const std::string& image_file_path)
{
    if (image_file_path.empty()) {
        //LOG_ERROR("image_file_path empty");
        return nullptr;
    }

    Texture2D* texture2d = new Texture2D();

    //读取 cpt 压缩纹理文件
    std::ifstream input_file_stream(image_file_path, std::ios::in | std::ios::binary);
    TextureFileHead cpt_file_head;
    input_file_stream.read((char*)&cpt_file_head, sizeof(TextureFileHead));

    unsigned char* data = (unsigned char*)malloc(cpt_file_head.compress_size_);
    input_file_stream.read((char*)data, cpt_file_head.compress_size_);
    input_file_stream.close();

    texture2d->gl_texture_format_ = cpt_file_head.gl_texture_format_;
    texture2d->width_ = cpt_file_head.width_;
    texture2d->height_ = cpt_file_head.height_;


    //1. 通知显卡创建纹理对象，返回句柄;
    glGenTextures(1, &(texture2d->texture_handle_));

    //2. 将纹理绑定到特定纹理目标;
    glBindTexture(GL_TEXTURE_2D, texture2d->texture_handle_);

    //3. 将压缩纹理数据上传到GPU;
    glCompressedTexImage2D(GL_TEXTURE_2D, 0, texture2d->gl_texture_format_, texture2d->width_, texture2d->height_, 0, cpt_file_head.compress_size_, data);

    //4. 指定放大，缩小滤波方式，线性滤波，即放大缩小的插值方式;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    free (data);

    return texture2d;
}

Texture2D* Texture2D::Create(unsigned short width, unsigned short height, unsigned int server_format, unsigned int client_format,
    unsigned int data_type, unsigned char* data, unsigned int data_size) {
    Texture2D* texture2d = new Texture2D();
    texture2d->gl_texture_format_ = server_format;
    texture2d->width_ = width;
    texture2d->height_ = height;

    glGenTextures(1, &(texture2d->texture_handle_));
    glBindTexture(GL_TEXTURE_2D, texture2d->texture_handle_);
    glTexImage2D(GL_TEXTURE_2D, 0, texture2d->gl_texture_format_, texture2d->width_, texture2d->height_, 0, client_format, data_type, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    //texture2d->texture_handle_ = GPUResourceMapper::GenerateTextureHandle();

    // 发出任务：创建纹理
    //RenderTaskProducer::ProduceRenderTaskCreateTexImage2D(texture2d->texture_handle_, texture2d->width_, texture2d->height_, texture2d->gl_texture_format_, client_format, data_type, data_size, data);

    return texture2d;
}