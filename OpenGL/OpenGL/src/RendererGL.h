#pragma once

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"


class RendererGL
{

public:
    void clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

};

