#include "TextureReference.h"

TextureReference::TextureReference(ID3D12Resource* resource) : textureResource_(resource), refCount_(1) {}

TextureReference::~TextureReference() {
    // デストラクタでリソースを解放する
    if (textureResource_) {
        textureResource_->Release();
    }
}

void TextureReference::AddRef() {
    refCount_++;
}

void TextureReference::Release() {

    refCount_--;
    if (refCount_ == 0) {
        // 参照がなくなったらリソースを解放
        delete this;
    }
}

ID3D12Resource* TextureReference::GetResource() const {
    return textureResource_;
}