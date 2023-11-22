#pragma once

#include <d3d12.h>
class TextureReference
{
public:
    TextureReference(ID3D12Resource* resource);
    ~TextureReference();

    void AddRef();
    void Release();
    ID3D12Resource* GetResource() const;

private:
    ID3D12Resource* textureResource_;
    unsigned int refCount_;
};


